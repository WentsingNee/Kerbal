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
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <kerbal/container/hash_table/hash_table.decl.hpp>


namespace kerbal
{

	namespace container
	{

	//===================
	// Constructor/Destructor

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table() :
			hash_table_base(this->bucket_alloc())
		{
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(size_type bucket_count) :
			hash_table_base(this->bucket_alloc(), bucket_count)
		{
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
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

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
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

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			InputIterator first, InputIterator last,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		) :
			hash_table_base(this->bucket_alloc(), first, last)
		{
		}

		/*
		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			InputIterator first, InputIterator last,
			size_type bucket_count,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			InputIterator first, InputIterator last,
			size_type bucket_count, const Hash & hash,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			InputIterator first, InputIterator last,
			size_type bucket_count, const Hash & hash, const key_equal & key_equal,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			InputIterator first, InputIterator last,
			size_type bucket_count, const Hash & hash, const key_equal & key_equal,
			const NodeAllocatorBR & nodeAllocatorBr,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			InputIterator first, InputIterator last,
			size_type bucket_count, const Hash & hash, const key_equal & key_equal,
			const NodeAllocatorBR & nodeAllocatorBr, const BucketAllocatorBR & bucketAllocatorBr,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);
		*/

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			kerbal::container::unique_tag_t tag,
			InputIterator first, InputIterator last,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		) :
			hash_table_base(tag, this->bucket_alloc(), first, last)
		{
		}

		/*
		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			kerbal::container::unique_tag_t,
			InputIterator first, InputIterator last,
			size_type bucket_count,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			kerbal::container::unique_tag_t,
			InputIterator first, InputIterator last,
			size_type bucket_count, const Hash & hash,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			kerbal::container::unique_tag_t,
			InputIterator first, InputIterator last,
			size_type bucket_count, const Hash & hash, const key_equal & key_equal,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			kerbal::container::unique_tag_t,
			InputIterator first, InputIterator last,
			size_type bucket_count, const Hash & hash, const key_equal & key_equal,
			const NodeAllocatorBR & nodeAllocatorBr,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			kerbal::container::unique_tag_t,
			InputIterator first, InputIterator last,
			size_type bucket_count, const Hash & hash, const key_equal & key_equal,
			const NodeAllocatorBR & nodeAllocatorBr, const BucketAllocatorBR & bucketAllocatorBr,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		);
		*/

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(hash_table const & src) :
			extract_compress_helper(kerbal::utility::in_place_t(), src.extract()),
			hash_compress_helper(kerbal::utility::in_place_t(), src.hash()),
			key_equal_compress_helper(kerbal::utility::in_place_t(), src.key_equal_obj()),
			node_allocator_overload(),
			bucket_allocator_overload(),
			hash_table_base(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				src.cbegin(), src.cend()
			)
		{
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(hash_table const & src, kerbal::container::unique_tag_t tag) :
			extract_compress_helper(kerbal::utility::in_place_t(), src.extract()),
			hash_compress_helper(kerbal::utility::in_place_t(), src.hash()),
			key_equal_compress_helper(kerbal::utility::in_place_t(), src.key_equal_obj()),
			node_allocator_overload(),
			bucket_allocator_overload(),
			hash_table_base(
				tag,
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				src.cbegin(), src.cend()
			)
		{
		}


#	if __cplusplus >= 201103L

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			std::initializer_list<value_type> ilist
		) :
			extract_compress_helper(),
			hash_compress_helper(),
			key_equal_compress_helper(),
			node_allocator_overload(),
			bucket_allocator_overload(),
			hash_table_base(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				ilist
			)
		{
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			kerbal::container::unique_tag_t tag,
			std::initializer_list<value_type> ilist
		) :
			extract_compress_helper(),
			hash_compress_helper(),
			key_equal_compress_helper(),
			node_allocator_overload(),
			bucket_allocator_overload(),
			hash_table_base(
				tag,
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				ilist
			)
		{
		}

#	else

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename U>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			kerbal::assign::assign_list<U> const & ilist
		) :
			extract_compress_helper(),
			hash_compress_helper(),
			key_equal_compress_helper(),
			node_allocator_overload(),
			bucket_allocator_overload(),
			hash_table_base(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				ilist
			)
		{
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename U>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_table(
			kerbal::container::unique_tag_t tag,
			kerbal::assign::assign_list<U> const & ilist
		) :
			extract_compress_helper(),
			hash_compress_helper(),
			key_equal_compress_helper(),
			node_allocator_overload(),
			bucket_allocator_overload(),
			hash_table_base(
				tag,
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				ilist
			)
		{
		}

#	endif

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		~hash_table()
		{
			this->hash_table_base::destroy_using_allocator(this->node_alloc(), this->bucket_alloc());
		}


	//===================
	// Lookup

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		bool
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		contains(key_type const & key) const
		{
			return this->hash_table_base::contains(
				this->extract(), this->hash(), this->key_equal_obj(),
				key
			);
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		find(key_type const & key)
		{
			return this->hash_table_base::find(
				this->extract(), this->hash(), this->key_equal_obj(),
				key
			);
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		find(key_type const & key) const
		{
			return this->hash_table_base::find(
				this->extract(), this->hash(), this->key_equal_obj(),
				key
			);
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		kerbal::utility::compressed_pair<
			typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator,
			typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		equal_range(key_type const & key)
		{
			return this->hash_table_base::equal_range(
				this->extract(), this->hash(), this->key_equal_obj(),
				key
			);
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		kerbal::utility::compressed_pair<
			typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator,
			typename hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator
		>
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		equal_range(key_type const & key) const
		{
			return this->hash_table_base::equal_range(
				this->extract(), this->hash(), this->key_equal_obj(),
				key
			);
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		size_type
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		count(key_type const & key) const
		{
			return this->hash_table_base::count(
				this->extract(), this->hash(), this->key_equal_obj(),
				key
			);
		}

	//===================
	// Insert

#	if __cplusplus >= 201103L

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		emplace(Args && ... args)
		{
			return this->hash_table_base::emplace_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				kerbal::utility::forward<Args>(args)...
			);
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		emplace_unique(Args && ... args)
		{
			return this->hash_table_base::emplace_unique_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				kerbal::utility::forward<Args>(args)...
			);
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) KERBAL_MACRO_CONCAT(Arg, i) const & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)

#	define FBODY(i) \
		template < \
			typename Entity, \
			typename Extract, typename Hash, typename KeyEqual, \
			typename NodeAllocator, typename BucketAllocator \
		> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator \
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>:: \
		emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->hash_table_base::emplace_using_allocator( \
				this->extract(), this->hash(), this->key_equal_obj(), \
				this->node_alloc(), this->bucket_alloc() \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
		} \
 \
		template < \
			typename Entity, \
			typename Extract, typename Hash, typename KeyEqual, \
			typename NodeAllocator, typename BucketAllocator \
		> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r \
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>:: \
		emplace_unique(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->hash_table_base::emplace_unique_using_allocator( \
				this->extract(), this->hash(), this->key_equal_obj(), \
				this->node_alloc(), this->bucket_alloc() \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif


		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(const_reference src)
		{
			return this->hash_table_base::insert_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				src
			);
		}

#	if __cplusplus >= 201103L

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(rvalue_reference src)
		{
			return this->hash_table_base::insert_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				kerbal::compatibility::move(src)
			);
		}

#	endif

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(InputIterator first, InputIterator last)
		{
			return this->hash_table_base::insert_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				first, last
			);
		}

#	if __cplusplus >= 201103L

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(std::initializer_list<value_type> ilist)
		{
			this->hash_table_base::insert_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				ilist
			);
		}

#	else

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename U>
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(kerbal::assign::assign_list<U> const & ilist)
		{
			this->hash_table_base::insert_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				ilist
			);
		}

#	endif

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert_unique(const_reference src)
		{
			return this->hash_table_base::insert_unique_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				src
			);
		}

#	if __cplusplus >= 201103L

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert_unique(rvalue_reference src)
		{
			return this->hash_table_base::insert_unique_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				kerbal::compatibility::move(src)
			);
		}

