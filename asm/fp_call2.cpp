
#include "fp_call2.h"
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#define intval sizeof uintptr_t


#define MAX_COUNT 16

#define BOOST_PP_LOCAL_MACRO(n)     typedef uintptr_t(__cdecl *c_callfunc##n)(BOOST_PP_ENUM_BINARY_PARAMS(n, uintptr_t BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT)); 
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()


#define BOOST_PP_LOCAL_MACRO(n)     typedef uintptr_t(__stdcall *std_callfunc##n)(BOOST_PP_ENUM_BINARY_PARAMS(n, uintptr_t BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT)); 
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()

#define BOOST_PP_LOCAL_MACRO(n)     typedef uintptr_t(__fastcall *fast_callfunc##n)(BOOST_PP_ENUM_BINARY_PARAMS(n, uintptr_t BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT)); 
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()


#define BOOST_PP_LOCAL_MACRO(n)     typedef uintptr_t(__thiscall *this_callfunc##n)(BOOST_PP_ENUM_BINARY_PARAMS(n, uintptr_t BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT)); 
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()


uintptr_t c_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count)
{
	switch (param_count)
	{
#define BOOST_PP_LOCAL_MACRO(n)     case n: return ((c_callfunc##n)(func_address))(BOOST_PP_ENUM_BINARY_PARAMS(n, param_list[,] BOOST_PP_INTERCEPT));
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()
	default:
		break;
	}
	return 0;
}

uintptr_t std_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count)
{
	switch (param_count)
	{
#define BOOST_PP_LOCAL_MACRO(n)     case n: return ((std_callfunc##n)(func_address))(BOOST_PP_ENUM_BINARY_PARAMS(n, param_list[,] BOOST_PP_INTERCEPT));
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()
	default:
		break;
	}
	return 0;
}

uintptr_t fast_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count)
{
	switch (param_count)
	{
#define BOOST_PP_LOCAL_MACRO(n)     case n: return ((fast_callfunc##n)(func_address))(BOOST_PP_ENUM_BINARY_PARAMS(n, param_list[,] BOOST_PP_INTERCEPT));
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()
	default:
		break;
	}
	return 0;
}


uintptr_t this_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count)
{
	switch (param_count)
	{
#define BOOST_PP_LOCAL_MACRO(n)     case n: return ((this_callfunc##n)(func_address))(BOOST_PP_ENUM_BINARY_PARAMS(n, param_list[,] BOOST_PP_INTERCEPT));
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()
	default:
		break;
	}
	return 0;
}


/*
uintptr_t c_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count)
{
	uintptr_t retval = 0;
	size_t param_list_size = param_count * sizeof(uintptr_t);
	for (size_t i = param_list_size; i > 0; i -= intval)
	{
		uintptr_t data = *(uintptr_t*)((uintptr_t)param_list + i - intval);
		_asm push data
	}
	_asm
	{
		call func_address
		add esp, param_list_size
		mov retval, eax
	}
	return retval;
}


uintptr_t std_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count)
{
	uintptr_t retval;
	size_t param_list_size = param_count * sizeof(uintptr_t);
	for (size_t i = param_list_size; i > 0; i -= intval)
	{
		uintptr_t data = *(uintptr_t*)((uintptr_t)param_list + i - intval);
		_asm push data
	}
	_asm
	{
		call func_address
		mov retval, eax
	}
	return retval;
}

uintptr_t this_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count)
{
	uintptr_t retval;
	size_t param_list_size = param_count * sizeof(uintptr_t);
	uintptr_t first = param_list[0];
	for (size_t i = param_list_size; i > intval; i -= intval)
	{
		uintptr_t data = *(uintptr_t*)((uintptr_t)param_list + i - intval);
		_asm push data
	}
	param_list_size -= intval;
	_asm
	{
		mov ecx, first
		call func_address
		mov retval, eax
	}
	return retval;
}


uintptr_t fast_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_count)
{
	uintptr_t retval;
	size_t param_list_size = param_count * sizeof(uintptr_t);
	uintptr_t first = param_list[0];
	uintptr_t second = param_list[1];
	for (size_t i = param_list_size; i > intval * 2; i -= intval)
	{
		uintptr_t data = *(uintptr_t*)((uintptr_t)param_list + i - intval);
		_asm push data
	}
	param_list_size -= intval * 2;
	_asm
	{
		mov ecx, first
		mov edx, second
		call func_address
		mov retval, eax
	}
	return retval;
}


*/