/**
 * @file       forward_list.impl.hpp
 * @brief
 * @date       2021-01-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_IMPL_HPP
#define KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_IMPL_HPP

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

#include <kerbal/container/detail/forward_list_base/forward_list_base.impl.hpp>
#include <kerbal/container/forward_list/forward_list.decl.hpp>


namespace kerbal
{

	namespace container
	{

	//===================
	// construct/copy/destroy

#	if __cplusplus < 201103L

		template <typename T, typename Allocator>
		forward_list<T, Allocator>::forward_list() :
			fl_allocator_overload(),
			fl_type_only()
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(const Allocator & alloc)
			KERBAL_CONDITIONAL_NOEXCEPT(
				fl_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
				fl_type_only::is_nothrow_default_constructible::value
			) :
			fl_allocator_overload(alloc),
			fl_type_only()
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(const forward_list & src) :
			fl_allocator_overload(),
			fl_type_only(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(const forward_list & src, const Allocator & alloc) :
			fl_allocator_overload(alloc),
			fl_type_only(this->alloc(), src.cbegin(), src.cend())
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(forward_list && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				fl_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<Allocator &&>::IS_TRUE::value &&
				fl_type_only::is_nothrow_move_constructible::value
			) :
			fl_allocator_overload(kerbal::compatibility::move(src.alloc())),
			fl_type_only(static_cast<fl_type_only &&>(src))
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(forward_list && src, const Allocator & alloc)
			KERBAL_CONDITIONAL_NOEXCEPT(
				fl_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
				fl_type_only::template is_nothrow_move_constructible_using_allocator<node_allocator_type>::value
			) :
			fl_allocator_overload(alloc),
			fl_type_only(
				this->alloc(),
				kerbal::compatibility::move(src.alloc()),
				static_cast<fl_type_only &&>(src)
			)
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(size_type n) :
			fl_allocator_overload(),
			fl_type_only(this->alloc(), n)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(size_type n, const Allocator & alloc) :
			fl_allocator_overload(alloc),
			fl_type_only(this->alloc(), n)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(size_type n, const_reference val) :
			fl_allocator_overload(),
			fl_type_only(this->alloc(), n, val)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(size_type n, const_reference val, const Allocator & alloc) :
			fl_allocator_overload(alloc),
			fl_type_only(this->alloc(), n, val)
		{
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(
			InputIterator first, InputIterator last,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
			>::type
		) :
			fl_allocator_overload(),
			fl_type_only(this->alloc(), first, last)
		{
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(
			InputIterator first, InputIterator last,
			const Allocator & alloc,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
			>::type
		) :
			fl_allocator_overload(alloc),
			fl_type_only(this->alloc(), first, last)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(std::initializer_list<value_type> ilist) :
			forward_list(ilist.begin(), ilist.end())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::forward_list(std::initializer_list<value_type> ilist, const Allocator & alloc) :
			forward_list(ilist.begin(), ilist.end(), alloc)
		{
		}

#	else

		template <typename T, typename Allocator>
		forward_list<T, Allocator>::forward_list(const kerbal::assign::assign_list<void> & ilist) :
			fl_allocator_overload(),
			fl_type_only()
		{
		}

		template <typename T, typename Allocator>
		template <typename U>
		forward_list<T, Allocator>::forward_list(const kerbal::assign::assign_list<U> & ilist) :
			fl_allocator_overload(),
			fl_type_only(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

		template <typename T, typename Allocator>
		forward_list<T, Allocator>::forward_list(const kerbal::assign::assign_list<void> & ilist, const Allocator & alloc) :
			fl_allocator_overload(alloc),
			fl_type_only()
		{
		}

		template <typename T, typename Allocator>
		template <typename U>
		forward_list<T, Allocator>::forward_list(const kerbal::assign::assign_list<U> & ilist, const Allocator & alloc) :
			fl_allocator_overload(alloc),
			fl_type_only(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator>::~forward_list()
		{
			this->fl_type_only::k_destroy_using_allocator(this->alloc());
		}


	//===================
	// assign

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator> &
		forward_list<T, Allocator>::operator=(const forward_list & src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator> &
		forward_list<T, Allocator>::operator=(forward_list && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(kerbal::utility::declthis<forward_list>()->assign(kerbal::compatibility::move(src)))
			)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<T, Allocator> &
		forward_list<T, Allocator>::operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	else

		template <typename T, typename Allocator>
		forward_list<T, Allocator> &
		forward_list<T, Allocator>::operator=(const kerbal::assign::assign_list<void> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

		template <typename T, typename Allocator>
		template <typename U>
		forward_list<T, Allocator> &
		forward_list<T, Allocator>::operator=(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::assign(const forward_list & src)
		{
			fl_type_only::k_assign_using_allocator(
				this->alloc(),
				src.alloc(),
				static_cast<const fl_type_only &>(src)
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::assign(forward_list && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				fl_type_only::template is_nothrow_move_assign_using_allocator<node_allocator_type>::value
			)
		{
			this->fl_type_only::k_assign_using_allocator(
				this->alloc(),
				kerbal::compatibility::move(src.alloc()),
				static_cast<fl_type_only &&>(src)
			);
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::assign(size_type count, const_reference val)
		{
			fl_type_only::k_assign_using_allocator(this->alloc(), count, val);
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		forward_list<T, Allocator>::assign(InputIterator first, InputIterator last)
		{
			fl_type_only::k_assign_using_allocator(this->alloc(), first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::assign(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
		}

#	else

		template <typename T, typename Allocator>
		void forward_list<T, Allocator>::assign(const kerbal::assign::assign_list<void> & ilist)
		{
			this->clear();
		}

		template <typename T, typename Allocator>
		template <typename U>
		void forward_list<T, Allocator>::assign(const kerbal::assign::assign_list<U> & ilist)
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
		forward_list<T, Allocator>::iterator
		forward_list<T, Allocator>::emplace_after(const_iterator before_pos, Args && ... args)
		{
			return fl_type_only::k_emplace_after_using_allocator(
				this->alloc(),
				before_pos,
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
		forward_list<T, Allocator>::iterator \
		forward_list<T, Allocator>::emplace_after( \
			const_iterator before_pos \
			KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
		) \
		{ \
			return fl_type_only::k_emplace_after_using_allocator( \
				this->alloc(), \
				before_pos \
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
		forward_list<T, Allocator>::iterator
		forward_list<T, Allocator>::insert_after(const_iterator before_pos, const_reference val)
		{
			return fl_type_only::k_insert_after_using_allocator(
				this->alloc(),
				before_pos,
				val
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::iterator
		forward_list<T, Allocator>::insert_after(const_iterator before_pos, rvalue_reference val)
		{
			return fl_type_only::k_insert_after_using_allocator(
				this->alloc(),
				before_pos,
				kerbal::compatibility::move(val)
			);
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::iterator
		forward_list<T, Allocator>::insert_after(const_iterator before_pos, size_type n, const_reference val)
		{
			return fl_type_only::k_insert_after_using_allocator(
				this->alloc(),
				before_pos,
				n, val
			);
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
			typename forward_list<T, Allocator>::iterator
		>::type
		forward_list<T, Allocator>::insert_after(const_iterator before_pos, InputIterator first, InputIterator last)
		{
			return fl_type_only::k_insert_after_using_allocator(
				this->alloc(),
				before_pos,
				first, last
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::iterator
		forward_list<T, Allocator>::insert_after(const_iterator before_pos, std::initializer_list<value_type> ilist)
		{
			return this->insert_after(before_pos, ilist.begin(), ilist.end());
		}

#	else

		template <typename T, typename Allocator>
		typename
		forward_list<T, Allocator>::iterator
		forward_list<T, Allocator>::insert_after(const_iterator before_pos, const kerbal::assign::assign_list<void> & ilist)
		{
			return before_pos.cast_to_mutable();
		}

		template <typename T, typename Allocator>
		template <typename U>
		typename
		forward_list<T, Allocator>::iterator
		forward_list<T, Allocator>::insert_after(const_iterator before_pos, const kerbal::assign::assign_list<U> & ilist)
		{
			return this->insert_after(before_pos, ilist.cbegin(), ilist.cend());
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::reference
		forward_list<T, Allocator>::emplace_front(Args && ... args)
		{
			return this->fl_type_only::k_emplace_front_using_allocator(
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
		forward_list<T, Allocator>::reference \
		forward_list<T, Allocator>::emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->fl_type_only::k_emplace_front_using_allocator( \
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
		void forward_list<T, Allocator>::push_front(const_reference val)
		{
			this->fl_type_only::k_push_front_using_allocator(
				this->alloc(),
				val
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::push_front(rvalue_reference val)
		{
			this->fl_type_only::k_push_front_using_allocator(
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
		forward_list<T, Allocator>::iterator
		forward_list<T, Allocator>::erase_after(const_iterator before_pos)
		{
			return fl_type_only::k_erase_after_using_allocator(this->alloc(), before_pos);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::iterator
		forward_list<T, Allocator>::erase_after(const_iterator before_first, const_iterator last)
		{
			return fl_type_only::k_erase_after_using_allocator(this->alloc(), before_first, last);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::pop_front()
		{
			this->fl_type_only::k_pop_front_using_allocator(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::clear()
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(
					kerbal::utility::declthis<fl_type_only>()->k_clear_using_allocator(
						kerbal::utility::declthis<forward_list>()->alloc()
					)
				)
			)
		{
			this->fl_type_only::k_clear_using_allocator(this->alloc());
		}


	//===================
	// operation

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::resize(size_type count)
		{
			this->fl_type_only::k_resize_using_allocator(this->alloc(), count);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::resize(size_type count, const_reference value)
		{
			this->fl_type_only::k_resize_using_allocator(this->alloc(), count, value);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::swap(forward_list & with)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(
					fl_allocator_overload::k_swap_allocator_if_propagate(
						kerbal::utility::declval<fl_allocator_overload &>(),
						kerbal::utility::declval<fl_allocator_overload &>()
					)
				) &&
				noexcept(
					fl_type_unrelated::k_swap_type_unrelated(
						kerbal::utility::declval<fl_type_unrelated &>(),
						kerbal::utility::declval<fl_type_unrelated &>()
					)
				)
			)
		{
			fl_allocator_overload::k_swap_allocator_if_propagate(
				static_cast<fl_allocator_overload &>(*this),
				static_cast<fl_allocator_overload &>(with)
			);
			fl_type_unrelated::k_swap_type_unrelated(
				static_cast<fl_type_unrelated &>(*this),
				static_cast<fl_type_unrelated &>(with)
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::iter_swap_after(const_iterator before_a, const_iterator before_b) KERBAL_NOEXCEPT
		{
			fl_type_only::k_iter_swap_after(before_a, before_b);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::reverse_after(const_iterator before_first, const_iterator last) KERBAL_NOEXCEPT
		{
			fl_type_only::k_reverse_after(before_first, last);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::merge(forward_list & other, BinaryPredict cmp)
		{
			this->fl_type_only::k_merge(static_cast<fl_type_only &>(other), cmp);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::merge(forward_list & other)
		{
			this->fl_type_only::k_merge(static_cast<fl_type_only &>(other));
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::sort_after(const_iterator before_first, const_iterator last, BinaryPredict cmp)
		{
			fl_type_only::k_sort_after(before_first, last, cmp);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::sort_after(const_iterator before_first, const_iterator last)
		{
			fl_type_only::k_sort_after(before_first, last);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::sort(BinaryPredict cmp)
		{
			fl_type_only::k_sort(cmp);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::sort()
		{
			fl_type_only::k_sort();
		}

		template <typename T, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::size_type
		forward_list<T, Allocator>::remove_after_if(const_iterator before_first, const_iterator last, UnaryPredicate predicate)
		{
			return fl_type_only::k_remove_after_if_using_allocator(this->alloc(), before_first, last, predicate);
		}

		template <typename T, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::size_type
		forward_list<T, Allocator>::remove_if(UnaryPredicate predicate)
		{
			return this->fl_type_only::k_remove_if_using_allocator(this->alloc(), predicate);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::size_type
		forward_list<T, Allocator>::remove_after(const_iterator before_first, const_iterator last, const_reference val)
		{
			return fl_type_only::k_remove_after_using_allocator(this->alloc(), before_first, last, val);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::size_type
		forward_list<T, Allocator>::remove(const_reference val)
		{
			return this->fl_type_only::k_remove_using_allocator(this->alloc(), val);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::size_type
		forward_list<T, Allocator>::unique(const_iterator first, const_iterator last, BinaryPredict equal_to)
		{
			return fl_type_only::k_unique_using_allocator(this->alloc(), first, last, equal_to);
		}

		template <typename T, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::size_type
		forward_list<T, Allocator>::unique(BinaryPredict equal_to)
		{
			return this->fl_type_only::k_unique_using_allocator(this->alloc(), equal_to);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::size_type
		forward_list<T, Allocator>::unique(const_iterator first, const_iterator last)
		{
			return fl_type_only::k_unique_using_allocator(this->alloc(), first, last);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		forward_list<T, Allocator>::size_type
		forward_list<T, Allocator>::unique()
		{
			return this->fl_type_only::k_unique_using_allocator(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::splice_after(
			const_iterator before_pos, forward_list & other
		) KERBAL_NOEXCEPT
		{
			fl_type_unrelated::k_splice_after(before_pos, other);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::splice_after(
			const_iterator before_pos, forward_list & /*other*/,
			const_iterator opos
		) KERBAL_NOEXCEPT
		{
			fl_type_unrelated::k_splice_after(before_pos, opos);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<T, Allocator>::splice_after(
			const_iterator before_pos, forward_list & /*other*/,
			const_iterator before_first, const_iterator last
		) KERBAL_NOEXCEPT
		{
			fl_type_unrelated::k_splice_after(before_pos, before_first, last);
		}


	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_IMPL_HPP
