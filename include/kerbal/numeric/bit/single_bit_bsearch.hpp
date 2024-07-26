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

#ifndef KERBAL_NUMERIC_BIT_SINGLE_BIT_BSEARCH_HPP
#define KERBAL_NUMERIC_BIT_SINGLE_BIT_BSEARCH_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/smath/countr_zero.hpp>
#include <kerbal/smath/has_single_bit.hpp>
#include <kerbal/smath/two_pow_sn.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>
#include <cstddef>


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
			// mask<u32, 16> ->  00000000000000001111111111111111
			template <typename Unsigned, unsigned int I>
			struct single_bit_bsearch_mask :
				kerbal::type_traits::integral_constant<
					Unsigned,
					static_cast<Unsigned>(-1) / (kerbal::smath::two_pow_sn<Unsigned, I>::value + 1)
				>
			{
				private:
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "type should be unsigned");
					KERBAL_STATIC_ASSERT((kerbal::smath::has_single_bit<unsigned, I>::value), "I should only has single bit");
			};


			template <typename Unsigned, std::size_t I>
			struct single_bit_bsearch_loop;

			template <typename Unsigned>
			struct single_bit_bsearch_loop<Unsigned, 0>
			{
				private:
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "type should be unsigned");

				public:
					KERBAL_CONSTEXPR
					static
					int f(Unsigned /*x*/) KERBAL_NOEXCEPT
					{
						return 0;
					}
			};

			template <typename Unsigned, std::size_t I>
			struct single_bit_bsearch_loop
			{
				private:
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "type should be unsigned");

				public:
					KERBAL_CONSTEXPR
					static
					int f(Unsigned x) KERBAL_NOEXCEPT
					{
						typedef kerbal::smath::two_pow_sn<Unsigned, I - 1> GRAININESS;
						typedef single_bit_bsearch_mask<Unsigned, GRAININESS::value> MASK;

						return single_bit_bsearch_loop<Unsigned, I - 1>::f(x) + (x & MASK::value ? 0 : GRAININESS::value);
					}
			};

		} // namespace detail


		// for u32:
		//   (x & 01010101010101010101010101010101 ? 0 : 1)
		// + (x & 00110011001100110011001100110011 ? 0 : 2)
		// + (x & 00001111000011110000111100001111 ? 0 : 4)
		// + (x & 00000000111111110000000011111111 ? 0 : 8)
		// + (x & 00000000000000001111111111111111 ? 0 : 16)
		KERBAL_MODULE_EXPORT
		template <typename Unsigned>
		KERBAL_CONSTEXPR
		int single_bit_bsearch(Unsigned x) KERBAL_NOEXCEPT
		{
			KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "type should be unsigned");
			typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(Unsigned)> DIGIT;
			typedef kerbal::smath::has_single_bit<std::size_t, DIGIT::value> bits_count_is_pow_of_2;
			KERBAL_STATIC_ASSERT(bits_count_is_pow_of_2::value, "the number of bits in type `Unsigned` should be pow of 2");
			typedef kerbal::smath::countr_zero<std::size_t, DIGIT::value> LOOP_DEPTH;

			return kerbal::numeric::detail::single_bit_bsearch_loop<Unsigned, LOOP_DEPTH::value>::f(x);
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_SINGLE_BIT_BSEARCH_HPP
