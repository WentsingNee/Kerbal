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

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <kerbal/smath/add_mod_sm.hpp>
#include <kerbal/smath/multiply_mod_a_b_sm.hpp>
#include <kerbal/smath/multiply_mod_sa_b_sm.hpp>
#include <kerbal/smath/xmod.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <
				typename ResultType, ResultType Base, ResultType Mod,
				int case_ = (Base == 1 ? 0 : 1)
			>
			struct sigma_pow_mod_sa_n_sm_impl;


			template <typename ResultType, ResultType Base, ResultType Mod>
			struct sigma_pow_mod_sa_n_sm_impl<ResultType, Base, Mod, 0> // Base == 1
			{
					/**
					 * @precondition n != 0
					 */
					template <typename Unsigned>
					KERBAL_CONSTEXPR14
					static
					ResultType f(Unsigned n) KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(
							kerbal::type_traits::is_unsigned<Unsigned>::value,
							"n must be unsigned"
						);
						return kerbal::smath::xmod<ResultType, Mod>::f(n);
					}
			};

			template <typename ResultType, ResultType Base, ResultType Mod>
			struct sigma_pow_mod_sa_n_sm_impl<ResultType, Base, Mod, 1>
			{

					/**
					 * @precondition n != 0
					 */
					template <typename Unsigned>
					KERBAL_CONSTEXPR14
					static
					ResultType f(Unsigned n) KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(
							kerbal::type_traits::is_unsigned<Unsigned>::value,
							"n must be unsigned"
						);

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
							poa = multiply_mod_a_b_sm<ResultType, Mod>::f(poa, poa);
							if (b) {
								poa = multiply_mod_sa_b_sm<ResultType, Base, Mod>::f(poa);
							}
							r = multiply_mod_a_b_sm<ResultType, Mod>::f(
								r,
								add_mod_sm<ResultType, Mod>::f(poa, 1)
							);
							b = (n >> lead) & 1;
							if (b) {
								// r = r * a + 1
								r = multiply_mod_sa_b_sm<ResultType, Base, Mod>::f(r);
								r = add_mod_sm<ResultType, Mod>::f(r, 1);
							}
						}
						return r;
					}
			};

		} // namespace detail


		// a ** (n - 1) + ... + a ** 3 + a ** 2 + a ** 1 + 1
		KERBAL_MODULE_EXPORT
		template <typename ResultType, ResultType Base, ResultType Mod>
		struct sigma_pow_mod_sa_n_sm :
			detail::sigma_pow_mod_sa_n_sm_impl<ResultType, Base, Mod>
		{
			private:
				KERBAL_STATIC_ASSERT(
					kerbal::type_traits::is_unsigned<ResultType>::value,
					"ResultType must be unsigned"
				);

				KERBAL_STATIC_ASSERT((Base != 0), "Base != 0");
		};

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_SIGMA_POW_MOD_SA_N_SM_HPP
