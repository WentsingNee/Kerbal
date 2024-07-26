/**
 * @file       pow_mod_sa_sn_sm.hpp
 * @brief
 * @date       2024-04-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_POW_MOD_SA_SN_SM_HPP
#define KERBAL_SMATH_POW_MOD_SA_SN_SM_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/smath/multiply_mod_sa_sb_sm.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <
				typename ResultType, typename IndexType, ResultType Base, IndexType Index, ResultType Mod,
				int case_ = (
					Index == 0 ?
					0 :
					Index % 2u == 0 ? 1 : 2
				)
			>
			struct pow_mod_sa_sn_sm_impl;

			template <typename ResultType, typename IndexType, ResultType Base, IndexType Index, ResultType Mod>
			struct pow_mod_sa_sn_sm_impl<ResultType, IndexType, Base, Index, Mod, 0>
			{
					typedef kerbal::type_traits::integral_constant<ResultType, 1> result;
			};

			template <typename ResultType, typename IndexType, ResultType Base, IndexType Index, ResultType Mod>
			struct pow_mod_sa_sn_sm_impl<ResultType, IndexType, Base, Index, Mod, 1>
			{
					typedef typename pow_mod_sa_sn_sm_impl<ResultType, IndexType, Base, Index / 2u, Mod>::result HALF_N_RESULT;
					typedef kerbal::smath::multiply_mod_sa_sb_sm<ResultType, HALF_N_RESULT::value, HALF_N_RESULT::value, Mod> result;
			};

			template <typename ResultType, typename IndexType, ResultType Base, IndexType Index, ResultType Mod>
			struct pow_mod_sa_sn_sm_impl<ResultType, IndexType, Base, Index, Mod, 2>
			{
					typedef typename pow_mod_sa_sn_sm_impl<ResultType, IndexType, Base, Index - 1u, Mod>::result PREV_RESULT;
					typedef kerbal::smath::multiply_mod_sa_sb_sm<ResultType, PREV_RESULT::value, Base, Mod> result;
			};


			template <typename ResultType, typename IndexType, ResultType Base, IndexType Index, ResultType Mod, bool = (Mod == 0)>
			struct pow_mod_sa_sn_sm_reduce_base;

			template <typename ResultType, typename IndexType, ResultType Base, IndexType Index, ResultType Mod>
			struct pow_mod_sa_sn_sm_reduce_base<ResultType, IndexType, Base, Index, Mod, true> : // m == 0
				pow_mod_sa_sn_sm_impl<ResultType, IndexType, Base, Index, Mod>::result
			{
			};

			template <typename ResultType, typename IndexType, ResultType Base, IndexType Index, ResultType Mod>
			struct pow_mod_sa_sn_sm_reduce_base<ResultType, IndexType, Base, Index, Mod, false> : // m != 0
				pow_mod_sa_sn_sm_impl<ResultType, IndexType, Base % Mod, Index, Mod>::result
			{
			};

		} // namespace detail

		/*
		 * a ** n % m
		 */
		KERBAL_MODULE_EXPORT
		template <typename ResultType, typename IndexType, ResultType Base, IndexType Index, ResultType Mod>
		struct pow_mod_sa_sn_sm : detail::pow_mod_sa_sn_sm_reduce_base<ResultType, IndexType, Base, Index, Mod>
		{
			private:
				KERBAL_STATIC_ASSERT(
					(kerbal::type_traits::is_unsigned<ResultType>::value),
					"ResultType should be unsigned"
				);
				KERBAL_STATIC_ASSERT(
					(kerbal::type_traits::is_unsigned<IndexType>::value),
					"IndexType should be unsigned"
				);
		};

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_POW_MOD_SA_SN_SM_HPP
