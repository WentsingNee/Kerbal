/**
 * @file       count.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_COUNT_HPP
#define KERBAL_ALGORITHM_QUERIER_COUNT_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename InputIterator, typename Type>
			KERBAL_CONSTEXPR14
			std::size_t k_count(
				InputIterator first, InputIterator last, const Type & value,
				std::input_iterator_tag
			)
			{
				std::size_t cnt = 0;
				while (first != last) {
					if (*first == value) {
						++cnt;
					}
					++first;
				}
				return cnt;
			}

			template <typename RandomAccessIterator, typename Type>
			KERBAL_CONSTEXPR14
			std::size_t k_count(
				RandomAccessIterator first, RandomAccessIterator last, const Type & value,
				std::random_access_iterator_tag
			)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				std::size_t cnt = 0;

#		define EACH() do { \
					if (*first == value) { \
						++cnt; \
					} \
					++first; \
				} while (false)

				difference_type trip_count(kerbal::iterator::distance(first, last));
				difference_type remain(trip_count & 3);
				for (trip_count >>= 2; trip_count > 0; --trip_count) {
					EACH();
					EACH();
					EACH();
					EACH();
				}

				if (remain >= 2) {
					EACH();
					EACH();
					remain -= 2;
				}
				if (remain >= 1) {
					EACH();
				}

#		undef EACH

				return cnt;
			}

		} // namespace detail

		template <typename InputIterator, typename Type>
		KERBAL_CONSTEXPR14
		std::size_t count(InputIterator first, InputIterator last, const Type & value)
		{
			return kerbal::algorithm::detail::k_count(
				first, last, value,
				kerbal::iterator::iterator_category(first)
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_COUNT_HPP
