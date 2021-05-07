/**
 * @file       find.avx2.part.hpp
 * @brief
 * @date       2021-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_AVX2_PART_HPP
#define KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_AVX2_PART_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <immintrin.h>

#include <kerbal/algorithm/querier/detail/find/find.plain.part.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			namespace avx2
			{

				inline
				const char *
				find(const char * first, const char * last, const char & x) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m256i) / sizeof(char)> STEP;

					__m256i const mx = _mm256_set1_epi8(x); // AVX
					__m256i const mALL_ONE = _mm256_set1_epi8(~0); // AVX
					std::size_t loop = (last - first) / STEP::value;
					for (std::size_t i = 0; i < loop; ++i) {
						const __m256i * const mpf = reinterpret_cast<const __m256i *>(first);
						__m256i mrf = _mm256_loadu_si256(mpf); // AVX
						mrf = _mm256_cmpeq_epi8(mrf, mx); // AVX2

						if (!_mm256_testz_si256(mrf, mALL_ONE)) { // AVX
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
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m256i) / sizeof(kerbal::compatibility::int16_t)> STEP;

					__m256i const mx = _mm256_set1_epi16(x); // AVX
					__m256i const mALL_ONE = _mm256_set1_epi16(~0); // AVX
					std::size_t loop = (last - first) / STEP::value;
					for (std::size_t i = 0; i < loop; ++i) {
						const __m256i * const mpf = reinterpret_cast<const __m256i *>(first);
						__m256i mrf = _mm256_loadu_si256(mpf); // AVX
						mrf = _mm256_cmpeq_epi16(mrf, mx); // AVX2

						if (!_mm256_testz_si256(mrf, mALL_ONE)) { // AVX
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
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m256i) / sizeof(kerbal::compatibility::int32_t)> STEP;

					__m256i const mx = _mm256_set1_epi32(x); // AVX
					__m256i const mALL_ONE = _mm256_set1_epi32(~0); // AVX
					std::size_t loop = (last - first) / STEP::value;
					for (std::size_t i = 0; i < loop; ++i) {
						const __m256i * const mpf = reinterpret_cast<const __m256i *>(first);
						__m256i mrf = _mm256_loadu_si256(mpf); // AVX
						mrf = _mm256_cmpeq_epi32(mrf, mx); // AVX2

						if (!_mm256_testz_si256(mrf, mALL_ONE)) { // AVX
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
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m256i) / sizeof(kerbal::compatibility::int64_t)> STEP;

					__m256i const mx = _mm256_set1_epi64x(x); // AVX
					__m256i const mALL_ONE = _mm256_set1_epi64x(~0); // AVX
					std::size_t loop = (last - first) / STEP::value;
					for (std::size_t i = 0; i < loop; ++i) {
						const __m256i * const mpf = reinterpret_cast<const __m256i *>(first);
						__m256i mrf = _mm256_loadu_si256(mpf); // AVX
						mrf = _mm256_cmpeq_epi64(mrf, mx); // AVX2

						if (!_mm256_testz_si256(mrf, mALL_ONE)) { // AVX
							break;
						}
						first += STEP::value;
					}
					return kerbal::algorithm::detail::plain::find(first, last, x);
				}

			} // namespace avx2

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_AVX2_PART_HPP
