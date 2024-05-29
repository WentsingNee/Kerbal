/**
 * @file       fill.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_FILL_HPP
#define KERBAL_ALGORITHM_MODIFIER_FILL_HPP

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR14
			void k_fill(ForwardIterator first, ForwardIterator last, const T & val, std::forward_iterator_tag)
			{
				while (first != last) {
					kerbal::assign::generic_assign(*first, val); // *first = val;
					++first;
				}
			}

		} // namespace detail

		template <typename ForwardIterator, typename T>
		KERBAL_CONSTEXPR14
		void fill(ForwardIterator first, ForwardIterator last, const T & val)
		{
			kerbal::algorithm::detail::k_fill(first, last, val, kerbal::iterator::iterator_category(first));
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_FILL_HPP
