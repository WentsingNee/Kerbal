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

#ifndef KERBAL_CONTAINER_DETAIL_IMPL_HASH_TABLE_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_IMPL_HASH_TABLE_BASE_IMPL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
//#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/allocator_traits.hpp>
//#include <kerbal/type_traits/enable_if.hpp>
//#include <kerbal/type_traits/integral_constant.hpp>

#include <kerbal/container/detail/decl/hash_table_base.decl.hpp>


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
					_K_size(0),
					_K_max_load_factor(1)
			{
				this->k_init_buckets(bucket_alloc);
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename BucketAlloc>
			KERBAL_CONSTEXPR20
			hash_table_base<Entity, Extract, HashCachePolicy>::
			hash_table_base(BucketAlloc & bucket_alloc, size_type bucket_count) :
					_K_size(0),
					_K_max_load_factor(1)
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
				typedef kerbal::memory::allocator_traits<BucketAlloc> bucket_allocator_traits;

				for (size_type i = 0; i < this->_K_bucket_count; ++i) {
					bucket_type & bucket_to_clear = this->_K_buckets[i];
					bucket_to_clear.clear_using_allocator(node_alloc);
					bucket_allocator_traits::destroy(bucket_alloc, &bucket_to_clear);
				}
				bucket_allocator_traits::deallocate(bucket_alloc, this->_K_buckets, this->_K_bucket_count);
			}

		//===================
		// Iterators

			template <typename Entity, typename Extract, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename hash_table_base<Entity, Extract, HashCachePolicy>::iterator
			hash_table_base<Entity, Extract, HashCachePolicy>::
			begin() KERBAL_NOEXCEPT
			{
				return iterator(_K_buckets, _K_buckets + _K_bucket_count, local_iterator(_K_buckets->begin()));
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename hash_table_base<Entity, Extract, HashCachePolicy>::const_iterator
			hash_table_base<Entity, Extract, HashCachePolicy>::
			begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(_K_buckets, _K_buckets + _K_bucket_count, const_local_iterator(_K_buckets->begin()));
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename hash_table_base<Entity, Extract, HashCachePolicy>::const_iterator
			hash_table_base<Entity, Extract, HashCachePolicy>::
			cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(_K_buckets, _K_buckets + _K_bucket_count, const_local_iterator(_K_buckets->begin()));
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename hash_table_base<Entity, Extract, HashCachePolicy>::iterator
			hash_table_base<Entity, Extract, HashCachePolicy>::
			end() KERBAL_NOEXCEPT
			{
				bucket_type * end_bucket = _K_buckets + _K_bucket_count;
				return iterator(end_bucket, end_bucket, local_iterator(_K_buckets->end()));
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename hash_table_base<Entity, Extract, HashCachePolicy>::const_iterator
			hash_table_base<Entity, Extract, HashCachePolicy>::
			end() const KERBAL_NOEXCEPT
			{
				bucket_type * end_bucket = _K_buckets + _K_bucket_count;
				return const_iterator(end_bucket, end_bucket, const_local_iterator(_K_buckets->end()));
			}

			template <typename Entity, typename Extract, typename HashCachePolicy>
			KERBAL_CONSTEXPR14
			typename hash_table_base<Entity, Extract, HashCachePolicy>::const_iterator
			hash_table_base<Entity, Extract, HashCachePolicy>::
			cend() const KERBAL_NOEXCEPT
			{
				bucket_type * end_bucket = _K_buckets + _K_bucket_count;
				return const_iterator(end_bucket, end_bucket, const_local_iterator(_K_buckets->end()));
			}


		//===================
		// Modifiers

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename KeyEqual>
			std::pair<
				typename hash_table_base<Entity, Extract, HashCachePolicy>::const_local_iterator,
				bool
			>
			hash_table_base<Entity, Extract, HashCachePolicy>::
			k_determine_insert_pos(const key_type & key, KeyEqual & key_equal, bucket_type & bucket_in) KERBAL_NOEXCEPT
			{
				Extract extract = this->extract();

				const_local_iterator before_it(bucket_in.cbefore_begin());
				const_local_iterator it(bucket_in.cbegin());
				const_local_iterator end(bucket_in.cend());

				while (it != end) {
					if (key_equal(extract(*it), key)) { // *it == key
						return std::pair<const_local_iterator, bool>(before_it, true);
					}
					before_it = it;
					++it;
				}

				return std::pair<const_local_iterator, bool>(bucket_in.cbefore_begin(), false);
			}

#	if __cplusplus >= 201103L

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename Hash, typename KeyEqual, typename NodeAlloc, typename BucketAlloc, typename ... Args>
			typename hash_table_base<Entity, Extract, HashCachePolicy>::iterator
			hash_table_base<Entity, Extract, HashCachePolicy>::
			emplace(Hash & hash, KeyEqual & key_equal, NodeAlloc & node_alloc, BucketAlloc & bucket_alloc, Args&& ... args)
			{
				if (this->size() + 1 > this->bucket_count() * this->max_load_factor()) {
					this->reserve(hash, bucket_alloc, 2 * this->size());
				}

				Extract extract = this->extract();

				hash_table_node * p = k_build_new_hash_node(node_alloc, kerbal::utility::forward<Args>(args)...);
				try {
					const key_type & key = extract(p->value);
					typename Hash::result_type hash_code = hash(key);
					p->set_cached_hash_code(hash_code);
					size_type bucket_id = hash_code % this->bucket_count();
					bucket_type & bucket_in = this->_K_buckets[bucket_id];

					const_local_iterator pos(this->k_determine_insert_pos(key, key_equal, bucket_in).first);

					bucket_in._K_hook_node_after(pos, p);
					++this->_K_size;
					return iterator(this->_K_buckets + bucket_id, this->_K_buckets + this->_K_bucket_count, pos.cast_to_mutable());
				} catch (...) {
					k_destroy_hash_node(node_alloc, p);
					throw;
				}
			}

#	endif

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename NodeAlloc>
			KERBAL_CONSTEXPR20
			void
			hash_table_base<Entity, Extract, HashCachePolicy>::
			clear(NodeAlloc & node_alloc)
			{
				for (size_type i = 0; i < this->_K_bucket_count; ++i) {
					bucket_type & bucket_to_clear = this->_K_buckets[i];
					bucket_to_clear.clear_using_allocator(node_alloc);
				}
				this->_K_size = 0;
			}



		//===================
		// Hash policy

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename Hash, typename BucketAlloc>
			KERBAL_CONSTEXPR20
			void hash_table_base<Entity, Extract, HashCachePolicy>::
			k_rehash_unchecked(Hash & hash, BucketAlloc & bucket_alloc, size_type new_bucket_count)
			{
				typedef kerbal::memory::allocator_traits<BucketAlloc> bucket_allocator_traits;

				bucket_type * new_buckets = k_create_new_buckets(bucket_alloc, new_bucket_count);

				for (size_type i = 0; i < this->_K_bucket_count; ++i) {
					bucket_type & bucket_clear = this->_K_buckets[i];
					local_iterator it(bucket_clear.begin());
					local_iterator end(bucket_clear.end());
					while (it != end) {
						hash_table_node * eq_front = static_cast<hash_table_node*>(it.current);
						hash_table_node * eq_back = eq_front;
						++it;
						while (it != end) {
							hash_table_node * ht_node = static_cast<hash_table_node*>(it.current);
							if (!static_cast<bool>(ht_node->value == eq_front->value)) {
								break;
							}
							eq_back = ht_node;
							++it;
						}
						bucket_type & bucket_in = new_buckets[eq_front->get_cached_hash_code(hash) % new_bucket_count];
						bucket_in.bucket_type::fl_type_unrelated::_K_hook_node_after(bucket_in.before_begin(), eq_front, eq_back);
					}
					bucket_clear.head_node.next = NULL;
					bucket_allocator_traits::destroy(bucket_alloc, &bucket_clear);
				}
				bucket_allocator_traits::deallocate(bucket_alloc, this->_K_buckets, this->_K_bucket_count);

				this->_K_buckets = new_buckets;
				this->_K_bucket_count = new_bucket_count;
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
				for (size_type i = 0; i < new_bucket_count; ++i) {
					bucket_allocator_traits::construct(bucket_alloc, &new_buckets[i]);
				}
				return new_buckets;
			}


#	if __cplusplus >= 201103L

			template <typename Entity, typename Extract, typename HashCachePolicy>
			template <typename NodeAlloc, typename ... Args>
			KERBAL_CONSTEXPR20
			typename hash_table_base<Entity, Extract, HashCachePolicy>::hash_table_node *
			hash_table_base<Entity, Extract, HashCachePolicy>::k_build_new_hash_node(NodeAlloc & node_alloc, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits;

				hash_table_node * p = ht_node_allocator_traits::allocate(node_alloc, 1);
#		if !__cpp_exceptions
				if (p == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if __cpp_exceptions
				try {
#		endif
					ht_node_allocator_traits::construct(node_alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
#		if __cpp_exceptions
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
#	if __cpp_exceptions
#		define FBODY(i) \
			template <typename Entity, typename Extract, typename HashCachePolicy> \
			template <typename KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename hash_table_base<Entity, Extract, HashCachePolicy>::hash_table_node * \
			hash_table_base<Entity, Extract, HashCachePolicy>::k_build_new_hash_node(NodeAlloc & node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits; \
 \
				hash_table_node * p = ht_node_allocator_traits::allocate(node_alloc, 1); \
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
			typename hash_table_base<Entity, Extract, HashCachePolicy>::hash_table_node * \
			hash_table_base<Entity, Extract, HashCachePolicy>::k_build_new_hash_node(NodeAlloc & node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits; \
 \
				hash_table_node * p = ht_node_allocator_traits::allocate(node_alloc, 1); \
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
			k_destroy_hash_node(NodeAlloc & node_alloc, hash_table_node * p)
			{
				typedef kerbal::memory::allocator_traits<NodeAlloc> ht_node_allocator_traits;
				ht_node_allocator_traits::destroy(node_alloc, p);
				ht_node_allocator_traits::deallocate(node_alloc, p, 1);
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_IMPL_HASH_TABLE_BASE_IMPL_HPP
