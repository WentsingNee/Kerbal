/**
 * @file       find.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_FIND_HPP
#define KERBAL_ALGORITHM_QUERIER_FIND_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename InputIterator, typename Type>
			KERBAL_CONSTEXPR14
			InputIterator
			k_find(InputIterator first, InputIterator last, const Type & value, std::input_iterator_tag)
			{
				while (first != last) {
					if (*first == value) {
						break;
					}
					++first;
				}
				return first;
			}

			template <typename RandomAccessIterator, typename Type>
			KERBAL_CONSTEXPR14
			RandomAccessIterator
			k_find(RandomAccessIterator first, RandomAccessIterator last, const Type & value, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#		define EACH() do { \
					if (*first == value) { \
						return first; \
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

				return first;
			}

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename InputIterator, typename Type>
		KERBAL_CONSTEXPR14
		InputIterator
		find(InputIterator first, InputIterator last, const Type & value)
		{
			return kerbal::algorithm::detail::k_find(first, last, value, kerbal::iterator::iterator_category(first));
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_FIND_HPP
