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

#ifndef KERBAL_CONTAINER_IMPL_LIST_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_LIST_IMPL_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/operators/generic_assign.hpp>

#include <kerbal/container/list.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#else
#	include <kerbal/type_traits/fundamental_deduction.hpp>
#endif

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list()
					KERBAL_CONDITIONAL_NOEXCEPT(
							std::is_nothrow_default_constructible<list_allocator_unrelated>::value &&
							std::is_nothrow_default_constructible<list_allocator_overload>::value
					)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload()
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(const Allocator& alloc)
					KERBAL_CONDITIONAL_NOEXCEPT((
							std::is_nothrow_default_constructible<list_allocator_unrelated>::value &&
							std::is_nothrow_constructible<list_allocator_overload, const Allocator&>::value
					))
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(alloc)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(const list& src)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload()
		{
			this->insert(this->cend(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(const list& src, const Allocator& alloc)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(alloc)
		{
			this->insert(this->cend(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload()
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(this->alloc(), n));
			list_type_unrelated::__hook_node(this->cend(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const Allocator& alloc)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(this->alloc(), n));
			list_type_unrelated::__hook_node(this->cend(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const_reference val)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload()
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(this->alloc(), n, val));
			list_type_unrelated::__hook_node(this->cend(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const_reference val, const Allocator& alloc)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(this->alloc(), n, val));
			list_type_unrelated::__hook_node(this->cend(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload()
		{
			this->insert(this->cend(), first, last);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(InputIterator first, InputIterator last, const Allocator& alloc,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(alloc)
		{
			this->insert(this->cend(), first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(list&& src)
					KERBAL_NOEXCEPT((
						std::is_nothrow_constructible<list_allocator_overload, node_allocator_type&&>::value
					))
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(kerbal::compatibility::move(src.alloc()))
		{
			if (!src.empty()) {
				list_type_unrelated::__swap_with_empty(src, *this);
			}
		}


		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::move_constructor_with_afforded_allocator_allocator_equal(list && src) KERBAL_NOEXCEPT
		{
			list_type_unrelated::__swap_with_empty(src, *this);
		}

		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::move_constructor_with_afforded_allocator_allocator_not_equal(list && src)
		{
			std::pair<node*, node*> range(this->__build_new_nodes_range_unguarded_move(this->alloc(), src.begin(), src.end()));
			list_type_unrelated::__hook_node(this->cend(), range.first, range.second);
		}

		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		template <bool is_allocator_always_equal>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<!is_allocator_always_equal>::type
		list<Tp, Allocator>::move_constructor_with_afforded_allocator_helper(list && src)
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
		list<Tp, Allocator>::move_constructor_with_afforded_allocator_helper(list && src) KERBAL_NOEXCEPT
		{
			this->move_constructor_with_afforded_allocator_allocator_equal(kerbal::compatibility::move(src));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(list&& src, const Allocator& alloc)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(alloc)
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
		list<Tp, Allocator>::list(std::initializer_list<value_type> src)
				: list(src.begin(), src.end())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(std::initializer_list<value_type> src, const Allocator& alloc)
				: list(src.begin(), src.end(), alloc)
		{
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		list<Tp, Allocator>::list(const kerbal::assign::assign_list<Up> & src)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload()
		{
			this->insert(this->cend(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		template <typename Up>
		list<Tp, Allocator>::list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(alloc)
		{
			this->insert(this->cend(), src.cbegin(), src.cend());
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::~list()
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->clear())
				)
		{
			this->clear();
		}

		//===================
		//assign

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>&
		list<Tp, Allocator>::operator=(const list& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(src))
				)
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
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(src))
				)
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
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(src.cbegin(), src.cend()))
				)
		{
			this->assign(src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::assign(size_type count, const_reference val)
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
		list<Tp, Allocator>::assign(InputIterator first, InputIterator last)
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
		void list<Tp, Allocator>::assign(list&& src)
		{
			this->swap(src);
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
		//insert

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::push_front(const_reference val)
		{
			this->emplace_front(val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::push_front(rvalue_reference val)
		{
			this->emplace_front(kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_front(Args&& ... args)
		{
			return *this->emplace(this->cbegin(), std::forward<Args>(args)...);
		}

#	else

		template <typename Tp, typename Allocator>
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_front()
		{
			return *this->emplace(this->cbegin());
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_front(const Arg0& arg0)
		{
			return *this->emplace(this->cbegin(), arg0);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1)
		{
			return *this->emplace(this->cbegin(), arg0, arg1);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			return *this->emplace(this->cbegin(), arg0, arg1, arg2);
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::push_back(const_reference val)
		{
			this->emplace_back(val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::push_back(rvalue_reference val)
		{
			this->emplace_back(kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_back(Args&& ... args)
		{
			return *this->emplace(this->cend(), std::forward<Args>(args)...);
		}

#	else

		template <typename Tp, typename Allocator>
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_back()
		{
			return *this->emplace(this->cend());
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_back(const Arg0& arg0)
		{
			return *this->emplace(this->cend(), arg0);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_back(const Arg0& arg0, const Arg1& arg1)
		{
			return *this->emplace(this->cend(), arg0, arg1);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::emplace_back(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			return *this->emplace(this->cend(), arg0, arg1, arg2);
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, const_reference val)
		{
			return this->emplace(pos, val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, size_type n, const_reference val)
		{
			if (n == 0) {
				return pos.cast_to_mutable();
			}
			std::pair<node*, node*> range(this->__build_n_new_nodes_unguarded(this->alloc(), n, val));
			list_type_unrelated::__hook_node(pos, range.first, range.second);
			return iterator(range.first);
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
			if (first == last) {
				return pos.cast_to_mutable();
			}
			std::pair<node*, node*> range(this->__build_new_nodes_range_unguarded(this->alloc(), first, last));
			list_type_unrelated::__hook_node(pos, range.first, range.second);
			return iterator(range.first);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return this->emplace(pos, kerbal::compatibility::move(val));
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
			node *p = this->__build_new_node(this->alloc(), std::forward<Args>(args)...);
			list_type_unrelated::__hook_node(pos, p);
			return iterator(p);
		}

#	else

		template <typename Tp, typename Allocator>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos)
		{
			node *p = this->__build_new_node(this->alloc());
			list_type_unrelated::__hook_node(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0)
		{
			node *p = this->__build_new_node(this->alloc(), arg0);
			list_type_unrelated::__hook_node(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->__build_new_node(this->alloc(), arg0, arg1);
			list_type_unrelated::__hook_node(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->__build_new_node(this->alloc(), arg0, arg1, arg2);
			list_type_unrelated::__hook_node(pos, p);
			return iterator(p);
		}

#	endif

		//===================
		//erase

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::pop_front()
		{
			this->erase(this->cbegin());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::pop_back()
		{
			this->erase(kerbal::iterator::prev(this->cend()));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::erase(const_iterator pos)
		{
			iterator pos_mut(pos.cast_to_mutable());
			node_base * p = list_type_unrelated::__unhook_node(pos_mut++);
			this->__destroy_node(this->alloc(), p);
			return pos_mut;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			iterator last_mut(last.cast_to_mutable());
			if (first != last) {
				iterator first_mut(first.cast_to_mutable());
				std::pair<node_base *, node_base *> range(this->list_type_unrelated::__unhook_node(first_mut, last_mut));
				node_base * start = range.first;
				node_base * back = range.second;
				back->next = NULL;
				this->__consecutive_destroy_node(this->alloc(), start);
			}
			return last_mut;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::clear()
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(
					kerbal::utility::declthis<list>()->erase(
							kerbal::utility::declthis<list>()->cbegin(), kerbal::utility::declthis<list>()->cend()
					)
				))
		{
			this->erase(this->cbegin(), this->cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::resize(size_type count)
		{
			const_iterator it(this->cbegin());
			const_iterator cend(this->cend());
			size_type size(kerbal::iterator::advance_at_most(it, count, cend));
			if (size == count) {
				this->erase(it, cend);
			} else {
				// note: count - size != 0
				std::pair<node*, node*> range(this->__build_n_new_nodes_unguarded(this->alloc(), count - size));
				list_type_unrelated::__hook_node(cend, range.first, range.second);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::resize(size_type count, const_reference value)
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
		void list<Tp, Allocator>::swap(list& ano)
		{
			this->list_allocator_overload::swap_allocator_if_propagate(ano);

			list_type_unrelated::__swap_type_unrelated(*this, ano);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove(const_reference val)
		{
			size_type i = 0;
			const_iterator it = this->cbegin();
			while (it != this->cend()) {
				if (*it == val) {
					it = this->erase(it);
					++i;
				} else {
					++it;
				}
			}
			return i;
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove_if(UnaryPredicate predicate)
		{
			size_type i = 0;
			const_iterator it = this->cbegin();
			while (it != this->cend()) {
				if (predicate(*it)) {
					it = this->erase(it);
					++i;
				} else {
					++it;
				}
			}
			return i;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list & other) KERBAL_NOEXCEPT
		{
			list_type_unrelated::splice(pos, other);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list &, const_iterator opos) KERBAL_NOEXCEPT
		{
			list_type_unrelated::splice(pos, opos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list &, const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			list_type_unrelated::splice(pos, first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list&& other) KERBAL_NOEXCEPT
		{
			list_type_unrelated::splice(pos, other);
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>& list<Tp, Allocator>::operator+=(const list& with)
		{
			this->insert(this->cend(), with.cbegin(), with.cend());
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>& list<Tp, Allocator>::operator+=(list&& with)
		{
			this->splice(this->cend(), kerbal::compatibility::move(with));
			return *this;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>& list<Tp, Allocator>::operator+=(std::initializer_list<value_type> with)
		{
			this->insert(this->cend(), with.begin(), with.end());
			return *this;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(const list<Tp, Allocator>& lhs, const list<Tp, Allocator>& rhs)
		{
			list<Tp, Allocator> r(lhs);
			r.insert(r.cend(), rhs.cbegin(), rhs.cend());
			return r;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(const list<Tp, Allocator>& lhs, list<Tp, Allocator>&& rhs)
		{
			list<Tp, Allocator> r(lhs);
			r += kerbal::compatibility::move(rhs);
			return r;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator>&& lhs, const list<Tp, Allocator>& rhs)
		{
			list<Tp, Allocator> r(kerbal::compatibility::move(lhs));
			r += rhs;
			return r;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator>&& lhs, list<Tp, Allocator>&& rhs)
		{
			list<Tp, Allocator> r(kerbal::compatibility::move(lhs));
			r += kerbal::compatibility::move(rhs);
			return r;
		}

#	endif

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_LIST_IMPL_HPP
