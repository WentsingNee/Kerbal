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

#include <kerbal/container/detail/forward_list_base/forward_list_base.impl.hpp>
#include <kerbal/container/forward_list/forward_list.decl.hpp>


namespace kerbal
{

	namespace container
	{

	//===================
	// construct/copy/destroy

#	if __cplusplus < 201103L

		template <typename Tp, typename Allocator>
		forward_list<Tp, Allocator>::forward_list() :
				fl_allocator_overload(),
				fl_allocator_unrelated()
		{
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(const Allocator& alloc)
				KERBAL_CONDITIONAL_NOEXCEPT(
						fl_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						fl_allocator_unrelated::is_nothrow_default_constructible::value
				) :
				fl_allocator_overload(alloc),
				fl_allocator_unrelated()
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(const forward_list & src) :
				fl_allocator_overload(),
				fl_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(const forward_list & src, const Allocator& alloc) :
				fl_allocator_overload(alloc),
				fl_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(size_type n) :
				fl_allocator_overload(),
				fl_allocator_unrelated(this->alloc(), n)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(size_type n, const Allocator& alloc) :
				fl_allocator_overload(alloc),
				fl_allocator_unrelated(this->alloc(), n)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(size_type n, const_reference val) :
				fl_allocator_overload(),
				fl_allocator_unrelated(this->alloc(), n, val)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(size_type n, const_reference val, const Allocator& alloc) :
				fl_allocator_overload(alloc),
				fl_allocator_unrelated(this->alloc(), n, val)
		{
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type) :
				fl_allocator_overload(),
				fl_allocator_unrelated(this->alloc(), first, last)
		{
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(InputIterator first, InputIterator last, const Allocator& alloc,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type) :
				fl_allocator_overload(alloc),
				fl_allocator_unrelated(this->alloc(), first, last)
		{
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(forward_list && src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						fl_allocator_overload::is_nothrow_constructible_from_allocator_rvalue_reference::value &&
						fl_allocator_unrelated::is_nothrow_move_constructible::value
				) :
				fl_allocator_overload(kerbal::compatibility::move(src.alloc())),
				fl_allocator_unrelated(static_cast<fl_allocator_unrelated &&>(src))
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(forward_list && src, const Allocator& alloc)
				KERBAL_CONDITIONAL_NOEXCEPT(
						fl_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						fl_allocator_unrelated::template is_nothrow_move_constructible_using_allocator<node_allocator_type>::value
				) :
				fl_allocator_overload(alloc),
				fl_allocator_unrelated(this->alloc(),
									   kerbal::compatibility::move(src.alloc()),
									   static_cast<fl_allocator_unrelated &&>(src))
		{
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(std::initializer_list<value_type> src) :
				forward_list(src.begin(), src.end())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(std::initializer_list<value_type> src, const Allocator& alloc) :
				forward_list(src.begin(), src.end(), alloc)
		{
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		forward_list<Tp, Allocator>::forward_list(const kerbal::assign::assign_list<Up> & src) :
				fl_allocator_overload(),
				fl_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename Tp, typename Allocator>
		template <typename Up>
		forward_list<Tp, Allocator>::forward_list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc) :
				fl_allocator_overload(alloc),
				fl_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::~forward_list()
		{
			this->fl_allocator_unrelated::destroy_using_allocator(this->alloc());
		}


	//===================
	// assign

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>&
		forward_list<Tp, Allocator>::operator=(const forward_list& src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>&
		forward_list<Tp, Allocator>::operator=(forward_list&& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<forward_list>()->assign(kerbal::compatibility::move(src)))
				)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>&
		forward_list<Tp, Allocator>::operator=(std::initializer_list<value_type> src)
		{
			this->assign(src);
			return *this;
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		forward_list<Tp, Allocator>&
		forward_list<Tp, Allocator>::operator=(const kerbal::assign::assign_list<Up> & src)
		{
			this->assign(src);
			return *this;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::assign(const forward_list& src)
		{
			fl_allocator_unrelated::assign_using_allocator(
					this->alloc(),
					src.alloc(),
					static_cast<const fl_allocator_unrelated &>(src));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::assign(size_type count, const_reference val)
		{
			fl_allocator_unrelated::assign_using_allocator(this->alloc(), count, val);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		forward_list<Tp, Allocator>::assign(InputIterator first, InputIterator last)
		{
			fl_allocator_unrelated::assign_using_allocator(this->alloc(), first, last);
		}


#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::assign(forward_list&& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						fl_allocator_unrelated::template is_nothrow_move_assign_using_allocator<node_allocator_type>::value
				)
		{
			this->fl_allocator_unrelated::assign_using_allocator(
					this->alloc(),
					kerbal::compatibility::move(src.alloc()),
					static_cast<fl_allocator_unrelated &&>(src));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::assign(std::initializer_list<value_type> src)
		{
			this->assign(src.begin(), src.end());
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		void forward_list<Tp, Allocator>::assign(const kerbal::assign::assign_list<Up> & src)
		{
			this->assign(src.cbegin(), src.cend());
		}

#	endif


	//===================
	// insert

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::push_front(const_reference val)
		{
			this->fl_allocator_unrelated::push_front_using_allocator(this->alloc(), val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::push_front(rvalue_reference val)
		{
			this->fl_allocator_unrelated::push_front_using_allocator(this->alloc(), kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::reference
		forward_list<Tp, Allocator>::emplace_front(Args&& ... args)
		{
			return this->fl_allocator_unrelated::emplace_front_using_allocator(this->alloc(), kerbal::utility::forward<Args>(args)...);
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
		typename forward_list<Tp, Allocator>::reference \
		forward_list<Tp, Allocator>::emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->fl_allocator_unrelated::emplace_front_using_allocator(this->alloc() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
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
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::insert_after(const_iterator pos, const_reference val)
		{
			return fl_allocator_unrelated::insert_after_using_allocator(this->alloc(), pos, val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::insert_after(const_iterator pos, size_type n, const_reference val)
		{
			return fl_allocator_unrelated::insert_after_using_allocator(this->alloc(), pos, n, val);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				typename forward_list<Tp, Allocator>::iterator
		>::type
		forward_list<Tp, Allocator>::insert_after(const_iterator pos, InputIterator first, InputIterator last)
		{
			return fl_allocator_unrelated::insert_after_using_allocator(this->alloc(), pos, first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::insert_after(const_iterator pos, rvalue_reference val)
		{
			return fl_allocator_unrelated::insert_after_using_allocator(this->alloc(), pos, kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::insert_after(const_iterator pos, std::initializer_list<value_type> src)
		{
			return this->insert_after(pos, src.begin(), src.end());
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::insert_after(const_iterator pos, const kerbal::assign::assign_list<Up> & src)
		{
			return this->insert_after(pos, src.cbegin(), src.cend());
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::emplace_after(const_iterator pos, Args&& ... args)
		{
			return fl_allocator_unrelated::emplace_after_using_allocator(this->alloc(), pos, kerbal::utility::forward<Args>(args)...);
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
		typename forward_list<Tp, Allocator>::iterator \
		forward_list<Tp, Allocator>::emplace_after(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			return fl_allocator_unrelated::emplace_after_using_allocator(this->alloc(), pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
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
		void forward_list<Tp, Allocator>::pop_front()
		{
			this->fl_allocator_unrelated::pop_front_using_allocator(this->alloc());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::erase_after(const_iterator pos)
		{
			return fl_allocator_unrelated::erase_after_using_allocator(this->alloc(), pos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::erase_after(const_iterator first, const_iterator last)
		{
			return fl_allocator_unrelated::erase_after_using_allocator(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::clear()
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<fl_allocator_unrelated>()->clear_using_allocator(
								kerbal::utility::declthis<forward_list>()->alloc()
						))
				)
		{
			this->fl_allocator_unrelated::clear_using_allocator(this->alloc());
		}


	//===================
	// operation

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::resize(size_type count)
		{
			this->fl_allocator_unrelated::resize_using_allocator(this->alloc(), count);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::resize(size_type count, const_reference value)
		{
			this->fl_allocator_unrelated::resize_using_allocator(this->alloc(), count, value);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::swap(forward_list & with)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(fl_allocator_overload::k_swap_allocator_if_propagate(
								kerbal::utility::declval<fl_allocator_overload&>(), kerbal::utility::declval<fl_allocator_overload&>()
						)) &&
						noexcept(fl_type_unrelated::_K_swap_type_unrelated(
								kerbal::utility::declval<fl_type_unrelated&>(), kerbal::utility::declval<fl_type_unrelated&>()
						))
				)
		{
			fl_allocator_overload::k_swap_allocator_if_propagate(
					static_cast<fl_allocator_overload&>(*this),
					static_cast<fl_allocator_overload&>(with));
			fl_type_unrelated::_K_swap_type_unrelated(
					static_cast<fl_type_unrelated&>(*this),
					static_cast<fl_type_unrelated&>(with));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::iter_swap_after(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
		{
			fl_allocator_unrelated::_K_iter_swap_after(a, b);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::reverse_after(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			fl_allocator_unrelated::_K_reverse_after(first, last);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::merge(forward_list & other, BinaryPredict cmp)
		{
			this->fl_allocator_unrelated::_K_merge(static_cast<fl_allocator_unrelated&>(other), cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::merge(forward_list & other)
		{
			this->fl_allocator_unrelated::_K_merge(static_cast<fl_allocator_unrelated&>(other));
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::sort_after(const_iterator first, const_iterator last, BinaryPredict cmp)
		{
			fl_allocator_unrelated::_K_sort_after(first, last, cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::sort_after(const_iterator first, const_iterator last)
		{
			fl_allocator_unrelated::_K_sort_after(first, last);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::sort(BinaryPredict cmp)
		{
			fl_allocator_unrelated::_K_sort(cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::sort()
		{
			fl_allocator_unrelated::_K_sort();
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::remove_after_if(const_iterator first, const_iterator last, UnaryPredicate predicate)
		{
			return fl_allocator_unrelated::remove_after_if_using_allocator(this->alloc(), first, last, predicate);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::remove_if(UnaryPredicate predicate)
		{
			return this->fl_allocator_unrelated::remove_if_using_allocator(this->alloc(), predicate);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::remove_after(const_iterator first, const_iterator last, const_reference val)
		{
			return fl_allocator_unrelated::remove_after_using_allocator(this->alloc(), first, last, val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::remove(const_reference val)
		{
			return this->fl_allocator_unrelated::remove_using_allocator(this->alloc(), val);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::unique(const_iterator first, const_iterator last, BinaryPredict equal_to)
		{
			return fl_allocator_unrelated::unique_using_allocator(this->alloc(), first, last, equal_to);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::unique(const_iterator first, const_iterator last)
		{
			return fl_allocator_unrelated::unique_using_allocator(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::unique(BinaryPredict equal_to)
		{
			return this->fl_allocator_unrelated::unique_using_allocator(this->alloc(), equal_to);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::unique()
		{
			return this->fl_allocator_unrelated::unique_using_allocator(this->alloc());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::splice_after(const_iterator pos, forward_list & other) KERBAL_NOEXCEPT
		{
			fl_type_unrelated::_K_splice_after(pos, other);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::splice_after(const_iterator pos, forward_list &, const_iterator opos) KERBAL_NOEXCEPT
		{
			fl_type_unrelated::_K_splice_after(pos, opos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::splice_after(const_iterator pos, forward_list &, const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			fl_type_unrelated::_K_splice_after(pos, first, last);
		}


	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_IMPL_HPP
