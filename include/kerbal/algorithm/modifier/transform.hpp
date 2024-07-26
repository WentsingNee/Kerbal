/**
 * @file       transform.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_TRANSFORM_HPP
#define KERBAL_ALGORITHM_MODIFIER_TRANSFORM_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename InputIterator, typename OutputIterator, typename UnaryOperation>
			KERBAL_CONSTEXPR14
			OutputIterator
			k_transform(
				InputIterator first, InputIterator last, OutputIterator out,
				UnaryOperation unary_op, std::input_iterator_tag
			)
			{
				while (first != last) {
					kerbal::assign::generic_assign(*out, unary_op(*first)); // *out = unary_op(*first);
					++out;
					++first;
				}
				return out;
			}

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename InputIterator, typename OutputIterator, typename UnaryOperation>
		KERBAL_CONSTEXPR14
		OutputIterator
		transform(InputIterator first, InputIterator last, OutputIterator out, UnaryOperation unary_op)
		{
			return kerbal::algorithm::detail::k_transform(
				first, last, out, unary_op,
				kerbal::iterator::iterator_category(first)
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOperation>
		KERBAL_CONSTEXPR14
		OutputIterator
		transform(
			InputIterator1 a_first, InputIterator1 a_last, InputIterator2 b_first,
			OutputIterator out, BinaryOperation binary_op
		)
		{
			while (a_first != a_last) {
				kerbal::assign::generic_assign(*out, binary_op(*a_first, *b_first));
				// *out = binary_op(*a_first, *b_first);
				++out;
				++a_first;
				++b_first;
			}
			return out;
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_TRANSFORM_HPP
