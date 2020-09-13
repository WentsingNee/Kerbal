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

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/operators/generic_assign.hpp>
#include <kerbal/utility/declval.hpp>

#include <kerbal/container/single_list.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list()
					KERBAL_CONDITIONAL_NOEXCEPT(
							std::is_nothrow_default_constructible<sl_allocator_unrelated>::value &&
							std::is_nothrow_default_constructible<sl_allocator_overload>::value
					)
				: sl_allocator_unrelated(), sl_allocator_overload()
		{
		}

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
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(n));
			this->__hook_node(this->cbegin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const Allocator& alloc)
				: sl_allocator_unrelated(), sl_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(n));
			this->__hook_node(this->cbegin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const_reference val)
				: sl_allocator_unrelated(), sl_allocator_overload()
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(n, val));
			this->__hook_node(this->cbegin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const_reference val, const Allocator& alloc)
				: sl_allocator_unrelated(), sl_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(n, val));
			this->__hook_node(this->cbegin(), p.first, p.second);
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
				: sl_allocator_unrelated(), sl_allocator_overload(kerbal::compatibility::move(src.alloc()))
		{
			if (!src.empty()) {
				sl_type_unrelated::swap_with_empty(src, *this);
			}
		}


		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::move_constructor_with_afforded_allocator_allocator_equal(single_list && src)
		{
			sl_type_unrelated::swap_with_empty(src, *this);
		}

		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::move_constructor_with_afforded_allocator_allocator_not_equal(single_list && src)
		{
			std::pair<node*, node*> range(this->__build_new_nodes_range_unguarded_move(src.begin(), src.end()));
			sl_type_unrelated::__hook_node(this->cend(), range.first, range.second);
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
		single_list<Tp, Allocator>::move_constructor_with_afforded_allocator_helper(single_list && src)
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
		{
			this->__consecutive_destroy_node(this->head_node.next);
		}

		//===================
		//assign

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
			size_type i = 0;
			while (i != count) {
				if (it != this->cend()) {
					kerbal::operators::generic_assign(*it, val); // *it = val;
					++i;
					++it;
				} else {
					this->insert(this->cend(), count - i, val);
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
		//insert

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
			node *p = this->__build_new_node(std::forward<Args>(args)...);
			this->__hook_node(this->basic_begin(), p);
			return p->value;
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front()
		{
			node *p = this->__build_new_node();
			this->__hook_node(this->basic_begin(), p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0& arg0)
		{
			node *p = this->__build_new_node(arg0);
			this->__hook_node(this->basic_begin(), p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->__build_new_node(arg0, arg1);
			this->__hook_node(this->basic_begin(), p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->__build_new_node(arg0, arg1, arg2);
			this->__hook_node(this->basic_begin(), p);
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
			node *p = this->__build_new_node(std::forward<Args>(args)...);
			this->__hook_node_back(p);
			return p->value;
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back()
		{
			node *p = this->__build_new_node();
			this->__hook_node_back(p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(const Arg0& arg0)
		{
			node *p = this->__build_new_node(arg0);
			this->__hook_node_back(p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->__build_new_node(arg0, arg1);
			this->__hook_node_back(p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->__build_new_node(arg0, arg1, arg2);
			this->__hook_node_back(p);
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
			std::pair<node*, node*> range(this->__build_n_new_nodes_unguarded(n, val));
			this->__hook_node(pos, range.first, range.second);
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
			std::pair<node*, node*> range(this->__build_new_nodes_range_unguarded(first, last));
			this->__hook_node(pos, range.first, range.second);
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
			node *p = this->__build_new_node(std::forward<Args>(args)...);
			this->__hook_node(pos, p);
			return pos.cast_to_mutable();
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::emplace(const_iterator pos)
		{
			node *p = this->__build_new_node();
			this->__hook_node(pos, p);
			return pos.cast_to_mutable();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0)
		{
			node *p = this->__build_new_node(arg0);
			this->__hook_node(pos, p);
			return pos.cast_to_mutable();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->__build_new_node(arg0, arg1);
			this->__hook_node(pos, p);
			return pos.cast_to_mutable();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->__build_new_node(arg0, arg1, arg2);
			this->__hook_node(pos, p);
			return pos.cast_to_mutable();
		}

#	endif

		//===================
		//erase

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
			iterator pos_mut(pos.cast_to_mutable());
			node_base * p = sl_type_unrelated::__unhook_node(pos_mut);
			this->__destroy_node(p);
			return pos_mut;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			iterator first_mut(first.cast_to_mutable());
			iterator last_mut(last.cast_to_mutable());
			if (first != last) {
				std::pair<node_base *, node_base *> range(this->sl_type_unrelated::__unhook_node(first_mut, last_mut));
				node_base * start = range.first;
				node_base * back = range.second;
				back->next = NULL;
				this->__consecutive_destroy_node(start);
			}
			return first_mut;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::clear()
		{
			this->__consecutive_destroy_node(this->head_node.next);
			this->head_node.next = NULL;
			this->last_iter = this->begin();
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::resize(size_type count)
		{
			const_iterator it(this->cbegin());
			const_iterator cend(this->cend());
			difference_type size = kerbal::iterator::advance_at_most(it, count, cend);
			if (size == count) {
				this->erase(it, cend);
			} else {
				// note: count - size != 0
				std::pair<node*, node*> range(this->__build_n_new_nodes_unguarded(count - size));
				this->__hook_node(cend, range.first, range.second);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::resize(size_type count, const_reference value)
		{
			const_iterator it(this->cbegin());
			difference_type size = kerbal::iterator::advance_at_most(it, count, this->cend());
			if (size == count) {
				this->erase(it, this->cend());
			} else {
				this->insert(this->cend(), count - size, value);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::swap(single_list & ano)
		{
			typedef typename node_allocator_traits::propagate_on_container_swap propagate_on_container_swap;
			this->swap_allocator_helper<propagate_on_container_swap::value>();

			sl_allocator_unrelated::swap_allocator_unrelated(ano);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::splice(const_iterator pos, single_list & other) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::splice(pos, other);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::splice(const_iterator pos, single_list & other, const_iterator opos) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::splice(pos, other, opos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::splice(const_iterator pos, single_list & other,
												const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			this->sl_type_unrelated::splice(pos, other, first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node_helper(kerbal::type_traits::false_type, Args&& ... args)
		{
			node *p = node_allocator_traits::allocate(this->alloc(), 1);
			try {
				node_allocator_traits::construct(this->alloc(), p, kerbal::utility::in_place_t(), std::forward<Args>(args)...);
			} catch (...) {
				node_allocator_traits::deallocate(this->alloc(), p, 1);
				throw;
			}
			return p;
		}

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node_helper(kerbal::type_traits::true_type, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(node_allocator_traits::allocate(kerbal::utility::declthis<single_list>()->alloc(), 1))
							)
		{
			node *p = node_allocator_traits::allocate(this->alloc(), 1);
			node_allocator_traits::construct(this->alloc(), p, kerbal::utility::in_place_t(), std::forward<Args>(args)...);
			return p;
		}

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node(Args&& ... args)
		{
			typedef
#	if __cpp_exceptions
			kerbal::type_traits::conditional_boolean<
					std::is_nothrow_constructible<Tp, Args...>::value
			>
#	else
			kerbal::type_traits::true_type
#	endif // __cpp_exceptions
			nothrow_while_construct;

			return this->__build_new_node_helper(nothrow_while_construct(), std::forward<Args>(args)...);
		}

#	else


#if __cpp_exceptions

#	define __build_new_node_body(args...) \
		{ \
			node *p = node_allocator_traits::allocate(this->alloc(), 1); \
			try { \
				node_allocator_traits::construct(this->alloc(), p, args); \
			} catch (...) { \
				node_allocator_traits::deallocate(this->alloc(), p, 1); \
				throw; \
			} \
			return p; \
		}

#else

#	define __build_new_node_body(args...) \
		{ \
			node *p = node_allocator_traits::allocate(this->alloc(), 1); \
			node_allocator_traits::construct(this->alloc(), p, args); \
			return p; \
		}

#endif // __cpp_exceptions


		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node()
		{
			__build_new_node_body(kerbal::utility::in_place_t());
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node(const Arg0 & arg0)
		{
			__build_new_node_body(kerbal::utility::in_place_t(), arg0);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node(const Arg0 & arg0, const Arg1 & arg1)
		{
			__build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node(const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
		{
			__build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1, arg2);
		}

#undef __build_new_node_body

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename... Args>
		KERBAL_CONSTEXPR20
		std::pair<typename single_list<Tp, Allocator>::node*, typename single_list<Tp, Allocator>::node*>
		single_list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n, Args&& ... args)
		{
			size_t cnt = 0;
			node * const start = this->__build_new_node(std::forward<Args>(args)...);
			node * back = start;
#		if __cpp_exceptions
			try {
#		endif // __cpp_exceptions
				++cnt;
				while (cnt != n) {
					node* new_node = this->__build_new_node(std::forward<Args>(args)...);
					back->next = new_node;
					back = new_node;
					++cnt;
				}
				return std::pair<node*, node*>(start, back);
#		if __cpp_exceptions
			} catch (...) {
				this->__consecutive_destroy_node(start);
				throw;
			}
#		endif // __cpp_exceptions
		}

#	else


#if __cpp_exceptions

#	define __build_n_new_nodes_unguarded_body(args...) \
		{ \
			size_t cnt = 0; \
			node * const start = this->__build_new_node(args); \
			node * back = start; \
			try { \
				++cnt; \
				while (cnt != n) { \
					node* new_node = this->__build_new_node(args); \
					back->next = new_node; \
					back = new_node; \
					++cnt; \
				} \
				return std::pair<node*, node*>(start, back); \
			} catch (...) { \
				this->__consecutive_destroy_node(start); \
				throw; \
			} \
		}

#else

#	define __build_n_new_nodes_unguarded_body(args...) \
		{ \
			size_t cnt = 0; \
			node * const start = this->__build_new_node(args); \
			node * back = start; \
			++cnt; \
			while (cnt != n) { \
				node* new_node = this->__build_new_node(args); \
				back->next = new_node; \
				back = new_node; \
				++cnt; \
			} \
			return std::pair<node*, node*>(start, back); \
		}

#endif


		template <typename Tp, typename Allocator>
		std::pair<typename single_list<Tp, Allocator>::node*, typename single_list<Tp, Allocator>::node*>
		single_list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n)
		{
			__build_n_new_nodes_unguarded_body();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		std::pair<typename single_list<Tp, Allocator>::node*, typename single_list<Tp, Allocator>::node*>
		single_list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n, const Arg0 & arg0)
		{
			__build_n_new_nodes_unguarded_body(arg0);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		std::pair<typename single_list<Tp, Allocator>::node*, typename single_list<Tp, Allocator>::node*>
		single_list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n, const Arg0 & arg0, const Arg1 & arg1)
		{
			__build_n_new_nodes_unguarded_body(arg0, arg1);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		std::pair<typename single_list<Tp, Allocator>::node*, typename single_list<Tp, Allocator>::node*>
		single_list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
		{
			__build_n_new_nodes_unguarded_body(arg0, arg1, arg2);
		}

#undef __build_n_new_nodes_unguarded_body

#	endif

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				std::pair<typename single_list<Tp, Allocator>::node*, typename single_list<Tp, Allocator>::node*>
		>::type
		single_list<Tp, Allocator>::__build_new_nodes_range_unguarded(InputIterator first, InputIterator last)
		{
			node * const start = this->__build_new_node(*first);
			node * back = start;
#		if __cpp_exceptions
			try {
#		endif // __cpp_exceptions
				++first;
				while (first != last) {
					node* new_node = this->__build_new_node(*first);
					back->next = new_node;
					back = new_node;
					++first;
				}
				return std::pair<node*, node*>(start, back);
#		if __cpp_exceptions
			} catch (...) {
				this->__consecutive_destroy_node(start);
				throw;
			}
#		endif // __cpp_exceptions
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		std::pair<typename single_list<Tp, Allocator>::node*, typename single_list<Tp, Allocator>::node*>
		single_list<Tp, Allocator>::__build_new_nodes_range_unguarded_move(iterator first, iterator last)
		{
			node * const start = this->__build_new_node(kerbal::compatibility::move(*first));
			node * back = start;
#		if __cpp_exceptions
			try {
#		endif // __cpp_exceptions
				++first;
				while (first != last) {
					node* new_node = this->__build_new_node(kerbal::compatibility::move(*first));
					back->next = new_node;
					back = new_node;
					++first;
				}
				return std::pair<node*, node*>(start, back);
#		if __cpp_exceptions
			} catch (...) {
				this->__consecutive_destroy_node(start);
				throw;
			}
#		endif // __cpp_exceptions
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::__destroy_node(node_base* p_node_base)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(node_allocator_traits::destroy(kerbal::utility::declthis<single_list>()->alloc(), kerbal::utility::declval<node*>())) &&
						noexcept(node_allocator_traits::deallocate(kerbal::utility::declthis<single_list>()->alloc(), kerbal::utility::declval<node*>(), 1))
				)
		{
			node * p_node = &p_node_base->template reinterpret_as<Tp>();
			node_allocator_traits::destroy(this->alloc(), p_node);
			node_allocator_traits::deallocate(this->alloc(), p_node, 1);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::__consecutive_destroy_node(node_base * start)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->__destroy_node(kerbal::utility::declval<node_base*>()))
				)
		{
			node_base * current_node_base = start;
			while (current_node_base != NULL) {
				node_base * next = current_node_base->next;
				this->__destroy_node(current_node_base);
				current_node_base = next;
			}
		}


	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_SINGLE_LIST_IMPL_HPP
