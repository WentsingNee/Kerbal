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

#ifndef KERBAL_CONTAINER_IMPL_LIST_BASE_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_LIST_BASE_IMPL_HPP

#include <kerbal/container/detail/list_base.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/iterator/iterator.hpp>
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
			bool list_type_unrelated::empty() const KERBAL_NOEXCEPT
			{
				return this->basic_begin() == this->basic_end();
			}

			KERBAL_CONSTEXPR20
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
			//operation

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::iter_swap(basic_iterator a, basic_iterator b) KERBAL_NOEXCEPT
			{
				node_base * pa = a.current;
				node_base * pb = b.current;
				kerbal::algorithm::swap(pa->prev, pb->prev);
				kerbal::algorithm::swap(pa->prev->next, pb->prev->next);
				kerbal::algorithm::swap(pa->next, pb->next);
				kerbal::algorithm::swap(pa->next->prev, pb->next->prev);
			}

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::reverse(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT
			{
				node_base * pre_first = first.current->prev;
				node_base * rit = last.current;
				while (first != last) {
					node_base * p = first.current;
					++first;
					p->next = rit;
					rit->prev = p;
					rit = p;
				}
				rit->prev = pre_first;
				pre_first->next = rit;
			}

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::reverse() KERBAL_NOEXCEPT
			{
				reverse(this->basic_begin(), this->basic_end());
			}

			KERBAL_CONSTEXPR20
			inline
			list_type_unrelated::basic_iterator
			list_type_unrelated::rotate(basic_iterator first, basic_iterator n_first, basic_iterator last) KERBAL_NOEXCEPT
			{
				if (first == n_first) {
					return last;
				}

				if (n_first == last) {
					return first;
				}

				std::pair<node_base *, node_base *> left_range(__unhook_node(first, n_first));
				__hook_node(last, left_range.first, left_range.second);
				return first;
			}

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::splice(basic_const_iterator pos, list_type_unrelated & other) KERBAL_NOEXCEPT
			{
				list_type_unrelated::splice(pos, other.basic_begin(), other.basic_end());
			}

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::splice(basic_const_iterator pos, basic_const_iterator opos) KERBAL_NOEXCEPT
			{
				basic_iterator opos_mut(opos.cast_to_mutable());
				node_base * p = list_type_unrelated::__unhook_node(opos_mut);
				list_type_unrelated::__hook_node(pos, p);
			}

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::splice(basic_const_iterator pos, basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				if (first == last) {
					return;
				}

				std::pair<node_base *, node_base *> range(list_type_unrelated::__unhook_node(first.cast_to_mutable(), last.cast_to_mutable()));
				node_base * start = range.first;
				node_base * back = range.second;
				list_type_unrelated::__hook_node(pos, start, back);
			}

			//===================
			//private

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::__hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				node_base * next = pos_mut.current;
				p->prev = next->prev;
				p->next = next;
				next->prev->next = p;
				next->prev = p;
			}

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::__hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
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

			KERBAL_CONSTEXPR20
			inline
			list_type_unrelated::node_base *
			list_type_unrelated::__unhook_node(basic_iterator pos) KERBAL_NOEXCEPT
			{
				node_base * p = pos.current;
				p->prev->next = p->next;
				p->next->prev = p->prev;
				return p;
			}

			KERBAL_CONSTEXPR20
			inline
			std::pair<list_type_unrelated::node_base *, list_type_unrelated::node_base *>
			list_type_unrelated::__unhook_node(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT
			{
				node_base * start = first.current;
				node_base * prev = start->prev;
				node_base * end = last.current;
				node_base * back = end->prev;
				end->prev = prev;
				prev->next = end;
				return std::pair<node_base *, node_base *>(start, back);
			}

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::__swap_with_empty(list_type_unrelated& not_empty_list, list_type_unrelated& empty_list) KERBAL_NOEXCEPT
			{
				empty_list.head_node.prev = not_empty_list.head_node.prev;
				empty_list.head_node.prev->next = &empty_list.head_node;
				empty_list.head_node.next = not_empty_list.head_node.next;
				empty_list.head_node.next->prev = &empty_list.head_node;
				not_empty_list.__init_node_base();
			}

			KERBAL_CONSTEXPR20
			inline
			void list_type_unrelated::__swap_type_unrelated(list_type_unrelated & lhs, list_type_unrelated & rhs) KERBAL_NOEXCEPT
			{
				bool is_rhs_empty = rhs.empty();
				if (lhs.empty()) {
					if (!is_rhs_empty) {
						// lhs.empty() && !rhs.empty()
						__swap_with_empty(rhs, lhs);
					}
				} else {
					if (is_rhs_empty) {
						// !lhs.empty() and rhs.empty()
						__swap_with_empty(lhs, rhs);
					} else {
						// !lhs.empty() and !rhs.empty()
						kerbal::algorithm::swap(lhs.head_node.prev, rhs.head_node.prev);
						lhs.head_node.prev->next = &lhs.head_node;
						rhs.head_node.prev->next = &rhs.head_node;

						kerbal::algorithm::swap(lhs.head_node.next, rhs.head_node.next);
						lhs.head_node.next->prev = &lhs.head_node;
						rhs.head_node.next->prev = &rhs.head_node;
					}
				}
			}



			//===================
			//element access

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::reference
			list_allocator_unrelated<Tp>::front() KERBAL_NOEXCEPT
			{
				return this->head_node.next->template reinterpret_as<Tp>().value;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_reference
			list_allocator_unrelated<Tp>::front() const KERBAL_NOEXCEPT
			{
				return this->head_node.next->template reinterpret_as<Tp>().value;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::reference
			list_allocator_unrelated<Tp>::back() KERBAL_NOEXCEPT
			{
				return this->head_node.prev->template reinterpret_as<Tp>().value;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_reference
			list_allocator_unrelated<Tp>::back() const KERBAL_NOEXCEPT
			{
				return this->head_node.prev->template reinterpret_as<Tp>().value;
			}

			//===================
			//iterator

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::iterator
			list_allocator_unrelated<Tp>::begin() KERBAL_NOEXCEPT
			{
				return iterator(this->head_node.next);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::iterator
			list_allocator_unrelated<Tp>::end() KERBAL_NOEXCEPT
			{
				return iterator(&this->head_node);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_iterator
			list_allocator_unrelated<Tp>::begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->head_node.next);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_iterator
			list_allocator_unrelated<Tp>::end() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->head_node);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_iterator
			list_allocator_unrelated<Tp>::cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->head_node.next);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_iterator
			list_allocator_unrelated<Tp>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->head_node);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::reverse_iterator
			list_allocator_unrelated<Tp>::rbegin() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::reverse_iterator
			list_allocator_unrelated<Tp>::rend() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->begin());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_reverse_iterator
			list_allocator_unrelated<Tp>::rbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_reverse_iterator
			list_allocator_unrelated<Tp>::rend() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->begin());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_reverse_iterator
			list_allocator_unrelated<Tp>::crbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->cend());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_reverse_iterator
			list_allocator_unrelated<Tp>::crend() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->cbegin());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::iterator
			list_allocator_unrelated<Tp>::nth(size_type index) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->begin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::const_iterator
			list_allocator_unrelated<Tp>::nth(size_type index) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->cbegin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::index_of(iterator it) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->begin(), it);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::index_of(const_iterator it) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->cbegin(), it);
			}


			//===================
			//operation

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::iter_swap_unstable(iterator a, iterator b)
			{
				kerbal::algorithm::iter_swap(a, b);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::iter_swap(iterator a, iterator b) KERBAL_NOEXCEPT
			{
				list_type_unrelated::iter_swap(a, b);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::iter_swap_fast(iterator a, iterator b)
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
						static void apply(list_allocator_unrelated & l, iterator a, iterator b, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
						{
							l.iter_swap(a, b);
						}

						KERBAL_CONSTEXPR20
						static void apply(list_allocator_unrelated & l, iterator a, iterator b, kerbal::type_traits::true_type)
						{
							l.iter_swap_unstable(a, b);
						}
				};

				apply_helper::apply(*this, a, b, policy());

			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::reverse_unstable(iterator first, iterator last) KERBAL_NOEXCEPT
			{
				kerbal::algorithm::reverse(first, last);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::reverse_unstable() KERBAL_NOEXCEPT
			{
				this->reverse_unstable(this->begin(), this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::reverse(iterator first, iterator last) KERBAL_NOEXCEPT
			{
				list_type_unrelated::reverse(first, last);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::reverse() KERBAL_NOEXCEPT
			{
				list_type_unrelated::reverse();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::reverse_fast(iterator first, iterator last) KERBAL_NOEXCEPT
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
						static void apply(list_allocator_unrelated & l, iterator first, iterator last, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
						{
							l.reverse(first, last);
						}

						KERBAL_CONSTEXPR20
						static void apply(list_allocator_unrelated & l, iterator first, iterator last, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
						{
							l.reverse_unstable(first, last);
						}
				};

				apply_helper::apply(*this, first, last, policy());
			};

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::reverse_fast() KERBAL_NOEXCEPT
			{
				this->reverse_fast(this->begin(), this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::iterator
			list_allocator_unrelated<Tp>::rotate(const_iterator first, const_iterator n_first, const_iterator last) KERBAL_NOEXCEPT
			{
				return iterator(list_type_unrelated::rotate(first.cast_to_mutable(), n_first.cast_to_mutable(), last.cast_to_mutable()));
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::merge(list_allocator_unrelated& other, BinaryPredict cmp)
			{
				const_iterator it(this->cbegin());
				const_iterator other_it(other.cbegin());
				while (it != this->cend()) {
					if (other_it != other.cend()) {
						if (cmp(*other_it, *it)) { // other_it < it
							splice(it, other_it++);
						} else { // other_it >= it
							++it;
						}
					} else {
						return;
					}
				}
				splice(it, other);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::merge(list_allocator_unrelated& other)
			{
				this->merge(other, std::less<value_type>());
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::merge_sort_merge(iterator first, iterator mid, iterator last, BinaryPredict cmp)
			{
				node * a = static_cast<node*>(first.current);
				node_base * const a_back = mid.current->prev;

				a_back->next = NULL;

				mid.current->prev = a->prev;
				a->prev->next = mid.current;

				while (a != NULL) {
					if (mid != last) {

#			if __cpp_exceptions
						bool flag = false;
						try {
							flag = static_cast<bool>(cmp(*mid, a->value));
						} catch (...) {
							__hook_node(mid, a, a_back);
							throw;
						}
#			else
						bool flag = static_cast<bool>(cmp(*mid, a->value));
#			endif // __cpp_exceptions


						if (flag) {
							++mid;
						} else {
							node_base * t = a->next;
							__hook_node(mid, a);
							a = static_cast<node*>(t);
						}
					} else {
						__hook_node(mid, a, a_back);
						return;
					}
				}
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::iterator
			list_allocator_unrelated<Tp>::merge_sort_n(iterator first, difference_type len, BinaryPredict cmp)
			{
				if (len == 0) {
					return first;
				}
				if (len == 1) {
					return kerbal::iterator::next(first);
				}
				if (len == 2) {
					iterator i(kerbal::iterator::next(first));
					iterator r(kerbal::iterator::next(i));
					if (cmp(*i, *first)) {
						this->iter_swap(first, i);
					}
					return r;
				}
				difference_type first_half_len = len / 2;

				iterator pre_first(kerbal::iterator::prev(first));
				iterator mid(this->merge_sort_n(first, first_half_len, cmp));

				iterator pre_mid(kerbal::iterator::prev(mid));
				iterator last(this->merge_sort_n(mid, len - first_half_len, cmp));

				first = kerbal::iterator::next(pre_first);
				mid = kerbal::iterator::next(pre_mid);
				this->merge_sort_merge(first, mid, last, cmp);

				return last;
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::sort(iterator first, iterator last, BinaryPredict cmp)
			{
				this->merge_sort_n(first, kerbal::iterator::distance(first, last), cmp);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::sort(iterator first, iterator last)
			{
				this->sort(first, last, std::less<value_type>());
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::sort(BinaryPredict cmp)
			{
				this->sort(this->begin(), this->end(), cmp);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::sort()
			{
				this->sort(this->begin(), this->end());
			}

#	if __cplusplus >= 201103L

#		if __cpp_exceptions

			template <typename Tp>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					!nothrow_while_construct,
					typename list_allocator_unrelated<Tp>::node*
			>::type
			list_allocator_unrelated<Tp>::__build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
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
					typename list_allocator_unrelated<Tp>::node*
			>::type
			list_allocator_unrelated<Tp>::__build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
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
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::__build_new_node(NodeAllocator & alloc, Args&& ... args)
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

				return __build_new_node_impl<nothrow_while_construct::value>(alloc, kerbal::utility::forward<Args>(args)...);
			}

#		else // __cpp_exceptions

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::__build_new_node(NodeAllocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate(alloc, 1);
				node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				return p;
			}

#		endif // __cpp_exceptions

#	else // __cplusplus >= 201103L

#		if __cpp_exceptions

#	define __build_new_node_body(args...) \
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

#	define __build_new_node_body(args...) \
		{ \
			typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
			node * p = node_allocator_traits::allocate(alloc, 1); \
			node_allocator_traits::construct(alloc, p, args); \
			return p; \
		}

#		endif // __cpp_exceptions


			template <typename Tp>
			template <typename NodeAllocator>
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::__build_new_node(NodeAllocator & alloc)
			{
				__build_new_node_body(kerbal::utility::in_place_t());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0>
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::__build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0)
			{
				__build_new_node_body(kerbal::utility::in_place_t(), arg0);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1>
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::__build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0, const Arg1 & arg1)
			{
				__build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::__build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
			{
				__build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1, arg2);
			}

#	undef __build_new_node_body

#	endif // __cplusplus >= 201103L


#	if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator, typename... Args>
			KERBAL_CONSTEXPR20
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::__build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, Args&& ... args)
			{
				size_t cnt = 0;
				node * const start = __build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				node * back = start;
#		if __cpp_exceptions
				try {
#		endif // __cpp_exceptions
					++cnt;
					while (cnt != n) {
						node * new_node = __build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
						new_node->prev = back;
						back->next = new_node;
						back = new_node;
						++cnt;
					}
					return std::pair<node*, node*>(start, back);
#		if __cpp_exceptions
				} catch (...) {
					__consecutive_destroy_node(alloc, start);
					throw;
				}
#		endif // __cpp_exceptions
			}

#	else


#if __cpp_exceptions

// args = {alloc, arg0, arg1...}
#	define __build_n_new_nodes_unguarded_body(args...) \
		{ \
			size_t cnt = 0; \
			node * const start = __build_new_node(args); \
			node * back = start; \
			try { \
				++cnt; \
				while (cnt != n) { \
					node * new_node = __build_new_node(args); \
					new_node->prev = back; \
					back->next = new_node; \
					back = new_node; \
					++cnt; \
				} \
				return std::pair<node*, node*>(start, back); \
			} catch (...) { \
				__consecutive_destroy_node(alloc, start); \
				throw; \
			} \
		}

#else

// args = {alloc, arg0, arg1...}
#	define __build_n_new_nodes_unguarded_body(args...) \
		{ \
			size_t cnt = 0; \
			node * const start = __build_new_node(args); \
			node * back = start; \
			++cnt; \
			while (cnt != n) { \
				node* new_node = __build_new_node(args); \
				new_node->prev = back; \
				back->next = new_node; \
				back = new_node; \
				++cnt; \
			} \
			return std::pair<node*, node*>(start, back); \
		}

#endif


			template <typename Tp>
			template <typename NodeAllocator>
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::__build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n)
			{
				__build_n_new_nodes_unguarded_body(alloc);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0>
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::__build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0)
			{
				__build_n_new_nodes_unguarded_body(alloc, arg0);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1>
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::__build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0, const Arg1 & arg1)
			{
				__build_n_new_nodes_unguarded_body(alloc, arg0, arg1);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::__build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
			{
				__build_n_new_nodes_unguarded_body(alloc, arg0, arg1, arg2);
			}

#	undef __build_n_new_nodes_unguarded_body

#	endif


			template <typename Tp>
			template <typename NodeAllocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			>::type
			list_allocator_unrelated<Tp>::__build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last)
			{
				node * const start = __build_new_node(alloc, *first);
				node * back = start;
#			if __cpp_exceptions
				try {
#			endif // __cpp_exceptions
					++first;
					while (first != last) {
						node* new_node = __build_new_node(alloc, *first);
						new_node->prev = back;
						back->next = new_node;
						back = new_node;
						++first;
					}
					return std::pair<node*, node*>(start, back);
#			if __cpp_exceptions
				} catch (...) {
					__consecutive_destroy_node(alloc, start);
					throw;
				}
#			endif // __cpp_exceptions
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::__build_new_nodes_range_unguarded_move(NodeAllocator & alloc, iterator first, iterator last)
			{
				node * const start = __build_new_node(alloc, kerbal::compatibility::move(*first));
				node * back = start;
#			if __cpp_exceptions
				try {
#			endif // __cpp_exceptions
					++first;
					while (first != last) {
						node* new_node = __build_new_node(alloc, kerbal::compatibility::move(*first));
						new_node->prev = back;
						back->next = new_node;
						back = new_node;
						++first;
					}
					return std::pair<node*, node*>(start, back);
#			if __cpp_exceptions
				} catch (...) {
					__consecutive_destroy_node(alloc, start);
					throw;
				}
#			endif // __cpp_exceptions
			}

#		endif


			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::__destroy_node(NodeAllocator & alloc, node_base* p_node_base)
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
			void list_allocator_unrelated<Tp>::__consecutive_destroy_node(NodeAllocator & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<list_allocator_unrelated>()->__destroy_node(alloc, kerbal::utility::declval<node_base*>()))
					)
			{
				node_base * current_node_base = start;
				while (current_node_base != NULL) {
					node_base * next = current_node_base->next;
					__destroy_node(alloc, current_node_base);
					current_node_base = next;
				}
			}

#		if __cplusplus >= 201703L
#			if __has_include(<memory_resource>)

			template <typename Tp>
			template <typename Node>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::__consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<list_allocator_unrelated>()->__destroy_node(alloc, kerbal::utility::declval<node_base*>()))
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
						__destroy_node(alloc, current_node_base);
						current_node_base = next;
					}
				}
			}

#			endif
#		endif

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_IMPL_LIST_BASE_IMPL_HPP
