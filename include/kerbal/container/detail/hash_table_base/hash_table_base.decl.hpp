/**
 * @file       hash_table_base.decl.hpp
 * @brief
 * @date       2022-03-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_DECL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <cstddef>

#include <kerbal/container/detail/hash_table_base/hash_table_base.fwd.hpp>
#include <kerbal/container/detail/hash_table_base/hash_table_node.hpp>
#include <kerbal/container/detail/hash_table_base/hash_table_iterator.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename HashCachePolicy>
			struct hash_table_base_typedef_helper
			{
					typedef Entity																			value_type;
					typedef kerbal::container::detail::hash_table_node_type_unrelated						node_type_unrelated;
					typedef kerbal::container::detail::hash_table_node_type_only<Entity>					node_type_only;
					typedef typename kerbal::container::detail::hash_table_node<Entity, HashCachePolicy>	node;
					typedef node_type_unrelated *															bucket_type;
			};

			template <typename Entity, typename HashCachePolicy>
			struct hash_table_base_node_size :
					kerbal::type_traits::integral_constant<std::size_t,
						sizeof(
							hash_table_base_typedef_helper<Entity, HashCachePolicy>::node
						)
					>
			{
			};

			template <typename Entity, typename HashCachePolicy>
			class hash_table_base
			{
				private:
					typedef kerbal::container::detail::hash_table_base_typedef_helper<Entity, HashCachePolicy>
																										hash_table_base_typedef_helper;

					template <typename Entity2, typename Extract2, typename Hash, typename NodeAllocatorBR, typename BucketAllocatorBR>
					friend struct hash_table_typedef_helper;

				protected:
					typedef typename hash_table_base_typedef_helper::node_type_unrelated		node_type_unrelated;
					typedef typename hash_table_base_typedef_helper::node_type_only				node_type_only;
					typedef typename hash_table_base_typedef_helper::node						node;
					typedef typename hash_table_base_typedef_helper::bucket_type				bucket_type;

				public:
					typedef Entity								value_type;
					typedef const value_type					const_type;
					typedef value_type &						reference;
					typedef const value_type &					const_reference;
					typedef value_type *						pointer;
					typedef const value_type *					const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type &&						rvalue_reference;
					typedef const value_type &&					const_rvalue_reference;
#			endif

					typedef std::size_t							size_type;
					typedef std::ptrdiff_t						difference_type;

					typedef kerbal::container::detail::hash_table_iter<Entity>						local_iterator;
					typedef kerbal::container::detail::hash_table_kiter<Entity>						const_local_iterator;
					typedef kerbal::container::detail::hash_table_iter<Entity>						iterator;
					typedef kerbal::container::detail::hash_table_kiter<Entity>						const_iterator;
					typedef kerbal::container::associative_unique_insert_r<iterator>				unique_insert_r;

					typedef kerbal::container::detail::hash_cache_policy_traits<HashCachePolicy>		hash_cache_policy_traits;
					typedef typename hash_cache_policy_traits::hash_result_type							hash_result_type;
					typedef typename hash_cache_policy_traits::CACHE_HASH_RESULT						CACHE_HASH_RESULT;

				protected:
					node_type_unrelated		k_head;
					bucket_type *			k_buckets;
					size_type				k_bucket_count;
					size_type				k_size;
					float					k_max_load_factor;

				protected:
					template <typename BucketAlloc>
					KERBAL_CONSTEXPR20
					explicit hash_table_base(BucketAlloc & bucket_alloc);

					template <typename BucketAlloc>
					KERBAL_CONSTEXPR20
					hash_table_base(BucketAlloc & bucket_alloc, size_type bucket_count);

					template <typename NodeAlloc, typename BucketAlloc>
					KERBAL_CONSTEXPR20
					void destroy_using_allocator(NodeAlloc & node_alloc, BucketAlloc & bucket_alloc);

				//===================
				// Iterators

					KERBAL_CONSTEXPR14
					iterator begin() KERBAL_NOEXCEPT
					{
						return iterator(this->k_head.k_next);
					}

					KERBAL_CONSTEXPR14
					const_iterator begin() const KERBAL_NOEXCEPT
					{
						return const_iterator(this->k_head.k_next);
					}

					KERBAL_CONSTEXPR14
					const_iterator cbegin() const KERBAL_NOEXCEPT
					{
						return const_iterator(this->k_head.k_next);
					}

					KERBAL_CONSTEXPR14
					iterator end() KERBAL_NOEXCEPT
					{
						return iterator(NULL);
					}

					KERBAL_CONSTEXPR14
					const_iterator end() const KERBAL_NOEXCEPT
					{
						return const_iterator(NULL);
					}

					KERBAL_CONSTEXPR14
					const_iterator cend() const KERBAL_NOEXCEPT
					{
						return const_iterator(NULL);
					}

				//===================
				// Capacity

					KERBAL_CONSTEXPR
					bool empty() const KERBAL_NOEXCEPT
					{
						return this->size() == 0;
					}

					KERBAL_CONSTEXPR
					size_type size() const KERBAL_NOEXCEPT
					{
						return this->k_size;
					}

					KERBAL_CONSTEXPR
					size_type max_size() const KERBAL_NOEXCEPT
					{
						return kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(node);
					}

				//===================
				// Modifiers

				protected:
					template <typename Extract, typename Hash>
					KERBAL_CONSTEXPR20
					iterator k_emplace_hook_node(Extract & extract, Hash & hash, node * p);

					template <typename Extract, typename Hash, typename KeyEqual>
					KERBAL_CONSTEXPR20
					unique_insert_r k_emplace_hook_node_unique(Extract & extract, Hash & hash, KeyEqual & key_equal, node * p);

					template <typename Extract, typename Hash>
					KERBAL_CONSTEXPR20
					void k_rehash_hook_node(Extract & extract, Hash & hash, node * p);

#		if __cplusplus >= 201103L

					template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename ... Args>
					KERBAL_CONSTEXPR20
					iterator emplace_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, Args&& ... args);

					template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename ... Args>
					KERBAL_CONSTEXPR20
					unique_insert_r emplace_unique_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, Args&& ... args);

#		endif

//					template <typename Extract, typename NodeAlloc, typename BucketAlloc>
//					KERBAL_CONSTEXPR20
//					iterator emplace_using_allocator(Extract & extract, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, const_reference src);
//
//#		if __cplusplus >= 201103L
//
//					template <typename Extract, typename NodeAlloc, typename BucketAlloc>
//					KERBAL_CONSTEXPR20
//					iterator emplace_unique_using_allocator(Extract & extract, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, rvalue_reference src);
//
//#		endif

					template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc>
					KERBAL_CONSTEXPR20
					iterator insert_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, const_reference src);

					template <typename Extract, typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename ... Args>
					KERBAL_CONSTEXPR20
					unique_insert_r insert_unique_using_allocator(Extract & extract, Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, const_reference src);

					template <typename NodeAlloc>
					KERBAL_CONSTEXPR20
					iterator erase_using_allocator(const_iterator pos, NodeAlloc & node_alloc);

					template <typename NodeAlloc>
					KERBAL_CONSTEXPR20
					void clear_using_allocator(NodeAlloc & node_alloc);

				//===================
				// Lookup

					// size_type count(const key_type & key) const;
					//
					// iterator find(const key_type & key);
					//
					// const_iterator find(const key_type & key) const;
					//
					// bool contains(const key_type & key) const;
					//
					// kerbal::utility::compressed_pair<iterator, iterator> equal_range(const key_type & key);
					//
					// kerbal::utility::compressed_pair<const_iterator, const_iterator> equal_range(const key_type & key) const;


				//===================
				// Bucket interface
/*
					KERBAL_CONSTEXPR20
					local_iterator begin(size_type bucket_idx) KERBAL_NOEXCEPT
					{
						return local_iterator(this->K_buckets[bucket_idx]->K_next);
					}

					KERBAL_CONSTEXPR20
					const_local_iterator begin(size_type bucket_idx) const KERBAL_NOEXCEPT
					{
						return const_local_iterator(this->K_buckets[bucket_idx]->K_next);
					}

					KERBAL_CONSTEXPR20
					const_local_iterator cbegin(size_type bucket_idx) const KERBAL_NOEXCEPT
					{
						return const_local_iterator(this->K_buckets[bucket_idx]->K_next);
					}

					KERBAL_CONSTEXPR20
					local_iterator end(size_type bucket_idx) KERBAL_NOEXCEPT
					{
						local_iterator it(this->begin(bucket_idx));
						size_type bucket_cnt = this->bucket_count();
						while (bucket_cnt != 0) {
							--bucket_cnt;
							++it;
						}
						return it;
					}

					KERBAL_CONSTEXPR20
					const_local_iterator end(size_type bucket_idx) const KERBAL_NOEXCEPT
					{
						const_local_iterator it(this->begin(bucket_idx));
						size_type bucket_cnt = this->bucket_count();
						while (bucket_cnt != 0) {
							--bucket_cnt;
							++it;
						}
						return it;
					}

					KERBAL_CONSTEXPR20
					const_local_iterator cend(size_type bucket_idx) const KERBAL_NOEXCEPT
					{
						return this->end(bucket_idx);
					}
*/
					KERBAL_CONSTEXPR
					size_type bucket_count() const KERBAL_NOEXCEPT
					{
						return this->k_bucket_count;
					}

					KERBAL_CONSTEXPR
					size_type max_bucket_count() const KERBAL_NOEXCEPT
					{
						return kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(bucket_type);
					}

					KERBAL_CONSTEXPR14
					size_type bucket_size(size_type bucket_idx) const KERBAL_NOEXCEPT;

					template <typename Hash, typename Key>
					KERBAL_CONSTEXPR14
					size_type bucket(Hash & hash, Key const & key) const KERBAL_NOEXCEPT
					{
						return k_hash_result_to_bucket_id(hash(key));
					}

				private:

					KERBAL_CONSTEXPR
					size_type k_hash_result_to_bucket_id(hash_result_type hash_result) const KERBAL_NOEXCEPT
					{
						return hash_result % this->bucket_count();
					}

				public:

				//===================
				// Hash policy

					KERBAL_CONSTEXPR
					float load_factor() const KERBAL_NOEXCEPT
					{
						return this->size() / float(this->bucket_count());
					}

					KERBAL_CONSTEXPR
					float max_load_factor() const KERBAL_NOEXCEPT
					{
						return this->k_max_load_factor;
					}

					KERBAL_CONSTEXPR14
					void max_load_factor(float mlf) KERBAL_NOEXCEPT
					{
						this->k_max_load_factor = mlf;
					}

					template <typename Extract, typename Hash, typename BucketAlloc>
					KERBAL_CONSTEXPR20
					void reserve_using_allocator(Extract & extract, Hash & hash, BucketAlloc & bucket_alloc, size_type new_size)
					{
						size_type new_bucket_count = k_first_prime_greater_equal_than(new_size / this->max_load_factor());
						this->k_rehash_unchecked(extract, hash, bucket_alloc, new_bucket_count);
					}

					template <typename Extract, typename Hash, typename BucketAlloc>
					KERBAL_CONSTEXPR20
					void k_rehash_unchecked(Extract & extract, Hash & hash, BucketAlloc & bucket_alloc, size_type new_bucket_count) KERBAL_NOEXCEPT;

					template <typename Extract, typename Hash, typename BucketAlloc>
					KERBAL_CONSTEXPR20
					void rehash(Extract & extract, Hash & hash, BucketAlloc & bucket_alloc, size_type new_bucket_count)
					{
						size_type minimum_bucket_count = this->size() / this->max_load_factor();
						this->k_rehash_unchecked(extract, hash, bucket_alloc, new_bucket_count < minimum_bucket_count ? minimum_bucket_count : new_bucket_count);
					}



				//===================
				// private

				private:

					KERBAL_CONSTEXPR14
					static size_type k_first_prime_greater_equal_than(size_type n) KERBAL_NOEXCEPT;

					template <typename BucketAlloc>
					KERBAL_CONSTEXPR20
					bucket_type * k_create_buckets(BucketAlloc & bucket_alloc, size_type new_bucket_count);

					template <typename BucketAlloc>
					KERBAL_CONSTEXPR20
					static void k_destroy_buckets(BucketAlloc & bucket_alloc, bucket_type * buckets, size_type new_bucket_count);

					template <typename BucketAlloc>
					KERBAL_CONSTEXPR20
					void k_init_buckets(BucketAlloc & bucket_alloc, size_type bucket_count = 17)
					{
						this->k_bucket_count = bucket_count;
						this->k_buckets = k_create_buckets(bucket_alloc, bucket_count);
					}

					template <typename Extract, typename Hash>
					KERBAL_CONSTEXPR20
					size_type k_bucket_id_of_front(Extract & extract, Hash & hash)
					{
						node * front_node = static_cast<node *>(this->k_head.k_next);
						hash_result_type front_hash = front_node->get_cached_hash_code(extract, hash);
						return k_hash_result_to_bucket_id(front_hash);
					}

#		if __cplusplus >= 201103L

					template <typename NodeAlloc, typename ... Args>
					KERBAL_CONSTEXPR20
					static node * k_build_new_node(NodeAlloc & node_alloc, Args && ... args);

#		else // __cplusplus >= 201103L

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
#			define FBODY(i) \
					template <typename KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static node * k_build_new_node(NodeAlloc & node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

#		else
#			define FBODY(i) \
					template <typename KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static node * k_build_new_node(NodeAlloc & node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));
#		endif

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif // __cplusplus >= 201103L

					template <typename NodeAlloc>
					KERBAL_CONSTEXPR20
					static void k_destroy_node_chain(NodeAlloc & node_alloc, node_type_unrelated * first, node_type_unrelated * last) KERBAL_NOEXCEPT
					{
						node_type_unrelated * it = first;
						while (it != last) {
							node_type_unrelated * next = it->k_next;
							k_destroy_node(node_alloc, it);
							it = next;
						}
					}

					template <typename NodeAlloc>
					KERBAL_CONSTEXPR20
					static void k_destroy_node(NodeAlloc & node_alloc, node_type_unrelated * p) KERBAL_NOEXCEPT;

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_DECL_HPP
