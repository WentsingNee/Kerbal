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

#ifndef KERBAL_CONTAINER_IMPL_HASH_TABLE_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_HASH_TABLE_IMPL_HPP

#include <kerbal/container/hash_table.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table() :
				hash_compress_helper(kerbal::utility::in_place_t()),
				key_equal_compress_helper(kerbal::utility::in_place_t()),
				_K_size(0),
				_K_max_load_factor(1)
		{
			this->_K_init_buckets();
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(size_type bucket_count) :
				hash_compress_helper(kerbal::utility::in_place_t()),
				key_equal_compress_helper(kerbal::utility::in_place_t()),
				_K_size(0),
				_K_max_load_factor(1)
		{
			this->_K_init_buckets(_K_first_prime_greater_equal_than(bucket_count));
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(size_type bucket_count, const Hash & hash) :
				hash_compress_helper(kerbal::utility::in_place_t(), hash),
				key_equal_compress_helper(kerbal::utility::in_place_t()),
				_K_size(0),
				_K_max_load_factor(1)
		{
			this->_K_init_buckets(_K_first_prime_greater_equal_than(bucket_count));
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(size_type bucket_count, const Hash & hash, const key_equal & key_equal) :
				hash_compress_helper(kerbal::utility::in_place_t(), hash),
				key_equal_compress_helper(kerbal::utility::in_place_t(), key_equal),
				_K_size(0),
				_K_max_load_factor(1)
		{
			this->_K_init_buckets(_K_first_prime_greater_equal_than(bucket_count));
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		~hash_table()
		{
			for (size_t i = 0; i < this->_K_bucket_count; ++i) {
				bucket_type & bucket_to_clear = this->_K_buckets[i];
				bucket_to_clear._K_clear(this->node_alloc());
				bucket_allocator_traits::destroy(this->bucket_alloc(), &bucket_to_clear);
			}
			bucket_allocator_traits::deallocate(this->bucket_alloc(), this->_K_buckets, this->_K_bucket_count);
		}


	//===================
	// Iterators

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR14
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		begin() KERBAL_NOEXCEPT
		{
			return iterator(_K_buckets, _K_buckets + _K_bucket_count, local_iterator(_K_buckets->begin()));
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR14
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		begin() const KERBAL_NOEXCEPT
		{
			return const_iterator(_K_buckets, _K_buckets + _K_bucket_count, const_local_iterator(_K_buckets->begin()));
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR14
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		cbegin() const KERBAL_NOEXCEPT
		{
			return const_iterator(_K_buckets, _K_buckets + _K_bucket_count, const_local_iterator(_K_buckets->begin()));
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR14
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		end() KERBAL_NOEXCEPT
		{
			bucket_type * end_bucket = _K_buckets + _K_bucket_count;
			return iterator(end_bucket, end_bucket, local_iterator(_K_buckets->end()));
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR14
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		end() const KERBAL_NOEXCEPT
		{
			bucket_type * end_bucket = _K_buckets + _K_bucket_count;
			return const_iterator(end_bucket, end_bucket, const_local_iterator(_K_buckets->end()));
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR14
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		cend() const KERBAL_NOEXCEPT
		{
			bucket_type * end_bucket = _K_buckets + _K_bucket_count;
			return const_iterator(end_bucket, end_bucket, const_local_iterator(_K_buckets->end()));
		}




		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		clear()
		{
			for (size_type i = 0; i < this->_K_bucket_count; ++i) {
				bucket_type & bucket_to_clear = this->_K_buckets[i];
				bucket_to_clear._K_clear(this->node_alloc());
			}
			this->_K_size = 0;
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		std::pair<
			typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_local_iterator,
			bool
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		_K_determine_insert_pos(const key_type & key, bucket_type & bucket_in)
		{
			key_equal & key_equal_obj = this->key_equal_obj();

			const_local_iterator before_it(bucket_in.cbefore_begin());
			const_local_iterator it(bucket_in.cbegin());
			const_local_iterator end(bucket_in.cend());

			bool found = false;

			while (it != end) {
				if (key_equal_obj(extract(*it), key)) { // *it == key
					found = true;
					break;
				}
				before_it = it;
				++it;
			}

			if (!found) {
				before_it = bucket_in.cbefore_begin();
			}

			return std::pair<const_local_iterator, bool>(before_it, found);
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(const_reference src)
		{
			Extract extract = this->extract();
			const key_type & key = extract(src);
			hasher & hasher = this->hash();
			hash_result_type hash_code = hasher(key);
			size_type bucket_id = hash_code % this->bucket_count();
			bucket_type & bucket_in = this->_K_buckets[bucket_id];

			const_local_iterator pos(this->_K_determine_insert_pos(key, bucket_in).first);

			hash_table_node * p = this->_K_build_new_hash_node(this->node_alloc(), src);
			p->set_cached_hash_code(hash_code);
			bucket_in._K_hook_node_after(pos, p);
			++this->_K_size;
			if (this->size() > this->bucket_count() * this->max_load_factor()) {
				this->reserve(2 * this->size());
			}

			// warning
		}

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

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		std::pair<
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
			bucket_type & bucket_in = this->_K_buckets[bucket_id];

			std::pair<const_local_iterator, bool> pos_result(this->_K_determine_insert_pos(key, bucket_in));

			if (pos_result.second) {
				return;
			}

			hash_table_node * p = this->_K_build_new_hash_node(this->node_alloc(), src);
			p->set_cached_hash_code(hash_code);
			bucket_in._K_hook_node_after(pos_result.first, p);
			++this->_K_size;
			if (this->size() > this->bucket_count() * this->max_load_factor()) {
				this->reserve(2 * this->size());
			}
		}

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


	//===================
	// private

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR14
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::size_type
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		_K_first_prime_greater_equal_than(size_type n) KERBAL_NOEXCEPT
		{
			while (true) {
				bool found = true;
				for (size_type i = 2; i * i <= n; ++i) {
					if (n % i == 0) {
						found = false;
						break;
					}
				}
				if (found) {
					return n;
				}
				++n;
			}
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::bucket_type *
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		_K_create_new_buckets(size_type new_bucket_count)
		{
			bucket_type * new_buckets = bucket_allocator_traits::allocate(this->bucket_alloc(), new_bucket_count);
			for (size_type i = 0; i < new_bucket_count; ++i) {
				bucket_allocator_traits::construct(this->bucket_alloc(), &new_buckets[i]);
			}
			return new_buckets;
		}

		template <typename Entity, typename Extract, typename Hash, typename KeyEqual,
				typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		_K_rehash_unchecked(size_type new_bucket_count)
		{
			bucket_type * new_buckets = _K_create_new_buckets(new_bucket_count);
			hasher & hash = this->hash();

			for (size_type i = 0; i < this->_K_bucket_count; ++i) {
				bucket_type & bucket_clear = this->_K_buckets[i];
				local_iterator it(bucket_clear.begin());
				local_iterator end(bucket_clear.end());
				while (it != end) {
					hash_table_node * hash_node = static_cast<hash_table_node*>(it.current);
					++it;
					bucket_type & bucket_in = new_buckets[hash_node->get_cached_hash_code(hash) % new_bucket_count];
					bucket_in.bucket_type::fl_type_unrelated::_K_hook_node_after(bucket_in.before_begin(), hash_node);
				}
				bucket_clear.head_node.next = NULL;
				bucket_allocator_traits::destroy(this->bucket_alloc(), &bucket_clear);
			}
			bucket_allocator_traits::deallocate(this->bucket_alloc(), this->_K_buckets, this->_K_bucket_count);

			this->_K_buckets = new_buckets;
			this->_K_bucket_count = new_bucket_count;
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

#endif // KERBAL_CONTAINER_IMPL_HASH_TABLE_IMPL_HPP
