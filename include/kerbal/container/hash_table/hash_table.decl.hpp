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

#include <kerbal/assign/assign_list.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
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
					typedef kerbal::container::detail::hash_table_base<Entity, hash_result_cache_policy>		hash_table_base;

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


		template <typename Entity, typename Extract, typename Hash, typename NodeAllocatorBR, typename BucketAllocatorBR>
		struct hash_table_node_size :
			kerbal::type_traits::integral_constant<std::size_t,
				sizeof(
					typename kerbal::container::detail::hash_table_typedef_helper<Entity, Extract, Hash, NodeAllocatorBR, BucketAllocatorBR>::node
				)
			>
		{
		};


		template <
			typename Entity,
			typename Extract,
			typename Hash,
			typename KeyEqual,
			typename NodeAllocatorBR,
			typename BucketAllocatorBR
		>
		class hash_table:
				private kerbal::utility::member_compress_helper<Extract>,
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

				typedef kerbal::utility::member_compress_helper<Extract>						extract_compress_helper;
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
				typedef typename hash_table_base::value_type				value_type;
				typedef typename hash_table_base::const_type				const_type;
				typedef typename hash_table_base::reference					reference;
				typedef typename hash_table_base::const_reference			const_reference;
				typedef typename hash_table_base::pointer					pointer;
				typedef typename hash_table_base::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename hash_table_base::rvalue_reference			rvalue_reference;
				typedef typename hash_table_base::const_rvalue_reference	const_rvalue_reference;
#		endif

				typedef Extract								extractor;
				typedef typename extractor::key_type		key_type;
				typedef Hash								hasher;
				typedef typename hasher::result_type		hash_result_type;
				typedef KeyEqual							key_equal;
				typedef std::size_t							size_type;
				typedef std::ptrdiff_t						difference_type;

//				typedef typename hash_table_base::local_iterator			local_iterator;
//				typedef typename hash_table_base::const_local_iterator		const_local_iterator;
				typedef typename hash_table_base::iterator					iterator;
				typedef typename hash_table_base::const_iterator			const_iterator;
				typedef typename hash_table_base::unique_insert_r			unique_insert_r;


