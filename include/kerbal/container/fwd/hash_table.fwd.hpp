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

#ifndef KERBAL_CONTAINER_FWD_HASH_TABLE_FWD_HPP
#define KERBAL_CONTAINER_FWD_HASH_TABLE_FWD_HPP

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/hash/hash.hpp>

#include <functional>
#include <memory>

#include <kerbal/container/detail/key_extractors.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Entity,
				typename Extract = kerbal::container::detail::identity_extractor<Entity>,
				typename Hash = kerbal::hash::hash<typename Extract::key_type>,
				typename KeyEqual = kerbal::compare::equal_to<typename Extract::key_type>,
				typename NodeAllocatorBR = std::allocator<Entity>,
				typename BucketAllocatorBR = std::allocator<Entity>
		>
		class hash_table;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_FWD_HASH_TABLE_FWD_HPP
