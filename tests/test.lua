package.path = package.path .. ';..\\tests\\?.lua;'

local asm = require 'asm'
print('111111')
local LoadLibraryA = asm.to_binary("mov eax, kernel32.LoadLibraryA\n jmp eax", 20, '(S)I', "LoadLibrary", "__stdcall")


local game = LoadLibraryA("D:\\war3\\game.dll")

print(game)

