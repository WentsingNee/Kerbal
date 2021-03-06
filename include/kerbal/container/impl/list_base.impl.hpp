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
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <utility> // std::pair

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			//===================
			//capacity

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
			//operation

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::_K_iter_swap(basic_const_iterator a, basic_const_iterator b) KERBAL_NOEXCEPT
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
			void list_type_unrelated::_K_reverse(basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
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
				_K_reverse(this->basic_cbegin(), this->basic_cend());
			}

			KERBAL_CONSTEXPR14
			inline
			list_type_unrelated::basic_iterator
			list_type_unrelated::_K_rotate(basic_const_iterator first, basic_const_iterator n_first, basic_const_iterator last) KERBAL_NOEXCEPT
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

				std::pair<node_base *, node_base *> left_range(_K_unhook_node(first_mut, n_first_mut));
				_K_hook_node(last_mut, left_range.first, left_range.second);
				return first_mut;
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::_K_splice(basic_const_iterator pos, list_type_unrelated & other) KERBAL_NOEXCEPT
			{
				list_type_unrelated::_K_splice(pos, other.basic_begin(), other.basic_end());
			}

#		if __cplusplus >= 201103L

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::_K_splice(basic_const_iterator pos, list_type_unrelated && other) KERBAL_NOEXCEPT
			{
				list_type_unrelated::_K_splice(pos, other.basic_begin(), other.basic_end());
			}

