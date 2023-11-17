/**
 * @file       avl_multiset.impl.hpp
 * @brief
 * @date       2023-11-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_AVL_MULTISET_AVL_MULTISET_IMPL_HPP
#define KERBAL_CONTAINER_AVL_MULTISET_AVL_MULTISET_IMPL_HPP

#include <kerbal/container/avl_multiset/avl_multiset.decl.hpp>
#include <kerbal/container/avl_ordered/avl_ordered.impl.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

#	if __cplusplus < 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset()
		{
		}

#	endif

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(const Allocator & alloc) :
			avl_ordered(alloc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(const KeyCompare & kc) :
			avl_ordered(kc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(const KeyCompare & kc, const Allocator & alloc) :
			avl_ordered(kc, alloc)
		{
		}


		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(const avl_multiset & src) :
			avl_ordered(static_cast<const avl_ordered &>(src))
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(const avl_multiset & src, const Allocator & alloc) :
			avl_ordered(static_cast<const avl_ordered &>(src), alloc)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(avl_multiset && src) :
			avl_ordered(static_cast<avl_ordered &&>(src))
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(avl_multiset && src, const Allocator & alloc) :
			avl_ordered(static_cast<avl_ordered &&>(src), alloc)
		{
		}

#	endif


		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			InputIterator first, InputIterator last
		) :
			avl_ordered(first, last)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			InputIterator first, InputIterator last,
			const Allocator & alloc
		) :
			avl_ordered(first, last, alloc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			InputIterator first, InputIterator last,
			const KeyCompare & kc
		) :
			avl_ordered(first, last, kc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			InputIterator first, InputIterator last,
			const KeyCompare & kc, const Allocator & alloc
		) :
			avl_ordered(first, last, kc, alloc)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			std::initializer_list<value_type> ilist
		) :
			avl_ordered(ilist)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			std::initializer_list<value_type> ilist,
			const Allocator & alloc
		) :
			avl_ordered(ilist, alloc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			std::initializer_list<value_type> ilist,
			const KeyCompare & kc
		) :
			avl_ordered(ilist, kc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			std::initializer_list<value_type> ilist,
			const KeyCompare & kc, const Allocator & alloc
		) :
			avl_ordered(ilist, kc, alloc)
		{
		}

#	else

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			const kerbal::assign::assign_list<U> & ilist
		) :
			avl_ordered(ilist)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			const kerbal::assign::assign_list<U> & ilist,
			const Allocator & alloc
		) :
			avl_ordered(ilist, alloc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			const kerbal::assign::assign_list<U> & ilist,
			const KeyCompare & kc
		) :
			avl_ordered(ilist, kc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_multiset<T, KeyCompare, Allocator>::
		avl_multiset(
			const kerbal::assign::assign_list<U> & ilist,
			const KeyCompare & kc, const Allocator & alloc
		) :
			avl_ordered(ilist, kc, alloc)
		{
		}

#	endif


		//===================
		// assign

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator> &
		avl_multiset<T, KeyCompare, Allocator>::
		operator=(const avl_multiset & src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator> &
		avl_multiset<T, KeyCompare, Allocator>::
		operator=(avl_multiset && src)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_multiset<T, KeyCompare, Allocator> &
		avl_multiset<T, KeyCompare, Allocator>::
		operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	else

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_multiset<T, KeyCompare, Allocator> &
		avl_multiset<T, KeyCompare, Allocator>::
		operator=(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	endif


		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		assign(const avl_multiset & src)
		{
			this->avl_ordered::assign(static_cast<const avl_ordered &>(src));
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		assign(avl_multiset && src)
		{
			this->avl_ordered::assign(static_cast<avl_ordered &&>(src));
		}

#	endif

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		assign(InputIterator first, InputIterator last)
		{
			this->avl_ordered::assign(first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		assign(std::initializer_list<value_type> ilist)
		{
			this->avl_ordered::assign(ilist);
		}

#	else

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		void
		avl_multiset<T, KeyCompare, Allocator>::
		assign(const kerbal::assign::assign_list<U> & ilist)
		{
			this->avl_ordered::assign(ilist);
		}

#	endif


		//===================
		// lookup

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::const_iterator
		avl_multiset<T, KeyCompare, Allocator>::
		find(const key_type & key) const
		{
			return this->avl_ordered::find(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_multiset<T, KeyCompare, Allocator>::const_iterator
		>::type
		avl_multiset<T, KeyCompare, Allocator>::
		find(const Key & key) const
		{
			return this->avl_ordered::find(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::const_iterator
		avl_multiset<T, KeyCompare, Allocator>::
		lower_bound(const key_type & key) const
		{
			return this->avl_ordered::lower_bound(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_multiset<T, KeyCompare, Allocator>::const_iterator
		>::type
		avl_multiset<T, KeyCompare, Allocator>::
		lower_bound(const Key & key) const
		{
			return this->avl_ordered::lower_bound(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::const_iterator
		avl_multiset<T, KeyCompare, Allocator>::
		upper_bound(const key_type & key) const
		{
			return this->avl_ordered::upper_bound(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_multiset<T, KeyCompare, Allocator>::const_iterator
		>::type
		avl_multiset<T, KeyCompare, Allocator>::
		upper_bound(const Key & key) const
		{
			return this->avl_ordered::upper_bound(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		kerbal::utility::compressed_pair<
			typename avl_multiset<T, KeyCompare, Allocator>::const_iterator,
			typename avl_multiset<T, KeyCompare, Allocator>::const_iterator
		>
		avl_multiset<T, KeyCompare, Allocator>::
		equal_range(const key_type & key) const
		{
			return this->avl_ordered::equal_range(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			kerbal::utility::compressed_pair<
				typename avl_multiset<T, KeyCompare, Allocator>::const_iterator,
				typename avl_multiset<T, KeyCompare, Allocator>::const_iterator
			>
		>::type
		avl_multiset<T, KeyCompare, Allocator>::
		equal_range(const Key & key) const
		{
			return this->avl_ordered::equal_range(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		bool
		avl_multiset<T, KeyCompare, Allocator>::
		contains(const key_type & key) const
		{
			return this->avl_ordered::contains(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			bool
		>::type
		avl_multiset<T, KeyCompare, Allocator>::
		contains(const Key & key) const
		{
			return this->avl_ordered::contains(key);
		}



		//===================
		// insert

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::const_iterator
		avl_multiset<T, KeyCompare, Allocator>::
		emplace(Args && ... args)
		{
			return this->avl_ordered::emplace(kerbal::utility::forward<Args>(args)...);
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T, typename KeyCompare, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		avl_multiset<T, KeyCompare, Allocator>::const_iterator \
		avl_multiset<T, KeyCompare, Allocator>:: \
		emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->avl_ordered::emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
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

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::const_iterator
		avl_multiset<T, KeyCompare, Allocator>::
		insert(const_reference src)
		{
			return this->avl_ordered::insert(src);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::const_iterator
		avl_multiset<T, KeyCompare, Allocator>::
		insert(rvalue_reference src)
		{
			return this->avl_ordered::insert(kerbal::compatibility::move(src));
		}

#	endif

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		insert(InputIterator first, InputIterator last)
		{
			this->avl_ordered::insert(first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		insert(std::initializer_list<value_type> ilist)
		{
			this->avl_ordered::insert(ilist);
		}

#	else

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		void
		avl_multiset<T, KeyCompare, Allocator>::
		insert(const kerbal::assign::assign_list<U> & ilist)
		{
			this->avl_ordered::insert(ilist);
		}

#	endif


		//===================
		// erase

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::iterator
		avl_multiset<T, KeyCompare, Allocator>::
		erase_not_end_unsafe(const_iterator pos) KERBAL_NOEXCEPT
		{
			return this->avl_ordered::erase_not_end_unsafe(pos);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::iterator
		avl_multiset<T, KeyCompare, Allocator>::
		erase(const_iterator pos) KERBAL_NOEXCEPT
		{
			return this->avl_ordered::erase(pos);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::iterator
		avl_multiset<T, KeyCompare, Allocator>::
		erase(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			return this->avl_ordered::erase(first, last);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::size_type
		avl_multiset<T, KeyCompare, Allocator>::
		erase(const key_type & key) KERBAL_NOEXCEPT
		{
			return this->avl_ordered::erase(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_multiset<T, KeyCompare, Allocator>::size_type
		>::type
		avl_multiset<T, KeyCompare, Allocator>::
		erase(const Key & key) KERBAL_NOEXCEPT
		{
			return this->avl_ordered::erase(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		clear() KERBAL_NOEXCEPT
		{
			this->avl_ordered::clear();
		}


		//===================
		// replace

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		avl_multiset<T, KeyCompare, Allocator>::const_iterator
		avl_multiset<T, KeyCompare, Allocator>::
		replace_emplace(
			const_iterator replace,
			Args && ... args
		)
		{
			return this->avl_ordered::replace_emplace(
				replace,
				kerbal::utility::forward<Args>(args)...
			);
		}

#	else

#	define EMPTY
#	define LEFT_JOIN_COMMA(exp) , exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T, typename KeyCompare, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		avl_multiset<T, KeyCompare, Allocator>::const_iterator \
		avl_multiset<T, KeyCompare, Allocator>:: \
		replace_emplace( \
			const_iterator replace \
			KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
		) \
		{ \
			return this->avl_ordered::replace_emplace( \
				replace \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef LEFT_JOIN_COMMA
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif


		//===================
		// operation

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename OtherKeyCompare>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		merge(avl_multiset<T, OtherKeyCompare, Allocator> & other)
		{
			this->avl_ordered::merge(static_cast<avl_ordered &>(other));
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename OtherKeyCompare>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		merge(avl_multiset<T, OtherKeyCompare, Allocator> && other)
		{
			this->avl_ordered::merge(static_cast<avl_ordered &&>(other));
		}

#	endif

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_multiset<T, KeyCompare, Allocator>::
		swap(avl_multiset & other)
		{
			this->avl_ordered::swap(static_cast<avl_ordered &>(other));
		}

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_AVL_MULTISET_AVL_MULTISET_IMPL_HPP
