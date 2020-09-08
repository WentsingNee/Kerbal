/**
 * @file       querier.hpp
 * @brief
 * @date       2019-9-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_HPP
#define KERBAL_ALGORITHM_QUERIER_HPP

#include <kerbal/algorithm/binary_type_predicate.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <functional> // std::less etc

namespace kerbal
{

	namespace algorithm
	{

		template <typename Type, typename BindType>
		struct __right_bind_euqal_to_val
		{
			const BindType & value;

			KERBAL_CONSTEXPR
			__right_bind_euqal_to_val(const BindType & value) KERBAL_NOEXCEPT :
						value(value)
			{
			}

			KERBAL_CONSTEXPR14
			bool operator()(const Type & value) const
			{
				return kerbal::algorithm::binary_type_equal_to<Type, BindType>()(value, this->value);
			}
		};

		template <typename UnaryPredicate>
		struct negate
		{
				UnaryPredicate pred;

				KERBAL_CONSTEXPR
				negate(UnaryPredicate pred) KERBAL_NOEXCEPT :
					pred(pred)
				{
				}

				template <typename Tp>
				KERBAL_CONSTEXPR14
				bool operator()(const Tp & val) const
				{
					return !static_cast<bool>(this->pred(val));
				}
		};



		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		InputIterator
		__find_if(InputIterator first, InputIterator last, UnaryPredicate pred, std::input_iterator_tag)
		{
			while (first != last) {
				if (pred(*first)) {
					break;
				}
				++first;
			}
			return first;
		}

		template <typename RandomAccessIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		RandomAccessIterator
		__find_if(RandomAccessIterator first, RandomAccessIterator last, UnaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				if (pred(*first)) {\
					return first;\
				}\
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

			return first;
		}

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		InputIterator
		find_if(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return kerbal::algorithm::__find_if(first, last, pred, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator, typename Type>
		KERBAL_CONSTEXPR14
		InputIterator
		__find(InputIterator first, InputIterator last, const Type & value, std::input_iterator_tag)
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
		__find(RandomAccessIterator first, RandomAccessIterator last, const Type & value, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				if (*first == value) {\
					return first;\
				}\
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

			return first;
		}

		template <typename InputIterator, typename Type>
		KERBAL_CONSTEXPR14
		InputIterator
		find(InputIterator first, InputIterator last, const Type & value)
		{
			return kerbal::algorithm::__find(first, last, value, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		InputIterator
		__find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred, std::input_iterator_tag)
		{
			while (first != last) {
				if (pred(*first)) {
					++first;
				} else {
					break;
				}
			}
			return first;
		}

		template <typename RandomAccessIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		RandomAccessIterator
		__find_if_not(RandomAccessIterator first, RandomAccessIterator last, UnaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				if (pred(*first)) {\
					++first;\
				} else {\
					break;\
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

			return first;
		}

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		InputIterator
		find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return kerbal::algorithm::__find_if_not(first, last, pred, kerbal::iterator::iterator_category(first));
		}

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return (kerbal::algorithm::find_if_not(first, last, pred) == last);
		}

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return (kerbal::algorithm::find_if(first, last, pred) != last);
		}

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return !kerbal::algorithm::any_of(first, last, pred);
		}



		template <typename InputIterator, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction
		__for_each(InputIterator first, InputIterator last, UnaryFunction f, std::input_iterator_tag)
		{
			while (first != last) {
				f(*first);
				++first;
			}
			return kerbal::compatibility::to_xvalue(f);
		}

		template <typename RandomAccessIterator, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction
		__for_each(RandomAccessIterator first, RandomAccessIterator last, UnaryFunction f, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				f(*first);\
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

			return kerbal::compatibility::to_xvalue(f);
		}

		template <typename InputIterator, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction
		for_each(InputIterator first, InputIterator last, UnaryFunction f)
		{
			return kerbal::algorithm::__for_each(first, last, f, kerbal::iterator::iterator_category(first));
		}



		template <typename BidirectionalIterator, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction
		__rfor_each(BidirectionalIterator first, BidirectionalIterator last, UnaryFunction f,
									std::input_iterator_tag)
		{
			while (first != last) {
				--last;
				f(*last);
			}
			return kerbal::compatibility::to_xvalue(f);
		}

		template <typename RandomAccessIterator, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction
		__rfor_each(RandomAccessIterator first, RandomAccessIterator last, UnaryFunction f, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do {\
				--last;\
				f(*last);\
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

			return kerbal::compatibility::to_xvalue(f);
		}

		template <typename BidirectionalIterator, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction
		rfor_each(BidirectionalIterator first, BidirectionalIterator last, UnaryFunction f)
		{
			return kerbal::algorithm::__rfor_each(first, last, f, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		size_t __count_if(InputIterator first, InputIterator last, UnaryPredicate pred, std::input_iterator_tag)
		{
			size_t cnt = 0;
			while (first != last) {
				if (pred(*first)) {
					++cnt;
				}
				++first;
			}
			return cnt;
		}

		template <typename RandomAccessIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		size_t __count_if(RandomAccessIterator first, RandomAccessIterator last, UnaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			size_t cnt = 0;

#	define EACH() do {\
				if (pred(*first)) {\
					++cnt;\
				}\
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

			return cnt;
		}

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		size_t count_if(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return kerbal::algorithm::__count_if(first, last, pred, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator, typename Type>
		KERBAL_CONSTEXPR14
		size_t __count(InputIterator first, InputIterator last, const Type & value, std::input_iterator_tag)
		{
			size_t cnt = 0;
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
		size_t __count(RandomAccessIterator first, RandomAccessIterator last, const Type & value, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			size_t cnt = 0;

#	define EACH() do {\
				if (*first == value) {\
					++cnt;\
				}\
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

			return cnt;
		}

		template <typename InputIterator, typename Type>
		KERBAL_CONSTEXPR14
		size_t count(InputIterator first, InputIterator last, const Type & value)
		{
			return kerbal::algorithm::__count(first, last, value, kerbal::iterator::iterator_category(first));
		}

		template <typename InputIterator, typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		InputIterator
		find_first_of(InputIterator first, InputIterator last,
						ForwardIterator s_first, ForwardIterator s_last,
						BinaryPredicate pred)
		{
			while (first != last) {
				for (ForwardIterator it(s_first); it != s_last; ++it) {
					if (pred(*first, *it)) {
						return first;
					}
				}
				++first;
			}
			return first;
		}

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		InputIterator
		find_first_of(InputIterator first, InputIterator last,
						ForwardIterator s_first, ForwardIterator s_last)
		{
			typedef typename kerbal::iterator::iterator_traits<InputIterator>::value_type value_type1;
			typedef typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type value_type2;

			return kerbal::algorithm::find_first_of(first, last, s_first, s_last,
					kerbal::algorithm::binary_type_equal_to<value_type1, value_type2>());
		}

		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator
		adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			if (first != last) {
				ForwardIterator nxt(kerbal::iterator::next(first));
				while (nxt != last) {
					if (pred(*first, *nxt)) {
						break;
					}
					first = nxt;
					++nxt;
				}
			}
			return first;
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		adjacent_find(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::algorithm::adjacent_find(first, last, kerbal::algorithm::binary_type_equal_to<value_type, value_type>());
		}



		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator __better_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;

			iterator selected(first);
			if (first != last) {
				++first;
				while (first != last) {
					if (pred(*first, *selected)) {
						selected = first;
					}
					++first;
				}
			}
			return selected;
		}

		template <typename RandomAccessIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		RandomAccessIterator __better_element(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			iterator selected(first);
			if (first != last) {
				++first;

#	define EACH() do {\
					if (pred(*first, *selected)) {\
						selected = first;\
					}\
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
			return selected;
		}

		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			return kerbal::algorithm::__better_element(first, last, pred, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::algorithm::min_element(first, last, std::less<value_type>());
		}

		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			return kerbal::algorithm::__better_element(first, last, pred, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::algorithm::max_element(first, last, std::greater<value_type>());
		}

		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		__minmax_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;

			iterator mini(first);
			iterator maxi(first);
			if (first != last) {
				++first;
				while (first != last) {
					if (pred(*first, *mini)) { // *first < *mini
						mini = first;
					} else if (!static_cast<bool>(pred(*first, *maxi))) { // *first >= *maxi
						maxi = first;
					}
					++first;
				}
			}
			return std::make_pair(mini, maxi);
		}

		template <typename RandomAccessIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		std::pair<RandomAccessIterator, RandomAccessIterator>
		__minmax_element(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			iterator mini(first);
			iterator maxi(first);
			if (first != last) {
				++first;

#	define EACH() do {\
					if (pred(*first, *mini)) {\
						mini = first;\
					} else if (!static_cast<bool>(pred(*first, *maxi))) {\
						maxi = first;\
					}\
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
			return std::make_pair(mini, maxi);
		}

		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		minmax_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			return kerbal::algorithm::__minmax_element(first, last, pred, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		minmax_element(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::algorithm::minmax_element(first, last, std::less<value_type>());
		}

	} //namespace algorithm

} //namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_HPP
