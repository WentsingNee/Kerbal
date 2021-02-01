/**
 * @file       single_list_base.impl.hpp
 * @brief
 * @date       2020-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_SINGLE_LIST_BASE_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_SINGLE_LIST_BASE_IMPL_HPP

#include <kerbal/container/detail/single_list_base.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			//===================
			//capacity

			KERBAL_CONSTEXPR20
			inline
			bool sl_type_unrelated::empty() const KERBAL_NOEXCEPT
			{
				return this->basic_begin() == this->basic_end();
			}

			KERBAL_CONSTEXPR20
			inline
			sl_type_unrelated::size_type
			sl_type_unrelated::size() const KERBAL_NOEXCEPT
			{
				basic_const_iterator first(this->basic_begin());
				basic_const_iterator last(this->basic_end());
				basic_iterator::difference_type sz = 0;
				while (first != last) {
					++first;
					++sz;
				}
				return sz;
			}

			//===================
			//operation

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::iter_swap(basic_iterator a, basic_iterator b) KERBAL_NOEXCEPT
			{
				node_base * pre_a = a.current;
				node_base * pre_b = b.current;
				node_base * pa = pre_a->next;
				node_base * pb = pre_b->next;
				kerbal::algorithm::swap(pre_a->next, pre_b->next);
				kerbal::algorithm::swap(pa->next, pb->next);
				if (pa->next == NULL) {
					this->last_iter = basic_iterator(pa);
				} else if (pb->next == NULL) {
					this->last_iter = basic_iterator(pb);
				}
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::reverse(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT
			{
				if (first == last) {
					return;
				}

				basic_iterator a(first); ++a;
				basic_iterator b(a); ++b;
				basic_iterator e(last); ++e;

				if (last == this->basic_end()) {
					this->last_iter = a;
				}

				while (a != last) {
					a.current->next = e.current;
					e = a;
					a = b;
					++b;
				}
				first.current->next = a.current;
				a.current->next = e.current;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::reverse() KERBAL_NOEXCEPT
			{
				this->reverse(this->basic_begin(), this->basic_end());
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::splice(basic_const_iterator pos, sl_type_unrelated & other)
																							KERBAL_NOEXCEPT
			{
				this->splice(pos, other, other.basic_begin(), other.basic_end());
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::splice(basic_const_iterator pos, sl_type_unrelated & other, basic_const_iterator opos)
																							KERBAL_NOEXCEPT
			{
				node_base * p = other._K_unhook_node(opos.cast_to_mutable());
				p->next = NULL;
				this->_K_hook_node(pos, p);
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::splice(basic_const_iterator pos, sl_type_unrelated & other,
											basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				if (first == last) {
					return;
				}
				std::pair<node_base *, node_base *> range(other._K_unhook_node(first.cast_to_mutable(), last.cast_to_mutable()));
				node_base * start = range.first;
				node_base * back = range.second;
				back->next = NULL;
				this->_K_hook_node(pos, start, back);
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::_K_hook_node_back(node_base * p) KERBAL_NOEXCEPT
			{
				node_base * prev = this->last_iter.current;
				prev->next = p;
				this->last_iter = basic_iterator(p);
			}

			//===================
			//private

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::_K_hook_node_not_back(basic_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				node_base * prev = pos.current;
				p->next = prev->next;
				prev->next = p;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::_K_hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				if (pos_mut != this->basic_end()) {
					this->_K_hook_node_not_back(pos_mut, p);
				} else {
					this->_K_hook_node_back(p);
				}
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::_K_hook_node_back(node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				node_base * prev = this->last_iter.current;
				this->last_iter = basic_iterator(back);
				prev->next = start;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::_K_hook_node_not_back(basic_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				node_base * prev = pos.current;
				back->next = prev->next;
				prev->next = start;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::_K_hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				if (pos_mut != this->basic_end()) {
					this->_K_hook_node_not_back(pos_mut, start, back);
				} else {
					this->_K_hook_node_back(start, back);
				}
			}

			KERBAL_CONSTEXPR20
			inline
			sl_node_base *
			sl_type_unrelated::_K_unhook_node(basic_iterator pos) KERBAL_NOEXCEPT
			{
				node_base * prev = pos.current;
				node_base * p = prev->next;
				prev->next = p->next;
				if (p->next == NULL) { // is back node
					this->last_iter = pos;
				}
				return p;
			}

			// pre-cond: first != last;
			KERBAL_CONSTEXPR20
			inline
			std::pair<sl_type_unrelated::node_base *, sl_type_unrelated::node_base *>
			sl_type_unrelated::_K_unhook_node(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT
			{
				node_base * prev = first.current;
				node_base * start = prev->next;
				node_base * back = last.current;

				prev->next = back->next;

				if (back->next == NULL) {
					this->last_iter = first;
				}

				return std::pair<node_base *, node_base *>(start, back);
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::_K_swap_with_empty(sl_type_unrelated & not_empty_list, sl_type_unrelated & empty_list) KERBAL_NOEXCEPT
			{
				empty_list.head_node.next = not_empty_list.head_node.next;
				not_empty_list.head_node.next = NULL;
				empty_list.last_iter = not_empty_list.last_iter;
				not_empty_list.last_iter = not_empty_list.basic_begin();
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::_K_swap_type_unrelated(sl_type_unrelated & lhs, sl_type_unrelated & rhs) KERBAL_NOEXCEPT
			{
				bool is_rhs_empty = rhs.empty();
				if (lhs.empty()) {
					if (!is_rhs_empty) {
						// lhs.empty() && !rhs.empty()
						_K_swap_with_empty(rhs, lhs);
					}
				} else {
					if (is_rhs_empty) {
						// !lhs.empty() and rhs.empty()
						_K_swap_with_empty(lhs, rhs);
					} else {
						// !lhs.empty() and !rhs.empty()
						kerbal::algorithm::swap(lhs.head_node.next, rhs.head_node.next);
						kerbal::algorithm::swap(lhs.last_iter, rhs.last_iter);
					}
				}
			}



			//===================
			//element access

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::reference
			sl_allocator_unrelated<Tp>::front() KERBAL_NOEXCEPT
			{
				return *this->begin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::const_reference
			sl_allocator_unrelated<Tp>::front() const KERBAL_NOEXCEPT
			{
				return *this->cbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::reference
			sl_allocator_unrelated<Tp>::back() KERBAL_NOEXCEPT
			{
				return this->end().current->template reinterpret_as<Tp>().value;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::const_reference
			sl_allocator_unrelated<Tp>::back() const KERBAL_NOEXCEPT
			{
				return this->cend().current->template reinterpret_as<Tp>().value;
			}

			//===================
			//iterator

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::iterator
			sl_allocator_unrelated<Tp>::begin() KERBAL_NOEXCEPT
			{
				return iterator(&this->head_node);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::iterator
			sl_allocator_unrelated<Tp>::end() KERBAL_NOEXCEPT
			{
				return iterator(this->last_iter);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::const_iterator
			sl_allocator_unrelated<Tp>::begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->head_node);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::const_iterator
			sl_allocator_unrelated<Tp>::end() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->last_iter);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::const_iterator
			sl_allocator_unrelated<Tp>::cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->head_node);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::const_iterator
			sl_allocator_unrelated<Tp>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->last_iter);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::iterator
			sl_allocator_unrelated<Tp>::nth(size_type index) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->begin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::const_iterator
			sl_allocator_unrelated<Tp>::nth(size_type index) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->cbegin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::size_type
			sl_allocator_unrelated<Tp>::index_of(iterator it) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->begin(), it);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::size_type
			sl_allocator_unrelated<Tp>::index_of(const_iterator it) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->cbegin(), it);
			}


			//===================
			//operation

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void sl_allocator_unrelated<Tp>::iter_swap_unstable(iterator a, iterator b)
			{
				kerbal::algorithm::iter_swap(a, b);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void sl_allocator_unrelated<Tp>::iter_swap(iterator a, iterator b) KERBAL_NOEXCEPT
			{
				detail::sl_type_unrelated::iter_swap(a, b);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void sl_allocator_unrelated<Tp>::iter_swap_fast(iterator a, iterator b)
			{

#		if __cplusplus >= 201103L

				struct policy
						: kerbal::type_traits::bool_constant<
								std::is_trivially_copy_constructible<Tp>::value &&
								std::is_trivially_copy_assignable<Tp>::value
						>
				{
				};

#		else

				struct policy
						: kerbal::type_traits::is_fundamental<Tp>
				{
				};

#		endif

				struct apply_helper
				{
						KERBAL_CONSTEXPR20
						static void apply(sl_allocator_unrelated & l, iterator a, iterator b, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
						{
							l.iter_swap(a, b);
						}

						KERBAL_CONSTEXPR20
						static void apply(sl_allocator_unrelated & l, iterator a, iterator b, kerbal::type_traits::true_type)
						{
							l.iter_swap_unstable(a, b);
						}
				};

				apply_helper::apply(*this, a, b, policy());

			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void sl_allocator_unrelated<Tp>::reverse(iterator first, iterator last) KERBAL_NOEXCEPT
			{
				sl_type_unrelated::reverse(first, last);
			}

#	if __cplusplus >= 201103L

#		if __cpp_exceptions

			template <typename Tp>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					!nothrow_while_construct,
					typename sl_allocator_unrelated<Tp>::node*
			>::type
			sl_allocator_unrelated<Tp>::_K_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate(alloc, 1);
				try {
					node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				} catch (...) {
					node_allocator_traits::deallocate(alloc, p, 1);
					throw;
				}
				return p;
			}

			template <typename Tp>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					nothrow_while_construct,
					typename sl_allocator_unrelated<Tp>::node*
			>::type
			sl_allocator_unrelated<Tp>::_K_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::allocator_traits<NodeAllocator>::allocate(alloc, 1))
					)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate(alloc, 1);
				node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				return p;
			}

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::node*
			sl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef
				kerbal::type_traits::conditional_boolean<
						noexcept(
								node_allocator_traits::construct(
										alloc, kerbal::utility::declval<node*>(),
										kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...
								)
						)
				> nothrow_while_construct;

				return _K_build_new_node_impl<nothrow_while_construct::value>(alloc, kerbal::utility::forward<Args>(args)...);
			}

#		else // __cpp_exceptions

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename sl_allocator_unrelated<Tp>::node*
			sl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate(alloc, 1);
				node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				return p;
			}

#		endif // __cpp_exceptions

#	else // __cplusplus >= 201103L

#		if __cpp_exceptions

#	define _K_build_new_node_body(args...) \
		{ \
			typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
			node * p = node_allocator_traits::allocate(alloc, 1); \
			try { \
				node_allocator_traits::construct(alloc, p, args); \
			} catch (...) { \
				node_allocator_traits::deallocate(alloc, p, 1); \
				throw; \
			} \
			return p; \
		}

#		else

#	define _K_build_new_node_body(args...) \
		{ \
			typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
			node * p = node_allocator_traits::allocate(alloc, 1); \
			node_allocator_traits::construct(alloc, p, args); \
			return p; \
		}

#		endif // __cpp_exceptions


			template <typename Tp>
			template <typename NodeAllocator>
			typename sl_allocator_unrelated<Tp>::node*
			sl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc)
			{
				_K_build_new_node_body(kerbal::utility::in_place_t());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0>
			typename sl_allocator_unrelated<Tp>::node*
			sl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0)
			{
				_K_build_new_node_body(kerbal::utility::in_place_t(), arg0);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1>
			typename sl_allocator_unrelated<Tp>::node*
			sl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0, const Arg1 & arg1)
			{
				_K_build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
			typename sl_allocator_unrelated<Tp>::node*
			sl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
			{
				_K_build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1, arg2);
			}

#	undef _K_build_new_node_body

#	endif // __cplusplus >= 201103L


#	if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator, typename... Args>
			KERBAL_CONSTEXPR20
			std::pair<typename sl_allocator_unrelated<Tp>::node*, typename sl_allocator_unrelated<Tp>::node*>
			sl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, Args&& ... args)
			{
				size_t cnt = 0;
				node * const start = _K_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				node * back = start;
#		if __cpp_exceptions
				try {
#		endif // __cpp_exceptions
					++cnt;
					while (cnt != n) {
						node * new_node = _K_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
						back->next = new_node;
						back = new_node;
						++cnt;
					}
					return std::pair<node*, node*>(start, back);
#		if __cpp_exceptions
				} catch (...) {
					_K_consecutive_destroy_node(alloc, start);
					throw;
				}
#		endif // __cpp_exceptions
			}

#	else


#if __cpp_exceptions

// args = {alloc, arg0, arg1...}
#	define _K_build_n_new_nodes_unguarded_body(args...) \
		{ \
			size_t cnt = 0; \
			node * const start = _K_build_new_node(args); \
			node * back = start; \
			try { \
				++cnt; \
				while (cnt != n) { \
					node * new_node = _K_build_new_node(args); \
					back->next = new_node; \
					back = new_node; \
					++cnt; \
				} \
				return std::pair<node*, node*>(start, back); \
			} catch (...) { \
				_K_consecutive_destroy_node(alloc, start); \
				throw; \
			} \
		}

#else

// args = {alloc, arg0, arg1...}
#	define _K_build_n_new_nodes_unguarded_body(args...) \
		{ \
			size_t cnt = 0; \
			node * const start = _K_build_new_node(args); \
			node * back = start; \
			++cnt; \
			while (cnt != n) { \
				node* new_node = _K_build_new_node(args); \
				back->next = new_node; \
				back = new_node; \
				++cnt; \
			} \
			return std::pair<node*, node*>(start, back); \
		}

#endif


			template <typename Tp>
			template <typename NodeAllocator>
			std::pair<typename sl_allocator_unrelated<Tp>::node*, typename sl_allocator_unrelated<Tp>::node*>
			sl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n)
			{
				_K_build_n_new_nodes_unguarded_body(alloc);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0>
			std::pair<typename sl_allocator_unrelated<Tp>::node*, typename sl_allocator_unrelated<Tp>::node*>
			sl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0)
			{
				_K_build_n_new_nodes_unguarded_body(alloc, arg0);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1>
			std::pair<typename sl_allocator_unrelated<Tp>::node*, typename sl_allocator_unrelated<Tp>::node*>
			sl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0, const Arg1 & arg1)
			{
				_K_build_n_new_nodes_unguarded_body(alloc, arg0, arg1);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
			std::pair<typename sl_allocator_unrelated<Tp>::node*, typename sl_allocator_unrelated<Tp>::node*>
			sl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
			{
				_K_build_n_new_nodes_unguarded_body(alloc, arg0, arg1, arg2);
			}

#	undef _K_build_n_new_nodes_unguarded_body

#	endif


			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					std::pair<typename sl_allocator_unrelated<Tp>::node*, typename sl_allocator_unrelated<Tp>::node*>
			>::type
			sl_allocator_unrelated<Tp>::_K_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last)
			{
				node * const start = _K_build_new_node(alloc, *first);
				node * back = start;
#			if __cpp_exceptions
				try {
#			endif // __cpp_exceptions
					++first;
					while (first != last) {
						node* new_node = _K_build_new_node(alloc, *first);
						back->next = new_node;
						back = new_node;
						++first;
					}
					return std::pair<node*, node*>(start, back);
#			if __cpp_exceptions
				} catch (...) {
					_K_consecutive_destroy_node(alloc, start);
					throw;
				}
#			endif // __cpp_exceptions
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			std::pair<typename sl_allocator_unrelated<Tp>::node*, typename sl_allocator_unrelated<Tp>::node*>
			sl_allocator_unrelated<Tp>::_K_build_new_nodes_range_unguarded_move(NodeAllocator & alloc, iterator first, iterator last)
			{
				node * const start = _K_build_new_node(alloc, kerbal::compatibility::move(*first));
				node * back = start;
#			if __cpp_exceptions
				try {
#			endif // __cpp_exceptions
					++first;
					while (first != last) {
						node* new_node = _K_build_new_node(alloc, kerbal::compatibility::move(*first));
						back->next = new_node;
						back = new_node;
						++first;
					}
					return std::pair<node*, node*>(start, back);
#			if __cpp_exceptions
				} catch (...) {
					_K_consecutive_destroy_node(alloc, start);
					throw;
				}
#			endif // __cpp_exceptions
			}

#		endif


			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_allocator_unrelated<Tp>::_K_destroy_node(NodeAllocator & alloc, node_base* p_node_base)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::allocator_traits<NodeAllocator>::destroy(alloc, kerbal::utility::declval<node*>())) &&
							noexcept(kerbal::memory::allocator_traits<NodeAllocator>::deallocate(alloc, kerbal::utility::declval<node*>(), 1))
					)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p_node = &p_node_base->template reinterpret_as<Tp>();
				node_allocator_traits::destroy(alloc, p_node);
				node_allocator_traits::deallocate(alloc, p_node, 1);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_allocator_unrelated<Tp>::_K_consecutive_destroy_node(NodeAllocator & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<sl_allocator_unrelated>()->_K_destroy_node(alloc, kerbal::utility::declval<node_base *>()))
					)
			{
				node_base * current_node_base = start;
				while (current_node_base != NULL) {
					node_base * next = current_node_base->next;
					_K_destroy_node(alloc, current_node_base);
					current_node_base = next;
				}
			}

#		if __cplusplus >= 201703L
#			if __has_include(<memory_resource>)

			template <typename Tp>
			template <typename Node>
			KERBAL_CONSTEXPR20
			void sl_allocator_unrelated<Tp>::_K_consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<sl_allocator_unrelated>()->_K_destroy_node(alloc, kerbal::utility::declval<node_base *>()))
					)
			{
				if (typeid(*alloc.resource()) == typeid(std::pmr::monotonic_buffer_resource)) {
					if constexpr (!std::is_trivially_destructible<Tp>::value) {
						typedef kerbal::memory::allocator_traits<std::pmr::polymorphic_allocator<Node> > node_allocator_traits;

						node_base * current_node_base = start;
						while (current_node_base != NULL) {
							node_base * next = current_node_base->next;
							node * p_node = &current_node_base->template reinterpret_as<Tp>();
							node_allocator_traits::destroy(alloc, p_node);
							current_node_base = next;
						}
					}
				} else {
					node_base * current_node_base = start;
					while (current_node_base != NULL) {
						node_base * next = current_node_base->next;
						_K_destroy_node(alloc, current_node_base);
						current_node_base = next;
					}
				}
			}

#			endif
#		endif

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_IMPL_SINGLE_LIST_BASE_IMPL_HPP
