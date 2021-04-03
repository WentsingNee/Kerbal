/**
 * @file       list.hpp
 * @brief
 * @date       2021-01-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_LIST_HPP
#define KERBAL_AUTONM_LIST_HPP

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/detail/list_node.hpp>
#include <kerbal/container/detail/list_base.hpp>
#include <kerbal/container/detail/list_iterator.hpp>
#include <kerbal/utility/noncopyable.hpp>

namespace kerbal
{

	namespace autonm
	{

		namespace detail
		{

			template <typename Tp>
			class autonm_list_node : public kerbal::container::detail::list_node<Tp>
			{
				private:
					typedef kerbal::container::detail::list_node<Tp> super;

				public:
					KERBAL_CONSTEXPR
					autonm_list_node() : super(kerbal::utility::in_place_t())
					{
					}

					KERBAL_CONSTEXPR14
					Tp& value() KERBAL_NOEXCEPT
					{
						return super::value;
					}

					KERBAL_CONSTEXPR14
					const Tp& value() const KERBAL_NOEXCEPT
					{
						return super::value;
					}
			};

		} // namespace detail

		template <typename Tp, typename AutonmPolicy>
		class list :
					protected kerbal::container::detail::list_allocator_unrelated<Tp>,
					private kerbal::utility::noncopyable
		{
			private:
				typedef kerbal::container::detail::list_type_unrelated				list_type_unrelated;
				typedef kerbal::container::detail::list_allocator_unrelated<Tp>		list_allocator_unrelated;

			public:
				typedef kerbal::autonm::detail::autonm_list_node<Tp> auto_node;

			public:
				typedef Tp							value_type;
				typedef const value_type			const_type;
				typedef value_type&					reference;
				typedef const value_type&			const_reference;
				typedef value_type*					pointer;
				typedef const value_type*			const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&				rvalue_reference;
				typedef const value_type&&			const_rvalue_reference;
#		endif

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef kerbal::container::detail::list_iter<Tp>			iterator;
				typedef kerbal::container::detail::list_kiter<Tp>			const_iterator;
				typedef kerbal::iterator::reverse_iterator<iterator>		reverse_iterator;
				typedef kerbal::iterator::reverse_iterator<const_iterator>	const_reverse_iterator;

			public:
				KERBAL_CONSTEXPR20
				list()
						KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_default_constructible<list_allocator_unrelated>::value
						)
					: list_allocator_unrelated(kerbal::container::detail::init_list_node_ptr_to_self_tag())
				{
				}

//#		if __cplusplus >= 201103L
//
//				KERBAL_CONSTEXPR20
//				list(list && src)
//						KERBAL_CONDITIONAL_NOEXCEPT(
//								std::is_nothrow_move_constructible<list_allocator_unrelated>::value
//						)
//					: list_allocator_unrelated(kerbal::compatibility::move(src))
//				{
//				}
//
//#		endif

			public:

			//===================
			//element access

				using list_allocator_unrelated::front;
				using list_allocator_unrelated::back;

			//===================
			//iterator

				using list_allocator_unrelated::begin;
				using list_allocator_unrelated::end;

				using list_allocator_unrelated::cbegin;
				using list_allocator_unrelated::cend;

				using list_allocator_unrelated::rbegin;
				using list_allocator_unrelated::rend;

				using list_allocator_unrelated::crbegin;
				using list_allocator_unrelated::crend;

				using list_allocator_unrelated::nth;
				using list_allocator_unrelated::index_of;

			//===================
			//capacity

				using list_allocator_unrelated::empty;
				using list_allocator_unrelated::size;
				using list_allocator_unrelated::max_size;

			//===================
			//insert

				KERBAL_CONSTEXPR20
				void push_front(auto_node & node) KERBAL_NOEXCEPT
				{
					list_type_unrelated::_K_hook_node(this->list_type_unrelated::basic_begin(), &node);
				}

				KERBAL_CONSTEXPR20
				void push_back(auto_node & node) KERBAL_NOEXCEPT
				{
					list_type_unrelated::_K_hook_node(this->list_type_unrelated::basic_end(), &node);
				}

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, auto_node & node) KERBAL_NOEXCEPT
				{
					list_type_unrelated::_K_hook_node(pos, &node);
					return iterator(&node);
				}

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_forward_compatible_iterator<ForwardIterator>::value,
						typename list<Tp, AutonmPolicy>::iterator
				>::type
				insert(const_iterator pos, ForwardIterator first, ForwardIterator last)
				{
					if (first == last) {
						return pos.cast_to_mutable();
					}

					iterator start(&*first);
					ForwardIterator next(first); ++next;

					while (next != last)
					{
						(*first).next = &*next;
						(*next).prev = &*first;
						first = next;
						++next;
					}

					list_type_unrelated::_K_hook_node(pos, start.current, &*first);
					return start;
				}

				using list_allocator_unrelated::reverse;
				using list_allocator_unrelated::reverse_unstable;
				using list_allocator_unrelated::reverse_fast;

				using list_allocator_unrelated::rotate;

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void merge(list & other, BinaryPredict cmp)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(list_allocator_unrelated::merge(static_cast<list_allocator_unrelated&>(other), cmp))
								)
				{
					list_allocator_unrelated::_K_merge(static_cast<list_allocator_unrelated&>(other), cmp);
				}

				KERBAL_CONSTEXPR20
				void merge(list & other)
				{
					list_allocator_unrelated::_K_merge(static_cast<list_allocator_unrelated&>(other));
				}

				using list_allocator_unrelated::sort;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list & other) KERBAL_NOEXCEPT
				{
					list_type_unrelated::_K_splice(pos, other);
				}

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list & /*other*/, const_iterator opos) KERBAL_NOEXCEPT
				{
					list_type_unrelated::_K_splice(pos, opos);
				}

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list & /*other*/, const_iterator first, const_iterator last) KERBAL_NOEXCEPT
				{
					list_type_unrelated::_K_splice(pos, first, last);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list&& other) KERBAL_NOEXCEPT
				{
					list_type_unrelated::_K_splice(pos, other);
				}

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator+=(list&& with) KERBAL_NOEXCEPT
				{
					this->splice(this->cend(), kerbal::compatibility::move(with));
					return *this;
				}

#		endif

		};

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator==(const list<Tp, AutonmPolicy> & lhs, const list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator!=(const list<Tp, AutonmPolicy> & lhs, const list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator<(const list<Tp, AutonmPolicy> & lhs, const list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator>(const list<Tp, AutonmPolicy> & lhs, const list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator<=(const list<Tp, AutonmPolicy> & lhs, const list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator>=(const list<Tp, AutonmPolicy> & lhs, const list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace autonm

} // namespace kerbal

#endif // KERBAL_AUTONM_LIST_HPP
