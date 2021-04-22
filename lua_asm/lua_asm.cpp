// lua_asm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <lua.hpp>

#pragma comment(lib, "luacore.lib")


int main(int argc, char** argv)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    for (int i = 1; i < argc; i++)
    {
        if (luaL_dofile(L, argv[i]) != LUA_OK)
        {
            printf("lua error %s\n", lua_tostring(L, -1));
        }
    }

    

    return 0;
}
