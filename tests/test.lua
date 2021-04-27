package.path = package.path .. ';..\\..\\tests\\?.lua;'

require 'add_function'

--local asm = require 'asm'
print('111111')
--local LoadLibraryA = asm.to_binary("mov eax, kernel32.LoadLibraryA\n jmp eax", '(S)I', "LoadLibrary", "__stdcall")
--
--
--local game = LoadLibraryA("D:\\war3\\game.dll")
--
--print(game)

local ffi = require 'ffi'

print(ffi)

ffi.cdef [[
    int MessageBoxA(int, const char*, const char*, int);
]]

ffi.C.MessageBoxA(0, "aa", "bb", 0)