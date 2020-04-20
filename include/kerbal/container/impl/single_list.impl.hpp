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

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/guard.hpp>

#include <kerbal/container/single_list.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list()
					KERBAL_CONDITIONAL_NOEXCEPT(
							std::is_nothrow_default_constructible<node_allocator_type>::value
					)
				: head_node(), last_iter(this->begin()), alloc()
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(const Allocator& alloc)
					KERBAL_CONDITIONAL_NOEXCEPT(
							std::is_nothrow_copy_constructible<node_allocator_type>::value
					)
				: head_node(), last_iter(this->begin()), alloc(alloc)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(const single_list & src)
				: head_node(), last_iter(this->begin()), alloc()
		{
			this->insert(this->cbegin(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(const single_list & src, const Allocator& alloc)
				: head_node(), last_iter(this->begin()), alloc(alloc)
		{
			this->insert(this->cbegin(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const Allocator& alloc)
				: head_node(), last_iter(this->begin()), alloc(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->__build_n_new_nodes_unguarded(n));
			this->__hook_node(this->cbegin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(size_type n, const_reference val, const Allocator& alloc)
				: head_node(), last_iter(this->begin()), alloc(alloc)
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
		single_list<Tp, Allocator>::single_list(InputIterator first, InputIterator last, const Allocator& alloc,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type)
				: head_node(), last_iter(this->begin()), alloc(alloc)
		{
			this->insert(this->cbegin(), first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(single_list && src)
				: head_node(), last_iter(this->begin()), alloc(std::move(src.alloc))
		{
			if (!src.empty()) {
				__swap_with_empty(src, *this);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(single_list && src, const Allocator& alloc)
				: head_node(), last_iter(this->begin()), alloc(alloc)
		{
			if (!src.empty()) {
				__swap_with_empty(src, *this);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator>::single_list(std::initializer_list<value_type> src, const Allocator& alloc)
				: single_list(src.begin(), src.end(), alloc)
		{
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
						noexcept(kerbal::utility::declthis<single_list>()->assign(std::move(src)))
				)
		{
			this->assign(std::move(src));
			return *this;
		}

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
					*it = val;
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
					*it = *first;
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

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::assign(std::initializer_list<value_type> src)
		{
			this->assign(src.begin(), src.end());
		}

#	endif

		//===================
		//element access

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::front() KERBAL_NOEXCEPT
		{
			return *this->begin();
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::const_reference
		single_list<Tp, Allocator>::front() const KERBAL_NOEXCEPT
		{
			return *this->cbegin();
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::back() KERBAL_NOEXCEPT
		{
			return this->end().current->template reinterpret_as<Tp>().value;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::const_reference
		single_list<Tp, Allocator>::back() const KERBAL_NOEXCEPT
		{
			return this->cend().current->template reinterpret_as<Tp>().value;
		}

		//===================
		//iterator

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::begin() KERBAL_NOEXCEPT
		{
			return iterator(&this->head_node);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::end() KERBAL_NOEXCEPT
		{
			return this->last_iter;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::begin() const KERBAL_NOEXCEPT
		{
			return const_iterator(&this->head_node);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::end() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->last_iter);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::cbegin() const KERBAL_NOEXCEPT
		{
			return const_iterator(&this->head_node);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::cend() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->last_iter);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::nth(size_type index) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::next(this->begin(), index);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::nth(size_type index) const KERBAL_NOEXCEPT
		{
			return kerbal::iterator::next(this->cbegin(), index);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::index_of(iterator it) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::distance(this->begin(), it);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::index_of(const_iterator it) const KERBAL_NOEXCEPT
		{
			return kerbal::iterator::distance(this->cbegin(), it);
		}

		//===================
		//capacity

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool single_list<Tp, Allocator>::empty() const KERBAL_NOEXCEPT
		{
			return this->cbegin() == this->cend();
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::size() const KERBAL_NOEXCEPT
		{
			return kerbal::iterator::distance(this->cbegin(), this->cend());
		}

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
			this->emplace_front(std::move(val));
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
			this->__hook_node_front(p);
			return p->value;
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front()
		{
			node *p = this->__build_new_node();
			this->__hook_node_front(p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0& arg0)
		{
			node *p = this->__build_new_node(arg0);
			this->__hook_node_front(p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->__build_new_node(arg0, arg1);
			this->__hook_node_front(p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->__build_new_node(arg0, arg1, arg2);
			this->__hook_node_front(p);
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
			this->emplace_back(std::move(val));
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
			return this->emplace(pos, std::move(val));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> src)
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
			node_base * prev = pos_mut.current;
			node_base * p = prev->next;
			prev->next = p->next;
			if (p->next == NULL) { // is back node
				this->last_iter = pos_mut;
			}
			this->__destroy_node(p);
			return pos_mut;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			iterator last_mut(last.cast_to_mutable());
			if (first == last) {
				return last_mut;
			}
			iterator first_mut(first.cast_to_mutable());
			node_base * prev = first_mut.current;
			node_base * start = prev->next;
			node_base * back = last_mut.current;
			node_base * next = back->next;
			prev->next = next;
			if (next == NULL) { // is back node
				this->last_iter = first_mut;
			}
			back->next = NULL;
			this->__consecutive_destroy_node(start);
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
			difference_type size = kerbal::iterator::advance_at_most(it, count, this->cend());
			if (size == count) {
				this->erase(it, this->cend());
			} else {
				this->insert(this->cend(), count - size);
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
					kerbal::algorithm::swap(this->head_node.next, ano.head_node.next);
					kerbal::algorithm::swap(this->last_iter, ano.last_iter);
				}
			}
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node_helper(kerbal::type_traits::false_type, Args&& ... args)
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
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node_helper(kerbal::type_traits::true_type, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(node_allocator_traits::allocate(kerbal::utility::declthis<single_list>()->alloc, 1))
							)
		{
			node *p = node_allocator_traits::allocate(this->alloc, 1);
			node_allocator_traits::construct(this->alloc, p, kerbal::utility::in_place_t(), std::forward<Args>(args)...);
			return p;
		}

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__build_new_node(Args&& ... args)
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
			try {
				++cnt;
				while (cnt != n) {
					node* new_node = this->__build_new_node(std::forward<Args>(args)...);
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
			try {
				++first;
				while (first != last) {
					node* new_node = this->__build_new_node(*first);
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
		void single_list<Tp, Allocator>::__destroy_node(node_base* p_node_base)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(node_allocator_traits::destroy(kerbal::utility::declthis<single_list>()->alloc, kerbal::utility::declval<node*>())) &&
						noexcept(node_allocator_traits::deallocate(kerbal::utility::declthis<single_list>()->alloc, kerbal::utility::declval<node*>(), 1))
				)
		{
			node * p_node = &p_node_base->template reinterpret_as<Tp>();
			node_allocator_traits::destroy(this->alloc, p_node);
			node_allocator_traits::deallocate(this->alloc, p_node, 1);
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

		// pre-cond: if pos == cend then p->next == NULL;
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::__hook_node_back(node_base * p) KERBAL_NOEXCEPT
		{
			node_base * prev = this->last_iter.current;
			prev->next = p;
			this->last_iter = iterator(p);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::__hook_node_front(node_base * p) KERBAL_NOEXCEPT
		{
			this->__hook_node(this->begin(), p);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::__hook_node(const_iterator pos, node_base * p) KERBAL_NOEXCEPT
		{
			if (pos != this->cend()) {
				iterator pos_mut(pos.cast_to_mutable());
				node_base * prev = pos_mut.current;
				p->next = prev->next;
				prev->next = p;
			} else {
				this->__hook_node_back(p);
			}
		}

		// pre-cond: if pos == cend then back->next == NULL;
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::__hook_node(const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
		{
			iterator pos_mut(pos.cast_to_mutable());
			node_base * prev = pos_mut.current;
			if (pos != this->cend()) {
				back->next = prev->next;
			} else {
				this->last_iter = iterator(back);
			}
			prev->next = start;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void single_list<Tp, Allocator>::__swap_with_empty(single_list& not_empty_list, single_list& empty_list) KERBAL_NOEXCEPT
		{
			empty_list.head_node.next = not_empty_list.head_node.next;
			not_empty_list.head_node.next = NULL;
			empty_list.last_iter = not_empty_list.last_iter;
			not_empty_list.last_iter = not_empty_list.begin();
		}


	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_SINGLE_LIST_IMPL_HPP
