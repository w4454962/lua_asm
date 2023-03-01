package.cpath = package.cpath .. ';bin\\release\\?.dll'

package.path = package.path .. ';tests\\?.lua'



local asm = require 'asm'
local ffi = require 'ffi'



local ffi = require 'ffi'

ffi.cdef [[
    typedef int (__fastcall* TestFunc)(uint32_t ecx, uint32_t edx, uint32_t r1, uint32_t r2);
]]

local uintptr = ffi.new("uint32_t[1]")

local function ffi_newfunc(func_type, address)
    uintptr[0] = address

    return ffi.cast(func_type, uintptr)
end 

local fast_code = [[
    push ebp
    mov ebp, esp 
    push ebx 

    mov eax, ecx 
    add eax, edx 

    mov ebx, [ebp + 8]
    add eax, ebx 

    mov ebx, [ebp + 0xC]
    add eax, ebx 

    pop ebx 
    pop ebp
    ret 0x8
]]

local fast_call = asm.to_binary(fast_code, '(IIII)I', 'fast_add', '__fastcall')

local func_addr = fast_call:get_address()

--正确的值
print('default', 10+20+30+40)

--测试 正确的 汇编函数
print('custom test', fast_call(10, 20, 30, 40))

--用ffi 运行汇编函数
print('ffi', ffi_newfunc('TestFunc', func_addr)(10,20,30,40))


local test_code = ([[
    mov eax, 0x%x
    
    push 40
    push 30
    mov edx, 20
    mov ecx, 10
    call eax 

    ret
]]):format(func_addr)


local test_code_func = asm.to_binary(test_code, '()I', '', '__fastcall')

local test_addr = test_code_func:get_address()

print('test 1', ffi_newfunc('int(*)()', test_addr)())

print('test 2', test_code_func() )

------------------------------------------------------------------------------------------

--ffi make fastcall 

local ffi_fast_call_func = ffi.cast('TestFunc', function (ecx, edx, r1, r2)
    local ret = ecx + edx + r1 + r2 
    print('ffi run add', ret)
    return ret
end)

print('ffi fastcall', ffi_fast_call_func(10,20,30,40))


local ffi_func_addr = tonumber(ffi_fast_call_func)

local ffi_test_code = ([[
    mov eax, 0x%x
    
    push 40
    push 30
    mov edx, 20
    mov ecx, 10
    call eax 

    ret
]]):format(ffi_func_addr)


local ffi_test_code_func = asm.to_binary(ffi_test_code, '()I', '', '__fastcall')

local ffi_test_addr = ffi_test_code_func:get_address()

------------------ 在这个步骤开始会崩溃 -------------------------------
print('crash start')

print('ffi test 1', ffi_newfunc('int(*)()', ffi_test_addr)())

print('ffi test 2', ffi_test_code_func() )



print('finish')

