/**
 * @file       list.impl.hpp
 * @brief
 * @date       2020-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_LIST_LIST_IMPL_HPP
#define KERBAL_CONTAINER_LIST_LIST_IMPL_HPP

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/utility/declval.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/detail/list_base/list_base.impl.hpp>
#include <kerbal/container/list/list.decl.hpp>


namespace kerbal
{

	namespace container
	{

	//===================
	// construct/copy/destroy

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list()
			KERBAL_CONDITIONAL_NOEXCEPT(
				list_allocator_overload::try_test_is_nothrow_default_constructible::IS_TRUE::value &&
				list_type_only::is_nothrow_init_to_self_constructible::value
			) :
			list_allocator_overload(),
			list_type_only(detail::init_list_node_ptr_to_self_tag())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(const Allocator & alloc)
			KERBAL_CONDITIONAL_NOEXCEPT(
				list_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
				list_type_only::is_nothrow_init_to_self_constructible::value
			) :
			list_allocator_overload(alloc),
			list_type_only(detail::init_list_node_ptr_to_self_tag())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(const list & src) :
			list_allocator_overload(),
			list_type_only(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(const list & src, const Allocator & alloc) :
			list_allocator_overload(alloc),
			list_type_only(this->alloc(), src.cbegin(), src.cend())
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(list && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				list_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<Allocator &&>::IS_TRUE::value &&
				list_type_only::is_nothrow_move_constructible::value
			) :
			list_allocator_overload(kerbal::compatibility::move(src.alloc())),
			list_type_only(static_cast<list_type_only &&>(src))
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(list && src, const Allocator & alloc)
			KERBAL_CONDITIONAL_NOEXCEPT(
				list_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
				list_type_only::template is_nothrow_move_constructible_using_allocator<node_allocator_type>::value
			) :
			list_allocator_overload(alloc),
			list_type_only(
				this->alloc(),
				kerbal::compatibility::move(src.alloc()),
				static_cast<list_type_only &&>(src)
			)
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(size_type n) :
			list_allocator_overload(),
			list_type_only(this->alloc(), n)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(size_type n, const Allocator & alloc) :
			list_allocator_overload(alloc),
			list_type_only(this->alloc(), n)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(size_type n, const_reference val) :
			list_allocator_overload(),
			list_type_only(this->alloc(), n, val)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(size_type n, const_reference val, const Allocator & alloc) :
			list_allocator_overload(alloc),
			list_type_only(this->alloc(), n, val)
		{
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(
			InputIterator first, InputIterator last,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
			>::type
		) :
			list_allocator_overload(),
			list_type_only(this->alloc(), first, last)
		{
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(
			InputIterator first, InputIterator last,
			const Allocator & alloc,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
			>::type
		) :
			list_allocator_overload(alloc),
			list_type_only(this->alloc(), first, last)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(std::initializer_list<value_type> ilist) :
			list(ilist.begin(), ilist.end())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::list(std::initializer_list<value_type> ilist, const Allocator & alloc) :
			list(ilist.begin(), ilist.end(), alloc)
		{
		}

#	else

		template <typename T, typename Allocator>
		list<T, Allocator>::list(const kerbal::assign::assign_list<void> & ilist) :
			list_allocator_overload(),
			list_type_only()
		{
		}

		template <typename T, typename Allocator>
		template <typename U>
		list<T, Allocator>::list(const kerbal::assign::assign_list<U> & ilist) :
			list_allocator_overload(),
			list_type_only(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

		template <typename T, typename Allocator>
		list<T, Allocator>::list(const kerbal::assign::assign_list<void> & ilist, const Allocator & alloc) :
			list_allocator_overload(alloc),
			list_type_only()
		{
		}

		template <typename T, typename Allocator>
		template <typename U>
		list<T, Allocator>::list(const kerbal::assign::assign_list<U> & ilist, const Allocator & alloc) :
			list_allocator_overload(alloc),
			list_type_only(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator>::~list()
		{
			this->list_type_only::k_destroy_using_allocator(this->alloc());
		}


	//===================
	// assign

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> &
		list<T, Allocator>::operator=(const list & src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> &
		list<T, Allocator>::operator=(list && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(kerbal::utility::declthis<list>()->assign(kerbal::compatibility::move(src)))
			)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> &
		list<T, Allocator>::operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	else

		template <typename T, typename Allocator>
		list<T, Allocator> &
		list<T, Allocator>::operator=(const kerbal::assign::assign_list<void> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

		template <typename T, typename Allocator>
		template <typename U>
		list<T, Allocator> &
		list<T, Allocator>::operator=(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::assign(const list & src)
		{
			list_type_only::k_assign_using_allocator(
				this->alloc(),
				src.alloc(),
				static_cast<const list_type_only &>(src)
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::assign(list && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				list_type_only::template is_nothrow_move_assign_using_allocator<node_allocator_type>::value
			)
		{
			this->list_type_only::k_assign_using_allocator(
				this->alloc(),
				kerbal::compatibility::move(src.alloc()),
				static_cast<list_type_only &&>(src)
			);
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::assign(size_type count, const_reference val)
		{
			list_type_only::k_assign_using_allocator(this->alloc(), count, val);
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		list<T, Allocator>::assign(InputIterator first, InputIterator last)
		{
			list_type_only::k_assign_using_allocator(this->alloc(), first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::assign(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
		}

#	else

		template <typename T, typename Allocator>
		void list<T, Allocator>::assign(const kerbal::assign::assign_list<void> & ilist)
		{
			this->clear();
		}

		template <typename T, typename Allocator>
		template <typename U>
		void list<T, Allocator>::assign(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist.cbegin(), ilist.cend());
		}

#	endif


	//===================
	// insert

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::iterator
		list<T, Allocator>::emplace(const_iterator pos, Args && ... args)
		{
			return list_type_only::k_emplace_using_allocator(
				this->alloc(),
				pos,
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
		template <typename T, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		list<T, Allocator>::iterator \
		list<T, Allocator>::emplace( \
			const_iterator pos \
			KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
		) \
		{ \
			return list_type_only::k_emplace_using_allocator( \
				this->alloc(), \
				pos \
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

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::iterator
		list<T, Allocator>::insert(const_iterator pos, const_reference val)
		{
			return list_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				val
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::iterator
		list<T, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return list_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				kerbal::compatibility::move(val)
			);
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::iterator
		list<T, Allocator>::insert(const_iterator pos, size_type n, const_reference val)
		{
			return list_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				n, val
			);
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
			typename list<T, Allocator>::iterator
		>::type
		list<T, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			return list_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				first, last
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::iterator
		list<T, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> ilist)
		{
			return this->insert(pos, ilist.begin(), ilist.end());
		}

#	else

		template <typename T, typename Allocator>
		typename
		list<T, Allocator>::iterator
		list<T, Allocator>::insert(const_iterator pos, const kerbal::assign::assign_list<void> & ilist)
		{
			return pos.cast_to_mutable();
		}

		template <typename T, typename Allocator>
		template <typename U>
		typename
		list<T, Allocator>::iterator
		list<T, Allocator>::insert(const_iterator pos, const kerbal::assign::assign_list<U> & ilist)
		{
			return this->insert(pos, ilist.begin(), ilist.end());
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::reference
		list<T, Allocator>::emplace_front(Args && ... args)
		{
			return this->list_type_only::k_emplace_front_using_allocator(
				this->alloc(),
				kerbal::utility::forward<Args>(args)...
			);
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		list<T, Allocator>::reference \
		list<T, Allocator>::emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->list_type_only::k_emplace_front_using_allocator( \
				this->alloc() \
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

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::push_front(const_reference val)
		{
			this->list_type_only::k_push_front_using_allocator(
				this->alloc(),
				val
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::push_front(rvalue_reference val)
		{
			this->list_type_only::k_push_front_using_allocator(
				this->alloc(),
				kerbal::compatibility::move(val)
			);
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::reference
		list<T, Allocator>::emplace_back(Args && ... args)
		{
			return this->list_type_only::k_emplace_back_using_allocator(
				this->alloc(),
				kerbal::utility::forward<Args>(args)...
			);
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		list<T, Allocator>::reference \
		list<T, Allocator>::emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->list_type_only::k_emplace_back_using_allocator( \
				this->alloc() \
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

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::push_back(const_reference val)
		{
			this->list_type_only::k_emplace_back_using_allocator(
				this->alloc(),
				val
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::push_back(rvalue_reference val)
		{
			this->list_type_only::k_emplace_back_using_allocator(
				this->alloc(),
				kerbal::compatibility::move(val)
			);
		}

#	endif


	//===================
	// erase

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::iterator
		list<T, Allocator>::erase(const_iterator pos)
		{
			return list_type_only::k_erase_using_allocator(this->alloc(), pos);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::iterator
		list<T, Allocator>::erase(const_iterator first, const_iterator last)
		{
			return list_type_only::k_erase_using_allocator(this->alloc(), first, last);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::pop_front()
		{
			this->list_type_only::k_pop_front_using_allocator(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::pop_back()
		{
			this->list_type_only::k_pop_back_using_allocator(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::clear()
			KERBAL_CONDITIONAL_NOEXCEPT(
				is_nothrow_clearable::value
			)
		{
			this->list_type_only::k_clear_using_allocator(this->alloc());
		}


	//===================
	// operation

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::resize(size_type count)
		{
			list_type_only::k_resize_using_allocator(this->alloc(), count);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::resize(size_type count, const_reference value)
		{
			list_type_only::k_resize_using_allocator(this->alloc(), count, value);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::swap(list & with)
			KERBAL_CONDITIONAL_NOEXCEPT(
				is_nothrow_swappable::value
			)
		{
			list_allocator_overload::k_swap_allocator_if_propagate(
				static_cast<list_allocator_overload &>(*this),
				static_cast<list_allocator_overload &>(with)
			);
			list_type_unrelated::k_swap_type_unrelated(
				static_cast<list_type_unrelated &>(*this),
				static_cast<list_type_unrelated &>(with)
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::iter_swap(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
		{
			list_type_only::k_iter_swap(a, b);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::reverse(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
		{
			list_type_only::k_reverse(a, b);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::merge(list & other, BinaryPredict cmp)
		{
			list_type_only::k_merge(static_cast<list_type_only &>(other), cmp);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::merge(list & other)
		{
			list_type_only::k_merge(static_cast<list_type_only &>(other));
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::merge(list && other, BinaryPredict cmp)
		{
			list_type_only::k_merge(static_cast<list_type_only &&>(other), cmp);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::merge(list && other)
		{
			list_type_only::k_merge(static_cast<list_type_only &&>(other));
		}

#	endif

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::sort(const_iterator first, const_iterator last, BinaryPredict cmp)
		{
			list_type_only::k_sort(first, last, cmp);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::sort(const_iterator first, const_iterator last)
		{
			list_type_only::k_sort(first, last);
		}

		template <typename T, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::size_type
		list<T, Allocator>::remove_if(const_iterator first, const_iterator last, UnaryPredicate predicate)
		{
			return list_type_only::k_remove_if_using_allocator(this->alloc(), first, last, predicate);
		}

		template <typename T, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::size_type
		list<T, Allocator>::remove_if(UnaryPredicate predicate)
		{
			return list_type_only::k_remove_if_using_allocator(this->alloc(), predicate);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::size_type
		list<T, Allocator>::remove(const_iterator first, const_iterator last, const_reference val)
		{
			return list_type_only::k_remove_using_allocator(this->alloc(), first, last, val);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::size_type
		list<T, Allocator>::remove(const_reference val)
		{
			return list_type_only::k_remove_using_allocator(this->alloc(), val);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredicate>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::size_type
		list<T, Allocator>::unique(const_iterator first, const_iterator last, BinaryPredicate pred)
		{
			return list_type_only::k_unique_using_allocator(this->alloc(), first, last, pred);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredicate>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::size_type
		list<T, Allocator>::unique(BinaryPredicate pred)
		{
			return list_type_only::k_unique_using_allocator(this->alloc(), pred);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::size_type
		list<T, Allocator>::unique(const_iterator first, const_iterator last)
		{
			return list_type_only::k_unique_using_allocator(this->alloc(), first, last);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		list<T, Allocator>::size_type
		list<T, Allocator>::unique()
		{
			return list_type_only::k_unique_using_allocator(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::splice(
			const_iterator pos, list & other
		) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(
				pos,
				static_cast<list_type_unrelated &>(other)
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::splice(
			const_iterator pos, list & /*other*/,
			const_iterator opos
		) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, opos);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::splice(
			const_iterator pos, list & /*other*/,
			const_iterator first, const_iterator last
		) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::splice(
			const_iterator pos, list && other
		) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(
				pos,
				static_cast<list_type_unrelated &&>(other)
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::splice(
			const_iterator pos, list && /*other*/,
			const_iterator opos
		) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, opos);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::splice(
			const_iterator pos, list && /*other*/,
			const_iterator first, const_iterator last
		) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, first, last);
		}

