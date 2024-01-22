/**
 * @file       iterator.hpp
 * @brief
 * @date       2018-9-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_ITERATOR_HPP
#define KERBAL_ITERATOR_ITERATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>


namespace kerbal
{

	namespace iterator
	{

		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type
			distance_impl(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				difference_type d(0);
				while (first != last) {
					++first;
					++d;
				}
				return d;
			}

			template <typename RandomAccessIterator>
			KERBAL_CONSTEXPR
			typename kerbal::iterator::iterator_traits<RandomAccessIterator>::difference_type
			distance_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<typename kerbal::iterator::iterator_traits<RandomAccessIterator>::difference_type>(last - first))
					)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				return static_cast<difference_type>(last - first);
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR
		typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type
		distance(ForwardIterator first, ForwardIterator last)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(kerbal::iterator::detail::distance_impl(first, last, kerbal::iterator::iterator_category(first)))
				)
		{
			return kerbal::iterator::detail::distance_impl(first, last, kerbal::iterator::iterator_category(first));
		}



		namespace detail
		{

			template <typename ForwardIterator, typename Distance>
			KERBAL_CONSTEXPR14
			void advance_impl(ForwardIterator & it, Distance dist, std::forward_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(dist != 0)) &&
						noexcept(--dist) &&
						noexcept(++it)
					)
			{
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Distance>::value,
									"Distance must be unsigned type");
				while (dist != 0) {
					--dist;
					++it;
				}
			}

			template <typename BidirectionalIterator, typename Distance>
			KERBAL_CONSTEXPR14
			void advance_impl(BidirectionalIterator & it, Distance dist, std::bidirectional_iterator_tag, kerbal::type_traits::false_type)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(dist < 0)) &&
						noexcept(dist = -dist) &&
						noexcept(static_cast<bool>(dist != 0)) &&
						noexcept(--dist) &&
						noexcept(--it) &&
						noexcept(++it)
					)
			{
				if (dist < 0) {
					dist = -dist;
					while (dist != 0) {
						--dist;
						--it;
					}
				} else {
					while (dist != 0) {
						--dist;
						++it;
					}
				}
			}

			template <typename BidirectionalIterator, typename Distance>
			KERBAL_CONSTEXPR14
			void advance_impl(BidirectionalIterator & it, Distance dist, std::bidirectional_iterator_tag, kerbal::type_traits::true_type)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::iterator::detail::advance_impl(it, dist, std::forward_iterator_tag()))
					)
			{
				kerbal::iterator::detail::advance_impl(it, dist, std::forward_iterator_tag());
			}

			template <typename BidirectionalIterator, typename Distance>
			KERBAL_CONSTEXPR14
			void advance_impl(BidirectionalIterator & it, Distance dist, std::bidirectional_iterator_tag tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::iterator::detail::advance_impl(it, dist, tag, kerbal::type_traits::is_unsigned<Distance>()))
					)
			{
				kerbal::iterator::detail::advance_impl(it, dist, tag, kerbal::type_traits::is_unsigned<Distance>());
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR14
			void advance_impl(RandomAccessIterator & it, Distance dist, std::random_access_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(it += dist)
					)
			{
				it += dist;
			}

		} // namespace detail

		template <typename ForwardIterator, typename Distance>
		KERBAL_CONSTEXPR14
		void advance(ForwardIterator & it, Distance dist)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(kerbal::iterator::detail::advance_impl(it, dist, kerbal::iterator::iterator_category(it)))
				)
		{
			kerbal::iterator::detail::advance_impl(it, dist, kerbal::iterator::iterator_category(it));
		}



		namespace detail
		{

			template <typename BidirectionalIterator, typename Distance>
			KERBAL_CONSTEXPR14
			BidirectionalIterator prev_impl(BidirectionalIterator it, Distance dist, std::bidirectional_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::iterator::advance(it, -dist))
					)
			{
				kerbal::iterator::advance(it, -dist);
				return it;
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR
			RandomAccessIterator prev_impl(RandomAccessIterator it, Distance dist, std::random_access_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(it - dist)
					)
			{
				return it - dist;
			}

		} // namespace detail

		template <typename BidirectionalIterator, typename Distance>
		KERBAL_CONSTEXPR
		BidirectionalIterator prev(BidirectionalIterator it, Distance dist)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(kerbal::iterator::detail::prev_impl(it, dist, kerbal::iterator::iterator_category(it)))
				)
		{
			return kerbal::iterator::detail::prev_impl(it, dist, kerbal::iterator::iterator_category(it));
		}



		namespace detail
		{

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			BidirectionalIterator prev_impl(BidirectionalIterator it, std::bidirectional_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(--it)
					)
			{
				--it;
				return it;
			}

			template <typename RandomAccessIterator>
			KERBAL_CONSTEXPR
			RandomAccessIterator prev_impl(RandomAccessIterator it, std::random_access_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(it - 1)
					)
			{
				return it - 1;
			}

		} // namespace detail

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR
		BidirectionalIterator prev(BidirectionalIterator it)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(kerbal::iterator::detail::prev_impl(it, kerbal::iterator::iterator_category(it)))
				)
		{
			return kerbal::iterator::detail::prev_impl(it, kerbal::iterator::iterator_category(it));
		}



		namespace detail
		{

			template <typename InputIterator, typename Distance>
			KERBAL_CONSTEXPR14
			InputIterator next_impl(InputIterator it, Distance dist, std::input_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::iterator::advance(it, dist))
					)
			{
				kerbal::iterator::advance(it, dist);
				return it;
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR
			RandomAccessIterator next_impl(RandomAccessIterator it, Distance dist, std::random_access_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(it + dist)
					)
			{
				return it + dist;
			}

		} // namespace detail

		template <typename InputIterator, typename Distance>
		KERBAL_CONSTEXPR
		InputIterator next(InputIterator it, Distance dist)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(kerbal::iterator::detail::next_impl(it, dist, kerbal::iterator::iterator_category(it)))
				)
		{
			return kerbal::iterator::detail::next_impl(it, dist, kerbal::iterator::iterator_category(it));
		}



		namespace detail
		{

			template <typename InputIterator>
			KERBAL_CONSTEXPR14
			InputIterator next_impl(InputIterator it, std::input_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(++it)
					)
			{
				++it;
				return it;
			}

			template <typename RandomAccessIterator>
			KERBAL_CONSTEXPR
			RandomAccessIterator next_impl(RandomAccessIterator it, std::random_access_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(it + 1)
					)
			{
				return it + 1;
			}

		} // namespace detail

		template <typename InputIterator>
		KERBAL_CONSTEXPR
		InputIterator next(InputIterator it)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(kerbal::iterator::detail::next_impl(it, kerbal::iterator::iterator_category(it)))
				)
		{
			return kerbal::iterator::detail::next_impl(it, kerbal::iterator::iterator_category(it));
		}



		namespace detail
		{

			template <typename InputIterator, typename Distance>
			KERBAL_CONSTEXPR14
			Distance advance_at_most_impl(InputIterator & it, Distance dist, InputIterator last,
					std::input_iterator_tag)
			{
				Distance d(0);
				while (static_cast<bool>(d < dist) && static_cast<bool>(it != last)) {
					++it;
					++d;
				}
				return d;
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR14
			Distance advance_at_most_impl(RandomAccessIterator & it, Distance dist, RandomAccessIterator last,
					std::random_access_iterator_tag)
			{
				Distance most_dist(kerbal::iterator::distance(it, last));
				if (dist < most_dist) {
					it += dist;
				} else {
					it = last;
					dist = most_dist;
				}
				return dist;
			}

		} // namespace detail

		template <typename InputIterator, typename Distance>
		KERBAL_CONSTEXPR14
		Distance advance_at_most(InputIterator & it, Distance dist, InputIterator last)
		{
			return kerbal::iterator::detail::advance_at_most_impl(it, dist, last, kerbal::iterator::iterator_category(it));
		}



		namespace detail
		{

			template <typename ForwardIterator, typename Distance>
			KERBAL_CONSTEXPR14
			ForwardIterator next_at_most_impl(ForwardIterator it, Distance dist, ForwardIterator last, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				difference_type d(0);
				while (static_cast<bool>(d < dist) && static_cast<bool>(it != last)) {
					++it;
					++d;
				}
				return it;
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR
			RandomAccessIterator next_at_most_impl(RandomAccessIterator it, Distance dist, RandomAccessIterator last, std::random_access_iterator_tag)
			{
				return dist < kerbal::iterator::distance(it, last) ? it + dist : last;
			}

		} // namespace detail

		template <typename ForwardIterator, typename Distance>
		KERBAL_CONSTEXPR
		ForwardIterator next_at_most(ForwardIterator it, Distance dist, ForwardIterator last)
		{
			return kerbal::iterator::detail::next_at_most_impl(it, dist, last, kerbal::iterator::iterator_category(it));
		}



		namespace detail
		{

			template <typename BidirectionalIterator, typename Distance>
			KERBAL_CONSTEXPR14
			Distance retreat_at_most_impl(BidirectionalIterator & it, Distance dist, BidirectionalIterator first,
					std::bidirectional_iterator_tag)
			{
				Distance d(0);
				while (static_cast<bool>(d < dist) && static_cast<bool>(it != first)) {
					--it;
					++d;
				}
				return d;
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR14
			Distance retreat_at_most_impl(RandomAccessIterator & it, Distance dist, RandomAccessIterator first,
					std::random_access_iterator_tag)
			{
				Distance most_dist(kerbal::iterator::distance(first, it));
				if (dist < most_dist) {
					it -= dist;
				} else {
					it = first;
					dist = most_dist;
				}
				return dist;
			}

		} // namespace detail

		template <typename BidirectionalIterator, typename Distance>
		KERBAL_CONSTEXPR14
		Distance retreat_at_most(BidirectionalIterator & it, Distance dist, BidirectionalIterator first)
		{
			return kerbal::iterator::detail::retreat_at_most_impl(it, dist, first, kerbal::iterator::iterator_category(it));
		}



		namespace detail
		{

			template <typename BidirectionalIterator, typename Distance>
			KERBAL_CONSTEXPR14
			BidirectionalIterator prev_at_most_impl(BidirectionalIterator it, Distance dist, BidirectionalIterator first,
					std::bidirectional_iterator_tag)
			{
				typedef BidirectionalIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				difference_type d(0);
				while (static_cast<bool>(d < dist) && static_cast<bool>(it != first)) {
					--it;
					++d;
				}
				return it;
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR
			RandomAccessIterator prev_at_most_impl(RandomAccessIterator it, Distance dist, RandomAccessIterator first,
					std::random_access_iterator_tag)
			{
				return dist < kerbal::iterator::distance(first, it) ? it - dist : first;
			}

		} // namespace detail

		template <typename BidirectionalIterator, typename Distance>
		KERBAL_CONSTEXPR
		BidirectionalIterator prev_at_most(BidirectionalIterator it, Distance dist, BidirectionalIterator first)
		{
			return kerbal::iterator::detail::prev_at_most_impl(it, dist, first, kerbal::iterator::iterator_category(it));
		}



		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator
			midden_iterator_impl(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				iterator forward_it(first);
				while (forward_it != last) {
					++forward_it;
					if (forward_it != last) {
						++forward_it;
						++first;
					} else {
						break;
					}
				}
				return first;
			}

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			BidirectionalIterator
			midden_iterator_impl(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag)
			{
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
			KERBAL_CONSTEXPR
			RandomAccessIterator
			midden_iterator_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
			{
				return first + (last - first) / 2;
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR
		ForwardIterator
		midden_iterator(ForwardIterator first, ForwardIterator last)
		{
			return kerbal::iterator::detail::midden_iterator_impl(first, last, kerbal::iterator::iterator_category(first));
		}



		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			std::pair<ForwardIterator, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type>
			midden_iterator_with_distance_impl(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				iterator forward_it(first);
				difference_type dist(0);
				while (forward_it != last) {
					++forward_it;
					++dist;
					if (forward_it != last) {
						++forward_it;
						++dist;
						++first;
					} else {
						break;
					}
				}
				return std::make_pair(first, dist);
			}

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			std::pair<BidirectionalIterator, typename kerbal::iterator::iterator_traits<BidirectionalIterator>::difference_type>
			midden_iterator_with_distance_impl(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag)
			{
				typedef BidirectionalIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

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
			KERBAL_CONSTEXPR14
			std::pair<RandomAccessIterator, typename kerbal::iterator::iterator_traits<RandomAccessIterator>::difference_type>
			midden_iterator_with_distance_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				difference_type dist(last - first);
				return std::make_pair(first + dist / 2, dist);
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, typename kerbal::iterator::iterator_traits<ForwardIterator>::difference_type>
		midden_iterator_with_distance(ForwardIterator first, ForwardIterator last)
		{
			return kerbal::iterator::detail::midden_iterator_with_distance_impl(first, last, kerbal::iterator::iterator_category(first));
		}



		namespace detail
		{

			template <typename ForwardIterator, typename Distance>
			KERBAL_CONSTEXPR14
			bool distance_less_than_impl(ForwardIterator first, ForwardIterator last, Distance dist, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				difference_type d(0);
				while (static_cast<bool>(first != last) && static_cast<bool>(d < dist)) {
					++first;
					++d;
				}
				return static_cast<bool>(d < dist);
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR
			bool distance_less_than_impl(RandomAccessIterator first, RandomAccessIterator last, Distance dist, std::random_access_iterator_tag)
			{
				return static_cast<bool>(kerbal::iterator::distance(first, last) < dist);
			}

		} // namespace detail

		template <typename ForwardIterator, typename Distance>
		KERBAL_CONSTEXPR
		bool distance_less_than(ForwardIterator first, ForwardIterator last, Distance dist)
		{
			return kerbal::iterator::detail::distance_less_than_impl(first, last, dist, kerbal::iterator::iterator_category(first));
		}



		namespace detail
		{

			template <typename ForwardIterator, typename Distance>
			KERBAL_CONSTEXPR14
			bool distance_equal_to_impl(ForwardIterator first, ForwardIterator last, Distance dist, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				difference_type d(0);
				while (static_cast<bool>(first != last) && static_cast<bool>(d < dist)) {
					++first;
					++d;
				}
				return static_cast<bool>(first == last) && static_cast<bool>(d == dist);
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR
			bool distance_equal_to_impl(RandomAccessIterator first, RandomAccessIterator last, Distance dist, std::random_access_iterator_tag)
			{
				return static_cast<bool>(kerbal::iterator::distance(first, last) == dist);
			}

		} // namespace detail

		template <typename ForwardIterator, typename Distance>
		KERBAL_CONSTEXPR
		bool distance_equal_to(ForwardIterator first, ForwardIterator last, Distance dist)
		{
			return kerbal::iterator::detail::distance_equal_to_impl(first, last, dist, kerbal::iterator::iterator_category(first));
		}



		namespace detail
		{

			template <typename ForwardIterator, typename Distance>
			KERBAL_CONSTEXPR14
			bool distance_greater_than_impl(ForwardIterator first, ForwardIterator last, Distance dist, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
				difference_type d(0);
				while (static_cast<bool>(first != last) && static_cast<bool>(d < dist)) {
					++first;
					++d;
				}
				return static_cast<bool>(first != last) && static_cast<bool>(d == dist);
			}

			template <typename RandomAccessIterator, typename Distance>
			KERBAL_CONSTEXPR
			bool distance_greater_than_impl(RandomAccessIterator first, RandomAccessIterator last, Distance dist, std::random_access_iterator_tag)
			{
				return static_cast<bool>(kerbal::iterator::distance(first, last) > dist);
			}

		} // namespace detail

		template <typename ForwardIterator, typename Distance>
		KERBAL_CONSTEXPR
		bool distance_greater_than(ForwardIterator first, ForwardIterator last, Distance dist)
		{
			return kerbal::iterator::detail::distance_greater_than_impl(first, last, dist, kerbal::iterator::iterator_category(first));
		}

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_ITERATOR_HPP
