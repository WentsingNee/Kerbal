/**
 * @file       bitarray.bmi2.hpp
 * @brief
 * @date       2022-11-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_DETAIL_BITARRY_BITARRAY_BMI2_HPP
#define KERBAL_NUMERIC_BIT_DETAIL_BITARRY_BITARRAY_BMI2_HPP

#include <kerbal/numeric/bit/detail/bitarray/bitarray.plain.hpp>

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <climits>
#include <cstddef>

#include <immintrin.h>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace bmi2
			{

#		define EACH(i) do { \
					unsigned char b = x >> (((sizeof(Unsigned) - 1) - (i)) * CHAR_BIT); \
					kerbal::compatibility::uint64_t t = _pdep_u64(static_cast<kerbal::compatibility::uint64_t>(b), MASK); \
					t = __bswap_64(t); \
					*(reinterpret_cast<kerbal::compatibility::uint64_t*>(static_cast<void*>(&r[(i) * CHAR_BIT]))) = t; \
				} while(false)

				inline
				bitarray_result<kerbal::compatibility::uint8_t>::type
				bitarray(kerbal::compatibility::uint8_t x) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint8_t Unsigned;
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;

					EACH(0);

					return r;
				}

				inline
				bitarray_result<kerbal::compatibility::uint16_t>::type
				bitarray(kerbal::compatibility::uint16_t x) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint16_t Unsigned;
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;

					EACH(0);
					EACH(1);

					return r;
				}

				inline
				bitarray_result<kerbal::compatibility::uint32_t>::type
				bitarray(kerbal::compatibility::uint32_t x) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Unsigned;
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;

					EACH(0);
					EACH(1);
					EACH(2);
					EACH(3);

					return r;
				}

				inline
				bitarray_result<kerbal::compatibility::uint64_t>::type
				bitarray(kerbal::compatibility::uint64_t x) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t Unsigned;
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;

					EACH(0);
					EACH(1);
					EACH(2);
					EACH(3);
					EACH(4);
					EACH(5);
					EACH(6);
					EACH(7);

					return r;
				}

				template <typename Unsigned>
				typename bitarray_result<Unsigned>::type
				bitarray(Unsigned x) KERBAL_NOEXCEPT
				{
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;
					for (std::size_t i = 0; i < sizeof(Unsigned); ++i) {
						EACH(i);
					}
					return r;
				}

#		undef EACH

			} // namespace bmi2

		} // namespace detail

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_DETAIL_BITARRY_BITARRAY_BMI2_HPP
