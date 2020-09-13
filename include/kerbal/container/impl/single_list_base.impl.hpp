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
				node_base * p = other.__unhook_node(opos.cast_to_mutable());
				p->next = NULL;
				this->__hook_node(pos, p);
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::splice(basic_const_iterator pos, sl_type_unrelated & other,
											basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				if (first == last) {
					return;
				}
				std::pair<node_base *, node_base *> range(other.__unhook_node(first.cast_to_mutable(), last.cast_to_mutable()));
				node_base * start = range.first;
				node_base * back = range.second;
				back->next = NULL;
				this->__hook_node(pos, start, back);
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::__hook_node_back(node_base * p) KERBAL_NOEXCEPT
			{
				node_base * prev = this->last_iter.current;
				prev->next = p;
				this->last_iter = basic_iterator(p);
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::__hook_node_not_back(basic_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				node_base * prev = pos.current;
				p->next = prev->next;
				prev->next = p;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::__hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				if (pos_mut != this->basic_end()) {
					__hook_node_not_back(pos_mut, p);
				} else {
					this->__hook_node_back(p);
				}
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::__hook_node_back(node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				node_base * prev = this->last_iter.current;
				this->last_iter = basic_iterator(back);
				prev->next = start;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::__hook_node_not_back(basic_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				node_base * prev = pos.current;
				back->next = prev->next;
				prev->next = start;
			}

			KERBAL_CONSTEXPR20
			inline
			void sl_type_unrelated::__hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				if (pos_mut != this->basic_end()) {
					__hook_node_not_back(pos_mut, start, back);
				} else {
					this->__hook_node_back(start, back);
				}
			}

			KERBAL_CONSTEXPR20
			inline
			sl_node_base *
			sl_type_unrelated::__unhook_node(basic_iterator pos) KERBAL_NOEXCEPT
			{
				node_base * prev = pos.current;
				node_base * p = prev->next;
				prev->next = p->next;
				if (p->next == NULL) { // is back node
					this->last_iter = pos;
				}
				return p;
			}

			KERBAL_CONSTEXPR20
			inline
			std::pair<sl_type_unrelated::node_base *, sl_type_unrelated::node_base *>
			sl_type_unrelated::__unhook_node(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT
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
			void sl_type_unrelated::swap_with_empty(sl_type_unrelated & not_empty_list, sl_type_unrelated & empty_list) KERBAL_NOEXCEPT
			{
				empty_list.head_node.next = not_empty_list.head_node.next;
				not_empty_list.head_node.next = NULL;
				empty_list.last_iter = not_empty_list.last_iter;
				not_empty_list.last_iter = not_empty_list.basic_begin();
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

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void sl_allocator_unrelated<Tp>::reverse() KERBAL_NOEXCEPT
			{
				sl_type_unrelated::reverse();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void sl_allocator_unrelated<Tp>::swap_allocator_unrelated(sl_allocator_unrelated & ano) KERBAL_NOEXCEPT
			{
				bool is_this_empty = this->empty();
				bool is_ano_empty = ano.empty();
				if (is_this_empty) {
					if (!is_ano_empty) {
						// this->empty() && !ano.empty()
						swap_with_empty(ano, *this);
					}
				} else {
					if (is_ano_empty) {
						// !this->empty() and ano.empty()
						swap_with_empty(*this, ano);
					} else {
						// !this->empty() and !ano.empty()
						kerbal::algorithm::swap(this->head_node.next, ano.head_node.next);
						kerbal::algorithm::swap(this->last_iter, ano.last_iter);
					}
				}
			}


		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_IMPL_SINGLE_LIST_BASE_IMPL_HPP
