/**
 * @file       incr_decr.hpp
 * @brief      
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_INCR_DECR_HPP
#define KERBAL_OPERATORS_INCR_DECR_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL


#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_copy_constructible.hpp>
#endif


KERBAL_EXPORT_MODULE_DECLARE(kerbal.operators.incr_decr)


namespace kerbal
{

	namespace operators
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct incrementable
		{
				KERBAL_CONSTEXPR14
				friend
				T operator++(T & x, int)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
					KERBAL_CONDITIONAL_NOEXCEPT(
						kerbal::type_traits::try_test_is_nothrow_copy_constructible<T>::IS_TRUE::value &&
						noexcept(++x)
					)
#	endif
				{
					T tmp(x);
					++x;
					return tmp;
				}
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct decrementable
		{
				KERBAL_CONSTEXPR14
				friend
				T operator--(T & x, int)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
					KERBAL_CONDITIONAL_NOEXCEPT(
						kerbal::type_traits::try_test_is_nothrow_copy_constructible<T>::IS_TRUE::value &&
						noexcept(--x)
					)
#	endif
				{
					T tmp(x);
					--x;
					return tmp;
				}
		};

	} // namespace operators

} // namespace kerbal

#endif // KERBAL_OPERATORS_INCR_DECR_HPP
