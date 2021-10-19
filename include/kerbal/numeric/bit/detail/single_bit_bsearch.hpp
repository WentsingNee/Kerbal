/**
 * @file       single_bit_bsearch.hpp
 * @brief
 * @date       2022-09-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_DETAIL_SINGLE_BIT_BSEARCH_HPP
#define KERBAL_NUMERIC_BIT_DETAIL_SINGLE_BIT_BSEARCH_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/smath/countr_zero.hpp>
#include <kerbal/smath/has_single_bit.hpp>
#include <kerbal/smath/two_pow_n.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>
#include <climits>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			// mask<u32, 1>  ->  01010101010101010101010101010101
			// mask<u32, 2>  ->  00110011001100110011001100110011
			// mask<u32, 4>  ->  00001111000011110000111100001111
			// mask<u32, 8>  ->  00000000111111110000000011111111
			template <typename Unsigned, unsigned int I>
			struct single_bit_bsearch_mask :
					kerbal::type_traits::integral_constant<
						Unsigned,
						static_cast<Unsigned>(-1) / (kerbal::smath::two_pow_n<Unsigned, I>::value + 1)
					>
			{
				private:
					KERBAL_STATIC_ASSERT((kerbal::smath::has_single_bit<unsigned, I>::value), "I should only has single bit");
			};


			template <typename Unsigned, int I>
			struct single_bit_bsearch_impl;

			template <typename Unsigned>
			struct single_bit_bsearch_impl<Unsigned, 0>
			{
					KERBAL_CONSTEXPR
					static int f(Unsigned /*x*/) KERBAL_NOEXCEPT
					{
						return 0;
					}
			};

			template <typename Unsigned, int I>
			struct single_bit_bsearch_impl
			{
					KERBAL_CONSTEXPR
					static int f(Unsigned x) KERBAL_NOEXCEPT
					{
						typedef kerbal::smath::two_pow_n<Unsigned, I - 1> GRAININESS;
						typedef single_bit_bsearch_mask<Unsigned, GRAININESS::value> MASK;

						return single_bit_bsearch_impl<Unsigned, I - 1>::f(x) + (x & MASK::value ? 0 : GRAININESS::value);
					}
			};

			template <typename Unsigned>
			struct single_bit_bsearch
			{
					KERBAL_CONSTEXPR
					static int f(Unsigned x) KERBAL_NOEXCEPT
					{
						typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(Unsigned)> DIGIT;
						typedef kerbal::smath::countr_zero<std::size_t, DIGIT::value> LOOP_DEPTH;

						return single_bit_bsearch_impl<Unsigned, LOOP_DEPTH::value>::f(x);
					}
			};

		} // namespace detail

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_DETAIL_SINGLE_BIT_BSEARCH_HPP
