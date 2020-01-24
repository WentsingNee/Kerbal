/**
 * @file       as_const.hpp
 * @brief
 * @date       2020-01-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_AS_CONST_HPP
#define KERBAL_UTILITY_AS_CONST_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/type_traits_details/const_deduction.hpp>

namespace kerbal
{

	namespace utility
	{

		template <typename Tp>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::add_const<Tp>&
		as_const(Tp& ref) KERBAL_NOEXCEPT
		{
			return ref;
		}

#	if __cplusplus >= 201103L

		template <typename Tp>
		void as_const(const Tp&&) = delete;

#	endif

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_AS_CONST_HPP
