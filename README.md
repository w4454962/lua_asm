# lua_asm
在lua里用asmjit + asmtk 即时将文本编译成机器码 并执行的项目


项目只配置了 vs2019的Resele|Debug  x86|win32 编译配置


例子
```lua

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


```

输出内容

```
run asm         300
memory address  40304640
code    8b 44 24 04 8b 54 24 08 01 d0 eb 03 83 c0 01 c2 08 00

```

也可以看tests/test_ffi.lua里面 用ffi 的方式执行汇编机器码。


to_binary 返回的 对象跟可执行内存 被lua gc管理释放 当不存在任何引用时会被回收， 如果取内存地址做相关操作记得将对象保持引用 避免野指针崩溃 
