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

#include <kerbal/container/detail/container_rebind_allocator_overload.hpp>
#include <kerbal/container/detail/list_base/list_node.hpp>
#include <kerbal/container/detail/list_base/list_iterator.hpp>
#include <kerbal/container/detail/list_base.hpp>

#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace autonm
	{

		namespace detail
		{

			template <typename Tp>
			class autonm_list_node :
					public kerbal::container::detail::list_node<Tp>
			{
				private:
					typedef kerbal::container::detail::list_node<Tp> super;

				public:
					KERBAL_CONSTEXPR
					autonm_list_node() :
							super(kerbal::utility::in_place_t())
					{
					}


#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit autonm_list_node(kerbal::utility::in_place_t in_place, Args&& ... args)
							: super(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

#		else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit autonm_list_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

			};

			template <typename Tp, typename SemiAllocator>
			struct list_typedef_helper
			{
					typedef kerbal::autonm::detail::autonm_list_node<Tp>									auto_node;
					typedef SemiAllocator																	semi_allocator_type;
					typedef kerbal::container::detail::container_rebind_allocator_overload<
						semi_allocator_type, auto_node
					>																						list_semi_allocator_overload;
			};

		} // namespace detail

		template <typename Tp, typename SemiAllocator>
		class list :
				protected kerbal::autonm::detail::list_typedef_helper<Tp, SemiAllocator>::list_semi_allocator_overload ,
				protected kerbal::container::detail::list_allocator_unrelated<Tp>,
				private kerbal::utility::noncopyable
		{
			private:
				typedef kerbal::autonm::detail::list_typedef_helper<Tp, SemiAllocator>	list_typedef_helper;
				typedef kerbal::container::detail::list_type_unrelated					list_type_unrelated;
				typedef typename list_typedef_helper::list_semi_allocator_overload		list_semi_allocator_overload;
				typedef kerbal::container::detail::list_allocator_unrelated<Tp>			list_allocator_unrelated;

			public:
				typedef typename list_typedef_helper::auto_node				auto_node;

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

				typedef typename list_allocator_unrelated::iterator					iterator;
				typedef typename list_allocator_unrelated::const_iterator 			const_iterator;
				typedef typename list_allocator_unrelated::reverse_iterator			reverse_iterator;
				typedef typename list_allocator_unrelated::const_reverse_iterator 	const_reverse_iterator;

			public:
				typedef SemiAllocator										semi_allocator_type;

			private:
				typedef typename list_semi_allocator_overload::rebind_allocator_type 		node_semi_allocator_type;
				typedef typename list_semi_allocator_overload::rebind_allocator_traits		node_semi_allocator_traits;

			private:
				KERBAL_CONSTEXPR14
				node_semi_allocator_type & semi_alloc() KERBAL_NOEXCEPT
				{
					return this->list_semi_allocator_overload::alloc();
				}

				KERBAL_CONSTEXPR
				const node_semi_allocator_type & semi_alloc() const KERBAL_NOEXCEPT
				{
					return this->list_semi_allocator_overload::alloc();
				}

			public:

			//===================
			// construct/copy/destroy

				KERBAL_CONSTEXPR20
				list()
						KERBAL_CONDITIONAL_NOEXCEPT(
								list_allocator_unrelated::is_nothrow_init_to_self_constructible::value
						) :
						list_allocator_unrelated(kerbal::container::detail::init_list_node_ptr_to_self_tag())
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list(list && src)
						KERBAL_CONDITIONAL_NOEXCEPT(
								list_allocator_unrelated::is_nothrow_move_constructible::value
						) :
						list_allocator_unrelated(kerbal::compatibility::move(src))
				{
				}

#		endif

				KERBAL_CONSTEXPR20
				~list()
				{
					this->list_allocator_unrelated::destroy_using_allocator(this->semi_alloc());
				}

			public:

			//===================
			// element access

				using list_allocator_unrelated::front;
				using list_allocator_unrelated::back;

			//===================
			// iterator

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
			// capacity

				using list_allocator_unrelated::empty;
				using list_allocator_unrelated::size;

			//===================
			// insert

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
					return (++pos).cast_to_mutable();
				}

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_forward_compatible_iterator<ForwardIterator>::value,
						iterator
				>::type
				insert(const_iterator pos, ForwardIterator first, ForwardIterator last)
				{
					if (first == last) {
						return pos.cast_to_mutable();
					}

					ForwardIterator it(first);
					ForwardIterator next(first); ++next;

					while (next != last) {
						(*it).next = &*next;
						(*next).prev = &*it;
						it = next;
						++next;
					}

					list_type_unrelated::_K_hook_node(pos, &*first, &*it);
					return iterator(&*first);
				}

/*
				template <typename ForwardIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_forward_compatible_iterator<ForwardIterator>::value,
						iterator
				>::type
				insert(const_iterator pos, ForwardIterator first, ForwardIterator last)
				{
					if (first == last) {
						return pos.cast_to_mutable();
					}

					ForwardIterator start(first);
					do {
						list_type_unrelated::_K_hook_node(pos, &*first);
						++first;
					} while (first != last);
					return iterator(&*start);
				}
*/

			//===================
			// erase

				KERBAL_CONSTEXPR20
				void clear()
				{
					list_allocator_unrelated::clear_using_allocator(this->semi_alloc());
				}

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator pos)
				{
					return list_allocator_unrelated::erase_using_allocator(this->semi_alloc(), pos);
				}

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator first, const_iterator last)
				{
					return list_allocator_unrelated::erase_using_allocator(this->semi_alloc(), first, last);
				}

				KERBAL_CONSTEXPR20
				void pop_front()
				{
					list_allocator_unrelated::pop_front_using_allocator(this->semi_alloc());
				}

				KERBAL_CONSTEXPR20
				void pop_back()
				{
					list_allocator_unrelated::pop_back_using_allocator(this->semi_alloc());
				}

			//===================
			// operation

				KERBAL_CONSTEXPR20
				void reverse(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
				{
					this->list_allocator_unrelated::_K_reverse(first, last);
				}

				KERBAL_CONSTEXPR20
				void reverse() KERBAL_NOEXCEPT
				{
					this->list_allocator_unrelated::reverse();
				}

				KERBAL_CONSTEXPR20
				iterator rotate(const_iterator first, const_iterator n_first, const_iterator last) KERBAL_NOEXCEPT
				{
					return this->list_allocator_unrelated::rotate(first, n_first, last);
				}

				using list_allocator_unrelated::rotate;

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void merge(list & other, BinaryPredict cmp)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<list>()->list_allocator_unrelated::_K_merge(static_cast<list_allocator_unrelated&>(other), cmp)
							)
						)
				{
					this->list_allocator_unrelated::_K_merge(static_cast<list_allocator_unrelated&>(other), cmp);
				}

				KERBAL_CONSTEXPR20
				void merge(list & other)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<list>()->list_allocator_unrelated::_K_merge(static_cast<list_allocator_unrelated&>(other))
							)
						)
				{
					this->list_allocator_unrelated::_K_merge(static_cast<list_allocator_unrelated&>(other));
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void sort(const_iterator first, const_iterator last, BinaryPredict cmp)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(list_allocator_unrelated::_K_sort(first, last, cmp))
						)
				{
					list_allocator_unrelated::_K_sort(first, last, cmp);
				}

				KERBAL_CONSTEXPR20
				void sort(const_iterator first, const_iterator last)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(list_allocator_unrelated::_K_sort(first, last))
						)
				{
					list_allocator_unrelated::_K_sort(first, last);
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void sort(BinaryPredict cmp)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<list>()->list_allocator_unrelated::sort(cmp))
						)
				{
					this->list_allocator_unrelated::sort(cmp);
				}

				KERBAL_CONSTEXPR20
				void sort()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<list>()->list_allocator_unrelated::sort())
						)
				{
					this->list_allocator_unrelated::sort();
				}

				KERBAL_CONSTEXPR20
				size_type remove(const_reference val)
				{
					return list_allocator_unrelated::remove_using_allocator(this->semi_alloc(), val);
				}

				KERBAL_CONSTEXPR20
				size_type remove(const_iterator first, const_iterator last, const_reference val)
				{
					return list_allocator_unrelated::remove_using_allocator(this->semi_alloc(), first, last, val);
				}

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_if(UnaryPredicate predicate)
				{
					return list_allocator_unrelated::remove_if_using_allocator(this->semi_alloc(), predicate);
				}

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_if(const_iterator first, const_iterator last, UnaryPredicate predicate)
				{
					return list_allocator_unrelated::remove_if_using_allocator(this->semi_alloc(), first, last, predicate);
				}

				KERBAL_CONSTEXPR20
				size_type unique()
				{
					return list_allocator_unrelated::unique_using_allocator(this->semi_alloc());
				}

				template <typename BinaryPredicate>
				KERBAL_CONSTEXPR20
				size_type unique(BinaryPredicate pred)
				{
					return list_allocator_unrelated::unique_using_allocator(this->semi_alloc(), pred);
				}

				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last)
				{
					return list_allocator_unrelated::unique_using_allocator(this->semi_alloc(), first, last);
				}

				template <typename BinaryPredicate>
				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last, BinaryPredicate pred)
				{
					return list_allocator_unrelated::unique_using_allocator(this->semi_alloc(), first, last, pred);
				}

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
				void splice(const_iterator pos, list && other) KERBAL_NOEXCEPT
				{
					list_type_unrelated::_K_splice(pos, other);
				}

