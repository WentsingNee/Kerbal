/**
 * @file       bitarray.bmi.hpp
 * @brief
 * @date       2022-11-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_BMI2_HPP
#define KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_BMI2_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/smath/max_sa_sb.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <kerbal/numeric/bit/bitarray/bitarray.plain.hpp>

#include <immintrin.h>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace bmi2
			{

				template <typename T, T a, T b>
				struct static_max :
						kerbal::type_traits::integral_constant<T, (a > b ? a : b)>
				{
				};

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint8_t>::type
				bitarray(kerbal::compatibility::uint8_t x)
				{
					typedef kerbal::compatibility::uint8_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					const uint64_t mask = 0x0101010101010101ull;

					kerbal::type_traits::aligned_storage<
							kerbal::smath::max_sa_sb<std::size_t, sizeof(bitarray_result_t), sizeof(uint64_t)>::value,
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;
					reinterpret_cast<uint64_t &>(as) = __bswap_64(_pdep_u64(static_cast<uint64_t>(x), mask));
					return reinterpret_cast<const bitarray_result_t&>(as);
				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint16_t>::type
				bitarray(kerbal::compatibility::uint16_t x)
				{
					typedef kerbal::compatibility::uint16_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					const uint64_t mask = 0x0101010101010101ull;

					kerbal::type_traits::aligned_storage<
							kerbal::smath::max_sa_sb<std::size_t, sizeof(bitarray_result_t), sizeof(uint64_t)>::value,
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;

					reinterpret_cast<uint64_t *>(&as)[1] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x), mask));
					reinterpret_cast<uint64_t *>(&as)[0] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 8), mask));

					return reinterpret_cast<const bitarray_result_t&>(as);
				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint32_t>::type
				bitarray(kerbal::compatibility::uint32_t x)
				{
					typedef kerbal::compatibility::uint32_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					const uint64_t mask = 0x0101010101010101ull;

					kerbal::type_traits::aligned_storage<
							kerbal::smath::max_sa_sb<std::size_t, sizeof(bitarray_result_t), sizeof(uint64_t)>::value,
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;

					reinterpret_cast<uint64_t *>(&as)[3] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x), mask));
					reinterpret_cast<uint64_t *>(&as)[2] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 8), mask));
					reinterpret_cast<uint64_t *>(&as)[1] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 16), mask));
					reinterpret_cast<uint64_t *>(&as)[0] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 24), mask));

					return reinterpret_cast<const bitarray_result_t&>(as);
				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint64_t>::type
				bitarray(kerbal::compatibility::uint64_t x)
				{
					typedef kerbal::compatibility::uint64_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					const uint64_t mask = 0x0101010101010101ull;

					kerbal::type_traits::aligned_storage<
							kerbal::smath::max_sa_sb<std::size_t, sizeof(bitarray_result_t), sizeof(uint64_t)>::value,
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;

					reinterpret_cast<uint64_t *>(&as)[7] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x), mask));
					reinterpret_cast<uint64_t *>(&as)[6] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 8), mask));
					reinterpret_cast<uint64_t *>(&as)[5] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 16), mask));
					reinterpret_cast<uint64_t *>(&as)[4] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 24), mask));
					reinterpret_cast<uint64_t *>(&as)[3] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 32), mask));
					reinterpret_cast<uint64_t *>(&as)[2] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 40), mask));
					reinterpret_cast<uint64_t *>(&as)[1] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 48), mask));
					reinterpret_cast<uint64_t *>(&as)[0] = __bswap_64(_pdep_u64(static_cast<uint64_t>(x >> 56), mask));

					return reinterpret_cast<const bitarray_result_t&>(as);
				}

			} // namespace bmi2

		} // namespace detail

	} // namespace numeric

} // namespace kerbal


#endif // KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_BMI2_HPP
