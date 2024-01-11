/**
 * @file       two_pow_n_minus_one.hpp
 * @brief
 * @date       2024-01-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_TWO_POW_N_MINUS_ONE_HPP
#define KERBAL_SMATH_TWO_POW_N_MINUS_ONE_HPP

#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename UIntType, std::size_t N, bool /* N == digits(UIntType) */>
			struct two_pow_n_minus_one_helper;

			template <typename UIntType, std::size_t N>
			struct two_pow_n_minus_one_helper<UIntType, N, true>
			{
					typedef kerbal::type_traits::integral_constant<
							UIntType,
							~static_cast<UIntType>(0u)
					> type;
			};

			template <typename UIntType, std::size_t N>
			struct two_pow_n_minus_one_helper<UIntType, N, false>
			{
					typedef kerbal::type_traits::integral_constant<
							UIntType,
							(static_cast<UIntType>(1u) << N) - 1u
					> type;
			};

		} // namespace detail


		template <typename UIntType, std::size_t N>
		struct two_pow_n_minus_one :
				public kerbal::smath::detail::two_pow_n_minus_one_helper<
					UIntType, N,
					N == kerbal::numeric::numeric_limits<UIntType>::DIGITS::value
				>::type
		{
		};

	} // namespace smath

} // namespace kerbal

#endif // KERBAL_SMATH_TWO_POW_N_MINUS_ONE_HPP
