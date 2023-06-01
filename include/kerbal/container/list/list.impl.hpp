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

#include <kerbal/compatibility/move.hpp>
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

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list()
				KERBAL_CONDITIONAL_NOEXCEPT(
						list_allocator_overload::is_nothrow_default_constructible::value &&
						list_allocator_unrelated::is_nothrow_init_to_self_constructible::value
				) :
				list_allocator_overload(),
				list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(const Allocator& alloc)
				KERBAL_CONDITIONAL_NOEXCEPT(
						list_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						list_allocator_unrelated::is_nothrow_init_to_self_constructible::value
				) :
				list_allocator_overload(alloc),
				list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(const list& src) :
				list_allocator_overload(),
				list_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(const list& src, const Allocator& alloc) :
				list_allocator_overload(alloc),
				list_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n) :
				list_allocator_overload(),
				list_allocator_unrelated(this->alloc(), n)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const Allocator& alloc) :
				list_allocator_overload(alloc),
				list_allocator_unrelated(this->alloc(), n)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const_reference val) :
				list_allocator_overload(),
				list_allocator_unrelated(this->alloc(), n, val)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const_reference val, const Allocator& alloc) :
				list_allocator_overload(alloc),
				list_allocator_unrelated(this->alloc(), n, val)
		{
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type) :
				list_allocator_overload(),
				list_allocator_unrelated(this->alloc(), first, last)
		{
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(InputIterator first, InputIterator last, const Allocator& alloc,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type) :
				list_allocator_overload(alloc),
				list_allocator_unrelated(this->alloc(), first, last)
		{
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(list&& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						list_allocator_overload::is_nothrow_constructible_from_allocator_rvalue_reference::value &&
						list_allocator_unrelated::is_nothrow_move_constructible::value
				) :
				list_allocator_overload(kerbal::compatibility::move(src.alloc())),
				list_allocator_unrelated(static_cast<list_allocator_unrelated &&>(src))
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(list&& src, const Allocator& alloc)
				KERBAL_CONDITIONAL_NOEXCEPT(
						list_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						list_allocator_unrelated::template is_nothrow_move_constructible_using_allocator<node_allocator_type>::value
				) :
				list_allocator_overload(alloc),
				list_allocator_unrelated(this->alloc(),
										 kerbal::compatibility::move(src.alloc()),
										 static_cast<list_allocator_unrelated &&>(src))
		{
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(std::initializer_list<value_type> src) :
				list(src.begin(), src.end())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(std::initializer_list<value_type> src, const Allocator& alloc) :
				list(src.begin(), src.end(), alloc)
		{
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		list<Tp, Allocator>::list(const kerbal::assign::assign_list<Up> & src) :
				list_allocator_overload(),
				list_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename Tp, typename Allocator>
		template <typename Up>
		list<Tp, Allocator>::list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc) :
				list_allocator_overload(alloc),
				list_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::~list()
		{
			this->list_allocator_unrelated::destroy_using_allocator(this->alloc());
		}


	//===================
	// assign

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>&
		list<Tp, Allocator>::operator=(const list& src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>&
		list<Tp, Allocator>::operator=(list&& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(kerbal::compatibility::move(src)))
				)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>&
		list<Tp, Allocator>::operator=(std::initializer_list<value_type> src)
		{
			this->assign(src);
			return *this;
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		list<Tp, Allocator>&
		list<Tp, Allocator>::operator=(const kerbal::assign::assign_list<Up> & src)
		{
			this->assign(src);
			return *this;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::assign(const list& src)
		{
			list_allocator_unrelated::assign_using_allocator(
					this->alloc(),
					src.alloc(),
					static_cast<const list_allocator_unrelated &>(src));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::assign(size_type count, const_reference val)
		{
			list_allocator_unrelated::assign_using_allocator(this->alloc(), count, val);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		list<Tp, Allocator>::assign(InputIterator first, InputIterator last)
		{
			list_allocator_unrelated::assign_using_allocator(this->alloc(), first, last);
		}


#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::assign(list&& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						list_allocator_unrelated::template is_nothrow_move_assign_using_allocator<node_allocator_type>::value
				)
		{
			this->list_allocator_unrelated::assign_using_allocator(
					this->alloc(),
					kerbal::compatibility::move(src.alloc()),
					static_cast<list_allocator_unrelated &&>(src));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::assign(std::initializer_list<value_type> src)
		{
			this->assign(src.begin(), src.end());
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		void list<Tp, Allocator>::assign(const kerbal::assign::assign_list<Up> & src)
		{
			this->assign(src.cbegin(), src.cend());
		}

#	endif


	//===================
	// insert

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::push_front(const_reference val)
		{
			this->list_allocator_unrelated::push_front_using_allocator(this->alloc(), val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::push_front(rvalue_reference val)
		{
			this->list_allocator_unrelated::push_front_using_allocator(this->alloc(), kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_front(Args&& ... args)
		{
			return this->list_allocator_unrelated::emplace_front_using_allocator(this->alloc(), kerbal::utility::forward<Args>(args)...);
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
		template <typename Tp, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename list<Tp, Allocator>::reference \
		list<Tp, Allocator>::emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->list_allocator_unrelated::emplace_front_using_allocator(this->alloc() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
		}

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

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::push_back(const_reference val)
		{
			this->list_allocator_unrelated::emplace_back_using_allocator(this->alloc(), val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::push_back(rvalue_reference val)
		{
			this->list_allocator_unrelated::emplace_back_using_allocator(this->alloc(), kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_back(Args&& ... args)
		{
			return this->list_allocator_unrelated::emplace_back_using_allocator(this->alloc(), kerbal::utility::forward<Args>(args)...);
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
		template <typename Tp, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename list<Tp, Allocator>::reference \
		list<Tp, Allocator>::emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->list_allocator_unrelated::emplace_back_using_allocator(this->alloc() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
		}

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

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, const_reference val)
		{
			return list_allocator_unrelated::insert_using_allocator(this->alloc(), pos, val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, size_type n, const_reference val)
		{
			return list_allocator_unrelated::insert_using_allocator(this->alloc(), pos, n, val);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				typename list<Tp, Allocator>::iterator
		>::type
		list<Tp, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			return list_allocator_unrelated::insert_using_allocator(this->alloc(), pos, first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return list_allocator_unrelated::insert_using_allocator(this->alloc(), pos, kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> src)
		{
			return this->insert(pos, src.begin(), src.end());
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, const kerbal::assign::assign_list<Up> & src)
		{
			return this->insert(pos, src.begin(), src.end());
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, Args&& ... args)
		{
			return list_allocator_unrelated::emplace_using_allocator(this->alloc(), pos, kerbal::utility::forward<Args>(args)...);
		}

#	else

#	define EMPTY
#	define LEFT_JOIN_COMMA(exp) , exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename Tp, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename list<Tp, Allocator>::iterator \
		list<Tp, Allocator>::emplace(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			return list_allocator_unrelated::emplace_using_allocator(this->alloc(), pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
		}

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
	// erase

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::pop_front()
		{
			this->list_allocator_unrelated::pop_front_using_allocator(this->alloc());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::pop_back()
		{
			this->list_allocator_unrelated::pop_back_using_allocator(this->alloc());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::erase(const_iterator pos)
		{
			return list_allocator_unrelated::erase_using_allocator(this->alloc(), pos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			return list_allocator_unrelated::erase_using_allocator(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::clear()
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list_allocator_unrelated>()->clear_using_allocator(
								kerbal::utility::declthis<list>()->alloc()
						))
				)
		{
			this->list_allocator_unrelated::clear_using_allocator(this->alloc());
		}


	//===================
	// operation

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::resize(size_type count)
		{
			list_allocator_unrelated::resize_using_allocator(this->alloc(), count);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::resize(size_type count, const_reference value)
		{
			list_allocator_unrelated::resize_using_allocator(this->alloc(), count, value);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::swap(list& with)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(list_allocator_overload::k_swap_allocator_if_propagate(
								kerbal::utility::declval<list_allocator_overload&>(), kerbal::utility::declval<list_allocator_overload&>()
						)) &&
						noexcept(list_type_unrelated::k_swap_type_unrelated(
								kerbal::utility::declval<list_type_unrelated&>(), kerbal::utility::declval<list_type_unrelated&>()
						))
				)
		{
			list_allocator_overload::k_swap_allocator_if_propagate(
					static_cast<list_allocator_overload&>(*this),
					static_cast<list_allocator_overload&>(with));
			list_type_unrelated::k_swap_type_unrelated(
					static_cast<list_type_unrelated&>(*this),
					static_cast<list_type_unrelated&>(with));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::iter_swap(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
		{
			list_allocator_unrelated::k_iter_swap(a, b);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::reverse(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
		{
			list_allocator_unrelated::k_reverse(a, b);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::merge(list & other, BinaryPredict cmp)
		{
			list_allocator_unrelated::k_merge(static_cast<list_allocator_unrelated&>(other), cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::merge(list & other)
		{
			list_allocator_unrelated::k_merge(static_cast<list_allocator_unrelated&>(other));
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::sort(const_iterator first, const_iterator last, BinaryPredict cmp)
		{
			list_allocator_unrelated::k_sort(first, last, cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::sort(const_iterator first, const_iterator last)
		{
			list_allocator_unrelated::k_sort(first, last);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove(const_reference val)
		{
			return list_allocator_unrelated::remove_using_allocator(this->alloc(), val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove(const_iterator first, const_iterator last, const_reference val)
		{
			return list_allocator_unrelated::remove_using_allocator(this->alloc(), first, last, val);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove_if(UnaryPredicate predicate)
		{
			return list_allocator_unrelated::remove_if_using_allocator(this->alloc(), predicate);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove_if(const_iterator first, const_iterator last, UnaryPredicate predicate)
		{
			return list_allocator_unrelated::remove_if_using_allocator(this->alloc(), first, last, predicate);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::unique()
		{
			return list_allocator_unrelated::unique_using_allocator(this->alloc());
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredicate>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::unique(BinaryPredicate pred)
		{
			return list_allocator_unrelated::unique_using_allocator(this->alloc(), pred);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::unique(const_iterator first, const_iterator last)
		{
			return list_allocator_unrelated::unique_using_allocator(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredicate>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::unique(const_iterator first, const_iterator last, BinaryPredicate pred)
		{
			return list_allocator_unrelated::unique_using_allocator(this->alloc(), first, last, pred);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list & other) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, other);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list & /*other*/, const_iterator opos) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, opos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list & /*other*/, const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list && other) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, kerbal::compatibility::move(other));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list && /*other*/, const_iterator opos) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, opos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list && /*other*/, const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			list_type_unrelated::k_splice(pos, first, last);
		}

#	endif

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::set_difference(list & l1, const list & l2, list & lto, BinaryPredict cmp)
		{
			list_allocator_unrelated::k_set_difference(static_cast<list_allocator_unrelated &>(l1), static_cast<const list_allocator_unrelated &>(l2),
														static_cast<list_allocator_unrelated &>(lto), cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::set_difference(list & l1, const list & l2, list & lto)
		{
			list_allocator_unrelated::k_set_difference(static_cast<list_allocator_unrelated &>(l1), static_cast<const list_allocator_unrelated &>(l2),
														static_cast<list_allocator_unrelated &>(lto));
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::set_intersection(list & l1, list & l2, list & lto, BinaryPredict cmp)
		{
			list_allocator_unrelated::k_set_intersection(static_cast<list_allocator_unrelated &>(l1), static_cast<list_allocator_unrelated &>(l2),
														  static_cast<list_allocator_unrelated &>(lto), cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::set_intersection(list & l1, list & l2, list & lto)
		{
			list_allocator_unrelated::k_set_intersection(static_cast<list_allocator_unrelated &>(l1), static_cast<list_allocator_unrelated &>(l2),
														  static_cast<list_allocator_unrelated &>(lto));
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::set_symmetric_difference(list & l1, list & l2, list & lto, BinaryPredict cmp)
		{
			list_allocator_unrelated::k_set_symmetric_difference(static_cast<list_allocator_unrelated &>(l1), static_cast<list_allocator_unrelated &>(l2),
																  static_cast<list_allocator_unrelated &>(lto), cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::set_symmetric_difference(list & l1, list & l2, list & lto)
		{
			list_allocator_unrelated::k_set_symmetric_difference(static_cast<list_allocator_unrelated &>(l1), static_cast<list_allocator_unrelated &>(l2),
																  static_cast<list_allocator_unrelated &>(lto));
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::set_union(list & l1, list & l2, list & lto, BinaryPredict cmp)
		{
			list_allocator_unrelated::k_set_union(static_cast<list_allocator_unrelated &>(l1), static_cast<list_allocator_unrelated &>(l2),
												   static_cast<list_allocator_unrelated &>(lto), cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::set_union(list & l1, list & l2, list & lto)
		{
			list_allocator_unrelated::k_set_union(static_cast<list_allocator_unrelated &>(l1), static_cast<list_allocator_unrelated &>(l2),
												   static_cast<list_allocator_unrelated &>(lto));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>& list<Tp, Allocator>::operator+=(const list & with)
		{
			this->insert(this->cend(), with.cbegin(), with.cend());
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>& list<Tp, Allocator>::operator+=(list && with)
		{
			this->splice(this->cend(), kerbal::compatibility::move(with));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>& list<Tp, Allocator>::operator+=(std::initializer_list<value_type> with)
		{
			this->insert(this->cend(), with.begin(), with.end());
			return *this;
		}

#	else

		template <typename Tp, typename Allocator>
		list<Tp, Allocator>& list<Tp, Allocator>::operator+=(const kerbal::assign::assign_list<value_type> & with)
		{
			this->insert(this->cend(), with.cbegin(), with.cend());
			return *this;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(const list<Tp, Allocator> & lhs, const list<Tp, Allocator> & rhs)
		{
			list<Tp, Allocator> r(lhs);
			r.insert(r.cend(), rhs.cbegin(), rhs.cend());
			return r;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(const list<Tp, Allocator> & lhs, list<Tp, Allocator> && rhs)
		{
			list<Tp, Allocator> r(lhs);
			r += kerbal::compatibility::move(rhs);
			return r;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator> && lhs, const list<Tp, Allocator> & rhs)
		{
			list<Tp, Allocator> r(kerbal::compatibility::move(lhs));
			r += rhs;
			return r;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator> && lhs, list<Tp, Allocator> && rhs)
		{
			list<Tp, Allocator> r(kerbal::compatibility::move(lhs));
			r += kerbal::compatibility::move(rhs);
			return r;
		}

#	endif

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_LIST_LIST_IMPL_HPP
