/**
 * @file       list_base.impl.hpp
 * @brief
 * @date       2020-08-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_BASE_IMPL_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compare/std_compare/std_compare.fwd.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/iterator/move_iterator.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if !KERBAL_HAS_EXCEPTIONS_SUPPORT
#	include <kerbal/memory/bad_alloc.hpp>
#	include <kerbal/utility/throw_this_exception.hpp>
#endif

#include <climits> // CHAR_BIT
#include <cstddef> // std::size_t

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <kerbal/type_traits/is_trivially_destructible.hpp>
#		include <memory_resource>
#	endif
#endif

#include <kerbal/container/detail/list_base/list_base.decl.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

		//===================
		//===================
		// list_type_unrelated

		//===================
		// capacity

			KERBAL_CONSTEXPR14
			inline
			bool list_type_unrelated::empty() const KERBAL_NOEXCEPT
			{
				return this->basic_begin() == this->basic_end();
			}

			KERBAL_CONSTEXPR14
			inline
			list_type_unrelated::size_type
			list_type_unrelated::size() const KERBAL_NOEXCEPT
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
		// operation

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_iter_swap(basic_const_iterator a, basic_const_iterator b) KERBAL_NOEXCEPT
			{
				node_base * pa = a.cast_to_mutable().current;
				node_base * pb = b.cast_to_mutable().current;
				kerbal::algorithm::swap(pa->prev, pb->prev);
				kerbal::algorithm::swap(pa->prev->next, pb->prev->next);
				kerbal::algorithm::swap(pa->next, pb->next);
				kerbal::algorithm::swap(pa->next->prev, pb->next->prev);
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_reverse(basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				basic_iterator first_mut(first.cast_to_mutable());
				basic_iterator last_mut(last.cast_to_mutable());
				node_base * before_first = first_mut.current->prev;
				node_base * rit = last_mut.current;
				while (first_mut != last_mut) {
					node_base * p = first_mut.current;
					++first_mut;
					p->next = rit;
					rit->prev = p;
					rit = p;
				}
				rit->prev = before_first;
				before_first->next = rit;
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::reverse() KERBAL_NOEXCEPT
			{
				k_reverse(this->basic_cbegin(), this->basic_cend());
			}

			KERBAL_CONSTEXPR14
			inline
			list_type_unrelated::basic_iterator
			list_type_unrelated::k_rotate(basic_const_iterator first, basic_const_iterator n_first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				basic_iterator first_mut(first.cast_to_mutable());
				basic_iterator n_first_mut(n_first.cast_to_mutable());
				basic_iterator last_mut(last.cast_to_mutable());

				if (first == n_first) {
					return last_mut;
				}

				if (n_first == last) {
					return first_mut;
				}

				list_node_base_chain chain(k_unhook_node(first_mut, n_first_mut));
				k_hook_node(last_mut, chain.start, chain.back);
				return first_mut;
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_splice(basic_const_iterator pos, list_type_unrelated & other) KERBAL_NOEXCEPT
			{
				list_type_unrelated::k_splice(pos, other.basic_begin(), other.basic_end());
			}

#		if __cplusplus >= 201103L

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_splice(basic_const_iterator pos, list_type_unrelated && other) KERBAL_NOEXCEPT
			{
				list_type_unrelated::k_splice(pos, other.basic_begin(), other.basic_end());
			}

#		endif

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_splice(basic_const_iterator pos, basic_const_iterator opos) KERBAL_NOEXCEPT
			{
				basic_iterator opos_mut(opos.cast_to_mutable());
				node_base * p = list_type_unrelated::k_unhook_node(opos_mut);
				list_type_unrelated::k_hook_node(pos, p);
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_splice(basic_const_iterator pos, basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				if (first == last) {
					return;
				}

				list_node_base_chain chain(list_type_unrelated::k_unhook_node(first.cast_to_mutable(), last.cast_to_mutable()));
				list_type_unrelated::k_hook_node(pos, chain.start, chain.back);
			}


		//===================
		// private

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				node_base * next = pos_mut.current;
				p->prev = next->prev;
				p->next = next;
				next->prev->next = p;
				next->prev = p;
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				// (?, ?)
				// (?, 1) (0, 2) (1, 3) (2, ?)
				basic_iterator pos_mut(pos.cast_to_mutable());
				node_base * next = pos_mut.current;
				start->prev = next->prev;
				back->next = next;
				start->prev->next = start;
				next->prev = back;
			}

			KERBAL_CONSTEXPR14
			inline
			list_type_unrelated::node_base *
			list_type_unrelated::k_unhook_node(basic_iterator pos) KERBAL_NOEXCEPT
			{
				node_base * p = pos.current;
				p->prev->next = p->next;
				p->next->prev = p->prev;
				return p;
			}

			KERBAL_CONSTEXPR14
			inline
			list_node_base_chain
			list_type_unrelated::k_unhook_node(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT
			{
				node_base * start = first.current;
				node_base * prev = start->prev;
				node_base * end = last.current;
				node_base * back = end->prev;
				end->prev = prev;
				prev->next = end;
				return list_node_base_chain(start, back);
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_swap_with_empty(list_type_unrelated& not_empty_list, list_type_unrelated& empty_list) KERBAL_NOEXCEPT
			{
				empty_list.k_head.prev = not_empty_list.k_head.prev;
				empty_list.k_head.prev->next = &empty_list.k_head;
				empty_list.k_head.next = not_empty_list.k_head.next;
				empty_list.k_head.next->prev = &empty_list.k_head;
				not_empty_list.k_init_node_base();
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::k_swap_type_unrelated(list_type_unrelated & lhs, list_type_unrelated & rhs) KERBAL_NOEXCEPT
			{
				bool is_rhs_empty = rhs.empty();
				if (lhs.empty()) {
					if (!is_rhs_empty) {
						// lhs.empty() && !rhs.empty()
						k_swap_with_empty(rhs, lhs);
					}
				} else {
					if (is_rhs_empty) {
						// !lhs.empty() and rhs.empty()
						k_swap_with_empty(lhs, rhs);
					} else {
						// !lhs.empty() and !rhs.empty()
						kerbal::algorithm::swap(lhs.k_head.prev, rhs.k_head.prev);
						lhs.k_head.prev->next = &lhs.k_head;
						rhs.k_head.prev->next = &rhs.k_head;

						kerbal::algorithm::swap(lhs.k_head.next, rhs.k_head.next);
						lhs.k_head.next->prev = &lhs.k_head;
						rhs.k_head.next->prev = &rhs.k_head;
					}
				}
			}


		//===================
		//===================
		// list_type_only

		//===================
		// construct/copy/destroy

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			list_type_only<T>::list_type_only(NodeAllocator & alloc, size_type n) :
					super(init_list_node_ptr_to_self_tag())
			{
				if (n == 0) {
					return;
				}
				list_node_chain<T> chain(this->k_build_n_new_nodes_unguarded(alloc, n));
				list_type_unrelated::k_hook_node(this->cend(), chain.start, chain.back);
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			list_type_only<T>::list_type_only(NodeAllocator & alloc, size_type n, const_reference val) :
					super(init_list_node_ptr_to_self_tag())
			{
				if (n == 0) {
					return;
				}
				list_node_chain<T> chain(this->k_build_n_new_nodes_unguarded(alloc, n, val));
				list_type_unrelated::k_hook_node(this->cend(), chain.start, chain.back);
			}

			template <typename T>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			list_type_only<T>::list_type_only(NodeAllocator & alloc, InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
					>::type) :
					super(init_list_node_ptr_to_self_tag())
			{
				k_insert_using_allocator(alloc, this->cend(), first, last);
			}

#		if __cplusplus >= 201103L

			template <typename T>
			KERBAL_CONSTEXPR14
			list_type_only<T>::list_type_only(list_type_only && src) KERBAL_NOEXCEPT :
					super(detail::init_list_node_ptr_to_self_tag())
			{
				if (src.empty()) {
					return;
				}
				list_type_unrelated::k_swap_with_empty(
						static_cast<list_type_unrelated &>(src),
						static_cast<list_type_unrelated &>(*this));
			}

			// move construct using allocator, allocator is equal
			template <typename T>
			KERBAL_CONSTEXPR14
			void list_type_only<T>::k_move_cnstrct_ua_ae(list_type_only && src) KERBAL_NOEXCEPT
			{
				if (src.empty()) {
					return;
				}
				list_type_unrelated::k_swap_with_empty(
						static_cast<list_type_unrelated &>(src),
						static_cast<list_type_unrelated &>(*this));
			}

			// move construct using allocator, allocator is not equal
			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_move_cnstrct_ua_ane(NodeAllocator & this_alloc, list_type_only && src)
			{
				if (src.empty()) {
					return;
				}
				list_node_chain<T> chain(
						k_build_new_nodes_range_unguarded(
								this_alloc,
								kerbal::iterator::make_move_iterator(src.begin()),
								kerbal::iterator::make_move_iterator(src.end())));
				list_type_unrelated::k_hook_node(this->cend(), chain.start, chain.back);
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_move_cnstrct_ua_helper(NodeAllocator & this_alloc, NodeAllocator && src_alloc, list_type_only && src,
																		 kerbal::type_traits::false_type /*is_always_equal*/)
			{
				if (this_alloc != src_alloc) {
					this->k_move_cnstrct_ua_ane(this_alloc, kerbal::compatibility::move(src));
				} else {
					this->k_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
				}
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR14
			void list_type_only<T>::k_move_cnstrct_ua_helper(NodeAllocator & /*this_alloc*/, NodeAllocator && /*src_alloc*/, list_type_only && src,
																		 kerbal::type_traits::true_type /*is_always_equal*/) KERBAL_NOEXCEPT
			{
				this->k_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR14
			list_type_only<T>::list_type_only(NodeAllocator & this_alloc, NodeAllocator && src_alloc, list_type_only && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_constructible_using_allocator<NodeAllocator>::value) :
					super(init_list_node_ptr_to_self_tag())
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> allocator_traits;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				this->k_move_cnstrct_ua_helper(this_alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src), is_always_equal());
			}

