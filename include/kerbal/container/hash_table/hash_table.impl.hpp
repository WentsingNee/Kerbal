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

#include "hash_table.decl.hpp"

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
				hash_compress_helper(kerbal::utility::in_place_t()),
				key_equal_compress_helper(kerbal::utility::in_place_t()),
				hash_table_base(this->bucket_alloc())
		{
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(size_type bucket_count) :
				hash_compress_helper(kerbal::utility::in_place_t()),
				key_equal_compress_helper(kerbal::utility::in_place_t()),
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
		~hash_table()
		{
			this->hash_table_base::destroy(this->node_alloc(), this->bucket_alloc());
		}


		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		clear()
		{
			this->hash_table_base::clear(this->node_alloc());
		}


#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		template <typename ... Args>
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::emplace(Args&& ... args)
		{
			return this->hash_table_base::emplace(
					this->hash(), this->key_equal_obj(),
					this->node_alloc(), this->bucket_alloc(),
					kerbal::utility::forward<Args>(args)...
			);
		}

#	endif


/*		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(const_reference src)
		{
			if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) {
				this->reserve(2 * this->size());
			}

			Extract extract = this->extract();
			const key_type & key = extract(src);
			hasher & hasher = this->hash();
			hash_result_type hash_code = hasher(key);
			size_type bucket_id = hash_code % this->bucket_count();
			bucket_type & bucket_in = this->k_buckets[bucket_id];

			const_local_iterator pos(this->k_determine_insert_pos(key, bucket_in).first);

			hash_table_node * p = this->k_build_new_hash_node(this->node_alloc(), src);
			p->set_cached_hash_code(hash_code);
			bucket_in.k_hook_node_after(pos, p);
			++this->k_size;
			return iterator(this->k_buckets + bucket_id, this->k_buckets + this->k_bucket_count, pos.cast_to_mutable());
		}*/

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(InputIterator first, InputIterator last)
		{
			while (first != last) {
				this->insert(*first);
				++first;
			}
		}

		/*template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		kerbal::utility::compressed_pair<
				typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator,
				bool
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert_no_exists(const_reference src)
		{
			Extract extract = this->extract();
			const key_type & key = extract(src);
			hash_result_type hash_code = this->hash()(key);
			size_type bucket_id = hash_code % this->bucket_count();
			bucket_type & bucket_in = this->k_buckets[bucket_id];

			kerbal::utility::compressed_pair<const_local_iterator, bool> pos_result(this->k_determine_insert_pos(key, bucket_in));

			if (pos_result.second) {
				iterator pos(this->k_buckets + bucket_id, this->k_buckets + this->k_bucket_count, pos_result);
				return std::make_pair(pos, true);
			}

			if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) {
				this->reserve(2 * this->size());
			}

			hash_table_node * p = this->k_build_new_hash_node(this->node_alloc(), src);
			hash_code = this->hash()(key);
			bucket_id = hash_code % this->bucket_count();
			p->set_cached_hash_code(hash_code);
			this->k_buckets[bucket_id].k_hook_node_after(pos_result.first, p);
			++this->k_size;
			iterator pos(this->k_buckets + bucket_id, this->k_buckets + this->k_bucket_count, pos.cast_to_mutable());
			return std::make_pair(pos, false);
		}*/

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert_no_exists(InputIterator first, InputIterator last)
		{
			while (first != last) {
				this->insert_no_exists(*first);
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
