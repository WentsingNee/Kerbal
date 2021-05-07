/**
 * @file       find.sse41.part.hpp
 * @brief
 * @date       2021-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_SSE41_PART_HPP
#define KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_SSE41_PART_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <emmintrin.h>
#include <smmintrin.h>

#include <kerbal/algorithm/querier/detail/find/find.plain.part.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			namespace sse41
			{

				inline
				const char *
				find(const char * first, const char * last, const char & x) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m128i) / sizeof(char)> STEP;

					__m128i const mx = _mm_set1_epi8(x); // SSE2
					__m128i const mALL_ONE = _mm_set1_epi8(~0); // SSE2
					std::size_t loop = (last - first) / STEP::value;
					for (std::size_t i = 0; i < loop; ++i) {
						const __m128i * const mpf = reinterpret_cast<const __m128i *>(first);
						__m128i mrf = _mm_loadu_si128(mpf); // SSE2
						mrf = _mm_cmpeq_epi8(mrf, mx); // SSE2

						if (!_mm_testz_si128(mrf, mALL_ONE)) { // SSE4.1
							break;
						}
						first += STEP::value;
					}
					return kerbal::algorithm::detail::plain::find(first, last, x);
				}

				inline
				const kerbal::compatibility::int16_t *
				find(
					const kerbal::compatibility::int16_t * first,
					const kerbal::compatibility::int16_t * last,
					const kerbal::compatibility::int16_t & x
				) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m128i) / sizeof(kerbal::compatibility::int16_t)> STEP;

					__m128i const mx = _mm_set1_epi16(x); // SSE2
					__m128i const mALL_ONE = _mm_set1_epi16(~0); // SSE2
					std::size_t loop = (last - first) / STEP::value;
					for (std::size_t i = 0; i < loop; ++i) {
						const __m128i * const mpf = reinterpret_cast<const __m128i *>(first);
						__m128i mrf = _mm_loadu_si128(mpf); // SSE2
						mrf = _mm_cmpeq_epi16(mrf, mx); // SSE2

						if (!_mm_testz_si128(mrf, mALL_ONE)) { // SSE4.1
							break;
						}
						first += STEP::value;
					}
					return kerbal::algorithm::detail::plain::find(first, last, x);
				}

				inline
				const kerbal::compatibility::int32_t *
				find(
					const kerbal::compatibility::int32_t * first,
					const kerbal::compatibility::int32_t * last,
					const kerbal::compatibility::int32_t & x
				) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m128i) / sizeof(kerbal::compatibility::int32_t)> STEP;

					__m128i const mx = _mm_set1_epi32(x); // SSE2
					__m128i const mALL_ONE = _mm_set1_epi32(~0); // SSE2
					std::size_t loop = (last - first) / STEP::value;
					for (std::size_t i = 0; i < loop; ++i) {
						const __m128i * const mpf = reinterpret_cast<const __m128i *>(first);
						__m128i mrf = _mm_loadu_si128(mpf); // SSE2
						mrf = _mm_cmpeq_epi32(mrf, mx); // SSE2

						if (!_mm_testz_si128(mrf, mALL_ONE)) { // SSE4.1
							break;
						}
						first += STEP::value;
					}
					return kerbal::algorithm::detail::plain::find(first, last, x);
				}

				inline
				const kerbal::compatibility::int64_t *
				find(
					const kerbal::compatibility::int64_t * first,
					const kerbal::compatibility::int64_t * last,
					const kerbal::compatibility::int64_t & x
				) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m128i) / sizeof(kerbal::compatibility::int64_t)> STEP;

					__m128i const mx = _mm_set1_epi64x(x); // SSE2
					__m128i const mALL_ONE = _mm_set1_epi64x(~0); // SSE2
					std::size_t loop = (last - first) / STEP::value;
					for (std::size_t i = 0; i < loop; ++i) {
						const __m128i * const mpf = reinterpret_cast<const __m128i *>(first);
						__m128i mrf = _mm_loadu_si128(mpf); // SSE2
						mrf = _mm_cmpeq_epi64(mrf, mx); // SSE4.1!!!

						if (!_mm_testz_si128(mrf, mALL_ONE)) { // SSE4.1
							break;
						}
						first += STEP::value;
					}
					return kerbal::algorithm::detail::plain::find(first, last, x);
				}

			} // namespace sse41

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_SSE41_PART_HPP
