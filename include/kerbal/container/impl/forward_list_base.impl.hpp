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

#ifndef KERBAL_CONTAINER_IMPL_FORWARD_LIST_BASE_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_FORWARD_LIST_BASE_IMPL_HPP

#include <kerbal/container/detail/forward_list_base.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
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
		//===================
		// fl_type_unrelated

		//===================
		// capacity

			KERBAL_CONSTEXPR14
			inline
			bool fl_type_unrelated::empty() const KERBAL_NOEXCEPT
			{
				return this->head_node.next == NULL;
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
			void fl_type_unrelated::_K_iter_swap_after(basic_const_iterator a, basic_const_iterator b) KERBAL_NOEXCEPT
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
			void fl_type_unrelated::_K_reverse_after(basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
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
				_K_reverse_after(this->basic_cbefore_begin(), this->basic_cend());
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::_K_splice_after(basic_const_iterator pos, fl_type_unrelated & other) KERBAL_NOEXCEPT
			{
				_K_splice_after(pos, other.basic_cbefore_begin(), other.basic_cend());
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::_K_splice_after(basic_const_iterator pos, basic_const_iterator opos) KERBAL_NOEXCEPT
			{
				node_base * p = _K_unhook_node_after(opos);
				_K_hook_node_after(pos, p);
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::_K_splice_after(basic_const_iterator pos, basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
			{
				basic_const_iterator back(first);
				if (back.current->next != last.current) {
					++back;
					while (back.current->next != last.current) {
						++back;
					}
					node_base * start = _K_unhook_node_after(first, last);
					_K_hook_node_after(pos, start, back.cast_to_mutable().current);
				}
			}


		//===================
		// private

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::_K_hook_node_after(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				p->next = pos_mut.current->next;
				pos_mut.current->next = p;
			}

			KERBAL_CONSTEXPR14
			inline
			void fl_type_unrelated::_K_hook_node_after(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT
			{
				basic_iterator pos_mut(pos.cast_to_mutable());
				back->next = pos_mut.current->next;
				pos_mut.current->next = start;
			}

			KERBAL_CONSTEXPR14
			inline
			fl_type_unrelated::node_base *
			fl_type_unrelated::_K_unhook_node_after(basic_const_iterator pos) KERBAL_NOEXCEPT
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
			fl_type_unrelated::_K_unhook_node_after(basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT
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
			void fl_type_unrelated::_K_swap_type_unrelated(fl_type_unrelated & lhs, fl_type_unrelated & rhs) KERBAL_NOEXCEPT
			{
				kerbal::algorithm::swap(lhs.head_node.next, rhs.head_node.next);
			}


		//===================
		//===================
		// fl_allocator_unrelated

#	if __cplusplus >= 201103L

			// pre-cond: allocator allows
			template <typename Tp>
			KERBAL_CONSTEXPR14
			fl_allocator_unrelated<Tp>::fl_allocator_unrelated(fl_allocator_unrelated && src) KERBAL_NOEXCEPT
					: fl_type_unrelated(static_cast<fl_type_unrelated&&>(src))
			{
			}

#	endif

		//===================
		// iterator

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::iterator
			fl_allocator_unrelated<Tp>::before_begin() KERBAL_NOEXCEPT
			{
				return iterator(&this->head_node);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::before_begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->head_node);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::cbefore_begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->head_node);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::iterator
			fl_allocator_unrelated<Tp>::begin() KERBAL_NOEXCEPT
			{
				return iterator(this->head_node.next);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->head_node.next);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->head_node.next);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::iterator
			fl_allocator_unrelated<Tp>::end() KERBAL_NOEXCEPT
			{
				return iterator(NULL);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::end() const KERBAL_NOEXCEPT
			{
				return const_iterator(NULL);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(NULL);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::iterator
			fl_allocator_unrelated<Tp>::nth(size_type index) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->begin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::nth(size_type index) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(this->cbegin(), index);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::index_of(iterator it) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->begin(), it);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::index_of(const_iterator it) const KERBAL_NOEXCEPT
			{
				return kerbal::iterator::distance(this->cbegin(), it);
			}


		//===================
		// element access

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::reference
			fl_allocator_unrelated<Tp>::front() KERBAL_NOEXCEPT
			{
				return this->head_node.next->template reinterpret_as<Tp>().value;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_reference
			fl_allocator_unrelated<Tp>::front() const KERBAL_NOEXCEPT
			{
				return this->head_node.next->template reinterpret_as<Tp>().value;
			}


		//===================
		// erase

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_allocator_unrelated<Tp>::iterator
			fl_allocator_unrelated<Tp>::_K_erase_after(NodeAllocator & alloc, const_iterator pos)
			{
				iterator pos_mut(pos.cast_to_mutable());
				node_base * p = _K_unhook_node_after(pos_mut);
				_K_destroy_node(alloc, p);
				return ++pos_mut;
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_allocator_unrelated<Tp>::iterator
			fl_allocator_unrelated<Tp>::_K_erase_after(NodeAllocator & alloc, const_iterator first, const_iterator last)
			{
				iterator first_mut(first.cast_to_mutable());
				iterator last_mut(last.cast_to_mutable());
				if (first != last) {
					node_base * first = _K_unhook_node_after(first_mut, last_mut);
					node_base * last = last_mut.current;
					_K_consecutive_destroy_node(alloc, first, last);
				}
				return ++first_mut;
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_allocator_unrelated<Tp>::_K_clear(NodeAllocator & alloc)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<fl_allocator_unrelated>()->_K_consecutive_destroy_node(
									alloc,
									kerbal::utility::declthis<fl_allocator_unrelated>()->head_node.next,
									NULL
							))
					)
			{
				_K_consecutive_destroy_node(alloc, this->head_node.next, NULL);
				this->head_node.next = NULL;
			}


		//===================
		// operation

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_iter_swap_after(const_iterator a, const_iterator b) KERBAL_NOEXCEPT
			{
				fl_type_unrelated::_K_iter_swap_after(a, b);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_reverse_after(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
			{
				fl_type_unrelated::_K_reverse_after(first, last);
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_merge_impl(fl_allocator_unrelated & other, BinaryPredict cmp, MERGE_VER_NOTHROW) KERBAL_NOEXCEPT
			{
				const_iterator it_other(other.cbegin());
				const_iterator it_this_before(this->cbefore_begin());
				const_iterator it_this(this->cbegin());
				const_iterator const cend(NULL);

				while (it_other != cend) {
					if (it_this != cend) {
						if (cmp(*it_other, *it_this)) {
							_K_hook_node_after(it_this_before, it_other++.cast_to_mutable().current);
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
				other.head_node.next = NULL;
			}

#		if __cpp_exceptions

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			void fl_allocator_unrelated<Tp>::_K_merge_impl(fl_allocator_unrelated & other, BinaryPredict cmp, MERGE_VER_MAY_THROW)
			{
				const_iterator it_other(other.cbegin());
				const_iterator it_this_before(this->cbefore_begin());
				const_iterator it_this(this->cbegin());
				const_iterator const cend(NULL);

				try {
					while (it_other != cend) {
						if (it_this != cend) {
							if (cmp(*it_other, *it_this)) {
								_K_hook_node_after(it_this_before, it_other++.cast_to_mutable().current);
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
					other.head_node.next = it_other.cast_to_mutable().current;
					throw;
				}
				other.head_node.next = NULL;
			}

#		endif

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_merge(fl_allocator_unrelated & other, BinaryPredict cmp)
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
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_merge(fl_allocator_unrelated & other)
			{
				this->_K_merge(other, std::less<value_type>());
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::_K_merge_sort_merge_after_impl(const_iterator before_first, const_iterator before_mid, const_iterator before_last, BinaryPredict cmp, MSM_VER_NOTHROW)
			{
				const_iterator mid(before_mid); ++mid;
				const_iterator last(before_last); ++last;
				const_iterator before_i(before_first);
				const_iterator i(before_i); ++i;
				const_iterator j(mid);

				while (i != mid) {
					if (j != last) {
						if (cmp(*j, *i)) {
							_K_hook_node_after(before_i, j++.cast_to_mutable().current);
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

#		if __cpp_exceptions

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::_K_merge_sort_merge_after_impl(const_iterator before_first, const_iterator before_mid, const_iterator before_last, BinaryPredict cmp, MSM_VER_MAY_THROW)
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
								_K_hook_node_after(before_i, j++.cast_to_mutable().current);
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
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::_K_merge_sort_merge_after(const_iterator before_first, const_iterator before_mid, const_iterator before_last, BinaryPredict cmp)
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

				return _K_merge_sort_merge_after_impl(before_first, before_mid, before_last, cmp, MSM_VERSION());

			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			typename fl_allocator_unrelated<Tp>::const_iterator
			fl_allocator_unrelated<Tp>::_K_merge_sort_n_after(const_iterator before_first, size_type n, BinaryPredict cmp)
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
				const_iterator before_mid(_K_merge_sort_n_after(before_first, first_len, cmp));
				const_iterator before_last(_K_merge_sort_n_after(before_mid, n - first_len, cmp));
				return _K_merge_sort_merge_after(before_first, before_mid, before_last, cmp);
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_merge_sort_after(const_iterator first, const_iterator last, BinaryPredict cmp)
			{
				_K_merge_sort_n_after(first, kerbal::iterator::distance(first, last) - 1, cmp);
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_sort_after(const_iterator first, const_iterator last, BinaryPredict cmp)
			{
				_K_merge_sort_after(first, last, cmp);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_sort_after(const_iterator first, const_iterator last)
			{
				_K_sort_after(first, last, std::less<value_type>());
			}

			template <typename Tp>
			template <typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_sort(BinaryPredict cmp)
			{
				_K_sort_after(this->cbefore_begin(), this->cend(), cmp);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void fl_allocator_unrelated<Tp>::_K_sort()
			{
				_K_sort(std::less<value_type>());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename UnaryPredicate>
			KERBAL_CONSTEXPR20
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::_K_remove_after_if(NodeAllocator & alloc, const_iterator first, const_iterator last, UnaryPredicate predicate)
			{
				size_type cnt = 0;
				const_iterator before_first(first);
				++first;
				while (first != last) {
					if (predicate(*first)) {
						++first;
						_K_erase_after(alloc, before_first);
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
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::_K_remove_if(NodeAllocator & alloc, UnaryPredicate predicate)
			{
				return _K_remove_after_if(alloc, this->cbefore_begin(), this->cend(), predicate);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::_K_remove_after(NodeAllocator & alloc, const_iterator first, const_iterator last, const_reference val)
			{
				return _K_remove_after_if(alloc, first, last, remove_predict(val));
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::_K_remove(NodeAllocator & alloc, const_reference val)
			{
				return _K_remove_after(alloc, this->cbefore_begin(), this->cend(), val);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::_K_unique(NodeAllocator & alloc, const_iterator first, const_iterator last, BinaryPredict equal_to)
			{
				size_type cnt = 0;
				if (first != last) {
					const_iterator forward(first); ++forward;
					while (forward != last) {
						if (equal_to(*first, *forward)) {
							++forward;
							_K_destroy_node(alloc, _K_unhook_node_after(first));
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
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::_K_unique(NodeAllocator & alloc, const_iterator first, const_iterator last)
			{
				return _K_unique(alloc, first, last, std::equal_to<value_type>());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename BinaryPredict>
			KERBAL_CONSTEXPR20
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::_K_unique(NodeAllocator & alloc, BinaryPredict equal_to)
			{
				return _K_unique(alloc, this->cbegin(), this->cend(), equal_to);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename fl_allocator_unrelated<Tp>::size_type
			fl_allocator_unrelated<Tp>::_K_unique(NodeAllocator & alloc)
			{
				return this->_K_unique(alloc, std::equal_to<value_type>());
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
					typename fl_allocator_unrelated<Tp>::node*
			>::type
			fl_allocator_unrelated<Tp>::_K_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
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
					typename fl_allocator_unrelated<Tp>::node*
			>::type
			fl_allocator_unrelated<Tp>::_K_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
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
			typename fl_allocator_unrelated<Tp>::node*
			fl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc, Args&& ... args)
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
			typename fl_allocator_unrelated<Tp>::node*
			fl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc, Args&& ... args)
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
			typename fl_allocator_unrelated<Tp>::node*
			fl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc)
			{
				_K_build_new_node_body(kerbal::utility::in_place_t());
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0>
			typename fl_allocator_unrelated<Tp>::node*
			fl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0)
			{
				_K_build_new_node_body(kerbal::utility::in_place_t(), arg0);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1>
			typename fl_allocator_unrelated<Tp>::node*
			fl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc,
															const Arg0 & arg0, const Arg1 & arg1)
			{
				_K_build_new_node_body(kerbal::utility::in_place_t(), arg0, arg1);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
			typename fl_allocator_unrelated<Tp>::node*
			fl_allocator_unrelated<Tp>::_K_build_new_node(NodeAllocator & alloc,
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
			std::pair<typename fl_allocator_unrelated<Tp>::node*, typename fl_allocator_unrelated<Tp>::node*>
			fl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, Args&& ... args)
			{
				--n;
				node * const start = _K_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				node * back = start;
#		if __cpp_exceptions
				try {
#		endif // __cpp_exceptions
					while (n != 0) {
						node * new_node = _K_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
						back->next = new_node;
						back = new_node;
						--n;
					}
					return std::pair<node*, node*>(start, back);
#		if __cpp_exceptions
				} catch (...) {
					_K_consecutive_destroy_node(alloc, start, NULL);
					throw;
				}
#		endif // __cpp_exceptions
			}

#	else


#if __cpp_exceptions

// args = {alloc, arg0, arg1...}
#	define _K_build_n_new_nodes_unguarded_body(args...) \
		{ \
			--n; \
			node * const start = _K_build_new_node(args); \
			node * back = start; \
			try { \
				while (n != 0) { \
					node * new_node = _K_build_new_node(args); \
					back->next = new_node; \
					back = new_node; \
					--n; \
				} \
				return std::pair<node*, node*>(start, back); \
			} catch (...) { \
				_K_consecutive_destroy_node(alloc, start, NULL); \
				throw; \
			} \
		}

#else

// args = {alloc, arg0, arg1...}
#	define _K_build_n_new_nodes_unguarded_body(args...) \
		{ \
			--n; \
			node * const start = _K_build_new_node(args); \
			node * back = start; \
			while (n != 0) { \
				node* new_node = _K_build_new_node(args); \
				back->next = new_node; \
				back = new_node; \
				--n; \
			} \
			return std::pair<node*, node*>(start, back); \
		}

#endif


			template <typename Tp>
			template <typename NodeAllocator>
			std::pair<typename fl_allocator_unrelated<Tp>::node*, typename fl_allocator_unrelated<Tp>::node*>
			fl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n)
			{
				_K_build_n_new_nodes_unguarded_body(alloc);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0>
			std::pair<typename fl_allocator_unrelated<Tp>::node*, typename fl_allocator_unrelated<Tp>::node*>
			fl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0)
			{
				_K_build_n_new_nodes_unguarded_body(alloc, arg0);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1>
			std::pair<typename fl_allocator_unrelated<Tp>::node*, typename fl_allocator_unrelated<Tp>::node*>
			fl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0, const Arg1 & arg1)
			{
				_K_build_n_new_nodes_unguarded_body(alloc, arg0, arg1);
			}

			template <typename Tp>
			template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
			std::pair<typename fl_allocator_unrelated<Tp>::node*, typename fl_allocator_unrelated<Tp>::node*>
			fl_allocator_unrelated<Tp>::_K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
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
					std::pair<typename fl_allocator_unrelated<Tp>::node*, typename fl_allocator_unrelated<Tp>::node*>
			>::type
			fl_allocator_unrelated<Tp>::_K_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last)
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
					_K_consecutive_destroy_node(alloc, start, NULL);
					throw;
				}
#			endif // __cpp_exceptions
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			std::pair<typename fl_allocator_unrelated<Tp>::node*, typename fl_allocator_unrelated<Tp>::node*>
			fl_allocator_unrelated<Tp>::_K_build_new_nodes_range_unguarded_move(NodeAllocator & alloc, iterator first, iterator last)
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
					_K_consecutive_destroy_node(alloc, start, NULL);
					throw;
				}
#			endif // __cpp_exceptions
			}

#		endif


			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_allocator_unrelated<Tp>::_K_destroy_node(NodeAllocator & alloc, node_base * p_node_base) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef typename node_allocator_traits::pointer real_pointer;

				real_pointer p_node = static_cast<real_pointer>(&p_node_base->template reinterpret_as<value_type>());
				node_allocator_traits::destroy(alloc, p_node);
				node_allocator_traits::deallocate(alloc, p_node, 1);
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_allocator_unrelated<Tp>::_K_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * first, node_base * last, CNSCTV_DES_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				while (first != last) {
					node_base * next = first->next;
					_K_destroy_node(alloc, first);
					first = next;
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_allocator_unrelated<Tp>::_K_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * first, node_base * last, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef typename node_allocator_traits::pointer real_pointer;

				while (first != last) {
					node_base * next = first->next;
					real_pointer p_node = static_cast<real_pointer>(&first->template reinterpret_as<value_type>());
					node_allocator_traits::destroy(alloc, p_node);
					first = next;
				}
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_allocator_unrelated<Tp>::_K_consecutive_destroy_node_impl(NodeAllocator & /*alloc*/, node_base * /*first*/, node_base * /*last*/, CNSCTV_DES_VER_NO_DESTROY) KERBAL_NOEXCEPT
			{
			}

			template <typename Tp>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void fl_allocator_unrelated<Tp>::_K_consecutive_destroy_node(NodeAllocator & alloc, node_base * first, node_base * last) KERBAL_NOEXCEPT
			{
				_K_consecutive_destroy_node_impl(alloc, first, last, CNSCTV_DES_VER_DEFAULT());
			}

#		if __cplusplus >= 201703L
#			if __has_include(<memory_resource>)

			template <typename Tp>
			template <typename Node>
			KERBAL_CONSTEXPR20
			void fl_allocator_unrelated<Tp>::_K_consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * first, node_base * last) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<std::pmr::polymorphic_allocator<Node> > node_allocator_traits;
				typedef typename node_allocator_traits::value_type real_value_type;

				if (typeid(*alloc.resource()) == typeid(std::pmr::monotonic_buffer_resource)) {
					if constexpr (!std::is_trivially_destructible<real_value_type>::value) {
						_K_consecutive_destroy_node_impl(alloc, first, last, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE());
					}
				} else {
					_K_consecutive_destroy_node_impl(alloc, first, last, CNSCTV_DES_VER_DEFAULT());
				}
			}

#			endif
#		endif


		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_FORWARD_LIST_BASE_IMPL_HPP
