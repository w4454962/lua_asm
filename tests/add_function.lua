local asm = require 'asm'

--cdecl call 
local cdecl_code = [[
    mov eax, [esp + 0x4] 
    mov edx, [esp + 0x8]
    mov ecx, [esp + 0xc]
    add eax, edx
    add eax, ecx
    ret  
]]

local c_add = asm.to_binary(cdecl_code, '(III)I', 'c_add', '__cdeclcall')


--std call 
local std_code = [[
    mov eax, [esp + 0x4] 
    mov edx, [esp + 0x8]
    mov ecx, [esp + 0xc]
    add eax, edx
    add eax, ecx
    ret  0xC
]]

local std_add = asm.to_binary(std_code, '(III)I', 'std_add', '__stdcall')


--this call 
local this_code = [[
    mov eax, [esp + 0x4] 
    mov edx, [esp + 0x8]
    add eax, edx
    add eax, ecx 
    ret 0x8
]]

local this_add = asm.to_binary(this_code, '(III)I', 'this_add', '__thiscall')


--fast call 
local fast_code = [[
    mov eax, [esp + 0x4] 
    add ecx, edx 
    add eax, ecx 
    ret 0x4
]]
local fast_add = asm.to_binary(fast_code, '(III)I', 'fast_add', '__fastcall')



local all_add_code = [[

    push ebp
    mov ebp, esp 
    push eax 

    pushad
    pushfd

    push 0x300
    push 0x200
    push 0x100
    mov esi, c_add
    call esi
    add esp, 0xc

    push eax
    push 0x1000
    push 0x2000
    mov esi, std_add
    call esi

    mov ecx, eax
    push 0x10000
    push 0x20000
    mov esi, this_add
    call esi

    mov ecx, eax 
    mov edx, 0x100000
    push 0x200000
    mov esi, fast_add
    call esi
    mov [ebp - 4], eax 

    popfd
    popad
    
    pop eax 
    pop ebp

    ret 
]]

print('cdecl call', c_add(100, 200, 300))
print('std call', std_add(100, 200, 300))
print('this_call', this_add(100, 200, 300))
print('fast_call', fast_add(100, 200, 300))

local all_add = asm.to_binary(all_add_code, '()I', 'aaa', '__cdeclcall')

local str = string.format("%x  %x", all_add(),  0x300+0x200+0x100+0x1000+0x2000+0x10000+0x20000+0x100000+0x200000)
print(str)

