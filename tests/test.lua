
local asm = require 'asm'


local code = [[
    mov eax, [esp + 4] 
    mov ebx, [esp + 8]
    add eax, ebx
    ret 
]]
local add_code = asm.to_binary(code, 100, '(II)I')


local function add(a, b)
    return add_code:c_call(a, b)
end 


print(add(5, 6))

print(add(1, 3))