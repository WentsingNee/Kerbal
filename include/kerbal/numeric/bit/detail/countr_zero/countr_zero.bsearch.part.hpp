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
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/numeric/bit/single_bit_bsearch.hpp>
#include <kerbal/smath/has_single_bit.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>
#include <cstddef>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace bsearch
			{

				template <typename Unsigned>
				KERBAL_CONSTEXPR14
				int countr_zero_impl(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
				{
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "x should be unsigned");
					return kerbal::numeric::detail::plain::countr_zero(x);
				}

				template <typename Unsigned>
				KERBAL_CONSTEXPR
				int countr_zero_impl(Unsigned x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
				{
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "x should be unsigned");
					return kerbal::numeric::single_bit_bsearch(
							static_cast<Unsigned>(
									(x & (-x)) + (x == 0 ? 1 : 0)
							)
					);
				}

				template <typename Unsigned>
				KERBAL_CONSTEXPR14
				int countr_zero(Unsigned x) KERBAL_NOEXCEPT
				{
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "x should be unsigned");
					typedef kerbal::smath::has_single_bit<std::size_t, CHAR_BIT * sizeof(Unsigned)> bits_count_is_pow_of_2;
					return countr_zero_impl(x, bits_count_is_pow_of_2());
				}

			} // namespace bsearch

		} // namespace detail

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_DETAIL_COUNTR_ZERO_COUNTR_ZERO_BSEARCH_PART_HPP
