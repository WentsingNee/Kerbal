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

		template <typename BidirectionalIterator, typename Distance>
		BidirectionalIterator prev(BidirectionalIterator it, Distance dist)
		{
			std::advance(it, -dist);
			return it;
		}

		template <typename BidirectionalIterator>
		BidirectionalIterator prev(BidirectionalIterator it)
		{
			std::advance(it, -1);
			return it;
		}

		template <typename InputIterator, typename Distance>
		InputIterator next(InputIterator it, Distance dist)
		{
			std::advance(it, dist);
			return it;
		}

		template <typename InputIterator>
		InputIterator next(InputIterator it)
		{
			std::advance(it, 1);
			return it;
		}

		template <typename InputIterator, typename Distance>
		typename std::iterator_traits<InputIterator>::difference_type
		__advance_at_most(InputIterator & it, Distance dist, InputIterator last,
				std::input_iterator_tag)
		{
			typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;
			difference_type i(0);
			while (static_cast<bool>(i < dist) && static_cast<bool>(it != last)) {
				++it;
				++i;
			}
			return i;
		}

		template <typename RandomAccessIterator, typename Distance>
		typename std::iterator_traits<RandomAccessIterator>::difference_type
		__advance_at_most(RandomAccessIterator & it, Distance dist, RandomAccessIterator last,
				std::random_access_iterator_tag)
		{
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			difference_type __d(dist);
			difference_type most_dist(std::distance(it, last));
			if (__d < most_dist) {
				it += __d;
			} else {
				it = last;
				__d = most_dist;
			}
			return __d;
		}

		template <typename InputIterator, typename Distance>
		typename std::iterator_traits<InputIterator>::difference_type
		advance_at_most(InputIterator & it, Distance dist, InputIterator last)
		{
			return __advance_at_most(it, dist, last, kerbal::type_traits::iterator_category(it));
		}

		template <typename InputIterator, typename Distance>
		InputIterator next_at_most(InputIterator it, Distance dist, InputIterator last)
		{
			advance_at_most(it, dist, last);
			return it;
		}

		template <typename BidirectionalIterator, typename Distance>
		typename std::iterator_traits<BidirectionalIterator>::difference_type
		__retreat_at_most(BidirectionalIterator & it, Distance dist, BidirectionalIterator first,
				std::bidirectional_iterator_tag)
		{
			typedef typename std::iterator_traits<BidirectionalIterator>::difference_type difference_type;
			difference_type i(0);
			while (static_cast<bool>(i < dist) && static_cast<bool>(it != first)) {
				--it;
				++i;
			}
			return i;
		}

		template <typename RandomAccessIterator, typename Distance>
		typename std::iterator_traits<RandomAccessIterator>::difference_type
		__retreat_at_most(RandomAccessIterator & it, Distance dist, RandomAccessIterator first,
				std::random_access_iterator_tag)
		{
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			difference_type __d(dist);
			difference_type most_dist(std::distance(first, it));
			if (__d < most_dist) {
				it -= __d;
			} else {
				it = first;
				__d = most_dist;
			}
			return __d;
		}

		template <typename BidirectionalIterator, typename Distance>
		typename std::iterator_traits<BidirectionalIterator>::difference_type
		retreat_at_most(BidirectionalIterator & it, Distance dist, BidirectionalIterator first)
		{
			return __retreat_at_most(it, dist, first, kerbal::type_traits::iterator_category(it));
		}

		template <typename BidirectionalIterator, typename Distance>
		BidirectionalIterator prev_at_most(BidirectionalIterator it, Distance dist, BidirectionalIterator first)
		{
			retreat_at_most(it, dist, first);
			return it;
		}

		template <typename ForwardIterator>
		ForwardIterator
		__midden_iterator(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;
			iterator forward_it = first;
			while (forward_it != last) {
				++forward_it;
				if (forward_it != last) {
					++forward_it;
					++first;
				}
			}
			return first;
		}

		template <typename BidirectionalIterator>
		BidirectionalIterator
		__midden_iterator(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag)
		{
			typedef BidirectionalIterator iterator;
			while (first != last) {
				--last;
				if (first != last) {
					++first;
				} else {
					break;
				}
			}
			return first;
		}

		template <typename RandomAccessIterator>
		RandomAccessIterator
		__midden_iterator(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;
			difference_type dist(last - first);
			return first + dist / 2;
		}

		template <typename ForwardIterator>
		ForwardIterator
		midden_iterator(ForwardIterator first, ForwardIterator last)
		{
			return __midden_iterator(first, last, kerbal::type_traits::iterator_category(first));
		}

		template <typename ForwardIterator>
		std::pair<ForwardIterator, typename std::iterator_traits<ForwardIterator>::difference_type>
		__midden_iterator_with_distance(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;

			iterator forward_it = first;
			difference_type dist(0);
			while (forward_it != last) {
				++forward_it;
				++dist;
				if (forward_it != last) {
					++forward_it;
					++dist;
					++first;
				}
			}
			return std::make_pair(first, dist);
		}

		template <typename BidirectionalIterator>
		std::pair<BidirectionalIterator, typename std::iterator_traits<BidirectionalIterator>::difference_type>
		__midden_iterator_with_distance(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag)
		{
			typedef BidirectionalIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;

			difference_type dist(0);
			while (first != last) {
				--last;
				++dist;
				if (first != last) {
					++first;
					++dist;
				} else {
					break;
				}
			}
			return std::make_pair(first, dist);
		}

		template <typename RandomAccessIterator>
		std::pair<RandomAccessIterator, typename std::iterator_traits<RandomAccessIterator>::difference_type>
		__midden_iterator_with_distance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;
			difference_type dist(last - first);
			return std::make_pair(first + dist / 2, dist);
		}

		template <typename ForwardIterator>
		std::pair<ForwardIterator, typename std::iterator_traits<ForwardIterator>::difference_type>
		midden_iterator_with_distance(ForwardIterator first, ForwardIterator last)
		{
			return __midden_iterator_with_distance(first, last, kerbal::type_traits::iterator_category(first));
		}

		template <typename ForwardIterator, typename Distance>
		bool __distance_is_less_than(ForwardIterator first, ForwardIterator last, Distance dist, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;
			difference_type __n(0);
			while (static_cast<bool>(first != last) && static_cast<bool>(__n < dist)) {
				++first;
				++__n;
			}
			return static_cast<bool>(__n < dist);
		}

		template <typename RandomAccessIterator, typename Distance>
		bool __distance_is_less_than(RandomAccessIterator first, RandomAccessIterator last, Distance dist, std::random_access_iterator_tag)
		{
			return static_cast<bool>(std::distance(first, last) < dist);
		}

		template <typename ForwardIterator, typename Distance>
		bool distance_is_less_than(ForwardIterator first, ForwardIterator last, Distance dist)
		{
			return __distance_is_less_than(first, last, dist, kerbal::type_traits::iterator_category(first));
		}

	}
}

#endif /* INCLUDE_KERBAL_ALGORITHM_ITERATOR_HPP_ */
