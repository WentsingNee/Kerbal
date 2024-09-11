/**
 * @file       rb_set.impl.hpp
 * @brief
 * @date       2024-09-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_RB_SET_RB_SET_IMPL_HPP
#define KERBAL_CONTAINER_RB_SET_RB_SET_IMPL_HPP

#include <kerbal/container/rb_set/rb_set.decl.hpp>
#include <kerbal/container/rb_ordered/rb_ordered.impl.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>
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
		rb_set<T, KeyCompare, Allocator>::
		rb_set()
		{
		}

#	endif

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(const Allocator & alloc) :
			rb_ordered(alloc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(const KeyCompare & kc) :
			rb_ordered(kc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(const KeyCompare & kc, const Allocator & alloc) :
			rb_ordered(kc, alloc)
		{
		}


		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(const rb_set & src) :
			rb_ordered(static_cast<const rb_ordered &>(src))
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(const rb_set & src, const Allocator & alloc) :
			rb_ordered(static_cast<const rb_ordered &>(src), alloc)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(rb_set && src) :
			rb_ordered(static_cast<rb_ordered &&>(src))
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(rb_set && src, const Allocator & alloc) :
			rb_ordered(static_cast<rb_ordered &&>(src), alloc)
		{
		}

#	endif


		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			InputIterator first, InputIterator last
		) :
			rb_ordered(kerbal::container::unique_tag_t(), first, last)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			InputIterator first, InputIterator last,
			const Allocator & alloc
		) :
			rb_ordered(kerbal::container::unique_tag_t(), first, last, alloc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			InputIterator first, InputIterator last,
			const KeyCompare & kc
		) :
			rb_ordered(kerbal::container::unique_tag_t(), first, last, kc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			InputIterator first, InputIterator last,
			const KeyCompare & kc, const Allocator & alloc
		) :
			rb_ordered(kerbal::container::unique_tag_t(), first, last, kc, alloc)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			std::initializer_list<value_type> ilist
		) :
			rb_ordered(kerbal::container::unique_tag_t(), ilist)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			std::initializer_list<value_type> ilist,
			const Allocator & alloc
		) :
			rb_ordered(kerbal::container::unique_tag_t(), ilist, alloc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			std::initializer_list<value_type> ilist,
			const KeyCompare & kc
		) :
			rb_ordered(kerbal::container::unique_tag_t(), ilist, kc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			std::initializer_list<value_type> ilist,
			const KeyCompare & kc, const Allocator & alloc
		) :
			rb_ordered(kerbal::container::unique_tag_t(), ilist, kc, alloc)
		{
		}

#	else

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			const kerbal::assign::assign_list<U> & ilist
		) :
			rb_ordered(kerbal::container::unique_tag_t(), ilist)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			const kerbal::assign::assign_list<U> & ilist,
			const Allocator & alloc
		) :
			rb_ordered(kerbal::container::unique_tag_t(), ilist, alloc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			const kerbal::assign::assign_list<U> & ilist,
			const KeyCompare & kc
		) :
			rb_ordered(kerbal::container::unique_tag_t(), ilist, kc)
		{
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		rb_set<T, KeyCompare, Allocator>::
		rb_set(
			const kerbal::assign::assign_list<U> & ilist,
			const KeyCompare & kc, const Allocator & alloc
		) :
			rb_ordered(kerbal::container::unique_tag_t(), ilist, kc, alloc)
		{
		}

#	endif


		//===================
		// assign

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator> &
		rb_set<T, KeyCompare, Allocator>::
		operator=(const rb_set & src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator> &
		rb_set<T, KeyCompare, Allocator>::
		operator=(rb_set && src)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		rb_set<T, KeyCompare, Allocator> &
		rb_set<T, KeyCompare, Allocator>::
		operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	else

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		rb_set<T, KeyCompare, Allocator> &
		rb_set<T, KeyCompare, Allocator>::
		operator=(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	endif


		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		rb_set<T, KeyCompare, Allocator>::
		assign(const rb_set & src)
		{
			this->rb_ordered::assign(static_cast<const rb_ordered &>(src));
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		rb_set<T, KeyCompare, Allocator>::
		assign(rb_set && src)
		{
			this->rb_ordered::assign(static_cast<rb_ordered &&>(src));
		}

#	endif

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		rb_set<T, KeyCompare, Allocator>::
		assign(InputIterator first, InputIterator last)
		{
			this->rb_ordered::assign_unique(first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		rb_set<T, KeyCompare, Allocator>::
		assign(std::initializer_list<value_type> ilist)
		{
			this->rb_ordered::assign_unique(ilist);
		}

#	else

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		void
		rb_set<T, KeyCompare, Allocator>::
		assign(const kerbal::assign::assign_list<U> & ilist)
		{
			this->rb_ordered::assign_unique(ilist);
		}

#	endif


		//===================
		// lookup

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::const_iterator
		rb_set<T, KeyCompare, Allocator>::
		find(const key_type & key) const
		{
			return this->rb_ordered::find(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename rb_set<T, KeyCompare, Allocator>::const_iterator
		>::type
		rb_set<T, KeyCompare, Allocator>::
		find(const Key & key) const
		{
			return this->rb_ordered::find(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::const_iterator
		rb_set<T, KeyCompare, Allocator>::
		lower_bound(const key_type & key) const
		{
			return this->rb_ordered::lower_bound(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename rb_set<T, KeyCompare, Allocator>::const_iterator
		>::type
		rb_set<T, KeyCompare, Allocator>::
		lower_bound(const Key & key) const
		{
			return this->rb_ordered::lower_bound(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::const_iterator
		rb_set<T, KeyCompare, Allocator>::
		upper_bound(const key_type & key) const
		{
			return this->rb_ordered::upper_bound(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename rb_set<T, KeyCompare, Allocator>::const_iterator
		>::type
		rb_set<T, KeyCompare, Allocator>::
		upper_bound(const Key & key) const
		{
			return this->rb_ordered::upper_bound(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		kerbal::utility::compressed_pair<
			typename rb_set<T, KeyCompare, Allocator>::const_iterator,
			typename rb_set<T, KeyCompare, Allocator>::const_iterator
		>
		rb_set<T, KeyCompare, Allocator>::
		equal_range(const key_type & key) const
		{
			return this->rb_ordered::equal_range(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			kerbal::utility::compressed_pair<
				typename rb_set<T, KeyCompare, Allocator>::const_iterator,
				typename rb_set<T, KeyCompare, Allocator>::const_iterator
			>
		>::type
		rb_set<T, KeyCompare, Allocator>::
		equal_range(const Key & key) const
		{
			return this->rb_ordered::equal_range(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		bool
		rb_set<T, KeyCompare, Allocator>::
		contains(const key_type & key) const
		{
			return this->rb_ordered::contains(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			bool
		>::type
		rb_set<T, KeyCompare, Allocator>::
		contains(const Key & key) const
		{
			return this->rb_ordered::contains(key);
		}



		//===================
		// insert

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::unique_insert_r
		rb_set<T, KeyCompare, Allocator>::
		emplace(Args && ... args)
		{
			return this->rb_ordered::emplace_unique(kerbal::utility::forward<Args>(args)...);
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
		rb_set<T, KeyCompare, Allocator>::unique_insert_r \
		rb_set<T, KeyCompare, Allocator>:: \
		emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->rb_ordered::emplace_unique(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
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
		rb_set<T, KeyCompare, Allocator>::unique_insert_r
		rb_set<T, KeyCompare, Allocator>::
		insert(const_reference src)
		{
			return this->rb_ordered::insert_unique(src);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::unique_insert_r
		rb_set<T, KeyCompare, Allocator>::
		insert(rvalue_reference src)
		{
			return this->rb_ordered::insert_unique(kerbal::compatibility::move(src));
		}

#	endif

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		rb_set<T, KeyCompare, Allocator>::
		insert(InputIterator first, InputIterator last)
		{
			this->rb_ordered::insert_unique(first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		rb_set<T, KeyCompare, Allocator>::
		insert(std::initializer_list<value_type> ilist)
		{
			this->rb_ordered::insert_unique(ilist);
		}

#	else

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename U>
		void
		rb_set<T, KeyCompare, Allocator>::
		insert(const kerbal::assign::assign_list<U> & ilist)
		{
			this->rb_ordered::insert_unique(ilist);
		}

#	endif


		//===================
		// erase

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::iterator
		rb_set<T, KeyCompare, Allocator>::
		erase_not_end_unsafe(const_iterator pos) KERBAL_NOEXCEPT
		{
			return this->rb_ordered::erase_not_end_unsafe(pos);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::iterator
		rb_set<T, KeyCompare, Allocator>::
		erase(const_iterator pos) KERBAL_NOEXCEPT
		{
			return this->rb_ordered::erase(pos);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::iterator
		rb_set<T, KeyCompare, Allocator>::
		erase(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			return this->rb_ordered::erase(first, last);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::size_type
		rb_set<T, KeyCompare, Allocator>::
		erase(const key_type & key) KERBAL_NOEXCEPT
		{
			return this->rb_ordered::erase(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename rb_set<T, KeyCompare, Allocator>::size_type
		>::type
		rb_set<T, KeyCompare, Allocator>::
		erase(const Key & key) KERBAL_NOEXCEPT
		{
			return this->rb_ordered::erase(key);
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		rb_set<T, KeyCompare, Allocator>::
		clear() KERBAL_NOEXCEPT
		{
			this->rb_ordered::clear();
		}


		//===================
		// replace

#	if __cplusplus >= 201103L

		template <typename T, typename KeyCompare, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		rb_set<T, KeyCompare, Allocator>::unique_insert_r
		rb_set<T, KeyCompare, Allocator>::
		replace_emplace(
			const_iterator replace,
			Args && ... args
		)
		{
			return this->rb_ordered::replace_emplace_unique(
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
		rb_set<T, KeyCompare, Allocator>::unique_insert_r \
		rb_set<T, KeyCompare, Allocator>:: \
		replace_emplace( \
			const_iterator replace \
			KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
		) \
		{ \
			return this->rb_ordered::replace_emplace_unique( \
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
		rb_set<T, KeyCompare, Allocator>::
		merge(rb_set<T, OtherKeyCompare, Allocator> & other)
		{
			this->rb_ordered::merge_unique(static_cast<rb_ordered &>(other));
		}

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		rb_set<T, KeyCompare, Allocator>::
		swap(rb_set & other)
		{
			this->rb_ordered::swap(static_cast<rb_ordered &>(other));
		}

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_RB_SET_RB_SET_IMPL_HPP
