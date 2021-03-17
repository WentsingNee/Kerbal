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

#include <kerbal/container/list.hpp>

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
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n));
			list_type_unrelated::_K_hook_node(this->cend(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const Allocator& alloc)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n));
			list_type_unrelated::_K_hook_node(this->cend(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const_reference val)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload()
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n, val));
			list_type_unrelated::_K_hook_node(this->cend(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator>::list(size_type n, const_reference val, const Allocator& alloc)
				: list_allocator_unrelated(detail::init_list_node_ptr_to_self_tag()), list_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n, val));
			list_type_unrelated::_K_hook_node(this->cend(), p.first, p.second);
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
				list_type_unrelated::_K_swap_with_empty(src, *this);
			}
		}


		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::move_constructor_with_afforded_allocator_allocator_equal(list && src) KERBAL_NOEXCEPT
		{
			list_type_unrelated::_K_swap_with_empty(src, *this);
		}

		// pre-condition: src.empty() == true
		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::move_constructor_with_afforded_allocator_allocator_not_equal(list && src)
		{
			std::pair<node*, node*> range(this->_K_build_new_nodes_range_unguarded_move(this->alloc(), src.begin(), src.end()));
			list_type_unrelated::_K_hook_node(this->cend(), range.first, range.second);
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
						noexcept(kerbal::utility::declthis<list>()->_K_consecutive_destroy_node(
								kerbal::utility::declthis<list>()->alloc(),
								kerbal::utility::declthis<list>()->head_node.next
						)) &&
						std::is_nothrow_destructible<list_allocator_overload>::value
				)
		{
			if (this->empty()) {
				return;
			}
			this->head_node.prev->next = NULL;
			this->_K_consecutive_destroy_node(this->alloc(), this->head_node.next);
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
			return *this->emplace(this->cbegin(), kerbal::utility::forward<Args>(args)...);
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
			return *this->emplace(this->cend(), kerbal::utility::forward<Args>(args)...);
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
			std::pair<node*, node*> range(this->_K_build_n_new_nodes_unguarded(this->alloc(), n, val));
			list_type_unrelated::_K_hook_node(pos, range.first, range.second);
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
			std::pair<node*, node*> range(this->_K_build_new_nodes_range_unguarded(this->alloc(), first, last));
			list_type_unrelated::_K_hook_node(pos, range.first, range.second);
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
			node *p = this->_K_build_new_node(this->alloc(), kerbal::utility::forward<Args>(args)...);
			list_type_unrelated::_K_hook_node(pos, p);
			return iterator(p);
		}

#	else

		template <typename Tp, typename Allocator>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos)
		{
			node *p = this->_K_build_new_node(this->alloc());
			list_type_unrelated::_K_hook_node(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0);
			list_type_unrelated::_K_hook_node(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1);
			list_type_unrelated::_K_hook_node(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1, arg2);
			list_type_unrelated::_K_hook_node(pos, p);
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
			return list_allocator_unrelated::_K_erase(this->alloc(), pos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::iterator
		list<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			return list_allocator_unrelated::_K_erase(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::clear()
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->erase(
								kerbal::utility::declthis<list>()->cbegin(), kerbal::utility::declthis<list>()->cend()
						))
				)
		{
			this->erase(this->cbegin(), this->cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::resize(size_type count)
		{
			const_iterator it(this->cbegin());
			const_iterator const cend(this->cend());
			size_type size(kerbal::iterator::advance_at_most(it, count, cend));
			if (size == count) {
				this->erase(it, cend);
			} else {
				// note: count - size != 0
				std::pair<node*, node*> range(this->_K_build_n_new_nodes_unguarded(this->alloc(), count - size));
				list_type_unrelated::_K_hook_node(cend, range.first, range.second);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::resize(size_type count, const_reference value)
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
		void list<Tp, Allocator>::swap(list& ano)
		{
			this->list_allocator_overload::swap_allocator_if_propagate(ano);

			list_type_unrelated::_K_swap_type_unrelated(*this, ano);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::iter_swap_unstable(const_iterator a, const_iterator b)
		{
			list_allocator_unrelated::_K_iter_swap_unstable(a, b);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::iter_swap(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
		{
			list_allocator_unrelated::_K_iter_swap(a, b);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::iter_swap_fast(const_iterator a, const_iterator b)
		{
			list_allocator_unrelated::_K_iter_swap_fast(a, b);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::reverse_unstable(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
		{
			list_allocator_unrelated::_K_reverse_unstable(a, b);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::reverse(const_iterator a, const_iterator b)
		{
			list_allocator_unrelated::_K_reverse(a, b);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::reverse_fast(const_iterator a, const_iterator b)
		{
			list_allocator_unrelated::_K_reverse_fast(a, b);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::merge(list & other, BinaryPredict cmp)
		{
			list_allocator_unrelated::_K_merge(static_cast<list_allocator_unrelated&>(other), cmp);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::merge(list & other)
		{
			list_allocator_unrelated::_K_merge(static_cast<list_allocator_unrelated&>(other));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove(const_reference val)
		{
			return list_allocator_unrelated::_K_remove(this->alloc(), val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove(const_iterator first, const_iterator last, const_reference val)
		{
			return list_allocator_unrelated::_K_remove(this->alloc(), first, last, val);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove_if(UnaryPredicate predicate)
		{
			return list_allocator_unrelated::_K_remove_if(this->alloc(), predicate);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::remove_if(const_iterator first, const_iterator last, UnaryPredicate predicate)
		{
			return list_allocator_unrelated::_K_remove_if(this->alloc(), first, last, predicate);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::unique()
		{
			return list_allocator_unrelated::_K_unique(this->alloc());
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredicate>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::unique(BinaryPredicate pred)
		{
			return list_allocator_unrelated::_K_unique(this->alloc(), pred);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::unique(const_iterator first, const_iterator last)
		{
			return list_allocator_unrelated::_K_unique(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredicate>
		KERBAL_CONSTEXPR20
		typename list<Tp, Allocator>::size_type
		list<Tp, Allocator>::unique(const_iterator first, const_iterator last, BinaryPredicate pred)
		{
			return list_allocator_unrelated::_K_unique(this->alloc(), first, last, pred);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list & other) KERBAL_NOEXCEPT
		{
			list_type_unrelated::_K_splice(pos, other);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list &, const_iterator opos) KERBAL_NOEXCEPT
		{
			list_type_unrelated::_K_splice(pos, opos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list &, const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			list_type_unrelated::_K_splice(pos, first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void list<Tp, Allocator>::splice(const_iterator pos, list&& other) KERBAL_NOEXCEPT
		{
			list_type_unrelated::_K_splice(pos, other);
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