#		endif

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_destroy_using_allocator(NodeAllocator & alloc) KERBAL_NOEXCEPT
			{
				if (this->empty()) {
					return;
				}
				this->k_head.prev->next = NULL;
				this->k_consecutive_destroy_node(alloc, this->k_head.next);
			}


		//===================
		// assign

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_assign_using_allocator(NodeAllocator & alloc, size_type count, const_reference val)
			{
				iterator it(this->begin());
				const_iterator const end(this->cend());
				while (count != 0) {
					if (it != end) {
						kerbal::assign::generic_assign(*it, val); // *it = val;
						--count;
						++it;
					} else {
						k_insert_using_allocator(alloc, end, count, val);
						return;
					}
				}
				k_erase_using_allocator(alloc, it, end);
			}

			template <typename T>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
			>::type
			list_type_only<T>::k_assign_using_allocator(NodeAllocator & alloc, InputIterator first, InputIterator last)
			{
				iterator it(this->begin());
				const_iterator const end(this->cend());
				while (first != last) {
					if (it != end) {
						kerbal::assign::generic_assign(*it, *first); // *it = *first;
						++first;
						++it;
					} else {
						k_insert_using_allocator(alloc, end, first, last);
						return;
					}
				}
				k_erase_using_allocator(alloc, it, end);
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & src_alloc, const list_type_only & src, CPYASS_VER_NOT_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_destroy_using_allocator(alloc);
					this->list_type_unrelated::k_init_node_base();
				}
				this->k_assign_using_allocator(alloc, src.cbegin(), src.cend());
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & src_alloc, const list_type_only & src, CPYASS_VER_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_destroy_using_allocator(alloc);
					this->list_type_unrelated::k_init_node_base();
				}
				alloc = src_alloc;
				this->k_assign_using_allocator(alloc, src.cbegin(), src.cend());
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & /*src_alloc*/, const list_type_only & src, CPYASS_VER_ALWAYS_EQUAL)
			{
				this->k_assign_using_allocator(alloc, src.cbegin(), src.cend());
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_assign_using_allocator(NodeAllocator & alloc, const NodeAllocator & src_alloc, const list_type_only & src)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> allocator_traits;
				typedef typename allocator_traits::propagate_on_container_copy_assignment propagate;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				typedef typename kerbal::type_traits::conditional<
						is_always_equal::value,
						CPYASS_VER_ALWAYS_EQUAL,
						typename kerbal::type_traits::conditional<
								propagate::value,
								CPYASS_VER_PROPAGATE,
								CPYASS_VER_NOT_PROPAGATE
						>::type
				>::type VER;

				this->k_cpy_ass_ua_impl(alloc, src_alloc, src, VER());
			}


