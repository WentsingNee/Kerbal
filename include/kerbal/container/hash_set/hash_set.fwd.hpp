/**
 * @file       hash_set.fwd.hpp
 * @brief
 * @date       2024-05-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_HASH_SET_HASH_SET_FWD_HPP
#define KERBAL_CONTAINER_HASH_SET_HASH_SET_FWD_HPP

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/hash/hash.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <
			typename T,
			typename Hash = kerbal::hash::hash<T>,
			typename KeyEqual = kerbal::compare::binary_type_equal_to<void, void>,
			typename NodeAllocator = std::allocator<T>,
			typename BucketAllocator = std::allocator<T>
		>
		class hash_set;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_HASH_SET_HASH_SET_FWD_HPP
