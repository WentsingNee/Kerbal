/**
 * @file       namespace_std_scope.hpp
 * @brief
 * @date       2020-11-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_NAMESPACE_STD_SCOPE_HPP
#define KERBAL_COMPATIBILITY_NAMESPACE_STD_SCOPE_HPP

#include <kerbal/config/cxx_stdlib.hpp>


#if KERBAL_CXX_STDLIB == KERBAL_CXX_STDLIB_LIBCXX

#	define KERBAL_NAMESPACE_STD_BEGIN    _LIBCPP_BEGIN_NAMESPACE_STD
#	define KERBAL_NAMESPACE_STD_END      _LIBCPP_END_NAMESPACE_STD

#else

#	define KERBAL_NAMESPACE_STD_BEGIN    namespace std {
#	define KERBAL_NAMESPACE_STD_END      }

#endif


#endif // KERBAL_COMPATIBILITY_NAMESPACE_STD_SCOPE_HPP
