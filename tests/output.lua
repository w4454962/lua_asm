
local asm = require 'asm'

--std call 
local std_code = [[
    mov eax, [esp + 0x4] 
    mov edx, [esp + 0x8]
    add eax, edx
    
    jmp pos   //支持重定位 以及跳转
    
    add eax, 1 
pos:  
    ret  0x8
]]

local std_add = asm.to_binary(std_code, '(II)I', 'std_code_name', '__stdcall')

print('run asm ', std_add(100, 200))

print('memory address', std_add:get_address())

local code = std_add:get_code()

local s = {}
for i = 1, #code do 
    local byte = code:sub(i, i):byte()
    s[#s + 1] = string.format("%02x ", byte)
end 
print('code', table.concat(s))
