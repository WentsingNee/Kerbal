/**
 * @file       forward_list_base.impl.hpp
 * @brief
 * @date       2021-01-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_FORWARD_LIST_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_FORWARD_LIST_BASE_IMPL_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compare/basic_compare.hpp>
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

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <kerbal/type_traits/is_trivially_destructible.hpp>
#		include <memory_resource>
#	endif
#endif

#include <kerbal/container/detail/forward_list_base/forward_list_base.decl.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

		//===================
		//===================
		// fl_type_unrelated

		//===================
		// capacity

			KERBAL_CONSTEXPR14
			inline
			bool fl_type_unrelated::empty() const KERBAL_NOEXCEPT
			{
				return this->k_head.next == NULL;
			}

			KERBAL_CONSTEXPR14
			inline
			fl_type_unrelated::size_type
			fl_type_unrelated::size() const KERBAL_NOEXCEPT
			{
				basic_const_iterator first(this->basic_cbegin());
				basic_const_iterator const cend(this->basic_cend());
				basic_iterator::difference_type sz = 0;
				while (first != cend) {
					++first;
					++sz;
				}
				return sz;
			}


		//===================
		// operation

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::k_iter_swap_after(basic_const_iterator a, basic_const_iterator b) KERBAL_NOEXCEPT
			{
				basic_iterator a_mut(a.cast_to_mutable());
				basic_iterator b_mut(b.cast_to_mutable());
				kerbal::algorithm::swap(a_mut.current->next, b_mut.current->next);
				node_base * a_after = a_mut.current->next;
				node_base * b_after = b_mut.current->next;
				kerbal::algorithm::swap(a_after->next, b_after->next);
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::k_reverse_after(basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				basic_iterator it(first.cast_to_mutable()); ++it;
				basic_iterator next(it);
				basic_iterator end(last.cast_to_mutable());
				while (it != last) {
					++next;
					it.current->next = end.current;
					end = it;
					it = next;
				}
				first.cast_to_mutable().current->next = end.current;
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::reverse() KERBAL_NOEXCEPT
			{
				k_reverse_after(this->basic_cbefore_begin(), this->basic_cend());
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::k_splice_after(basic_const_iterator pos, fl_type_unrelated & other) KERBAL_NOEXCEPT
			{
				k_splice_after(pos, other.basic_cbefore_begin(), other.basic_cend());
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::k_splice_after(basic_const_iterator pos, basic_const_iterator opos) KERBAL_NOEXCEPT
			{
				node_base * p = k_unhook_node_after(opos);
				k_hook_node_after(pos, p);
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::k_splice_after(basic_const_iterator pos, basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				basic_const_iterator back(first);
				if (back.current->next != last.current) {
					++back;
					while (back.current->next != last.current) {
						++back;
					}
					node_base * start = k_unhook_node_after(first, last);
					k_hook_node_after(pos, start, back.cast_to_mutable().current);
				}
			}


		//===================
		// private

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::k_hook_node_after(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				p->next = pos_mut.current->next;
				pos_mut.current->next = p;
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::k_hook_node_after(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				back->next = pos_mut.current->next;
				pos_mut.current->next = start;
			}

			KERBAL_CONSTEXPR14
			inline
			fl_type_unrelated::node_base *
			fl_type_unrelated::k_unhook_node_after(basic_const_iterator pos) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				node_base * current = pos_mut.current;
				node_base * after = current->next;
				current->next = after->next;
				return after;
			}

			// pre-cond: first != last;
			KERBAL_CONSTEXPR14
			inline
			fl_type_unrelated::node_base *
			fl_type_unrelated::k_unhook_node_after(basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				basic_iterator first_mut(first.cast_to_mutable());
				basic_iterator last_mut(last.cast_to_mutable());
				node_base * ret = first_mut.current->next;
				first_mut.current->next = last_mut.current;
				return ret;
			}

			// pre-cond: lhs and rhs are lists of same type
			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::k_swap_type_unrelated(fl_type_unrelated & lhs, fl_type_unrelated & rhs) KERBAL_NOEXCEPT
			{
				kerbal::algorithm::swap(lhs.k_head.next, rhs.k_head.next);
			}


		//===================
		//===================
		// fl_type_only

#	if __cplusplus >= 201103L

			// pre-cond: allocator allows
			template <typename Tp>
			KERBAL_CONSTEXPR14
			fl_type_only<Tp>::fl_type_only(fl_type_only && src) KERBAL_NOEXCEPT :
					fl_type_unrelated(static_cast<fl_type_unrelated&&>(src))
			{
			}

			// move construct using allocator, allocator is equal
			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_move_cnstrct_ua_ae(fl_type_only && src) KERBAL_NOEXCEPT
			{
				fl_type_unrelated::k_swap_type_unrelated(
						static_cast<fl_type_unrelated &>(src),
						static_cast<fl_type_unrelated &>(*this));
			}

			// move construct using allocator, allocator is not equal
			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_move_cnstrct_ua_ane(NodeAllocator & this_alloc, fl_type_only && src)
			{
				if (src.empty()) {
					return;
				}
				sl_node_chain<Tp> chain(
						k_build_new_nodes_range_unguarded(
								this_alloc,
								kerbal::iterator::make_move_iterator(src.begin()),
								kerbal::iterator::make_move_iterator(src.end())));
				fl_type_unrelated::k_hook_node_after(this->basic_before_begin(), chain.start, chain.back);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_move_cnstrct_ua_helper(NodeAllocator & this_alloc, NodeAllocator && src_alloc, fl_type_only && src,
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
			void fl_type_only<Tp>::k_move_cnstrct_ua_helper(NodeAllocator & /*this_alloc*/, NodeAllocator && /*src_alloc*/, fl_type_only && src,
																	   kerbal::type_traits::true_type /*is_always_equal*/) KERBAL_NOEXCEPT
			{
				this->k_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR14
			fl_type_only<Tp>::fl_type_only(NodeAllocator & this_alloc, NodeAllocator && src_alloc, fl_type_only && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_constructible_using_allocator<NodeAllocator>::value) :
					fl_type_unrelated()
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> allocator_traits;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				this->k_move_cnstrct_ua_helper(this_alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src), is_always_equal());
			}

