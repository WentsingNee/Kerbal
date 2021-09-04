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

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <utility> // std::pair
#if __cplusplus >= 201103L
#	include <initializer_list>
#	include <type_traits>
#endif

#include <kerbal/container/single_list.hpp>

namespace kerbal
{

	namespace container
	{

	//===================
	// construct/copy/destroy

#	if __cplusplus < 201103L

		template <typename Tp, typename Allocator>
		single_list<Tp, Allocator>::single_list()
				: sl_allocator_unrelated(), sl_allocator_overload()
		{
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(const Allocator& alloc)
					KERBAL_CONDITIONAL_NOEXCEPT((
							std::is_nothrow_default_constructible<sl_allocator_unrelated>::value &&
							std::is_nothrow_constructible<sl_allocator_overload, const Allocator&>::value
					))
				: sl_allocator_unrelated(), sl_allocator_overload(alloc)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(const single_list & src)
				: sl_allocator_unrelated(), sl_allocator_overload()
		{
			this->insert(this->cbegin(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(const single_list & src, const Allocator& alloc)
				: sl_allocator_unrelated(), sl_allocator_overload(alloc)
		{
			this->insert(this->cbegin(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n)
				: sl_allocator_unrelated(), sl_allocator_overload()
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n));
			this->_K_hook_node(this->cbegin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const Allocator& alloc)
				: sl_allocator_unrelated(), sl_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n));
			this->_K_hook_node(this->cbegin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const_reference val)
				: sl_allocator_unrelated(), sl_allocator_overload()
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n, val));
			this->_K_hook_node(this->cbegin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const_reference val, const Allocator& alloc)
				: sl_allocator_unrelated(), sl_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n, val));
			this->_K_hook_node(this->cbegin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type)
				: sl_allocator_unrelated(), sl_allocator_overload()
		{
			this->insert(this->cbegin(), first, last);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(InputIterator first, InputIterator last, const Allocator& alloc,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type)
				: sl_allocator_unrelated(), sl_allocator_overload(alloc)
		{
			this->insert(this->cbegin(), first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(single_list && src)
					KERBAL_NOEXCEPT((
						std::is_nothrow_constructible<sl_allocator_overload, node_allocator_type&&>::value
					))
				: sl_allocator_unrelated(), sl_allocator_overload(kerbal::compatibility::move(src.alloc()))
		{
			if (!src.empty()) {
				sl_type_unrelated::_K_swap_with_empty(src, *this);
			}
		}


		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::move_constructor_with_afforded_allocator_allocator_equal(single_list && src) KERBAL_NOEXCEPT
		{
			sl_type_unrelated::_K_swap_with_empty(src, *this);
		}

		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::move_constructor_with_afforded_allocator_allocator_not_equal(single_list && src)
		{
			std::pair<node*, node*> range(this->_K_build_new_nodes_range_unguarded_move(this->alloc(), src.begin(), src.end()));
			sl_type_unrelated::_K_hook_node(this->cend(), range.first, range.second);
		}

		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		template <bool is_allocator_always_equal>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<!is_allocator_always_equal>::type
		single_list<Tp, Allocator>::move_constructor_with_afforded_allocator_helper(single_list && src)
		{
			if (this->alloc() != src.alloc()) {
				this->move_constructor_with_afforded_allocator_allocator_not_equal(kerbal::compatibility::move(src));
			} else {
				this->move_constructor_with_afforded_allocator_allocator_equal(kerbal::compatibility::move(src));
			}
		}

		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		template <bool is_allocator_always_equal>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<is_allocator_always_equal>::type
		single_list<Tp, Allocator>::move_constructor_with_afforded_allocator_helper(single_list && src) KERBAL_NOEXCEPT
		{
			this->move_constructor_with_afforded_allocator_allocator_equal(kerbal::compatibility::move(src));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(single_list && src, const Allocator& alloc)
				: sl_allocator_unrelated(), sl_allocator_overload(alloc)
		{
			if (src.empty()) {
				return;
			}
			typedef typename std::allocator_traits<node_allocator_type>::is_always_equal is_always_equal;
//			typedef typename node_allocator_traits::is_always_equal is_always_equal;
			this->move_constructor_with_afforded_allocator_helper<is_always_equal::value>(kerbal::compatibility::move(src));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(std::initializer_list<value_type> src)
				: single_list(src.begin(), src.end())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(std::initializer_list<value_type> src, const Allocator& alloc)
				: single_list(src.begin(), src.end(), alloc)
		{
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		single_list<Tp, Allocator>::single_list(const kerbal::assign::assign_list<Up> & src)
				: sl_allocator_unrelated(), sl_allocator_overload()
		{
			this->insert(this->cend(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		template <typename Up>
		single_list<Tp, Allocator>::single_list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc)
				: sl_allocator_unrelated(), sl_allocator_overload(alloc)
		{
			this->insert(this->cend(), src.cbegin(), src.cend());
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::~single_list()
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->_K_consecutive_destroy_node(
								kerbal::utility::declthis<single_list>()->alloc(),
								kerbal::utility::declthis<single_list>()->head_node.next
						)) &&
						std::is_nothrow_destructible<sl_allocator_overload>::value
				)
		{
			this->_K_consecutive_destroy_node(this->alloc(), this->head_node.next);
		}


	//===================
	// assign

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>&
		single_list<Tp, Allocator>::operator=(const single_list& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->assign(src))
				)
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
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->assign(src))
				)
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
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->assign(src.cbegin(), src.cend()))
				)
		{
			this->assign(src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::assign(size_type count, const_reference val)
		{
			iterator it(this->begin());
			while (count != 0) {
				if (it != this->cend()) {
					kerbal::operators::generic_assign(*it, val); // *it = val;
					--count;
					++it;
				} else {
					this->insert(this->cend(), count, val);
					return;
				}
			}
			this->erase(it, this->cend());
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		single_list<Tp, Allocator>::assign(InputIterator first, InputIterator last)
		{
			iterator it(this->begin());
			while (first != last) {
				if (it != this->cend()) {
					kerbal::operators::generic_assign(*it, *first); // *it = *first;
					++first;
					++it;
				} else {
					this->insert(this->cend(), first, last);
					return;
				}
			}
			this->erase(it, this->cend());
		}


#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::assign(single_list&& src)
		{
			this->swap(src);
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
			this->emplace_front(val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::push_front(rvalue_reference val)
		{
			this->emplace_front(kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(Args&& ... args)
		{
			node *p = this->_K_build_new_node(this->alloc(), kerbal::utility::forward<Args>(args)...);
			this->_K_hook_node(this->basic_begin(), p);
			return p->value;
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front()
		{
			node *p = this->_K_build_new_node(this->alloc());
			this->_K_hook_node(this->basic_begin(), p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0& arg0)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0);
			this->_K_hook_node(this->basic_begin(), p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1);
			this->_K_hook_node(this->basic_begin(), p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1, arg2);
			this->_K_hook_node(this->basic_begin(), p);
			return p->value;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::push_back(const_reference val)
		{
			this->emplace_back(val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::push_back(rvalue_reference val)
		{
			this->emplace_back(kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(Args&& ... args)
		{
			node *p = this->_K_build_new_node(this->alloc(), kerbal::utility::forward<Args>(args)...);
			this->_K_hook_node_back(p);
			return p->value;
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back()
		{
			node *p = this->_K_build_new_node(this->alloc());
			this->_K_hook_node_back(p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(const Arg0& arg0)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0);
			this->_K_hook_node_back(p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1);
			this->_K_hook_node_back(p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1, arg2);
			this->_K_hook_node_back(p);
			return p->value;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::insert(const_iterator pos, const_reference val)
		{
			return this->emplace(pos, val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::insert(const_iterator pos, size_type n, const_reference val)
		{
			if (n == 0) {
				return pos.cast_to_mutable();
			}
			std::pair<node*, node*> range(this->_K_build_n_new_nodes_unguarded(this->alloc(), n, val));
			this->_K_hook_node(pos, range.first, range.second);
			return pos.cast_to_mutable();
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
			if (first == last) {
				return pos.cast_to_mutable();
			}
			std::pair<node*, node*> range(this->_K_build_new_nodes_range_unguarded(this->alloc(), first, last));
			this->_K_hook_node(pos, range.first, range.second);
			return pos.cast_to_mutable();
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return this->emplace(pos, kerbal::compatibility::move(val));
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
			node *p = this->_K_build_new_node(this->alloc(), kerbal::utility::forward<Args>(args)...);
			this->_K_hook_node(pos, p);
			return pos.cast_to_mutable();
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::emplace(const_iterator pos)
		{
			node *p = this->_K_build_new_node(this->alloc());
			this->_K_hook_node(pos, p);
			return pos.cast_to_mutable();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0);
			this->_K_hook_node(pos, p);
			return pos.cast_to_mutable();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1);
			this->_K_hook_node(pos, p);
			return pos.cast_to_mutable();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1, arg2);
			this->_K_hook_node(pos, p);
			return pos.cast_to_mutable();
		}

#	endif


	//===================
	// erase

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::pop_front()
		{
			this->erase(this->cbegin());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::erase(const_iterator pos)
		{
			return this->_K_erase(this->alloc(), pos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			return this->_K_erase(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::clear()
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::utility::declthis<sl_allocator_unrelated>()->_K_clear(
								kerbal::utility::declthis<single_list>()->alloc()
						))
				)
		{
			this->sl_allocator_unrelated::_K_clear(this->alloc());
		}


	//===================
	// operation

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::resize(size_type count)
		{
			const_iterator it(this->cbegin());
			const_iterator const cend(this->cend());
			size_type size(kerbal::iterator::advance_at_most(it, count, cend));
			if (size == count) {
				this->erase(it, cend);
			} else {
				// note: count - size != 0
				std::pair<node*, node*> range(this->_K_build_n_new_nodes_unguarded(this->alloc(), count - size));
				this->_K_hook_node(cend, range.first, range.second);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::resize(size_type count, const_reference value)
		{
			const_iterator it(this->cbegin());
			const_iterator const cend(this->cend());
			size_type size(kerbal::iterator::advance_at_most(it, count, cend));
			if (size == count) {
				this->erase(it, cend);
			} else {
				this->insert(cend, count - size, value);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::swap(single_list & with)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(sl_allocator_overload::_K_swap_allocator_if_propagate(
								kerbal::utility::declval<sl_allocator_overload&>(), kerbal::utility::declval<sl_allocator_overload&>()
						)) &&
						noexcept(sl_type_unrelated::_K_swap_type_unrelated(
								kerbal::utility::declval<sl_type_unrelated&>(), kerbal::utility::declval<sl_type_unrelated&>()
						))
				)
		{
			sl_allocator_overload::_K_swap_allocator_if_propagate(
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
			return sl_allocator_unrelated::_K_remove(this->alloc(), val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::remove(const_iterator first, const_iterator last, const_reference val)
		{
			return sl_allocator_unrelated::_K_remove(this->alloc(), first, last, val);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::remove_if(UnaryPredicate predicate)
		{
			return sl_allocator_unrelated::_K_remove_if(this->alloc(), predicate);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::remove_if(const_iterator first, const_iterator last, UnaryPredicate predicate)
		{
			return sl_allocator_unrelated::_K_remove_if(this->alloc(), first, last, predicate);
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
