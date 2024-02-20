/**
 * @file       reverse.sse2.hpp
 * @brief
 * @date       2024-02-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_SSE2_HPP
#define KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_SSE2_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <cstddef>

#include <emmintrin.h>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			namespace sse2
			{

				inline
				__m128i k_reverse_swap_hi_lo(__m128i xmm) KERBAL_NOEXCEPT
				{
					int const REV_MASK = 78; // 0b'01'00'11'10
					return _mm_shuffle_epi32(xmm, REV_MASK); // SSE2
				}

				inline
				__m128i k_reverse_epi8(__m128i xmm) KERBAL_NOEXCEPT
				{
					int const REV_MASK = 27; // 0b'00'01'10'11
					xmm = _mm_shufflelo_epi16(xmm, REV_MASK); // SSE2
					return _mm_shuffle_epi32(xmm, REV_MASK); // SSE2
				}

				inline
				void reverse(kerbal::compatibility::uint8_t * first, kerbal::compatibility::uint8_t * last) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint8_t * iterator;
					typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last));
					std::size_t const STEP = sizeof(__m128i) / 2 / sizeof(value_type);
					int const REV_MASK = 27; // 0b'00'01'10'11

					std::size_t loop = dist / (STEP * 2);
					std::size_t remain = dist % (STEP * 2);
					for (std::size_t i = 0; i < loop; ++i) {
						last -= STEP;
						__m128i * const mpf = reinterpret_cast<__m128i *>(first);
						__m128i * const mpl = reinterpret_cast<__m128i *>(last);
						__m128i xmm_f = _mm_loadu_si64(mpf); // SSE2
						__m128i xmm_l = _mm_loadu_si64(mpl); // SSE2
						xmm_f = _mm_shufflelo_epi16(xmm_f, REV_MASK); // SSE2
						xmm_l = _mm_shufflelo_epi16(xmm_l, REV_MASK); // SSE2
						_mm_storeu_si64(mpf , xmm_l); // SSE2
						_mm_storeu_si64(mpl , xmm_f); // SSE2
						first += STEP;
					}
					for (std::size_t i = 0; i < remain / 2; ++i) {
						--last;
						kerbal::algorithm::iter_swap(first, last);
						++first;
					}
				}

				inline
				void reverse(kerbal::compatibility::uint16_t * first, kerbal::compatibility::uint16_t * last) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint16_t * iterator;
					typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last));
					std::size_t const STEP = sizeof(__m128i) / 2 / sizeof(value_type);
					int const REV_MASK = 27; // 0b'00'01'10'11

					std::size_t loop = dist / (STEP * 2);
					std::size_t remain = dist % (STEP * 2);
					for (std::size_t i = 0; i < loop; ++i) {
						last -= STEP;
						__m128i * const mpf = reinterpret_cast<__m128i *>(first);
						__m128i * const mpl = reinterpret_cast<__m128i *>(last);
						__m128i xmm_f = _mm_loadu_si64(mpf); // SSE2
						__m128i xmm_l = _mm_loadu_si64(mpl); // SSE2
						xmm_f = _mm_shufflelo_epi16(xmm_f, REV_MASK); // SSE2
						xmm_l = _mm_shufflelo_epi16(xmm_l, REV_MASK); // SSE2
						_mm_storeu_si64(mpf , xmm_l); // SSE2
						_mm_storeu_si64(mpl , xmm_f); // SSE2
						first += STEP;
					}
					for (std::size_t i = 0; i < remain / 2; ++i) {
						--last;
						kerbal::algorithm::iter_swap(first, last);
						++first;
					}
				}
				//
				// inline
				// void reverse(kerbal::compatibility::uint16_t * first, kerbal::compatibility::uint16_t * last) KERBAL_NOEXCEPT
				// {
				// 	typedef kerbal::compatibility::uint16_t * iterator;
				// 	typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
				// 	typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				//
				// 	difference_type dist(kerbal::iterator::distance(first, last));
				// 	std::size_t const STEP = sizeof(__m128i) / sizeof(value_type);
				// 	int const REV_MASK = 27; // 0b'00'01'10'11
				//
				// 	std::size_t loop = dist / (STEP * 2);
				// 	std::size_t remain = dist % (STEP * 2);
				// 	for (std::size_t i = 0; i < loop; ++i) {
				// 		last -= STEP;
				// 		__m128i * const mpf = reinterpret_cast<__m128i *>(first);
				// 		__m128i * const mpl = reinterpret_cast<__m128i *>(last);
				// 		__m128i xmm_f = _mm_loadu_si128(mpf); // SSE2
				// 		__m128i xmm_l = _mm_loadu_si128(mpl); // SSE2
				// 		xmm_f = _mm_shufflehi_epi16(xmm_f, REV_MASK); // SSE2
				// 		xmm_f = _mm_shufflelo_epi16(xmm_f, REV_MASK); // SSE2
				// 		xmm_f = k_reverse_swap_hi_lo(xmm_f); // SSE2
				// 		xmm_l = _mm_shufflehi_epi16(xmm_l, REV_MASK); // SSE2
				// 		xmm_l = _mm_shufflelo_epi16(xmm_l, REV_MASK); // SSE2
				// 		xmm_l = k_reverse_swap_hi_lo(xmm_l); // SSE2
				// 		_mm_storeu_si128(mpf , xmm_l); // SSE2
				// 		_mm_storeu_si128(mpl , xmm_f); // SSE2
				// 		first += STEP;
				// 	}
				// 	for (std::size_t i = 0; i < remain / 2; ++i) {
				// 		--last;
				// 		kerbal::algorithm::iter_swap(first, last);
				// 		++first;
				// 	}
				// }

				inline
				void reverse(kerbal::compatibility::uint32_t * first, kerbal::compatibility::uint32_t * last) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t * iterator;
					typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last));
					std::size_t const STEP = sizeof(__m128i) / sizeof(value_type);
					int const REV_MASK = 27; // 0b'00'01'10'11

					std::size_t loop = dist / (STEP * 2);
					std::size_t remain = dist % (STEP * 2);
					for (std::size_t i = 0; i < loop; ++i) {
						last -= STEP;
						__m128i * const mpf = reinterpret_cast<__m128i *>(first);
						__m128i * const mpl = reinterpret_cast<__m128i *>(last);
						__m128i xmm_f = _mm_loadu_si128(mpf); // SSE2
						__m128i xmm_l = _mm_loadu_si128(mpl); // SSE2
						xmm_f = _mm_shuffle_epi32(xmm_f, REV_MASK); // SSE2
						xmm_l = _mm_shuffle_epi32(xmm_l, REV_MASK); // SSE2
						_mm_storeu_si128(mpf , xmm_l); // SSE2
						_mm_storeu_si128(mpl , xmm_f); // SSE2
						first += STEP;
					}
					for (std::size_t i = 0; i < remain / 2; ++i) {
						--last;
						kerbal::algorithm::iter_swap(first, last);
						++first;
					}
				}

			} // namespace sse2

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_SSE2_HPP
