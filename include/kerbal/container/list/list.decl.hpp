/**
 * @file       list.decl.hpp
 * @brief
 * @date       2020-02-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_LIST_LIST_DECL_HPP
#define KERBAL_CONTAINER_LIST_LIST_DECL_HPP

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
#include <kerbal/container/detail/list_base/list_base.decl.hpp>

#include <kerbal/container/detail/list_base/list_iterator.hpp>
#include <kerbal/container/detail/list_base/list_node.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp, typename Allocator>
			struct list_typedef_helper
			{
					typedef kerbal::container::detail::list_type_only<Tp>					list_type_only;
					typedef typename list_type_only::node 									node;
					typedef Allocator																	allocator_type;
					typedef kerbal::container::detail::container_rebind_allocator_overload<
							allocator_type, node
					>																					list_allocator_overload;
			};

		} // namespace detail


		namespace detail
		{

			template <typename Tp, typename Allocator>
			struct list_node_size_helper
			{
					typedef kerbal::type_traits::integral_constant<
							std::size_t,
							sizeof(typename kerbal::container::list<Tp, Allocator>::node)
					> type;
			};

		} // namespace detail

		template <typename Tp, typename Allocator>
		struct list_node_size :
				kerbal::container::detail::list_node_size_helper<Tp, Allocator>::type
		{
		};


		template <typename Tp, typename Allocator>
		class list:
				protected detail::list_typedef_helper<Tp, Allocator>::list_allocator_overload,
				protected detail::list_typedef_helper<Tp, Allocator>::list_type_only
		{
			private:
				typedef kerbal::container::detail::list_type_unrelated				list_type_unrelated;
				typedef detail::list_typedef_helper<Tp, Allocator>					list_typedef_helper;
				typedef typename list_typedef_helper::list_allocator_overload 		list_allocator_overload;
				typedef typename list_typedef_helper::list_type_only				list_type_only;

			public:
				typedef typename list_type_only::value_type					value_type;
				typedef typename list_type_only::const_type					const_type;
				typedef typename list_type_only::reference					reference;
				typedef typename list_type_only::const_reference			const_reference;
				typedef typename list_type_only::pointer					pointer;
				typedef typename list_type_only::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename list_type_only::rvalue_reference			rvalue_reference;
				typedef typename list_type_only::const_rvalue_reference		const_rvalue_reference;
#		endif

				typedef typename list_type_only::size_type					size_type;
				typedef typename list_type_only::difference_type			difference_type;

				typedef typename list_type_only::iterator					iterator;
				typedef typename list_type_only::const_iterator				const_iterator;
				typedef typename list_type_only::reverse_iterator			reverse_iterator;
				typedef typename list_type_only::const_reverse_iterator		const_reverse_iterator;

			private:
				typedef typename list_type_only::node_base					node_base;
				typedef typename list_type_only::node						node;

				friend struct kerbal::container::detail::list_node_size_helper<Tp, Allocator>;

			public:
				typedef Allocator														allocator_type;

			private:
				typedef typename list_allocator_overload::rebind_allocator_type			node_allocator_type;
				typedef typename list_allocator_overload::rebind_allocator_traits 		node_allocator_traits;

			private:

				using list_allocator_overload::alloc;

			public:

			//===================
			// construct/copy/destroy

				KERBAL_CONSTEXPR20
				list() KERBAL_CONDITIONAL_NOEXCEPT(
						list_allocator_overload::try_test_is_nothrow_default_constructible::IS_TRUE::value &&
						list_type_only::is_nothrow_init_to_self_constructible::value
				);

				KERBAL_CONSTEXPR20
				explicit
				list(const Allocator& alloc) KERBAL_CONDITIONAL_NOEXCEPT(
						list_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
						list_type_only::is_nothrow_init_to_self_constructible::value
				);

				KERBAL_CONSTEXPR20
				list(const list & src);

				KERBAL_CONSTEXPR20
				list(const list & src, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				explicit
				list(size_type n);

				KERBAL_CONSTEXPR20
				list(size_type n, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				list(size_type n, const_reference val);

				KERBAL_CONSTEXPR20
				list(size_type n, const_reference val, const Allocator& alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				list(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				list(InputIterator first, InputIterator last, const Allocator& alloc,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list(list && src) KERBAL_CONDITIONAL_NOEXCEPT(
						list_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<Allocator &&>::IS_TRUE::value &&
						list_type_only::is_nothrow_move_constructible::value
				);

				KERBAL_CONSTEXPR20
				list(list && src, const Allocator& alloc) KERBAL_CONDITIONAL_NOEXCEPT(
						list_allocator_overload::template try_test_is_nothrow_constructible_from_allocator<const Allocator &>::IS_TRUE::value &&
						list_type_only::template is_nothrow_move_constructible_using_allocator<node_allocator_type>::value
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list(std::initializer_list<value_type> src);

				KERBAL_CONSTEXPR20
				list(std::initializer_list<value_type> src, const Allocator& alloc);

#		else

				list(const kerbal::assign::assign_list<void> & src);

				template <typename Up>
				list(const kerbal::assign::assign_list<Up> & src);

				list(const kerbal::assign::assign_list<void> & src, const Allocator& alloc);

				template <typename Up>
				list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc);

#		endif

				KERBAL_CONSTEXPR20
				~list();

			//===================
			// assign

				KERBAL_CONSTEXPR20
				list& operator=(const list & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator=(list && src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(kerbal::compatibility::move(src)))
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator=(std::initializer_list<value_type> src);

#		else

				list& operator=(const kerbal::assign::assign_list<void> & src);

				template <typename Up>
				list& operator=(const kerbal::assign::assign_list<Up> & src);

#		endif

				KERBAL_CONSTEXPR20
				void assign(const list & src);

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
				void assign(list&& src) KERBAL_CONDITIONAL_NOEXCEPT(
						list_type_only::template is_nothrow_move_assign_using_allocator<node_allocator_type>::value
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> src);

#		else

				void assign(const kerbal::assign::assign_list<void> & src);

				template <typename Up>
				void assign(const kerbal::assign::assign_list<Up> & src);

#		endif

			//===================
			// element access

				using list_type_only::front;
				using list_type_only::back;

			//===================
			// iterator

				using list_type_only::begin;
				using list_type_only::end;

				using list_type_only::cbegin;
				using list_type_only::cend;

				using list_type_only::rbegin;
				using list_type_only::rend;

				using list_type_only::crbegin;
				using list_type_only::crend;

				using list_type_only::nth;
				using list_type_only::index_of;

			//===================
			// capacity

				using list_type_unrelated::empty;
				using list_type_unrelated::size;

				KERBAL_CONSTEXPR
				size_type max_size() const KERBAL_NOEXCEPT
				{
					return node_allocator_traits::max_size(this->alloc());
				}

			//===================
			// insert

				KERBAL_CONSTEXPR20
				void push_front(const_reference val);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push_front(rvalue_reference val);

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				reference emplace_front(Args&& ... args);

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				reference emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i));

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
				void push_back(const_reference val);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push_back(rvalue_reference val);

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				reference emplace_back(Args&& ... args);

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				reference emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i));

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
				iterator insert(const_iterator pos, const_reference val);

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, size_type n, const_reference val);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						iterator
				>::type
				insert(const_iterator pos, InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, rvalue_reference val);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, std::initializer_list<value_type> src);

#		else

				iterator insert(const_iterator pos, const kerbal::assign::assign_list<void> & src);

				template <typename Up>
				iterator insert(const_iterator pos, const kerbal::assign::assign_list<Up> & src);

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				iterator emplace(const_iterator pos, Args&& ... args);

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator emplace(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif

			//===================
			// erase

				KERBAL_CONSTEXPR20
				void pop_front();

				KERBAL_CONSTEXPR20
				void pop_back();

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator pos);

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator first, const_iterator last);

				KERBAL_CONSTEXPR20
				void clear() KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list_type_only>()->k_clear_using_allocator(
								kerbal::utility::declthis<list>()->alloc()
						))
				);

			//===================
			// operation

				KERBAL_CONSTEXPR20
				void resize(size_type count);

				KERBAL_CONSTEXPR20
				void resize(size_type count, const_reference value);

				KERBAL_CONSTEXPR20
				void swap(list & with) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(list_allocator_overload::k_swap_allocator_if_propagate(
								kerbal::utility::declval<list_allocator_overload&>(), kerbal::utility::declval<list_allocator_overload&>()
						)) &&
						noexcept(list_type_unrelated::k_swap_type_unrelated(
								kerbal::utility::declval<list_type_unrelated&>(), kerbal::utility::declval<list_type_unrelated&>()
						))
				);

				KERBAL_CONSTEXPR20
				void iter_swap(const_iterator a, const_iterator b) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void reverse(const_iterator a, const_iterator b) KERBAL_NOEXCEPT;

				using list_type_only::reverse;

				using list_type_only::rotate;

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void merge(list & other, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void merge(list & other);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void sort(const_iterator first, const_iterator last, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void sort(const_iterator first, const_iterator last);

				using list_type_only::sort;

				KERBAL_CONSTEXPR20
				size_type remove(const_reference val);

				KERBAL_CONSTEXPR20
				size_type remove(const_iterator first, const_iterator last, const_reference val);

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_if(UnaryPredicate predicate);

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_if(const_iterator first, const_iterator last, UnaryPredicate predicate);

				KERBAL_CONSTEXPR20
				size_type unique();

				template <typename BinaryPredicate>
				KERBAL_CONSTEXPR20
				size_type unique(BinaryPredicate pred);

				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last);

				template <typename BinaryPredicate>
				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last, BinaryPredicate pred);

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list & other) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list & other, const_iterator opos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list & other, const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list && other) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list && other, const_iterator opos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list && other, const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

#		endif

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				static void set_difference(list & l1, const list & l2, list & lto, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				static void set_difference(list & l1, const list & l2, list & lto);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				static void set_intersection(list & l1, list & l2, list & lto, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				static void set_intersection(list & l1, list & l2, list & lto);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				static void set_symmetric_difference(list & l1, list & l2, list & lto, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				static void set_symmetric_difference(list & l1, list & l2, list & lto);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				static void set_union(list & l1, list & l2, list & lto, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				static void set_union(list & l1, list & l2, list & lto);

				KERBAL_CONSTEXPR20
				list& operator+=(const list & with);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator+=(list && with);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator+=(std::initializer_list<value_type> with);

#		else

				list& operator+=(const kerbal::assign::assign_list<void> & with);

				template <typename U>
				list& operator+=(const kerbal::assign::assign_list<U> & with);

#		endif

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Alloc =
					std::allocator<typename kerbal::iterator::iterator_traits<InputIterator>::value_type> >
		list(InputIterator, InputIterator, Alloc = Alloc())
				-> list<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Alloc>;

		template <typename Tp, typename Alloc = std::allocator<Tp> >
		list(std::initializer_list<Tp> src, Alloc = Alloc()) -> list<Tp, Alloc>;

#	endif


		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(const list<Tp, Allocator> & lhs, const list<Tp, Allocator> & rhs);

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(const list<Tp, Allocator> & lhs, list<Tp, Allocator> && rhs);

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator> && lhs, const list<Tp, Allocator> & rhs);

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator> && lhs, list<Tp, Allocator> && rhs);

#	endif

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator==(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator!=(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<=(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>=(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

	namespace algorithm
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(kerbal::container::list<Tp, Allocator> & a, kerbal::container::list<Tp, Allocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Tp, typename Allocator>
	KERBAL_CONSTEXPR20
	void swap(kerbal::container::list<Tp, Allocator> & a, kerbal::container::list<Tp, Allocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_LIST_LIST_DECL_HPP
