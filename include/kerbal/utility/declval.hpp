/**
 * @file       declval.hpp
 * @brief
 * @date       2019-11-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_DECLVAL_HPP
#define KERBAL_UTILITY_DECLVAL_HPP

#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/add_rvalue_reference.hpp>
#else
#	include <kerbal/type_traits/add_lvalue_reference.hpp>
#endif


namespace kerbal
{

	namespace utility
	{

#	if __cplusplus >= 201103L

		template <typename T>
		typename kerbal::type_traits::add_rvalue_reference<T>::type
		declval() KERBAL_NOEXCEPT;

#	else

		template <typename T>
		typename kerbal::type_traits::add_lvalue_reference<T>::type
		declval() KERBAL_NOEXCEPT;

#	endif

		template <typename T>
		T *
		declthis() KERBAL_NOEXCEPT;

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_DECLVAL_HPP
