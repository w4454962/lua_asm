# lua_asm
在lua里用keystnoe 即时将文本编译成机器码 并执行的项目


项目只配置了 vs2019的Resele|Debug  x86|win32 编译配置

如果需要其他版本 可以 https://github.com/keystone-engine/keystone 从该项目里重新编译keystone.lib


例子
```lua
local asm = requore 'asm'

--std call 
local std_code = [[
    mov eax, [esp + 0x4] 
    mov edx, [esp + 0x8]
    add eax, edx
    ret  0x8
]]

local std_add = asm.to_binary(std_code, '(II)I', 'std_code_name', '__stdcall')

print('memory address', std_add:get_address())

print('run asm ', std_add(100, 200))

```

也可以看tests/test_ffi.lua里面 用ffi 的方式执行汇编机器码。
