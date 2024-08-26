/**
 * @file       single_list.impl.hpp
 * @brief
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_SINGLE_LIST_SINGLE_LIST_IMPL_HPP
#define KERBAL_CONTAINER_SINGLE_LIST_SINGLE_LIST_IMPL_HPP

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
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

#include <kerbal/container/detail/single_list_base/single_list_base.impl.hpp>
#include <kerbal/container/single_list/single_list.decl.hpp>


namespace kerbal
{

	namespace container
	{

	//===================
	// construct/copy/destroy

#	if __cplusplus < 201103L

		template <typename T, typename Allocator>
		single_list<T, Allocator>::single_list() :
			sl_allocator_overload(),
			sl_type_only()
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(const Allocator & alloc)
			KERBAL_CONDITIONAL_NOEXCEPT(
				sl_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
				sl_type_only::is_nothrow_default_constructible::value
			) :
			sl_allocator_overload(alloc),
			sl_type_only()
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(const single_list & src) :
			sl_allocator_overload(),
			sl_type_only(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(const single_list & src, const Allocator & alloc) :
			sl_allocator_overload(alloc),
			sl_type_only(this->alloc(), src.cbegin(), src.cend())
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(single_list && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				sl_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<Allocator &&>::IS_TRUE::value &&
				sl_type_only::is_nothrow_move_constructible::value
			) :
			sl_allocator_overload(kerbal::compatibility::move(src.alloc())),
			sl_type_only(static_cast<sl_type_only &&>(src))
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(single_list && src, const Allocator & alloc)
			KERBAL_CONDITIONAL_NOEXCEPT(
				sl_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
				sl_type_only::template is_nothrow_move_constructible_using_allocator<node_allocator_type>::value
			) :
			sl_allocator_overload(alloc),
			sl_type_only(
				this->alloc(),
				kerbal::compatibility::move(src.alloc()),
				static_cast<sl_type_only &&>(src)
			)
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(size_type n) :
			sl_allocator_overload(),
			sl_type_only(this->alloc(), n)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(size_type n, const Allocator & alloc) :
			sl_allocator_overload(alloc),
			sl_type_only(this->alloc(), n)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(size_type n, const_reference val) :
			sl_allocator_overload(),
			sl_type_only(this->alloc(), n, val)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(size_type n, const_reference val, const Allocator & alloc) :
			sl_allocator_overload(alloc),
			sl_type_only(this->alloc(), n, val)
		{
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(
			InputIterator first, InputIterator last,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
			>::type
		) :
			sl_allocator_overload(),
			sl_type_only(this->alloc(), first, last)
		{
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(
			InputIterator first, InputIterator last,
			const Allocator & alloc,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
			>::type
		) :
			sl_allocator_overload(alloc),
			sl_type_only(this->alloc(), first, last)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(std::initializer_list<value_type> ilist) :
			single_list(ilist.begin(), ilist.end())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::single_list(std::initializer_list<value_type> ilist, const Allocator & alloc) :
			single_list(ilist.begin(), ilist.end(), alloc)
		{
		}

#	else

		template <typename T, typename Allocator>
		single_list<T, Allocator>::single_list(const kerbal::assign::assign_list<void> & ilist) :
			sl_allocator_overload(),
			sl_type_only()
		{
		}

		template <typename T, typename Allocator>
		template <typename U>
		single_list<T, Allocator>::single_list(const kerbal::assign::assign_list<U> & ilist) :
			sl_allocator_overload(),
			sl_type_only(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

		template <typename T, typename Allocator>
		single_list<T, Allocator>::single_list(const kerbal::assign::assign_list<void> & ilist, const Allocator & alloc) :
			sl_allocator_overload(alloc),
			sl_type_only()
		{
		}

		template <typename T, typename Allocator>
		template <typename U>
		single_list<T, Allocator>::single_list(const kerbal::assign::assign_list<U> & ilist, const Allocator & alloc) :
			sl_allocator_overload(alloc),
			sl_type_only(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>::~single_list()
		{
			this->sl_type_only::k_destroy_using_allocator(this->alloc());
		}


	//===================
	// assign

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator> &
		single_list<T, Allocator>::operator=(const single_list & src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator> &
		single_list<T, Allocator>::operator=(single_list && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(kerbal::utility::declthis<single_list>()->assign(kerbal::compatibility::move(src)))
			)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator> &
		single_list<T, Allocator>::operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	else

		template <typename T, typename Allocator>
		single_list<T, Allocator> &
		single_list<T, Allocator>::operator=(const kerbal::assign::assign_list<void> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

		template <typename T, typename Allocator>
		template <typename U>
		single_list<T, Allocator> &
		single_list<T, Allocator>::operator=(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::assign(const single_list & src)
		{
			this->sl_type_only::k_assign_using_allocator(
				this->alloc(),
				src.alloc(),
				static_cast<const sl_type_only &>(src)
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::assign(single_list && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				sl_type_only::template is_nothrow_move_assign_using_allocator<node_allocator_type>::value
			)
		{
			this->sl_type_only::k_assign_using_allocator(
				this->alloc(),
				kerbal::compatibility::move(src.alloc()),
				static_cast<sl_type_only &&>(src)
			);
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::assign(size_type count, const_reference val)
		{
			this->sl_type_only::k_assign_using_allocator(this->alloc(), count, val);
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		single_list<T, Allocator>::assign(InputIterator first, InputIterator last)
		{
			this->sl_type_only::k_assign_using_allocator(this->alloc(), first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::assign(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
		}

#	else

		template <typename T, typename Allocator>
		void single_list<T, Allocator>::assign(const kerbal::assign::assign_list<void> & ilist)
		{
			this->clear();
		}

		template <typename T, typename Allocator>
		template <typename U>
		void single_list<T, Allocator>::assign(const kerbal::assign::assign_list<U> & ilist)
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
		single_list<T, Allocator>::iterator
		single_list<T, Allocator>::emplace(const_iterator pos, Args && ... args)
		{
			return this->sl_type_only::k_emplace_using_allocator(
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
		single_list<T, Allocator>::iterator \
		single_list<T, Allocator>::emplace( \
			const_iterator pos \
			KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
		) \
		{ \
			return this->sl_type_only::k_emplace_using_allocator( \
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
		single_list<T, Allocator>::iterator
		single_list<T, Allocator>::insert(const_iterator pos, const_reference val)
		{
			return this->sl_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				val
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		single_list<T, Allocator>::iterator
		single_list<T, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return this->sl_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				kerbal::compatibility::move(val)
			);
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		single_list<T, Allocator>::iterator
		single_list<T, Allocator>::insert(const_iterator pos, size_type n, const_reference val)
		{
			return this->sl_type_only::k_insert_using_allocator(
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
			typename single_list<T, Allocator>::iterator
		>::type
		single_list<T, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			return this->sl_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				first, last
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		single_list<T, Allocator>::iterator
		single_list<T, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> ilist)
		{
			return this->insert(pos, ilist.begin(), ilist.end());
		}

#	else

		template <typename T, typename Allocator>
		typename
		single_list<T, Allocator>::iterator
		single_list<T, Allocator>::insert(const_iterator pos, const kerbal::assign::assign_list<void> & ilist)
		{
			return pos.cast_to_mutable();
		}

		template <typename T, typename Allocator>
		template <typename U>
		typename
		single_list<T, Allocator>::iterator
		single_list<T, Allocator>::insert(const_iterator pos, const kerbal::assign::assign_list<U> & ilist)
		{
			return this->insert(pos, ilist.begin(), ilist.end());
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		single_list<T, Allocator>::reference
		single_list<T, Allocator>::emplace_front(Args && ... args)
		{
			return this->sl_type_only::k_emplace_front_using_allocator(
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
		single_list<T, Allocator>::reference \
		single_list<T, Allocator>::emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->sl_type_only::k_emplace_front_using_allocator( \
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
		void single_list<T, Allocator>::push_front(const_reference val)
		{
			this->sl_type_only::k_push_front_using_allocator(
				this->alloc(),
				val
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::push_front(rvalue_reference val)
		{
			this->sl_type_only::k_push_front_using_allocator(
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
		single_list<T, Allocator>::reference
		single_list<T, Allocator>::emplace_back(Args && ... args)
		{
			return this->sl_type_only::k_emplace_back_using_allocator(
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
		single_list<T, Allocator>::reference \
		single_list<T, Allocator>::emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->sl_type_only::k_emplace_back_using_allocator( \
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
		void single_list<T, Allocator>::push_back(const_reference val)
		{
			this->sl_type_only::k_push_back_using_allocator(
				this->alloc(),
				val
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::push_back(rvalue_reference val)
		{
			this->sl_type_only::k_push_back_using_allocator(
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
		single_list<T, Allocator>::iterator
		single_list<T, Allocator>::erase(const_iterator pos)
		{
			return this->sl_type_only::k_erase_using_allocator(this->alloc(), pos);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		single_list<T, Allocator>::iterator
		single_list<T, Allocator>::erase(const_iterator first, const_iterator last)
		{
			return this->sl_type_only::k_erase_using_allocator(this->alloc(), first, last);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::pop_front()
		{
			this->sl_type_only::k_pop_front_using_allocator(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::clear()
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(
					kerbal::utility::declthis<sl_type_only>()->k_clear_using_allocator(
						kerbal::utility::declthis<single_list>()->alloc()
					)
				)
			)
		{
			this->sl_type_only::k_clear_using_allocator(this->alloc());
		}


	//===================
	// operation

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::resize(size_type count)
		{
			this->sl_type_only::k_resize_using_allocator(this->alloc(), count);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::resize(size_type count, const_reference value)
		{
			this->sl_type_only::k_resize_using_allocator(this->alloc(), count, value);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::swap(single_list & with)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(
					sl_allocator_overload::k_swap_allocator_if_propagate(
						kerbal::utility::declval<sl_allocator_overload &>(),
						kerbal::utility::declval<sl_allocator_overload &>()
					)
				) &&
				noexcept(
					sl_type_unrelated::k_swap_type_unrelated(
						kerbal::utility::declval<sl_type_unrelated &>(),
						kerbal::utility::declval<sl_type_unrelated &>()
					)
				)
			)
		{
			sl_allocator_overload::k_swap_allocator_if_propagate(
				static_cast<sl_allocator_overload &>(*this),
				static_cast<sl_allocator_overload &>(with)
			);
			sl_type_unrelated::k_swap_type_unrelated(
				static_cast<sl_type_unrelated &>(*this),
				static_cast<sl_type_unrelated &>(with)
			);
		}

		template <typename T, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename
		single_list<T, Allocator>::size_type
		single_list<T, Allocator>::remove_if(const_iterator first, const_iterator last, UnaryPredicate predicate)
		{
			return sl_type_only::k_remove_if_using_allocator(this->alloc(), first, last, predicate);
		}

		template <typename T, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename
		single_list<T, Allocator>::size_type
		single_list<T, Allocator>::remove_if(UnaryPredicate predicate)
		{
			return sl_type_only::k_remove_if_using_allocator(this->alloc(), predicate);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		single_list<T, Allocator>::size_type
		single_list<T, Allocator>::remove(const_iterator first, const_iterator last, const_reference val)
		{
			return sl_type_only::k_remove_using_allocator(this->alloc(), first, last, val);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		single_list<T, Allocator>::size_type
		single_list<T, Allocator>::remove(const_reference val)
		{
			return sl_type_only::k_remove_using_allocator(this->alloc(), val);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::splice(
			const_iterator pos, single_list & other
		) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::k_splice(
				pos,
				static_cast<sl_type_unrelated &>(other)
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::splice(
			const_iterator pos, single_list & other,
			const_iterator opos
		) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::k_splice(
				pos,
				static_cast<sl_type_unrelated &>(other),
				opos
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::splice(
			const_iterator pos, single_list & other,
			const_iterator first, const_iterator last
		) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::k_splice(
				pos,
				static_cast<sl_type_unrelated &>(other),
				first, last
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::splice(
			const_iterator pos, single_list && other
		) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::k_splice(
				pos,
				static_cast<sl_type_unrelated &&>(other)
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::splice(
			const_iterator pos, single_list && other,
			const_iterator opos
		) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::k_splice(
				pos,
				static_cast<sl_type_unrelated &&>(other),
				opos
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<T, Allocator>::splice(
			const_iterator pos, single_list && other,
			const_iterator first, const_iterator last
		) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::k_splice(
				pos,
				static_cast<sl_type_unrelated &&>(other),
				first, last
			);
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator> &
		single_list<T, Allocator>::
		operator+=(const single_list & with)
		{
			this->insert(this->cend(), with.cbegin(), with.cend());
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator> &
		single_list<T, Allocator>::
		operator+=(single_list && with)
		{
			this->splice(this->cend(), kerbal::compatibility::move(with));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator> &
		single_list<T, Allocator>::
		operator+=(std::initializer_list<value_type> with)
		{
			this->insert(this->cend(), with.begin(), with.end());
			return *this;
		}

#	else

		template <typename T, typename Allocator>
		single_list<T, Allocator> &
		single_list<T, Allocator>::
		operator+=(const kerbal::assign::assign_list<void> & with)
		{
			return *this;
		}

		template <typename T, typename Allocator>
		template <typename U>
		single_list<T, Allocator> &
		single_list<T, Allocator>::
		operator+=(const kerbal::assign::assign_list<U> & with)
		{
			this->insert(this->cend(), with.cbegin(), with.cend());
			return *this;
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>
		operator+(const single_list<T, Allocator> & lhs, const single_list<T, Allocator> & rhs)
		{
			single_list<T, Allocator> r(lhs);
			r.insert(r.cend(), rhs.cbegin(), rhs.cend());
			return r;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>
		operator+(const single_list<T, Allocator> & lhs, single_list<T, Allocator> && rhs)
		{
			single_list<T, Allocator> r(lhs);
			r += kerbal::compatibility::move(rhs);
			return r;
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>
		operator+(single_list<T, Allocator> && lhs, const single_list<T, Allocator> & rhs)
		{
			single_list<T, Allocator> r(kerbal::compatibility::move(lhs));
			r += rhs;
			return r;
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<T, Allocator>
		operator+(single_list<T, Allocator> && lhs, single_list<T, Allocator> && rhs)
		{
			single_list<T, Allocator> r(kerbal::compatibility::move(lhs));
			r += kerbal::compatibility::move(rhs);
			return r;
		}

#	endif

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_SINGLE_LIST_SINGLE_LIST_IMPL_HPP
