local asm = require 'asm'

--cdecl call 
local cdecl_code = [[
    mov eax, [esp + 0x4] 
    mov ebx, [esp + 0x8]
    mov ecx, [esp + 0xc]
    add eax, ebx
    add eax, ecx
    ret  
]]

local cdecl_code_object = asm.to_binary(cdecl_code, 100, '(III)I')

function c_add(a, b, c)
    return cdecl_code_object:c_call(a, b, c)
end 

--std call 
local std_code = [[
    mov eax, [esp + 0x4] 
    mov ebx, [esp + 0x8]
    mov ecx, [esp + 0xc]
    add eax, ebx
    add eax, ecx
    ret  0xC
]]

local std_code = asm.to_binary(cdecl_code, 100, '(III)I')

function std_add(a, b, c)
    return std_code:c_call(a, b, c)
end 



--this call 
local this_code = [[
    mov eax, [esp + 0x4] 
    mov ebx, [esp + 0x8]
    add eax, ebx
    add eax, ecx 
    ret 
]]

local this_code_object = asm.to_binary(this_code, 100, '(III)I')

function this_add(a, b, c)
    return this_code_object:this_call(a, b, c)
end 


--fast call 
local fast_code = [[
    mov eax, [esp + 0x4] 
    add ecx, edx 
    add eax, ecx 
    ret
]]
local fast_code_object = asm.to_binary(fast_code, 100, '(III)I')

function fast_add(a, b, c)
    return fast_code_object:fast_call(a, b, c)
end 

print('cdecl call', c_add(100, 200, 300))
print('std call', std_add(100, 200, 300))
print('this_call', this_add(100, 200, 300))
print('fast_call', fast_add(100, 200, 300))