/**
 * @file       addable.hpp
 * @brief
 * @date       2019-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_ADDABLE_HPP
#define KERBAL_OPERATORS_ADDABLE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/cuda.hpp>


namespace kerbal
{

	namespace operators
	{

		template <typename T, typename U = T>
		struct addable
		{
				KERBAL_CONSTEXPR14
				KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
				friend
				T operator+(T lhs, const U & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs += rhs))
#	endif
				{
					lhs += rhs;
					return lhs;
				}
		};

		template <typename T, typename U>
		struct addable_left
		{
				KERBAL_CONSTEXPR14
				KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
				friend
				T operator+(const U & lhs, const T & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(rhs + lhs))
#	endif
				{
					return rhs + lhs;
				}
		};

	} // namespace operators

} // namespace kerbal

#endif // KERBAL_OPERATORS_ADDABLE_HPP
