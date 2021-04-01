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

#include <kerbal/container/detail/key_of_value_extractor.hpp>
#include <kerbal/hash/hash.hpp>

#include <functional>
#include <memory>

namespace kerbal
{

	namespace container
	{

		template <typename Entity,
				typename Extract = kerbal::container::detail::identity_extractor<Entity>,
				typename Hash = kerbal::hash::hash<typename Extract::key_type>,
				typename KeyEqual = std::equal_to<typename Extract::key_type>,
				typename NodeAllocatorBR = std::allocator<Entity>,
				typename BucketAllocatorBR = std::allocator<Entity>
		>
		class hash_table;

		namespace detail
		{

			template <typename Tp, typename Hash, bool CacheHashResult>
			class hash_table_node;

			template <typename Entity>
			class hash_table_local_iter;

			template <typename HTPayload>
			class hash_table_local_kiter;

			template <typename Entity>
			class hash_table_iter;

			template <typename Entity>
			class hash_table_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_FWD_HASH_TABLE_FWD_HPP
