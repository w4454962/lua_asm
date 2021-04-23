#pragma once
#include "stdlib.h"

#include "binary.h"

#include <string>
#include <Windows.h>
#include <memory>
#include <vector>
int lua_error_print(lua_State* L, const char* err, ...);
extern std::map<std::string, BinaryData*> symbol_map;

static int ldelete(lua_State* L)
{
    BinaryData** ptr = (BinaryData**)luaL_checkudata(L, 1, "binarydata");
    luaL_argcheck(L, ptr != NULL, 1, "invalid user data");
	BinaryData* data = *ptr;

	if (data == nullptr)
		return 0;

	std::vector<std::string> list;

	for (auto&& [k, v] : data->ref_map)
	{
		if (v != data && v->ref_count-- <= 0)
		{
			symbol_map.erase(k);
			list.push_back(k);
			if (v->code)
			{
				VirtualFree(v->code, 0, MEM_RELEASE);
				v->code = 0;
			}
			
			delete v;
		}
	}
	for (auto& k : list)
	{
		data->ref_map.erase(k);
	}

	if (data->ref_count-- <= 0)
	{
		symbol_map.erase(data->name);
		if (data->code)
		{
			VirtualFree(data->code, 0, MEM_RELEASE);
			data->code = 0;
		}
		delete data;
		*ptr = nullptr;
	}
	
    return 0;
}

static int lgetaddress(lua_State* L)
{
    BinaryData** ptr = (BinaryData**)luaL_checkudata(L, 1, "binarydata");
    luaL_argcheck(L, ptr != NULL, 1, "invalid user data");
	BinaryData* data = *ptr;
    lua_pushinteger(L, (uintptr_t)data->code);
    return 1;
}


#define intval sizeof uintptr_t

uintptr_t c_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval = 0;

	for (size_t i = param_list_size; i > 0; i -= intval)
	{
		uintptr_t data = *(uintptr_t*)((uintptr_t)param_list + i - intval);
		_asm push data 
	}
	_asm
	{
		call func_address
		add esp, param_list_size
		mov retval, eax 
	}
	return retval;
}

uintptr_t std_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval;
	
	for (size_t i = param_list_size; i > 0; i -= intval)
	{
		uintptr_t data = *(uintptr_t*)((uintptr_t)param_list + i - intval);
		_asm push data
	}
	_asm
	{
		call func_address
		mov retval, eax
	} 
	return retval;
}
uintptr_t this_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval;
	uintptr_t first = param_list[0];
	for (size_t i = param_list_size; i > intval; i -= intval)
	{
		uintptr_t data = *(uintptr_t*)((uintptr_t)param_list + i - intval);
		_asm push data
	}
	param_list_size -= intval;
	_asm
	{
		mov ecx, first
		call func_address
		add esp, param_list_size
		mov retval, eax
	}
	return retval;
}

uintptr_t fast_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval;
	uintptr_t first = param_list[0];
	uintptr_t second = param_list[1];
	for (size_t i = param_list_size; i > intval * 2; i -= intval)
	{
		uintptr_t data = *(uintptr_t*)((uintptr_t)param_list + i - intval);
		_asm push data
	}
	param_list_size -= intval * 2;
	_asm
	{
		mov ecx, first
		mov edx, second
		call func_address
		add esp, param_list_size
		mov retval, eax
	}
	return retval;
}


uintptr_t call(CALL_TYPE type, uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	switch (type)
	{
	case C_CALL:
		return c_call(func_address, param_list, param_list_size);
		break;
	case STD_CALL:
		return std_call(func_address, param_list, param_list_size);
		break;
	case THIS_CALL:
		return this_call(func_address, param_list, param_list_size);
		break;
	case FAST_CALL:
		return fast_call(func_address, param_list, param_list_size);
		break;
	default:
		break;
	}
	return 0;
}

static int lcall(lua_State* L, CALL_TYPE type)
{

    BinaryData** ptr = (BinaryData**)luaL_checkudata(L, 1, "binarydata");
    luaL_argcheck(L, ptr != NULL, 1, "invalid user data");
	BinaryData* data = *ptr;
    const char* param = data->params;

	double real_stack[0x100];
	uintptr_t param_list[0x100];;
	uintptr_t input = 0, value = 0, param_count = 0;
	ZeroMemory(param_list, sizeof(param_list));

	for (int i = 0; i < (int)strlen(param); i++)
	{
		uintptr_t pushvalue = 0;
		switch (param[i])
		{
		case ')':
			value = call(type, (uintptr_t)data->code, param_list, param_count * sizeof(uintptr_t));
			input = 0;
			break;
		case '(':
			input = 1;
			break;
		case 'I':
		{
			if (input)
				pushvalue = lua_tointeger(L, param_count + 2);
			else
				lua_pushinteger(L, value);
			break;
		}
		case 'R':
		{
			if (input)
			{

				real_stack[param_count] = lua_tonumber(L, param_count + 2);
				pushvalue = (uint32_t)&real_stack[param_count];
			}
			else
				lua_pushnumber(L, *(double*)&value);
			break;
		}
		case 'S':
		{
			if (input)
				pushvalue = (uint32_t)lua_tostring(L, param_count + 2);
			
			else
				lua_pushstring(L, (const char*)value);
			break;
		}
		case 'B':
		{
			if (input)
				pushvalue = lua_toboolean(L, param_count + 2);
			else
				lua_pushboolean(L, value);
			break;
		}
	
		default:
			break;
		}

		if (input && param[i] != ')' && param[i] != '(')
		{
			param_list[param_count++] = pushvalue;
		}
		
	}
	return 1;
}

int lua_c_call(lua_State* L)
{
	return lcall(L, C_CALL);
}

int lua_std_call(lua_State* L)
{
	return lcall(L, STD_CALL);
}

int lua_this_call(lua_State* L)
{
	if (lua_gettop(L) < 2)
		lua_error_print(L, "miss parameter");

	return lcall(L, THIS_CALL);
}

int lua_fast_call(lua_State* L)
{
	if (lua_gettop(L) < 3)
		lua_error_print(L, "miss parameter");
	
	return lcall(L, FAST_CALL);
}

int register_binary_class(lua_State* L)
{
    luaL_newmetatable(L, "binarydata");

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    lua_pushcfunction(L, ldelete);
    lua_setfield(L, -2, "__gc");

    lua_pushcfunction(L, lgetaddress);
    lua_setfield(L, -2, "get_address");

	lua_pushcfunction(L, lua_c_call);
	lua_setfield(L, -2, "__call");

    lua_pushcfunction(L, lua_c_call);
    lua_setfield(L, -2, "c_call");

	lua_pushcfunction(L, lua_std_call);
	lua_setfield(L, -2, "std_call");

	lua_pushcfunction(L, lua_this_call);
	lua_setfield(L, -2, "this_call");

	lua_pushcfunction(L, lua_fast_call);
	lua_setfield(L, -2, "fast_call");

    return 1;
}