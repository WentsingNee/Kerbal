/**
 * @file       multiply_mod_sa_sb_sm.hpp
 * @brief
 * @date       2024-03-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_MULTIPLY_MOD_SA_SB_SM_HPP
#define KERBAL_SMATH_MULTIPLY_MOD_SA_SB_SM_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <kerbal/smath/detail/is_never_overflow_for_mul_mod.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <
				typename ResultType, ResultType a, ResultType b, ResultType m,
				int = multiply_mod_sa_b_sm_selector<ResultType, a, m>::value
			>
			struct multiply_mod_sa_sb_sm_impl_dispatch;


			template <typename ResultType, ResultType a, ResultType b, ResultType m, bool>
			struct multiply_mod_sa_sb_sm_impl_t1_case;

			template <typename ResultType, ResultType a, ResultType b, ResultType m>
			struct multiply_mod_sa_sb_sm_impl_t1_case<ResultType, a, b, m, false>
			{
					typedef kerbal::type_traits::integral_constant<ResultType, m / a> Q;
					typedef kerbal::type_traits::integral_constant<ResultType, m % a> R;

					typedef multiply_mod_sa_sb_sm_impl_dispatch<
						ResultType, R::value, b / Q::value, m
					> RESULT;
			};

			template <typename ResultType, ResultType a, ResultType b, ResultType m>
			struct multiply_mod_sa_sb_sm_impl_t1_case<ResultType, a, b, m, true>
			{
					typedef kerbal::type_traits::integral_constant<ResultType, m / a> Q;
					typedef kerbal::type_traits::integral_constant<ResultType, m % a> R;

					typedef kerbal::type_traits::integral_constant<
						ResultType, R::value * (b / Q::value)
					> RESULT;
			};

			template <typename ResultType, ResultType a, ResultType b, ResultType m>
			struct multiply_mod_sa_sb_sm_impl_t1
			{
					typedef kerbal::type_traits::integral_constant<ResultType, m / a> Q;
					typedef kerbal::type_traits::integral_constant<ResultType, m % a> R;

					typedef typename multiply_mod_sa_sb_sm_impl_t1_case<
						ResultType,
						a, b, m,
						R::value <= Q::value
					>::RESULT RESULT;
			};

			template <typename ResultType, ResultType a, ResultType b, ResultType m>
			struct multiply_mod_sa_sb_sm_schrage
			{
					typedef kerbal::type_traits::integral_constant<ResultType, m / a> Q;
					typedef kerbal::type_traits::integral_constant<ResultType, m % a> R;

					typedef kerbal::type_traits::integral_constant<
						ResultType, a * (b % Q::value)
					> t0;

					typedef typename multiply_mod_sa_sb_sm_impl_t1<
						ResultType, a, b, m
					>::RESULT t1;

					typedef kerbal::type_traits::integral_constant<
						ResultType,
						t0::value - t1::value + (t0::value < t1::value) * m
					> RESULT;
			};


			template <
				typename ResultType, ResultType a, ResultType b, ResultType m,
				bool = (b <= kerbal::numeric::numeric_limits<ResultType>::MAX::value / a)
			>
			struct multiply_mod_sa_sb_sm_impl_is_overflow_handler;

			template <typename ResultType, ResultType a, ResultType b, ResultType m>
			struct multiply_mod_sa_sb_sm_impl_is_overflow_handler<ResultType, a, b, m, false> :
				multiply_mod_sa_sb_sm_schrage<ResultType, a, b, m>::RESULT
			{
			};

			// a * b will not overflow
			template <typename ResultType, ResultType a, ResultType b, ResultType m>
			struct multiply_mod_sa_sb_sm_impl_is_overflow_handler<ResultType, a, b, m, true> :
				kerbal::type_traits::integral_constant<ResultType, a * b % m>
			{
			};


			template <typename ResultType, ResultType a, ResultType b, ResultType m>
			struct multiply_mod_sa_sb_sm_impl_dispatch<ResultType, a, b, m, 0> : // m != 0 && a % m != 0
				multiply_mod_sa_sb_sm_impl_is_overflow_handler<ResultType, a, b, m>
			{
				private:
					KERBAL_STATIC_ASSERT(a % m == a, "static check failed");
					KERBAL_STATIC_ASSERT(m != 0 && a != 0, "static check failed");
			};

			template <typename ResultType, ResultType a, ResultType b, ResultType m>
			struct multiply_mod_sa_sb_sm_impl_dispatch<ResultType, a, b, m, 1> : // m != 0 && a % m == 0
				kerbal::type_traits::integral_constant<ResultType, 0>
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0 && a % m == 0, "static check failed");
			};

			template <typename ResultType, ResultType a, ResultType b, ResultType m>
			struct multiply_mod_sa_sb_sm_impl_dispatch<ResultType, a, b, m, 2> : // m == 0
				kerbal::type_traits::integral_constant<
					ResultType, a * b
				> //TODO overflow
			{
				private:
					KERBAL_STATIC_ASSERT(m == 0, "static check failed");
			};

		} // namespace detail


		KERBAL_MODULE_EXPORT
		template <typename ResultType, ResultType a, ResultType b, ResultType m>
		struct multiply_mod_sa_sb_sm :
			detail::multiply_mod_sa_sb_sm_impl_dispatch<
				ResultType,
				m == 0 ? a : a % m,
				m == 0 ? b : b % m,
				m
			>
		{
			private:
				KERBAL_STATIC_ASSERT(
					kerbal::type_traits::is_unsigned<ResultType>::value,
					"ResultType should be unsigned"
				);
		};

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_MULTIPLY_MOD_SA_SB_SM_HPP
