/**
 * @file       mt_generate_copy_n.sse2.part.hpp
 * @brief
 * @date       2022-11-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_SSE2_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_SSE2_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <emmintrin.h>

#include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.plain.part.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace sse2
			{

				template <
					std::size_t U, kerbal::compatibility::uint32_t D,
					std::size_t S, kerbal::compatibility::uint32_t B,
					std::size_t T, kerbal::compatibility::uint32_t C,
					std::size_t L
				>
				void mt_generate_copy_n(
					const kerbal::compatibility::uint32_t mt_now[],
					kerbal::compatibility::uint32_t * out,
					std::size_t n
				) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;
					const __m128i xmm_B = _mm_set1_epi32(B); // SSE2
					const __m128i xmm_C = _mm_set1_epi32(C); // SSE2
					const __m128i xmm_D = _mm_set1_epi32(D); // SSE2

					unsigned int i = 0; // Note: gcc unreasonable warning: iteration 4611686018427387903 invokes undefined behavior [-Waggressive-loop-optimizations]
					for (; i + STEP::value <= n; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt_now[i])); // SSE2
						__m128i xmm_shift, xmm_and;

						xmm_shift = _mm_srli_epi32(xmm_mti, U); // SSE2
						xmm_and = _mm_and_si128(xmm_shift, xmm_D); // SSE2
						xmm_mti = _mm_xor_si128(xmm_mti, xmm_and); // SSE2

						xmm_shift = _mm_slli_epi32(xmm_mti, S); // SSE2
						xmm_and = _mm_and_si128(xmm_shift, xmm_B); // SSE2
						xmm_mti = _mm_xor_si128(xmm_mti, xmm_and); // SSE2

						xmm_shift = _mm_slli_epi32(xmm_mti, T); // SSE2
						xmm_and = _mm_and_si128(xmm_shift, xmm_C); // SSE2
						xmm_mti = _mm_xor_si128(xmm_mti, xmm_and); // SSE2

						xmm_shift = _mm_srli_epi32(xmm_mti, L); // SSE2
						xmm_mti = _mm_xor_si128(xmm_mti, xmm_shift); // SSE2

						_mm_storeu_si128(reinterpret_cast<__m128i *>(out), xmm_mti); // SSE2
						out += STEP::value;
					}

					while (i < n) {
						EACH(i);
						++i;
					}

				}

				template <
					std::size_t U, kerbal::compatibility::uint64_t D,
					std::size_t S, kerbal::compatibility::uint64_t B,
					std::size_t T, kerbal::compatibility::uint64_t C,
					std::size_t L
				>
				void mt_generate_copy_n(
					const kerbal::compatibility::uint64_t mt_now[],
					kerbal::compatibility::uint64_t * out,
					std::size_t n
				) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t result_type;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 64> STEP;
					const __m128i xmm_B = _mm_set1_epi64x(B); // SSE2
					const __m128i xmm_C = _mm_set1_epi64x(C); // SSE2
					const __m128i xmm_D = _mm_set1_epi64x(D); // SSE2

					unsigned int i = 0; // Note: gcc unreasonable warning: iteration 4611686018427387903 invokes undefined behavior [-Waggressive-loop-optimizations]
					for (; i + STEP::value <= n; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt_now[i])); // SSE2
						__m128i xmm_shift, xmm_and;

						xmm_shift = _mm_srli_epi64(xmm_mti, U); // SSE2
						xmm_and = _mm_and_si128(xmm_shift, xmm_D); // SSE2
						xmm_mti = _mm_xor_si128(xmm_mti, xmm_and); // SSE2

						xmm_shift = _mm_slli_epi64(xmm_mti, S); // SSE2
						xmm_and = _mm_and_si128(xmm_shift, xmm_B); // SSE2
						xmm_mti = _mm_xor_si128(xmm_mti, xmm_and); // SSE2

						xmm_shift = _mm_slli_epi64(xmm_mti, T); // SSE2
						xmm_and = _mm_and_si128(xmm_shift, xmm_C); // SSE2
						xmm_mti = _mm_xor_si128(xmm_mti, xmm_and); // SSE2

						xmm_shift = _mm_srli_epi64(xmm_mti, L); // SSE2
						xmm_mti = _mm_xor_si128(xmm_mti, xmm_shift); // SSE2

						_mm_storeu_si128(reinterpret_cast<__m128i *>(out), xmm_mti); // SSE2
						out += STEP::value;
					}

					while (i < n) {
						EACH(i);
						++i;
					}

				}

			} // namespace sse2

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_SSE2_PART_HPP
