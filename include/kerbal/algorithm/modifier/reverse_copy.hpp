/**
 * @file       reverse_copy.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_REVERSE_COPY_HPP
#define KERBAL_ALGORITHM_MODIFIER_REVERSE_COPY_HPP

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename BidirectionalIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			OutputIterator
			k_reverse_copy(
				BidirectionalIterator first, BidirectionalIterator last, OutputIterator to,
				std::bidirectional_iterator_tag
			)
			{
				while (first != last) {
					--last;
					kerbal::assign::generic_assign(*to, *last); // *to = *last;
					++to;
				}
				return to;
			}

			template <typename RandomAccessIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			OutputIterator
			k_reverse_copy(
				RandomAccessIterator first, RandomAccessIterator last, OutputIterator to,
				std::random_access_iterator_tag
			)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#		define EACH() do { \
					--last; \
					kerbal::assign::generic_assign(*to, *last); /*  *to = *last; */ \
					++to; \
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

				return to;
			}

		} // namespace detail

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to)
		{
			return kerbal::algorithm::detail::k_reverse_copy(
				first, last, to,
				kerbal::iterator::iterator_category(first)
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_REVERSE_COPY_HPP