#	endif

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			fl_type_only<Tp>::fl_type_only(NodeAllocator & alloc, size_type n) :
					fl_type_unrelated()
			{
				if (n == 0) {
					return;
				}
				sl_node_chain<Tp> chain(k_build_n_new_nodes_unguarded(alloc, n));
				k_hook_node_after(this->basic_cbefore_begin(), chain.start, chain.back);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			fl_type_only<Tp>::fl_type_only(NodeAllocator & alloc, size_type n, const_reference val) :
					fl_type_unrelated()
			{
				if (n == 0) {
					return;
				}
				sl_node_chain<Tp> chain(k_build_n_new_nodes_unguarded(alloc, n, val));
				k_hook_node_after(this->basic_cbefore_begin(), chain.start, chain.back);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			fl_type_only<Tp>::fl_type_only(NodeAllocator & alloc, InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value, int
					>::type) :
					fl_type_unrelated()
			{
				k_insert_after_using_allocator(alloc, this->cbefore_begin(), first, last);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_destroy_using_allocator(NodeAllocator & alloc) KERBAL_NOEXCEPT
			{
				this->k_consecutive_destroy_node(alloc, this->k_head.next, NULL);
			}


		//===================
		// assign

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_assign_using_allocator(NodeAllocator & alloc, size_type count, const_reference val)
			{
				const_iterator before_it(this->before_begin());
				iterator it(this->begin());
				const_iterator const cend(this->cend());
				while (count != 0) {
					if (it != cend) {
						kerbal::assign::generic_assign(*it, val); // *it = val;
						--count;
						before_it = it;
						++it;
					} else {
						k_insert_after_using_allocator(alloc, before_it, count, val);
						return;
					}
				}
				k_erase_after_using_allocator(alloc, before_it, cend);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
			>::type
			fl_type_only<Tp>::k_assign_using_allocator(NodeAllocator & alloc, InputIterator first, InputIterator last)
			{
				iterator before_it(this->before_begin());
				iterator it(this->begin());
				const_iterator const cend(this->cend());
				while (first != last) {
					if (it != cend) {
						kerbal::assign::generic_assign(*it, *first); // *it = *first;
						++first;
						before_it = it;
						++it;
					} else {
						k_insert_after_using_allocator(alloc, before_it, first, last);
						return;
					}
				}
				k_erase_after_using_allocator(alloc, before_it, cend);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & src_alloc, const fl_type_only & src, CPYASS_VER_NOT_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_destroy_using_allocator(alloc);
					this->k_head.next = NULL;
				}
				this->k_assign_using_allocator(alloc, src.cbegin(), src.cend());
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & src_alloc, const fl_type_only & src, CPYASS_VER_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_destroy_using_allocator(alloc);
					this->k_head.next = NULL;
				}
				alloc = src_alloc;
				this->k_assign_using_allocator(alloc, src.cbegin(), src.cend());
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & /*src_alloc*/, const fl_type_only & src, CPYASS_VER_ALWAYS_EQUAL)
			{
				this->k_assign_using_allocator(alloc, src.cbegin(), src.cend());
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_assign_using_allocator(NodeAllocator & alloc, const NodeAllocator & src_alloc, const fl_type_only & src)
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
			void fl_type_only<Tp>::k_move_assign(NodeAllocator & alloc, fl_type_only && src) KERBAL_NOEXCEPT
			{
				this->k_destroy_using_allocator(alloc);
				this->k_head.next = NULL;
				fl_type_unrelated::k_swap_type_unrelated(static_cast<fl_type_unrelated &>(src), static_cast<fl_type_unrelated &>(*this));
			}

			// move assign using allocator, allocator is equal
			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_mov_ass_ua_ae(NodeAllocator & alloc, fl_type_only && src) KERBAL_NOEXCEPT
			{
				this->k_move_assign(alloc, kerbal::compatibility::move(src));
			}

			// move assign using allocator, allocator is not equal
			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_mov_ass_ua_ane(NodeAllocator & alloc, fl_type_only && src)
			{
				this->k_assign_using_allocator(
						alloc,
						kerbal::iterator::make_move_iterator(src.begin()),
						kerbal::iterator::make_move_iterator(src.end()));
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && src_alloc, fl_type_only && src,
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
			void fl_type_only<Tp>::k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && src_alloc, fl_type_only && src,
																MOVASS_VER_PROPAGATE)
			{
				this->k_destroy_using_allocator(alloc);
				this->k_head.next = NULL;
				alloc = kerbal::compatibility::move(src_alloc);
				fl_type_unrelated::k_swap_type_unrelated(static_cast<fl_type_unrelated &>(src), static_cast<fl_type_unrelated &>(*this));
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && /*src_alloc*/, fl_type_only && src,
																MOVASS_VER_ALWAYS_EQUAL) KERBAL_NOEXCEPT
			{
				this->k_mov_ass_ua_ae(alloc, kerbal::compatibility::move(src));
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_assign_using_allocator(NodeAllocator & alloc, NodeAllocator && src_alloc, fl_type_only && src)
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
		// iterator

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::before_begin() KERBAL_NOEXCEPT
			{
				return iterator(&this->k_head);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::before_begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->k_head);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::cbefore_begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->k_head);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::begin() KERBAL_NOEXCEPT
			{
				return iterator(this->k_head.next);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_head.next);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_head.next);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::end() KERBAL_NOEXCEPT
			{
				return iterator(NULL);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::end() const KERBAL_NOEXCEPT
			{
				return const_iterator(NULL);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(NULL);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::nth(size_type index) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->begin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::nth(size_type index) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->cbegin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::index_of(iterator it) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->begin(), it);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::index_of(const_iterator it) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->cbegin(), it);
			}


		//===================
		// element access

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::reference
			fl_type_only<Tp>::front() KERBAL_NOEXCEPT
			{
				return this->k_head.next->template reinterpret_as<Tp>().member();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_reference
			fl_type_only<Tp>::front() const KERBAL_NOEXCEPT
			{
				return this->k_head.next->template reinterpret_as<Tp>().member();
			}


		//===================
		// insert

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_push_front_using_allocator(NodeAllocator & alloc, const_reference val)
			{
				this->k_emplace_front_using_allocator(alloc, val);
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_push_front_using_allocator(NodeAllocator & alloc, rvalue_reference val)
			{
				this->k_emplace_front_using_allocator(alloc, kerbal::compatibility::move(val));
			}

#		endif

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::reference
			fl_type_only<Tp>::k_emplace_front_using_allocator(NodeAllocator & alloc, Args&& ... args)
			{
				node *p = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				fl_type_unrelated::k_hook_node_after(this->basic_cbefore_begin(), p);
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
			typename fl_type_only<Tp>::reference \
			fl_type_only<Tp>::k_emplace_front_using_allocator(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				node *p = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				fl_type_unrelated::k_hook_node_after(this->basic_cbefore_begin(), p); \
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
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::k_insert_after_using_allocator(NodeAllocator & alloc, const_iterator pos, const_reference val)
			{
				return k_emplace_after_using_allocator(alloc, pos, val);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::k_insert_after_using_allocator(NodeAllocator & alloc, const_iterator pos, size_type n, const_reference val)
			{
				if (n == 0) {
					return pos.cast_to_mutable();
				}
				sl_node_chain<Tp> chain(k_build_n_new_nodes_unguarded(alloc, n, val));
				fl_type_unrelated::k_hook_node_after(pos, chain.start, chain.back);
				return iterator(chain.back);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					typename fl_type_only<Tp>::iterator
			>::type
			fl_type_only<Tp>::k_insert_after_using_allocator(NodeAllocator & alloc, const_iterator pos, InputIterator first, InputIterator last)
			{
				if (first == last) {
					return pos.cast_to_mutable();
				}
				sl_node_chain<Tp> chain(k_build_new_nodes_range_unguarded(alloc, first, last));
				fl_type_unrelated::k_hook_node_after(pos, chain.start, chain.back);
				return iterator(chain.back);
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::k_insert_after_using_allocator(NodeAllocator & alloc, const_iterator pos, rvalue_reference val)
			{
				return k_emplace_after_using_allocator(alloc, pos, kerbal::compatibility::move(val));
			}

#		endif

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::k_emplace_after_using_allocator(NodeAllocator & alloc, const_iterator pos, Args&& ... args)
			{
				node *p = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				fl_type_unrelated::k_hook_node_after(pos, p);
				return iterator(p);
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
			typename fl_type_only<Tp>::iterator \
			fl_type_only<Tp>::k_emplace_after_using_allocator(NodeAllocator & alloc, const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				node *p = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				fl_type_unrelated::k_hook_node_after(pos, p); \
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

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_pop_front_using_allocator(NodeAllocator & alloc)
			{
				k_erase_after_using_allocator(alloc, this->cbefore_begin());
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::k_erase_after_using_allocator(NodeAllocator & alloc, const_iterator pos)
			{
				iterator pos_mut(pos.cast_to_mutable());
				node_base * p = fl_type_unrelated::k_unhook_node_after(pos_mut);
				k_destroy_node(alloc, p);
				return ++pos_mut;
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::iterator
			fl_type_only<Tp>::k_erase_after_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last)
			{
				iterator first_mut(first.cast_to_mutable());
				iterator last_mut(last.cast_to_mutable());
				if (first != last) {
					node_base * first = fl_type_unrelated::k_unhook_node_after(first_mut, last_mut);
					node_base * last = last_mut.current;
					k_consecutive_destroy_node(alloc, first, last);
				}
				return ++first_mut;
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_clear_using_allocator(NodeAllocator & alloc)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<fl_type_only>()->k_consecutive_destroy_node(
									alloc,
									kerbal::utility::declthis<fl_type_only>()->k_head.next,
									NULL
							))
					)
			{
				k_consecutive_destroy_node(alloc, this->k_head.next, NULL);
				this->k_head.next = NULL;
			}


		//===================
		// operation

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_resize_using_allocator(NodeAllocator & alloc, size_type count)
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
						sl_node_chain<Tp> chain(k_build_n_new_nodes_unguarded(alloc, count));
						fl_type_unrelated::k_hook_node_after(before_it, chain.start, chain.back);
						return;
					}
				}
				k_erase_after_using_allocator(alloc, before_it, cend);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_resize_using_allocator(NodeAllocator & alloc, size_type count, const_reference value)
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
						sl_node_chain<Tp> chain(k_build_n_new_nodes_unguarded(alloc, count, value));
						fl_type_unrelated::k_hook_node_after(before_it, chain.start, chain.back);
						return;
					}
				}
				k_erase_after_using_allocator(alloc, before_it, cend);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_iter_swap_after(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
			{
				fl_type_unrelated::k_iter_swap_after(a, b);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_reverse_after(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
			{
				fl_type_unrelated::k_reverse_after(first, last);
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_merge_impl(fl_type_only & other, BinaryPredict cmp, MERGE_VER_NOTHROW) KERBAL_NOEXCEPT
			{
				const_iterator it_other(other.cbegin());
				const_iterator it_this_before(this->cbefore_begin());
				const_iterator it_this(this->cbegin());
				const_iterator const cend(NULL);

				while (it_other != cend) {
					if (it_this != cend) {
						if (cmp(*it_other, *it_this)) {
							fl_type_unrelated::k_hook_node_after(it_this_before, it_other++.cast_to_mutable().current);
							++it_this_before;
						} else {
							it_this_before = it_this;
							++it_this;
						}
					} else {
						it_this_before.cast_to_mutable().current->next = it_other.cast_to_mutable().current;
						break;
					}
				}
				other.k_head.next = NULL;
			}

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_merge_impl(fl_type_only & other, BinaryPredict cmp, MERGE_VER_MAY_THROW)
			{
				const_iterator it_other(other.cbegin());
				const_iterator it_this_before(this->cbefore_begin());
				const_iterator it_this(this->cbegin());
				const_iterator const cend(NULL);

				try {
					while (it_other != cend) {
						if (it_this != cend) {
							if (cmp(*it_other, *it_this)) {
								fl_type_unrelated::k_hook_node_after(it_this_before, it_other++.cast_to_mutable().current);
								++it_this_before;
							} else {
								it_this_before = it_this;
								++it_this;
							}
						} else {
							it_this_before.cast_to_mutable().current->next = it_other.cast_to_mutable().current;
							break;
						}
					}
				} catch (...) {
					other.k_head.next = it_other.cast_to_mutable().current;
					throw;
				}
				other.k_head.next = NULL;
			}

#		endif

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_merge(fl_type_only & other, BinaryPredict cmp)
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

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_merge(fl_type_only & other)
			{
				this->k_merge(other, kerbal::compare::less<value_type>());
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::k_merge_sort_merge_after_impl(const_iterator before_first, const_iterator before_mid, const_iterator before_last, BinaryPredict cmp, MSM_VER_NOTHROW)
			{
				const_iterator mid(before_mid); ++mid;
				const_iterator last(before_last); ++last;
				const_iterator before_i(before_first);
				const_iterator i(before_i); ++i;
				const_iterator j(mid);

				while (i != mid) {
					if (j != last) {
						if (cmp(*j, *i)) {
							fl_type_unrelated::k_hook_node_after(before_i, j++.cast_to_mutable().current);
							++before_i;
						} else {
							before_i = i;
							++i;
						}
					} else {
						before_mid.cast_to_mutable().current->next = last.cast_to_mutable().current;
						return before_mid;
					}
				}
				before_mid.cast_to_mutable().current->next = j.cast_to_mutable().current;
				return before_last;
			}

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::k_merge_sort_merge_after_impl(const_iterator before_first, const_iterator before_mid, const_iterator before_last, BinaryPredict cmp, MSM_VER_MAY_THROW)
			{
				const_iterator mid(before_mid); ++mid;
				const_iterator last(before_last); ++last;
				const_iterator before_i(before_first);
				const_iterator i(before_i); ++i;
				const_iterator j(mid);

				try {
					while (i != mid) {
						if (j != last) {
							if (cmp(*j, *i)) {
								fl_type_unrelated::k_hook_node_after(before_i, j++.cast_to_mutable().current);
								++before_i;
							} else {
								before_i = i;
								++i;
							}
						} else {
							before_mid.cast_to_mutable().current->next = last.cast_to_mutable().current;
							return before_mid;
						}
					}
				} catch (...) {
					before_mid.cast_to_mutable().current->next = j.cast_to_mutable().current;
					throw;
				}
				before_mid.cast_to_mutable().current->next = j.cast_to_mutable().current;
				return before_last;
			}

#		endif

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::k_merge_sort_merge_after(const_iterator before_first, const_iterator before_mid, const_iterator before_last, BinaryPredict cmp)
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

				return k_merge_sort_merge_after_impl(before_first, before_mid, before_last, cmp, MSM_VERSION());

			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			typename fl_type_only<Tp>::const_iterator
			fl_type_only<Tp>::k_merge_sort_n_after(const_iterator before_first, size_type n, BinaryPredict cmp)
			{
				if (n == 0) {
					return before_first;
				}
				if (n == 1) {
					++before_first;
					return before_first;
				}
				if (n == 2) {
					const_iterator a(before_first); ++a;
					const_iterator b(a); ++b;
					if (cmp(*b, *a)) {
						iterator first_mut(before_first.cast_to_mutable());
						iterator a_mut(a.cast_to_mutable());
						iterator b_mut(b.cast_to_mutable());
						a_mut.current->next = b_mut.current->next;
						b_mut.current->next = a_mut.current;
						first_mut.current->next = b_mut.current;
						return a;
					} else {
						return b;
					}
				}

				size_type first_len(n / 2);
				const_iterator before_mid(k_merge_sort_n_after(before_first, first_len, cmp));
				const_iterator before_last(k_merge_sort_n_after(before_mid, n - first_len, cmp));
				return k_merge_sort_merge_after(before_first, before_mid, before_last, cmp);
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_merge_sort_after(const_iterator first, const_iterator last, BinaryPredict cmp)
			{
				k_merge_sort_n_after(first, kerbal::iterator::distance(first, last) - 1, cmp);
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_sort_after(const_iterator first, const_iterator last, BinaryPredict cmp)
			{
				k_merge_sort_after(first, last, cmp);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_sort_after(const_iterator first, const_iterator last)
			{
				k_sort_after(first, last, kerbal::compare::less<value_type>());
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_sort(BinaryPredict cmp)
			{
				k_sort_after(this->cbefore_begin(), this->cend(), cmp);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_type_only<Tp>::k_sort()
			{
				k_sort(kerbal::compare::less<value_type>());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename UnaryPredicate>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::k_remove_after_if_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, UnaryPredicate predicate)
			{
				size_type cnt = 0;
				const_iterator before_first(first);
				++first;
				while (first != last) {
					if (predicate(*first)) {
						++first;
						k_erase_after_using_allocator(alloc, before_first);
						++cnt;
					} else {
						before_first = first;
						++first;
					}
				}
				return cnt;
			}

			template <typename Tp>
			template <typename NodeAllocator, typename UnaryPredicate>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::k_remove_if_using_allocator(NodeAllocator & alloc, UnaryPredicate predicate)
			{
				return k_remove_after_if_using_allocator(alloc, this->cbefore_begin(), this->cend(), predicate);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::k_remove_after_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, const_reference val)
			{
				return k_remove_after_if_using_allocator(alloc, first, last, remove_predict(val));
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::k_remove_using_allocator(NodeAllocator & alloc, const_reference val)
			{
				return k_remove_after_using_allocator(alloc, this->cbefore_begin(), this->cend(), val);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::k_unique_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, BinaryPredict equal_to)
			{
				size_type cnt = 0;
				if (first != last) {
					const_iterator forward(first); ++forward;
					while (forward != last) {
						if (equal_to(*first, *forward)) {
							++forward;
							k_destroy_node(alloc, fl_type_unrelated::k_unhook_node_after(first));
							++cnt;
						} else {
							first = forward;
							++forward;
						}
					}
				}
				return cnt;
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::k_unique_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last)
			{
				return k_unique_using_allocator(alloc, first, last, kerbal::compare::equal_to<value_type>());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::k_unique_using_allocator(NodeAllocator & alloc, BinaryPredict equal_to)
			{
				return k_unique_using_allocator(alloc, this->cbegin(), this->cend(), equal_to);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::size_type
			fl_type_only<Tp>::k_unique_using_allocator(NodeAllocator & alloc)
			{
				return this->k_unique_using_allocator(alloc, kerbal::compare::equal_to<value_type>());
			}


		//===================
		// private

#	if __cplusplus >= 201103L

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename Tp>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					!nothrow_while_construct,
					typename fl_type_only<Tp>::node*
			>::type
			fl_type_only<Tp>::k_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
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
					typename fl_type_only<Tp>::node*
			>::type
			fl_type_only<Tp>::k_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
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
			typename fl_type_only<Tp>::node*
			fl_type_only<Tp>::k_build_new_node(NodeAllocator & alloc, Args&& ... args)
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

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename fl_type_only<Tp>::node*
			fl_type_only<Tp>::k_build_new_node(NodeAllocator & alloc, Args&& ... args)
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
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename fl_type_only<Tp>::node* \
			fl_type_only<Tp>::k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
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
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename fl_type_only<Tp>::node* \
			fl_type_only<Tp>::k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
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

			template <typename Tp>
			template <typename NodeAllocator, typename... Args>
			KERBAL_CONSTEXPR20
			sl_node_chain<Tp>
			fl_type_only<Tp>::k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, Args&& ... args)
			{
				--n;
				node * const start = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				node * back = start;
#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#		endif // KERBAL_HAS_EXCEPTIONS_SUPPORT
					while (n != 0) {
						node * new_node = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
						back->next = new_node;
						back = new_node;
						--n;
					}
					return sl_node_chain<Tp>(start, back);
#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_consecutive_destroy_node(alloc, start, NULL);
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
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			sl_node_chain<Tp> \
			fl_type_only<Tp>::k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				--n; \
				node * const start = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				node * back = start; \
				try { \
					while (n != 0) { \
						node * new_node = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
						back->next = new_node; \
						back = new_node; \
						--n; \
					} \
					return sl_node_chain<Tp>(start, back); \
				} catch (...) { \
					k_consecutive_destroy_node(alloc, start, NULL); \
					throw; \
				} \
			}
#	else // KERBAL_HAS_EXCEPTIONS_SUPPORT
#		define FBODY(i) \
			template <typename Tp> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			sl_node_chain<Tp> \
			fl_type_only<Tp>::k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				--n; \
				node * const start = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				node * back = start; \
				while (n != 0) { \
					node* new_node = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					back->next = new_node; \
					back = new_node; \
					--n; \
				} \
				return sl_node_chain<Tp>(start, back); \
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


			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					sl_node_chain<Tp>
			>::type
			fl_type_only<Tp>::k_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last)
			{
				node * const start = k_build_new_node(alloc, *first);
				node * back = start;
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif // KERBAL_HAS_EXCEPTIONS_SUPPORT
					++first;
					while (first != last) {
						node* new_node = k_build_new_node(alloc, *first);
						back->next = new_node;
						back = new_node;
						++first;
					}
					return sl_node_chain<Tp>(start, back);
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_consecutive_destroy_node(alloc, start, NULL);
					throw;
				}
#			endif // KERBAL_HAS_EXCEPTIONS_SUPPORT
			}


			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_destroy_node(NodeAllocator & alloc, node_base * p_node_base) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef typename node_allocator_traits::pointer allocator_pointer_type;

				node * p_node = &p_node_base->template reinterpret_as<value_type>();
				allocator_pointer_type p_node_act = static_cast<allocator_pointer_type>(p_node);
				node_allocator_traits::destroy(alloc, p_node_act);
				node_allocator_traits::deallocate_one(alloc, p_node_act);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * first, node_base * last, CNSCTV_DES_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				while (first != last) {
					node_base * next = first->next;
					k_destroy_node(alloc, first);
					first = next;
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * first, node_base * last, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef typename node_allocator_traits::pointer allocator_pointer_type;

				while (first != last) {
					node_base * next = first->next;
					node * p_node = &first->template reinterpret_as<value_type>();
					allocator_pointer_type p_node_act = static_cast<allocator_pointer_type>(p_node);
					node_allocator_traits::destroy(alloc, p_node_act);
					first = next;
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_consecutive_destroy_node_impl(NodeAllocator & /*alloc*/, node_base * /*first*/, node_base * /*last*/, CNSCTV_DES_VER_NO_DESTROY) KERBAL_NOEXCEPT
			{
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_consecutive_destroy_node(NodeAllocator & alloc, node_base * first, node_base * last) KERBAL_NOEXCEPT
			{
				k_consecutive_destroy_node_impl(alloc, first, last, CNSCTV_DES_VER_DEFAULT());
			}

			template <typename Tp>
			template <typename T, typename UpstreamAllocator>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_consecutive_destroy_node(kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & alloc, node_base * first, node_base * last) KERBAL_NOEXCEPT
			{
				typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<Tp>::IS_TRUE::value,
					CNSCTV_DES_VER_NO_DESTROY,
					CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE
				>::type VER;
				k_consecutive_destroy_node_impl(alloc, first, last, VER());
			}

#		if __cplusplus >= 201703L
#			if __has_include(<memory_resource>)

			template <typename Tp>
			template <typename Node>
			KERBAL_CONSTEXPR20
			void fl_type_only<Tp>::k_consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * first, node_base * last) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<std::pmr::polymorphic_allocator<Node> > node_allocator_traits;
				typedef typename node_allocator_traits::value_type real_value_type;

				if (typeid(*alloc.resource()) == typeid(std::pmr::monotonic_buffer_resource)) {
					if constexpr (!kerbal::type_traits::try_test_is_trivially_destructible<real_value_type>::IS_TRUE::value) {
						k_consecutive_destroy_node_impl(alloc, first, last, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE());
					}
				} else {
					k_consecutive_destroy_node_impl(alloc, first, last, CNSCTV_DES_VER_DEFAULT());
				}
			}

#			endif
#		endif


		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_FORWARD_LIST_BASE_IMPL_HPP
