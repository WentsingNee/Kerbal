/**
 * @file       sequence_compare.hpp
 * @brief      
 * @date       2019-6-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SEQUENCE_COMPARE_HPP_
#define KERBAL_ALGORITHM_SEQUENCE_COMPARE_HPP_

#include <kerbal/algorithm/binary_type_predicate.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{
	namespace algorithm
	{

		template <typename InputIterator1, typename InputIterator2, typename Compare>
		KERBAL_CONSTEXPR14 bool __sequence_equal_to(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last, Compare cmp,
				std::input_iterator_tag, std::input_iterator_tag)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(a_first != a_last)) &&
						noexcept(static_cast<bool>(b_first != b_last)) &&
						noexcept(static_cast<bool>(cmp(*a_first, *b_first))) &&
						noexcept(++a_first) &&
						noexcept(++b_first)
				)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (cmp(*a_first, *b_first)) { // namely *a == *b
					++a_first;
					++b_first;
				} else {
					return false;
				}
			}
			return !(static_cast<bool>(a_first != a_last) || static_cast<bool>(b_first != b_last));
			// a_first == a_last && b_first == b_last => true
			// a_first != a_last || b_first != b_last => false
		}

		template <typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		KERBAL_CONSTEXPR14 bool __sequence_equal_to(RandomAccessIterator1 a_first, RandomAccessIterator1 a_last,
				RandomAccessIterator2 b_first, RandomAccessIterator2 b_last, Compare cmp,
				std::random_access_iterator_tag, std::random_access_iterator_tag)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(kerbal::iterator::distance(a_first, a_last) != kerbal::iterator::distance(b_first, b_last))) &&
						noexcept(static_cast<bool>(a_first != a_last)) &&
						noexcept(static_cast<bool>(cmp(*a_first, *b_first))) &&
						noexcept(++a_first) &&
						noexcept(++b_first)
				)
		{
			if (kerbal::iterator::distance(a_first, a_last) != kerbal::iterator::distance(b_first, b_last)) {
				return false;
			}
			while (a_first != a_last) { // size are equal and b will not out of range
				if (cmp(*a_first, *b_first)) { // namely *a == *b
					++a_first;
					++b_first;
				} else {
					return false;
				}
			}
			return true;
		}

		template <typename InputIterator1, typename InputIterator2, typename Compare>
		KERBAL_CONSTEXPR bool sequence_equal_to(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last, Compare cmp)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(__sequence_equal_to(a_first, a_last, b_first, b_last, cmp,
								kerbal::iterator::iterator_category(a_first),
								kerbal::iterator::iterator_category(b_first)))
				)
		{
			return __sequence_equal_to(a_first, a_last, b_first, b_last, cmp,
					kerbal::iterator::iterator_category(a_first),
					kerbal::iterator::iterator_category(b_first));
		}

		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR bool sequence_equal_to(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(sequence_equal_to(a_first, a_last, b_first, b_last,
								binary_type_equal_to<
									typename kerbal::iterator::iterator_traits<InputIterator1>::value_type,
									typename kerbal::iterator::iterator_traits<InputIterator2>::value_type
								>()))
				)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type Tp;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type Up;
			return sequence_equal_to(a_first, a_last, b_first, b_last, binary_type_equal_to<Tp, Up>());
		}

		template <typename InputIterator1, typename InputIterator2, typename Compare>
		KERBAL_CONSTEXPR14 bool __sequence_not_equal_to(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last, Compare cmp,
				std::input_iterator_tag, std::input_iterator_tag)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (cmp(*a_first, *b_first)) { // namely *a != *b
					return true;
				} else {
					++a_first;
					++b_first;
				}
			}
			return (static_cast<bool>(a_first != a_last) || static_cast<bool>(b_first != b_last));
		}

		template <typename RandomAccessIterator1, typename RandomAccessIterator2, typename Compare>
		KERBAL_CONSTEXPR14 bool __sequence_not_equal_to(RandomAccessIterator1 a_first, RandomAccessIterator1 a_last,
				RandomAccessIterator2 b_first, RandomAccessIterator2 b_last, Compare cmp,
				std::random_access_iterator_tag, std::random_access_iterator_tag)
		{
			if (kerbal::iterator::distance(a_first, a_last) != kerbal::iterator::distance(b_first, b_last)) {
				return true;
			}
			while (a_first != a_last) { // size are equal and b will not out of range
				if (cmp(*a_first, *b_first)) { // namely *a != *b
					return true;
				} else {
					++a_first;
					++b_first;
				}
			}
			return false;
		}

		template <typename InputIterator1, typename InputIterator2, typename Compare>
		KERBAL_CONSTEXPR bool sequence_not_equal_to(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last, Compare cmp)
		{
			return __sequence_not_equal_to(a_first, a_last, b_first, b_last, cmp,
					kerbal::iterator::iterator_category(a_first),
					kerbal::iterator::iterator_category(b_first));
		}

		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR bool sequence_not_equal_to(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type Tp;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type Up;
			return sequence_not_equal_to(a_first, a_last, b_first, b_last, binary_type_not_equal_to<Tp, Up>());
		}

		template <typename InputIterator1, typename InputIterator2, typename Compare>
		KERBAL_CONSTEXPR14 bool sequence_less(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last, Compare cmp)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (cmp(*a_first, *b_first)) { // namely *a < *b
					return true;
				} else if (cmp(*b_first, *a_first)) { // namely *a > *b
					return false;
				} else { // namely *a == *b
					++a_first;
					++b_first;
				}
			}
			/*
			 * 1 2 3
			 * 1 2 3
			 * false
			 *
			 * 1 2 3
			 * 1 2
			 * false
			 *
			 * 1 2
			 * 1 2 3
			 * true
			 *
			 * b_first == b_last => false
			 * b_first != b_last => true
			 */
			return static_cast<bool>(b_first != b_last);
		}

		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR bool sequence_less(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type Tp;
//			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type Up;
			return sequence_less(a_first, a_last, b_first, b_last, std::less<Tp>());
		}

		template <typename InputIterator1, typename InputIterator2, typename Compare>
		KERBAL_CONSTEXPR14 bool sequence_greater(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last, Compare cmp)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (cmp(*a_first, *b_first)) { // namely *a > *b
					return true;
				} else if (cmp(*b_first, *a_first)) { // namely *a < *b
					return false;
				} else { // namely *a == *b
					++a_first;
					++b_first;
				}
			}
			return static_cast<bool>(a_first != a_last);
			// a_first == a_last => false
			// a_first != a_last =? true
		}

		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR bool sequence_greater(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type Tp;
//			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type Up;
			return sequence_greater(a_first, a_last, b_first, b_last, std::greater<Tp>());
		}

		template <typename InputIterator1, typename InputIterator2, typename Compare>
		KERBAL_CONSTEXPR14 bool sequence_less_equal(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last, Compare cmp)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (cmp(*a_first, *b_first)) { // namely *a <= *b
					if (cmp(*b_first, *a_first)) { // namely *a >= *b
						// namely *a == *b
						++a_first;
						++b_first;
					} else { // namely *a < *b
						return true;
					}
				} else { // namely *a > *b
					return false;
				}
			}
			return !static_cast<bool>(a_first != a_last);
		}

		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR bool sequence_less_equal(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type Tp;
//			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type Up;
			return sequence_less_equal(a_first, a_last, b_first, b_last, std::less_equal<Tp>());
		}

		template <typename InputIterator1, typename InputIterator2, typename Compare>
		KERBAL_CONSTEXPR14 bool sequence_greater_equal(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last, Compare cmp)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (cmp(*a_first, *b_first)) { // namely *a >= *b
					if (cmp(*b_first, *a_first)) { // namely *a <= *b
						// namely *a == *b
						++a_first;
						++b_first;
					} else { // namely *a > *b
						return true;
					}
				} else { // namely *a < *b
					return false;
				}
			}
			return !static_cast<bool>(b_first != b_last);
		}

		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR bool sequence_greater_equal(InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type Tp;
//			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type Up;
			return sequence_greater_equal(a_first, a_last, b_first, b_last, std::greater_equal<Tp>());
		}

	}

}


#endif /* KERBAL_ALGORITHM_SEQUENCE_COMPARE_HPP_ */
