#include "fpcall2.h"
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/iteration/local.hpp>


#define intval sizeof uintptr_t


#define MAX_COUNT 30

#define BOOST_PP_LOCAL_MACRO(n)     uintptr_t(__cdecl *c_callfunc ##n)(BOOST_PP_ENUM_BINARY_PARAMS(n, uintptr_t BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT)); 
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()


#define BOOST_PP_LOCAL_MACRO(n)     uintptr_t(__stdcall *std_callfunc ##n)(BOOST_PP_ENUM_BINARY_PARAMS(n, uintptr_t BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT)); 
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()

#define BOOST_PP_LOCAL_MACRO(n)     uintptr_t(__fastcall *fast_callfunc ##n)(BOOST_PP_ENUM_BINARY_PARAMS(n, uintptr_t BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT)); 
#define BOOST_PP_LOCAL_LIMITS (2, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()


#define BOOST_PP_LOCAL_MACRO(n)     uintptr_t(__thiscall *this_callfunc ##n)(BOOST_PP_ENUM_BINARY_PARAMS(n, uintptr_t BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT)); 
#define BOOST_PP_LOCAL_LIMITS (2, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()


uintptr_t c_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval = 0;

	switch (param_list_size / intval)
	{
#define BOOST_PP_LOCAL_MACRO(n)     case n: c_callfunc##n = decltype(c_callfunc##n)(func_address); retval = c_callfunc##n(BOOST_PP_ENUM_BINARY_PARAMS(n, param_list[,] BOOST_PP_INTERCEPT)); break;
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()
	default:
		break;
	}
	return retval;
}

uintptr_t std_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval = 0;

	switch (param_list_size / intval)
	{
#define BOOST_PP_LOCAL_MACRO(n)     case n: std_callfunc##n = decltype(std_callfunc##n)(func_address); retval = std_callfunc##n(BOOST_PP_ENUM_BINARY_PARAMS(n, param_list[,] BOOST_PP_INTERCEPT)); break;
#define BOOST_PP_LOCAL_LIMITS (0, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()
	default:
		break;
	}
	return retval;
}

uintptr_t fast_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval = 0;

	switch (param_list_size / intval)
	{
#define BOOST_PP_LOCAL_MACRO(n)     case n: fast_callfunc##n = decltype(fast_callfunc##n)(func_address); retval = fast_callfunc##n(BOOST_PP_ENUM_BINARY_PARAMS(n, param_list[,] BOOST_PP_INTERCEPT)); break;
#define BOOST_PP_LOCAL_LIMITS (2, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()
	default:
		break;
	}
	return retval;
}


uintptr_t this_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval = 0;

	switch (param_list_size / intval)
	{
#define BOOST_PP_LOCAL_MACRO(n)     case n: this_callfunc##n = decltype(this_callfunc##n)(func_address); retval = this_callfunc##n(BOOST_PP_ENUM_BINARY_PARAMS(n, param_list[,] BOOST_PP_INTERCEPT)); break;
#define BOOST_PP_LOCAL_LIMITS (2, MAX_COUNT)
#include BOOST_PP_LOCAL_ITERATE()
	default:
		break;
	}
	return retval;
}


/*
uintptr_t c_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval = 0;

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


uintptr_t std_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval;

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

uintptr_t this_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval;
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


uintptr_t fast_call(uintptr_t func_address, const uintptr_t* param_list, size_t param_list_size)
{
	uintptr_t retval;
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