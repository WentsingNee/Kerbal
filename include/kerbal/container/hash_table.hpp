/**
 * @file       hash_table.hpp
 * @brief
 * @date       2020-08-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_HASH_TABLE_HPP
#define KERBAL_CONTAINER_HASH_TABLE_HPP

#include <kerbal/container/fwd/hash_table.fwd.hpp>

#include <kerbal/container/detail/hash_table_iterator.hpp>
#include <kerbal/container/detail/hash_table_node.hpp>
#include <kerbal/container/detail/forward_list_base.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus < 201103L
#	include <kerbal/assign/assign_list.hpp>
#else
#	include <initializer_list>
#endif

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <utility> // std::pair
#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Hash, typename NodeAllocatorBR>
			struct hash_table_typedef_helper
			{
				private:
					typedef Entity																value_type;
					typedef kerbal::container::detail::sl_node<Entity>							fl_node;
					typedef kerbal::container::detail::hash_table_node<Entity, Hash>			ht_node;
					typedef kerbal::container::detail::fl_allocator_unrelated<Entity>			bucket_type;

					typedef kerbal::memory::allocator_traits<AllocatorBR>								allocator_traits;

				public:
					typedef typename allocator_traits::template rebind_traits<bucket_type>::other		bucket_allocator_traits;
					typedef typename allocator_traits::template rebind_traits<ht_node>::other			ht_node_allocator_traits;

					typedef typename allocator_traits::template rebind_alloc<bucket_type>::other		bucket_allocator_type;
					typedef typename allocator_traits::template rebind_alloc<ht_node>::other			ht_node_allocator_type;
			};

		} // namespace detail

		template <typename Entity,
				typename Extract,
				typename Hash,
				typename KeyEqual,
				typename NodeAllocatorBR,
				typename BucketAllocatorBR
		>
		class hash_table :
				private kerbal::utility::member_compress_helper<Hash>,
				private kerbal::utility::member_compress_helper<KeyEqual>,
				private detail::hash_table_node_allocator_compress_helper<Entity, Hash, NodeAllocatorBR>,
				private detail::hash_table_bucket_allocator_compress_helper<Entity, Hash, BucketAllocatorBR>
		{
			private:
				typedef kerbal::utility::member_compress_helper<Hash>										hash_compress_helper;
				typedef kerbal::utility::member_compress_helper<KeyEqual>									key_equal_compress_helper;
				typedef detail::hash_table_node_allocator_compress_helper<Entity, Hash, NodeAllocatorBR>		node_allocator_compress_helper;
				typedef detail::hash_table_bucket_allocator_compress_helper<Entity, Hash, BucketAllocatorBR>	bucket_allocator_compress_helper;

			public:
				typedef typename Extract::key_type			key_type;
				typedef Entity								value_type;
				typedef const value_type					const_type;
				typedef value_type &						reference;
				typedef const value_type &					const_reference;
				typedef value_type *						pointer;
				typedef const value_type *					const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type &&						rvalue_reference;
				typedef const value_type &&					const_rvalue_reference;
#		endif

				typedef Hash								hasher;
				typedef typename Hash::result_type			hash_result_type;
				typedef KeyEqual							key_equal;
				typedef std::size_t							size_type;
				typedef std::ptrdiff_t						difference_type;

			protected:
				typedef kerbal::container::detail::hash_table_node<Entity, Hash>				hash_table_node;
				typedef typename node_allocator_compress_helper::ht_node_allocator_traits		ht_node_allocator_traits;
				typedef typename bucket_allocator_compress_helper::bucket_allocator_traits		bucket_allocator_traits;
				typedef typename node_allocator_compress_helper::ht_node_allocator_type			ht_node_allocator_type;
				typedef typename bucket_allocator_compress_helper::bucket_allocator_type		bucket_allocator_type;

				typedef typename bucket_allocator_type::value_type			bucket_type;

				using node_allocator_compress_helper::node_alloc;
				using bucket_allocator_compress_helper::bucket_alloc;
				ht_node_allocator_type & node_alloc()
				{
					return super::member();
				}

				bucket_allocator_type & bucket_alloc()
				{
					return super::member();
				}


			public:
				typedef kerbal::container::detail::hash_table_local_iter<Entity>				local_iterator;
				typedef kerbal::container::detail::hash_table_local_kiter<Entity>				const_local_iterator;
				typedef kerbal::container::detail::hash_table_iter<Entity>						iterator;
				typedef kerbal::container::detail::hash_table_kiter<Entity>						const_iterator;

				typedef kerbal::type_traits::integral_constant<size_t, sizeof(hash_table_node)>		NODE_SIZE;
				typedef typename hash_table_node::CACHE_HASH_CODE									CACHE_HASH_CODE;

			protected:
				bucket_type *		_K_buckets;
				size_type			_K_bucket_count;
				size_type			_K_size;
				float				_K_max_load_factor;

			public:
				hash_table();

				explicit
				hash_table(size_type bucket_count);

				hash_table(size_type bucket_count, const Hash & hash);

				hash_table(size_type bucket_count, const Hash & hash, const key_equal & key_equal);

				hash_table(size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							const NodeAllocatorBR & nodeAllocatorBr);

				hash_table(size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							const NodeAllocatorBR & nodeAllocatorBr, const BucketAllocatorBR & bucketAllocatorBr);

			protected:

			public:
				template <typename InputIterator>
				hash_table(InputIterator first, InputIterator last,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
						   >::type = 0
				);

				template <typename InputIterator>
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				template <typename InputIterator>
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count, const Hash & hash,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				template <typename InputIterator>
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				template <typename InputIterator>
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							const NodeAllocatorBR & nodeAllocatorBr,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				template <typename InputIterator>
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							const NodeAllocatorBR & nodeAllocatorBr, const BucketAllocatorBR & bucketAllocatorBr,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				~hash_table();


			//===================
			// Observers

			public:
				KERBAL_CONSTEXPR
				Extract extract() const KERBAL_NOEXCEPT
				{
					return Extract();
				}

				KERBAL_CONSTEXPR14
				Hash & hash() KERBAL_NOEXCEPT
				{
					return hash_compress_helper::member();
				}

				KERBAL_CONSTEXPR
				const Hash & hash() const KERBAL_NOEXCEPT
				{
					return hash_compress_helper::member();
				}

				KERBAL_CONSTEXPR14
				key_equal & key_equal_obj() KERBAL_NOEXCEPT
				{
					return key_equal_compress_helper::member();
				}

				KERBAL_CONSTEXPR
				const key_equal & key_equal_obj() const KERBAL_NOEXCEPT
				{
					return key_equal_compress_helper::member();
				}

			//===================
			// Iterators

				KERBAL_CONSTEXPR14
				iterator begin() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_iterator begin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_iterator cbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				iterator end() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_iterator end() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_iterator cend() const KERBAL_NOEXCEPT;

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
					return this->_K_size;
				}

				KERBAL_CONSTEXPR
				size_type max_size() const KERBAL_NOEXCEPT
				{
					return kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(hash_table_node);
				}

			//===================
			// Modifiers

				void clear();

			protected:
				std::pair<const_local_iterator, bool>
				_K_determine_insert_pos(const key_type & key, bucket_type & bucket_in);

			public:
				iterator insert(const_reference src);

#		if __cplusplus >= 201103L
				iterator insert(rvalue_reference src);
#		endif

				iterator insert(const_iterator hint, const_reference src);

#		if __cplusplus >= 201103L
				iterator insert(const_iterator hint, rvalue_reference src);
#		endif

				template <typename InputIterator>
				void insert(InputIterator first, InputIterator last);

#		if __cplusplus < 201103L
				template <typename Up>
				void insert(const kerbal::assign::assign_list<Up> & ilist);
#		else
				void insert(std::initializer_list<value_type> ilist);
#		endif


				std::pair<iterator, bool> insert_no_exists(const_reference src);

#		if __cplusplus >= 201103L
				std::pair<iterator, bool> insert_no_exists(rvalue_reference src);
#		endif

				std::pair<iterator, bool> insert_no_exists(const_iterator hint, const_reference src);

#		if __cplusplus >= 201103L
				std::pair<iterator, bool> insert_no_exists(const_iterator hint, rvalue_reference src);
#		endif

				template <typename InputIterator>
				void insert_no_exists(InputIterator first, InputIterator last);

#		if __cplusplus < 201103L
				template <typename Up>
				void insert_no_exists(const kerbal::assign::assign_list<Up> & ilist);
#		else
				void insert_no_exists(std::initializer_list<value_type> ilist);
#		endif


#		if __cplusplus < 201103L

				iterator emplace();

				template <typename Arg0>
				iterator emplace(const Arg0 & arg0);

				template <typename Arg0, typename Arg1>
				iterator emplace(const Arg0 & arg0, const Arg1 & arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				iterator emplace(const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2);

#		else

				template <typename ... Args >
				iterator emplace(Args&& ... args);

#		endif


#		if __cplusplus < 201103L

				iterator emplace_hint(const_iterator hint);

				template <typename Arg0>
				iterator emplace_hint(const_iterator hint, const Arg0 & arg0);

				template <typename Arg0, typename Arg1>
				iterator emplace_hint(const_iterator hint, const Arg0 & arg0, const Arg1 & arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				iterator emplace_hint(const_iterator hint, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2);

#		else

				template <typename ... Args >
				iterator emplace_hint(const_iterator hint, Args&& ... args);

#		endif


#		if __cplusplus < 201103L

				std::pair<iterator, bool> emplace_no_exists();

				template <typename Arg0>
				std::pair<iterator, bool> emplace_no_exists(const Arg0 & arg0);

				template <typename Arg0, typename Arg1>
				std::pair<iterator, bool> emplace_no_exists(const Arg0 & arg0, const Arg1 & arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				std::pair<iterator, bool> emplace_no_exists(const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2);

#		else

				template <typename ... Args >
				std::pair<iterator, bool> emplace_no_exists(Args&& ... args);

#		endif


#		if __cplusplus < 201103L

				std::pair<iterator, bool> emplace_hint_no_exists(const_iterator hint);

				template <typename Arg0>
				std::pair<iterator, bool> emplace_hint_no_exists(const_iterator hint, const Arg0 & arg0);

				template <typename Arg0, typename Arg1>
				std::pair<iterator, bool> emplace_hint_no_exists(const_iterator hint, const Arg0 & arg0, const Arg1 & arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				std::pair<iterator, bool> emplace_hint_no_exists(const_iterator hint, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2);

#		else

				template <typename ... Args >
				std::pair<iterator, bool> emplace_hint_no_exists(const_iterator hint, Args&& ... args);

#		endif


				iterator erase(const_iterator pos);

				iterator erase(const_iterator first, const_iterator last);

				iterator erase(const key_type& key);

				void swap(hash_table & with);


			//===================
			// Lookup

				size_type count(const key_type & key) const;

				iterator find(const key_type & key);

				const_iterator find(const key_type & key) const;

				bool contains(const key_type & key) const;

				std::pair<iterator, iterator> equal_range(const key_type & key);

				std::pair<const_iterator, const_iterator> equal_range(const key_type & key) const;


			//===================
			// Bucket interface

				KERBAL_CONSTEXPR20
				local_iterator begin(size_type bucket_idx) KERBAL_NOEXCEPT
				{
					return local_iterator(this->_K_buckets[bucket_idx].begin());
				}

				KERBAL_CONSTEXPR20
				const_local_iterator begin(size_type bucket_idx) const KERBAL_NOEXCEPT
				{
					return const_local_iterator(this->_K_buckets[bucket_idx].cbegin());
				}

				KERBAL_CONSTEXPR20
				const_local_iterator cbegin(size_type bucket_idx) const KERBAL_NOEXCEPT
				{
					return const_local_iterator(this->_K_buckets[bucket_idx].cbegin());
				}

				KERBAL_CONSTEXPR20
				local_iterator end(size_type bucket_idx) KERBAL_NOEXCEPT
				{
					return local_iterator(this->_K_buckets[bucket_idx].end());
				}

				KERBAL_CONSTEXPR20
				const_local_iterator end(size_type bucket_idx) const KERBAL_NOEXCEPT
				{
					return const_local_iterator(this->_K_buckets[bucket_idx].cend());
				}

				KERBAL_CONSTEXPR20
				const_local_iterator cend(size_type bucket_idx) const KERBAL_NOEXCEPT
				{
					return const_local_iterator(this->_K_buckets[bucket_idx].cend());
				}

				KERBAL_CONSTEXPR
				size_type bucket_count() const KERBAL_NOEXCEPT
				{
					return this->_K_bucket_count;
				}

				KERBAL_CONSTEXPR
				size_type max_bucket_count() const KERBAL_NOEXCEPT
				{
					return static_cast<size_type>(-1) / sizeof(bucket_type);
				}

				KERBAL_CONSTEXPR14
				size_type bucket_size(size_type bucket_idx) const KERBAL_NOEXCEPT
				{
					return this->_K_buckets[bucket_idx].size();
				}

				KERBAL_CONSTEXPR14
				size_type bucket(const key_type & key) const
				{
					return this->hash()(key) % this->bucket_count();
				}

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
					return this->_K_max_load_factor;
				}

				KERBAL_CONSTEXPR14
				void max_load_factor(float mlf) KERBAL_NOEXCEPT
				{
					this->_K_max_load_factor = mlf;
				}

				void reserve(size_type new_size)
				{
					size_type new_bucket_count = _K_first_prime_greater_equal_than(new_size / this->max_load_factor());
					this->_K_rehash_unchecked(new_bucket_count);
				}

				void rehash(size_type new_bucket_count)
				{
					size_type minimum_bucket_count = this->size() / this->max_load_factor();
					this->_K_rehash_unchecked(new_bucket_count < minimum_bucket_count ? minimum_bucket_count : new_bucket_count);
				}

			//===================
			// private

			private:

				KERBAL_CONSTEXPR14
				static size_type _K_first_prime_greater_equal_than(size_type n) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				bucket_type * _K_create_new_buckets(size_type new_bucket_count);

				KERBAL_CONSTEXPR20
				void _K_init_buckets(size_type bucket_count = 17)
				{
					this->_K_bucket_count = bucket_count;
					this->_K_buckets = _K_create_new_buckets(bucket_count);
				}

				KERBAL_CONSTEXPR20
				void _K_rehash_unchecked(size_type new_bucket_count);

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				hash_table_node * _K_build_new_hash_node(ht_node_allocator_type & node_alloc, Args && ... args)
				{
					hash_table_node * p = ht_node_allocator_traits::allocate(node_alloc, 1);
					ht_node_allocator_traits::construct(node_alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
					return p;
				}

		};

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/hash_table.impl.hpp>

#endif // KERBAL_CONTAINER_HASH_TABLE_HPP
