/**
 * @file       sigma_pow_mod_sa_n_sm.hpp
 * @brief
 * @date       2022-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_SIGMA_POW_MOD_SA_N_SM_HPP
#define KERBAL_SMATH_SIGMA_POW_MOD_SA_N_SM_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <kerbal/smath/add_mod_sm.hpp>
#include <kerbal/smath/multiply_mod_a_b_sm.hpp>
#include <kerbal/smath/multiply_mod_sa_b_sm.hpp>


namespace kerbal
{

	namespace smath
	{

		// a ** (n - 1) + ... + a ** 3 + a ** 2 + a ** 1 + 1
		template <typename ResultType, ResultType a, ResultType m>
		struct sigma_pow_mod_sa_n_sm
		{

				template <typename Unsigned>
				KERBAL_CONSTEXPR14
				static ResultType cacl(Unsigned n) KERBAL_NOEXCEPT
				{
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "n must be unsigned");

					/*
					 *   e.g. for n = 21
					 *
					 *   16  8  4  2  1
					 *    1  0  1  0  1  r = r * a + 1
					 *       1  0  1  0  r = r * (a ** 10 + 1)
					 *          1  0  1  r = r * (a ** 5 + 1)
					 *          1  0  0  r = r * a + 1
					 *             1  0  r = r * (a ** 2 + 1)
					 *                1  r = r * a + 1
					 */

					// pre: n != 0
					int lead = CHAR_BIT * sizeof(n) - 1;
					{
						// to opt: lead = CHAR_BIT * sizeof(n) - 1 - __builtin_clzll(n);
						while (((n >> lead) & 1) == 0) {
							lead--;
						}
					}
					ResultType r = 1;
					bool b = true;
					ResultType poa = 1;
					while (lead > 0) {
						--lead;
						poa = multiply_mod_a_b_sm<ResultType, m>::cacl(poa, poa);
						if (b) {
							poa = multiply_mod_a_b_sm<ResultType, m>::cacl(a, poa);
						}
						r = multiply_mod_a_b_sm<ResultType, m>::cacl(
							r,
							add_mod_sm<ResultType, m>::cacl(poa, 1)
						);
						b = (n >> lead) & 1;
						if (b) {
							// r = r * a + 1
							r = multiply_mod_sa_b_sm<ResultType, a, m>::cacl(r);
							r = add_mod_sm<ResultType, m>::cacl(r, 1);
						}
					}
					return r;
				}
		};

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_SIGMA_POW_MOD_SA_N_SM_HPP
