/**
 * @file       hash_set.impl.hpp
 * @brief
 * @date       2024-05-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_HASH_SET_HASH_SET_IMPL_HPP
#define KERBAL_CONTAINER_HASH_SET_HASH_SET_IMPL_HPP

#include <kerbal/assign/assign_list.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/container/hash_set/hash_set.decl.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/compressed_pair.hpp>
#include <kerbal/utility/forward.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <kerbal/container/hash_table/hash_table.impl.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

#	if __cplusplus < 201103L

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		hash_set()
		{
		}

#	endif

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator> &
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		operator=(hash_set const & src)
		{
			this->assign(src);
			return *this;
		}

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		void
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		assign(hash_set const & src)
		{
			this->hash_table::assign_unique(src);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator> &
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		operator=(hash_set && src)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		void
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		assign(hash_set && src)
		{
			this->hash_table::assign_unique(kerbal::compatibility::move(src));
		}

#	endif

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		assign(InputIterator first, InputIterator last)
		{
			this->hash_table::assign_unique(first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator> &
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist);
			return *this;
		}

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		void
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		assign(std::initializer_list<value_type> ilist)
		{
			this->hash_table::assign_unique(ilist);
		}

#	else

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		template <typename U>
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator> &
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		operator=(kerbal::assign::assign_list<U> const & ilist)
		{
			this->assign(ilist);
			return *this;
		}

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		template <typename U>
		void
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		assign(kerbal::assign::assign_list<U> const & ilist)
		{
			this->hash_table::assign_unique(ilist);
		}

#	endif

	//===================
	// lookup

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		typename
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		find(const_reference key) const
		{
			return this->hash_table::find(key);
		}

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		typename
		kerbal::utility::compressed_pair<
			typename hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator,
			typename hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::const_iterator
		>
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		equal_range(const_reference key) const
		{
			return this->hash_table::equal_range(key);
		}

	//===================
	// insert

#	if __cplusplus >= 201103L

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		emplace(Args&& ... args)
		{
			return this->hash_table::emplace_unique(kerbal::utility::forward<Args>(args)...);
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) KERBAL_MACRO_CONCAT(Arg, i) const & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r \
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>:: \
		emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->hash_table::emplace_unique(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		typename
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(const_reference src)
		{
			return this->hash_table::insert_unique(src);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		typename
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::unique_insert_r
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(rvalue_reference src)
		{
			return this->hash_table::insert_unique(kerbal::compatibility::move(src));
		}

#	endif

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(InputIterator first, InputIterator last)
		{
			this->hash_table::insert_unique(first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		void
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(std::initializer_list<value_type> ilist)
		{
			this->hash_table::insert_unique(ilist);
		}

#	else

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		template <typename U>
		KERBAL_CONSTEXPR20
		void
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		insert(kerbal::assign::assign_list<U> const & ilist)
		{
			this->hash_table::insert_unique(ilist);
		}

#	endif

	//===================
	// erase

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		typename
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		erase_not_end_unsafe(const_iterator pos) KERBAL_NOEXCEPT
		{
			return this->hash_table::erase_not_end_unsafe(pos);
		}

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		typename
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		erase(const_iterator pos) KERBAL_NOEXCEPT
		{
			return this->hash_table::erase(pos);
		}

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		typename
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::iterator
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		erase(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			return this->hash_table::erase(first, last);
		}

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		typename
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::size_type
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		erase(key_type const & key) KERBAL_NOEXCEPT
		{
			return this->hash_table::erase_unique(key);
		}

		template <typename T, typename Hash, typename KeyEqual, typename NodeAllocator, typename BucketAllocator>
		KERBAL_CONSTEXPR20
		void
		hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>::
		clear() KERBAL_NOEXCEPT
		{
			return this->hash_table::clear();
		}

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_HASH_SET_HASH_SET_IMPL_HPP
