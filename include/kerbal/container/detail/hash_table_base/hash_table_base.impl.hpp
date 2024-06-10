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
#include <kerbal/assign/assign_list.hpp>
#include <kerbal/compare/minmax.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/uninitialized/construct.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/as_const.hpp>
#include <kerbal/utility/forward.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

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
			KERBAL_CONSTEXPR14
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(BucketAlloc & bucket_alloc) :
				k_size(0),
				k_max_load_factor(1)
			{
				this->k_init_buckets(bucket_alloc);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename BucketAlloc>
			KERBAL_CONSTEXPR14
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(BucketAlloc & bucket_alloc, size_type bucket_count) :
				k_size(0),
				k_max_load_factor(1)
			{
				// this->k_init_buckets(bucket_alloc, k_first_prime_greater_equal_than(bucket_count));
				this->k_init_buckets(bucket_alloc, bucket_count);
			}


			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename InputIterator
			>
			KERBAL_CONSTEXPR14
			void
			hash_table_base<Entity, HashCachePolicy>::
			k_cnstrct_by_range(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				InputIterator first, InputIterator last
			)
			{
				k_hash_check(hash);

				this->k_init_buckets(bucket_alloc, 7);
				while (first != last) {
					this->emplace_using_allocator(
						extract, hash, key_equal,
						node_alloc, bucket_alloc,
						*first
					);
					++first;
				}
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename InputIterator
			>
			KERBAL_CONSTEXPR14
			void
			hash_table_base<Entity, HashCachePolicy>::
			k_cnstrct_unique_by_range(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				InputIterator first, InputIterator last
			)
			{
				k_hash_check(hash);

				this->k_init_buckets(bucket_alloc, 7);
				while (first != last) {
					this->emplace_unique_using_allocator(
						extract, hash, key_equal,
						node_alloc, bucket_alloc,
						*first
					);
					++first;
				}
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename InputIterator
			>
			KERBAL_CONSTEXPR14
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				InputIterator first, InputIterator last
			) :
				k_size(0),
				k_max_load_factor(1)
			{
				k_hash_check(hash);

				this->k_cnstrct_by_range(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					first, last
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename InputIterator
			>
			KERBAL_CONSTEXPR14
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				kerbal::container::unique_tag_t,
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				InputIterator first, InputIterator last
			) :
				k_size(0),
				k_max_load_factor(1)
			{
				k_hash_check(hash);

				this->k_cnstrct_unique_by_range(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					first, last
				);
			}


#	if __cplusplus >=  201103L

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR14
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				std::initializer_list<value_type> ilist
			) :
				hash_table_base(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					ilist.begin(), ilist.end()
				)
			{
				k_hash_check(hash);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR14
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				kerbal::container::unique_tag_t tag,
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				std::initializer_list<value_type> ilist
			) :
				hash_table_base(
					tag,
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					ilist.begin(), ilist.end()
				)
			{
				k_hash_check(hash);
			}

#	else

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				kerbal::assign::assign_list<void> const & ilist
			) :
				k_size(0),
				k_max_load_factor(1)
			{
				k_hash_check(hash);

				this->k_init_buckets(bucket_alloc);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename U
			>
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				kerbal::assign::assign_list<U> const & ilist
			) :
				k_size(0),
				k_max_load_factor(1)
			{
				k_hash_check(hash);

				this->k_cnstrct_by_range(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					ilist.cbegin(), ilist.cend()
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				kerbal::container::unique_tag_t,
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				kerbal::assign::assign_list<void> const & ilist
			) :
				k_size(0),
				k_max_load_factor(1)
			{
				k_hash_check(hash);

				this->k_init_buckets(bucket_alloc);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename U
			>
			hash_table_base<Entity, HashCachePolicy>::
			hash_table_base(
				kerbal::container::unique_tag_t,
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				kerbal::assign::assign_list<U> const & ilist
			) :
				k_size(0),
				k_max_load_factor(1)
			{
				k_hash_check(hash);

				this->k_cnstrct_unique_by_range(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					ilist.cbegin(), ilist.cend()
				);
			}

#	endif


			template <typename Entity, typename HashCachePolicy>
			template <typename NodeAlloc, typename BucketAlloc>
			KERBAL_CONSTEXPR14
			void
			hash_table_base<Entity, HashCachePolicy>::
			destroy_using_allocator(NodeAlloc & node_alloc, BucketAlloc & bucket_alloc)
			{
				k_destroy_node_chain(node_alloc, node::reinterpret_as(this->k_head.k_next), NULL);
				k_destroy_buckets(bucket_alloc, this->k_buckets, this->k_bucket_count);
			}


		//===================
		// Iterators

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename
			hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			begin() KERBAL_NOEXCEPT
			{
				return iterator(this->k_head.k_next);
			}

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR
			typename
			hash_table_base<Entity, HashCachePolicy>::const_iterator
			hash_table_base<Entity, HashCachePolicy>::
			begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_head.k_next);
			}

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR
			typename
			hash_table_base<Entity, HashCachePolicy>::const_iterator
			hash_table_base<Entity, HashCachePolicy>::
			cbegin() const KERBAL_NOEXCEPT
			{
				return this->begin();
			}

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename
			hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			end() KERBAL_NOEXCEPT
			{
				return iterator(NULL);
			}

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR
			typename
			hash_table_base<Entity, HashCachePolicy>::const_iterator
			hash_table_base<Entity, HashCachePolicy>::
			end() const KERBAL_NOEXCEPT
			{
				return const_iterator(NULL);
			}

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR
			typename
			hash_table_base<Entity, HashCachePolicy>::const_iterator
			hash_table_base<Entity, HashCachePolicy>::
			cend() const KERBAL_NOEXCEPT
			{
				return this->end();
			}


		//===================
		// Capacity

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR
			bool
			hash_table_base<Entity, HashCachePolicy>::
			empty() const KERBAL_NOEXCEPT
			{
				return this->size() == 0;
			}

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR
			typename
			hash_table_base<Entity, HashCachePolicy>::size_type
			hash_table_base<Entity, HashCachePolicy>::
			size() const KERBAL_NOEXCEPT
			{
				return this->k_size;
			}

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR
			typename
			hash_table_base<Entity, HashCachePolicy>::size_type
			hash_table_base<Entity, HashCachePolicy>::
			max_size() const KERBAL_NOEXCEPT
			{
				return kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(node);
			}


		//===================
		// Lookup

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR14
			bool
			hash_table_base<Entity, HashCachePolicy>::
			contains(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				typename Extract::key_type const & key
			) const
			{
				k_hash_check(hash);
				return this->find(extract, hash, key_equal, key) != this->cend();
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR14
			typename
			hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			find(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				typename Extract::key_type const & key
			)
			{
				k_hash_check(hash);
				return kerbal::utility::as_const(*this).find(extract, hash, key_equal, key).cast_to_mutable();
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR14
			typename
			hash_table_base<Entity, HashCachePolicy>::const_iterator
			hash_table_base<Entity, HashCachePolicy>::
			find(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				typename Extract::key_type const & key
			) const
			{
				k_hash_check(hash);

				hash_result_type hash_code = hash(key);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type const & bucket_in = this->k_buckets[bucket_id_in];
				node * cur = node::reinterpret_as(bucket_in->k_next);
				while (NULL != cur) {
					hash_result_type hash_code_cur = cur->get_cached_hash_code(extract, hash);
					if (hash_code_cur == hash_code) {
						if (key_equal(extract(cur->member()), key)) {
							return const_iterator(cur);
						}
					} else if (this->k_hash_result_to_bucket_id(hash_code_cur) != bucket_id_in) {
						break;
					}
					cur = node::reinterpret_as(cur->k_next);
				}
				return this->end();
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<
				typename hash_table_base<Entity, HashCachePolicy>::iterator,
				typename hash_table_base<Entity, HashCachePolicy>::iterator
			>
			hash_table_base<Entity, HashCachePolicy>::
			equal_range(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				typename Extract::key_type const & key
			)
			{
				k_hash_check(hash);
				kerbal::utility::compressed_pair<const_iterator, const_iterator> eqr(
					kerbal::utility::as_const(*this).equal_range(
						extract, hash, key_equal,
						key
					)
				);
				return kerbal::utility::make_compressed_pair(
					eqr.first().cast_to_mutable(),
					eqr.second().cast_to_mutable()
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<
				typename hash_table_base<Entity, HashCachePolicy>::const_iterator,
				typename hash_table_base<Entity, HashCachePolicy>::const_iterator
			>
			hash_table_base<Entity, HashCachePolicy>::
			equal_range(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				typename Extract::key_type const & key
			) const
			{
				k_hash_check(hash);

				hash_result_type hash_code = hash(key);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type const & bucket_in = this->k_buckets[bucket_id_in];
				node * cur = node::reinterpret_as(bucket_in->k_next);
				while (NULL != cur) {
					hash_result_type hash_code_cur = cur->get_cached_hash_code(extract, hash);
					if (hash_code_cur == hash_code) {
						if (key_equal(extract(cur->member()), key)) {
							const_iterator first(cur);
							cur = node::reinterpret_as(cur->k_next);
							while (NULL != cur) {
								if (!static_cast<bool>(key_equal(extract(cur->member()), key))) {
									break;
								}
								cur = node::reinterpret_as(cur->k_next);
							}
							const_iterator last(cur);
							return kerbal::utility::make_compressed_pair(
								first, last
							);
						}
					} else if (this->k_hash_result_to_bucket_id(hash_code_cur) != bucket_id_in) {
						break;
					}
					cur = node::reinterpret_as(cur->k_next);
				}
				return kerbal::utility::make_compressed_pair(
					this->cend(),
					this->cend()
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR14
			typename
			hash_table_base<Entity, HashCachePolicy>::size_type
			hash_table_base<Entity, HashCachePolicy>::
			count(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				typename Extract::key_type const & key
			) const
			{
				k_hash_check(hash);

				hash_result_type hash_code = hash(key);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type const & bucket_in = this->k_buckets[bucket_id_in];
				node * cur = node::reinterpret_as(bucket_in->k_next);
				while (NULL != cur) {
					hash_result_type hash_code_cur = cur->get_cached_hash_code(extract, hash);
					if (hash_code_cur == hash_code) {
						if (key_equal(extract(cur->member()), key)) {
							size_type cnt = 1;
							cur = node::reinterpret_as(cur->k_next);
							while (NULL != cur) {
								if (!static_cast<bool>(key_equal(extract(cur->member()), key))) {
									break;
								}
								++cnt;
								cur = node::reinterpret_as(cur->k_next);
							}
							return cnt;
						}
					} else if (this->k_hash_result_to_bucket_id(hash_code_cur) != bucket_id_in) {
						break;
					}
					cur = node::reinterpret_as(cur->k_next);
				}
				return 0;
			}


		//===================
		// Node Hook/Unhook

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR14
			typename
			hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			k_emplace_hook_node(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				node * p
			)
			{
				k_hash_check(hash);

				typedef typename Extract::key_type key_type;

				const key_type & key = extract(p->member());
				hash_result_type hash_code = p->get_cached_hash_code(extract, hash);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type & bucket_in = this->k_buckets[bucket_id_in];

				node_type_unrelated * prev = bucket_in;
				node * cur = node::reinterpret_as(prev->k_next);
				while (NULL != cur) {
					hash_result_type hash_code_cur = cur->get_cached_hash_code(extract, hash);

					if (hash_code_cur == hash_code) { // same hash
						if (key_equal(extract(cur->member()), key)) { // same key
							break;
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
					cur = node::reinterpret_as(cur->k_next);
				}
				// insert node
				//   hook node on chain
				p->k_next = cur;
				prev->k_next = p;

				++this->k_size;
				return iterator(p);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual>
			KERBAL_CONSTEXPR14
			typename
			hash_table_base<Entity, HashCachePolicy>::unique_insert_r
			hash_table_base<Entity, HashCachePolicy>::
			k_emplace_hook_node_unique(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				node * p
			)
			{
				k_hash_check(hash);

				typedef typename Extract::key_type key_type;

				const key_type & key = extract(p->member());
				hash_result_type hash_code = p->get_cached_hash_code(extract, hash);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type & bucket_in = this->k_buckets[bucket_id_in];

				node_type_unrelated * prev = bucket_in;
				node * cur = node::reinterpret_as(prev->k_next);
				while (NULL != cur) {
					hash_result_type hash_code_cur = cur->get_cached_hash_code(extract, hash);

					if (hash_code_cur == hash_code) { // same hash
						if (key_equal(extract(cur->member()), key)) { // same key
							return unique_insert_r(iterator(cur), false);
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
					cur = node::reinterpret_as(cur->k_next);
				}
				// insert node
				//   hook node on chain
				p->k_next = cur;
				prev->k_next = p;

				++this->k_size;
				return unique_insert_r(iterator(p), true);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash>
			KERBAL_CONSTEXPR14
			void
			hash_table_base<Entity, HashCachePolicy>::
			k_rehash_hook_node(
				Extract & extract, Hash & hash,
				node * p
			)
			{
				k_hash_check(hash);

				hash_result_type hash_code = p->get_cached_hash_code(extract, hash);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type & bucket_in = this->k_buckets[bucket_id_in];

				node_type_unrelated * prev = bucket_in;
				node * cur = node::reinterpret_as(prev->k_next);
				// insert node
				//   hook node on chain
				p->k_next = cur;
				prev->k_next = p;

				if (NULL == cur) {
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


//			template <typename Entity, typename HashCachePolicy>
//			template <typename Extract, typename Hash>
//			KERBAL_CONSTEXPR14
//			bool
//			hash_table_base<Entity, HashCachePolicy>::
//			next_is_diff_bucket(Extract & extract, Hash & hash, node * prev, node * next)
//			{
//				k_hash_check(hash);
//				if (NULL == next) {
//					return true;
//				}
//
//				hash_result_type next_hash_code = next->get_cached_hash_code(extract, hash);
//				size_type bucket_id_next = this->k_hash_result_to_bucket_id(next_hash_code);
//				if (bucket_id_in != bucket_id_next) {
//					this->k_buckets[bucket_id_next] = prev;
//					return true;
//				}
//
//				return false;
//			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash>
			KERBAL_CONSTEXPR14
			typename
			hash_table_base<Entity, HashCachePolicy>::node *
			hash_table_base<Entity, HashCachePolicy>::
			k_unhook_node(Extract & extract, Hash & hash, node * p)
			{
				k_hash_check(hash);

				hash_result_type hash_code = p->get_cached_hash_code(extract, hash);
				size_type bucket_id_in = this->k_hash_result_to_bucket_id(hash_code);
				bucket_type & bucket_in = this->k_buckets[bucket_id_in];

				node_type_unrelated * prev = bucket_in;
				for (node_type_unrelated * cur = prev->k_next; cur != p; ) {
					prev = cur;
					cur = cur->k_next;
				}

				node * next = node::reinterpret_as(p->k_next);
				prev->k_next = next;

				bool next_is_diff_bucket = false;
				if (NULL != next) {
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
					if (&this->k_head != prev) {
						node * prev_node = node::reinterpret_as(prev);
						hash_result_type prev_hash_code = prev_node->get_cached_hash_code(extract, hash);
						size_type bucket_id_prev = this->k_hash_result_to_bucket_id(prev_hash_code);
						if (bucket_id_in != bucket_id_prev) {
							bucket_in = &this->k_head;
						}
					} else {
						bucket_in = &this->k_head;
					}
				}
				--this->k_size;
				return next;
			}


		//===================
		// Insert

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			k_emplace_aux(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				node * p
			)
			{

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif
					this->k_emplace_hook_node(extract, hash, key_equal, p);
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_destroy_node(node_alloc, p);
					throw;
				}
#			endif

				if (this->size() > this->bucket_count() * this->max_load_factor()) {
					this->reserve_using_allocator(extract, hash, bucket_alloc, 2 * this->size());
				}

				return iterator(p);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::unique_insert_r
			hash_table_base<Entity, HashCachePolicy>::
			k_emplace_unique_aux(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				node * p
			)
			{
				bool insert_happen = false;

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif
					unique_insert_r uir(this->k_emplace_hook_node_unique(extract, hash, key_equal, p));
					insert_happen = uir.insert_happen();
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_destroy_node(node_alloc, p);
					throw;
				}
#			endif

				if (insert_happen) {
					if (this->size() > this->bucket_count() * this->max_load_factor()) {
						this->reserve_using_allocator(extract, hash, bucket_alloc, 2 * this->size());
					}
				} else {
					k_destroy_node(node_alloc, p);
				}
				return unique_insert_r(iterator(p), insert_happen);
			}

#	if __cplusplus >= 201103L

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename ... Args
			>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			emplace_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				Args && ... args
			)
			{
				k_hash_check(hash);

				node * p = k_build_new_node(node_alloc, kerbal::utility::forward<Args>(args)...);
				return this->k_emplace_aux(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					p
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename ... Args
			>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::unique_insert_r
			hash_table_base<Entity, HashCachePolicy>::
			emplace_unique_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				Args && ... args
			)
			{
				k_hash_check(hash);

				node * p = k_build_new_node(node_alloc, kerbal::utility::forward<Args>(args)...);
				return this->k_emplace_unique_aux(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					p
				);
			}

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) KERBAL_MACRO_CONCAT(Arg, i) const & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename Entity, typename HashCachePolicy> \
			template < \
				typename Extract, typename Hash, typename KeyEqual, \
				typename NodeAlloc, typename BucketAlloc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
			> \
			typename \
			hash_table_base<Entity, HashCachePolicy>::iterator \
			hash_table_base<Entity, HashCachePolicy>:: \
			emplace_using_allocator( \
				Extract & extract, Hash & hash, KeyEqual & key_equal, \
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
			) \
			{ \
				k_hash_check(hash); \
 \
				node * p = k_build_new_node( \
					node_alloc \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
				); \
				return this->k_emplace_aux( \
					extract, hash, key_equal, \
					node_alloc, bucket_alloc, \
					p \
				); \
			} \
 \
			template <typename Entity, typename HashCachePolicy> \
			template < \
				typename Extract, typename Hash, typename KeyEqual, \
				typename NodeAlloc, typename BucketAlloc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
			> \
			typename \
			hash_table_base<Entity, HashCachePolicy>::unique_insert_r \
			hash_table_base<Entity, HashCachePolicy>:: \
			emplace_unique_using_allocator( \
				Extract & extract, Hash & hash, KeyEqual & key_equal, \
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
			) \
			{ \
				k_hash_check(hash); \
 \
				node * p = k_build_new_node( \
					node_alloc \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
				); \
				return this->k_emplace_unique_aux( \
					extract, hash, key_equal, \
					node_alloc, bucket_alloc, \
					p \
				); \
			} \

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
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			insert_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				const_reference src
			)
			{
				k_hash_check(hash);
				return this->emplace_using_allocator(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					src
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::unique_insert_r
			hash_table_base<Entity, HashCachePolicy>::
			insert_unique_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				const_reference src
			)
			{
				k_hash_check(hash);
				return this->emplace_unique_using_allocator(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					src
				);
			}


#	if __cplusplus >= 201103L

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			insert_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				rvalue_reference src
			)
			{
				k_hash_check(hash);
				return this->emplace_using_allocator(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					kerbal::compatibility::move(src)
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::unique_insert_r
			hash_table_base<Entity, HashCachePolicy>::
			insert_unique_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				rvalue_reference src
			)
			{
				k_hash_check(hash);
				return this->emplace_unique_using_allocator(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					kerbal::compatibility::move(src)
				);
			}

#	endif // if __cplusplus >= 201103L

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename InputIterator
			>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
			>::type
			hash_table_base<Entity, HashCachePolicy>::
			insert_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				InputIterator first, InputIterator last
			)
			{
				k_hash_check(hash);
				while (first != last) {
					this->emplace_using_allocator(
						extract, hash, key_equal,
						node_alloc, bucket_alloc,
						*first
					);
					++first;
				}
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename InputIterator
			>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
			>::type
			hash_table_base<Entity, HashCachePolicy>::
			insert_unique_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				InputIterator first, InputIterator last
			)
			{
				k_hash_check(hash);
				while (first != last) {
					this->emplace_unique_using_allocator(
						extract, hash, key_equal,
						node_alloc, bucket_alloc,
						*first
					);
					++first;
				}
			}

#	if __cplusplus >= 201103L

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			insert_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				std::initializer_list<value_type> ilist
			)
			{
				k_hash_check(hash);
				this->insert_using_allocator(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					ilist.begin(), ilist.end()
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			insert_unique_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				std::initializer_list<value_type> ilist
			)
			{
				k_hash_check(hash);
				this->insert_unique_using_allocator(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					ilist.begin(), ilist.end()
				);
			}

#	else // if __cplusplus >= 201103L

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			insert_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				kerbal::assign::assign_list<void> const & ilist
			)
			{
				k_hash_check(hash);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename U
			>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			insert_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				kerbal::assign::assign_list<U> const & ilist
			)
			{
				k_hash_check(hash);
				this->insert_using_allocator(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					ilist.cbegin(), ilist.cend()
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc
			>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			insert_unique_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				kerbal::assign::assign_list<void> const & ilist
			)
			{
				k_hash_check(hash);
			}

			template <typename Entity, typename HashCachePolicy>
			template <
				typename Extract, typename Hash, typename KeyEqual,
				typename NodeAlloc, typename BucketAlloc,
				typename U
			>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			insert_unique_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, BucketAlloc & bucket_alloc,
				kerbal::assign::assign_list<U> const & ilist
			)
			{
				k_hash_check(hash);
				this->insert_unique_using_allocator(
					extract, hash, key_equal,
					node_alloc, bucket_alloc,
					ilist.cbegin(), ilist.cend()
				);
			}

#	endif // if __cplusplus >= 201103L



		//===================
		// Erase

			template <typename Entity, typename HashCachePolicy>
			template <typename NodeAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			clear_using_allocator(NodeAlloc & node_alloc) KERBAL_NOEXCEPT
			{
				k_destroy_node_chain(node_alloc, node::reinterpret_as(this->k_head.k_next), NULL);
				this->k_head.k_next = NULL;
				this->k_size = 0;
				kerbal::algorithm::fill(
					this->k_buckets,
					this->k_buckets + this->k_bucket_count,
					static_cast<bucket_type>(&this->k_head)
				);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename NodeAlloc>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::iterator
			hash_table_base<Entity, HashCachePolicy>::
			erase_using_allocator(
				Extract & extract, Hash & hash,
				NodeAlloc & node_alloc,
				const_iterator pos
			) KERBAL_NOEXCEPT
			{
				k_hash_check(hash);
				if (NULL == pos.k_current) {
					return pos.cast_to_mutable();
				}
				node * p = node::reinterpret_as(pos.cast_to_mutable().k_current);
				iterator ret(this->k_unhook_node(extract, hash, p));
				k_destroy_node(node_alloc, p);
				return ret;
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename NodeAlloc>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::size_type
			hash_table_base<Entity, HashCachePolicy>::
			erase_using_allocator(
				Extract & extract, Hash & hash, NodeAlloc & node_alloc,
				const_iterator first, const_iterator last
			) KERBAL_NOEXCEPT
			{
				k_hash_check(hash);
				size_type cnt = 0;
				while (first != last) {
					node * p = node::reinterpret_as(first.cast_to_mutable().k_current);
					first = const_iterator(this->k_unhook_node(extract, hash, p));
					k_destroy_node(node_alloc, p);
					++cnt;
				}
				return cnt;
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc>
			KERBAL_CONSTEXPR20
			typename
			hash_table_base<Entity, HashCachePolicy>::size_type
			hash_table_base<Entity, HashCachePolicy>::
			erase_using_allocator(
				Extract & extract, Hash & hash, KeyEqual & key_equal,
				NodeAlloc & node_alloc, typename Extract::key_type const & key
			) KERBAL_NOEXCEPT
			{
				k_hash_check(hash);
				kerbal::utility::compressed_pair<const_iterator, const_iterator> er(
					this->equal_range(
						extract, hash, key_equal,
						key
					)
				);
				return this->erase_using_allocator(
					extract, hash,
					node_alloc,
					er.first(), er.second()
				);
			}


		//===================
		// Hash policy

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			reserve_using_allocator(
				Extract & extract, Hash & hash,
				BucketAlloc & bucket_alloc,
				size_type new_size
			)
			{
				k_hash_check(hash);
				size_type new_bucket_count = k_first_prime_greater_equal_than(new_size / this->max_load_factor());
				this->k_rehash_unchecked(extract, hash, bucket_alloc, new_bucket_count);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			k_rehash_unchecked(
				Extract & extract, Hash & hash,
				BucketAlloc & bucket_alloc,
				size_type new_bucket_count
			)
			{
				k_hash_check(hash);
				if (0 == new_bucket_count) {
					new_bucket_count = 1;
				}

				bucket_type * old_buckets = this->k_buckets;
				size_type old_bucket_count = this->k_bucket_count;
				this->k_buckets = this->k_create_buckets(bucket_alloc, new_bucket_count);
				this->k_bucket_count = new_bucket_count;
				k_destroy_buckets(bucket_alloc, old_buckets, old_bucket_count);

				node * cur = node::reinterpret_as(this->k_head.k_next);
				this->k_head.k_next = NULL;

				while (NULL != cur) {
					node * next = node::reinterpret_as(cur->k_next);
					this->k_rehash_hook_node(extract, hash, cur);
					cur = next;
				}
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename Extract, typename Hash, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			rehash(
				Extract & extract, Hash & hash,
				BucketAlloc & bucket_alloc,
				size_type new_bucket_count
			)
			{
				k_hash_check(hash);
				size_type minimum_bucket_count = this->size() / this->max_load_factor();
				this->k_rehash_unchecked(
					extract, hash,
					bucket_alloc,
					kerbal::compare::max(new_bucket_count, minimum_bucket_count)
				);
			}



		//===================
		// Private

			template <typename Entity, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename
			hash_table_base<Entity, HashCachePolicy>::size_type
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
			typename
			hash_table_base<Entity, HashCachePolicy>::bucket_type *
			hash_table_base<Entity, HashCachePolicy>::
			k_create_buckets(BucketAlloc & bucket_alloc, size_type new_bucket_count)
			{
				typedef kerbal::memory::allocator_traits<BucketAlloc> bucket_allocator_traits;

				bucket_type * new_buckets = bucket_allocator_traits::allocate(bucket_alloc, new_bucket_count);
//				kerbal::algorithm::fill(
//					new_buckets,
//					new_buckets + new_bucket_count,
//					static_cast<bucket_type>(&this->k_head)
//				);
				kerbal::memory::uninitialized_fill(
					new_buckets,
					new_buckets + new_bucket_count,
					static_cast<bucket_type>(&this->k_head)
				);
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
			typename
			hash_table_base<Entity, HashCachePolicy>::node *
			hash_table_base<Entity, HashCachePolicy>::
			k_build_new_node(NodeAlloc & node_alloc, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits;

				node * p = ht_node_allocator_traits::allocate_one(node_alloc);
#		if !KERBAL_HAS_EXCEPTIONS_SUPPORT
				if (NULL == p) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#		endif
					ht_node_allocator_traits::construct(
						node_alloc, p,
						kerbal::utility::in_place_t(),
						kerbal::utility::forward<Args>(args)...
					);
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
#		define ARGS_DECL(i) KERBAL_MACRO_CONCAT(Arg, i) const & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

#		define FBODY(i) \
			template <typename Entity, typename HashCachePolicy> \
			template < \
				typename NodeAlloc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
			> \
			typename \
			hash_table_base<Entity, HashCachePolicy>::node * \
			hash_table_base<Entity, HashCachePolicy>:: \
			k_build_new_node( \
				NodeAlloc & node_alloc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
			) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits; \
 \
				node * p = ht_node_allocator_traits::allocate_one(node_alloc); \
 \
				try { \
					ht_node_allocator_traits::construct( \
						node_alloc, p, \
						kerbal::utility::in_place_t() \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
					); \
				} catch (...) { \
					ht_node_allocator_traits::deallocate_one(node_alloc, p); \
					throw; \
				} \
				return p; \
			} \

#	else

#			define FBODY(i) \
			template <typename Entity, typename HashCachePolicy> \
			template < \
				typename NodeAlloc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
			> \
			typename \
			hash_table_base<Entity, HashCachePolicy>::node * \
			hash_table_base<Entity, HashCachePolicy>:: \
			k_build_new_node( \
				NodeAlloc & node_alloc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
			) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits; \
 \
				node * p = ht_node_allocator_traits::allocate_one(node_alloc); \
				if (NULL == p) { \
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception(); \
				} \
 \
				ht_node_allocator_traits::construct( \
					node_alloc, p, \
					kerbal::utility::in_place_t() \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
				); \
				return p; \
			} \

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
			void
			hash_table_base<Entity, HashCachePolicy>::
			k_destroy_node(NodeAlloc & node_alloc, node * p) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits;
				ht_node_allocator_traits::destroy(node_alloc, p);
				ht_node_allocator_traits::deallocate_one(node_alloc, p);
			}

			template <typename Entity, typename HashCachePolicy>
			template <typename NodeAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, HashCachePolicy>::
			k_destroy_node_chain(NodeAlloc & node_alloc, node * first, node * last) KERBAL_NOEXCEPT
			{
				node * it = first;
				while (it != last) {
					node_type_unrelated * next = it->k_next;
					k_destroy_node(node_alloc, it);
					it = node::reinterpret_as(next);
				}
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_IMPL_HPP
