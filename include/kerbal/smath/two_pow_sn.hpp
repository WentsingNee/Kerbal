/**
 * @file       two_pow_sn.hpp
 * @brief
 * @date       2024-03-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_TWO_POW_SN_HPP
#define KERBAL_SMATH_TWO_POW_SN_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <cstddef>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename ResultType, std::size_t N, bool /* N == digits(ResultType) */>
			struct two_pow_sn_helper;

			template <typename ResultType, std::size_t N>
			struct two_pow_sn_helper<ResultType, N, true>
			{
					typedef kerbal::type_traits::integral_constant<
						ResultType,
						0
					> type;
			};

			template <typename ResultType, std::size_t N>
			struct two_pow_sn_helper<ResultType, N, false>
			{
					typedef kerbal::type_traits::integral_constant<
						ResultType,
						static_cast<ResultType>(1u) << N
					> type;
			};

		} // namespace detail


		/**
		 * 0 if n == digits of ResultType else is 2 ** n
		 */
		template <typename ResultType, std::size_t N>
		struct two_pow_sn :
			kerbal::smath::detail::two_pow_sn_helper<
				ResultType, N,
				N == kerbal::numeric::numeric_limits<ResultType>::DIGITS::value
			>::type
		{
			private:
				KERBAL_STATIC_ASSERT(
					kerbal::type_traits::is_unsigned<ResultType>::value,
					"ResultType should be unsigned"
				);
		};

	} // namespace smath

} // namespace kerbal

#endif // KERBAL_SMATH_TWO_POW_SN_HPP
