/**
 * @file       pow_mod_sa_n_sm.hpp
 * @brief
 * @date       2022-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_POW_MOD_SA_N_SM_HPP
#define KERBAL_SMATH_POW_MOD_SA_N_SM_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <kerbal/smath/multiply_mod_a_b_sm.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename ResultType, ResultType a, ResultType m, bool = (m == 0)>
			struct pow_mod_sa_n_sm_impl;

			template <typename ResultType, ResultType a, ResultType m>
			struct pow_mod_sa_n_sm_impl<ResultType, a, m, true> // m == 0
			{
				private:
					KERBAL_STATIC_ASSERT(m == 0, "static check failed");

				public:
					template <typename Unsigned>
					KERBAL_CONSTEXPR14
					static ResultType cacl(Unsigned n) KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "n must be unsigned");

						ResultType r = 1;
						ResultType base = a;
						while (true) {
							Unsigned half_n = n / 2;
							if (n % 2 == 1) {
								r *= base;
							}
							if (half_n == 0) {
								break;
							}
							base *= base;
							n = half_n;
						}
						return r;
					}
			};

			template <typename ResultType, ResultType a_, ResultType m>
			struct pow_mod_sa_n_sm_impl<ResultType, a_, m, false> // m != 0
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0, "static check failed");
					typedef kerbal::type_traits::integral_constant<ResultType, a_ % m> a;

				public:
					template <typename Unsigned>
					KERBAL_CONSTEXPR14
					static ResultType cacl(Unsigned n) KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "n must be unsigned");

						ResultType r = 1;
						ResultType base = a::value;
						while (true) {
							Unsigned half_n = n / 2;
							if (n % 2 == 1) {
								r = kerbal::smath::multiply_mod_a_b_sm<ResultType, m>::cacl(r, base);
							}
							if (half_n == 0) {
								break;
							}
							base = kerbal::smath::multiply_mod_a_b_sm<ResultType, m>::cacl(base, base);
							n = half_n;
						}
						return r;
					}
			};

		} // namespace detail

		/*
		 * a ** n % m
		 */
		template <typename ResultType, ResultType a, ResultType m>
		struct pow_mod_sa_n_sm : detail::pow_mod_sa_n_sm_impl<ResultType, a, m>
		{
		};

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_POW_MOD_SA_N_SM_HPP
