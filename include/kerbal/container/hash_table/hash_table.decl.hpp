/**
 * @file       hash_table.decl.hpp
 * @brief
 * @date       2022-03-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_DECL_HPP
#define KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_DECL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/bad_alloc.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/utility/compressed_pair.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

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

#include <cstddef>

#include <kerbal/container/hash_table/hash_table.fwd.hpp>

#include <kerbal/container/detail/container_rebind_allocator_overload.hpp>
#include <kerbal/container/detail/hash_table_base.hpp>



namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Extract, typename Hash, typename NodeAllocatorBR, typename BucketAllocatorBR>
			struct hash_table_typedef_helper
			{
					typedef typename kerbal::container::detail::hash_node_traits<Entity, Hash>::hash_result_cache_policy	hash_result_cache_policy;
					typedef kerbal::container::detail::hash_table_base<Entity, Extract, hash_result_cache_policy>		hash_table_base;

					typedef typename hash_table_base::node				node;
					typedef typename hash_table_base::bucket_type		bucket_type;

					typedef kerbal::memory::allocator_traits<NodeAllocatorBR>									node_allocator_br_traits;
					typedef typename node_allocator_br_traits::template rebind_alloc<node>::other				node_allocator_type;
					typedef typename node_allocator_br_traits::template rebind_traits<node>::other				node_allocator_traits;
					typedef kerbal::container::detail::container_rebind_allocator_overload<
							NodeAllocatorBR, node
					>																							node_allocator_overload;

					typedef kerbal::memory::allocator_traits<BucketAllocatorBR>									bucket_allocator_br_traits;
					typedef typename bucket_allocator_br_traits::template rebind_alloc<bucket_type>::other		bucket_allocator_type;
					typedef typename bucket_allocator_br_traits::template rebind_traits<bucket_type>::other		bucket_allocator_traits;
					typedef kerbal::container::detail::container_rebind_allocator_overload<
							BucketAllocatorBR, bucket_type
					>																							bucket_allocator_overload;

			};

		} // namespace detail

		template <typename Entity,
				typename Extract,
				typename Hash,
				typename KeyEqual,
				typename NodeAllocatorBR,
				typename BucketAllocatorBR
		>
		class hash_table:
				private kerbal::utility::member_compress_helper<Hash>,
				private kerbal::utility::member_compress_helper<KeyEqual>,
				private kerbal::container::detail::hash_table_typedef_helper<
					Entity, Extract, Hash, NodeAllocatorBR, BucketAllocatorBR
				>::node_allocator_overload,
				private kerbal::container::detail::hash_table_typedef_helper<
					Entity, Extract, Hash, NodeAllocatorBR, BucketAllocatorBR
				>::bucket_allocator_overload,
				protected kerbal::container::detail::hash_table_typedef_helper<
					Entity, Extract, Hash, NodeAllocatorBR, BucketAllocatorBR
				>::hash_table_base
		{
			private:
				typedef kerbal::container::detail::hash_table_typedef_helper<
					Entity, Extract, Hash, NodeAllocatorBR, BucketAllocatorBR
				>																				hash_table_typedef_helper;

				typedef kerbal::utility::member_compress_helper<Hash>							hash_compress_helper;
				typedef kerbal::utility::member_compress_helper<KeyEqual>						key_equal_compress_helper;

				typedef typename hash_table_typedef_helper::node								node;
				typedef typename hash_table_typedef_helper::bucket_type							bucket_type;

				typedef typename hash_table_typedef_helper::node_allocator_type					node_allocator_type;
				typedef typename hash_table_typedef_helper::node_allocator_traits				node_allocator_traits;
				typedef typename hash_table_typedef_helper::node_allocator_overload				node_allocator_overload;

				typedef typename hash_table_typedef_helper::bucket_allocator_traits				bucket_allocator_traits;
				typedef typename hash_table_typedef_helper::bucket_allocator_type				bucket_allocator_type;
				typedef typename hash_table_typedef_helper::bucket_allocator_overload			bucket_allocator_overload;

				typedef typename hash_table_typedef_helper::hash_table_base						hash_table_base;

			public:
				typedef typename hash_table_base::key_type					key_type;
				typedef typename hash_table_base::value_type				value_type;
				typedef typename hash_table_base::const_type				const_type;
				typedef typename hash_table_base::reference					reference;
				typedef typename hash_table_base::const_reference			const_reference;

#		if __cplusplus >= 201103L
				typedef typename hash_table_base::rvalue_reference			rvalue_reference;
				typedef typename hash_table_base::const_rvalue_reference	const_rvalue_reference;
#		endif

				typedef Hash								hasher;
				typedef typename Hash::result_type			hash_result_type;
				typedef KeyEqual							key_equal;
				typedef std::size_t							size_type;
				typedef std::ptrdiff_t						difference_type;

//				typedef typename hash_table_base::local_iterator			local_iterator;
//				typedef typename hash_table_base::const_local_iterator		const_local_iterator;
				typedef typename hash_table_base::iterator					iterator;
				typedef typename hash_table_base::const_iterator			const_iterator;
				typedef typename hash_table_base::unique_insert_r			unique_insert_r;

//				typedef typename hash_table_base::NODE_SIZE					NODE_SIZE;
//				typedef typename hash_table_base::CACHE_HASH_RESULT			CACHE_HASH_RESULT;

			protected:

				KERBAL_CONSTEXPR14
				node_allocator_type & node_alloc() KERBAL_NOEXCEPT
				{
					return node_allocator_overload::alloc();
				}

				KERBAL_CONSTEXPR
				const node_allocator_type & node_alloc() const KERBAL_NOEXCEPT
				{
					return node_allocator_overload::alloc();
				}

				KERBAL_CONSTEXPR14
				bucket_allocator_type & bucket_alloc() KERBAL_NOEXCEPT
				{
					return bucket_allocator_overload::alloc();
				}

				KERBAL_CONSTEXPR
				const bucket_allocator_type & bucket_alloc() const KERBAL_NOEXCEPT
				{
					return bucket_allocator_overload::alloc();
				}


			public:
				KERBAL_CONSTEXPR20
				hash_table();

				KERBAL_CONSTEXPR20
				explicit hash_table(size_type bucket_count);

				KERBAL_CONSTEXPR20
				hash_table(size_type bucket_count, const Hash & hash);

				KERBAL_CONSTEXPR20
				hash_table(size_type bucket_count, const Hash & hash, const key_equal & key_equal);

				KERBAL_CONSTEXPR20
				hash_table(size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							const NodeAllocatorBR & nodeAllocatorBr);

				KERBAL_CONSTEXPR20
				hash_table(size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							const NodeAllocatorBR & nodeAllocatorBr, const BucketAllocatorBR & bucketAllocatorBr);

			protected:

			public:
				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(InputIterator first, InputIterator last,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
						   >::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count, const Hash & hash,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							const NodeAllocatorBR & nodeAllocatorBr,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(InputIterator first, InputIterator last,
							size_type bucket_count, const Hash & hash, const key_equal & key_equal,
							const NodeAllocatorBR & nodeAllocatorBr, const BucketAllocatorBR & bucketAllocatorBr,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
				);

				KERBAL_CONSTEXPR20
				~hash_table();


			//===================
			// Observers

			public:
				KERBAL_CONSTEXPR
				Extract & extract() KERBAL_NOEXCEPT
				{
					return hash_table_base::extract();
				}

				KERBAL_CONSTEXPR
				const Extract & extract() const KERBAL_NOEXCEPT
				{
					return hash_table_base::extract();
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

				using hash_table_base::begin;
				using hash_table_base::cbegin;
				using hash_table_base::end;
				using hash_table_base::cend;

			//===================
			// Capacity

				using hash_table_base::empty;
				using hash_table_base::size;
				using hash_table_base::max_size;

			//===================
			// Modifiers

			public:

				void clear();

#		if __cplusplus >= 201103L

				template <typename ... Args >
				iterator emplace(Args&& ... args);

				template <typename ... Args >
				unique_insert_r
				emplace_unique(Args&& ... args);

				template <typename ... Args >
				iterator emplace_hint(const_iterator hint, Args&& ... args);

				template <typename ... Args >
				unique_insert_r
				emplace_unique_hint(const_iterator hint, Args&& ... args);

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)

#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)); \
 \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				unique_insert_r \
				emplace_unique(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)); \
 \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator emplace_hint(const_iterator hint KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \
 \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				unique_insert_r \
				emplace_unique_hint(const_iterator hint KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		endif


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

#		if __cplusplus >= 201103L
				void insert(std::initializer_list<value_type> ilist);
#		else
				template <typename Up>
				void insert(const kerbal::assign::assign_list<Up> & ilist);
#		endif


				unique_insert_r insert_unique(const_reference src);
				unique_insert_r insert_unique(const_iterator hint, const_reference src);

#		if __cplusplus >= 201103L
				unique_insert_r insert_unique(rvalue_reference src);
				unique_insert_r insert_unique(const_iterator hint, rvalue_reference src);
#		endif

				template <typename InputIterator>
				void insert_unique(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L
				void insert_unique(std::initializer_list<value_type> ilist);
#		else
				template <typename Up>
				void insert_unique(const kerbal::assign::assign_list<Up> & ilist);
#		endif


				iterator erase(const_iterator pos);

				iterator erase(const_iterator first, const_iterator last);

				iterator erase(const key_type & key);

				void swap(hash_table & with);

			//===================
			// Bucket interface

				using hash_table_base::bucket_count;
				using hash_table_base::max_bucket_count;
				using hash_table_base::bucket_size;

				KERBAL_CONSTEXPR14
				size_type bucket(const key_type & key) const
				{
					return this->hash_table_base::bucket(this->hash(), key);
				}

			//===================
			// Hash policy

				using hash_table_base::load_factor;
				using hash_table_base::max_load_factor;

				KERBAL_CONSTEXPR20
				void reserve(size_type new_size)
				{
					this->hash_table_base::reserve_using_allocator(this->hash(), this->bucket_alloc(), new_size);
				}

				KERBAL_CONSTEXPR20
				void rehash(size_type new_bucket_count)
				{
					this->hash_table_base::rehash(this->hash(), this->bucket_alloc(), new_bucket_count);
				}

		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_DECL_HPP
