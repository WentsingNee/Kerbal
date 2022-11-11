/**
 * @file       all_chunk.sse41.hpp
 * @brief
 * @date       2022-11-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_SSE41_HPP
#define KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_SSE41_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <emmintrin.h> // SSE2
#include <smmintrin.h> // SSE4.1

#include <kerbal/bitset/detail/all_chunk/all_chunk.plain.hpp>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			namespace sse41
			{

				inline bool all_chunk(const kerbal::compatibility::uint32_t block[], std::size_t trunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;

					std::size_t i = 0;
					for (; i + STEP::value <= trunk_size; i += STEP::value) {
						__m128i xmm_block = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i])); // SSE2
						if (!_mm_test_all_ones(xmm_block)) { // SSE4.1
							return false;
						}
					}

					while (i < trunk_size) {
						EACH(i);
						++i;
					}

					return true;
				}

				inline bool all_chunk4(const kerbal::compatibility::uint32_t block[], std::size_t trunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;

					std::size_t i = 0;
					for (; i + 4 * STEP::value <= trunk_size; i += 4 * STEP::value) {
						__m128i xmm_blockp0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 0 * STEP::value])); // SSE2
						__m128i xmm_blockp1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 1 * STEP::value])); // SSE2
						__m128i xmm_blockp2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 2 * STEP::value])); // SSE2
						__m128i xmm_blockp3 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 3 * STEP::value])); // SSE2

						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp1); // SSE2
						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp2); // SSE2
						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp3); // SSE2


						if (!_mm_test_all_ones(xmm_blockp0)) { // SSE4.1
							return false;
						}
					}

					while (i < trunk_size) {
						EACH(i);
						++i;
					}

					return true;
				}

				inline bool all_chunk8(const kerbal::compatibility::uint32_t block[], std::size_t trunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;

					std::size_t i = 0;
					for (; i + 8 * STEP::value <= trunk_size; i += 8 * STEP::value) {
						__m128i xmm_blockp0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 0 * STEP::value])); // SSE2
						__m128i xmm_blockp1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 1 * STEP::value])); // SSE2
						__m128i xmm_blockp2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 2 * STEP::value])); // SSE2
						__m128i xmm_blockp3 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 3 * STEP::value])); // SSE2
						__m128i xmm_blockp4 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 4 * STEP::value])); // SSE2
						__m128i xmm_blockp5 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 5 * STEP::value])); // SSE2
						__m128i xmm_blockp6 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 6 * STEP::value])); // SSE2
						__m128i xmm_blockp7 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&block[i + 7 * STEP::value])); // SSE2

						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp1); // SSE2
						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp2); // SSE2
						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp3); // SSE2
						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp4); // SSE2
						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp5); // SSE2
						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp6); // SSE2
						xmm_blockp0 = _mm_and_si128(xmm_blockp0, xmm_blockp7); // SSE2


						if (!_mm_test_all_ones(xmm_blockp0)) { // SSE4.1
							return false;
						}
					}

					while (i < trunk_size) {
						EACH(i);
						++i;
					}

					return true;
				}

			} // namespace sse41

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_SSE41_HPP
