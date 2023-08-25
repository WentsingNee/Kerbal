/**
 * @file       avl_ordered.fwd.hpp
 * @brief
 * @date       2023-05-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_AVL_ORDERED_AVL_ORDERED_FWD_HPP
#define KERBAL_AUTONM_AVL_ORDERED_AVL_ORDERED_FWD_HPP

namespace kerbal
{

	namespace autonm
	{

		namespace detail
		{

			template <typename T>
			class autonm_avl_ordered_node;

		} // namespace detail

		template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator>
		class avl_ordered;

	} // namespace autonm

} // namespace kerbal

#endif // KERBAL_AUTONM_AVL_ORDERED_AVL_ORDERED_FWD_HPP
