#pragma once
#include <inttypes.h>

#define intval sizeof uintptr_t


uintptr_t c_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size);
uintptr_t std_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size);
uintptr_t this_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size);
uintptr_t fast_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size);

