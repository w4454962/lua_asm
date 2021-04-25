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

local cdecl_code_object = asm.to_binary(cdecl_code, 100, '(III)I', 'c_add')

function c_add(a, b, c)
    return cdecl_code_object:c_call(a, b, c)
end 

--std call 
local std_code = [[
    mov eax, [esp + 0x4] 
    mov edx, [esp + 0x8]
    mov ecx, [esp + 0xc]
    add eax, edx
    add eax, ecx
    ret  0xC
]]

local std_code = asm.to_binary(std_code, 100, '(III)I', 'std_add')

function std_add(a, b, c)
    return std_code:std_call(a, b, c)
end 

--this call 
local this_code = [[
    mov eax, [esp + 0x4] 
    mov edx, [esp + 0x8]
    add eax, edx
    add eax, ecx 
    ret 0x8
]]

local this_code_object = asm.to_binary(this_code, 100, '(III)I', 'this_add')

function this_add(a, b, c)
    return this_code_object:this_call(a, b, c)
end 


--fast call 
local fast_code = [[
    mov eax, [esp + 0x4] 
    add ecx, edx 
    add eax, ecx 
    ret 0x4
]]
local fast_code_object = asm.to_binary(fast_code, 100, '(III)I', 'fast_add')

function fast_add(a, b, c)
    return fast_code_object:fast_call(a, b, c)
end 




local all_add_code = [[
 

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


    ret 
]]

print('cdecl call', c_add(100, 200, 300))
print('std call', std_add(100, 200, 300))
print('this_call', this_add(100, 200, 300))
print('fast_call', fast_add(100, 200, 300))

local all_add = asm.to_binary(all_add_code, 100, '()I', 'aaa')
local str = string.format("%x  %x", all_add:c_call(),  0x300+0x200+0x100+0x1000+0x2000+0x10000+0x20000+0x100000+0x200000)
print(str)

