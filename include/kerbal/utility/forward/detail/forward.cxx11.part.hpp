/**
 * @file       forward.cxx11.part.hpp
 * @brief
 * @date       2020-10-19
 * @author     Peter
 * @remark     move from kerbal/utility/forward.hpp, 2023-08-25
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_FORWARD_DETAIL_FORWARD_CXX11_PART_HPP
#define KERBAL_UTILITY_FORWARD_DETAIL_FORWARD_CXX11_PART_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif


#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL


#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/is_lvalue_reference.hpp>
#include <kerbal/type_traits/remove_reference.hpp>


KERBAL_START_MODULE
KERBAL_EXPORT_MODULE(kerbal.utility.forward)


#if KERBAL_ENABLE_MODULES_kerbal_utility_forward

// import kerbal.type_traits;

#else


#endif



namespace kerbal
{

	namespace utility
	{

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp&& forward(typename kerbal::type_traits::remove_reference<Tp>::type & val) KERBAL_NOEXCEPT
		{
			return static_cast<Tp&&>(val);
		}

		KERBAL_MODULE_EXPORT
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

#endif // KERBAL_UTILITY_FORWARD_DETAIL_FORWARD_CXX11_PART_HPP
