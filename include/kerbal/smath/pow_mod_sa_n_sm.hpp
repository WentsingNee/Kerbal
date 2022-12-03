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
#include <kerbal/smath/multiply_mod_a_b_sm.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename ResultType, ResultType Base, ResultType Mod>
			struct pow_mod_sa_n_sm_impl
			{
				public:
					template <typename IndexType>
					KERBAL_CONSTEXPR14
					static
					ResultType f(IndexType index) KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<IndexType>::value, "index must be unsigned");

						ResultType r = 1;
						ResultType base = Base;
						while (true) {
							IndexType half_n = index / 2u;
							if (index % 2u != 0) {
								r = kerbal::smath::multiply_mod_a_b_sm<ResultType, Mod>::f(r, base);
							}
							if (half_n == 0) {
								break;
							}
							base = kerbal::smath::multiply_mod_a_b_sm<ResultType, Mod>::f(base, base);
							index = half_n;
						}
						return r;
					}
			};


			template <typename ResultType, ResultType Base, ResultType Mod, bool = (Mod == 0)>
			struct pow_mod_sa_n_sm_reduce_base;

			template <typename ResultType, ResultType Base, ResultType Mod>
			struct pow_mod_sa_n_sm_reduce_base<ResultType, Base, Mod, true> : // Mod == 0
				pow_mod_sa_n_sm_impl<ResultType, Base, Mod>
			{
			};

			template <typename ResultType, ResultType Base, ResultType Mod>
			struct pow_mod_sa_n_sm_reduce_base<ResultType, Base, Mod, false> : // Mod != 0
				pow_mod_sa_n_sm_impl<ResultType, Base % Mod, Mod>
			{
			};

		} // namespace detail

		/*
		 * a ** n % m
		 */
		template <typename ResultType, ResultType Base, ResultType Mod>
		struct pow_mod_sa_n_sm :
			detail::pow_mod_sa_n_sm_reduce_base<ResultType, Base, Mod>
		{
			private:
				KERBAL_STATIC_ASSERT(
					(kerbal::type_traits::is_unsigned<ResultType>::value),
					"ResultType should be unsigned"
				);
		};

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_POW_MOD_SA_N_SM_HPP