#		endif

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::_K_splice(basic_const_iterator pos, basic_const_iterator opos) KERBAL_NOEXCEPT
			{
				basic_iterator opos_mut(opos.cast_to_mutable());
				node_base * p = list_type_unrelated::_K_unhook_node(opos_mut);
				list_type_unrelated::_K_hook_node(pos, p);
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::_K_splice(basic_const_iterator pos, basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				if (first == last) {
					return;
				}

				std::pair<node_base *, node_base *> range(list_type_unrelated::_K_unhook_node(first.cast_to_mutable(), last.cast_to_mutable()));
				node_base * start = range.first;
				node_base * back = range.second;
				list_type_unrelated::_K_hook_node(pos, start, back);
			}

			//===================
			//private

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::_K_hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT
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
			void list_type_unrelated::_K_hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
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
			list_type_unrelated::_K_unhook_node(basic_iterator pos) KERBAL_NOEXCEPT
			{
				node_base * p = pos.current;
				p->prev->next = p->next;
				p->next->prev = p->prev;
				return p;
			}

			KERBAL_CONSTEXPR14
			inline
			std::pair<list_type_unrelated::node_base *, list_type_unrelated::node_base *>
			list_type_unrelated::_K_unhook_node(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT
			{
				node_base * start = first.current;
				node_base * prev = start->prev;
				node_base * end = last.current;
				node_base * back = end->prev;
				end->prev = prev;
				prev->next = end;
				return std::pair<node_base *, node_base *>(start, back);
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::_K_swap_with_empty(list_type_unrelated& not_empty_list, list_type_unrelated& empty_list) KERBAL_NOEXCEPT
			{
				empty_list.head_node.prev = not_empty_list.head_node.prev;
				empty_list.head_node.prev->next = &empty_list.head_node;
				empty_list.head_node.next = not_empty_list.head_node.next;
				empty_list.head_node.next->prev = &empty_list.head_node;
				not_empty_list._K_init_node_base();
			}

			KERBAL_CONSTEXPR14
			inline
			void list_type_unrelated::_K_swap_type_unrelated(list_type_unrelated & lhs, list_type_unrelated & rhs) KERBAL_NOEXCEPT
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
		// element access

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
		// iterator

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
		// erase

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::iterator
			list_allocator_unrelated<Tp>::_K_erase(NodeAllocator & alloc, const_iterator pos)
			{
				iterator pos_mut(pos.cast_to_mutable());
				node_base * p = list_type_unrelated::_K_unhook_node(pos_mut++);
				_K_destroy_node(alloc, p);
				return pos_mut;
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::iterator
			list_allocator_unrelated<Tp>::_K_erase(NodeAllocator & alloc, const_iterator first, const_iterator last)
			{
				iterator last_mut(last.cast_to_mutable());
				if (first != last) {
					iterator first_mut(first.cast_to_mutable());
					std::pair<node_base *, node_base *> range(list_type_unrelated::_K_unhook_node(first_mut, last_mut));
					node_base * start = range.first;
					node_base * back = range.second;
					back->next = NULL;
					_K_consecutive_destroy_node(alloc, start);
				}
				return last_mut;
			}


		//===================
		// operation

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_iter_swap_unstable(const_iterator a, const_iterator b)
			{
				kerbal::algorithm::iter_swap(a.cast_to_mutable(), b.cast_to_mutable());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_iter_swap(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
			{
				list_type_unrelated::_K_iter_swap(a, b);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_iter_swap_fast(const_iterator a, const_iterator b)
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
						static void apply(const_iterator a, const_iterator b, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
						{
							_K_iter_swap(a, b);
						}

						KERBAL_CONSTEXPR20
						static void apply(const_iterator a, const_iterator b, kerbal::type_traits::true_type)
						{
							_K_iter_swap_unstable(a, b);
						}
				};

				apply_helper::apply(a, b, policy());

			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_reverse_unstable(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
			{
				kerbal::algorithm::reverse(first.cast_to_mutable(), last.cast_to_mutable());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::reverse_unstable() KERBAL_NOEXCEPT
			{
				_K_reverse_unstable(this->cbegin(), this->cend());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_reverse(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
			{
				list_type_unrelated::_K_reverse(first, last);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_reverse_fast(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
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
						static void apply(const_iterator first, const_iterator last, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
						{
							_K_reverse(first, last);
						}

						KERBAL_CONSTEXPR20
						static void apply(const_iterator first, const_iterator last, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
						{
							_K_reverse_unstable(first, last);
						}
				};

				apply_helper::apply(first, last, policy());
			};

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::reverse_fast() KERBAL_NOEXCEPT
			{
				_K_reverse_fast(this->cbegin(), this->cend());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::iterator
			list_allocator_unrelated<Tp>::rotate(const_iterator first, const_iterator n_first, const_iterator last) KERBAL_NOEXCEPT
			{
				return iterator(list_type_unrelated::_K_rotate(first, n_first, last));
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_merge_impl(list_allocator_unrelated & other, BinaryPredict cmp, MERGE_VER_NOTHROW) KERBAL_NOEXCEPT
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
							_K_hook_node(it, p);
						} else { // *other_it >= *it
							++it;
						}
					} else {
						// node: it has made sure that the remain range is not empty
						node_base * remain_start = other_it.cast_to_mutable().current;
						node_base * remain_back = other.head_node.prev;
						_K_hook_node(end, remain_start, remain_back);
						break;
					}
				}
				other._K_init_node_base();
			}

#		if __cpp_exceptions

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_merge_impl(list_allocator_unrelated & other, BinaryPredict cmp, MERGE_VER_MAY_THROW)
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
								_K_hook_node(it, p);
							} else { // *other_it >= *it
								++it;
							}
						} else {
							// node: it has made sure that the remain range is not empty
							node_base * remain_start = other_it.cast_to_mutable().current;
							node_base * remain_back = other.head_node.prev;
							_K_hook_node(end, remain_start, remain_back);
							break;
						}
					}
				} catch (...) {
					node_base * p = other_it.cast_to_mutable().current;
					p->prev = &other.head_node;
					other.head_node.next = p;
					throw;
				}
				other._K_init_node_base();
			}

#		endif

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_merge(list_allocator_unrelated & other, BinaryPredict cmp)
			{

#		if __cpp_exceptions

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

				this->_K_merge_impl(other, cmp, MERGE_VERSION());

			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_merge(list_allocator_unrelated& other)
			{
				this->_K_merge(other, std::less<value_type>());
			}

			template <typename Tp>
			template <typename BinaryPredict>
			inline
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_merge_sort_merge(iterator first, iterator mid, iterator last, BinaryPredict cmp, MSM_VER_NOTHROW)
			{
				iterator before_mid(kerbal::iterator::prev(mid));
				const_iterator i(first);
				const_iterator j(mid);
				while (i != mid) {
					if (j != last) {
						if (cmp(*j, *i)) {
							_K_hook_node(i, (j++).cast_to_mutable().current);
						} else {
							++i;
						}
					} else {
						break;
					}
				}
				before_mid.current->next = j.cast_to_mutable().current;
				j.cast_to_mutable().current->prev = before_mid.current;
			}

#		if __cpp_exceptions

			template <typename Tp>
			template <typename BinaryPredict>
			inline
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_merge_sort_merge(iterator first, iterator mid, iterator last, BinaryPredict cmp, MSM_VER_MAY_THROW)
			{
				iterator before_mid(kerbal::iterator::prev(mid));
				const_iterator i(first);
				const_iterator j(mid);
				try {
					while (i != mid) {
						if (j != last) {
							if (cmp(*j, *i)) {
								_K_hook_node(i, (j++).cast_to_mutable().current);
							} else {
								++i;
							}
						} else {
							break;
						}
					}
				} catch (...) {
					before_mid.current->next = j.cast_to_mutable().current;
					j.cast_to_mutable().current->prev = before_mid.current;
					throw;
				}
				before_mid.current->next = j.cast_to_mutable().current;
				j.cast_to_mutable().current->prev = before_mid.current;
			}

#		endif

			template <typename Tp>
			template <typename BinaryPredict>
			inline
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::merge_sort_merge(iterator first, iterator mid, iterator last, BinaryPredict cmp)
			{

#		if __cpp_exceptions

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

				_K_merge_sort_merge(first, mid, last, cmp, MSM_VERSION());

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
						_K_iter_swap(first, i);
					}
					return r;
				}
				difference_type first_half_len = len / 2;

				iterator pre_first(kerbal::iterator::prev(first));
				iterator mid(merge_sort_n(first, first_half_len, cmp));

				iterator pre_mid(kerbal::iterator::prev(mid));
				iterator last(merge_sort_n(mid, len - first_half_len, cmp));

				first = kerbal::iterator::next(pre_first);
				mid = kerbal::iterator::next(pre_mid);
				merge_sort_merge(first, mid, last, cmp);

				return last;
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_sort(iterator first, iterator last, BinaryPredict cmp)
			{
				merge_sort_n(first, kerbal::iterator::distance(first, last), cmp);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_sort(iterator first, iterator last)
			{
				_K_sort(first, last, std::less<value_type>());
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::sort(BinaryPredict cmp)
			{
				_K_sort(this->begin(), this->end(), cmp);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::sort()
			{
				_K_sort(this->begin(), this->end());
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::_K_remove(NodeAllocator & alloc, const_reference val)
			{
				return _K_remove(alloc, this->cbegin(), this->cend(), val);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::_K_remove(NodeAllocator & alloc, const_iterator first, const_iterator last, const_reference val)
			{
				return _K_remove_if(alloc, first, last, remove_predict(val));
			}

			template <typename Tp>
			template <typename NodeAllocator, typename UnaryPredicate>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::_K_remove_if(NodeAllocator & alloc, UnaryPredicate predicate)
			{
				return _K_remove_if(alloc, this->cbegin(), this->cend(), predicate);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename UnaryPredicate>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::_K_remove_if(NodeAllocator & alloc, const_iterator first, const_iterator last, UnaryPredicate predicate)
			{
				size_type i = 0;
				while (first != last) {
					if (predicate(*first)) {
						node_base * p = _K_unhook_node(first++.cast_to_mutable());
						_K_destroy_node(alloc, p);
						// <=> first = _K_erase(alloc, first);
						++i;
					} else {
						++first;
					}
				}
				return i;
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::_K_unique(NodeAllocator & alloc)
			{
				return _K_unique(alloc, this->cbegin(), this->cend());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename BinaryPredicate>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::_K_unique(NodeAllocator & alloc, BinaryPredicate pred)
			{
				return _K_unique(alloc, this->cbegin(), this->cend(), pred);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::_K_unique(NodeAllocator & alloc, const_iterator first, const_iterator last)
			{
				return _K_unique(alloc, first, last, std::equal_to<value_type>());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename BinaryPredicate>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::size_type
			list_allocator_unrelated<Tp>::_K_unique(NodeAllocator & alloc, const_iterator first, const_iterator last, BinaryPredicate pred)
			{
				size_type r = 0;

				if (first != last) {
					const_iterator forward(first); ++forward;

					while (forward != last) {
						if (pred(*first, *forward)) {
							node_base * p = list_type_unrelated::_K_unhook_node(forward++.cast_to_mutable());
							_K_destroy_node(alloc, p);
							// <=> _K_erase(alloc, forward++);
							++r;
						} else {
							first = forward;
							++forward;
						}
					}
				}

				return r;
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
					typename list_allocator_unrelated<Tp>::node*
			>::type
			list_allocator_unrelated<Tp>::_K_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
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
			list_allocator_unrelated<Tp>::_K_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
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
			list_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc, Args&& ... args)
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

				return _K_build_new_node_impl<nothrow_while_construct::value>(alloc, kerbal::utility::forward<Args>(args)...);
			}

#		else // __cpp_exceptions

			template <typename Tp>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc, Args&& ... args)
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
			list_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc)
			{
				__build_new_node_body(kerbal::utility::in_place_t());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0>
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0)
			{
				__build_new_node_body(kerbal::utility::in_place_t(), arg0);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1>
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0, const Arg1 & arg1)
			{
				__build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
			typename list_allocator_unrelated<Tp>::node*
			list_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc,
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
			list_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, Args&& ... args)
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
						new_node->prev = back;
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
#	define __build_n_new_nodes_unguarded_body(args...) \
		{ \
			size_t cnt = 0; \
			node * const start = _K_build_new_node(args); \
			node * back = start; \
			try { \
				++cnt; \
				while (cnt != n) { \
					node * new_node = _K_build_new_node(args); \
					new_node->prev = back; \
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
#	define __build_n_new_nodes_unguarded_body(args...) \
		{ \
			size_t cnt = 0; \
			node * const start = _K_build_new_node(args); \
			node * back = start; \
			++cnt; \
			while (cnt != n) { \
				node* new_node = _K_build_new_node(args); \
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
			list_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n)
			{
				__build_n_new_nodes_unguarded_body(alloc);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0>
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0)
			{
				__build_n_new_nodes_unguarded_body(alloc, arg0);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1>
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0, const Arg1 & arg1)
			{
				__build_n_new_nodes_unguarded_body(alloc, arg0, arg1);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
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
			list_allocator_unrelated<Tp>::_K_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last)
			{
				node * const start = _K_build_new_node(alloc, *first);
				node * back = start;
#			if __cpp_exceptions
				try {
#			endif // __cpp_exceptions
					++first;
					while (first != last) {
						node* new_node = _K_build_new_node(alloc, *first);
						new_node->prev = back;
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
			std::pair<typename list_allocator_unrelated<Tp>::node*, typename list_allocator_unrelated<Tp>::node*>
			list_allocator_unrelated<Tp>::_K_build_new_nodes_range_unguarded_move(NodeAllocator & alloc, iterator first, iterator last)
			{
				node * const start = _K_build_new_node(alloc, kerbal::compatibility::move(*first));
				node * back = start;
#			if __cpp_exceptions
				try {
#			endif // __cpp_exceptions
					++first;
					while (first != last) {
						node* new_node = _K_build_new_node(alloc, kerbal::compatibility::move(*first));
						new_node->prev = back;
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
			void list_allocator_unrelated<Tp>::_K_destroy_node(NodeAllocator & alloc, node_base* p_node_base)
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
			void list_allocator_unrelated<Tp>::_K_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * start, CNSCTV_DES_VER_DEFAULT)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(_K_destroy_node(alloc, kerbal::utility::declval<node_base*>()))
					)
			{
				node_base * current_node_base = start;
				while (current_node_base != NULL) {
					node_base * next = current_node_base->next;
					_K_destroy_node(alloc, current_node_base);
					current_node_base = next;
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE)
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
			void list_allocator_unrelated<Tp>::_K_consecutive_destroy_node_impl(NodeAllocator & /*alloc*/, node_base * /*start*/, CNSCTV_DES_VER_NO_DESTROY) KERBAL_NOEXCEPT
			{
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_consecutive_destroy_node(NodeAllocator & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(_K_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT()))
					)
			{
				_K_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT());
			}

#		if __cplusplus >= 201703L
#			if __has_include(<memory_resource>)

			template <typename Tp>
			template <typename Node>
			KERBAL_CONSTEXPR20
			void list_allocator_unrelated<Tp>::_K_consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * start)
					KERBAL_CONDITIONAL_NOEXCEPT(
						(
							!std::is_trivially_destructible<Tp>::value ?
							noexcept(_K_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE())) :
							true
						) &&
						noexcept(_K_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT()))
					)
			{
				if (typeid(*alloc.resource()) == typeid(std::pmr::monotonic_buffer_resource)) {
					if constexpr (!std::is_trivially_destructible<Tp>::value) {
						_K_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE());
					}
				} else {
					_K_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT());
				}
			}

#			endif
#		endif

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_IMPL_LIST_BASE_IMPL_HPP
