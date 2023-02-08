#include <Windows.h>
#include <memory>
#include <asmjit/x86.h>
#include <asmtk/asmtk.h>
#include "asm_convert.h"
#include "binary.h"
#include <regex>
#include <map>

using namespace asmjit;
using namespace asmtk;

BinaryData* g_current;

std::map<std::string, BinaryData*> symbol_map;

static Error ASMJIT_CDECL unknownSymbolHandler(AsmParser* parser, Operand* dst, const char* symbol, size_t size) {
    void* data = parser->unknownSymbolHandlerData();
    //printf("SymbolHandler called on symbol '%.*s' (data %p)\n", int(size), symbol, data);

    std::string str = std::string(symbol, size);

    auto it = symbol_map.find(str);
    if (it != symbol_map.end())
    {
        auto* data = it->second;
        *dst = imm((uintptr_t)data->code);

        auto& map = g_current->ref_map;
        if (map.find(str) == map.end())
        {
            data->ref_count++;
            map[str] = data;
        }
        return kErrorOk;
    }

    std::regex reg("(\\w+)\\.(\\w+)");
    auto words_begin = std::sregex_iterator(str.begin(), str.end(), reg);
    auto words_end = std::sregex_iterator();
    for (; words_begin != words_end; ++words_begin)
    {
        std::string module_name = words_begin->str(1);
        std::string proname = words_begin->str(2);
        HMODULE handle = GetModuleHandleA(module_name.c_str());
        if (!handle) handle = LoadLibraryA(module_name.c_str());
        if (handle)
        {
            *dst = imm(GetProcAddress(handle, proname.c_str()));
            return kErrorOk;
        }
    }
    return kErrorOk;
}

int lua_error_print(lua_State* L, const char* err, ...)
{
    va_list ap;
    va_start(ap, err);
    lua_pushvfstring(L, err, ap);
    return lua_error(L);
}


#ifdef _WIN32
Environment env(Arch::kX86);

#elif _WIN64
Environment env(Arch::kX64);

#endif // _WIN32


int asm_to_binary(lua_State* L)
{
    if (!lua_isstring(L, 1))
        return 0;


    BinaryData* data = new BinaryData();
  
    g_current = data;

    if (lua_isstring(L, 2))
    {
        size_t len = 0;
        const char* info = lua_tolstring(L, 2, &len);

        strncpy(data->params, info, len > 256 ? 256 : len);
    }

    if (lua_isstring(L, 3))
    {
        size_t len = 0;
        const char* info = lua_tolstring(L, 3, &len);

        strncpy(data->name, info, len > 256 ? 256 : len);

        symbol_map[data->name] = data;
    }
    if (lua_isstring(L, 4))
    {
        const char* calltype = lua_tostring(L, 4);

        data->type = CALL_TYPE::C_CALL;
        if (strcmp(calltype, "__stdcall") == 0)
            data->type = CALL_TYPE::STD_CALL;

        else if (strcmp(calltype, "__thiscall") == 0)
            data->type = CALL_TYPE::THIS_CALL;

        else if (strcmp(calltype, "__fastcall") == 0)
            data->type = CALL_TYPE::FAST_CALL;
        else if (strcmp(calltype, "__cdeclcall") == 0)
            data->type = CALL_TYPE::C_CALL;
    }

    size_t text_size;
    const char* text = lua_tolstring(L, 1, &text_size);


    CodeHolder code;

    auto err = code.init(env, 0);
    if (err != kErrorOk) {
        printf("%s\n", DebugUtils::errorAsString(err));
        return false;
    }

    
    x86::Assembler assembler(&code);

    AsmParser parser(&assembler);

    parser.setUnknownSymbolHandler(unknownSymbolHandler);

    err = parser.parse(text, text_size);
    if (err != kErrorOk) {
        printf("%s\n%s\n", text, DebugUtils::errorAsString(err));
        return false;
    }

    // Check for unresolved relocations
    if (code._relocations.size()) {
        printf("unresolved relocation\n");
        return false;
    }

    void* buffer = VirtualAlloc(NULL, code.codeSize(), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    data->code = buffer;
    data->size = code.codeSize();

    code.relocateToBase((uint64_t)buffer);
 
    code.copyFlattenedData(buffer, code.codeSize());


    BinaryData** ptr = (BinaryData**)lua_newuserdata(L, sizeof(BinaryData*));
    *ptr = data;
   
    luaL_getmetatable(L, "binarydata");

    lua_setmetatable(L, -2);

    return 1;
}
