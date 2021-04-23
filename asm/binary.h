#pragma once

#include <lua.hpp>

enum CALL_TYPE
{
    C_CALL,
    STD_CALL ,
    THIS_CALL,
    FAST_CALL,
};
struct BinaryData
{
    size_t size;
    void* code;
    char params[256];
    char name[256];
};

int register_binary_class(lua_State* L);
