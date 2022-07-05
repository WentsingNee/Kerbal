/**
 * @file       modifier.fwd.hpp
 * @brief
 * @date       2022-07-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_MODIFIER_FWD_HPP
#define KERBAL_ALGORITHM_MODIFIER_MODIFIER_FWD_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <kerbal/utility/compressed_pair/compressed_pair.fwd.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy(InputIterator first, InputIterator last, OutputIterator to);

		template <typename InputIterator, typename SizeType, typename OutputIterator>
		KERBAL_CONSTEXPR14
		kerbal::utility::compressed_pair<InputIterator, OutputIterator>
		copy_n(InputIterator first, SizeType n, OutputIterator to);

		template <typename InputIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_if(InputIterator first, InputIterator last, OutputIterator to, UnaryPredicate pred);

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last);

		template <typename BidirectionalIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_backward_if(BidirectionalIterator first, BidirectionalIterator last,
							OutputIterator to_last, UnaryPredicate pred);

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move(InputIterator first, InputIterator last, OutputIterator to);

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last);


		template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename CompareFuntion>
		KERBAL_CONSTEXPR14
		OutputIterator
		merge(InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			OutputIterator to, CompareFuntion cmp);

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		merge(InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			OutputIterator to);

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void reverse(BidirectionalIterator first, BidirectionalIterator last);

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to);

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		rotate(ForwardIterator first, ForwardIterator n_first, ForwardIterator last);


		template <typename ForwardIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		rotate_copy(ForwardIterator first, ForwardIterator mid, ForwardIterator last, OutputIterator to);

		template <typename ForwardIterator, typename BinaryPredict>
		KERBAL_CONSTEXPR14
		void inplace_merge(ForwardIterator first, ForwardIterator mid, ForwardIterator last, BinaryPredict cmp);

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void inplace_merge(ForwardIterator first, ForwardIterator mid, ForwardIterator last);

		template <typename ForwardIterator, typename UnaryPredicate, typename Tp>
		KERBAL_CONSTEXPR14
		void replace_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred, const Tp & new_val);

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void replace(ForwardIterator first, ForwardIterator last, const Tp & old_val, const Tp & new_val);

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void fill(ForwardIterator first, ForwardIterator last, const Tp & val);

		template <typename InputIterator, typename OutputIterator, typename UnaryOperation>
		KERBAL_CONSTEXPR14
		OutputIterator
		transform(InputIterator first, InputIterator last, OutputIterator out, UnaryOperation unary_op);

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOperation >
		KERBAL_CONSTEXPR14
		OutputIterator
		transform(InputIterator1 a_first, InputIterator1 a_last, InputIterator2 b_first,
				  OutputIterator out, BinaryOperation binary_op);

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void iota(ForwardIterator first, ForwardIterator last, const Tp & value);

		template <typename ForwardIterator, typename BinaryPredict>
		KERBAL_CONSTEXPR14
		ForwardIterator
		unique(ForwardIterator first, ForwardIterator last, BinaryPredict equal);

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		unique(ForwardIterator first, ForwardIterator last);

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_MODIFIER_FWD_HPP
