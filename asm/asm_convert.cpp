#include <Windows.h>
#include <memory>
#include <keystone\keystone.h>
#include "asm_convert.h"
#include "binary.h"
#include <regex>
#include <map>

BinaryData* g_current;

std::map<std::string, BinaryData*> symbol_map;

bool asm_sym_resolver(const char* symbol, uint64_t* value)
{
    std::string str = symbol;

    auto it = symbol_map.find(str);
    if (it != symbol_map.end())
    {
        auto* data = it->second;
        *value = (uint64_t)data->code;

        auto& map = g_current->ref_map;
        if (map.find(str) == map.end())
        {
            data->ref_count++;
            map[str] = data;
        }
       
        return true;
    }

    std::regex reg("(\\w+)\\.(\\w+)");
    auto words_begin = std::sregex_iterator(str.begin(), str.end(), reg);
    auto words_end = std::sregex_iterator();
    for (; words_begin != words_end; ++words_begin)
    {
        std::string module_name = words_begin->str(1);
        std::string proname = words_begin->str(2);
        HMODULE handle = LoadLibraryA(module_name.c_str());
        if (handle)
        {
            *value = (uint64_t)GetProcAddress(handle, proname.c_str());
            return true;
        }
    }

    return false;
}


int lua_error_print(lua_State* L, const char* err, ...)
{
    va_list ap;
    va_start(ap, err);
    lua_pushvfstring(L, err, ap);
    return lua_error(L);
}



int asm_to_binary(lua_State* L)
{
    if (!lua_isstring(L, 1) || !lua_isinteger(L, 2))
        return 0;


    size_t buffer_size = lua_tointeger(L, 2);
    
    void* buffer = VirtualAlloc(NULL, buffer_size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);


    BinaryData** ptr = (BinaryData**)lua_newuserdata(L, sizeof(BinaryData*));
    BinaryData* data = new BinaryData();
    *ptr = data;
    g_current = data;
    data->size = buffer_size;
    data->code = buffer;
    if (lua_isstring(L, 3))
    {
        size_t len = 0;
        const char* info = lua_tolstring(L, 3, &len);

        strncpy(data->params, info, len > 256 ? 256 : len);
    }

    if (lua_isstring(L, 4))
    {
        size_t len = 0;
        const char* info = lua_tolstring(L, 4, &len);

        strncpy(data->name, info, len > 256 ? 256 : len);

        symbol_map[data->name] = data;
    }

    ks_engine* ks;
    ks_err err;
    size_t count;
    size_t size;
    const char* code = lua_tolstring(L, 1, &size);

    unsigned char* encode;


    err = ks_open(KS_ARCH_X86, KS_MODE_32, &ks);
    if (err != KS_ERR_OK) {
        
        return lua_error_print(L, "failed on ks_open()");
    }
    ks_option(ks, KS_OPT_SYNTAX, KS_OPT_SYNTAX_NASM);
    ks_option(ks, KS_OPT_SYM_RESOLVER, (size_t)asm_sym_resolver);

    if (ks_asm(ks, code, (uint64_t)buffer, &encode, &size, &count) != KS_ERR_OK || size == 0) {
        return lua_error_print(L, "ERROR: ks_asm() failed & count = %d, error = %d\n",
            count, ks_errno(ks));
    }

    memcpy(buffer, encode, buffer_size < size ? buffer_size : size);


    data->code_size = size;
   
    luaL_getmetatable(L, "binarydata");

    lua_setmetatable(L, -2);
    // NOTE: free encode after usage to avoid leaking memory
    ks_free(encode);

    // close Keystone instance when done
    ks_close(ks);
    return 1;
}
