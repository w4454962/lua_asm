﻿// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <windows.h>


#include <lua.hpp>
#include "asm_convert.h"
#include "binary.h"

# define EXPORT __declspec(dllexport)

extern "C" void init_lua_module();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

int ltest(lua_State* L)
{
    printf("test\n");

    return 0;
}

static int lua_tindex(lua_State* L)
{
    return 0;
}

static int lua_tnewindex(lua_State* L)
{
    return 0;
}

static int lua_tpairs(lua_State* L)
{
    return 0;
}

static int lua_tcall(lua_State* L)
{

    return 0;
}


EXTERN_C EXPORT int luaopen_asm(lua_State * L)
{
    init_lua_module();


    luaL_checkversion(L);

    register_binary_class(L);

    luaL_Reg regfunc[] = {
         { "to_binary", asm_to_binary},
         { NULL, NULL },
    };

    luaL_Reg metamethod[] = {
        {"__index", lua_tindex},
        {"__newindex", lua_tnewindex},
        {"__pairs", lua_tpairs},
        {"__call", lua_tcall},
    };

    luaL_newlib(L, regfunc);
    lua_newtable(L);
    for (int i = 0; i < sizeof(metamethod) / sizeof(luaL_Reg); i++)
    {
        luaL_Reg& reg = metamethod[i];
        if (reg.name && reg.func)
        {
            lua_pushstring(L, reg.name);
            lua_pushcclosure(L, reg.func, 0);
            lua_rawset(L, -3);
        }
    }

    lua_setmetatable(L, -2);

   

    return 1;
}