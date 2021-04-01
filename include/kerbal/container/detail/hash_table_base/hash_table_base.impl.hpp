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
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/is_same.hpp>

#include <kerbal/container/detail/hash_table_base/hash_table_base.decl.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename BucketAlloc>
			KERBAL_CONSTEXPR20
			hash_table_base<Entity, Extract, HashCachePolicy>::
			hash_table_base(BucketAlloc & bucket_alloc) :
					k_size(0),
					k_max_load_factor(1)
			{
				this->k_init_buckets(bucket_alloc);
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename BucketAlloc>
			KERBAL_CONSTEXPR20
			hash_table_base<Entity, Extract, HashCachePolicy>::
			hash_table_base(BucketAlloc & bucket_alloc, size_type bucket_count) :
					k_size(0),
					k_max_load_factor(1)
			{
				this->k_init_buckets(bucket_alloc, k_first_prime_greater_equal_than(bucket_count));
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename NodeAlloc, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, Extract, HashCachePolicy>::
			destroy(NodeAlloc & node_alloc, BucketAlloc & bucket_alloc)
			{
				k_destroy_node_chain(node_alloc, this->k_head.k_next, NULL);
				typedef kerbal::memory::allocator_traits<BucketAlloc> bucket_allocator_traits;
				bucket_allocator_traits::deallocate(bucket_alloc, this->k_buckets, this->k_bucket_count);
			}

		//===================
		// Modifiers

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename Hash>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, Extract, HashCachePolicy>::
			k_hook_node_bucket_empty(Hash & hash, node * p, bucket_type & bucket_in)
			{
				Extract & extract = this->extract();

				if (this->k_head.k_next != NULL) {
					node * first_node = static_cast<node *>(this->k_head.k_next);
					hash_result_type first_node_hash_code = first_node->get_cached_hash_code(extract, hash);
					size_type first_node_bucket_id = k_hash_result_to_bucket_id(first_node_hash_code);
					bucket_type & first_node_bucket_in = this->k_buckets[first_node_bucket_id];
					first_node_bucket_in = p;
				}
				bucket_in = static_cast<node*>(&this->k_head);
				p->k_next = this->k_head.k_next;
				this->k_head.k_next = p;
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, Extract, HashCachePolicy>::
			k_hook_node(Hash & hash, KeyEqual & key_equal, node * p)
			{
				Extract & extract = this->extract();

				const key_type & key = extract(p->member());
				hash_result_type hash_code = hash(key);
				p->set_cached_hash_code(hash_code);
				size_type bucket_id = k_hash_result_to_bucket_id(hash_code);
				bucket_type & bucket_in = this->k_buckets[bucket_id];

				if (bucket_in == NULL) {
					k_hook_node_bucket_empty(hash, p, bucket_in);
				} else {
					node_type_unrelated * prev = bucket_in;
					node * cur = static_cast<node *>(prev->k_next);
					while (cur != NULL) {
						hash_result_type cur_hash_code = cur->get_cached_hash_code(extract, hash);

						if (cur_hash_code == hash_code) { // same hash
							if (key_equal(extract(cur->member()), key)) { // same key
								p->k_next = cur;
								prev->k_next = p;
								break;
							} // else: same hash but different key => other elements in the same bucket
						} else { // different hash
							size_type cur_bucket_id = k_hash_result_to_bucket_id(cur_hash_code);
							if (cur_bucket_id != bucket_id) { // different bucket
								p->k_next = cur;
								prev->k_next = p;
								this->k_buckets[cur_bucket_id] = p;
								break;
							} // else: different hash but same bucket
						}

						prev = cur;
						cur = static_cast<node *>(cur->k_next);
					}
				}
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR20
			bool
			hash_table_base<Entity, Extract, HashCachePolicy>::
			k_hook_node_no_exists(Hash & hash, KeyEqual & key_equal, node * p)
			{
				Extract & extract = this->extract();

				const key_type & key = extract(p->member());
				hash_result_type hash_code = hash(key);
				p->set_cached_hash_code(hash_code);
				size_type bucket_id = k_hash_result_to_bucket_id(hash_code);
				bucket_type & bucket_in = this->k_buckets[bucket_id];

				if (bucket_in == NULL) {
					k_hook_node_bucket_empty(hash, p, bucket_in);
					return true;
				} else {
					node_type_unrelated * prev = bucket_in;
					node * cur = static_cast<node *>(prev->k_next);
					while (cur != NULL) {
						hash_result_type cur_hash_code = cur->get_cached_hash_code(extract, hash);

						if (cur_hash_code == hash_code) { // same hash
							if (key_equal(extract(cur->member()), key)) { // same key
								return false;
							} // else: same hash but different key => other elements in the same bucket
						} else { // different hash
							size_type cur_bucket_id = k_hash_result_to_bucket_id(cur_hash_code);
							if (cur_bucket_id != bucket_id) { // different bucket
								p->k_next = cur;
								prev->k_next = p;
								this->k_buckets[cur_bucket_id] = p;
								return true;
							} // else: different hash but same bucket
						}

						prev = cur;
						cur = static_cast<node *>(cur->k_next);
					}
				}
			}

#	if __cplusplus >= 201103L

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename ... Args>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, Extract, HashCachePolicy>::iterator
			hash_table_base<Entity, Extract, HashCachePolicy>::
			emplace(Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, Args&& ... args)
			{
				KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Hash::result_type, hash_result_type>::value), "should same");

				if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) {
					this->reserve(hash, key_equal, bucket_alloc, 2 * this->size());
				}

				node * p = k_build_new_node(node_alloc, kerbal::utility::forward<Args>(args)...);
				try {
					k_hook_node(hash, key_equal, p);
				} catch (...) {
					k_destroy_node(node_alloc, p);
					throw;
				}
				++this->k_size;
				return iterator(p);
			}

#	endif

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename NodeAlloc>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, Extract, HashCachePolicy>::iterator
			hash_table_base<Entity, Extract, HashCachePolicy>::
			erase(const_iterator pos, NodeAlloc & node_alloc)
			{
				if (pos.k_current == NULL) {
					return pos.cast_to_mutable();
				}



				--this->k_size;
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename NodeAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, Extract, HashCachePolicy>::
			clear(NodeAlloc & node_alloc)
			{
				k_destroy_node_chain(node_alloc, this->k_head.k_next, NULL);
				this->k_head.k_next = NULL;
				this->k_size = 0;
				kerbal::algorithm::fill(this->k_buckets, this->k_buckets + this->k_bucket_count, static_cast<bucket_type>(NULL));
			}



		//===================
		// Hash policy

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename Hash, typename KeyEqual, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			void hash_table_base<Entity, Extract, HashCachePolicy>::
			k_rehash_unchecked(Hash & hash, KeyEqual & key_equal, BucketAlloc & bucket_alloc, size_type new_bucket_count) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<BucketAlloc> bucket_allocator_traits;

				bucket_allocator_traits::deallocate(bucket_alloc, this->k_buckets, this->k_bucket_count);
				this->k_buckets = k_create_new_buckets(bucket_alloc, new_bucket_count);
				this->k_bucket_count = new_bucket_count;

				node * first = static_cast<node *>(this->k_head.k_next);
				this->k_head.k_next = NULL;

				while (first != NULL) {
					node * next = static_cast<node *>(first->k_next);
					k_hook_node(hash, key_equal, first);
					first = next;
				}

			}



		//===================
		// private

			template <typename Entity, typename Extract, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename hash_table_base<Entity, Extract, HashCachePolicy>::size_type
			hash_table_base<Entity, Extract, HashCachePolicy>::
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

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename BucketAlloc>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, Extract, HashCachePolicy>::bucket_type *
			hash_table_base<Entity, Extract, HashCachePolicy>::
			k_create_new_buckets(BucketAlloc & bucket_alloc, size_type new_bucket_count)
			{
				typedef kerbal::memory::allocator_traits<BucketAlloc> bucket_allocator_traits;

				bucket_type * new_buckets = bucket_allocator_traits::allocate(bucket_alloc, new_bucket_count);
				kerbal::algorithm::fill(new_buckets, new_buckets + new_bucket_count, static_cast<bucket_type>(NULL)); // noexcept
				return new_buckets;
			}


#	if __cplusplus >= 201103L

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename NodeAlloc, typename ... Args>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, Extract, HashCachePolicy>::node *
			hash_table_base<Entity, Extract, HashCachePolicy>::k_build_new_node(NodeAlloc & node_alloc, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits;

				node * p = ht_node_allocator_traits::allocate(node_alloc, 1);
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
					ht_node_allocator_traits::deallocate(node_alloc, p, 1);
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
			template <typename Entity, typename Extract, typename HashCachePolicy> \
			template <typename KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename hash_table_base<Entity, Extract, HashCachePolicy>::node * \
			hash_table_base<Entity, Extract, HashCachePolicy>::k_build_new_node(NodeAlloc & node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits; \
 \
				node * p = ht_node_allocator_traits::allocate(node_alloc, 1); \
 \
				try { \
					ht_node_allocator_traits::construct(node_alloc, p, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				} catch (...) { \
					ht_node_allocator_traits::deallocate(node_alloc, p, 1); \
					throw; \
				} \
				return p; \
			}

#	else
#			define FBODY(i) \
			template <typename Entity, typename Extract, typename HashCachePolicy> \
			template <typename KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename hash_table_base<Entity, Extract, HashCachePolicy>::node * \
			hash_table_base<Entity, Extract, HashCachePolicy>::k_build_new_node(NodeAlloc & node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits; \
 \
				node * p = ht_node_allocator_traits::allocate(node_alloc, 1); \
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

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename NodeAlloc>
			KERBAL_CONSTEXPR20
			void hash_table_base<Entity, Extract, HashCachePolicy>::
			k_destroy_node(NodeAlloc & node_alloc, node_type_unrelated * p) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits;
				node * p_to_node = static_cast<node *>(p);
				ht_node_allocator_traits::destroy(node_alloc, p_to_node);
				ht_node_allocator_traits::deallocate(node_alloc, p_to_node, 1);
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_IMPL_HPP