#		if __cplusplus >= 201103L

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_move_assign(NodeAllocator & alloc, list_type_only && src) KERBAL_NOEXCEPT
			{
				this->k_destroy_using_allocator(alloc);
				this->list_type_unrelated::k_init_node_base();
				if (!src.empty()) {
					list_type_unrelated::k_swap_with_empty(static_cast<list_type_unrelated &>(src), static_cast<list_type_unrelated &>(*this));
				}
			}

			// move assign using allocator, allocator is equal
			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_mov_ass_ua_ae(NodeAllocator & alloc, list_type_only && src) KERBAL_NOEXCEPT
			{
				this->k_move_assign(alloc, kerbal::compatibility::move(src));
			}

			// move assign using allocator, allocator is not equal
			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_mov_ass_ua_ane(NodeAllocator & alloc, list_type_only && src)
			{
				this->k_assign_using_allocator(
						alloc,
						kerbal::iterator::make_move_iterator(src.begin()),
						kerbal::iterator::make_move_iterator(src.end()));
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && src_alloc, list_type_only && src,
																  MOVASS_VER_NOT_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_mov_ass_ua_ane(alloc, kerbal::compatibility::move(src));
				} else {
					this->k_mov_ass_ua_ae(alloc, kerbal::compatibility::move(src));
				}
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && src_alloc, list_type_only && src,
																  MOVASS_VER_PROPAGATE)
			{
				this->k_destroy_using_allocator(alloc);
				this->list_type_unrelated::k_init_node_base();
				alloc = kerbal::compatibility::move(src_alloc);
				if (!src.empty()) {
					list_type_unrelated::k_swap_with_empty(static_cast<list_type_unrelated &>(src), static_cast<list_type_unrelated &>(*this));
				}
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && /*src_alloc*/, list_type_only && src,
																  MOVASS_VER_ALWAYS_EQUAL) KERBAL_NOEXCEPT
			{
				this->k_mov_ass_ua_ae(alloc, kerbal::compatibility::move(src));
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_assign_using_allocator(NodeAllocator & alloc, NodeAllocator && src_alloc, list_type_only && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_assign_using_allocator<NodeAllocator>::value)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> allocator_traits;
				typedef typename allocator_traits::propagate_on_container_move_assignment propagate;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				typedef typename kerbal::type_traits::conditional<
						is_always_equal::value,
						MOVASS_VER_ALWAYS_EQUAL,
						typename kerbal::type_traits::conditional<
								propagate::value,
								MOVASS_VER_PROPAGATE,
								MOVASS_VER_NOT_PROPAGATE
						>::type
				>::type VER;

				this->k_mov_ass_ua_impl(
						alloc,
						kerbal::compatibility::move(src_alloc),
						kerbal::compatibility::move(src),
						VER()
				);
			}

#		endif


		//===================
		// element access

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::reference
			list_type_only<T>::front() KERBAL_NOEXCEPT
			{
				return node::reinterpret_as(this->k_head.next)->member();
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_reference
			list_type_only<T>::front() const KERBAL_NOEXCEPT
			{
				return node::reinterpret_as(this->k_head.next)->member();
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::reference
			list_type_only<T>::back() KERBAL_NOEXCEPT
			{
				return node::reinterpret_as(this->k_head.prev)->member();
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_reference
			list_type_only<T>::back() const KERBAL_NOEXCEPT
			{
				return node::reinterpret_as(this->k_head.prev)->member();
			}


		//===================
		// iterator

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::begin() KERBAL_NOEXCEPT
			{
				return iterator(this->k_head.next);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_iterator
			list_type_only<T>::begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_head.next);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_iterator
			list_type_only<T>::cbegin() const KERBAL_NOEXCEPT
			{
				return this->begin();
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::end() KERBAL_NOEXCEPT
			{
				return iterator(&this->k_head);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_iterator
			list_type_only<T>::end() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->k_head);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_iterator
			list_type_only<T>::cend() const KERBAL_NOEXCEPT
			{
				return this->end();
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::reverse_iterator
			list_type_only<T>::rbegin() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->end());
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_reverse_iterator
			list_type_only<T>::rbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->end());
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_reverse_iterator
			list_type_only<T>::crbegin() const KERBAL_NOEXCEPT
			{
				return this->rbegin();
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::reverse_iterator
			list_type_only<T>::rend() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->begin());
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_reverse_iterator
			list_type_only<T>::rend() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->begin());
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_reverse_iterator
			list_type_only<T>::crend() const KERBAL_NOEXCEPT
			{
				return this->rend();
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::nth(size_type index) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->begin(), index);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_iterator
			list_type_only<T>::nth(size_type index) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->cbegin(), index);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::index_of(iterator it) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->begin(), it);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::index_of(const_iterator it) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->cbegin(), it);
			}


		//===================
		// insert

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_push_front_using_allocator(NodeAllocator & alloc, const_reference val)
			{
				this->k_emplace_front_using_allocator(alloc, val);
			}

#		if __cplusplus >= 201103L

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_push_front_using_allocator(NodeAllocator & alloc, rvalue_reference val)
			{
				this->k_emplace_front_using_allocator(alloc, kerbal::compatibility::move(val));
			}

#		endif

