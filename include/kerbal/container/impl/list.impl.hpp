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

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/guard.hpp>
#include <kerbal/operators/generic_assign.hpp>

#include <kerbal/container/list.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list()
					KERBAL_CONDITIONAL_NOEXCEPT(
							std::is_nothrow_default_constructible<node_allocator_type>::value
					)
				: head_node(detail::init_list_node_ptr_to_self_tag()), alloc()
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(const Allocator& alloc)
					KERBAL_CONDITIONAL_NOEXCEPT(
							std::is_nothrow_copy_constructible<node_allocator_type>::value
					)
				: head_node(detail::init_list_node_ptr_to_self_tag()), alloc(alloc)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(const list& src)
				: head_node(detail::init_list_node_ptr_to_self_tag()), alloc()
		{
			this->insert(this->cend(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(const list& src, const Allocator& alloc)
				: head_node(detail::init_list_node_ptr_to_self_tag()), alloc(alloc)
		{
			this->insert(this->cend(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const Allocator& alloc)
				: head_node(detail::init_list_node_ptr_to_self_tag()), alloc(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(n));
			__hook_node(this->cend(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const_reference val, const Allocator& alloc)
				: head_node(detail::init_list_node_ptr_to_self_tag()), alloc(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(n, val));
			__hook_node(this->cend(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(InputIterator first, InputIterator last, const Allocator& alloc,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type)
				: head_node(detail::init_list_node_ptr_to_self_tag()), alloc(alloc)
		{
			this->insert(this->cend(), first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(list&& src)
				: head_node(detail::init_list_node_ptr_to_self_tag()), alloc(std::move(src.alloc))
		{
			if (!src.empty()) {
				__swap_with_empty(src, *this);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(list&& src, const Allocator& alloc)
				: head_node(detail::init_list_node_ptr_to_self_tag()), alloc(alloc)
		{
			if (!src.empty()) {
				__swap_with_empty(src, *this);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(std::initializer_list<value_type> src, const Allocator& alloc)
				: list(src.begin(), src.end(), alloc)
		{
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
						noexcept(kerbal::utility::declthis<list>()->assign(std::move(src)))
				)
		{
			this->assign(std::move(src));
			return *this;
		}

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

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::assign(std::initializer_list<value_type> src)
		{
			this->assign(src.begin(), src.end());
		}

#	endif

		//===================
		//element access

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::front() KERBAL_NOEXCEPT
		{
			return this->head_node.next->template reinterpret_as<Tp>().value;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_reference
		list<Tp, Allocator>::front() const KERBAL_NOEXCEPT
		{
			return this->head_node.next->template reinterpret_as<Tp>().value;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::reference
		list<Tp, Allocator>::back() KERBAL_NOEXCEPT
		{
			return this->head_node.prev->template reinterpret_as<Tp>().value;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_reference
		list<Tp, Allocator>::back() const KERBAL_NOEXCEPT
		{
			return this->head_node.prev->template reinterpret_as<Tp>().value;
		}

		//===================
		//iterator

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::begin() KERBAL_NOEXCEPT
		{
			return iterator(this->head_node.next);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::end() KERBAL_NOEXCEPT
		{
			return iterator(&this->head_node);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_iterator
		list<Tp, Allocator>::begin() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->head_node.next);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_iterator
		list<Tp, Allocator>::end() const KERBAL_NOEXCEPT
		{
			return const_iterator(&this->head_node);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_iterator
		list<Tp, Allocator>::cbegin() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->head_node.next);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_iterator
		list<Tp, Allocator>::cend() const KERBAL_NOEXCEPT
		{
			return const_iterator(&this->head_node);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::reverse_iterator
		list<Tp, Allocator>::rbegin() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->end());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::reverse_iterator
		list<Tp, Allocator>::rend() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->begin());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_reverse_iterator
		list<Tp, Allocator>::rbegin() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->end());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_reverse_iterator
		list<Tp, Allocator>::rend() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->begin());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_reverse_iterator
		list<Tp, Allocator>::crbegin() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_reverse_iterator
		list<Tp, Allocator>::crend() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->cbegin());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::nth(size_type index) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::next(this->begin(), index);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::const_iterator
		list<Tp, Allocator>::nth(size_type index) const KERBAL_NOEXCEPT
		{
			return kerbal::iterator::next(this->cbegin(), index);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::index_of(iterator it) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::distance(this->begin(), it);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::index_of(const_iterator it) const KERBAL_NOEXCEPT
		{
			return kerbal::iterator::distance(this->cbegin(), it);
		}

		//===================
		//capacity

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool list<Tp, Allocator>::empty() const KERBAL_NOEXCEPT
		{
			return this->head_node.next == &this->head_node;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::size() const KERBAL_NOEXCEPT
		{
			return kerbal::iterator::distance(this->cbegin(), this->cend());
		}

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
			this->emplace_front(std::move(val));
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
			this->emplace_back(std::move(val));
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
			std::pair<node*, node*> range(this->__build_n_new_nodes_unguarded(n, val));
			__hook_node(pos, range.first, range.second);
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
			std::pair<node*, node*> range(this->__build_new_nodes_range_unguarded(first, last));
			__hook_node(pos, range.first, range.second);
			return iterator(range.first);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return this->emplace(pos, std::move(val));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> src)
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
			node *p = this->__build_new_node(std::forward<Args>(args)...);
			__hook_node(pos, p);
			return iterator(p);
		}

#	else

		template <typename Tp, typename Allocator>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos)
		{
			node *p = this->__build_new_node();
			__hook_node(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0)
		{
			node *p = this->__build_new_node(arg0);
			__hook_node(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->__build_new_node(arg0, arg1);
			__hook_node(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->__build_new_node(arg0, arg1, arg2);
			__hook_node(pos, p);
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
			node_base * p = pos_mut.current;
			++pos_mut;
			p->prev->next = p->next;
			p->next->prev = p->prev;
			this->__destroy_node(p);
			return pos_mut;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			iterator last_mut(last.cast_to_mutable());
			if (first == last) {
				return last_mut;
			}
			iterator first_mut(first.cast_to_mutable());
			node_base * start = first_mut.current;
			node_base * end = last_mut.current;
			end->prev->next = NULL;
			end->prev = start->prev;
			start->prev->next = end;
			this->__consecutive_destroy_node(start);
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
			difference_type size = kerbal::iterator::advance_at_most(it, count, cend);
			if (size == count) {
				this->erase(it, cend);
			} else {
				// note: count - size != 0
				std::pair<node*, node*> range(this->__build_n_new_nodes_unguarded(count - size));
				__hook_node(cend, range.first, range.second);
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
			bool is_this_empty = this->empty();
			bool is_ano_empty = ano.empty();
			kerbal::algorithm::swap(this->alloc, ano.alloc);
			if (is_this_empty) {
				if (!is_ano_empty) {
					// this->empty() && !ano.empty()
					__swap_with_empty(ano, *this);
				}
			} else {
				if (is_ano_empty) {
					// !this->empty() and ano.empty()
					__swap_with_empty(*this, ano);
				} else {
					// !this->empty() and !ano.empty()
					kerbal::algorithm::swap(this->head_node.prev, ano.head_node.prev);
					this->head_node.prev->next = &this->head_node;
					ano.head_node.prev->next = &ano.head_node;

					kerbal::algorithm::swap(this->head_node.next, ano.head_node.next);
					this->head_node.next->prev = &this->head_node;
					ano.head_node.next->prev = &ano.head_node;
				}
			}
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
		void list<Tp, Allocator>::splice(const_iterator pos, list& other) KERBAL_NOEXCEPT
		{

#	if __cplusplus >= 201103L
			this->splice(pos, std::move(other));
#	else
			this->splice(pos, other, other.cbegin(), other.cend());
#	endif

		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list& other, const_iterator opos) KERBAL_NOEXCEPT
		{
			iterator opos_mut(opos.cast_to_mutable());
			node_base * p = opos_mut.current;
			p->prev->next = p->next;
			p->next->prev = p->prev;
			__hook_node(pos, p);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list& other, const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			if (first == last) {
				return;
			}
			iterator first_mut(first.cast_to_mutable());
			iterator last_mut(last.cast_to_mutable());
			node_base * start = first_mut.current;
			node_base * end = last_mut.current;
			start->prev->next = end;
			end->prev = start->prev;
			__hook_node(pos, start, end->prev);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list&& other) KERBAL_NOEXCEPT
		{
			this->splice(pos, other, other.cbegin(), other.cend());
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
			this->splice(this->cend(), std::move(with));
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
			r += std::move(rhs);
			return r;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator>&& lhs, const list<Tp, Allocator>& rhs)
		{
			list<Tp, Allocator> r(std::move(lhs));
			r += rhs;
			return r;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator>&& lhs, list<Tp, Allocator>&& rhs)
		{
			list<Tp, Allocator> r(std::move(lhs));
			r += std::move(rhs);
			return r;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::node*
		list<Tp, Allocator>::__build_new_node_helper(kerbal::type_traits::false_type, Args&& ...args)
		{
			node *p = node_allocator_traits::allocate(this->alloc, 1);
			kerbal::memory::guard<node, release_uninit_res> gd(p, release_uninit_res(this->alloc));
			node_allocator_traits::construct(this->alloc, p, kerbal::utility::in_place_t(), std::forward<Args>(args)...);
			gd.release();
			return p;
		}

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::node*
		list<Tp, Allocator>::__build_new_node_helper(kerbal::type_traits::true_type, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(node_allocator_traits::allocate(kerbal::utility::declthis<list>()->alloc, 1))
							)
		{
			node *p = node_allocator_traits::allocate(this->alloc, 1);
			node_allocator_traits::construct(this->alloc, p, kerbal::utility::in_place_t(), std::forward<Args>(args)...);
			return p;
		}

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::node*
		list<Tp, Allocator>::__build_new_node(Args&& ... args)
		{
			typedef kerbal::type_traits::conditional_boolean<
					std::is_nothrow_constructible<Tp, Args...>::value
			> nothrow_while_construct;
			return this->__build_new_node_helper(nothrow_while_construct(), std::forward<Args>(args)...);
		}

#	else

#define __build_new_node_body(args...) \
		{ \
			node *p = node_allocator_traits::allocate(this->alloc, 1); \
			kerbal::memory::guard<node, release_uninit_res> gd(p, release_uninit_res(this->alloc)); \
			node_allocator_traits::construct(this->alloc, p, args); \
			gd.release(); \
			return p; \
		}


		template <typename Tp, typename Allocator>
		typename list<Tp, Allocator>::node*
		list<Tp, Allocator>::__build_new_node()
		{
			__build_new_node_body(kerbal::utility::in_place_t());
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename list<Tp, Allocator>::node*
		list<Tp, Allocator>::__build_new_node(const Arg0 & arg0)
		{
			__build_new_node_body(kerbal::utility::in_place_t(), arg0);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename list<Tp, Allocator>::node*
		list<Tp, Allocator>::__build_new_node(const Arg0 & arg0, const Arg1 & arg1)
		{
			__build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename list<Tp, Allocator>::node*
		list<Tp, Allocator>::__build_new_node(const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
		{
			__build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1, arg2);
		}

#undef __build_new_node_body

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename... Args>
		KERBAL_CONSTEXPR20
		std::pair<typename list<Tp, Allocator>::node*, typename list<Tp, Allocator>::node*>
		list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n, Args&& ... args)
		{
			size_t cnt = 0;
			node * const start = this->__build_new_node(std::forward<Args>(args)...);
			node * back = start;
			try {
				++cnt;
				while (cnt != n) {
					node* new_node = this->__build_new_node(std::forward<Args>(args)...);
					new_node->prev = back;
					back->next = new_node;
					back = new_node;
					++cnt;
				}
				return std::pair<node*, node*>(start, back);
			} catch (...) {
				this->__consecutive_destroy_node(start);
				throw;
			}
		}

#	else


#define __build_n_new_nodes_unguarded_body(args...) \
		{ \
			size_t cnt = 0; \
			node * const start = this->__build_new_node(args); \
			node * back = start; \
			try { \
				++cnt; \
				while (cnt != n) { \
					node* new_node = this->__build_new_node(args); \
					new_node->prev = back; \
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


		template <typename Tp, typename Allocator>
		std::pair<typename list<Tp, Allocator>::node*, typename list<Tp, Allocator>::node*>
		list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n)
		{
			__build_n_new_nodes_unguarded_body();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		std::pair<typename list<Tp, Allocator>::node*, typename list<Tp, Allocator>::node*>
		list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n, const Arg0 & arg0)
		{
			__build_n_new_nodes_unguarded_body(arg0);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		std::pair<typename list<Tp, Allocator>::node*, typename list<Tp, Allocator>::node*>
		list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n, const Arg0 & arg0, const Arg1 & arg1)
		{
			__build_n_new_nodes_unguarded_body(arg0, arg1);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		std::pair<typename list<Tp, Allocator>::node*, typename list<Tp, Allocator>::node*>
		list<Tp, Allocator>::__build_n_new_nodes_unguarded(size_type n, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
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
				std::pair<typename list<Tp, Allocator>::node*, typename list<Tp, Allocator>::node*>
		>::type
		list<Tp, Allocator>::__build_new_nodes_range_unguarded(InputIterator first, InputIterator last)
		{
			node * const start = this->__build_new_node(*first);
			node * back = start;
			try {
				++first;
				while (first != last) {
					node* new_node = this->__build_new_node(*first);
					new_node->prev = back;
					back->next = new_node;
					back = new_node;
					++first;
				}
				return std::pair<node*, node*>(start, back);
			} catch (...) {
				this->__consecutive_destroy_node(start);
				throw;
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::__destroy_node(node_base* p_node_base)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(node_allocator_traits::destroy(kerbal::utility::declthis<list>()->alloc, kerbal::utility::declval<node*>())) &&
						noexcept(node_allocator_traits::deallocate(kerbal::utility::declthis<list>()->alloc, kerbal::utility::declval<node*>(), 1))
				)
		{
			node * p_node = &p_node_base->template reinterpret_as<Tp>();
			node_allocator_traits::destroy(this->alloc, p_node);
			node_allocator_traits::deallocate(this->alloc, p_node, 1);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::__consecutive_destroy_node(node_base * start)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->__destroy_node(kerbal::utility::declval<node_base*>()))
				)
		{
			node_base * current_node_base = start;
			while (current_node_base != NULL) {
				node_base * next = current_node_base->next;
				this->__destroy_node(current_node_base);
				current_node_base = next;
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::__hook_node(const_iterator pos, node_base * p) KERBAL_NOEXCEPT
		{
			iterator pos_mut(pos.cast_to_mutable());
			node_base * next = pos_mut.current;
			p->prev = next->prev;
			p->next = next;
			next->prev->next = p;
			next->prev = p;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::__hook_node(const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
		{
			// (?, ?)
			// (?, 1) (0, 2) (1, 3) (2, ?)
			iterator pos_mut(pos.cast_to_mutable());
			node_base * next = pos_mut.current;
			start->prev = next->prev;
			back->next = next;
			start->prev->next = start;
			next->prev = back;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::__swap_with_empty(list& not_empty_list, list& empty_list) KERBAL_NOEXCEPT
		{
			empty_list.head_node.prev = not_empty_list.head_node.prev;
			empty_list.head_node.prev->next = &empty_list.head_node;
			empty_list.head_node.next = not_empty_list.head_node.next;
			empty_list.head_node.next->prev = &empty_list.head_node;
			not_empty_list.__init_node_base();
		}


	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_LIST_IMPL_HPP
