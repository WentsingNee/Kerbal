/**
 * @file       reverse.ssse3.hpp
 * @brief
 * @date       2024-02-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_SSSE3_HPP
#define KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_SSSE3_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <cstddef>

#include <emmintrin.h>
#include <tmmintrin.h>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			namespace ssse3
			{

				inline
				void reverse(kerbal::compatibility::uint8_t * first, kerbal::compatibility::uint8_t * last) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint8_t * iterator;
					typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last));
					std::size_t const STEP = sizeof(__m128i) / sizeof(value_type);
					__m128i const REV_MASK = _mm_setr_epi8(
						15, 14, 13, 12, 11, 10,  9,  8,
						 7,  6,  5,  4,  3,  2,  1,  0
					); // SSE2

					std::size_t loop = dist / (STEP * 2);
					std::size_t remain = dist % (STEP * 2);
					for (std::size_t i = 0; i < loop; ++i) {
						last -= STEP;
						__m128i * const mpf = reinterpret_cast<__m128i *>(first);
						__m128i * const mpl = reinterpret_cast<__m128i *>(last);
						__m128i xmm_f = _mm_loadu_si128(mpf); // SSE2
						__m128i xmm_l = _mm_loadu_si128(mpl); // SSE2
						xmm_f = _mm_shuffle_epi8(xmm_f, REV_MASK); // SSSE3
						xmm_l = _mm_shuffle_epi8(xmm_l, REV_MASK); // SSSE3
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

				inline
				void reverse(kerbal::compatibility::uint16_t * first, kerbal::compatibility::uint16_t * last) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint16_t * iterator;
					typedef kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last));
					std::size_t const STEP = sizeof(__m128i) / sizeof(value_type);
					__m128i const REV_MASK = _mm_setr_epi8(
						14, 15, 12, 13, 10, 11,  8,  9,
						 6,  7,  4,  5,  2,  3,  0,  1
					); // SSE2

					std::size_t loop = dist / (STEP * 2);
					std::size_t remain = dist % (STEP * 2);
					for (std::size_t i = 0; i < loop; ++i) {
						last -= STEP;
						__m128i * const mpf = reinterpret_cast<__m128i *>(first);
						__m128i * const mpl = reinterpret_cast<__m128i *>(last);
						__m128i xmm_f = _mm_loadu_si128(mpf); // SSE2
						__m128i xmm_l = _mm_loadu_si128(mpl); // SSE2
						xmm_f = _mm_shuffle_epi8(xmm_f, REV_MASK); // SSSE3
						xmm_l = _mm_shuffle_epi8(xmm_l, REV_MASK); // SSSE3
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

			} // namespace ssse3

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_SSSE3_HPP
