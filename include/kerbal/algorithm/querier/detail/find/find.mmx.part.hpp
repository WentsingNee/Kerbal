/**
 * @file       find.mmx.part.hpp
 * @brief
 * @date       2021-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_MMX_PART_HPP
#define KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_MMX_PART_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <kerbal/algorithm/querier/detail/find/find.plain.part.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			namespace mmx
			{

				inline
				const kerbal::compatibility::int8_t *
				find(
					const kerbal::compatibility::int8_t * first,
					const kerbal::compatibility::int8_t * last,
					const kerbal::compatibility::int8_t & x
				) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m64) / sizeof(kerbal::compatibility::int8_t)> STEP;

					__m64 const mx = _mm_set1_pi8(x); // MMX
					__m64 const mALL_ONE = _mm_set1_pi8(~0); // MMX
					std::size_t loop = (last - first) / STEP::value;
					for (std::size_t i = 0; i < loop; ++i) {
						const __m64 * const mpf = reinterpret_cast<const __m64 *>(first);
						__m64 mrf = _mm_loadu_si128(mpf); // SSE2
						mrf = _mm_cmpeq_epi8(mrf, mx); // SSE2

						if (!_mm_test_all_zeros(mrf, mALL_ONE)) { // SSE4.1
							break;
						}
						first += STEP::value;
					}
					return kerbal::algorithm::detail::plain::find(first, last, x);
				}

			} // namespace mmx

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_MMX_PART_HPP
