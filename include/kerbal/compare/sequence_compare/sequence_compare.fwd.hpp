/**
 * @file       sequence_compare.fwd.hpp
 * @brief
 * @date       2023-01-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPARE_SEQUENCE_COMPARE_SEQUENCE_COMPARE_FWD_HPP
#define KERBAL_COMPARE_SEQUENCE_COMPARE_SEQUENCE_COMPARE_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace compare
	{

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename BinaryTypeEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			BinaryTypeEqualToPredicate equal_to
		);

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename BinaryTypeEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			const Container1 & container1, const Container2 & container2,
			BinaryTypeEqualToPredicate equal_to
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			const Container1 & container1, const Container2 & container2
		);

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t N, typename BinaryTypeEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			const T (& a)[N], const U (& b)[N],
			BinaryTypeEqualToPredicate equal_to
		);

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t N>
		KERBAL_CONSTEXPR14
		bool sequence_equal_to(
			const T (& a)[N], const U (& b)[N]
		);

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t M, std::size_t N, typename BinaryTypeEqualToPredicate>
		KERBAL_CONSTEXPR
		bool sequence_equal_to(
			const T (&)[M], const U (&)[N],
			BinaryTypeEqualToPredicate
		) KERBAL_NOEXCEPT;

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR
		bool sequence_equal_to(
			const T (&)[N], const U (&)[N]
		) KERBAL_NOEXCEPT;


		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename BinaryTypeNotEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			BinaryTypeNotEqualToPredicate not_equal_to
		);

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename BinaryTypeNotEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			const Container1 & container1, const Container2 & container2,
			BinaryTypeNotEqualToPredicate not_equal_to
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			const Container1 & container1,
			const Container2 & container2
		);

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t N, typename BinaryTypeNotEqualToPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			const T (& a)[N], const U (& b)[N],
			BinaryTypeNotEqualToPredicate not_equal_to
		);

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t N>
		KERBAL_CONSTEXPR14
		bool sequence_not_equal_to(
			const T (& a)[N], const U (& b)[N]
		);

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t M, std::size_t N, typename BinaryTypeNotEqualToPredicate>
		KERBAL_CONSTEXPR
		bool sequence_not_equal_to(
			const T (&)[M], const U (&)[N],
			BinaryTypeNotEqualToPredicate
		) KERBAL_NOEXCEPT;

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR
		bool sequence_not_equal_to(
			const T (&)[N], const U (&)[N]
		) KERBAL_NOEXCEPT;


		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename LessPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_less(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			LessPredicate less
		);

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_less(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename LessPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_less(
			const Container1 & container1, const Container2 & container2,
			LessPredicate less
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_less(
			const Container1 & container1, const Container2 & container2
		);


		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename GreaterPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_greater(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			GreaterPredicate greater
		);

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_greater(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename GreaterPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_greater(
			const Container1 & container1, const Container2 & container2,
			GreaterPredicate greater
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_greater(
			const Container1 & container1, const Container2 & container2
		);


		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename LessEqualPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_less_equal(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			LessEqualPredicate less_equal
		);

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_less_equal(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename LessEqualPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_less_equal(
			const Container1 & container1, const Container2 & container2,
			LessEqualPredicate less_equal
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_less_equal(
			const Container1 & container1,
			const Container2 & container2
		);


		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename GreaterEqualPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_greater_equal(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			GreaterEqualPredicate greater_equal
		);

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2>
		KERBAL_CONSTEXPR14
		bool sequence_greater_equal(
			InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2, typename GreaterEqualPredicate>
		KERBAL_CONSTEXPR14
		bool sequence_greater_equal(
			const Container1 & container1, const Container2 & container2,
			GreaterEqualPredicate greater_equal
		);

		KERBAL_MODULE_EXPORT
		template <typename Container1, typename Container2>
		KERBAL_CONSTEXPR14
		bool sequence_greater_equal(
			const Container1 & container1, const Container2 & container2
		);

	} // namespace compare

} // namespace kerbal

#endif // KERBAL_COMPARE_SEQUENCE_COMPARE_SEQUENCE_COMPARE_FWD_HPP
