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

#ifndef KERBAL_CONTAINER_IMPL_FORWARD_LIST_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_FORWARD_LIST_IMPL_HPP

#include <kerbal/container/forward_list.hpp>

namespace kerbal
{

	namespace container
	{

	//===================
	// construct/copy/destroy

#	if __cplusplus < 201103L

		template <typename Tp, typename Allocator>
		forward_list<Tp, Allocator>::forward_list()
				: fl_allocator_unrelated(), fl_allocator_overload()
		{
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(const Allocator& alloc)
					KERBAL_CONDITIONAL_NOEXCEPT((
							std::is_nothrow_default_constructible<fl_allocator_unrelated>::value &&
							std::is_nothrow_constructible<fl_allocator_overload, const Allocator&>::value
					))
				: fl_allocator_unrelated(), fl_allocator_overload(alloc)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(const forward_list & src)
				: fl_allocator_unrelated(), fl_allocator_overload()
		{
			this->insert_after(this->cbefore_begin(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(const forward_list & src, const Allocator& alloc)
				: fl_allocator_unrelated(), fl_allocator_overload(alloc)
		{
			this->insert_after(this->cbefore_begin(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(size_type n)
				: fl_allocator_unrelated(), fl_allocator_overload()
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n));
			this->_K_hook_node_after(this->basic_cbefore_begin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(size_type n, const Allocator& alloc)
				: fl_allocator_unrelated(), fl_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n));
			this->_K_hook_node_after(this->basic_cbefore_begin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(size_type n, const_reference val)
				: fl_allocator_unrelated(), fl_allocator_overload()
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n, val));
			this->_K_hook_node_after(this->basic_cbefore_begin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(size_type n, const_reference val, const Allocator& alloc)
				: fl_allocator_unrelated(), fl_allocator_overload(alloc)
		{
			if (n == 0) {
				return;
			}
			std::pair<node*, node*> p(this->_K_build_n_new_nodes_unguarded(this->alloc(), n, val));
			this->_K_hook_node_after(this->basic_cbefore_begin(), p.first, p.second);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type)
				: fl_allocator_unrelated(), fl_allocator_overload()
		{
			this->insert_after(this->cbefore_begin(), first, last);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(InputIterator first, InputIterator last, const Allocator& alloc,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
				>::type)
				: fl_allocator_unrelated(), fl_allocator_overload(alloc)
		{
			this->insert_after(this->cbefore_begin(), first, last);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(forward_list && src)
					KERBAL_NOEXCEPT((
						std::is_nothrow_constructible<fl_allocator_overload, node_allocator_type&&>::value
					))
				: fl_allocator_unrelated(), fl_allocator_overload(kerbal::compatibility::move(src.alloc()))
		{
			fl_type_unrelated::_K_swap_type_unrelated(src, *this);
		}


		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::_K_move_constructor_with_afforded_allocator_equal(forward_list && src) KERBAL_NOEXCEPT
		{
			fl_type_unrelated::_K_swap_type_unrelated(src, *this);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::_K_move_constructor_with_afforded_allocator_not_equal(forward_list && src)
		{
			if (src.empty()) {
				return;
			}
			std::pair<node*, node*> range(this->_K_build_new_nodes_range_unguarded_move(this->alloc(), src.begin(), src.end()));
			fl_type_unrelated::_K_hook_node_after(this->basic_cbefore_begin(), range.first, range.second);
		}

		template <typename Tp, typename Allocator>
		template <bool is_allocator_always_equal>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<!is_allocator_always_equal>::type
		forward_list<Tp, Allocator>::_K_move_constructor_with_afforded_allocator_helper(forward_list && src)
		{
			if (this->alloc() != src.alloc()) {
				this->_K_move_constructor_with_afforded_allocator_not_equal(kerbal::compatibility::move(src));
			} else {
				this->_K_move_constructor_with_afforded_allocator_equal(kerbal::compatibility::move(src));
			}
		}

		template <typename Tp, typename Allocator>
		template <bool is_allocator_always_equal>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<is_allocator_always_equal>::type
		forward_list<Tp, Allocator>::_K_move_constructor_with_afforded_allocator_helper(forward_list && src) KERBAL_NOEXCEPT
		{
			this->_K_move_constructor_with_afforded_allocator_equal(kerbal::compatibility::move(src));
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(forward_list && src, const Allocator& alloc)
				: fl_allocator_unrelated(), fl_allocator_overload(alloc)
		{
			typedef typename std::allocator_traits<node_allocator_type>::is_always_equal is_always_equal;
//			typedef typename node_allocator_traits::is_always_equal is_always_equal;
			this->_K_move_constructor_with_afforded_allocator_helper<is_always_equal::value>(kerbal::compatibility::move(src));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(std::initializer_list<value_type> src)
				: forward_list(src.begin(), src.end())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::forward_list(std::initializer_list<value_type> src, const Allocator& alloc)
				: forward_list(src.begin(), src.end(), alloc)
		{
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		forward_list<Tp, Allocator>::forward_list(const kerbal::assign::assign_list<Up> & src)
				: fl_allocator_unrelated(), fl_allocator_overload()
		{
			this->insert_after(this->cbefore_begin(), src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		template <typename Up>
		forward_list<Tp, Allocator>::forward_list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc)
				: fl_allocator_unrelated(), fl_allocator_overload(alloc)
		{
			this->insert_after(this->cbefore_begin(), src.cbegin(), src.cend());
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>::~forward_list()
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<forward_list>()->_K_consecutive_destroy_node(
								kerbal::utility::declthis<forward_list>()->alloc(),
								kerbal::utility::declthis<forward_list>()->head_node.next,
								NULL
						)) &&
						std::is_nothrow_destructible<fl_allocator_overload>::value
				)
		{
			this->_K_consecutive_destroy_node(this->alloc(), this->head_node.next, NULL);
		}


	//===================
	// assign

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		forward_list<Tp, Allocator>&
		forward_list<Tp, Allocator>::operator=(const forward_list& src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<forward_list>()->assign(src))
				)
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
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<forward_list>()->assign(src))
				)
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
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<forward_list>()->assign(src.cbegin(), src.cend()))
				)
		{
			this->assign(src.cbegin(), src.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::assign(size_type count, const_reference val)
		{
			const_iterator before_it(this->before_begin());
			iterator it(this->begin());
			const_iterator const cend(this->cend());
			while (count != 0) {
				if (it != cend) {
					kerbal::operators::generic_assign(*it, val); // *it = val;
					--count;
					before_it = it;
					++it;
				} else {
					this->insert_after(before_it, count, val);
					return;
				}
			}
			this->erase_after(before_it, cend);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		forward_list<Tp, Allocator>::assign(InputIterator first, InputIterator last)
		{
			iterator before_it(this->before_begin());
			iterator it(this->begin());
			const_iterator const cend(this->cend());
			while (first != last) {
				if (it != cend) {
					kerbal::operators::generic_assign(*it, *first); // *it = *first;
					++first;
					before_it = it;
					++it;
				} else {
					this->insert_after(before_it, first, last);
					return;
				}
			}
			this->erase_after(before_it, cend);
		}


#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::assign(forward_list&& src)
		{
			this->swap(src);
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
			this->emplace_front(val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::push_front(rvalue_reference val)
		{
			this->emplace_front(kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::reference
		forward_list<Tp, Allocator>::emplace_front(Args&& ... args)
		{
			node *p = this->_K_build_new_node(this->alloc(), kerbal::utility::forward<Args>(args)...);
			this->_K_hook_node_after(this->basic_cbefore_begin(), p);
			return p->value;
		}

#	else

		template <typename Tp, typename Allocator>
		typename forward_list<Tp, Allocator>::reference
		forward_list<Tp, Allocator>::emplace_front()
		{
			node *p = this->_K_build_new_node(this->alloc());
			this->_K_hook_node_after(this->basic_cbefore_begin(), p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename forward_list<Tp, Allocator>::reference
		forward_list<Tp, Allocator>::emplace_front(const Arg0& arg0)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0);
			this->_K_hook_node_after(this->basic_cbefore_begin(), p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename forward_list<Tp, Allocator>::reference
		forward_list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1);
			this->_K_hook_node_after(this->basic_cbefore_begin(), p);
			return p->value;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename forward_list<Tp, Allocator>::reference
		forward_list<Tp, Allocator>::emplace_front(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1, arg2);
			this->_K_hook_node_after(this->basic_cbefore_begin(), p);
			return p->value;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::insert_after(const_iterator pos, const_reference val)
		{
			return this->emplace_after(pos, val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::insert_after(const_iterator pos, size_type n, const_reference val)
		{
			if (n == 0) {
				return pos.cast_to_mutable();
			}
			std::pair<node*, node*> range(this->_K_build_n_new_nodes_unguarded(this->alloc(), n, val));
			this->_K_hook_node_after(pos, range.first, range.second);
			return iterator(range.second);
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
			if (first == last) {
				return pos.cast_to_mutable();
			}
			std::pair<node*, node*> range(this->_K_build_new_nodes_range_unguarded(this->alloc(), first, last));
			this->_K_hook_node_after(pos, range.first, range.second);
			return iterator(range.second);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::insert_after(const_iterator pos, rvalue_reference val)
		{
			return this->emplace_after(pos, kerbal::compatibility::move(val));
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
			return this->insert_after(pos, src.begin(), src.end());
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::emplace_after(const_iterator pos, Args&& ... args)
		{
			node *p = this->_K_build_new_node(this->alloc(), kerbal::utility::forward<Args>(args)...);
			this->_K_hook_node_after(pos, p);
			return iterator(p);
		}

#	else

		template <typename Tp, typename Allocator>
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::emplace_after(const_iterator pos)
		{
			node *p = this->_K_build_new_node(this->alloc());
			this->_K_hook_node_after(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::emplace_after(const_iterator pos, const Arg0& arg0)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0);
			this->_K_hook_node_after(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::emplace_after(const_iterator pos, const Arg0& arg0, const Arg1& arg1)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1);
			this->_K_hook_node_after(pos, p);
			return iterator(p);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::emplace_after(const_iterator pos, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			node *p = this->_K_build_new_node(this->alloc(), arg0, arg1, arg2);
			this->_K_hook_node_after(pos, p);
			return iterator(p);
		}

#	endif

	//===================
	// erase

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::pop_front()
		{
			this->erase_after(this->cbefore_begin());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::erase_after(const_iterator pos)
		{
			return fl_allocator_unrelated::_K_erase_after(this->alloc(), pos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::iterator
		forward_list<Tp, Allocator>::erase_after(const_iterator first, const_iterator last)
		{
			return fl_allocator_unrelated::_K_erase_after(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::clear()
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<fl_allocator_unrelated>()->_K_clear(
								kerbal::utility::declthis<forward_list>()->alloc()
						))
				)
		{
			this->fl_allocator_unrelated::_K_clear(this->alloc());
		}


	//===================
	// operation

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::resize(size_type count)
		{
			const_iterator before_it(this->before_begin());
			iterator it(this->begin());
			const_iterator const cend(this->cend());
			while (count != 0) {
				if (it != cend) {
					--count;
					before_it = it;
					++it;
				} else {
					// pre-condition: count != 0
					std::pair<node*, node*> range(this->_K_build_n_new_nodes_unguarded(this->alloc(), count));
					this->_K_hook_node_after(before_it, range.first, range.second);
					return;
				}
			}
			this->erase_after(before_it, cend);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::resize(size_type count, const_reference value)
		{
			const_iterator before_it(this->before_begin());
			iterator it(this->begin());
			const_iterator const cend(this->cend());
			while (count != 0) {
				if (it != cend) {
					--count;
					before_it = it;
					++it;
				} else {
					// pre-condition: count != 0
					std::pair<node*, node*> range(this->_K_build_n_new_nodes_unguarded(this->alloc(), count, value));
					this->_K_hook_node_after(before_it, range.first, range.second);
					return;
				}
			}
			this->erase_after(before_it, cend);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void forward_list<Tp, Allocator>::swap(forward_list & with)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(fl_allocator_overload::_K_swap_allocator_if_propagate(
								kerbal::utility::declval<fl_allocator_overload&>(), kerbal::utility::declval<fl_allocator_overload&>()
						)) &&
						noexcept(fl_type_unrelated::_K_swap_type_unrelated(
								kerbal::utility::declval<fl_type_unrelated&>(), kerbal::utility::declval<fl_type_unrelated&>()
						))
				)
		{
			fl_allocator_overload::_K_swap_allocator_if_propagate(
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
			return fl_allocator_unrelated::_K_remove_after_if(this->alloc(), first, last, predicate);
		}

		template <typename Tp, typename Allocator>
		template <typename UnaryPredicate>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::remove_if(UnaryPredicate predicate)
		{
			return this->fl_allocator_unrelated::_K_remove_if(this->alloc(), predicate);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::remove_after(const_iterator first, const_iterator last, const_reference val)
		{
			return fl_allocator_unrelated::_K_remove_after(this->alloc(), first, last, val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::remove(const_reference val)
		{
			return this->fl_allocator_unrelated::_K_remove(this->alloc(), val);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::unique(const_iterator first, const_iterator last, BinaryPredict equal_to)
		{
			return fl_allocator_unrelated::_K_unique(this->alloc(), first, last, equal_to);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::unique(const_iterator first, const_iterator last)
		{
			return fl_allocator_unrelated::_K_unique(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		template <typename BinaryPredict>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::unique(BinaryPredict equal_to)
		{
			return this->fl_allocator_unrelated::_K_unique(this->alloc(), equal_to);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename forward_list<Tp, Allocator>::size_type
		forward_list<Tp, Allocator>::unique()
		{
			return this->fl_allocator_unrelated::_K_unique(this->alloc());
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

#endif // KERBAL_CONTAINER_IMPL_FORWARD_LIST_IMPL_HPP
