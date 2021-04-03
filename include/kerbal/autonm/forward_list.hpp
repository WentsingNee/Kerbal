/**
 * @file       forward_list.hpp
 * @brief
 * @date       2021-01-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_FORWARD_LIST_HPP
#define KERBAL_AUTONM_FORWARD_LIST_HPP

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/detail/single_list_node.hpp>
#include <kerbal/container/detail/forward_list_base.hpp>
#include <kerbal/container/detail/forward_list_iterator.hpp>
#include <kerbal/utility/noncopyable.hpp>

namespace kerbal
{

	namespace autonm
	{

		namespace detail
		{

			template <typename Tp>
			class autonm_sl_node : public kerbal::container::detail::sl_node<Tp>
			{
				private:
					typedef kerbal::container::detail::sl_node<Tp> super;

				public:
					KERBAL_CONSTEXPR
					autonm_sl_node() : super(kerbal::utility::in_place_t())
					{
					}
			};

		} // namespace detail

		template <typename Tp, typename AutonmPolicy>
		class forward_list :
					protected kerbal::container::detail::fl_allocator_unrelated<Tp>,
					private kerbal::utility::noncopyable
		{
			private:
				typedef kerbal::container::detail::fl_type_unrelated				fl_type_unrelated;
				typedef kerbal::container::detail::fl_allocator_unrelated<Tp>		fl_allocator_unrelated;

			public:
				typedef kerbal::autonm::detail::autonm_sl_node<Tp> auto_node;

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

				typedef kerbal::container::detail::fl_iter<Tp>				iterator;
				typedef kerbal::container::detail::fl_kiter<Tp>				const_iterator;

			public:
				KERBAL_CONSTEXPR20
				forward_list()
						KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_default_constructible<fl_allocator_unrelated>::value
						)
					: fl_allocator_unrelated()
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list(forward_list && src)
						KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_move_constructible<fl_allocator_unrelated>::value
						)
					: fl_allocator_unrelated(kerbal::compatibility::move(src))
				{
				}

#		endif

			//===================
			//element access

				using fl_allocator_unrelated::front;

			//===================
			//iterator

				using fl_allocator_unrelated::before_begin;
				using fl_allocator_unrelated::cbefore_begin;

				using fl_allocator_unrelated::begin;
				using fl_allocator_unrelated::end;

				using fl_allocator_unrelated::cbegin;
				using fl_allocator_unrelated::cend;

				using fl_allocator_unrelated::nth;
				using fl_allocator_unrelated::index_of;

			//===================
			//capacity

				using fl_type_unrelated::empty;
//				using fl_type_unrelated::size;
				using fl_allocator_unrelated::max_size;

			//===================
			//insert

				KERBAL_CONSTEXPR20
				void push_front(auto_node & node) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_hook_node_after(this->basic_before_begin(), &node);
				}

				KERBAL_CONSTEXPR20
				iterator insert_after(const_iterator pos, auto_node & node) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_hook_node_after(pos, &node);
					return iterator(&node);
				}

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_forward_compatible_iterator<ForwardIterator>::value,
						typename forward_list<Tp, AutonmPolicy>::iterator
				>::type
				insert_after(const_iterator pos, ForwardIterator first, ForwardIterator last)
				{
					if (first == last) {
						return pos.cast_to_mutable();
					}
					iterator ret(&*first);
					do {
						fl_type_unrelated::_K_hook_node_after(pos, &*first);
						++first;
					} while (first != last);
					return ret;
				}

				using fl_allocator_unrelated::reverse;

//				using fl_allocator_unrelated::rotate;

//				template <typename BinaryPredict>
//				KERBAL_CONSTEXPR20
//				void merge(list & other, BinaryPredict cmp)
//								KERBAL_CONDITIONAL_NOEXCEPT(
//										noexcept(fl_allocator_unrelated::merge(static_cast<fl_allocator_unrelated&>(other), cmp))
//								)
//				{
//					fl_allocator_unrelated::merge(static_cast<fl_allocator_unrelated&>(other), cmp);
//				}
//
//				KERBAL_CONSTEXPR20
//				void merge(list & other)
//				{
//					fl_allocator_unrelated::merge(static_cast<fl_allocator_unrelated&>(other));
//				}
//
//				using fl_allocator_unrelated::sort;

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list & other) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_splice_after(pos, other);
				}

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list & /*other*/, const_iterator opos) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_splice_after(pos, opos);
				}

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list & /*other*/, const_iterator first, const_iterator last) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_splice_after(pos, first, last);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list && other) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_splice_after(pos, other);
				}

#		endif

		};

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator==(const forward_list<Tp, AutonmPolicy> & lhs, const forward_list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator!=(const forward_list<Tp, AutonmPolicy> & lhs, const forward_list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator<(const forward_list<Tp, AutonmPolicy> & lhs, const forward_list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator>(const forward_list<Tp, AutonmPolicy> & lhs, const forward_list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator<=(const forward_list<Tp, AutonmPolicy> & lhs, const forward_list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename AutonmPolicy>
		KERBAL_CONSTEXPR20
		bool operator>=(const forward_list<Tp, AutonmPolicy> & lhs, const forward_list<Tp, AutonmPolicy> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace autonm

} // namespace kerbal

#endif // KERBAL_AUTONM_FORWARD_LIST_HPP