#	endif

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert_unique(InputIterator first, InputIterator last)
		{
			this->hash_table_base::insert_unique_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				first, last
			);
		}

#	if __cplusplus >= 201103L

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert_unique(std::initializer_list<value_type> ilist)
		{
			this->hash_table_base::insert_unique_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				ilist
			);
		}

#	else

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		template <typename U>
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert_unique(kerbal::assign::assign_list<U> const & ilist)
		{
			this->hash_table_base::insert_unique_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(), this->bucket_alloc(),
				ilist
			);
		}

#	endif



	//===================
	// Erase

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		clear()
		{
			this->hash_table_base::clear_using_allocator(this->node_alloc());
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		erase(const_iterator pos)
		{
			return this->hash_table_base::erase_using_allocator(
				this->extract(), this->hash(),
				this->node_alloc(),
				pos
			);
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::size_type
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		erase(const_iterator first, const_iterator last)
		{
			return this->hash_table_base::erase_using_allocator(
				this->extract(), this->hash(),
				this->node_alloc(),
				first, last
			);
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		typename
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::size_type
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		erase(key_type const & key)
		{
			return this->hash_table_base::erase_using_allocator(
				this->extract(), this->hash(), this->key_equal_obj(),
				this->node_alloc(),
				key
			);
		}


	//===================
	// Hash policy

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		reserve(size_type new_size)
		{
			this->hash_table_base::reserve_using_allocator(
				this->extract(), this->hash(),
				this->bucket_alloc(),
				new_size
			);
		}

		template <
			typename Entity,
			typename Extract, typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		void
		hash_table<Entity, Extract, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		rehash(size_type new_bucket_count)
		{
			this->hash_table_base::rehash(
				this->extract(), this->hash(),
				this->bucket_alloc(),
				new_bucket_count
			);
		}

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_HASH_TABLE_HASH_TABLE_IMPL_HPP
