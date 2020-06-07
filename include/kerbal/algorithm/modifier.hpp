/**
 * @file       modifier.hpp
 * @brief
 * @date       2019-9-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_HPP
#define KERBAL_ALGORITHM_MODIFIER_HPP

#include <kerbal/algorithm/binary_type_predicate.hpp>
#include <kerbal/algorithm/querier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace algorithm
	{

		template <typename Tp>
		KERBAL_CONSTEXPR14
		void swap(Tp & lhs, Tp & rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(
									std::is_nothrow_move_constructible<Tp>::value &&
									std::is_nothrow_move_assignable<Tp>::value
							)
		{
			Tp t(kerbal::compatibility::to_xvalue(lhs));
			lhs = kerbal::compatibility::to_xvalue(rhs);
			rhs = kerbal::compatibility::to_xvalue(t);
		}

		template <typename ForwardIterator1, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		void iter_swap(ForwardIterator1 lhs, ForwardIterator2 rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::algorithm::swap(*lhs, *rhs))
							)
		{
			kerbal::algorithm::swap(*lhs, *rhs);
		}

		template <typename ForwardIterator1, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		ForwardIterator2
		__range_swap(ForwardIterator1 a_first, ForwardIterator1 a_last, ForwardIterator2 b_first,
						std::forward_iterator_tag)
											KERBAL_CONDITIONAL_NOEXCEPT(
													noexcept(static_cast<bool>(a_first != a_last)) &&
													noexcept(kerbal::algorithm::iter_swap(a_first, b_first)) &&
													noexcept(++a_first) &&
													noexcept(++b_first)
											)
		{
			while (a_first != a_last) {
				kerbal::algorithm::iter_swap(a_first, b_first);
				++a_first;
				++b_first;
			}
			return b_first;
		}

		template <typename RandomAccessIterator1, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		ForwardIterator2
		__range_swap(RandomAccessIterator1 a_first, RandomAccessIterator1 a_last, ForwardIterator2 b_first,
						std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator1 iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				kerbal::algorithm::iter_swap(a_first, b_first);\
				++a_first;\
				++b_first;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(a_first, a_last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}
			difference_type remain(kerbal::iterator::distance(a_first, a_last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return b_first;
		}

		template <typename ForwardIterator1, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		ForwardIterator2
		range_swap(ForwardIterator1 a_first, ForwardIterator1 a_last, ForwardIterator2 b_first)
		{
			return kerbal::algorithm::__range_swap(a_first, a_last, b_first,
									kerbal::iterator::iterator_category(a_first));
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		void
		swap(Tp (&lhs)[N], Tp (&rhs)[N])
		{
			kerbal::algorithm::range_swap(lhs + 0, lhs + N, rhs + 0);
		}



		template <typename InputIterator, typename InputIteratorEnd, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__copy(InputIterator first, InputIteratorEnd last, OutputIterator to,
				std::input_iterator_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												noexcept(static_cast<bool>(first != last)) &&
												noexcept(*to = *first) &&
												noexcept(++to) &&
												noexcept(++first)
										)
		{
			while (first != last) {
				*to = *first;
				++to;
				++first;
			}
			return to;
		}

		template <typename RandomAccessIterator, typename RandomAccessIteratorEnd, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__copy(RandomAccessIterator first, RandomAccessIteratorEnd last, OutputIterator to,
				std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				*to = *first;\
				++to;\
				++first;\
			} while(false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to;
		}

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy(InputIterator first, InputIterator last, OutputIterator to)
		{
			return kerbal::algorithm::__copy(first, last, to, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		__copy_if(InputIterator first, InputIterator last, OutputIterator to,
				UnaryPredicate pred, std::input_iterator_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												noexcept(static_cast<bool>(first != last)) &&
												noexcept(static_cast<bool>(pred(*first))) &&
												noexcept(*to = *first) &&
												noexcept(++to) &&
												noexcept(++first)
										)
		{
			while (first != last) {
				if (pred(*first)) {
					*to = *first;
					++to;
				}
				++first;
			}
			return to;
		}

		template <typename RandomAccessIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		__copy_if(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to,
				UnaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				if (pred(*first)) {\
					*to = *first;\
					++to;\
				}\
				++first;\
			} while(false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to;
		}

		template <typename InputIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_if(InputIterator first, InputIterator last, OutputIterator to, UnaryPredicate pred)
		{
			return kerbal::algorithm::__copy_if(first, last, to, pred, kerbal::iterator::iterator_category(first));
		}



		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__copy_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last,
						std::bidirectional_iterator_tag)
													KERBAL_CONDITIONAL_NOEXCEPT(
															noexcept(static_cast<bool>(first != last)) &&
															noexcept(--last) &&
															noexcept(--to_last) &&
															noexcept(*to_last = *last)
													)
		{
			while (first != last) {
				--last;
				--to_last;
				*to_last = *last;
			}
			return to_last;
		}

		template <typename RandomAccessIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__copy_backward(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to_last,
						std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				--last;\
				--to_last;\
				*to_last = *last;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to_last;
		}

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last)
		{
			return kerbal::algorithm::__copy_backward(first, last, to_last, kerbal::iterator::iterator_category(first));
		}



		template <typename BidirectionalIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		__copy_backward_if(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last,
							UnaryPredicate pred, std::bidirectional_iterator_tag)
		{
			while (first != last) {
				--last;
				if (pred(*last)) {
					--to_last;
					*to_last = *last;
				}
			}
			return to_last;
		}

		template <typename RandomAccessIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		__copy_backward_if(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to_last,
							UnaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				--last;\
				if (pred(*last)) {\
					--to_last;\
					*to_last = *last;\
				}\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to_last;
		}

		template <typename BidirectionalIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_backward_if(BidirectionalIterator first, BidirectionalIterator last,
							OutputIterator to_last, UnaryPredicate pred)
		{
			return kerbal::algorithm::__copy_backward_if(first, last, to_last, pred, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__move(InputIterator first, InputIterator last, OutputIterator to, std::input_iterator_tag)
		{
			 while (first != last) {
				*to = kerbal::compatibility::to_xvalue(*first);
				++to;
				++first;
			 }
			return to;
		}

		template <typename RandomAccessIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__move(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				*to = kerbal::compatibility::to_xvalue(*first);\
				++to;\
				++first;\
			} while(false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to;
		}

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move(InputIterator first, InputIterator last, OutputIterator to)
		{
			return kerbal::algorithm::__move(first, last, to, kerbal::iterator::iterator_category(first));
		}



		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__move_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last,
						std::bidirectional_iterator_tag)
		{
			while (first != last) {
				--last;
				--to_last;
				*to_last = kerbal::compatibility::to_xvalue(*last);
			}
			return to_last;
		}

		template <typename RandomAccessIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__move_backward(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to_last,
						std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				--last;\
				--to_last;\
				*to_last = kerbal::compatibility::to_xvalue(*last);\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to_last;
		}

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last)
		{
			return kerbal::algorithm::__move_backward(first, last, to_last, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename CompareFuntion>
		KERBAL_CONSTEXPR14
		OutputIterator
		merge(InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			OutputIterator to, CompareFuntion cmp)
									KERBAL_CONDITIONAL_NOEXCEPT(
											noexcept(static_cast<bool>(a_first != a_last)) &&
											noexcept(static_cast<bool>(b_first != b_last)) &&
											noexcept(static_cast<bool>(cmp(*b_first, *a_first))) &&
											noexcept(*to = *b_first) &&
											noexcept(++to) &&
											noexcept(++b_first) &&
											noexcept(*to = *a_first) &&
											noexcept(++a_first) &&
											noexcept(kerbal::algorithm::copy(a_first, a_last, to)) &&
											noexcept(kerbal::algorithm::copy(b_first, b_last, to))
									)
		{
			while (a_first != a_last) {
				if (b_first != b_last) {
					if (cmp(*b_first, *a_first)) { // b < a
						*to = *b_first;
						++to;
						++b_first;
					} else { // b >= a
						*to = *a_first;
						++to;
						++a_first;
					}
				} else {
					return kerbal::algorithm::copy(a_first, a_last, to);
				}
			}
			return kerbal::algorithm::copy(b_first, b_last, to);
		}

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		merge(InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			OutputIterator to)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type type1;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type type2;
			return kerbal::algorithm::merge(a_first, a_last, b_first, b_last, to, kerbal::algorithm::binary_type_equal_to<type2, type1>());
		}

		template <typename ForwardIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator
		__partition(ForwardIterator first, ForwardIterator last,
					UnaryPredicate pred, std::forward_iterator_tag)
		{
			first = kerbal::algorithm::find_if_not(first, last, pred);
			if (first != last) {
				ForwardIterator adv(kerbal::iterator::next(first));
				while (adv != last) {
					if (pred(*adv)) {
						kerbal::algorithm::iter_swap(first, adv);
						++first;
					}
					++adv;
				}
			}
			return first;
		}

		namespace detail
		{

			template <typename BidirectionalIterator, typename UnaryPredicate>
			KERBAL_CONSTEXPR14
			bool __partition_move_first_iter(BidirectionalIterator &first, BidirectionalIterator &last,
											 UnaryPredicate &pred, std::bidirectional_iterator_tag)
			{
				while (first != last) {
					if (pred(*first)) {
						++first;
					} else {
						return false;
					}
				}
				return true;
			}

			template <typename BidirectionalIterator, typename UnaryPredicate>
			KERBAL_CONSTEXPR14
			bool __partition_move_last_iter(BidirectionalIterator &first, BidirectionalIterator &last,
											UnaryPredicate &pred, std::bidirectional_iterator_tag)
			{
				while (first != last) {
					if (pred(*last)) {
						return false;
					} else {
						--last;
					}
				}
				return true;
			}

		} // namespace detail

		template <typename BidirectionalIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		BidirectionalIterator
		__partition(BidirectionalIterator first, BidirectionalIterator last,
					UnaryPredicate pred, std::bidirectional_iterator_tag)
		{
			while (true) {
				if (kerbal::algorithm::detail::__partition_move_first_iter(first, last, pred, kerbal::iterator::iterator_category(first))) {
					return first;
				}
				--last;
				if (kerbal::algorithm::detail::__partition_move_last_iter(first, last, pred, kerbal::iterator::iterator_category(first))) {
					return first;
				}
				kerbal::algorithm::iter_swap(first, last);
				++first;
			}
		}

		template <typename ForwardIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator partition(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
		{
			return kerbal::algorithm::__partition(first, last, pred, kerbal::iterator::iterator_category(first));
		}



		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void __reverse(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag)
		{
			while (first != last) {
				--last;
				if (first != last) {
					kerbal::algorithm::iter_swap(first, last);
					++first;
				} else {
					break;
				}
			}
		}

		template <typename RandomAccessIterator>
		KERBAL_CONSTEXPR14
		void __reverse(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				--last;\
				kerbal::algorithm::iter_swap(first, last);\
				++first;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 3); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain >= 6) {
				EACH();
			}
			if (remain >= 4) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}

#	undef EACH

		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void reverse(BidirectionalIterator first, BidirectionalIterator last)
		{
			kerbal::algorithm::__reverse(first, last, kerbal::iterator::iterator_category(first));
		}



		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to,
						std::bidirectional_iterator_tag)
		{
			while (first != last) {
				--last;
				*to = *last;
				++to;
			}
			return to;
		}

		template <typename RandomAccessIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__reverse_copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to,
						std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				--last;\
				*to = *last;\
				++to;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to;
		}

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to)
		{
			return kerbal::algorithm::__reverse_copy(first, last, to, kerbal::iterator::iterator_category(first));
		}



		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		__send_adv_iterator_to_last(ForwardIterator first, ForwardIterator adv, ForwardIterator last,
										std::forward_iterator_tag)
		{
			while (adv != last) {
				++first;
				++adv;
			}
			return first;
		}

		template <typename RandomAccessIterator>
		KERBAL_CONSTEXPR14
		RandomAccessIterator
		__send_adv_iterator_to_last(RandomAccessIterator first, RandomAccessIterator adv, RandomAccessIterator last,
										std::random_access_iterator_tag)
		{
			return kerbal::iterator::next(first, kerbal::iterator::distance(adv, last));
		}

		template <typename RandomAccessIterator>
		KERBAL_CONSTEXPR14
		RandomAccessIterator
		__send_adv_iterator_to_last(RandomAccessIterator first, RandomAccessIterator adv, RandomAccessIterator last)
		{
			return kerbal::algorithm::__send_adv_iterator_to_last(first, adv, last,
					kerbal::iterator::iterator_category(first));
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		BidirectionalIterator rotate(BidirectionalIterator first, BidirectionalIterator new_first, BidirectionalIterator last)
		{
			kerbal::algorithm::reverse(first, new_first);
			kerbal::algorithm::reverse(new_first, last);
			kerbal::algorithm::reverse(first, last);
			return __send_adv_iterator_to_last(first, new_first, last);
		}

		template <typename ForwardIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator rotate_copy(ForwardIterator first, ForwardIterator mid, ForwardIterator last, OutputIterator to)
		{
			to = kerbal::algorithm::copy(mid, last, to);
			return kerbal::algorithm::copy(first, mid, to);
		}



		template <typename ForwardIterator, typename UnaryPredicate, typename Tp>
		KERBAL_CONSTEXPR14
		void __replace_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred,
							const Tp & new_val, std::forward_iterator_tag)
		{
			while (first != last) {
				if (pred(*first)) {
					*first = new_val;
				}
				++first;
			}
		}

		template <typename RandomAccessIterator, typename UnaryPredicate, typename Tp>
		KERBAL_CONSTEXPR14
		void __replace_if(RandomAccessIterator first, RandomAccessIterator last, UnaryPredicate pred,
							const Tp & new_val, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				if (pred(*first)) {\
					*first = new_val;\
				}\
				++first;\
			} while(false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

		}

		template <typename ForwardIterator, typename UnaryPredicate, typename Tp>
		KERBAL_CONSTEXPR14
		void replace_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred, const Tp & new_val)
		{
			kerbal::algorithm::__replace_if(first, last, pred, new_val, kerbal::iterator::iterator_category(first));
		}



		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void replace(ForwardIterator first, ForwardIterator last, const Tp & old_val, const Tp & new_val)
		{
			kerbal::algorithm::replace_if(first, last,
					kerbal::algorithm::__right_bind_euqal_to_val<Tp, Tp>(old_val), new_val);
		}



		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void __fill(ForwardIterator first, ForwardIterator last, const Tp & val, std::forward_iterator_tag)
		{
			while (first != last) {
				*first = val;
				++first;
			}
		}

		template <typename RandomAccessIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void __fill(RandomAccessIterator first, RandomAccessIterator last, const Tp & val, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				*first = val;\
				++first;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void fill(ForwardIterator first, ForwardIterator last, const Tp & val)
		{
			kerbal::algorithm::__fill(first, last, val, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator, typename OutputIterator, typename UnaryOperation>
		KERBAL_CONSTEXPR14
		OutputIterator
		__transform(InputIterator first, InputIterator last, OutputIterator out,
					UnaryOperation unary_op, std::input_iterator_tag)
		{
			while (first != last) {
				*out = unary_op(*first);
				++out;
				++first;
			}
			return out;
		}

		template <typename RandomAccessIterator, typename OutputIterator, typename UnaryOperation>
		KERBAL_CONSTEXPR14
		OutputIterator
		__transform(RandomAccessIterator first, RandomAccessIterator last, OutputIterator out,
					UnaryOperation unary_op, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				*out = unary_op(*first);\
				++out;\
				++first;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}


#	undef EACH

			return out;
		}

		template <typename InputIterator, typename OutputIterator, typename UnaryOperation>
		KERBAL_CONSTEXPR14
		OutputIterator
		transform(InputIterator first, InputIterator last, OutputIterator out, UnaryOperation unary_op)
		{
			return kerbal::algorithm::__transform(first, last, out, unary_op, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void __iota(ForwardIterator first, ForwardIterator last, Tp value, std::forward_iterator_tag)
		{
			while (first != last) {
				*first = value;
				++first;
				++value;
			}
		}

		template <typename RandomAccessIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void __iota(RandomAccessIterator first, RandomAccessIterator last, Tp value, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				*first = value;\
				++first;\
				++value;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void iota(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			kerbal::algorithm::__iota(first, last, value, kerbal::iterator::iterator_category(first));
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_HPP
