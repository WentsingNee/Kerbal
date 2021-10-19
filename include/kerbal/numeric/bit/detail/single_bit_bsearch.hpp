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
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <cstddef>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			template <typename Unsigned, int I>
			struct single_bit_bsearch_pow_of_2 :
					kerbal::type_traits::integral_constant<
						Unsigned,
						static_cast<Unsigned>(1) << I
					>
			{
				private:
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "Type should be unsigned");
			};

			template <typename Unsigned, Unsigned x>
			struct single_bit_bsearch_has_single_bit :
					kerbal::type_traits::bool_constant<
						(x & (x - 1)) == 0
					>
			{
				private:
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "Type should be unsigned");
			};

			// mask<u32, 1>  ->  01010101010101010101010101010101
			// mask<u32, 2>  ->  00110011001100110011001100110011
			// mask<u32, 4>  ->  00001111000011110000111100001111
			template <typename Unsigned, unsigned int I>
			struct single_bit_bsearch_mask :
					kerbal::type_traits::integral_constant<
							Unsigned,
							static_cast<Unsigned>(-1) / ((static_cast<Unsigned>(1u) << I) + 1)
					>
			{
				private:
					KERBAL_STATIC_ASSERT((single_bit_bsearch_has_single_bit<unsigned, I>::value), "I should only has single bit");
			};

			template <std::size_t I>
			struct single_bit_bsearch_depth : kerbal::type_traits::integral_constant<int, -1>
			{
			};

			template <>
			struct single_bit_bsearch_depth<8> : kerbal::type_traits::integral_constant<int, 3>
			{
			};

			template <>
			struct single_bit_bsearch_depth<16> : kerbal::type_traits::integral_constant<int, 4>
			{
			};

			template <>
			struct single_bit_bsearch_depth<32> : kerbal::type_traits::integral_constant<int, 5>
			{
			};

			template <>
			struct single_bit_bsearch_depth<64> : kerbal::type_traits::integral_constant<int, 6>
			{
			};

			template <>
			struct single_bit_bsearch_depth<128> : kerbal::type_traits::integral_constant<int, 7>
			{
			};


			template <typename Unsigned, int I>
			struct single_bit_bsearch;

			template <typename Unsigned>
			struct single_bit_bsearch<Unsigned, -1>
			{
					KERBAL_CONSTEXPR
					static int f(Unsigned x) KERBAL_NOEXCEPT
					{
						return 0;
					}
			};

			template <typename Unsigned, int I>
			struct single_bit_bsearch
			{
					typedef single_bit_bsearch_pow_of_2<Unsigned, I> G;
					typedef single_bit_bsearch_mask<Unsigned, G::value> MASK;

					KERBAL_CONSTEXPR
					static int f(Unsigned x) KERBAL_NOEXCEPT
					{
						return single_bit_bsearch<Unsigned, I - 1>::f(x) + (x & MASK::value ? 0 : G::value);
					}
			};

		} // namespace detail

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_DETAIL_SINGLE_BIT_BSEARCH_HPP
