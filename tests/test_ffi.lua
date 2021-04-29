
local asm = require 'asm'

local ffi = require 'ffi'


function addr2func(address, cdef)
    local ptr = ffi.new('int[1]', address)
    return ffi.cast(cdef, ptr)
end 

--cdecl call 
local cdecl_code = [[
    mov eax, [esp + 0x4] 
    mov edx, [esp + 0x8]
    add eax, edx
    ret  
]]

local test_add = asm.to_binary(cdecl_code)

local func = addr2func(test_add:get_address(), "int(*test_add)(int, int)")

print('test_ffi', func(10, 20))