//				typedef typename hash_table_base::NODE_SIZE					NODE_SIZE;
				typedef typename hash_table_base::CACHE_HASH_RESULT			CACHE_HASH_RESULT;

			protected:

				KERBAL_CONSTEXPR20
				node_allocator_type & node_alloc() KERBAL_NOEXCEPT
				{
					return node_allocator_overload::alloc();
				}

				KERBAL_CONSTEXPR20
				const node_allocator_type & node_alloc() const KERBAL_NOEXCEPT
				{
					return node_allocator_overload::alloc();
				}

				KERBAL_CONSTEXPR20
				bucket_allocator_type & bucket_alloc() KERBAL_NOEXCEPT
				{
					return bucket_allocator_overload::alloc();
				}

				KERBAL_CONSTEXPR20
				const bucket_allocator_type & bucket_alloc() const KERBAL_NOEXCEPT
				{
					return bucket_allocator_overload::alloc();
				}


			//===================
			// Constructor/Destructor

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
				hash_table(
					size_type bucket_count, const Hash & hash, const key_equal & key_equal,
					const NodeAllocatorBR & nodeAllocatorBr
				);

				KERBAL_CONSTEXPR20
				hash_table(
					size_type bucket_count, const Hash & hash, const key_equal & key_equal,
					const NodeAllocatorBR & nodeAllocatorBr, const BucketAllocatorBR & bucketAllocatorBr
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(
					InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(
					InputIterator first, InputIterator last,
					size_type bucket_count,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(
					InputIterator first, InputIterator last,
					size_type bucket_count, const Hash & hash,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(
					InputIterator first, InputIterator last,
					size_type bucket_count, const Hash & hash, const key_equal & key_equal,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(
					InputIterator first, InputIterator last,
					size_type bucket_count, const Hash & hash, const key_equal & key_equal,
					const NodeAllocatorBR & nodeAllocatorBr,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_table(
					InputIterator first, InputIterator last,
					size_type bucket_count, const Hash & hash, const key_equal & key_equal,
					const NodeAllocatorBR & nodeAllocatorBr, const BucketAllocatorBR & bucketAllocatorBr,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				KERBAL_CONSTEXPR20
				hash_table(hash_table const & src);

				KERBAL_CONSTEXPR20
				hash_table(hash_table const & src, kerbal::container::unique_tag_t);

				KERBAL_CONSTEXPR20
				~hash_table();


			//===================
			// Assign

			public:

				KERBAL_CONSTEXPR20
				hash_table & operator=(hash_table const & src)
				{
					this->clear();
					this->insert(src.cbegin(), src.cend()); // TODO
					return *this;
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				assign(InputIterator first, InputIterator last);

				KERBAL_CONSTEXPR20
				void assign(hash_table const & src);

#		if __cplusplus >= 201103L
				KERBAL_CONSTEXPR20
				void assign(hash_table && src);
#		endif

#		if __cplusplus >= 201103L
				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> ilist);
#		else
				template <typename U>
				KERBAL_CONSTEXPR20
				void assign(kerbal::assign::assign_list<U> const & ilist);
#		endif

			//===================
			// Observers

			public:

				KERBAL_CONSTEXPR20
				Extract & extract() KERBAL_NOEXCEPT
				{
					return extract_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				const Extract & extract() const KERBAL_NOEXCEPT
				{
					return extract_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				Hash & hash() KERBAL_NOEXCEPT
				{
					return hash_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				const Hash & hash() const KERBAL_NOEXCEPT
				{
					return hash_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				key_equal & key_equal_obj() KERBAL_NOEXCEPT
				{
					return key_equal_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				const key_equal & key_equal_obj() const KERBAL_NOEXCEPT
				{
					return key_equal_compress_helper::member();
				}

			//===================
			// Iterators

			public:

				using hash_table_base::begin;
				using hash_table_base::cbegin;

				using hash_table_base::end;
				using hash_table_base::cend;

			//===================
			// Capacity

			public:

				using hash_table_base::empty;
				using hash_table_base::size;
				using hash_table_base::max_size;

			//===================
			// Bucket interface

			public:

				using hash_table_base::bucket_count;
				using hash_table_base::max_bucket_count;
				using hash_table_base::bucket_size;

				KERBAL_CONSTEXPR20
				size_type bucket(key_type const & key) const
				{
					return this->hash_table_base::bucket(this->hash(), key);
				}

			//===================
			// Lookup

			public:

				KERBAL_CONSTEXPR20
				iterator find(key_type const & key);

				KERBAL_CONSTEXPR20
				const_iterator find(key_type const & key) const;

			//===================
			// Insert

			public:

#		if __cplusplus >= 201103L

				template <typename ... Args >
				KERBAL_CONSTEXPR20
				iterator emplace(Args&& ... args);

				template <typename ... Args >
				KERBAL_CONSTEXPR20
				unique_insert_r
				emplace_unique(Args&& ... args);

				template <typename ... Args >
				KERBAL_CONSTEXPR20
				iterator emplace_hint(const_iterator hint, Args&& ... args);

				template <typename ... Args >
				KERBAL_CONSTEXPR20
				unique_insert_r
				emplace_unique_hint(const_iterator hint, Args&& ... args);

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(Arg, i) const & KERBAL_MACRO_CONCAT(arg, i)

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

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif


				KERBAL_CONSTEXPR20
				iterator insert(const_reference src);

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator hint, const_reference src);


#		if __cplusplus >= 201103L
				KERBAL_CONSTEXPR20
				iterator insert(rvalue_reference src);

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator hint, rvalue_reference src);
#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				insert(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L
				KERBAL_CONSTEXPR20
				void insert(std::initializer_list<value_type> ilist);
#		else
				template <typename U>
				void insert(const kerbal::assign::assign_list<U> & ilist);
#		endif


				KERBAL_CONSTEXPR20
				unique_insert_r insert_unique(const_reference src);

				KERBAL_CONSTEXPR20
				unique_insert_r insert_unique(const_iterator hint, const_reference src);

#		if __cplusplus >= 201103L
				KERBAL_CONSTEXPR20
				unique_insert_r insert_unique(rvalue_reference src);

				KERBAL_CONSTEXPR20
				unique_insert_r insert_unique(const_iterator hint, rvalue_reference src);
#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				insert_unique(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L
				KERBAL_CONSTEXPR20
				void insert_unique(std::initializer_list<value_type> ilist);
#		else
				template <typename Up>
				void insert_unique(const kerbal::assign::assign_list<Up> & ilist);
#		endif


			//===================
			// Erase

			public:

				KERBAL_CONSTEXPR20
				void clear();

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator pos);

				KERBAL_CONSTEXPR20
				size_type erase(const_iterator first, const_iterator last);

				KERBAL_CONSTEXPR20
				size_type erase(key_type const & key);

			//===================
			// Modifiers

			public:

				KERBAL_CONSTEXPR20
				void swap(hash_table & with);

				KERBAL_CONSTEXPR20
				void merge(hash_table & with);

			//===================
			// Hash policy

			public:

				using hash_table_base::load_factor;
				using hash_table_base::max_load_factor;

				KERBAL_CONSTEXPR20
				void reserve(size_type new_size)
				{
					this->hash_table_base::reserve_using_allocator(this->extract(), this->hash(), this->bucket_alloc(), new_size);
				}

				KERBAL_CONSTEXPR20
				void rehash(size_type new_bucket_count)
				{
					this->hash_table_base::rehash(this->extract(), this->hash(), this->bucket_alloc(), new_bucket_count);
				}

		};

/*
		template <
			typename Entity,
			typename Extract,
			typename Hash,
			typename KeyEqual,
			typename NodeAllocatorBR,
			typename BucketAllocatorBR
		>
		KERBAL_CONSTEXPR20
		bool operator==(
			const hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocatorBR, BucketAllocatorBR> & lhs,
			const hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocatorBR, BucketAllocatorBR2> & rhs
		)
		{
			if (lhs.size() != rhs.size()) {
				return false;
			}
			return ;
		}

		template <
			typename Entity,
			typename Extract,
			typename Hash,
			typename KeyEqual,
			typename NodeAllocatorBR,
			typename BucketAllocatorBR
		>
		KERBAL_CONSTEXPR20
		bool operator!=(
			const hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocatorBR, BucketAllocatorBR> & lhs,
			const hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocatorBR, BucketAllocatorBR2> & rhs
		)
		{
			if (lhs.size() != rhs.size()) {
				return true;
			}
			return ;
		}
*/

	} // namespace container

	namespace algorithm
	{

		template <
			typename Entity,
			typename Extract,
			typename Hash,
			typename KeyEqual,
			typename NodeAllocatorBR,
			typename BucketAllocatorBR
		>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::container::hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocatorBR, BucketAllocatorBR> & a,
			kerbal::container::hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocatorBR, BucketAllocatorBR> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <
		typename Entity,
		typename Extract,
		typename Hash,
		typename KeyEqual,
		typename NodeAllocatorBR,
		typename BucketAllocatorBR
	>
	KERBAL_CONSTEXPR20
	void swap(
		kerbal::container::hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocatorBR, BucketAllocatorBR> & a,
		kerbal::container::hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocatorBR, BucketAllocatorBR> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_DECL_HPP
