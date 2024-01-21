/**
 * @file       move.hpp
 * @brief      
 * @date       2019-06-02
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_MOVE_HPP
#define KERBAL_COMPATIBILITY_MOVE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


KERBAL_EXPORT_MODULE_DECLARE(kerbal.compatibility.move)


#if KERBAL_ENABLE_MODULES

import kerbal.type_traits.remove_reference;

#else

#include <kerbal/type_traits/remove_reference.hpp>

#endif


namespace kerbal
{

	namespace compatibility
	{

#	if __cplusplus < 201103L

		KERBAL_MODULE_EXPORT
		template <typename T>
		typename kerbal::type_traits::remove_reference<T>::type &
		to_xvalue(T & value)
		{
			return static_cast<typename kerbal::type_traits::remove_reference<T>::type &&>(value);
		}

#	else

		KERBAL_MODULE_EXPORT
		template <typename T>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::remove_reference<T>::type &&
		to_xvalue(T && value) KERBAL_NOEXCEPT
		{
			return static_cast<typename kerbal::type_traits::remove_reference<T>::type &>(value);
		}

#	endif


#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename T>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::remove_reference<T>::type &&
		move(T && value) KERBAL_NOEXCEPT
		{
			return static_cast<typename kerbal::type_traits::remove_reference<T>::type &&>(value);
		}

#	endif

	} // namespace compatibility

} // namespace kerbal

#endif // KERBAL_COMPATIBILITY_MOVE_HPP
