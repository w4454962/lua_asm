#pragma once
#include <inttypes.h>


uintptr_t c_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count);
uintptr_t std_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count);
uintptr_t this_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count);
uintptr_t fast_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count);

