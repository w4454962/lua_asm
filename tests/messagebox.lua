
local asm = require 'asm'


local code = [[
    push ebp
    mov ebp, esp
    mov eax, [ebp + 0x14] 
    push eax 
    mov eax, [ebp + 0x10] 
    push eax 
    mov eax, [ebp + 0xC] 
    push eax 
    mov eax, [ebp + 0x8] 
    push eax 
    mov eax, user32.MessageBoxA
    call eax 
    mov esp, ebp
    pop ebp
    ret 
]]

local object = asm.to_binary(code, 100, '(ISSI)V')

function MessageBoxA(hwnd, text, title, flag)
    object:c_call(hwnd, text, title, flag)
end 

MessageBoxA(0, "hello worlds!", "title", 0)
