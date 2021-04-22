#pragma once

#include <lua.hpp>

struct BinaryData
{
    size_t size;
    void* code;
    char info[256];
};

int register_binary_class(lua_State* L);
