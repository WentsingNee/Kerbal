/**
 * @file       hash_table_base.impl.hpp
 * @brief
 * @date       2022-03-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_IMPL_HPP

#include <kerbal/algorithm/modifier/fill.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/uninitialized/construct.hpp>
#include <kerbal/type_traits/is_same.hpp>

#include <kerbal/container/detail/hash_table_base/hash_table_base.decl.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

		//===================
		// Constructor/Destructor

			template <typename Entity, typename HashCachePolicy>
			template <typename BucketAlloc>
			KERBAL_CONSTEXPR20
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(BucketAlloc & bucket_alloc) :
				k_size(0),
				k_max_load_factor(1)
			{
				this->k_init_buckets(bucket_alloc);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename BucketAlloc>
			KERBAL_CONSTEXPR20
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(BucketAlloc & bucket_alloc, size_type bucket_count) :
				k_size(0),
				k_max_load_factor(1)
			{
				// this->k_init_buckets(bucket_alloc, k_first_prime_greater_equal_than(bucket_count));
				this->k_init_buckets(bucket_alloc, bucket_count);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename InputIterator>
			KERBAL_CONSTEXPR20
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				InputIterator first, InputIterator last
			) :
				k_size(0),
				k_max_load_factor(1)
			{
				this->k_init_buckets(bucket_alloc, 7);
				while (first != last) {
					this->emplace_using_allocator(extract, hash, key_equal, node_alloc, bucket_alloc, *first);
					++first;
				}
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename InputIterator>
			KERBAL_CONSTEXPR20
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				kerbal::container::unique_tag_t, InputIterator first, InputIterator last
			) :
				k_size(0),
				k_max_load_factor(1)
			{
				this->k_init_buckets(bucket_alloc, 7);
				while (first != last) {
					this->emplace_unique_using_allocator(extract, hash, key_equal, node_alloc, bucket_alloc, *first);
					++first;
				}
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename NodeAlloc, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			destroy_using_allocator(NodeAlloc & node_alloc, BucketAlloc & bucket_alloc)
			{
				k_destroy_node_chain(node_alloc, static_cast<node *>(this->k_head.k_next), NULL);
				k_destroy_buckets(bucket_alloc, this->k_buckets, this->k_bucket_count);
			}

		//===================
		// Node Hook/Unhook

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::k_emplace_hook_node(Extract & extract, Hash & hash, node * p)
			{
				this->k_rehash_hook_node(extract, hash, p);
				++this->k_size;
				return iterator(p);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::unique_insert_r
			hash_table_base<Entity, HashCachePolicy>::
			k_emplace_hook_node_unique(Extract & extract, Hash & hash, KeyEqual & key_equal, node * p)
			{
				typedef typename Extract::key_type key_type;

				const key_type & key = extract(p->member());
				hash_result_type hash_code = p->get_cached_hash_code(extract, hash);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type & bucket_in = this->k_buckets[bucket_id_in];

				node_type_unrelated * prev = bucket_in;
				// for (size_type i = 0; i <= this->k_bucket_count; ++i) {
				// 	std::printf("%zu  %p\n", i, this->k_buckets[i]);
				// }
				// std::printf("%zu/%zu %zu  %zu\n", hash_code, this->k_bucket_count, bucket_id_in, bucket_id_next);
				// std::printf("\n");
				node * cur = static_cast<node *>(prev->k_next);
				while (true) {
					if (cur == NULL) {
						break;
					}
					hash_result_type hash_code_cur = cur->get_cached_hash_code(extract, hash);

					if (hash_code_cur == hash_code) { // same hash
						if (key_equal(extract(cur->member()), key)) { // same key
							return unique_insert_r(static_cast<node_type_unrelated *>(cur), false);
						} // else: same hash but different key => other elements in the same bucket
					} else {
						size_type bucket_id_cur= this->k_hash_result_to_bucket_id(hash_code_cur);
						if (bucket_id_cur != bucket_id_in) {
							bucket_type & bucket_cur = this->k_buckets[bucket_id_cur];
							bucket_cur = p;
							break;
						}
					}
					prev = cur;
					cur = static_cast<node *>(cur->k_next);
				}
				// insert node
				//   hook node on chain
				p->k_next = cur;
				prev->k_next = p;

				++this->k_size;
				return unique_insert_r(static_cast<node_type_unrelated *>(p), true);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::k_rehash_hook_node(Extract & extract, Hash & hash, node * p)
			{
				hash_result_type hash_code = p->get_cached_hash_code(extract, hash);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type & bucket_in = this->k_buckets[bucket_id_in];

				node_type_unrelated * prev = bucket_in;
				node * cur = static_cast<node *>(prev->k_next);
				// insert node
				//   hook node on chain
				p->k_next = cur;
				prev->k_next = p;

				if (cur == NULL) {
					return;
				}
				hash_result_type hash_code_next = cur->get_cached_hash_code(extract, hash);
				size_type bucket_id_next = this->k_hash_result_to_bucket_id(hash_code_next);
				if (bucket_id_in == bucket_id_next) {
					return;
				}
				bucket_type & bucket_next = this->k_buckets[bucket_id_next];
				bucket_next = p;
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::node *
			hash_table_base<Entity, HashCachePolicy>::k_unhook_node(Extract & extract, Hash & hash, node * p)
			{
				hash_result_type hash_code = p->get_cached_hash_code(extract, hash);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type & bucket_in = this->k_buckets[bucket_id_in];

				node_type_unrelated * prev = bucket_in;
				for (node_type_unrelated * cur = prev->k_next; cur != p; ) {
					prev = cur;
					cur = cur->k_next;
				}

				node * next = static_cast<node *>(p->k_next);
				prev->k_next = next;

				bool next_is_diff_bucket = false;
				if (next != NULL) {
					hash_result_type next_hash_code = next->get_cached_hash_code(extract, hash);
					size_type bucket_id_next = this->k_hash_result_to_bucket_id(next_hash_code);
					if (bucket_id_in != bucket_id_next) {
						this->k_buckets[bucket_id_next] = prev;
						next_is_diff_bucket = true;
					}
				} else {
					next_is_diff_bucket = true;
				}

				if (next_is_diff_bucket) {
					if (prev != &this->k_head) {
						node * prev_node = static_cast<node *>(prev);
						hash_result_type prev_hash_code = prev_node->get_cached_hash_code(extract, hash);
						size_type bucket_id_prev = this->k_hash_result_to_bucket_id(prev_hash_code);
						if (bucket_id_in != bucket_id_prev) {
							bucket_in = NULL;
						}
					} else {
						bucket_in = NULL;
					}
				}
				--this->k_size;
				return next;
			}



		//===================
		// Insert

#	if __cplusplus >= 201103L

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename ... Args>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			emplace_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, Args&& ... args)
			{
				KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Hash::result_type, hash_result_type>::value), "should same");

				if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) {
					this->reserve_using_allocator(extract, hash, bucket_alloc, 2 * this->size());
				}

				node * p = k_build_new_node(node_alloc, kerbal::utility::forward<Args>(args)...);
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif
					return this->k_emplace_hook_node(extract, hash, p);
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_destroy_node(node_alloc, p);
					throw;
				}
#			endif
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename ... Args>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::unique_insert_r
			hash_table_base<Entity, HashCachePolicy>::
			emplace_unique_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, Args&& ... args)
			{
				KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Hash::result_type, hash_result_type>::value), "should same");

				if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) {
					this->reserve_using_allocator(extract, hash, bucket_alloc, 2 * this->size());
				}

				node * p = k_build_new_node(node_alloc, kerbal::utility::forward<Args>(args)...);
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif
					unique_insert_r uir(this->k_emplace_hook_node_unique(extract, hash, key_equal, p));
					if (!uir.insert_happen()) {
						k_destroy_node(node_alloc, p);
					}
					return uir;
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_destroy_node(node_alloc, p);
					throw;
				}
#			endif
			}

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
#		define FBODY(i) \
			template <typename Entity, typename HashCachePolicy> \
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename KeyCompare KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename hash_table_base<Entity, HashCachePolicy>::iterator \
			hash_table_base<Entity, HashCachePolicy>::emplace_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Hash::result_type, hash_result_type>::value), "should same"); \
 \
				if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) { \
					this->reserve_using_allocator(extract, hash, bucket_alloc, 2 * this->size()); \
				} \
 \
				node * p = k_build_new_node(node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
 \
				try { \
					return this->k_emplace_hook_node(extract, hash, p); \
				} catch (...) { \
					k_destroy_node(node_alloc, p); \
					throw; \
				} \
			} \
 \
			template <typename Entity, typename HashCachePolicy> \
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename hash_table_base<Entity, HashCachePolicy>::unique_insert_r \
			hash_table_base<Entity, HashCachePolicy>::emplace_unique_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Hash::result_type, hash_result_type>::value), "should same"); \
 \
				if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) { \
					this->reserve_using_allocator(extract, hash, bucket_alloc, 2 * this->size()); \
				} \
 \
				node * p = k_build_new_node(node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
 \
				try { \
					unique_insert_r uir(this->k_emplace_hook_node_unique(extract, hash, key_equal, p)); \
					if (!uir.insert_happen()) { \
						k_destroy_node(node_alloc, p); \
					} \
					return uir; \
				} catch (...) { \
					k_destroy_node(node_alloc, p); \
					throw; \
				} \
			}
#	else
#		define FBODY(i) \
			template <typename Entity, typename HashCachePolicy> \
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename KeyCompare KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename hash_table_base<Entity, HashCachePolicy>::iterator \
			hash_table_base<Entity, HashCachePolicy>::emplace_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Hash::result_type, hash_result_type>::value), "should same"); \
 \
				if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) { \
					this->reserve_using_allocator(extract, hash, bucket_alloc, 2 * this->size()); \
				} \
 \
				node * p = k_build_new_node(node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
 \
				return this->k_emplace_hook_node(extract, hash, p); \
			} \
 \
			template <typename Entity, typename HashCachePolicy> \
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename hash_table_base<Entity, HashCachePolicy>::unique_insert_r \
			hash_table_base<Entity, HashCachePolicy>::emplace_unique_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Hash::result_type, hash_result_type>::value), "should same"); \
 \
				if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) { \
					this->reserve_using_allocator(extract, hash, bucket_alloc, 2 * this->size()); \
				} \
 \
				node * p = k_build_new_node(node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
 \
				unique_insert_r uir(this->k_emplace_hook_node_unique(extract, hash, key_equal, p)); \
				if (!uir.insert_happen()) { \
					k_destroy_node(node_alloc, p); \
				} \
				return uir; \
			}
#	endif

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			insert_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, const_reference src)
			{
				return this->emplace_using_allocator(extract, hash, key_equal, node_alloc, bucket_alloc, src);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::unique_insert_r
			hash_table_base<Entity, HashCachePolicy>::
			insert_unique_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, const_reference src)
			{
				return this->emplace_unique_using_allocator(extract, hash, key_equal, node_alloc, bucket_alloc, src);
			}

		//===================
		// Erase

			template <typename Entity, typename HashCachePolicy>
			template <typename NodeAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			clear_using_allocator(NodeAlloc & node_alloc)
			{
				k_destroy_node_chain(node_alloc, static_cast<node *>(this->k_head.k_next), NULL);
				this->k_head.k_next = NULL;
				this->k_size = 0;
				kerbal::algorithm::fill(this->k_buckets, this->k_buckets + this->k_bucket_count, static_cast<bucket_type>(&this->k_head));
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename NodeAlloc>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			erase_using_allocator(Extract & extract, Hash & hash, NodeAlloc & node_alloc, const_iterator pos)
			{
				if (pos.k_current == NULL) {
					return pos.cast_to_mutable();
				}
				node * p = static_cast<node *>(pos.cast_to_mutable().k_current);
				iterator ret(this->k_unhook_node(extract, hash, p));
				k_destroy_node(node_alloc, p);
				return ret;
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			erase_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, typename Extract::key_type const & key)
			{
				return this->erase_using_allocator(extract, hash, node_alloc, this->find(extract, hash, key_equal, key));
			}

		//===================
		// Lookup

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			find(Extract & extract, Hash & hash, KeyEqual & key_equal, typename Extract::key_type const & key)
			{
				hash_result_type hash_code = hash(key);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type const & bucket_in = this->k_buckets[bucket_id_in];
				if (NULL != bucket_in) {
					node * cur = static_cast<node *>(bucket_in->k_next);
					while (NULL != cur) {
						hash_result_type hash_code_cur = cur->get_cached_hash_code(extract, hash);
						if (hash_code_cur == hash_code) {
							if (key_equal(cur->member(), key)) {
								return iterator(cur);
							}
						} else if (this->k_hash_result_to_bucket_id(hash_code_cur) != bucket_id_in) {
							break;
						}
						cur = static_cast<node *>(cur->k_next);
					}
				}
				return this->end();
			}



		//===================
		// Hash policy

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			void hash_table_base<Entity, HashCachePolicy>::
			k_rehash_unchecked(Extract & extract, Hash & hash, BucketAlloc & bucket_alloc, size_type new_bucket_count) KERBAL_NOEXCEPT
			{
				k_destroy_buckets(bucket_alloc, this->k_buckets, this->k_bucket_count);
				this->k_buckets = this->k_create_buckets(bucket_alloc, new_bucket_count);
				this->k_bucket_count = new_bucket_count;

				node * cur = static_cast<node *>(this->k_head.k_next);
				this->k_head.k_next = NULL;

				while (cur != NULL) {
					node * next = static_cast<node *>(cur->k_next);
					this->k_rehash_hook_node(extract, hash, cur);
					cur = next;
				}

			}



		//===================
		// private

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename hash_table_base<Entity, HashCachePolicy>::size_type
			hash_table_base<Entity, HashCachePolicy>::
			k_first_prime_greater_equal_than(size_type n) KERBAL_NOEXCEPT
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

			template <typename Entity, typename HashCachePolicy>
			template <typename BucketAlloc>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::bucket_type *
			hash_table_base<Entity, HashCachePolicy>::
			k_create_buckets(BucketAlloc & bucket_alloc, size_type new_bucket_count)
			{
				typedef kerbal::memory::allocator_traits<BucketAlloc> bucket_allocator_traits;

				bucket_type * new_buckets = bucket_allocator_traits::allocate(bucket_alloc, new_bucket_count);
				// kerbal::algorithm::fill(new_buckets, new_buckets + new_bucket_count, static_cast<bucket_type>(&this->k_head));
				kerbal::memory::uninitialized_fill(new_buckets, new_buckets + new_bucket_count, static_cast<bucket_type>(&this->k_head));
				return new_buckets;
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename BucketAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			k_destroy_buckets(BucketAlloc & bucket_alloc, bucket_type * buckets, size_type new_bucket_count)
			{
				typedef kerbal::memory::allocator_traits<BucketAlloc> bucket_allocator_traits;

				bucket_allocator_traits::deallocate(bucket_alloc, buckets, new_bucket_count);
			}


#	if __cplusplus >= 201103L

			template <typename Entity, typename HashCachePolicy>
			template <typename NodeAlloc, typename ... Args>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, HashCachePolicy>::node *
			hash_table_base<Entity, HashCachePolicy>::k_build_new_node(NodeAlloc & node_alloc, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits;

				node * p = ht_node_allocator_traits::allocate_one(node_alloc);
#		if !KERBAL_HAS_EXCEPTIONS_SUPPORT
				if (p == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#		endif
					ht_node_allocator_traits::construct(node_alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					ht_node_allocator_traits::deallocate_one(node_alloc, p);
					throw;
				}
#		endif
				return p;
			}

#	else // __cplusplus >= 201103L

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
#		define FBODY(i) \
			template <typename Entity, typename HashCachePolicy> \
			template <typename KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename hash_table_base<Entity, HashCachePolicy>::node * \
			hash_table_base<Entity, HashCachePolicy>::k_build_new_node(NodeAlloc & node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits; \
 \
				node * p = ht_node_allocator_traits::allocate_one(node_alloc); \
 \
				try { \
					ht_node_allocator_traits::construct(node_alloc, p, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				} catch (...) { \
					ht_node_allocator_traits::deallocate_one(node_alloc, p); \
					throw; \
				} \
				return p; \
			}

#	else
#			define FBODY(i) \
			template <typename Entity, typename HashCachePolicy> \
			template <typename KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename hash_table_base<Entity, HashCachePolicy>::node * \
			hash_table_base<Entity, HashCachePolicy>::k_build_new_node(NodeAlloc & node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits; \
 \
				node * p = ht_node_allocator_traits::allocate_one(node_alloc); \
				if (p == NULL) { \
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception(); \
				} \
 \
				ht_node_allocator_traits::construct(node_alloc, p, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				return p; \
			}
#	endif

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif // __cplusplus >= 201103L

			template <typename Entity, typename HashCachePolicy>
			template <typename NodeAlloc>
			KERBAL_CONSTEXPR20
			void hash_table_base<Entity, HashCachePolicy>::
			k_destroy_node(NodeAlloc & node_alloc, node * p) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits;
				ht_node_allocator_traits::destroy(node_alloc, p);
				ht_node_allocator_traits::deallocate_one(node_alloc, p);
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_IMPL_HPP
