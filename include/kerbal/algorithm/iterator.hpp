/**
 * @file		iterator.hpp
 * @brief
 * @date		2018年9月17日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_ALGORITHM_ITERATOR_HPP_
#define INCLUDE_KERBAL_ALGORITHM_ITERATOR_HPP_

#include <kerbal/type_traits/iterator_traits.hpp>

namespace kerbal
{
	namespace algorithm
	{

		template <typename BidirectionalCompatibleIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_birectional_compatible_iterator<BidirectionalCompatibleIterator>::value,
		BidirectionalCompatibleIterator>::type prev(BidirectionalCompatibleIterator it, Distance dist)
		{
			std::advance(it, -dist);
			return it;
		}

		template <typename InputCompatibleIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value,
		InputCompatibleIterator>::type next(InputCompatibleIterator it, Distance dist)
		{
			std::advance(it, dist);
			return it;
		}

		template <typename BidirectionalCompatibleIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_birectional_compatible_iterator<BidirectionalCompatibleIterator>::value,
		BidirectionalCompatibleIterator>::type prev(BidirectionalCompatibleIterator it)
		{
			std::advance(it, -1);
			return it;
		}

		template <typename InputCompatibleIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value,
		InputCompatibleIterator>::type next(InputCompatibleIterator it)
		{
			std::advance(it, 1);
			return it;
		}

		template <typename InputButNotRandomAccessCompatibleIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_input_compatible_iterator<InputButNotRandomAccessCompatibleIterator>::value
				&&
				!kerbal::type_traits::is_random_access_compatible_iterator<InputButNotRandomAccessCompatibleIterator>::value,
		typename std::iterator_traits<InputButNotRandomAccessCompatibleIterator>::difference_type>::type
		advance_at_most(InputButNotRandomAccessCompatibleIterator & it, Distance dist, InputButNotRandomAccessCompatibleIterator end)
		{
			typedef typename std::iterator_traits<InputButNotRandomAccessCompatibleIterator>::difference_type difference_type;
			difference_type i = 0;
			while (i < dist && it != end) {
				++it;
				++i;
			}
			return i;
		}

		template <typename RandomAccessIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_random_access_iterator<RandomAccessIterator>::value,
		typename std::iterator_traits<RandomAccessIterator>::difference_type>::type
		advance_at_most(RandomAccessIterator & it, Distance dist, RandomAccessIterator end)
		{
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			difference_type __d = dist;
			difference_type most_dist = std::distance(it, end);
			if (__d < most_dist) {
				it += __d;
			} else {
				it = end;
				__d = most_dist;
			}
			return __d;
		}

		template <typename InputCompatibleIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value,
		InputCompatibleIterator>::type next_at_most(InputCompatibleIterator it, Distance dist, InputCompatibleIterator end)
		{
			advance_at_most(it, dist, end);
			return it;
		}

		template <typename BidirectionalIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_bidirectional_iterator<BidirectionalIterator>::value,
		typename std::iterator_traits<BidirectionalIterator>::difference_type>::type
		retreat_at_most(BidirectionalIterator & it, Distance dist, BidirectionalIterator begin)
		{
			typedef typename std::iterator_traits<BidirectionalIterator>::difference_type difference_type;
			difference_type i = 0;
			while (i < dist && it != begin) {
				--it;
				++i;
			}
			return i;
		}

		template <typename RandomAccessIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_random_access_iterator<RandomAccessIterator>::value,
		typename std::iterator_traits<RandomAccessIterator>::difference_type>::type
		retreat_at_most(RandomAccessIterator & it, Distance dist, RandomAccessIterator begin)
		{
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			difference_type __d = dist;
			difference_type most_dist = std::distance(begin, it);
			if (__d < most_dist) {
				it -= __d;
			} else {
				it = begin;
				__d = most_dist;
			}
			return __d;
		}

		template <typename BidirectionalCompatibleIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_birectional_compatible_iterator<BidirectionalCompatibleIterator>::value,
		BidirectionalCompatibleIterator>::type prev_at_most(BidirectionalCompatibleIterator it, Distance dist, BidirectionalCompatibleIterator begin)
		{
			retreat_at_most(it, dist, begin);
			return it;
		}

		template <typename ForwardIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_iterator<ForwardIterator>::value,
		ForwardIterator>::type
		midden_iterator(ForwardIterator begin, ForwardIterator end)
		{
			typedef ForwardIterator iterator;
			iterator forward_it = begin;
			while (forward_it != end) {
				++forward_it;
				if (forward_it != end) {
					++forward_it;
					++begin;
				}
			}
			return begin;
		}

		template <typename ForwardIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_iterator<ForwardIterator>::value,
		std::pair<ForwardIterator, typename std::iterator_traits<ForwardIterator>::difference_type> >::type
		midden_iterator_with_distance(ForwardIterator begin, ForwardIterator end)
		{
			typedef ForwardIterator iterator;
			iterator forward_it = begin;
			typename std::iterator_traits<iterator>::difference_type dist(0);
			while (forward_it != end) {
				++forward_it;
				++dist;
				if (forward_it != end) {
					++forward_it;
					++dist;
					++begin;
				}
			}
			return std::make_pair(begin, dist);
		}

		template <typename BidirectionalIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_bidirectional_iterator<BidirectionalIterator>::value,
		BidirectionalIterator>::type
		midden_iterator(BidirectionalIterator begin, BidirectionalIterator end)
		{
			typedef BidirectionalIterator iterator;
			while (begin != end) {
				--end;
				if (begin != end) {
					++begin;
				} else {
					break;
				}
			}
			return begin;
		}

		template <typename BidirectionalIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_bidirectional_iterator<BidirectionalIterator>::value,
		std::pair<BidirectionalIterator, typename std::iterator_traits<BidirectionalIterator>::difference_type> >::type
		midden_iterator_with_distance(BidirectionalIterator begin, BidirectionalIterator end)
		{
			typedef BidirectionalIterator iterator;
			typename std::iterator_traits<iterator>::difference_type dist(0);
			while (begin != end) {
				--end;
				++dist;
				if (begin != end) {
					++begin;
					++dist;
				} else {
					break;
				}
			}
			return std::make_pair(begin, dist);
		}

		template <typename RandomAccessIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_random_access_iterator<RandomAccessIterator>::value,
		RandomAccessIterator>::type
		midden_iterator(RandomAccessIterator begin, RandomAccessIterator end)
		{
			typedef RandomAccessIterator iterator;
			typename std::iterator_traits<iterator>::difference_type dist(end - begin);
			return begin + dist / 2;
		}

		template <typename RandomAccessIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_random_access_iterator<RandomAccessIterator>::value,
		std::pair<RandomAccessIterator, typename std::iterator_traits<RandomAccessIterator>::difference_type> >::type
		midden_iterator_with_distance(RandomAccessIterator begin, RandomAccessIterator end)
		{
			typedef RandomAccessIterator iterator;
			typename std::iterator_traits<iterator>::difference_type dist(end - begin);
			return std::make_pair(begin + dist / 2, dist);
		}

		template <typename BidirectionalButNotRandomAccessCompatibleIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_birectional_compatible_iterator<BidirectionalButNotRandomAccessCompatibleIterator>::value
				&&
				!kerbal::type_traits::is_random_access_compatible_iterator<BidirectionalButNotRandomAccessCompatibleIterator>::value,
		bool>::type distance_is_less_than(BidirectionalButNotRandomAccessCompatibleIterator begin, BidirectionalButNotRandomAccessCompatibleIterator end, Distance dist)
		{
			typedef BidirectionalButNotRandomAccessCompatibleIterator iterator;
			typename std::iterator_traits<iterator>::difference_type __n(0);
			while (begin != end && static_cast<bool>(__n < dist)) {
				++begin;
				++__n;
			}
			return static_cast<bool>(__n < dist);
		}

		template <typename RandomAccessIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_random_access_iterator<RandomAccessIterator>::value,
		bool>::type distance_is_less_than(RandomAccessIterator begin, RandomAccessIterator end, Distance dist)
		{
			return std::distance(begin, end) < dist;
		}

	}
}

#endif /* INCLUDE_KERBAL_ALGORITHM_ITERATOR_HPP_ */
