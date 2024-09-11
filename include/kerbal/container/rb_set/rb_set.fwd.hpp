/**
 * @file       rb_set.fwd.hpp
 * @brief
 * @date       2024-09-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_RB_SET_RB_SET_FWD_HPP
#define KERBAL_CONTAINER_RB_SET_RB_SET_FWD_HPP

#include <kerbal/compare/binary_type_compare.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <
			typename T,
			typename KeyCompare = kerbal::compare::binary_type_less<void, void>,
			typename Allocator = std::allocator<T>
		>
		class rb_set;

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_RB_SET_RB_SET_FWD_HPP
