/**
 * @file       iota.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_IOTA_HPP
#define KERBAL_ALGORITHM_MODIFIER_IOTA_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator, typename Tp>
			KERBAL_CONSTEXPR14
			void k_iota(ForwardIterator first, ForwardIterator last, Tp value, std::forward_iterator_tag)
			{
				while (first != last) {
					*first = value;
					++first;
					++value;
				}
			}

		} // namespace detail

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		void iota(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			kerbal::algorithm::detail::k_iota(first, last, value, kerbal::iterator::iterator_category(first));
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_IOTA_HPP