#		if __cplusplus >= 201103L

			template <typename T>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::reference
			list_type_only<T>::k_emplace_front_using_allocator(NodeAllocator & alloc, Args&& ... args)
			{
				return *k_emplace_using_allocator(alloc, this->cbegin(), kerbal::utility::forward<Args>(args)...);
			}

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename T> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename list_type_only<T>::reference \
			list_type_only<T>::k_emplace_front_using_allocator(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				return *k_emplace_using_allocator(alloc, this->cbegin() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
			}

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#		endif

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_push_back_using_allocator(NodeAllocator & alloc, const_reference val)
			{
				this->k_emplace_back_using_allocator(alloc, val);
			}

#		if __cplusplus >= 201103L

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_push_back_using_allocator(NodeAllocator & alloc, rvalue_reference val)
			{
				this->k_emplace_back_using_allocator(alloc, kerbal::compatibility::move(val));
			}

#		endif

#		if __cplusplus >= 201103L

			template <typename T>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::reference
			list_type_only<T>::k_emplace_back_using_allocator(NodeAllocator & alloc, Args&& ... args)
			{
				return *k_emplace_using_allocator(alloc, this->cend(), kerbal::utility::forward<Args>(args)...);
			}

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename T> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename list_type_only<T>::reference \
			list_type_only<T>::k_emplace_back_using_allocator(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				return *k_emplace_using_allocator(alloc, this->cend() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
			}

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#		endif

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::k_insert_using_allocator(NodeAllocator & alloc, const_iterator pos, const_reference val)
			{
				return k_emplace_using_allocator(alloc, pos, val);
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::k_insert_using_allocator(NodeAllocator & alloc, const_iterator pos, size_type n, const_reference val)
			{
				if (n == 0) {
					return pos.cast_to_mutable();
				}
				list_node_chain<T> chain(k_build_n_new_nodes_unguarded(alloc, n, val));
				list_type_unrelated::k_hook_node(pos, chain.start, chain.back);
				return iterator(chain.start);
			}

			template <typename T>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					typename list_type_only<T>::iterator
			>::type
			list_type_only<T>::k_insert_using_allocator(NodeAllocator & alloc, const_iterator pos, InputIterator first, InputIterator last)
			{
				if (first == last) {
					return pos.cast_to_mutable();
				}
				list_node_chain<T> chain(k_build_new_nodes_range_unguarded(alloc, first, last));
				list_type_unrelated::k_hook_node(pos, chain.start, chain.back);
				return iterator(chain.start);
			}

#		if __cplusplus >= 201103L

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::k_insert_using_allocator(NodeAllocator & alloc, const_iterator pos, rvalue_reference val)
			{
				return k_emplace_using_allocator(alloc, pos, kerbal::compatibility::move(val));
			}

#		endif

#		if __cplusplus >= 201103L

			template <typename T>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::k_emplace_using_allocator(NodeAllocator & alloc, const_iterator pos, Args&& ... args)
			{
				node *p = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				list_type_unrelated::k_hook_node(pos, p);
				return iterator(p);
			}

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename T> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename list_type_only<T>::iterator \
			list_type_only<T>::k_emplace_using_allocator(NodeAllocator & alloc, const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				node *p = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				list_type_unrelated::k_hook_node(pos, p); \
				return iterator(p); \
			}

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#		endif


		//===================
		// erase

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_pop_front_using_allocator(NodeAllocator & alloc)
			{
				k_erase_using_allocator(alloc, this->cbegin());
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_pop_back_using_allocator(NodeAllocator & alloc)
			{
				k_erase_using_allocator(alloc, kerbal::iterator::prev(this->cend()));
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::k_erase_using_allocator(NodeAllocator & alloc, const_iterator pos)
			{
				iterator pos_mut(pos.cast_to_mutable());
				node_base * p = list_type_unrelated::k_unhook_node(pos_mut++);
				k_destroy_node(alloc, p);
				return pos_mut;
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::k_erase_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last)
			{
				iterator last_mut(last.cast_to_mutable());
				if (first != last) {
					iterator first_mut(first.cast_to_mutable());
					list_node_base_chain chain(list_type_unrelated::k_unhook_node(first_mut, last_mut));
					chain.back->next = NULL;
					k_consecutive_destroy_node(alloc, chain.start);
				}
				return last_mut;
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_clear_using_allocator(NodeAllocator & alloc)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(k_erase_using_allocator(alloc,
							kerbal::utility::declthis<list_type_only>()->cbegin(),
							kerbal::utility::declthis<list_type_only>()->cend())
					))
			{
				k_erase_using_allocator(alloc, this->cbegin(), this->cend());
			}


		//===================
		// operation

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_resize_using_allocator(NodeAllocator & alloc, size_type count)
			{
				const_iterator it(this->cbegin());
				const_iterator const cend(this->cend());
				size_type size(kerbal::iterator::advance_at_most(it, count, cend));
				if (size == count) {
					k_erase_using_allocator(alloc, it, cend);
				} else {
					// note: count - size != 0
					list_node_chain<T> chain(k_build_n_new_nodes_unguarded(alloc, count - size));
					list_type_unrelated::k_hook_node(cend, chain.start, chain.back);
				}
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_resize_using_allocator(NodeAllocator & alloc, size_type count, const_reference value)
			{
				const_iterator it(this->cbegin());
				const_iterator const cend(this->cend());
				size_type size(kerbal::iterator::advance_at_most(it, count, cend));
				if (size == count) {
					k_erase_using_allocator(alloc, it, cend);
				} else {
					k_insert_using_allocator(alloc, cend, count - size, value);
				}
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_iter_swap(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
			{
				list_type_unrelated::k_iter_swap(a, b);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_reverse(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
			{
				list_type_unrelated::k_reverse(first, last);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::iterator
			list_type_only<T>::rotate(const_iterator first, const_iterator n_first, const_iterator last) KERBAL_NOEXCEPT
			{
				return iterator(list_type_unrelated::k_rotate(first, n_first, last));
			}

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_merge_impl(list_type_only & other, BinaryPredict cmp, MERGE_VER_NOTHROW) KERBAL_NOEXCEPT
			{
				const_iterator it(this->cbegin());
				const_iterator const end(this->cend());
				const_iterator other_it(other.cbegin());
				const_iterator const other_end(other.cend());
				while (other_it != other_end) {
					if (it != end) {
						if (cmp(*other_it, *it)) { // *other_it < *it
							node_base * p = other_it.cast_to_mutable().current;
							++other_it;
							k_hook_node(it, p);
						} else { // *other_it >= *it
							++it;
						}
					} else {
						// node: it has made sure that the remain range is not empty
						node_base * remain_start = other_it.cast_to_mutable().current;
						node_base * remain_back = other.k_head.prev;
						k_hook_node(end, remain_start, remain_back);
						break;
					}
				}
				other.k_init_node_base();
			}

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_merge_impl(list_type_only & other, BinaryPredict cmp, MERGE_VER_MAY_THROW)
			{
				const_iterator it(this->cbegin());
				const_iterator const end(this->cend());
				const_iterator other_it(other.cbegin());
				const_iterator const other_end(other.cend());
				try {
					while (other_it != other_end) {
						if (it != end) {
							if (cmp(*other_it, *it)) { // *other_it < *it, waring: may throw!!!
								node_base * p = other_it.cast_to_mutable().current;
								++other_it;
								k_hook_node(it, p);
							} else { // *other_it >= *it
								++it;
							}
						} else {
							// node: it has made sure that the remain range is not empty
							node_base * remain_start = other_it.cast_to_mutable().current;
							node_base * remain_back = other.k_head.prev;
							k_hook_node(end, remain_start, remain_back);
							break;
						}
					}
				} catch (...) {
					node_base * p = other_it.cast_to_mutable().current;
					p->prev = &other.k_head;
					other.k_head.next = p;
					throw;
				}
				other.k_init_node_base();
			}

#		endif

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_merge(list_type_only & other, BinaryPredict cmp)
			{

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

#			if __cplusplus >= 201103L

				typedef typename kerbal::type_traits::conditional<
					noexcept(cmp(
							kerbal::utility::declval<const_reference>(),
							kerbal::utility::declval<const_reference>())),
					MERGE_VER_NOTHROW,
					MERGE_VER_MAY_THROW
				>::type MERGE_VERSION;

#			else
				typedef MERGE_VER_MAY_THROW MERGE_VERSION;
#			endif
#		else
				typedef MERGE_VER_NOTHROW MERGE_VERSION;
#		endif

				this->k_merge_impl(other, cmp, MERGE_VERSION());

			}

			template <typename T>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_merge(list_type_only& other)
			{
				this->k_merge(other, kerbal::compare::less<value_type>());
			}

			template <typename T>
			template <typename BinaryPredict>
			inline
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_merge_sort_merge(const_iterator first, const_iterator mid, const_iterator last, BinaryPredict cmp, MSM_VER_NOTHROW)
			{
				const_iterator before_mid(kerbal::iterator::prev(mid));
				const_iterator i(first);
				const_iterator j(mid);
				while (i != mid) {
					if (j != last) {
						if (cmp(*j, *i)) {
							k_hook_node(i, (j++).cast_to_mutable().current);
						} else {
							++i;
						}
					} else {
						break;
					}
				}
				before_mid.cast_to_mutable().current->next = j.cast_to_mutable().current;
				j.cast_to_mutable().current->prev = before_mid.cast_to_mutable().current;
			}

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename T>
			template <typename BinaryPredict>
			inline
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_merge_sort_merge(const_iterator first, const_iterator mid, const_iterator last, BinaryPredict cmp, MSM_VER_MAY_THROW)
			{
				const_iterator before_mid(kerbal::iterator::prev(mid));
				const_iterator i(first);
				const_iterator j(mid);
				try {
					while (i != mid) {
						if (j != last) {
							if (cmp(*j, *i)) {
								k_hook_node(i, (j++).cast_to_mutable().current);
							} else {
								++i;
							}
						} else {
							break;
						}
					}
				} catch (...) {
					before_mid.cast_to_mutable().current->next = j.cast_to_mutable().current;
					j.cast_to_mutable().current->prev = before_mid.cast_to_mutable().current;
					throw;
				}
				before_mid.cast_to_mutable().current->next = j.cast_to_mutable().current;
				j.cast_to_mutable().current->prev = before_mid.cast_to_mutable().current;
			}

#		endif

			template <typename T>
			template <typename BinaryPredict>
			inline
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_merge_sort_merge(const_iterator first, const_iterator mid, const_iterator last, BinaryPredict cmp)
			{

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

#			if __cplusplus >= 201103L

				typedef typename kerbal::type_traits::conditional<
						noexcept(cmp(
								kerbal::utility::declval<const_reference>(),
								kerbal::utility::declval<const_reference>())),
						MSM_VER_NOTHROW,
						MSM_VER_MAY_THROW
				>::type MSM_VERSION;

#			else
				typedef MSM_VER_MAY_THROW MSM_VERSION;
#			endif
#		else
				typedef MSM_VER_NOTHROW MSM_VERSION;
#		endif

				k_merge_sort_merge(first, mid, last, cmp, MSM_VERSION());

			}

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::const_iterator
			list_type_only<T>::k_merge_sort_n(const_iterator first, difference_type len, BinaryPredict cmp)
			{
				if (len == 0) {
					return first;
				}
				if (len == 1) {
					return kerbal::iterator::next(first);
				}
				if (len == 2) {
					const_iterator i(kerbal::iterator::next(first));
					const_iterator r(kerbal::iterator::next(i));
					if (cmp(*i, *first)) {
						k_iter_swap(first, i);
					}
					return r;
				}
				difference_type first_half_len = len / 2;

				const_iterator pre_first(kerbal::iterator::prev(first));
				const_iterator mid(k_merge_sort_n(first, first_half_len, cmp));

				const_iterator pre_mid(kerbal::iterator::prev(mid));
				const_iterator last(k_merge_sort_n(mid, len - first_half_len, cmp));

				first = kerbal::iterator::next(pre_first);
				mid = kerbal::iterator::next(pre_mid);
				k_merge_sort_merge(first, mid, last, cmp);

				return last;
			}

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_merge_sort(const_iterator first, const_iterator last, BinaryPredict cmp)
			{
				k_merge_sort_n(first, kerbal::iterator::distance(first, last), cmp);
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_radix_sort_back_fill(
					const_iterator insert_pos, kerbal::type_traits::false_type /*unsigned*/,
					list_type_only buckets[], std::size_t BUCKETS_NUM) KERBAL_NOEXCEPT
			{
				for (std::size_t i = 0; i < BUCKETS_NUM; ++i) {
					k_splice(insert_pos, buckets[i]);
				}
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_radix_sort_back_fill(
					const_iterator insert_pos, kerbal::type_traits::true_type /*signed*/,
					list_type_only buckets[], std::size_t BUCKETS_NUM) KERBAL_NOEXCEPT
			{
				for (std::size_t i = BUCKETS_NUM / 2; i < BUCKETS_NUM; ++i) {
					k_splice(insert_pos, buckets[i]);
				}
				for (std::size_t i = 0; i < BUCKETS_NUM / 2; ++i) {
					k_splice(insert_pos, buckets[i]);
				}
			}

			template <typename T>
			template <std::size_t RADIX_BIT_WIDTH>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_radix_sort(
					const_iterator first, const_iterator last, kerbal::type_traits::false_type asc,
					kerbal::type_traits::integral_constant<std::size_t, RADIX_BIT_WIDTH>) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, 1 << RADIX_BIT_WIDTH> BUCKETS_NUM;
				list_type_only buckets[2][BUCKETS_NUM::value];

				for (int i = 0; i < 2; ++i) {
					for (std::size_t j = 0; j < BUCKETS_NUM::value; ++j) {
						buckets[i][j].k_init_node_base();
					}
				}

				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH;
				typedef kerbal::type_traits::integral_constant<std::size_t, VALUE_TYPE_BIT_WIDTH::value / RADIX_BIT_WIDTH + (VALUE_TYPE_BIT_WIDTH::value % RADIX_BIT_WIDTH != 0)> ROUNDS;

				// first round
				for (const_iterator it(first); it != last; ) {
					int bucket_id = *it % BUCKETS_NUM::value;
					list_type_only & bucket_in = buckets[0][bucket_id];
					bucket_in.k_splice(bucket_in.cend(), it++);
				}

				for (std::size_t round = 1; round < ROUNDS::value; ++round) {
					list_type_only (& buckets_from)[BUCKETS_NUM::value] = buckets[(round + 1) % 2];
					list_type_only (& buckets_to)[BUCKETS_NUM::value] = buckets[round % 2];

					for (std::size_t i = 0; i < BUCKETS_NUM::value; ++i) {
						list_type_only & bucket_out = buckets_from[i];
						const_iterator it(bucket_out.begin());
						const_iterator const cend(bucket_out.end());
						while (it != cend) {
							int bucket_id = (*it >> (RADIX_BIT_WIDTH * round)) % BUCKETS_NUM::value;
							list_type_only & bucket_in = buckets_to[bucket_id];
							bucket_in.k_splice(bucket_in.cend(), it++);
						}
					}
				}

				k_radix_sort_back_fill<true>(
						last, kerbal::type_traits::is_signed<value_type>(),
						buckets[(ROUNDS::value + 1) % 2], BUCKETS_NUM::value);
			}

			template <typename T>
			template <std::size_t RADIX_BIT_WIDTH>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_radix_sort(
					const_iterator first, const_iterator last, kerbal::type_traits::true_type desc,
					kerbal::type_traits::integral_constant<std::size_t, RADIX_BIT_WIDTH>) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, 1 << RADIX_BIT_WIDTH> BUCKETS_NUM;
				list_type_only buckets[2][BUCKETS_NUM::value];

				for (int i = 0; i < 2; ++i) {
					for (std::size_t j = 0; j < BUCKETS_NUM::value; ++j) {
						buckets[i][j].k_init_node_base();
					}
				}

				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH;
				typedef kerbal::type_traits::integral_constant<std::size_t, VALUE_TYPE_BIT_WIDTH::value / RADIX_BIT_WIDTH + (VALUE_TYPE_BIT_WIDTH::value % RADIX_BIT_WIDTH != 0)> ROUNDS;

				// first round
				for (const_iterator it(first); it != last; ) {
					int bucket_id = BUCKETS_NUM::value - 1 - *it % BUCKETS_NUM::value;
					list_type_only & bucket_in = buckets[0][bucket_id];
					bucket_in.k_splice(bucket_in.cend(), it++);
				}

				for (std::size_t round = 1; round < ROUNDS::value; ++round) {
					list_type_only (& buckets_from)[BUCKETS_NUM::value] = buckets[(round + 1) % 2];
					list_type_only (& buckets_to)[BUCKETS_NUM::value] = buckets[round % 2];

					for (std::size_t i = 0; i < BUCKETS_NUM::value; ++i) {
						list_type_only & bucket_out = buckets_from[i];
						const_iterator it(bucket_out.begin());
						const_iterator const cend(bucket_out.end());
						while (it != cend) {
							int bucket_id = BUCKETS_NUM::value - 1 - (*it >> (RADIX_BIT_WIDTH * round)) % BUCKETS_NUM::value;
							list_type_only & bucket_in = buckets_to[bucket_id];
							bucket_in.k_splice(bucket_in.cend(), it++);
						}
					}
				}

				k_radix_sort_back_fill<true>(
						last, kerbal::type_traits::is_signed<value_type>(),
						buckets[(ROUNDS::value + 1) % 2], BUCKETS_NUM::value);
			}

			template <typename T>
			template <typename Order>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_radix_sort(const_iterator first, const_iterator last, Order /*order*/) KERBAL_NOEXCEPT
			{
				k_radix_sort(first, last, kerbal::type_traits::bool_constant<Order::value>(),
						   kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT>());
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_radix_sort(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
			{
				k_radix_sort(first, last, kerbal::type_traits::false_type());
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type, typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, BinaryPredict cmp)
			{
				k_merge_sort(first, last, cmp);
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, kerbal::compare::less<value_type> /*cmp*/)
			{
				k_radix_sort(first, last, kerbal::type_traits::false_type());
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, kerbal::compare::greater<value_type> /*cmp*/)
			{
				k_radix_sort(first, last, kerbal::type_traits::true_type());
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, kerbal::compare::less<void> /*cmp*/)
			{
				k_radix_sort(first, last, kerbal::type_traits::false_type());
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, kerbal::compare::greater<void> /*cmp*/)
			{
				k_radix_sort(first, last, kerbal::type_traits::true_type());
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, std::less<value_type> /*cmp*/)
			{
				k_radix_sort(first, last, kerbal::type_traits::false_type());
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, std::greater<value_type> /*cmp*/)
			{
				k_radix_sort(first, last, kerbal::type_traits::true_type());
			}

#		if __cplusplus >= 201402L

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, std::less<void> /*cmp*/)
			{
				k_radix_sort(first, last, kerbal::type_traits::false_type());
			}

			template <typename T>
			template <bool is_radix_sort_acceptable_type>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, std::greater<void> /*cmp*/)
			{
				k_radix_sort(first, last, kerbal::type_traits::true_type());
			}

#		endif

			template <typename T>
			template <bool is_radix_sort_acceptable_type, typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<!is_radix_sort_acceptable_type>::type
			list_type_only<T>::k_sort_method_overload(const_iterator first, const_iterator last, BinaryPredict cmp)
			{
				k_merge_sort(first, last, cmp);
			}

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_sort(const_iterator first, const_iterator last, BinaryPredict cmp)
			{
//				k_merge_sort(first, last, cmp);
				k_sort_method_overload<is_list_radix_sort_acceptable_type<value_type>::value>(first, last, cmp);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_sort(const_iterator first, const_iterator last)
			{
				k_sort(first, last, kerbal::compare::less<value_type>());
			}

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::sort(BinaryPredict cmp)
			{
				k_sort(this->begin(), this->end(), cmp);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::sort()
			{
				k_sort(this->begin(), this->end());
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::k_remove_using_allocator(NodeAllocator & alloc, const_reference val)
			{
				return k_remove_using_allocator(alloc, this->cbegin(), this->cend(), val);
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::k_remove_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, const_reference val)
			{
				return k_remove_if_using_allocator(alloc, first, last, remove_predict(val));
			}

			template <typename T>
			template <typename NodeAllocator, typename UnaryPredicate>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::k_remove_if_using_allocator(NodeAllocator & alloc, UnaryPredicate predicate)
			{
				return k_remove_if_using_allocator(alloc, this->cbegin(), this->cend(), predicate);
			}

			template <typename T>
			template <typename NodeAllocator, typename UnaryPredicate>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::k_remove_if_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, UnaryPredicate predicate)
			{
				size_type i = 0;
				while (first != last) {
					if (predicate(*first)) {
						node_base * p = k_unhook_node(first++.cast_to_mutable());
						k_destroy_node(alloc, p);
						// <=> first = k_erase_using_allocator(alloc, first);
						++i;
					} else {
						++first;
					}
				}
				return i;
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::k_unique_using_allocator(NodeAllocator & alloc)
			{
				return k_unique_using_allocator(alloc, this->cbegin(), this->cend());
			}

			template <typename T>
			template <typename NodeAllocator, typename BinaryPredicate>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::k_unique_using_allocator(NodeAllocator & alloc, BinaryPredicate pred)
			{
				return k_unique_using_allocator(alloc, this->cbegin(), this->cend(), pred);
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::k_unique_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last)
			{
				return k_unique_using_allocator(alloc, first, last, kerbal::compare::equal_to<value_type>());
			}

			template <typename T>
			template <typename NodeAllocator, typename BinaryPredicate>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::size_type
			list_type_only<T>::k_unique_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, BinaryPredicate pred)
			{
				size_type r = 0;

				if (first != last) {
					const_iterator forward(first); ++forward;

					while (forward != last) {
						if (pred(*first, *forward)) {
							node_base * p = list_type_unrelated::k_unhook_node(forward++.cast_to_mutable());
							k_destroy_node(alloc, p);
							// <=> k_erase_using_allocator(alloc, forward++);
							++r;
						} else {
							first = forward;
							++forward;
						}
					}
				}

				return r;
			}

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_set_difference(list_type_only & l1, const list_type_only & l2, list_type_only & lto, BinaryPredict cmp)
			{
				const_iterator it1(l1.cbegin());
				const_iterator it2(l2.cbegin());
				const_iterator const end1(l1.cend());
				const_iterator const end2(l2.cend());

				while (it1 != end1) {
					if (it2 != end2) {
						if (cmp(*it1, *it2)) { // *it1 < *it2
							lto.k_splice(lto.cend(), it1++);
						} else if (cmp(*it2, *it1)) { // *it2 < *it1
							++it2;
						} else { // *it1 == *first2
							++it1;
							++it2;
						}
					} else {
						lto.k_splice(lto.cend(), it1, end1);
						break;
					}
				}
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_set_difference(list_type_only & l1, const list_type_only & l2, list_type_only & lto)
			{
				list_type_only::k_set_difference(l1, l2, lto, kerbal::compare::less<value_type>());
			}

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_set_intersection(list_type_only & l1, list_type_only & l2, list_type_only & lto, BinaryPredict cmp)
			{
				const_iterator it1(l1.cbegin());
				const_iterator it2(l2.cbegin());
				const_iterator const end1(l1.cend());
				const_iterator const end2(l2.cend());

				while (it1 != end1) {
					if (it2 != end2) {
						if (cmp(*it1, *it2)) { // *it1 < *it2
							++it1;
						} else if (cmp(*it2, *it1)) { // *it2 < *it1
							++it2;
						} else { // *it1 == *first2
							lto.k_splice(lto.cend(), it1++);
							++it2;
						}
					} else {
						break;
					}
				}
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_set_intersection(list_type_only & l1, list_type_only & l2, list_type_only & lto)
			{
				list_type_only::k_set_intersection(l1, l2, lto, kerbal::compare::less<value_type>());
			}

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_set_symmetric_difference(list_type_only & l1, list_type_only & l2, list_type_only & lto, BinaryPredict cmp)
			{
				const_iterator it1(l1.cbegin());
				const_iterator it2(l2.cbegin());
				const_iterator const end1(l1.cend());
				const_iterator const end2(l2.cend());

				while (it1 != end1) {
					if (it2 != end2) {
						if (cmp(*it1, *it2)) { // *it1 < *it2
							lto.k_splice(lto.cend(), it1++);
						} else if (cmp(*it2, *it1)) { // *it2 < *it1
							lto.k_splice(lto.cend(), it2++);
						} else { // *it1 == *first2
							++it1;
							++it2;
						}
					} else {
						lto.k_splice(lto.cend(), it1, end1);
						return;
					}
				}
				lto.k_splice(lto.cend(), it2, end2);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_set_symmetric_difference(list_type_only & l1, list_type_only & l2, list_type_only & lto)
			{
				list_type_only::k_set_symmetric_difference(l1, l2, lto, kerbal::compare::less<value_type>());
			}

			template <typename T>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_set_union(list_type_only & l1, list_type_only & l2, list_type_only & lto, BinaryPredict cmp)
			{
				const_iterator it1(l1.cbegin());
				const_iterator it2(l2.cbegin());
				const_iterator const end1(l1.cend());
				const_iterator const end2(l2.cend());

				while (it1 != end1) {
					if (it2 != end2) {
						if (cmp(*it2, *it1)) { // *it2 < *it1
							lto.k_splice(lto.cend(), it2++);
						} else {
							bool b = cmp(*it1, *it2); // *it1 < *it2
							lto.k_splice(lto.cend(), it1++);
							if (!b) { // *it1 == *it2
								++it2;
							}
						}
					} else {
						lto.k_splice(lto.cend(), it1, end1);
						return;
					}
				}
				lto.k_splice(lto.cend(), it2, end2);
			}

			template <typename T>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_set_union(list_type_only & l1, list_type_only & l2, list_type_only & lto)
			{
				list_type_only::k_set_union(l1, l2, lto, kerbal::compare::less<value_type>());
			}


		//===================
		// private

#	if __cplusplus >= 201103L

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename T>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					!nothrow_while_construct,
					typename list_type_only<T>::node*
			>::type
			list_type_only<T>::k_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate_one(alloc);
				try {
					node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				} catch (...) {
					node_allocator_traits::deallocate_one(alloc, p);
					throw;
				}
				return p;
			}

			template <typename T>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					nothrow_while_construct,
					typename list_type_only<T>::node*
			>::type
			list_type_only<T>::k_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::allocator_traits<NodeAllocator>::allocate_one(alloc))
					)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate_one(alloc);
				node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				return p;
			}

			template <typename T>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::node*
			list_type_only<T>::k_build_new_node(NodeAllocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef
				kerbal::type_traits::bool_constant<
						noexcept(
								node_allocator_traits::construct(
										alloc, kerbal::utility::declval<node*>(),
										kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...
								)
						)
				> nothrow_while_construct;

				return k_build_new_node_impl<nothrow_while_construct::value>(alloc, kerbal::utility::forward<Args>(args)...);
			}

#		else // KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename T>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename list_type_only<T>::node*
			list_type_only<T>::k_build_new_node(NodeAllocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate_one(alloc);
				if (p == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
				node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				return p;
			}

#		endif // KERBAL_HAS_EXCEPTIONS_SUPPORT

#	else // __cplusplus >= 201103L

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
#		define FBODY(i) \
			template <typename T> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename list_type_only<T>::node* \
			list_type_only<T>::k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
				node * p = node_allocator_traits::allocate_one(alloc); \
				try { \
					node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				} catch (...) { \
					node_allocator_traits::deallocate_one(alloc, p); \
					throw; \
				} \
				return p; \
			}
#	else // KERBAL_HAS_EXCEPTIONS_SUPPORT
#		define FBODY(i) \
			template <typename T> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename list_type_only<T>::node* \
			list_type_only<T>::k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
				node * p = node_allocator_traits::allocate_one(alloc); \
				if (p == NULL) { \
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception(); \
				} \
				node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				return p; \
			}
#	endif // KERBAL_HAS_EXCEPTIONS_SUPPORT

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif // __cplusplus >= 201103L


#	if __cplusplus >= 201103L

			template <typename T>
			template <typename NodeAllocator, typename... Args>
			KERBAL_CONSTEXPR20
			list_node_chain<T>
			list_type_only<T>::k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, Args&& ... args)
			{
				size_type cnt = 0;
				node_base head;
				node_base * prev = &head;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#		endif // KERBAL_HAS_EXCEPTIONS_SUPPORT
					do {
						node * new_node = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
						new_node->prev = prev;
						prev->next = new_node;
						prev = new_node;
						++cnt;
					} while (cnt != n);
					return list_node_chain<T>(
							node::reinterpret_as(head.next),
							node::reinterpret_as(prev)
					);
#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_consecutive_destroy_node(alloc, head.next);
					throw;
				}
#		endif // KERBAL_HAS_EXCEPTIONS_SUPPORT
			}

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
#		define FBODY(i) \
			template <typename T> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			list_node_chain<T> \
			list_type_only<T>::k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				size_type cnt = 0; \
				node_base head; \
				node_base * prev = &head; \
 \
				try { \
					do { \
						node * new_node = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
						new_node->prev = prev; \
						prev->next = new_node; \
						prev = new_node; \
						++cnt; \
					} while (cnt != n); \
					return list_node_chain<T>( \
							node::reinterpret_as(head.next), \
							node::reinterpret_as(prev) \
					); \
				} catch (...) { \
					k_consecutive_destroy_node(alloc, head.next); \
					throw; \
				} \
			}
#	else // KERBAL_HAS_EXCEPTIONS_SUPPORT
#		define FBODY(i) \
			template <typename T> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			list_node_chain<T> \
			list_type_only<T>::k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				size_type cnt = 0; \
				node_base head; \
				node_base * prev = &head; \
 \
				do { \
					node * new_node = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					new_node->prev = prev; \
					prev->next = new_node; \
					prev = new_node; \
					++cnt; \
				} while (cnt != n); \
				return list_node_chain<T>( \
						node::reinterpret_as(head.next), \
						node::reinterpret_as(prev) \
				); \
			}
#	endif // KERBAL_HAS_EXCEPTIONS_SUPPORT

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif


			template <typename T>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					list_node_chain<T>
			>::type
			list_type_only<T>::k_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last)
			{
				node_base head;
				node_base * prev = &head;

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif // KERBAL_HAS_EXCEPTIONS_SUPPORT
					do {
						node * new_node = k_build_new_node(alloc, *first);
						new_node->prev = prev;
						prev->next = new_node;
						prev = new_node;
						++first;
					} while (first != last);
					return list_node_chain<T>(
							node::reinterpret_as(head.next),
							node::reinterpret_as(prev)
					);
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_consecutive_destroy_node(alloc, head.next);
					throw;
				}
#			endif // KERBAL_HAS_EXCEPTIONS_SUPPORT
			}


			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_destroy_node(NodeAllocator & alloc, node_base* p_node_base)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::memory::allocator_traits<NodeAllocator>::destroy(
								alloc,
								kerbal::utility::declval<typename kerbal::memory::allocator_traits<NodeAllocator>::pointer>()
							)
						) &&
						noexcept(
							kerbal::memory::allocator_traits<NodeAllocator>::deallocate_one(
								alloc,
								kerbal::utility::declval<typename kerbal::memory::allocator_traits<NodeAllocator>::pointer>()
							)
						)
					)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef typename node_allocator_traits::pointer allocator_pointer_type;

				node * p_node = node::reinterpret_as(p_node_base);
				allocator_pointer_type p_node_act = static_cast<allocator_pointer_type>(p_node);
				node_allocator_traits::destroy(alloc, p_node_act);
				node_allocator_traits::deallocate_one(alloc, p_node_act);
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * start, CNSCTV_DES_VER_DEFAULT)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(k_destroy_node(alloc, kerbal::utility::declval<node_base*>()))
					)
			{
				node_base * current_node_base = start;
				while (current_node_base != NULL) {
					node_base * next = current_node_base->next;
					k_destroy_node(alloc, current_node_base);
					current_node_base = next;
				}
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::allocator_traits<NodeAllocator>::destroy(
									alloc,
									kerbal::utility::declval<typename kerbal::memory::allocator_traits<NodeAllocator>::pointer>())
							)
					)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef typename node_allocator_traits::pointer allocator_pointer_type;

				node_base * current_node_base = start;
				while (current_node_base != NULL) {
					node_base * next = current_node_base->next;
					node * p_node = node::reinterpret_as(current_node_base);
					allocator_pointer_type p_node_act = static_cast<allocator_pointer_type>(p_node);
					node_allocator_traits::destroy(alloc, p_node_act);
					current_node_base = next;
				}
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_consecutive_destroy_node_impl(NodeAllocator & /*alloc*/, node_base * /*start*/, CNSCTV_DES_VER_NO_DESTROY) KERBAL_NOEXCEPT
			{
			}

			template <typename T>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_consecutive_destroy_node(NodeAllocator & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT()))
					)
			{
				k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT());
			}

			template <typename T>
			template <typename U, typename UpstreamAllocator>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_consecutive_destroy_node(kerbal::memory::monotonic_allocator<U, UpstreamAllocator> & alloc, node_base * start)
			{
				typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<T>::IS_TRUE::value,
					CNSCTV_DES_VER_NO_DESTROY,
					CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE
				>::type VER;
				k_consecutive_destroy_node_impl(alloc, start, VER());
			}

#		if __cplusplus >= 201703L
#			if __has_include(<memory_resource>)

			template <typename T>
			template <typename Node>
			KERBAL_CONSTEXPR20
			void list_type_only<T>::k_consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
						(
							!kerbal::type_traits::try_test_is_trivially_destructible<T>::IS_TRUE::value ?
							noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE())) :
							true
						) &&
						noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT()))
					)
			{
				if (typeid(*alloc.resource()) == typeid(std::pmr::monotonic_buffer_resource)) {
					if constexpr (!kerbal::type_traits::try_test_is_trivially_destructible<T>::IS_TRUE::value) {
						k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE());
					}
				} else {
					k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT());
				}
			}

#			endif
#		endif


		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_BASE_IMPL_HPP
