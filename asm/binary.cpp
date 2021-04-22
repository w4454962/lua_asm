#pragma once
#include "stdlib.h"

#include "binary.h"
#include "fp_call.h"
#include <string>
#include <Windows.h>
#include <memory>

static int ldelete(lua_State* L)
{
    BinaryData* data = (BinaryData*)luaL_checkudata(L, 1, "binarydata");
    luaL_argcheck(L, data != NULL, 1, "invalid user data");

    delete data->code;
    delete data;
    return 0;
}

static int lgetaddress(lua_State* L)
{
    BinaryData* data = (BinaryData*)luaL_checkudata(L, 1, "binarydata");
    luaL_argcheck(L, data != NULL, 1, "invalid user data");

    lua_pushinteger(L, (uintptr_t)data->code);
    return 1;
}


double real_stack[0x100];
int param_list[0x100];;

static int lcall(lua_State* L)
{
    BinaryData* data = (BinaryData*)luaL_checkudata(L, 1, "binarydata");
    luaL_argcheck(L, data != NULL, 1, "invalid user data");
    
    const char* param = data->info;

	char type;

	int input = 0, value = 0, param_count = 0;
	ZeroMemory(param_list, sizeof(param_list));
	uintptr_t addr = (uintptr_t)data->code;

	for (int i = 0; i < (int)strlen(param); i++)
	{
		type = param[i];
		if (param[i] == ')')
		{
			input = param_count * 4;

			for (int i = param_count; i > 0; i--)
			{
				int data = param_list[i];
				_asm push data
			}
			_asm call addr
 			_asm mov value, eax
			_asm add esp, input
			input = 0;
		}
		else if (param[i] == '(')
		{
			input = 1;
		}
		else if (type != '\0')
		{
			
			int retval = 0;
			switch (type)
			{
			case 'I':
			{
				if (input)
					retval = lua_tointeger(L, param_count + 2);
				else
					lua_pushinteger(L, value);
				break;
			}
			case 'R':
			{
				if (input)
				{

					real_stack[param_count] = lua_tonumber(L, param_count + 2);
					retval = (uint32_t)&real_stack[param_count];
				}
				else
					lua_pushnumber(L, *(double*)&value);
				break;
			}
			case 'S':
			{
				if (input)
					retval = (uint32_t)lua_tostring(L, param_count + 2);
				else
					lua_pushstring(L, (const char*)value);
				break;
			}

			case 'B':
			{
				if (input)
					retval = lua_toboolean(L, param_count + 2);
				else
					lua_pushboolean(L, value);
				break;
			}
			}
			if (input)
			{
				param_count++;
				param_list[param_count] = retval;

			}
			type = '\0';
		}
	}
	return 1;
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

    lua_pushcfunction(L, lcall);
    lua_setfield(L, -2, "c_call");

    return 1;
}