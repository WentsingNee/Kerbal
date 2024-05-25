/**
 * @file       hash_table.fwd.hpp
 * @brief
 * @date       2020-10-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_FWD_HPP
#define KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_FWD_HPP

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/hash/hash.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <typename Entity,
				typename Extract = kerbal::container::identity_extractor<Entity>,
				typename Hash = kerbal::hash::hash<typename Extract::key_type>,
				typename NodeAllocatorBR = std::allocator<Entity>,
				typename BucketAllocatorBR = std::allocator<Entity>
		>
		struct hash_table_node_size;

		template <typename Entity,
				typename Extract = kerbal::container::identity_extractor<Entity>,
				typename Hash = kerbal::hash::hash<typename Extract::key_type>,
				typename KeyEqual = kerbal::compare::binary_type_equal_to<void, void>,
				typename NodeAllocatorBR = std::allocator<Entity>,
				typename BucketAllocatorBR = std::allocator<Entity>
		>
		class hash_table;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_FWD_HPP
