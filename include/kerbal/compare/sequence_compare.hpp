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

#ifndef KERBAL_COMPARE_SEQUENCE_COMPARE_HPP
#define KERBAL_COMPARE_SEQUENCE_COMPARE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compare/sequence_compare/sequence_compare.fwd.hpp>

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <cstddef>


namespace kerbal
{

	namespace compare
	{

		namespace detail
		{

			template <typename InputIterator1, typename InputIterator2, typename BinaryTypeEqualToPredicate>
			KERBAL_CONSTEXPR14
			bool sequence_equal_to_helper(
				InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last,
				BinaryTypeEqualToPredicate equal_to,
				std::input_iterator_tag, std::input_iterator_tag
			)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(static_cast<bool>(a_first != a_last)) &&
					noexcept(static_cast<bool>(b_first != b_last)) &&
					noexcept(static_cast<bool>(equal_to(*a_first, *b_first))) &&
					noexcept(++a_first) &&
					noexcept(++b_first)
				)
			{
				while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
					if (equal_to(*a_first, *b_first)) { // namely *a == *b
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

			template <typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryTypeEqualToPredicate>
			KERBAL_CONSTEXPR14
			bool sequence_equal_to_helper(
				RandomAccessIterator1 a_first, RandomAccessIterator1 a_last,
				RandomAccessIterator2 b_first, RandomAccessIterator2 b_last,
				BinaryTypeEqualToPredicate equal_to,
				std::random_access_iterator_tag, std::random_access_iterator_tag
			)
			{
				typedef RandomAccessIterator1 iterator1;
				typedef typename kerbal::iterator::iterator_traits<iterator1>::difference_type difference_type;

				difference_type trip_count(kerbal::iterator::distance(a_first, a_last));
				if (trip_count != kerbal::iterator::distance(b_first, b_last)) {
					return false;
				}

#		define EACH() do { \
					if (equal_to(*a_first, *b_first)) { /* namely *a == *b*/ \
						++a_first; \
						++b_first; \
					} else { \
						return false; \
					} \
				} while (false)

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

				return true;
			}

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename BinaryTypeEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			BinaryTypeEqualToPredicate equal_to
		)
		{
			return kerbal::compare::detail::sequence_equal_to_helper(
				a_first, a_last,
				b_first, b_last,
				equal_to,
				kerbal::iterator::iterator_category(a_first),
				kerbal::iterator::iterator_category(b_first)
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type T;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type U;
			return sequence_equal_to(
				a_first, a_last,
				b_first, b_last,
				kerbal::compare::binary_type_equal_to<T, U>()
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename BinaryTypeEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			const Container1 & container1, const Container2 & container2,
			BinaryTypeEqualToPredicate equal_to
		)
		{
			return sequence_equal_to(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2),
				equal_to
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(const Container1 & container1, const Container2 & container2)
		{
			return sequence_equal_to(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2)
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t N, typename BinaryTypeEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			const T (& a)[N], const U (& b)[N],
			BinaryTypeEqualToPredicate equal_to
		)
		{
			return sequence_equal_to(
				a, a + N,
				b, b + N,
				equal_to
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t N>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(const T (& a)[N], const U (& b)[N])
		{
			return sequence_equal_to(
				a, a + N,
				b, b + N
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t M, std::size_t N, typename BinaryTypeEqualToPredicate>
		KERBAL_CONSTEXPR
		bool sequence_equal_to(const T (&)[M], const U (&)[N], BinaryTypeEqualToPredicate) KERBAL_NOEXCEPT
		{
			return false;
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR
		bool sequence_equal_to(const T (&)[N], const U (&)[N]) KERBAL_NOEXCEPT
		{
			return false;
		}



		namespace detail
		{

			template <typename InputIterator1, typename InputIterator2, typename BinaryTypeNotEqualToPredicate>
			KERBAL_CONSTEXPR14
			bool sequence_not_equal_to_helper(
				InputIterator1 a_first, InputIterator1 a_last,
				InputIterator2 b_first, InputIterator2 b_last,
				BinaryTypeNotEqualToPredicate not_equal_to,
				std::input_iterator_tag, std::input_iterator_tag
			)
			{
				while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
					if (not_equal_to(*a_first, *b_first)) { // namely *a != *b
						return true;
					} else {
						++a_first;
						++b_first;
					}
				}
				return
					static_cast<bool>(a_first != a_last) ||
					static_cast<bool>(b_first != b_last);
			}

			template <typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryTypeNotEqualToPredicate>
			KERBAL_CONSTEXPR14
			bool sequence_not_equal_to_helper(
				RandomAccessIterator1 a_first, RandomAccessIterator1 a_last,
				RandomAccessIterator2 b_first, RandomAccessIterator2 b_last,
				BinaryTypeNotEqualToPredicate not_equal_to,
				std::random_access_iterator_tag, std::random_access_iterator_tag
			)
			{
				typedef RandomAccessIterator1 iterator1;
				typedef typename kerbal::iterator::iterator_traits<iterator1>::difference_type difference_type;

				difference_type trip_count(kerbal::iterator::distance(a_first, a_last));
				if (trip_count != kerbal::iterator::distance(b_first, b_last)) {
					return true;
				}

#		define EACH() do { \
					if (not_equal_to(*a_first, *b_first)) { /* namely *a != *b*/ \
						return true; \
					} else { \
						++a_first; \
						++b_first; \
					} \
				} while (false)

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

				return false;
			}

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename BinaryTypeNotEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			BinaryTypeNotEqualToPredicate not_equal_to
		)
		{
			return kerbal::compare::detail::sequence_not_equal_to_helper(
				a_first, a_last,
				b_first, b_last,
				not_equal_to,
				kerbal::iterator::iterator_category(a_first),
				kerbal::iterator::iterator_category(b_first)
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type T;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type U;
			return sequence_not_equal_to(
				a_first, a_last,
				b_first, b_last,
				kerbal::compare::binary_type_not_equal_to<T, U>()
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename BinaryTypeNotEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			const Container1 & container1, const Container2 & container2,
			BinaryTypeNotEqualToPredicate not_equal_to
		)
		{
			return sequence_not_equal_to(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2),
				not_equal_to
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(const Container1 & container1, const Container2 & container2)
		{
			return sequence_not_equal_to(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2)
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t N, typename BinaryTypeNotEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			const T (& a)[N], const U (& b)[N],
			BinaryTypeNotEqualToPredicate not_equal_to
		)
		{
			return sequence_not_equal_to(
				a, a + N,
				b, b + N,
				not_equal_to
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t N>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(const T (& a)[N], const U (& b)[N])
		{
			return sequence_equal_to(
				a, a + N,
				b, b + N
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t M, std::size_t N, typename BinaryTypeNotEqualToPredicate>
		KERBAL_CONSTEXPR
		bool sequence_not_equal_to(const T (&)[M], const U (&)[N], BinaryTypeNotEqualToPredicate) KERBAL_NOEXCEPT
		{
			return true;
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR
		bool sequence_not_equal_to(const T (&)[N], const U (&)[N]) KERBAL_NOEXCEPT
		{
			return true;
		}



		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename LessPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_less(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			LessPredicate less
		)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (less(*a_first, *b_first)) { // namely *a < *b
					return true;
				} else if (less(*b_first, *a_first)) { // namely *a > *b
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

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_less(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		)
		{
			return sequence_less(
				a_first, a_last,
				b_first, b_last,
				kerbal::compare::binary_type_less<void, void>()
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename LessPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_less(
			const Container1 & container1, const Container2 & container2,
			LessPredicate less
		)
		{
			return sequence_less(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2),
				less
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_less(const Container1 & container1, const Container2 & container2)
		{
			return sequence_less(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2)
			);
		}



		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename GreaterPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_greater(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			GreaterPredicate greater
		)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (greater(*a_first, *b_first)) { // namely *a > *b
					return true;
				} else if (greater(*b_first, *a_first)) { // namely *a < *b
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

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_greater(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		)
		{
			return sequence_greater(
				a_first, a_last,
				b_first, b_last,
				kerbal::compare::binary_type_greater<void, void>()
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename GreaterPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_greater(
			const Container1 & container1, const Container2 & container2,
			GreaterPredicate greater
		)
		{
			return sequence_greater(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2),
				greater
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_greater(const Container1 & container1, const Container2 & container2)
		{
			return sequence_greater(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2)
			);
		}



		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename LessEqualPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_less_equal(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			LessEqualPredicate less_equal
		)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (less_equal(*a_first, *b_first)) { // namely *a <= *b
					if (less_equal(*b_first, *a_first)) { // namely *a >= *b
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

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_less_equal(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		)
		{
			return sequence_less_equal(
				a_first, a_last,
				b_first, b_last,
				kerbal::compare::binary_type_less_equal<void, void>()
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename LessEqualPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_less_equal(
			const Container1 & container1, const Container2 & container2,
			LessEqualPredicate less_equal
		)
		{
			return sequence_less_equal(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2),
				less_equal
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_less_equal(const Container1 & container1, const Container2 & container2)
		{
			return sequence_less_equal(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2)
			);
		}



		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename GreaterEqualPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_greater_equal(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			GreaterEqualPredicate greater_equal
		)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (greater_equal(*a_first, *b_first)) { // namely *a >= *b
					if (greater_equal(*b_first, *a_first)) { // namely *a <= *b
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

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_greater_equal(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		)
		{
			return sequence_greater_equal(
				a_first, a_last,
				b_first, b_last,
				kerbal::compare::binary_type_greater_equal<void, void>()
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename GreaterEqualPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_greater_equal(
			const Container1 & container1, const Container2 & container2,
			GreaterEqualPredicate greater_equal
		)
		{
			return sequence_greater_equal(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2),
				greater_equal
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_greater_equal(const Container1 & container1, const Container2 & container2)
		{
			return sequence_greater_equal(
				kerbal::container::cbegin(container1), kerbal::container::cend(container1),
				kerbal::container::cbegin(container2), kerbal::container::cend(container2)
			);
		}

	} // namespace compare

} // namespace kerbal

#endif // KERBAL_COMPARE_SEQUENCE_COMPARE_HPP
