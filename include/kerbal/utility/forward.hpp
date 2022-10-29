/**
 * @file       forward.hpp
 * @brief
 * @date       2020-10-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_FORWARD_HPP
#define KERBAL_UTILITY_FORWARD_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/is_lvalue_reference.hpp>
#include <kerbal/type_traits/remove_reference.hpp>

#include <type_traits>


namespace kerbal
{

	namespace utility
	{

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp&& forward(typename kerbal::type_traits::remove_reference<Tp>::type & val) KERBAL_NOEXCEPT
		{
			return static_cast<Tp&&>(val);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp&& forward(typename kerbal::type_traits::remove_reference<Tp>::type && val) KERBAL_NOEXCEPT
		{
			static_assert(kerbal::type_traits::is_lvalue_reference<Tp>::value == 0,
						  "template argument substituting Tp is an lvalue reference type");
			return static_cast<Tp&&>(val);
		}

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_FORWARD_HPP
