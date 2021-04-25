
#include <boost/preprocessor/iteration/local.hpp>
#define BOOST_PP_LOCAL_MACRO(n) COMMON_LOOP(n)
#define BOOST_PP_LOCAL_LIMITS   COMMON_LOOP_LIMITS
#include BOOST_PP_LOCAL_ITERATE()
#undef  COMMON_LOOP
#undef  COMMON_LOOP_LIMITS