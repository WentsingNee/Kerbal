/**
 * @file       is_never_overflow_for_mul_mod.hpp
 * @brief
 * @date       2022-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_DETAIL_IS_NEVER_OVERFLOW_FOR_MUL_MOD_HPP
#define KERBAL_SMATH_DETAIL_IS_NEVER_OVERFLOW_FOR_MUL_MOD_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/conditional.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename ResultType, ResultType a, ResultType m>
			struct multiply_mod_sa_b_sm_selector :
				kerbal::type_traits::integral_constant<
					int,
					(
						m != 0 ?
						((a % m != 0) ? 0 : 1) :
						2
					)
				>
			{
			};

			template <typename ResultType, ResultType a, ResultType m, typename Integer, int>
			struct is_never_overflow_for_mul_mod_sa_sm_dispatch;

			// m != 0 && a % m != 0
			template <typename ResultType, ResultType a, ResultType m, typename Integer>
			struct is_never_overflow_for_mul_mod_sa_sm_dispatch<ResultType, a, m, Integer, 0> :
				kerbal::type_traits::bool_constant<
					m - 1 <= kerbal::numeric::numeric_limits<Integer>::MAX::value / (a % m)
				>
			{
				private:
					KERBAL_STATIC_ASSERT(a % m == a, "static check failed");
					KERBAL_STATIC_ASSERT(m != 0 && a % m != 0, "static check failed");
			};

			// m != 0 && a % m == 0
			template <typename ResultType, ResultType a, ResultType m, typename Integer>
			struct is_never_overflow_for_mul_mod_sa_sm_dispatch<ResultType, a, m, Integer, 1> :
				kerbal::type_traits::false_type
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0 && a % m == 0, "static check failed");
			};

			// m == 0
			template <typename ResultType, ResultType a, ResultType m, typename Integer>
			struct is_never_overflow_for_mul_mod_sa_sm_dispatch<ResultType, a, m, Integer, 2> :
				kerbal::type_traits::bool_constant<
					kerbal::numeric::numeric_limits<ResultType>::MAX::value <=
					kerbal::numeric::numeric_limits<Integer>::MAX::value / a
				>
			{
				private:
					KERBAL_STATIC_ASSERT(m == 0, "static check failed");
			};

			/**
			 * check whether a * (m - 1) will exceed the representation range of Integer type
			 */
			template <typename ResultType, ResultType a, ResultType m, typename Integer>
			struct is_never_overflow_for_mul_mod :
				is_never_overflow_for_mul_mod_sa_sm_dispatch<
					ResultType, a, m, Integer,
					multiply_mod_sa_b_sm_selector<ResultType, a, m>::value
				>
			{
			};



			template <typename ResultType, ResultType a, ResultType m>
			struct find_never_overflow_integer_type_for_mul_mod
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0, "static check failed");

					template <typename Integer>
					struct is_never_overflow :
						is_never_overflow_for_mul_mod<ResultType, a, m, Integer>
					{
					};

				public:
					typedef typename kerbal::type_traits::conditional<
						is_never_overflow<unsigned short>::value,
						unsigned short,
						typename kerbal::type_traits::conditional<
							is_never_overflow<unsigned int>::value,
							unsigned int,
							typename kerbal::type_traits::conditional<
								is_never_overflow<unsigned long>::value,
								unsigned long,
								typename kerbal::type_traits::conditional<
									is_never_overflow<unsigned long long>::value,
									unsigned long long,
									void
								>::type
							>::type
						>::type
					>::type type;

			};

		} // namespace detail

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_DETAIL_IS_NEVER_OVERFLOW_FOR_MUL_MOD_HPP
