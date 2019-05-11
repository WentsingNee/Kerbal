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

#include <iterator>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/is_same.hpp>

namespace kerbal
{
	namespace algorithm
	{

		template <typename Iterator, typename IteratorTag>
		struct iterator_is_type_of: public kerbal::type_traits::conditional_boolean<
				kerbal::type_traits::is_same<
						typename std::iterator_traits<Iterator>::iterator_category,
						IteratorTag
				>::value
		>
		{
		};

		template <typename Iterator, typename IteratorTag>
		struct is_compatible_iterator_type_of;

		template <typename Iterator>
		struct is_compatible_iterator_type_of<Iterator, std::random_access_iterator_tag>: public
			kerbal::type_traits::conditional_boolean<
				kerbal::type_traits::is_same<
					typename std::iterator_traits<Iterator>::iterator_category,
					std::random_access_iterator_tag
				>::value
			>
		{
		};

		template <typename Iterator>
		struct is_compatible_iterator_type_of<Iterator, std::bidirectional_iterator_tag>: public
			kerbal::type_traits::conditional_boolean<
				kerbal::type_traits::is_same<
					typename std::iterator_traits<Iterator>::iterator_category,
					std::bidirectional_iterator_tag
				>::value
					||
				kerbal::algorithm::is_compatible_iterator_type_of<Iterator, std::random_access_iterator_tag>::value
			>
		{
		};

		template <typename Iterator>
		struct is_compatible_iterator_type_of<Iterator, std::forward_iterator_tag>: public
			kerbal::type_traits::conditional_boolean<
				kerbal::type_traits::is_same<
					typename std::iterator_traits<Iterator>::iterator_category,
					std::forward_iterator_tag
				>::value
					||
				kerbal::algorithm::is_compatible_iterator_type_of<Iterator, std::bidirectional_iterator_tag>::value
			>
		{
		};

		template <typename Iterator>
		struct is_compatible_iterator_type_of<Iterator, std::input_iterator_tag>: public
			kerbal::type_traits::conditional_boolean<
				kerbal::type_traits::is_same<
					typename std::iterator_traits<Iterator>::iterator_category,
					std::input_iterator_tag
				>::value
					||
				kerbal::algorithm::is_compatible_iterator_type_of<Iterator, std::forward_iterator_tag>::value
			>
		{
		};

		template <typename BidirectionalIterator, typename Distance>
		BidirectionalIterator prev(BidirectionalIterator it, Distance dist)
		{
			std::advance(it, -dist);
			return it;
		}

		template <typename InputIterator, typename Distance>
		InputIterator next(InputIterator it, Distance dist)
		{
			std::advance(it, dist);
			return it;
		}

		template <typename BidirectionalIterator>
		BidirectionalIterator prev(BidirectionalIterator it)
		{
			std::advance(it, -1);
			return it;
		}

		template <typename InputIterator>
		InputIterator next(InputIterator it)
		{
			std::advance(it, 1);
			return it;
		}

		template <typename InputIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				iterator_is_type_of<InputIterator, std::input_iterator_tag>::value,
				InputIterator>::type
		advance_at_most(InputIterator & it, Distance dist, InputIterator end)
		{
			typename std::iterator_traits<InputIterator>::difference_type __d = dist;
			while (__d-- && it != end) {
				++it;
			}
		}

		template <typename ForwardIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				iterator_is_type_of<ForwardIterator, std::forward_iterator_tag>::value,
				ForwardIterator>::type
		advance_at_most(ForwardIterator & it, Distance dist, ForwardIterator end)
		{
			typename std::iterator_traits<ForwardIterator>::difference_type __d = dist;
			while (__d-- && it != end) {
				++it;
			}
		}

		template <typename BidirectionalIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				iterator_is_type_of<BidirectionalIterator, std::bidirectional_iterator_tag>::value,
				BidirectionalIterator>::type
		advance_at_most(BidirectionalIterator & it, Distance dist, BidirectionalIterator end)
		{
			typename std::iterator_traits<BidirectionalIterator>::difference_type __d = dist;
			while (__d-- && it != end) {
				++it;
			}
		}

		template <typename RandomAccessIterator, typename Distance>
		typename kerbal::type_traits::enable_if<
				iterator_is_type_of<RandomAccessIterator, std::random_access_iterator_tag>::value,
				RandomAccessIterator>::type
		advance_at_most(RandomAccessIterator & it, Distance dist, RandomAccessIterator end)
		{
			typename std::iterator_traits<RandomAccessIterator>::difference_type __d = dist;
			if (__d < std::distance(it, end)) {
				it += __d;
			} else {
				it = end;
			}
		}

		template <typename InputIterator, typename Distance>
		InputIterator next_at_most(InputIterator it, Distance dist, InputIterator end)
		{
			advance_at_most(it, dist, end);
			return it;
		}

		template <typename ForwardIterator>
		typename kerbal::type_traits::enable_if<
				iterator_is_type_of<ForwardIterator, std::forward_iterator_tag>::value,
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
				iterator_is_type_of<ForwardIterator, std::forward_iterator_tag>::value,
				std::pair<ForwardIterator,
						typename std::iterator_traits<ForwardIterator>::difference_type> >::type
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
				iterator_is_type_of<BidirectionalIterator, std::bidirectional_iterator_tag>::value,
				BidirectionalIterator>::type
		midden_iterator(BidirectionalIterator begin, BidirectionalIterator end)
		{
			typedef BidirectionalIterator iterator;
			while (begin != end) {
				--end;
				if (begin != end) {
					++begin;
				} else {
					return begin;
				}
			}
			return begin;
		}

		template <typename BidirectionalIterator>
		typename kerbal::type_traits::enable_if<
				iterator_is_type_of<BidirectionalIterator, std::bidirectional_iterator_tag>::value,
				std::pair<BidirectionalIterator,
						typename std::iterator_traits<BidirectionalIterator>::difference_type> >::type
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
					return std::make_pair(begin, dist);
				}
			}
			return std::make_pair(begin, dist);
		}

		template <typename RandomAccessIterator>
		typename kerbal::type_traits::enable_if<
				iterator_is_type_of<RandomAccessIterator, std::random_access_iterator_tag>::value,
				RandomAccessIterator>::type
		midden_iterator(RandomAccessIterator begin, RandomAccessIterator end)
		{
			typedef RandomAccessIterator iterator;
			return begin + (end - begin) / 2;
		}

		template <typename RandomAccessIterator>
		typename kerbal::type_traits::enable_if<
				iterator_is_type_of<RandomAccessIterator, std::random_access_iterator_tag>::value,
				std::pair<RandomAccessIterator,
						typename std::iterator_traits<RandomAccessIterator>::difference_type> >::type
		midden_iterator_with_distance(RandomAccessIterator begin, RandomAccessIterator end)
		{
			typedef RandomAccessIterator iterator;
			typename std::iterator_traits<iterator>::difference_type dist(end - begin);
			return std::make_pair(begin + dist / 2, dist);
		}

	}
}

#endif /* INCLUDE_KERBAL_ALGORITHM_ITERATOR_HPP_ */
