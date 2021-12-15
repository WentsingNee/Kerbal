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

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace operators
	{

		template <typename Tp>
		struct incrementable
		{
				KERBAL_CONSTEXPR14
				friend Tp operator++(Tp& x, int)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_copy_constructible<Tp>::value &&
								noexcept(++x)
						)
#	endif
				{
					Tp tmp(x);
					++x;
					return tmp;
				}
		};

		template <class Tp>
		struct decrementable
		{
				KERBAL_CONSTEXPR14
				friend Tp operator--(Tp& x, int)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_copy_constructible<Tp>::value &&
								noexcept(--x)
						)
#	endif
				{
					Tp tmp(x);
					--x;
					return tmp;
				}
		};

	} // namespace operators

} // namespace kerbal

#endif // KERBAL_OPERATORS_INCR_DECR_HPP