#		endif

				KERBAL_CONSTEXPR20
				void swap(list & with) KERBAL_NOEXCEPT
				{
					list_semi_allocator_overload::k_swap_allocator_if_propagate(
						static_cast<list_semi_allocator_overload&>(*this),
						static_cast<list_semi_allocator_overload&>(with)
					);
					list_type_unrelated::_K_swap_type_unrelated(
						static_cast<list_type_unrelated &>(*this),
						static_cast<list_type_unrelated &>(with)
					);
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				static void set_difference(list & l1, const list & l2, list & lto, BinaryPredict cmp)
				{
					list_allocator_unrelated::_K_set_difference(l1, l2, lto, cmp);
				}

				KERBAL_CONSTEXPR20
				static void set_difference(list & l1, const list & l2, list & lto)
				{
					list_allocator_unrelated::_K_set_difference(l1, l2, lto);
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				static void set_intersection(list & l1, list & l2, list & lto, BinaryPredict cmp)
				{
					list_allocator_unrelated::_K_set_intersection(l1, l2, lto, cmp);
				}

				KERBAL_CONSTEXPR20
				static void set_intersection(list & l1, list & l2, list & lto)
				{
					list_allocator_unrelated::_K_set_intersection(l1, l2, lto);
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				static void set_symmetric_difference(list & l1, list & l2, list & lto, BinaryPredict cmp)
				{
					list_allocator_unrelated::_K_set_symmetric_difference(l1, l2, lto, cmp);
				}

				KERBAL_CONSTEXPR20
				static void set_symmetric_difference(list & l1, list & l2, list & lto)
				{
					list_allocator_unrelated::_K_set_symmetric_difference(l1, l2, lto);
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				static void set_union(list & l1, list & l2, list & lto, BinaryPredict cmp)
				{
					list_allocator_unrelated::_K_set_union(l1, l2, lto, cmp);
				}

				KERBAL_CONSTEXPR20
				static void set_union(list & l1, list & l2, list & lto)
				{
					list_allocator_unrelated::_K_set_union(l1, l2, lto);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator+=(list && with) KERBAL_NOEXCEPT
				{
					this->splice(this->cend(), kerbal::compatibility::move(with));
					return *this;
				}

#		endif

		};

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator==(const list<Tp, SemiAllocator> & lhs, const list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator!=(const list<Tp, SemiAllocator> & lhs, const list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator<(const list<Tp, SemiAllocator> & lhs, const list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator>(const list<Tp, SemiAllocator> & lhs, const list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator<=(const list<Tp, SemiAllocator> & lhs, const list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator>=(const list<Tp, SemiAllocator> & lhs, const list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace autonm

	namespace algorithm
	{

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		void swap(kerbal::autonm::list<Tp, SemiAllocator> & a, kerbal::autonm::list<Tp, SemiAllocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Tp, typename SemiAllocator>
	KERBAL_CONSTEXPR20
	void swap(kerbal::autonm::list<Tp, SemiAllocator> & a, kerbal::autonm::list<Tp, SemiAllocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_AUTONM_LIST_HPP
