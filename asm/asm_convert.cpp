#include <Windows.h>
#include <memory>
#include <keystone\keystone.h>
#include "asm_convert.h"
#include "binary.h"

bool asm_sym_resolver(const char* symbol, uint64_t* value)
{
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


    
    BinaryData* data = (BinaryData*)lua_newuserdata(L, sizeof(BinaryData));
    ZeroMemory(data, sizeof(BinaryData));
    data->size = size;
    data->code = buffer;
    if (lua_isstring(L, 3))
    {
        size_t len = 0;
        const char* info = lua_tolstring(L, 3, &len);

        strncpy(data->info, info, len > 256 ? 256 : len);
    }

    luaL_getmetatable(L, "binarydata");

    lua_setmetatable(L, -2);
    // NOTE: free encode after usage to avoid leaking memory
    ks_free(encode);

    // close Keystone instance when done
    ks_close(ks);

    return 1;
}
