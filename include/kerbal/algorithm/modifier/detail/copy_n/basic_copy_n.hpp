/**
 * @file       basic_copy_n.hpp
 * @brief
 * @date       2024-02-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_DETAIL_COPY_N_BASIC_COPY_N_HPP
#define KERBAL_ALGORITHM_MODIFIER_DETAIL_COPY_N_BASIC_COPY_N_HPP

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename InputIterator, typename OutputIterator>
			struct basic_copy_n_ret
			{
				InputIterator first;
				OutputIterator second;

				KERBAL_CONSTEXPR
				basic_copy_n_ret(const InputIterator & first, const OutputIterator & second) :
					first(first),
					second(second)
				{
				}

			};

			template <typename InputIterator, typename SizeType, typename OutputIterator>
			KERBAL_CONSTEXPR14
			basic_copy_n_ret<InputIterator, OutputIterator>
			basic_copy_n(InputIterator first, SizeType n, OutputIterator to)
			{
				while (n > 0) {
					kerbal::assign::generic_assign(*to, *first); // *to = *first;
					--n;
					++to;
					++first;
				}
				return basic_copy_n_ret<InputIterator, OutputIterator>(first, to);
			}

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_DETAIL_COPY_N_BASIC_COPY_N_HPP
