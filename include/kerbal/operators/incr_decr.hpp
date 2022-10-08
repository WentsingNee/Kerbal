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

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/cuda.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_copy_constructible.hpp>
#endif


namespace kerbal
{

	namespace operators
	{

		template <typename T>
		struct incrementable
		{
				KERBAL_CONSTEXPR14
				KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
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

		template <class T>
		struct decrementable
		{
				KERBAL_CONSTEXPR14
				KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
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
