/**
 * @file       modifiers.hpp
 * @brief
 * @date       2019-9-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIERS_HPP_
#define KERBAL_ALGORITHM_MODIFIERS_HPP_

#include <kerbal/algorithm/binary_type_predicate.hpp>
#include <kerbal/algorithm/querier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

namespace kerbal
{
	namespace algorithm
	{

		template <typename Tp>
		KERBAL_CONSTEXPR14
		void
		swap(Tp & lhs, Tp & rhs)
		{
			Tp t(kerbal::compatibility::to_xvalue(lhs));
			lhs = rhs;
			rhs = t;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		void
		swap(Tp (&lhs)[N], Tp (&rhs)[N])
		{
			size_t i = 0;
			for (size_t trip_count(N >> 2); trip_count > 0; --trip_count) {
				kerbal::algorithm::swap(lhs[i], rhs[i]); ++i;
				kerbal::algorithm::swap(lhs[i], rhs[i]); ++i;
				kerbal::algorithm::swap(lhs[i], rhs[i]); ++i;
				kerbal::algorithm::swap(lhs[i], rhs[i]); ++i;
			}
			size_t remain(N - i);
			if (remain == 3) {
				kerbal::algorithm::swap(lhs[i], rhs[i]); ++i;
			}
			if (remain >= 2) {
				kerbal::algorithm::swap(lhs[i], rhs[i]); ++i;
			}
			if (remain >= 1) {
				kerbal::algorithm::swap(lhs[i], rhs[i]); ++i;
			}
		}

		template <typename ForwardIterator1, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		void
		iter_swap(ForwardIterator1 lhs, ForwardIterator2 rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(std::swap(*lhs, *rhs))
							)
		{
			kerbal::algorithm::swap(*lhs, *rhs);
		}

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy(InputIterator first, InputIterator last, OutputIterator to)
		{
			typedef InputIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::reference reference;

			struct each
			{
					OutputIterator & to;

					KERBAL_CONSTEXPR
					each(OutputIterator & to) :
							to(to)
					{
					}

					KERBAL_CONSTEXPR14
					void operator()(const reference val)
					{
						*to = val;
						++to;
					}
			};

			kerbal::algorithm::for_each(first, last, each(to));
			return to;
		}

		template <typename InputIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_if(InputIterator first, InputIterator last, OutputIterator to, UnaryPredicate pred)
		{
			typedef InputIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::reference reference;

			struct each
			{
					OutputIterator & to;
					UnaryPredicate pred;

					KERBAL_CONSTEXPR
					each(OutputIterator & to, UnaryPredicate pred) :
							to(to), pred(pred)
					{
					}

					KERBAL_CONSTEXPR14
					void operator()(const reference val)
					{
						if (this->pred(val)) {
							*to = val;
							++to;
						}
					}
			};

			kerbal::algorithm::for_each(first, last, each(to, pred));
			return to;
		}

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::reference reference;

			struct each
			{
					OutputIterator & to_last;

					KERBAL_CONSTEXPR
					each(OutputIterator & to_last) :
						to_last(to_last)
					{
					}

					KERBAL_CONSTEXPR14
					void operator()(const reference val)
					{
						--to_last;
						*to_last = val;
					}
			};

			kerbal::algorithm::rfor_each(first, last, each(to_last));
			return to_last;
		}

		template <typename BidirectionalIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_backward_if(BidirectionalIterator first, BidirectionalIterator last,
						OutputIterator to_last, UnaryPredicate pred)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::reference reference;

			struct each
			{
					OutputIterator & to_last;
					UnaryPredicate pred;

					KERBAL_CONSTEXPR
					each(OutputIterator & to_last, UnaryPredicate pred) :
						to_last(to_last), pred(pred)
					{
					}

					KERBAL_CONSTEXPR14
					void operator()(const reference val)
					{
						if (this->pred(val)) {
							--to_last;
							*to_last = val;
						}
					}
			};

			kerbal::algorithm::rfor_each(first, last, each(to_last, pred));
			return to_last;
		}

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move(InputIterator first, InputIterator last, OutputIterator to)
		{
			typedef InputIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::reference reference;

			struct each
			{
					OutputIterator & to;

					KERBAL_CONSTEXPR
					each(OutputIterator & to) :
							to(to)
					{
					}

					KERBAL_CONSTEXPR14
					void operator()(const reference val)
					{
						*to = kerbal::compatibility::to_xvalue(val);
						++to;
					}
			};

			kerbal::algorithm::for_each(first, last, each(to));
			return to;
		}

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::reference reference;

			struct each
			{
					OutputIterator & to_last;

					KERBAL_CONSTEXPR
					each(OutputIterator & to_last) :
						to_last(to_last)
					{
					}

					KERBAL_CONSTEXPR14
					void operator()(const reference val)
					{
						--to_last;
						*to_last = kerbal::compatibility::to_xvalue(val);
					}
			};

			kerbal::algorithm::rfor_each(first, last, each(to_last));
			return to_last;
		}

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename CompareFuntion>
		KERBAL_CONSTEXPR14
		OutputIterator
		merge(InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			OutputIterator to, CompareFuntion cmp)
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
		ForwardIterator __partition(ForwardIterator first, ForwardIterator last, UnaryPredicate pred,
				std::forward_iterator_tag)
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

		template <typename BidirectionalIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		BidirectionalIterator __partition(BidirectionalIterator first, BidirectionalIterator last,
				UnaryPredicate pred,
				std::bidirectional_iterator_tag)
		{
			while (true) {
				while (true) {
					if (first != last) {
						if (pred(*first)) {
							++first;
						} else {
							break;
						}
					} else {
						return first;
					}
				}
				--last;
				while (true) {
					if (first != last) {
						if (!bool(pred(*last))) {
							--last;
						} else {
							break;
						}
					} else {
						return first;
					}
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
		void reverse(BidirectionalIterator first, BidirectionalIterator last)
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

		template <typename ForwardIterator, typename UnaryPredicate, typename Tp>
		KERBAL_CONSTEXPR14
		void replace_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred, const Tp & new_val)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::reference reference;

			struct each
			{
				UnaryPredicate pred;
				const Tp & new_val;

				KERBAL_CONSTEXPR
				each(UnaryPredicate pred, const Tp & new_val) :
						pred(pred), new_val(new_val)
				{
				}

				KERBAL_CONSTEXPR14
				void operator()(reference old) const
				{
					if (this->pred(old)) {
						old = this->new_val;
					}
				}
			};
			kerbal::algorithm::for_each(first, last, each(pred, new_val));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void replace(ForwardIterator first, ForwardIterator last, const Tp & old_val, const Tp & new_val)
		{
			kerbal::algorithm::replace_if(first, last,
					kerbal::algorithm::__right_bind_euqal_to_val<Tp, Tp>(old_val), new_val);
		}

		template <typename ForwardIterator1, typename ForwardIterator2>
		KERBAL_CONSTEXPR14
		ForwardIterator2
		__range_swap(ForwardIterator1 a_first, ForwardIterator1 a_last, ForwardIterator2 b_first,
						std::forward_iterator_tag)
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

#		define EACH()\
		do {\
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

#		undef EACH

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

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void fill(ForwardIterator first, ForwardIterator last, const Tp & val)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::reference reference;

			struct each
			{
					const Tp & val;

					KERBAL_CONSTEXPR
					each(const Tp & val) KERBAL_NOEXCEPT :
							val(val)
					{
					}

					KERBAL_CONSTEXPR14
					void operator()(reference old_val) const
					{
						old_val = this->val;
					}
			};
			kerbal::algorithm::for_each(first, last, each(val));
		}

		template <typename ForwardIterator, typename OutputIterator, typename UnaryOperation>
		KERBAL_CONSTEXPR14
		OutputIterator
		transform(ForwardIterator first, ForwardIterator last, OutputIterator out, UnaryOperation unary_op)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::reference reference;

			struct each
			{
					OutputIterator & out;
					UnaryOperation unary_op;

					KERBAL_CONSTEXPR
					each(OutputIterator & out, UnaryOperation unary_op) KERBAL_NOEXCEPT :
							out(out), unary_op(unary_op)
					{
					}

					KERBAL_CONSTEXPR14
					void operator()(const reference val)
					{
						*this->out = this->unary_op(val);
						++this->out;
					}
			};
			kerbal::algorithm::for_each(first, last, each(out, unary_op));
			return out;
		}

	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* KERBAL_ALGORITHM_MODIFIERS_HPP_ */
