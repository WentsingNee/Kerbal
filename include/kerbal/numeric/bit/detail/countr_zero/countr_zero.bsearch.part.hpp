/**
 * @file       countr_zero.bsearch.part.hpp
 * @brief
 * @date       2023-09-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_DETAIL_COUNTR_ZERO_COUNTR_ZERO_BSEARCH_PART_HPP
#define KERBAL_NUMERIC_BIT_DETAIL_COUNTR_ZERO_COUNTR_ZERO_BSEARCH_PART_HPP

#include <kerbal/numeric/bit/detail/countr_zero/countr_zero.plain.part.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/numeric/bit/detail/single_bit_bsearch.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <climits>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace bsearch
			{

				template <typename Unsigned>
				KERBAL_CONSTEXPR
				typename kerbal::type_traits::enable_if<
						single_bit_bsearch_depth<CHAR_BIT * sizeof(Unsigned)>::value != -1,
						int
				>::type
				countr_zero(Unsigned x) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(Unsigned)> DIGIT;
					typedef kerbal::numeric::detail::single_bit_bsearch_depth<DIGIT::value> N;
					return kerbal::numeric::detail::single_bit_bsearch<Unsigned, N::value - 1>::f(x & (-x)) + (x == 0 ? 1 : 0);
				}

				template <typename Unsigned>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<
						single_bit_bsearch_depth<CHAR_BIT * sizeof(Unsigned)>::value == -1,
						int
				>::type
				countr_zero(Unsigned x) KERBAL_NOEXCEPT
				{
					return kerbal::numeric::detail::plain::countr_zero(x);
				}

			} // namespace bsearch

		} // namespace detail

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_DETAIL_COUNTR_ZERO_COUNTR_ZERO_BSEARCH_PART_HPP
