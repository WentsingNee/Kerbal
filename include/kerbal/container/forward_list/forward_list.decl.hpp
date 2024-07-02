/**
 * @file       forward_list.decl.hpp
 * @brief
 * @date       2021-01-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_DECL_HPP
#define KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_DECL_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/declval.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <memory>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <cstddef>

#include <kerbal/container/detail/container_rebind_allocator_overload.hpp>
#include <kerbal/container/detail/forward_list_base/forward_list_base.decl.hpp>

#include <kerbal/container/detail/forward_list_base/forward_list_iterator.hpp>
#include <kerbal/container/detail/single_list_base/single_list_node.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename T, typename Allocator>
			struct fl_typedef_helper
			{
					typedef kerbal::container::detail::fl_type_only<T>			fl_type_only;
					typedef typename fl_type_only::node 						node;
					typedef Allocator											allocator_type;
					typedef kerbal::container::detail::container_rebind_allocator_overload<
							allocator_type, node
					>															fl_allocator_overload;
			};

		} // namespace detail


		namespace detail
		{

			template <typename T, typename Allocator>
			struct forward_list_node_size_helper
			{
				typedef kerbal::type_traits::integral_constant<
					std::size_t,
					sizeof(typename kerbal::container::forward_list<T, Allocator>::node)
				> type;
			};

		} // namespace detail

		template <typename T, typename Allocator>
		struct forward_list_node_size :
			kerbal::container::detail::forward_list_node_size_helper<T, Allocator>::type
		{
		};


		template <typename T, typename Allocator>
		class forward_list :
			protected detail::fl_typedef_helper<T, Allocator>::fl_allocator_overload,
			protected detail::fl_typedef_helper<T, Allocator>::fl_type_only
		{
			private:
				typedef kerbal::container::detail::fl_type_unrelated			fl_type_unrelated;
				typedef detail::fl_typedef_helper<T, Allocator>					fl_typedef_helper;
				typedef typename fl_typedef_helper::fl_allocator_overload 		fl_allocator_overload;
				typedef typename fl_typedef_helper::fl_type_only				fl_type_only;

			public:
				typedef typename fl_type_only::value_type				value_type;
				typedef typename fl_type_only::const_type				const_type;
				typedef typename fl_type_only::reference				reference;
				typedef typename fl_type_only::const_reference			const_reference;
				typedef typename fl_type_only::pointer					pointer;
				typedef typename fl_type_only::const_pointer			const_pointer;

#		if __cplusplus >= 201103L
				typedef typename fl_type_only::rvalue_reference			rvalue_reference;
				typedef typename fl_type_only::const_rvalue_reference	const_rvalue_reference;
#		endif

				typedef typename fl_type_only::size_type				size_type;
				typedef typename fl_type_only::difference_type			difference_type;

				typedef typename fl_type_only::iterator					iterator;
				typedef typename fl_type_only::const_iterator			const_iterator;

			private:
				typedef typename fl_type_only::node_base				node_base;
				typedef typename fl_type_only::node						node;

				friend struct kerbal::container::detail::forward_list_node_size_helper<T, Allocator>;

			public:
				typedef Allocator														allocator_type;

			private:
				typedef typename fl_allocator_overload::rebind_allocator_type			node_allocator_type;
				typedef typename fl_allocator_overload::rebind_allocator_traits 		node_allocator_traits;

			private:

				using fl_allocator_overload::alloc;

			public:

			//===================
			// construct/copy/destroy

#		if __cplusplus >= 201103L

				forward_list() = default;

#		else

				forward_list();

#		endif

				KERBAL_CONSTEXPR20
				explicit
				forward_list(const Allocator & alloc)
					KERBAL_CONDITIONAL_NOEXCEPT(
						fl_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
						fl_type_only::is_nothrow_default_constructible::value
					)
				;

				KERBAL_CONSTEXPR20
				forward_list(const forward_list & src);

				KERBAL_CONSTEXPR20
				forward_list(const forward_list & src, const Allocator & alloc);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list(forward_list && src)
					KERBAL_CONDITIONAL_NOEXCEPT(
						fl_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<Allocator &&>::IS_TRUE::value &&
						fl_type_only::is_nothrow_move_constructible::value
					)
				;

				KERBAL_CONSTEXPR20
				forward_list(forward_list && src, const Allocator & alloc)
					KERBAL_CONDITIONAL_NOEXCEPT(
						fl_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
						fl_type_only::template is_nothrow_move_constructible_using_allocator<node_allocator_type>::value
					)
				;

#		endif

				KERBAL_CONSTEXPR20
				explicit
				forward_list(size_type n);

				KERBAL_CONSTEXPR20
				forward_list(size_type n, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				forward_list(size_type n, const_reference val);

				KERBAL_CONSTEXPR20
				forward_list(size_type n, const_reference val, const Allocator & alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				forward_list(
					InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				forward_list(
					InputIterator first, InputIterator last,
					const Allocator & alloc,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list(std::initializer_list<value_type> ilist);

				KERBAL_CONSTEXPR20
				forward_list(std::initializer_list<value_type> ilist, const Allocator & alloc);

#		else

				forward_list(const kerbal::assign::assign_list<void> & ilist);

				template <typename U>
				forward_list(const kerbal::assign::assign_list<U> & ilist);

				forward_list(const kerbal::assign::assign_list<void> & ilist, const Allocator & alloc);

				template <typename U>
				forward_list(const kerbal::assign::assign_list<U> & ilist, const Allocator & alloc);

#		endif

				KERBAL_CONSTEXPR20
				~forward_list();

			//===================
			// assign

				KERBAL_CONSTEXPR20
				forward_list & operator=(const forward_list & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list & operator=(forward_list && src)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::utility::declthis<forward_list>()->assign(kerbal::compatibility::move(src))
						)
					)
				;

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list & operator=(std::initializer_list<value_type> ilist);

#		else

				forward_list & operator=(const kerbal::assign::assign_list<void> & ilist);

				template <typename U>
				forward_list & operator=(const kerbal::assign::assign_list<U> & ilist);

#		endif

				KERBAL_CONSTEXPR20
				void assign(const forward_list & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(forward_list && src)
					KERBAL_CONDITIONAL_NOEXCEPT(
						fl_type_only::template is_nothrow_move_assign_using_allocator<node_allocator_type>::value
					)
				;

#		endif

				KERBAL_CONSTEXPR20
				void assign(size_type count, const_reference val);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				assign(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> ilist);

#		else

				void assign(const kerbal::assign::assign_list<void> & ilist);

				template <typename U>
				void assign(const kerbal::assign::assign_list<U> & ilist);

#		endif

			//===================
			// element access

				using fl_type_only::front;

			//===================
			// iterator

				using fl_type_only::before_begin;
				using fl_type_only::cbefore_begin;

				using fl_type_only::begin;
				using fl_type_only::cbegin;

				using fl_type_only::end;
				using fl_type_only::cend;

				using fl_type_only::nth;
				using fl_type_only::index_of;

			//===================
			// capacity

				using fl_type_only::empty;
				using fl_type_only::size;

				KERBAL_CONSTEXPR
				size_type max_size() const KERBAL_NOEXCEPT
				{
					return node_allocator_traits::max_size(this->alloc());
				}

			//===================
			// lookup

				using fl_type_only::find_before_if;
				using fl_type_only::find_before;

			//===================
			// insert

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				iterator emplace_after(const_iterator before_pos, Args && ... args);

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator emplace_after(const_iterator before_pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif

				KERBAL_CONSTEXPR20
				iterator insert_after(const_iterator before_pos, const_reference val);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert_after(const_iterator before_pos, rvalue_reference val);

#		endif

				KERBAL_CONSTEXPR20
				iterator insert_after(const_iterator before_pos, size_type n, const_reference val);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					iterator
				>::type
				insert_after(const_iterator before_pos, InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert_after(const_iterator before_pos, std::initializer_list<value_type> ilist);

#		else

				iterator insert_after(const_iterator before_pos, const kerbal::assign::assign_list<void> & ilist);

				template <typename U>
				iterator insert_after(const_iterator before_pos, const kerbal::assign::assign_list<U> & ilist);

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				reference emplace_front(Args && ... args);

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				reference emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)); \

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif

				KERBAL_CONSTEXPR20
				void push_front(const_reference val);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push_front(rvalue_reference val);

#		endif

			//===================
			// erase

				KERBAL_CONSTEXPR20
				iterator erase_after(const_iterator before_pos);

				KERBAL_CONSTEXPR20
				iterator erase_after(const_iterator before_first, const_iterator last);

				KERBAL_CONSTEXPR20
				void pop_front();

				KERBAL_CONSTEXPR20
				void clear()
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::utility::declthis<fl_type_only>()->k_clear_using_allocator(
								kerbal::utility::declthis<forward_list>()->alloc()
							)
						)
					)
				;

			//===================
			// operation

				KERBAL_CONSTEXPR20
				void resize(size_type count);

				KERBAL_CONSTEXPR20
				void resize(size_type count, const_reference value);

				KERBAL_CONSTEXPR20
				void swap(forward_list & with)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							fl_allocator_overload::k_swap_allocator_if_propagate(
								kerbal::utility::declval<fl_allocator_overload &>(),
								kerbal::utility::declval<fl_allocator_overload &>()
							)
						) &&
						noexcept(
							fl_type_unrelated::k_swap_type_unrelated(
								kerbal::utility::declval<fl_type_unrelated &>(),
								kerbal::utility::declval<fl_type_unrelated &>()
							)
						)
					)
				;

				KERBAL_CONSTEXPR20
				void iter_swap_after(const_iterator before_a, const_iterator before_b) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void reverse_after(const_iterator before_first, const_iterator last) KERBAL_NOEXCEPT;

				using fl_type_unrelated::reverse;

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void merge(forward_list & other, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void merge(forward_list & other);

#		if __cplusplus >= 201103L

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void merge(forward_list && other, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void merge(forward_list && other);

#		endif

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void sort_after(const_iterator before_first, const_iterator last, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void sort_after(const_iterator before_first, const_iterator last);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void sort(BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void sort();

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_after_if(const_iterator before_first, const_iterator last, UnaryPredicate predicate);

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_if(UnaryPredicate predicate);

				KERBAL_CONSTEXPR20
				size_type remove_after(const_iterator before_first, const_iterator last, const_reference val);

				KERBAL_CONSTEXPR20
				size_type remove(const_reference val);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last, BinaryPredict equal_to);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				size_type unique(BinaryPredict equal_to);

				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last);

				KERBAL_CONSTEXPR20
				size_type unique();

				KERBAL_CONSTEXPR20
				void splice_after(
					const_iterator before_pos, forward_list & other
				) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice_after(
					const_iterator before_pos, forward_list & other,
					const_iterator opos
				) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice_after(
					const_iterator before_pos, forward_list & other,
					const_iterator before_first, const_iterator last
				) KERBAL_NOEXCEPT;

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void splice_after(
					const_iterator before_pos, forward_list && other
				) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice_after(
					const_iterator before_pos, forward_list && other,
					const_iterator opos
				) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice_after(
					const_iterator before_pos, forward_list && other,
					const_iterator before_first, const_iterator last
				) KERBAL_NOEXCEPT;

#		endif

		};

#	if __cplusplus >= 201703L

		template <
			typename InputIterator,
			typename Alloc =
				std::allocator<typename kerbal::iterator::iterator_traits<InputIterator>::value_type>
		>
		forward_list(InputIterator, InputIterator, Alloc = Alloc()) ->
		forward_list<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Alloc>;

		template <typename T, typename Alloc = std::allocator<T> >
		forward_list(std::initializer_list<T>, Alloc = Alloc()) ->
		forward_list<T, Alloc>;

#	endif


		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator==(
			const forward_list<T, Allocator> & lhs,
			const forward_list<T, Allocator> & rhs
		)
		{
			return kerbal::compare::sequence_equal_to(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator!=(
			const forward_list<T, Allocator> & lhs,
			const forward_list<T, Allocator> & rhs
		)
		{
			return kerbal::compare::sequence_not_equal_to(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<(
			const forward_list<T, Allocator> & lhs,
			const forward_list<T, Allocator> & rhs
		)
		{
			return kerbal::compare::sequence_less(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>(
			const forward_list<T, Allocator> & lhs,
			const forward_list<T, Allocator> & rhs
		)
		{
			return kerbal::compare::sequence_greater(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<=(
			const forward_list<T, Allocator> & lhs,
			const forward_list<T, Allocator> & rhs
		)
		{
			return kerbal::compare::sequence_less_equal(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>=(
			const forward_list<T, Allocator> & lhs,
			const forward_list<T, Allocator> & rhs
		)
		{
			return kerbal::compare::sequence_greater_equal(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

	} // namespace container

	namespace algorithm
	{

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::container::forward_list<T, Allocator> & a,
			kerbal::container::forward_list<T, Allocator> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename Allocator>
	KERBAL_CONSTEXPR20
	void swap(
		kerbal::container::forward_list<T, Allocator> & a,
		kerbal::container::forward_list<T, Allocator> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_DECL_HPP
