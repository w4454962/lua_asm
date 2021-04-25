#pragma once

#include <lua.hpp>
#include <map>
#include <string>

enum class CALL_TYPE
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
    CALL_TYPE type;
    int ref_count;
    std::map<std::string, struct BinaryData*> ref_map;
};

int register_binary_class(lua_State* L);
