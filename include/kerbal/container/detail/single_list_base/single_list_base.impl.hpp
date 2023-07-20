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

#ifndef KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_BASE_IMPL_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/generic_assign.hpp>
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
#	include <kerbal/iterator/move_iterator.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if !__cpp_exceptions
#	include <kerbal/memory/bad_alloc.hpp>
#	include <kerbal/utility/throw_this_exception.hpp>
#endif

#include <cstddef>

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <kerbal/type_traits/is_trivially_destructible.hpp>
#		include <kerbal/type_traits/tribool_constant.hpp>
#		include <memory_resource>
#	endif
#endif

#include <kerbal/container/detail/single_list_base/single_list_base.decl.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

		//===================
		//===================
		// sl_type_unrelated

		//===================
		// capacity

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
		// operation

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_iter_swap(basic_iterator a, basic_iterator b) KERBAL_NOEXCEPT
			{
				node_base * pre_a = a.current;
				node_base * pre_b = b.current;
				node_base * pa = pre_a->next;
				node_base * pb = pre_b->next;
				kerbal::algorithm::swap(pre_a->next, pre_b->next);
				kerbal::algorithm::swap(pa->next, pb->next);
				if (pa->next == NULL) {
					this->k_last = basic_iterator(pa);
				} else if (pb->next == NULL) {
					this->k_last = basic_iterator(pb);
				}
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_reverse(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT
			{
				if (first == last) {
					return;
				}

				basic_iterator a(first); ++a;
				basic_iterator b(a); ++b;
				basic_iterator e(last); ++e;

				if (last == this->basic_end()) {
					this->k_last = a;
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
				this->k_reverse(this->basic_begin(), this->basic_end());
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_splice(basic_const_iterator pos, sl_type_unrelated & other)
																							KERBAL_NOEXCEPT
			{
				this->k_splice(pos, other, other.basic_begin(), other.basic_end());
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_splice(basic_const_iterator pos, sl_type_unrelated & other, basic_const_iterator opos)
																							KERBAL_NOEXCEPT
			{
				node_base * p = other.k_unhook_node(opos.cast_to_mutable());
				p->next = NULL;
				this->k_hook_node(pos, p);
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_splice(basic_const_iterator pos, sl_type_unrelated & other,
											basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				if (first == last) {
					return;
				}
				sl_node_base_chain chain(other.k_unhook_node(first.cast_to_mutable(), last.cast_to_mutable()));
				chain.back->next = NULL;
				this->k_hook_node(pos, chain.start, chain.back);
			}

#		if __cplusplus >= 201103L

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_splice(basic_const_iterator pos, sl_type_unrelated && other)
																							KERBAL_NOEXCEPT
			{
				this->k_splice(pos, kerbal::compatibility::move(other), other.basic_begin(), other.basic_end());
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_splice(basic_const_iterator pos, sl_type_unrelated && other, basic_const_iterator opos)
																							KERBAL_NOEXCEPT
			{
				node_base * p = other.k_unhook_node(opos.cast_to_mutable());
				p->next = NULL;
				this->k_hook_node(pos, p);
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_splice(basic_const_iterator pos, sl_type_unrelated && other,
											basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				if (first == last) {
					return;
				}
				sl_node_base_chain chain(other.k_unhook_node(first.cast_to_mutable(), last.cast_to_mutable()));
				chain.back->next = NULL;
				this->k_hook_node(pos, chain.start, chain.back);
			}

#		endif

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_hook_node_back(node_base * p) KERBAL_NOEXCEPT
			{
				node_base * prev = this->k_last.current;
				prev->next = p;
				this->k_last = basic_iterator(p);
			}

		//===================
		// private

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_hook_node_not_back(basic_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				node_base * prev = pos.current;
				p->next = prev->next;
				prev->next = p;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				if (pos_mut != this->basic_end()) {
					this->k_hook_node_not_back(pos_mut, p);
				} else {
					this->k_hook_node_back(p);
				}
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_hook_node_back(node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				node_base * prev = this->k_last.current;
				this->k_last = basic_iterator(back);
				prev->next = start;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_hook_node_not_back(basic_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				node_base * prev = pos.current;
				back->next = prev->next;
				prev->next = start;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				if (pos_mut != this->basic_end()) {
					this->k_hook_node_not_back(pos_mut, start, back);
				} else {
					this->k_hook_node_back(start, back);
				}
			}

			KERBAL_CONSTEXPR20
			inline
			sl_node_base *
			sl_type_unrelated::k_unhook_node(basic_iterator pos) KERBAL_NOEXCEPT
			{
				node_base * prev = pos.current;
				node_base * p = prev->next;
				prev->next = p->next;
				if (p->next == NULL) { // is back node
					this->k_last = pos;
				}
				return p;
			}

			// pre-cond: first != last;
			KERBAL_CONSTEXPR20
			inline
			sl_node_base_chain
			sl_type_unrelated::k_unhook_node(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT
			{
				node_base * prev = first.current;
				node_base * start = prev->next;
				node_base * back = last.current;

				prev->next = back->next;

				if (back->next == NULL) {
					this->k_last = first;
				}

				return sl_node_base_chain(start, back);
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_swap_with_empty(sl_type_unrelated & not_empty_list, sl_type_unrelated & empty_list) KERBAL_NOEXCEPT
			{
				empty_list.k_head.next = not_empty_list.k_head.next;
				empty_list.k_last = not_empty_list.k_last;
				not_empty_list.k_init_node_base();
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::k_swap_type_unrelated(sl_type_unrelated & lhs, sl_type_unrelated & rhs) KERBAL_NOEXCEPT
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
						kerbal::algorithm::swap(lhs.k_head.next, rhs.k_head.next);
						kerbal::algorithm::swap(lhs.k_last, rhs.k_last);
					}
				}
			}


		//===================
		//===================
		// sl_type_only

		//===================
		// construct/copy/destroy

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			sl_type_only<Tp>::sl_type_only(NodeAllocator & alloc, size_type n) :
					super()
			{
				if (n == 0) {
					return;
				}
				sl_node_chain<Tp> chain(k_build_n_new_nodes_unguarded(alloc, n));
				this->k_hook_node(this->cbegin(), chain.start, chain.back);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			sl_type_only<Tp>::sl_type_only(NodeAllocator & alloc, size_type n, const_reference val) :
					super()
			{
				if (n == 0) {
					return;
				}
				sl_node_chain<Tp> chain(k_build_n_new_nodes_unguarded(alloc, n, val));
				this->k_hook_node(this->cbegin(), chain.start, chain.back);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			sl_type_only<Tp>::sl_type_only(NodeAllocator & alloc, InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
					>::type) :
					super()
			{
				this->k_insert_using_allocator(alloc, this->cbegin(), first, last);
			}

#	if __cplusplus >= 201103L

			// pre-cond: allocator allows
			template <typename Tp>
			KERBAL_CONSTEXPR14
			sl_type_only<Tp>::sl_type_only(sl_type_only && src) KERBAL_NOEXCEPT :
					sl_type_unrelated()
			{
				if (src.empty()) {
					return;
				}
				sl_type_unrelated::k_swap_with_empty(
						static_cast<sl_type_unrelated &>(src),
						static_cast<sl_type_unrelated &>(*this));
			}

			// move construct using allocator, allocator is equal
			template <typename Tp>
			KERBAL_CONSTEXPR14
			void sl_type_only<Tp>::k_move_cnstrct_ua_ae(sl_type_only && src) KERBAL_NOEXCEPT
			{
				if (src.empty()) {
					return;
				}
				sl_type_unrelated::k_swap_with_empty(
						static_cast<sl_type_unrelated &>(src),
						static_cast<sl_type_unrelated &>(*this));
			}

			// move construct using allocator, allocator is not equal
			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_move_cnstrct_ua_ane(NodeAllocator & this_alloc, sl_type_only && src)
			{
				if (src.empty()) {
					return;
				}
				sl_node_chain<Tp> chain(
						k_build_new_nodes_range_unguarded(
								this_alloc,
								kerbal::iterator::make_move_iterator(src.begin()),
								kerbal::iterator::make_move_iterator(src.end())));
				sl_type_unrelated::k_hook_node_back(chain.start, chain.back);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_move_cnstrct_ua_helper(NodeAllocator & this_alloc, NodeAllocator && src_alloc, sl_type_only && src,
																	   kerbal::type_traits::false_type /*is_always_equal*/)
			{
				if (this_alloc != src_alloc) {
					this->k_move_cnstrct_ua_ane(this_alloc, kerbal::compatibility::move(src));
				} else {
					this->k_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR14
			void sl_type_only<Tp>::k_move_cnstrct_ua_helper(NodeAllocator & /*this_alloc*/, NodeAllocator && /*src_alloc*/, sl_type_only && src,
																	   kerbal::type_traits::true_type /*is_always_equal*/) KERBAL_NOEXCEPT
			{
				this->k_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR14
			sl_type_only<Tp>::sl_type_only(NodeAllocator & this_alloc, NodeAllocator && src_alloc, sl_type_only && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_constructible_using_allocator<NodeAllocator>::value) :
					sl_type_unrelated()
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> allocator_traits;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				this->k_move_cnstrct_ua_helper(this_alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src), is_always_equal());
			}

#	endif

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_destroy_using_allocator(NodeAllocator & alloc) KERBAL_NOEXCEPT
			{
				this->k_consecutive_destroy_node(alloc, this->k_head.next);
			}


		//===================
		// assign

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_assign_using_allocator(NodeAllocator & alloc, size_type count, const_reference val)
			{
				iterator it(this->begin());
				const_iterator const end(this->cend());
				while (count != 0) {
					if (it != end) {
						kerbal::assign::generic_assign(*it, val); // *it = val;
						--count;
						++it;
					} else {
						this->k_insert_using_allocator(alloc, end, count, val);
						return;
					}
				}
				this->k_erase_using_allocator(alloc, it, end);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
			>::type
			sl_type_only<Tp>::k_assign_using_allocator(NodeAllocator & alloc, InputIterator first, InputIterator last)
			{
				iterator it(this->begin());
				const_iterator const end(this->cend());
				while (first != last) {
					if (it != end) {
						kerbal::assign::generic_assign(*it, *first); // *it = *first;
						++first;
						++it;
					} else {
						this->k_insert_using_allocator(alloc, end, first, last);
						return;
					}
				}
				this->k_erase_using_allocator(alloc, it, end);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & src_alloc, const sl_type_only & src, CPYASS_VER_NOT_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_destroy_using_allocator(alloc);
					this->sl_type_unrelated::k_init_node_base();
				}
				this->k_assign_using_allocator(alloc, src.cbegin(), src.cend());
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & src_alloc, const sl_type_only & src, CPYASS_VER_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_destroy_using_allocator(alloc);
					this->sl_type_unrelated::k_init_node_base();
				}
				alloc = src_alloc;
				this->k_assign_using_allocator(alloc, src.cbegin(), src.cend());
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & /*src_alloc*/, const sl_type_only & src, CPYASS_VER_ALWAYS_EQUAL)
			{
				this->k_assign_using_allocator(alloc, src.cbegin(), src.cend());
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_assign_using_allocator(NodeAllocator & alloc, const NodeAllocator & src_alloc, const sl_type_only & src)
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

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_move_assign(NodeAllocator & alloc, sl_type_only && src) KERBAL_NOEXCEPT
			{
				this->k_destroy_using_allocator(alloc);
				this->sl_type_unrelated::k_init_node_base();
				if (!src.empty()) {
					sl_type_unrelated::k_swap_with_empty(static_cast<sl_type_unrelated &>(src), static_cast<sl_type_unrelated &>(*this));
				}
			}

			// move assign using allocator, allocator is equal
			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_mov_ass_ua_ae(NodeAllocator & alloc, sl_type_only && src) KERBAL_NOEXCEPT
			{
				this->k_move_assign(alloc, kerbal::compatibility::move(src));
			}

			// move assign using allocator, allocator is not equal
			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_mov_ass_ua_ane(NodeAllocator & alloc, sl_type_only && src)
			{
				this->k_assign_using_allocator(
						alloc,
						kerbal::iterator::make_move_iterator(src.begin()),
						kerbal::iterator::make_move_iterator(src.end()));
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && src_alloc, sl_type_only && src,
																MOVASS_VER_NOT_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_mov_ass_ua_ane(alloc, kerbal::compatibility::move(src));
				} else {
					this->k_mov_ass_ua_ae(alloc, kerbal::compatibility::move(src));
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && src_alloc, sl_type_only && src,
																MOVASS_VER_PROPAGATE)
			{
				this->k_destroy_using_allocator(alloc);
				this->sl_type_unrelated::k_init_node_base();
				alloc = kerbal::compatibility::move(src_alloc);
				if (!src.empty()) {
					sl_type_unrelated::k_swap_with_empty(static_cast<sl_type_unrelated &>(src), static_cast<sl_type_unrelated &>(*this));
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && /*src_alloc*/, sl_type_only && src,
																MOVASS_VER_ALWAYS_EQUAL) KERBAL_NOEXCEPT
			{
				this->k_mov_ass_ua_ae(alloc, kerbal::compatibility::move(src));
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_assign_using_allocator(NodeAllocator & alloc, NodeAllocator && src_alloc, sl_type_only && src)
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

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::reference
			sl_type_only<Tp>::front() KERBAL_NOEXCEPT
			{
				return *this->begin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::const_reference
			sl_type_only<Tp>::front() const KERBAL_NOEXCEPT
			{
				return *this->cbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::reference
			sl_type_only<Tp>::back() KERBAL_NOEXCEPT
			{
				return this->end().current->template reinterpret_as<Tp>().member();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::const_reference
			sl_type_only<Tp>::back() const KERBAL_NOEXCEPT
			{
				return this->cend().current->template reinterpret_as<Tp>().member();
			}


		//===================
		// iterator

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::iterator
			sl_type_only<Tp>::begin() KERBAL_NOEXCEPT
			{
				return iterator(&this->k_head);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::iterator
			sl_type_only<Tp>::end() KERBAL_NOEXCEPT
			{
				return iterator(this->k_last);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::const_iterator
			sl_type_only<Tp>::begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->k_head);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::const_iterator
			sl_type_only<Tp>::end() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_last);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::const_iterator
			sl_type_only<Tp>::cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->k_head);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::const_iterator
			sl_type_only<Tp>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_last);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::iterator
			sl_type_only<Tp>::nth(size_type index) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->begin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::const_iterator
			sl_type_only<Tp>::nth(size_type index) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->cbegin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::size_type
			sl_type_only<Tp>::index_of(iterator it) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->begin(), it);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::size_type
			sl_type_only<Tp>::index_of(const_iterator it) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->cbegin(), it);
			}


		//===================
		// insert

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_push_front_using_allocator(NodeAllocator & alloc, const_reference val)
			{
				this->k_emplace_front_using_allocator(alloc, val);
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_push_front_using_allocator(NodeAllocator & alloc, rvalue_reference val)
			{
				this->k_emplace_front_using_allocator(alloc, kerbal::compatibility::move(val));
			}

#		endif

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::reference
			sl_type_only<Tp>::k_emplace_front_using_allocator(NodeAllocator & alloc, Args&& ... args)
			{
				node *p = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				this->k_hook_node(this->basic_begin(), p);
				return p->member();
			}

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename sl_type_only<Tp>::reference \
			sl_type_only<Tp>::k_emplace_front_using_allocator(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				node *p = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				this->k_hook_node(this->basic_begin(), p); \
				return p->member(); \
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

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_push_back_using_allocator(NodeAllocator & alloc, const_reference val)
			{
				this->k_emplace_back_using_allocator(alloc, val);
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_push_back_using_allocator(NodeAllocator & alloc, rvalue_reference val)
			{
				this->k_emplace_back_using_allocator(alloc, kerbal::compatibility::move(val));
			}

#		endif

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::reference
			sl_type_only<Tp>::k_emplace_back_using_allocator(NodeAllocator & alloc, Args&& ... args)
			{
				node *p = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				this->k_hook_node_back(p);
				return p->member();
			}

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename sl_type_only<Tp>::reference \
			sl_type_only<Tp>::k_emplace_back_using_allocator(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				node *p = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				this->k_hook_node_back(p); \
				return p->member(); \
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

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::iterator
			sl_type_only<Tp>::k_insert_using_allocator(NodeAllocator & alloc, const_iterator pos, const_reference val)
			{
				return this->k_emplace_using_allocator(alloc, pos, val);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::iterator
			sl_type_only<Tp>::k_insert_using_allocator(NodeAllocator & alloc, const_iterator pos, size_type n, const_reference val)
			{
				if (n == 0) {
					return pos.cast_to_mutable();
				}
				sl_node_chain<Tp> chain(k_build_n_new_nodes_unguarded(alloc, n, val));
				this->k_hook_node(pos, chain.start, chain.back);
				return pos.cast_to_mutable();
			}

			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					typename sl_type_only<Tp>::iterator
			>::type
			sl_type_only<Tp>::k_insert_using_allocator(NodeAllocator & alloc, const_iterator pos, InputIterator first, InputIterator last)
			{
				if (first == last) {
					return pos.cast_to_mutable();
				}
				sl_node_chain<Tp> chain(k_build_new_nodes_range_unguarded(alloc, first, last));
				this->k_hook_node(pos, chain.start, chain.back);
				return pos.cast_to_mutable();
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::iterator
			sl_type_only<Tp>::k_insert_using_allocator(NodeAllocator & alloc, const_iterator pos, rvalue_reference val)
			{
				return this->k_emplace_using_allocator(alloc, pos, kerbal::compatibility::move(val));
			}

#		endif

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::iterator
			sl_type_only<Tp>::k_emplace_using_allocator(NodeAllocator & alloc, const_iterator pos, Args&& ... args)
			{
				node *p = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				this->k_hook_node(pos, p);
				return pos.cast_to_mutable();
			}

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename sl_type_only<Tp>::iterator \
			sl_type_only<Tp>::k_emplace_using_allocator(NodeAllocator & alloc, const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				node *p = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				this->k_hook_node(pos, p); \
				return pos.cast_to_mutable(); \
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

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_pop_front_using_allocator(NodeAllocator & alloc)
			{
				this->k_erase_using_allocator(alloc, this->cbegin());
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::iterator
			sl_type_only<Tp>::k_erase_using_allocator(NodeAllocator & alloc, const_iterator pos)
			{
				iterator pos_mut(pos.cast_to_mutable());
				node_base * p = this->k_unhook_node(pos_mut);
				k_destroy_node(alloc, p);
				return pos_mut;
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::iterator
			sl_type_only<Tp>::k_erase_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last)
			{
				iterator first_mut(first.cast_to_mutable());
				iterator last_mut(last.cast_to_mutable());
				if (first != last) {
					sl_node_base_chain chain(this->k_unhook_node(first_mut, last_mut));
					chain.back->next = NULL;
					k_consecutive_destroy_node(alloc, chain.start);
				}
				return first_mut;
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_clear_using_allocator(NodeAllocator & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::utility::declthis<sl_type_only>()->k_consecutive_destroy_node(
										alloc,
										kerbal::utility::declthis<sl_type_only>()->k_head.next
								))
						)
			{
				k_consecutive_destroy_node(alloc, this->k_head.next);
				this->k_init_node_base();
			}


		//===================
		// operation

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_resize_using_allocator(NodeAllocator & alloc, size_type count)
			{
				const_iterator it(this->cbegin());
				const_iterator const cend(this->cend());
				size_type size(kerbal::iterator::advance_at_most(it, count, cend));
				if (size == count) {
					this->k_erase_using_allocator(alloc, it, cend);
				} else {
					// note: count - size != 0
					sl_node_chain<Tp> chain(k_build_n_new_nodes_unguarded(alloc, count - size));
					this->k_hook_node(cend, chain.start, chain.back);
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_resize_using_allocator(NodeAllocator & alloc, size_type count, const_reference value)
			{
				const_iterator it(this->cbegin());
				const_iterator const cend(this->cend());
				size_type size(kerbal::iterator::advance_at_most(it, count, cend));
				if (size == count) {
					this->k_erase_using_allocator(alloc, it, cend);
				} else {
					this->k_insert_using_allocator(alloc, cend, count - size, value);
				}
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::iter_swap(iterator a, iterator b) KERBAL_NOEXCEPT
			{
				sl_type_unrelated::k_iter_swap(a, b);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::reverse(iterator first, iterator last) KERBAL_NOEXCEPT
			{
				sl_type_unrelated::k_reverse(first, last);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::size_type
			sl_type_only<Tp>::k_remove_using_allocator(NodeAllocator & alloc, const_reference val)
			{
				return k_remove_using_allocator(alloc, this->cbegin(), this->cend(), val);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::size_type
			sl_type_only<Tp>::k_remove_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, const_reference val)
			{
				return k_remove_if_using_allocator(alloc, first, last, remove_predict(val));
			}

			template <typename Tp>
			template <typename NodeAllocator, typename UnaryPredicate>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::size_type
			sl_type_only<Tp>::k_remove_if_using_allocator(NodeAllocator & alloc, UnaryPredicate predicate)
			{
				return k_remove_if_using_allocator(alloc, this->cbegin(), this->cend(), predicate);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename UnaryPredicate>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::size_type
			sl_type_only<Tp>::k_remove_if_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last,  UnaryPredicate predicate)
			{
				size_type i = 0;
				while (first != last) {
					if (predicate(*first)) {
						first = this->k_erase_using_allocator(alloc, first);
						++i;
					} else {
						++first;
					}
				}
				return i;
			}


		//===================
		// private

#	if __cplusplus >= 201103L

#		if __cpp_exceptions

			template <typename Tp>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					!nothrow_while_construct,
					typename sl_type_only<Tp>::node*
			>::type
			sl_type_only<Tp>::k_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
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

			template <typename Tp>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					nothrow_while_construct,
					typename sl_type_only<Tp>::node*
			>::type
			sl_type_only<Tp>::k_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::memory::allocator_traits<NodeAllocator>::allocate_one(alloc))
					)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate_one(alloc);
				node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				return p;
			}

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::node*
			sl_type_only<Tp>::k_build_new_node(NodeAllocator & alloc, Args&& ... args)
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

#		else // __cpp_exceptions

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename sl_type_only<Tp>::node*
			sl_type_only<Tp>::k_build_new_node(NodeAllocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate_one(alloc);
				if (p == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
				node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				return p;
			}

#		endif // __cpp_exceptions

#	else // __cplusplus >= 201103L

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	if __cpp_exceptions
#		define FBODY(i) \
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename sl_type_only<Tp>::node* \
			sl_type_only<Tp>::k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
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
#	else // __cpp_exceptions
#		define FBODY(i) \
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename sl_type_only<Tp>::node* \
			sl_type_only<Tp>::k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
				node * p = node_allocator_traits::allocate_one(alloc); \
				if (p == NULL) { \
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception(); \
				} \
				node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				return p; \
			}
#	endif // __cpp_exceptions

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

			template <typename Tp>
			template <typename NodeAllocator, typename... Args>
			KERBAL_CONSTEXPR20
			sl_node_chain<Tp>
			sl_type_only<Tp>::k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, Args&& ... args)
			{
				std::size_t cnt = 0;
				node * const start = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				node * back = start;
#		if __cpp_exceptions
				try {
#		endif // __cpp_exceptions
					++cnt;
					while (cnt != n) {
						node * new_node = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
						back->next = new_node;
						back = new_node;
						++cnt;
					}
					return sl_node_chain<Tp>(start, back);
#		if __cpp_exceptions
				} catch (...) {
					k_consecutive_destroy_node(alloc, start);
					throw;
				}
#		endif // __cpp_exceptions
			}

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	if __cpp_exceptions
#		define FBODY(i) \
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			sl_node_chain<Tp> \
			sl_type_only<Tp>::k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				std::size_t cnt = 0; \
				node * const start = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				node * back = start; \
				try { \
					++cnt; \
					while (cnt != n) { \
						node * new_node = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
						back->next = new_node; \
						back = new_node; \
						++cnt; \
					} \
					return sl_node_chain<Tp>(start, back); \
				} catch (...) { \
					k_consecutive_destroy_node(alloc, start); \
					throw; \
				} \
			}
#	else // __cpp_exceptions
#		define FBODY(i) \
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			sl_node_chain<Tp> \
			sl_type_only<Tp>::k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				std::size_t cnt = 0; \
				node * const start = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				node * back = start; \
				++cnt; \
				while (cnt != n) { \
					node * new_node = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					back->next = new_node; \
					back = new_node; \
					++cnt; \
				} \
				return sl_node_chain<Tp>(start, back); \
			}
#	endif // __cpp_exceptions

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif


			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					sl_node_chain<Tp>
			>::type
			sl_type_only<Tp>::k_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last)
			{
				node * const start = k_build_new_node(alloc, *first);
				node * back = start;
#			if __cpp_exceptions
				try {
#			endif // __cpp_exceptions
					++first;
					while (first != last) {
						node* new_node = k_build_new_node(alloc, *first);
						back->next = new_node;
						back = new_node;
						++first;
					}
					return sl_node_chain<Tp>(start, back);
#			if __cpp_exceptions
				} catch (...) {
					k_consecutive_destroy_node(alloc, start);
					throw;
				}
#			endif // __cpp_exceptions
			}


			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_destroy_node(NodeAllocator & alloc, node_base* p_node_base)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::memory::allocator_traits<NodeAllocator>::destroy(alloc, kerbal::utility::declval<node*>())) &&
						noexcept(kerbal::memory::allocator_traits<NodeAllocator>::deallocate_one(alloc, kerbal::utility::declval<node*>()))
					)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p_node = &p_node_base->template reinterpret_as<Tp>();
				node_allocator_traits::destroy(alloc, p_node);
				node_allocator_traits::deallocate_one(alloc, p_node);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * start, CNSCTV_DES_VER_DEFAULT)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<sl_type_only>()->k_destroy_node(alloc, kerbal::utility::declval<node_base *>()))
					)
			{
				node_base * current_node_base = start;
				while (current_node_base != NULL) {
					node_base * next = current_node_base->next;
					k_destroy_node(alloc, current_node_base);
					current_node_base = next;
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::allocator_traits<NodeAllocator>::destroy(alloc, kerbal::utility::declval<node*>()))
					)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;

				node_base * current_node_base = start;
				while (current_node_base != NULL) {
					node_base * next = current_node_base->next;
					node * p_node = &current_node_base->template reinterpret_as<Tp>();
					node_allocator_traits::destroy(alloc, p_node);
					current_node_base = next;
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_consecutive_destroy_node_impl(NodeAllocator & /*alloc*/, node_base * /*start*/, CNSCTV_DES_VER_NO_DESTROY) KERBAL_NOEXCEPT
			{
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_consecutive_destroy_node(NodeAllocator & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT()))
					)
			{
				k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT());
			}

			template <typename Tp>
			template <typename T, typename UpstreamAllocator>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_consecutive_destroy_node(kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & alloc, node_base * start)
			{
				typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::tribool_is_true<kerbal::type_traits::try_test_is_trivially_destructible<Tp> >::value,
						CNSCTV_DES_VER_NO_DESTROY,
						CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE
				>::type VER;
				k_consecutive_destroy_node_impl(alloc, start, VER());
			}

#		if __cplusplus >= 201703L
#			if __has_include(<memory_resource>)

			template <typename Tp>
			template <typename Node>
			KERBAL_CONSTEXPR20
			void sl_type_only<Tp>::k_consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
						(
							!kerbal::type_traits::tribool_is_true<kerbal::type_traits::try_test_is_trivially_destructible<Tp> >::value ?
							noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE())) :
							true
						) &&
						noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT()))
					)
			{
				if (typeid(*alloc.resource()) == typeid(std::pmr::monotonic_buffer_resource)) {
					if constexpr (!kerbal::type_traits::tribool_is_true<kerbal::type_traits::try_test_is_trivially_destructible<Tp> >::value) {
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


#endif // KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_BASE_IMPL_HPP