#	endif

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::set_difference(list & l1, const list & l2, list & lto, BinaryPredict cmp)
		{
			list_type_only::k_set_difference(
				static_cast<list_type_only &>(l1),
				static_cast<const list_type_only &>(l2),
				static_cast<list_type_only &>(lto),
				cmp
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::set_difference(list & l1, const list & l2, list & lto)
		{
			list_type_only::k_set_difference(
				static_cast<list_type_only &>(l1),
				static_cast<const list_type_only &>(l2),
				static_cast<list_type_only &>(lto)
			);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::set_intersection(list & l1, list & l2, list & lto, BinaryPredict cmp)
		{
			list_type_only::k_set_intersection(
				static_cast<list_type_only &>(l1),
				static_cast<list_type_only &>(l2),
				static_cast<list_type_only &>(lto),
				cmp
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::set_intersection(list & l1, list & l2, list & lto)
		{
			list_type_only::k_set_intersection(
				static_cast<list_type_only &>(l1),
				static_cast<list_type_only &>(l2),
				static_cast<list_type_only &>(lto)
			);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::set_symmetric_difference(list & l1, list & l2, list & lto, BinaryPredict cmp)
		{
			list_type_only::k_set_symmetric_difference(
				static_cast<list_type_only &>(l1),
				static_cast<list_type_only &>(l2),
				static_cast<list_type_only &>(lto),
				cmp
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::set_symmetric_difference(list & l1, list & l2, list & lto)
		{
			list_type_only::k_set_symmetric_difference(
				static_cast<list_type_only &>(l1),
				static_cast<list_type_only &>(l2),
				static_cast<list_type_only &>(lto)
			);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::set_union(list & l1, list & l2, list & lto, BinaryPredict cmp)
		{
			list_type_only::k_set_union(
				static_cast<list_type_only &>(l1),
				static_cast<list_type_only &>(l2),
				static_cast<list_type_only &>(lto),
				cmp
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<T, Allocator>::set_union(list & l1, list & l2, list & lto)
		{
			list_type_only::k_set_union(
				static_cast<list_type_only &>(l1),
				static_cast<list_type_only &>(l2),
				static_cast<list_type_only &>(lto)
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> & list<T, Allocator>::operator+=(const list & with)
		{
			this->insert(this->cend(), with.cbegin(), with.cend());
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> & list<T, Allocator>::operator+=(list && with)
		{
			this->splice(this->cend(), kerbal::compatibility::move(with));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> & list<T, Allocator>::operator+=(std::initializer_list<value_type> with)
		{
			this->insert(this->cend(), with.begin(), with.end());
			return *this;
		}

#	else

		template <typename T, typename Allocator>
		list<T, Allocator> & list<T, Allocator>::operator+=(const kerbal::assign::assign_list<void> & with)
		{
			return *this;
		}

		template <typename T, typename Allocator>
		template <typename U>
		list<T, Allocator> & list<T, Allocator>::operator+=(const kerbal::assign::assign_list<U> & with)
		{
			this->insert(this->cend(), with.cbegin(), with.cend());
			return *this;
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> operator+(const list<T, Allocator> & lhs, const list<T, Allocator> & rhs)
		{
			list<T, Allocator> r(lhs);
			r.insert(r.cend(), rhs.cbegin(), rhs.cend());
			return r;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> operator+(const list<T, Allocator> & lhs, list<T, Allocator> && rhs)
		{
			list<T, Allocator> r(lhs);
			r += kerbal::compatibility::move(rhs);
			return r;
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> operator+(list<T, Allocator> && lhs, const list<T, Allocator> & rhs)
		{
			list<T, Allocator> r(kerbal::compatibility::move(lhs));
			r += rhs;
			return r;
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		list<T, Allocator> operator+(list<T, Allocator> && lhs, list<T, Allocator> && rhs)
		{
			list<T, Allocator> r(kerbal::compatibility::move(lhs));
			r += kerbal::compatibility::move(rhs);
			return r;
		}

#	endif

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_LIST_LIST_IMPL_HPP
