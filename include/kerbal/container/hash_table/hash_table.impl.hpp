/**
 * @file       hash_table.impl.hpp
 * @brief
 * @date       2021-03-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_IMPL_HPP
#define KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_IMPL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>

#include <kerbal/container/hash_table/hash_table.decl.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table() :
				hash_table_base(this->bucket_alloc())
		{
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(size_type bucket_count) :
				hash_table_base(this->bucket_alloc(), bucket_count)
		{
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(size_type bucket_count, const Hash & hash) :
				hash_compress_helper(kerbal::utility::in_place_t(), hash),
				key_equal_compress_helper(kerbal::utility::in_place_t()),
				hash_table_base(this->bucket_alloc(), bucket_count)
		{
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(size_type bucket_count, const Hash & hash, const key_equal & key_equal) :
				hash_compress_helper(kerbal::utility::in_place_t(), hash),
				key_equal_compress_helper(kerbal::utility::in_place_t(), key_equal),
				hash_table_base(this->bucket_alloc(), bucket_count)
		{
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(hash_table const & src) :
			hash_table_base(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				src.cbegin(), src.cend()
			)
		{
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(hash_table const & src, kerbal::container::unique_tag_t tag) :
			hash_table_base(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				tag, src.cbegin(), src.cend()
			)
		{
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		~hash_table()
		{
			this->hash_table_base::destroy_using_allocator(this->node_alloc(), this->bucket_alloc());
		}


		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		clear()
		{
			this->hash_table_base::clear_using_allocator(this->node_alloc());
		}


#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::emplace(Args&& ... args)
		{
			return this->hash_table_base::emplace_using_allocator(
					this->extract(), this->hash(), this->key_equal_obj(),
					this->node_alloc(), this->bucket_alloc(),
					kerbal::utility::forward<Args>(args)...
			);
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::emplace_unique(Args&& ... args)
		{
			return this->hash_table_base::emplace_unique_using_allocator(
					this->extract(), this->hash(), this->key_equal_obj(),
					this->node_alloc(), this->bucket_alloc(),
					kerbal::utility::forward<Args>(args)...
			);
		}

#	endif


		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(const_reference src)
		{
			return this->hash_table_base::insert_using_allocator(
					this->extract(), this->hash(), this->key_equal_obj(),
					this->node_alloc(), this->bucket_alloc(),
					src
			);
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(InputIterator first, InputIterator last)
		{
			while (first != last) {
				this->insert(*first);
				++first;
			}
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert_unique(const_reference src)
		{
			return this->hash_table_base::insert_unique_using_allocator(
					this->extract(), this->hash(), this->key_equal_obj(),
					this->node_alloc(), this->bucket_alloc(),
					src
			);
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert_unique(InputIterator first, InputIterator last)
		{
			while (first != last) {
				this->insert_unique(*first);
				++first;
			}
		}



/*
		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
*/

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_IMPL_HPP
