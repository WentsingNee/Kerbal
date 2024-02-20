/**
 * @file       reverse.avx2.hpp
 * @brief
 * @date       2024-02-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_AVX2_HPP
#define KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_AVX2_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <cstddef>

#include <immintrin.h>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			namespace avx2
			{

				inline
				__m256i k_reverse_swap_hi_lo(__m256i ymm) KERBAL_NOEXCEPT
				{
					int const REV_MASK = 78; // 0b'01'00'11'10
					return _mm256_permute4x64_epi64(ymm, REV_MASK); // AVX2
				}

				inline
				void reverse(kerbal::compatibility::uint8_t * first, kerbal::compatibility::uint8_t * last) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint8_t * iterator;
					typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last));
					std::size_t const STEP = sizeof(__m256i) / sizeof(value_type);
					__m256i const REV_MASK = _mm256_setr_epi8(
						31, 30, 29, 28, 27, 26, 25, 24,
						23, 22, 21, 20, 19, 18, 17, 16,
						15, 14, 13, 12, 11, 10,  9,  8,
						 7,  6,  5,  4,  3,  2,  1,  0
					); // AVX

					std::size_t loop = dist / (STEP * 2);
					std::size_t remain = dist % (STEP * 2);
					for (std::size_t i = 0; i < loop; ++i) {
						last -= STEP;
						__m256i * const mpf = reinterpret_cast<__m256i *>(first);
						__m256i * const mpl = reinterpret_cast<__m256i *>(last);
						__m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						__m256i ymm_l = _mm256_loadu_si256(mpl); // AVX
						ymm_f = k_reverse_swap_hi_lo(
							_mm256_shuffle_epi8(ymm_f, REV_MASK) // AVX2
						);
						ymm_l = k_reverse_swap_hi_lo(
							_mm256_shuffle_epi8(ymm_l, REV_MASK) // AVX2
						);
						_mm256_storeu_si256(mpf , ymm_l); // AVX
						_mm256_storeu_si256(mpl , ymm_f); // AVX
						first += STEP;
					}
					if (remain >= STEP) {
						last -= STEP;
						__m256i * const mpf = reinterpret_cast<__m256i *>(first);
						__m256i * const mpl = reinterpret_cast<__m256i *>(last);
						__m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						__m256i ymm_l = _mm256_loadu_si256(mpl); // AVX
						ymm_f = k_reverse_swap_hi_lo(
							_mm256_shuffle_epi8(ymm_f, REV_MASK) // AVX2
						);
						ymm_l = k_reverse_swap_hi_lo(
							_mm256_shuffle_epi8(ymm_l, REV_MASK) // AVX2
						);
						_mm256_storeu_si256(mpf , ymm_l); // AVX
						_mm256_storeu_si256(mpl , ymm_f); // AVX
					} else {
						for (std::size_t i = 0; i < remain / 2; ++i) {
							--last;
							kerbal::algorithm::iter_swap(first, last);
							++first;
						}
					}
				}

				inline
				void reverse(kerbal::compatibility::uint16_t * first, kerbal::compatibility::uint16_t * last) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint16_t * iterator;
					typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last));
					std::size_t const STEP = sizeof(__m256i) / sizeof(value_type);
					__m256i const REV_MASK = _mm256_setr_epi8(
						30, 31, 28, 29, 26, 27, 24, 25,
						22, 23, 20, 21, 18, 19, 16, 17,
						14, 15, 12, 13, 10, 11,  8,  9,
						 6,  7,  4,  5,  2,  3,  0,  1
					); // AVX

					std::size_t loop = dist / (STEP * 2);
					std::size_t remain = dist % (STEP * 2);
					for (std::size_t i = 0; i < loop; ++i) {
						last -= STEP;
						__m256i * const mpf = reinterpret_cast<__m256i *>(first);
						__m256i * const mpl = reinterpret_cast<__m256i *>(last);
						__m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						__m256i ymm_l = _mm256_loadu_si256(mpl); // AVX
						ymm_f = k_reverse_swap_hi_lo(
							_mm256_shuffle_epi8(ymm_f, REV_MASK) // AVX2
						);
						ymm_l = k_reverse_swap_hi_lo(
							_mm256_shuffle_epi8(ymm_l, REV_MASK) // AVX2
						);
						_mm256_storeu_si256(mpf , ymm_l); // AVX
						_mm256_storeu_si256(mpl , ymm_f); // AVX
						first += STEP;
					}
					if (remain >= STEP) {
						last -= STEP;
						__m256i * const mpf = reinterpret_cast<__m256i *>(first);
						__m256i * const mpl = reinterpret_cast<__m256i *>(last);
						__m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						__m256i ymm_l = _mm256_loadu_si256(mpl); // AVX
						ymm_f = k_reverse_swap_hi_lo(
							_mm256_shuffle_epi8(ymm_f, REV_MASK) // AVX2
						);
						ymm_l = k_reverse_swap_hi_lo(
							_mm256_shuffle_epi8(ymm_l, REV_MASK) // AVX2
						);
						_mm256_storeu_si256(mpf , ymm_l); // AVX
						_mm256_storeu_si256(mpl , ymm_f); // AVX
					} else {
						for (std::size_t i = 0; i < remain / 2; ++i) {
							--last;
							kerbal::algorithm::iter_swap(first, last);
							++first;
						}
					}
				}

				inline
				void reverse(kerbal::compatibility::uint32_t * first, kerbal::compatibility::uint32_t * last) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t * iterator;
					typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last));
					std::size_t const STEP = sizeof(__m256i) / sizeof(value_type);
					__m256i const REV_MASK = _mm256_setr_epi32(7, 6, 5, 4, 3, 2, 1, 0); // AVX

					std::size_t loop = dist / (STEP * 2);
					std::size_t remain = dist % (STEP * 2);
					for (std::size_t i = 0; i < loop; ++i) {
						last -= STEP;
						__m256i * const mpf = reinterpret_cast<__m256i *>(first);
						__m256i * const mpl = reinterpret_cast<__m256i *>(last);
						__m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						__m256i ymm_l = _mm256_loadu_si256(mpl); // AVX
						ymm_f = _mm256_permutevar8x32_epi32(ymm_f, REV_MASK); // AVX2
						ymm_l = _mm256_permutevar8x32_epi32(ymm_l, REV_MASK); // AVX2
						_mm256_storeu_si256(mpf , ymm_l); // AVX
						_mm256_storeu_si256(mpl , ymm_f); // AVX
						first += STEP;
					}
					if (remain >= STEP) {
						last -= STEP;
						__m256i * const mpf = reinterpret_cast<__m256i *>(first);
						__m256i * const mpl = reinterpret_cast<__m256i *>(last);
						__m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						__m256i ymm_l = _mm256_loadu_si256(mpl); // AVX
						ymm_f = _mm256_permutevar8x32_epi32(ymm_f, REV_MASK); // AVX2
						ymm_l = _mm256_permutevar8x32_epi32(ymm_l, REV_MASK); // AVX2
						_mm256_storeu_si256(mpf , ymm_l); // AVX
						_mm256_storeu_si256(mpl , ymm_f); // AVX
					} else {
						// __m256i * const mpf = reinterpret_cast<__m256i *>(first);
						// __m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						// ymm_f = _mm256_permutevar8x32_epi32(ymm_f, permute_mask); // AVX2
						// _mm256_storeu_si256(mpf , ymm_f); // AVX
						for (std::size_t i = 0; i < remain / 2; ++i) {
							--last;
							kerbal::algorithm::iter_swap(first, last);
							++first;
						}
					}
				}

				inline
				void reverse(kerbal::compatibility::uint64_t * first, kerbal::compatibility::uint64_t * last) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t * iterator;
					typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last));
					std::size_t const STEP = sizeof(__m256i) / sizeof(value_type);
					int const REV_MASK = 27; // 0b'00'01'10'11

					std::size_t loop = dist / (STEP * 2);
					std::size_t remain = dist % (STEP * 2);
					for (std::size_t i = 0; i < loop; ++i) {
						last -= STEP;
						__m256i * const mpf = reinterpret_cast<__m256i *>(first);
						__m256i * const mpl = reinterpret_cast<__m256i *>(last);
						__m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						__m256i ymm_l = _mm256_loadu_si256(mpl); // AVX
						ymm_f = _mm256_permute4x64_epi64(ymm_f, REV_MASK); // AVX2
						ymm_l = _mm256_permute4x64_epi64(ymm_l, REV_MASK); // AVX2
						_mm256_storeu_si256(mpf , ymm_l); // AVX
						_mm256_storeu_si256(mpl , ymm_f); // AVX
						first += STEP;
					}
					if (remain >= STEP) {
						last -= STEP;
						__m256i * const mpf = reinterpret_cast<__m256i *>(first);
						__m256i * const mpl = reinterpret_cast<__m256i *>(last);
						__m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						__m256i ymm_l = _mm256_loadu_si256(mpl); // AVX
						ymm_f = _mm256_permute4x64_epi64(ymm_f, REV_MASK); // AVX2
						ymm_l = _mm256_permute4x64_epi64(ymm_l, REV_MASK); // AVX2
						_mm256_storeu_si256(mpf , ymm_l); // AVX
						_mm256_storeu_si256(mpl , ymm_f); // AVX
					} else {
						// __m256i * const mpf = reinterpret_cast<__m256i *>(first);
						// __m256i ymm_f = _mm256_loadu_si256(mpf); // AVX
						// ymm_f = _mm256_permutevar8x32_epi32(ymm_f, permute_mask); // AVX2
						// _mm256_storeu_si256(mpf , ymm_f); // AVX
						for (std::size_t i = 0; i < remain / 2; ++i) {
							--last;
							kerbal::algorithm::iter_swap(first, last);
							++first;
						}
					}
				}

			} // namespace avx2

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_AVX2_HPP
