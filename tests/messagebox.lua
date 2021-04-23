
local asm = require 'asm'


local code = [[
    mov eax, user32.MessageBoxA
    jmp eax
]]

local object = asm.to_binary(code, 100, '(ISSI)V', 'xxx')

function MessageBoxA(hwnd, text, title, flag)
    object:std_call(hwnd, text, title, flag)
end 

MessageBoxA(0, "hello worlds!", "title", 0)
