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

#ifndef KERBAL_CONTAINER_IMPL_SINGLE_LIST_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_SINGLE_LIST_IMPL_HPP

#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/operators/generic_assign.hpp>
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

#include <kerbal/container/detail/single_list_base.hpp>


namespace kerbal
{

	namespace container
	{

	//===================
	// construct/copy/destroy

#	if __cplusplus < 201103L

		template <typename Tp, typename Allocator>
		single_list<Tp, Allocator>::single_list() :
				sl_allocator_overload(),
				sl_allocator_unrelated()
		{
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(const Allocator& alloc)
				KERBAL_CONDITIONAL_NOEXCEPT(
						sl_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						sl_allocator_unrelated::is_nothrow_default_constrctible::value
				) :
				sl_allocator_overload(alloc),
				sl_allocator_unrelated()
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(const single_list & src) :
				sl_allocator_overload(),
				sl_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(const single_list & src, const Allocator& alloc) :
				sl_allocator_overload(alloc),
				sl_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n) :
				sl_allocator_overload(),
				sl_allocator_unrelated(this->alloc(), n)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const Allocator& alloc) :
				sl_allocator_overload(alloc),
				sl_allocator_unrelated(this->alloc(), n)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const_reference val) :
				sl_allocator_overload(),
				sl_allocator_unrelated(this->alloc(), n, val)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const_reference val, const Allocator& alloc) :
				sl_allocator_overload(alloc),
				sl_allocator_unrelated(this->alloc(), n, val)
		{
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type) :
				sl_allocator_overload(),
				sl_allocator_unrelated(this->alloc(), first, last)
		{
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(InputIterator first, InputIterator last, const Allocator& alloc,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type) :
				sl_allocator_overload(alloc),
				sl_allocator_unrelated(this->alloc(), first, last)
		{
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(single_list && src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						sl_allocator_overload::is_nothrow_constructible_from_allocator_rvalue_reference::value &&
						sl_allocator_unrelated::is_nothrow_move_constrctible::value
				) :
				sl_allocator_overload(kerbal::compatibility::move(src.alloc())),
				sl_allocator_unrelated(static_cast<sl_allocator_unrelated &&>(src))
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(single_list && src, const Allocator& alloc)
				KERBAL_CONDITIONAL_NOEXCEPT(
						sl_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						sl_allocator_unrelated::template is_nothrow_move_constructible_using_allocator<node_allocator_type>::value
				) :
				sl_allocator_overload(alloc),
				sl_allocator_unrelated(this->alloc(),
									   kerbal::compatibility::move(src.alloc()),
									   static_cast<sl_allocator_unrelated &&>(src))
		{
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(std::initializer_list<value_type> src) :
				single_list(src.begin(), src.end())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(std::initializer_list<value_type> src, const Allocator& alloc) :
				single_list(src.begin(), src.end(), alloc)
		{
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		single_list<Tp, Allocator>::single_list(const kerbal::assign::assign_list<Up> & src) :
				sl_allocator_overload(),
				sl_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

		template <typename Tp, typename Allocator>
		template <typename Up>
		single_list<Tp, Allocator>::single_list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc) :
				sl_allocator_overload(alloc),
				sl_allocator_unrelated(this->alloc(), src.cbegin(), src.cend())
		{
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::~single_list()
		{
			this->sl_allocator_unrelated::destroy_using_allocator(this->alloc());
		}


	//===================
	// assign

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>&
		single_list<Tp, Allocator>::operator=(const single_list& src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>&
		single_list<Tp, Allocator>::operator=(single_list&& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->assign(kerbal::compatibility::move(src)))
				)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>&
		single_list<Tp, Allocator>::operator=(std::initializer_list<value_type> src)
		{
			this->assign(src);
			return *this;
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		single_list<Tp, Allocator>&
		single_list<Tp, Allocator>::operator=(const kerbal::assign::assign_list<Up> & src)
		{
			this->assign(src);
			return *this;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::assign(const single_list& src)
		{
			this->sl_allocator_unrelated::assign_using_allocator(
					this->alloc(),
					src.alloc(),
					static_cast<const sl_allocator_unrelated &>(src));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::assign(size_type count, const_reference val)
		{
			this->sl_allocator_unrelated::assign_using_allocator(this->alloc(), count, val);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		single_list<Tp, Allocator>::assign(InputIterator first, InputIterator last)
		{
			this->sl_allocator_unrelated::assign_using_allocator(this->alloc(), first, last);
		}


#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::assign(single_list&& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						sl_allocator_unrelated::template is_nothrow_move_assign_using_allocator<node_allocator_type>::value
				)
		{
			this->sl_allocator_unrelated::assign_using_allocator(
					this->alloc(),
					kerbal::compatibility::move(src.alloc()),
					static_cast<sl_allocator_unrelated &&>(src));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::assign(std::initializer_list<value_type> src)
		{
			this->assign(src.begin(), src.end());
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		void single_list<Tp, Allocator>::assign(const kerbal::assign::assign_list<Up> & src)
		{
			this->assign(src.cbegin(), src.cend());
		}

#	endif


	//===================
	// insert

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::push_front(const_reference val)
		{
			this->sl_allocator_unrelated::push_front_using_allocator(this->alloc(), val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::push_front(rvalue_reference val)
		{
			this->sl_allocator_unrelated::push_front_using_allocator(this->alloc(), kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(Args&& ... args)
		{
			return this->sl_allocator_unrelated::emplace_front_using_allocator(this->alloc(), kerbal::utility::forward<Args>(args)...);
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
		typename single_list<Tp, Allocator>::reference \
		single_list<Tp, Allocator>::emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->sl_allocator_unrelated::emplace_front_using_allocator(this->alloc() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
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
		void single_list<Tp, Allocator>::push_back(const_reference val)
		{
			this->sl_allocator_unrelated::push_back_using_allocator(this->alloc(), val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::push_back(rvalue_reference val)
		{
			this->sl_allocator_unrelated::push_back_using_allocator(this->alloc(), kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(Args&& ... args)
		{
			return this->sl_allocator_unrelated::emplace_back_using_allocator(this->alloc(), kerbal::utility::forward<Args>(args)...);
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
		typename single_list<Tp, Allocator>::reference \
		single_list<Tp, Allocator>::emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->sl_allocator_unrelated::emplace_back_using_allocator(this->alloc() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
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
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::insert(const_iterator pos, const_reference val)
		{
			return this->sl_allocator_unrelated::insert_using_allocator(this->alloc(), pos, val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::insert(const_iterator pos, size_type n, const_reference val)
		{
			return this->sl_allocator_unrelated::insert_using_allocator(this->alloc(), pos, n, val);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				typename single_list<Tp, Allocator>::iterator
		>::type
		single_list<Tp, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			return this->sl_allocator_unrelated::insert_using_allocator(this->alloc(), pos, first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return this->sl_allocator_unrelated::insert_using_allocator(this->alloc(), pos, kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> src)
		{
			return this->insert(pos, src.begin(), src.end());
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::insert(const_iterator pos, const kerbal::assign::assign_list<Up> & src)
		{
			return this->insert(pos, src.begin(), src.end());
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::emplace(const_iterator pos, Args&& ... args)
		{
			return this->sl_allocator_unrelated::emplace_using_allocator(this->alloc(), pos, kerbal::utility::forward<Args>(args)...);
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
		typename single_list<Tp, Allocator>::iterator \
		single_list<Tp, Allocator>::emplace(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->sl_allocator_unrelated::emplace_using_allocator(this->alloc(), pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
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
		void single_list<Tp, Allocator>::pop_front()
		{
			this->sl_allocator_unrelated::pop_front_using_allocator(this->alloc());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::erase(const_iterator pos)
		{
			return this->sl_allocator_unrelated::erase_using_allocator(this->alloc(), pos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			return this->sl_allocator_unrelated::erase_using_allocator(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::clear()
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<sl_allocator_unrelated>()->clear_using_allocator(
								kerbal::utility::declthis<single_list>()->alloc()
						))
				)
		{
			this->sl_allocator_unrelated::clear_using_allocator(this->alloc());
		}


	//===================
	// operation

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::resize(size_type count)
		{
			this->sl_allocator_unrelated::resize_using_allocator(this->alloc(), count);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::resize(size_type count, const_reference value)
		{
			this->sl_allocator_unrelated::resize_using_allocator(this->alloc(), count, value);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::swap(single_list & with)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(sl_allocator_overload::k_swap_allocator_if_propagate(
								kerbal::utility::declval<sl_allocator_overload&>(), kerbal::utility::declval<sl_allocator_overload&>()
						)) &&
						noexcept(sl_type_unrelated::_K_swap_type_unrelated(
								kerbal::utility::declval<sl_type_unrelated&>(), kerbal::utility::declval<sl_type_unrelated&>()
						))
				)
		{
			sl_allocator_overload::k_swap_allocator_if_propagate(
					static_cast<sl_allocator_overload&>(*this),
					static_cast<sl_allocator_overload&>(with));
			sl_type_unrelated::_K_swap_type_unrelated(
					static_cast<sl_type_unrelated&>(*this),
					static_cast<sl_type_unrelated&>(with));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::remove(const_reference val)
		{
			return sl_allocator_unrelated::remove_using_allocator(this->alloc(), val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::remove(const_iterator first, const_iterator last, const_reference val)
		{
			return sl_allocator_unrelated::remove_using_allocator(this->alloc(), first, last, val);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::remove_if(UnaryPredicate predicate)
		{
			return sl_allocator_unrelated::remove_if_using_allocator(this->alloc(), predicate);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::remove_if(const_iterator first, const_iterator last, UnaryPredicate predicate)
		{
			return sl_allocator_unrelated::remove_if_using_allocator(this->alloc(), first, last, predicate);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::splice(const_iterator pos, single_list & other) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::_K_splice(pos, other);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::splice(const_iterator pos, single_list & other, const_iterator opos) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::_K_splice(pos, other, opos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::splice(const_iterator pos, single_list & other,
												const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::_K_splice(pos, other, first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::splice(const_iterator pos, single_list && other) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::_K_splice(pos, kerbal::compatibility::move(other));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::splice(const_iterator pos, single_list && other, const_iterator opos) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::_K_splice(pos, kerbal::compatibility::move(other), opos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::splice(const_iterator pos, single_list && other,
												const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::_K_splice(pos, kerbal::compatibility::move(other), first, last);
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>& single_list<Tp, Allocator>::operator+=(const single_list & with)
		{
			this->insert(this->cend(), with.cbegin(), with.cend());
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>& single_list<Tp, Allocator>::operator+=(single_list && with)
		{
			this->splice(this->cend(), kerbal::compatibility::move(with));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>& single_list<Tp, Allocator>::operator+=(std::initializer_list<value_type> with)
		{
			this->insert(this->cend(), with.begin(), with.end());
			return *this;
		}

#	else

		template <typename Tp, typename Allocator>
		single_list<Tp, Allocator>& single_list<Tp, Allocator>::operator+=(const kerbal::assign::assign_list<value_type> & with)
		{
			this->insert(this->cend(), with.cbegin(), with.cend());
			return *this;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator> operator+(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			single_list<Tp, Allocator> r(lhs);
			r.insert(r.cend(), rhs.cbegin(), rhs.cend());
			return r;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator> operator+(const single_list<Tp, Allocator> & lhs, single_list<Tp, Allocator> && rhs)
		{
			single_list<Tp, Allocator> r(lhs);
			r += kerbal::compatibility::move(rhs);
			return r;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator> operator+(single_list<Tp, Allocator> && lhs, const single_list<Tp, Allocator> & rhs)
		{
			single_list<Tp, Allocator> r(kerbal::compatibility::move(lhs));
			r += rhs;
			return r;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator> operator+(single_list<Tp, Allocator> && lhs, single_list<Tp, Allocator> && rhs)
		{
			single_list<Tp, Allocator> r(kerbal::compatibility::move(lhs));
			r += kerbal::compatibility::move(rhs);
			return r;
		}

#	endif

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_SINGLE_LIST_IMPL_HPP
