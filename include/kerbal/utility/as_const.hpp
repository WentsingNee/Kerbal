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

#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL


#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


KERBAL_EXPORT_MODULE_DECLARE(kerbal.utility.as_const)


#if KERBAL_ENABLE_MODULES

import kerbal.type_traits.add_const;

#else

#include <kerbal/type_traits/add_const.hpp>

#endif


namespace kerbal
{

	namespace utility
	{

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::add_const<Tp>::type &
		as_const(Tp& ref) KERBAL_NOEXCEPT
		{
			return ref;
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		void as_const(const Tp&&) = delete;

#	endif

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_AS_CONST_HPP
