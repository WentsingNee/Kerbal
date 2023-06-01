/**
 * @file       single_list.decl.hpp
 * @brief
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_SINGLE_LIST_SINGLE_LIST_DECL_HPP
#define KERBAL_CONTAINER_SINGLE_LIST_SINGLE_LIST_DECL_HPP

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

#include <kerbal/container/detail/container_rebind_allocator_overload.hpp>
#include <kerbal/container/detail/single_list_base/single_list_base.decl.hpp>

#include <kerbal/container/detail/single_list_base/single_list_iterator.hpp>
#include <kerbal/container/detail/single_list_base/single_list_node.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp, typename Allocator>
			struct sl_typedef_helper
			{
					typedef kerbal::container::detail::sl_allocator_unrelated<Tp>						sl_allocator_unrelated;
					typedef typename sl_allocator_unrelated::node 										node;
					typedef Allocator																	allocator_type;
					typedef kerbal::container::detail::container_rebind_allocator_overload<
							allocator_type, node
					>																					sl_allocator_overload;
			};

		} // namespace detail


		namespace detail
		{

			template <typename Tp, typename Allocator>
			struct single_list_node_size_helper
			{
					typedef kerbal::type_traits::integral_constant<
							std::size_t,
							sizeof(typename kerbal::container::single_list<Tp, Allocator>::node)
					> type;
			};

		} // namespace detail

		template <typename Tp, typename Allocator>
		struct single_list_node_size :
				kerbal::container::detail::single_list_node_size_helper<Tp, Allocator>::type
		{
		};


		template <typename Tp, typename Allocator>
		class single_list:
				protected detail::sl_typedef_helper<Tp, Allocator>::sl_allocator_overload,
				protected detail::sl_typedef_helper<Tp, Allocator>::sl_allocator_unrelated
		{
			private:
				typedef kerbal::container::detail::sl_type_unrelated					sl_type_unrelated;
				typedef detail::sl_typedef_helper<Tp, Allocator>						sl_typedef_helper;
				typedef typename sl_typedef_helper::sl_allocator_overload 				sl_allocator_overload;
				typedef typename sl_typedef_helper::sl_allocator_unrelated				sl_allocator_unrelated;

			public:
				typedef typename sl_allocator_unrelated::value_type					value_type;
				typedef typename sl_allocator_unrelated::const_type					const_type;
				typedef typename sl_allocator_unrelated::reference					reference;
				typedef typename sl_allocator_unrelated::const_reference			const_reference;
				typedef typename sl_allocator_unrelated::pointer					pointer;
				typedef typename sl_allocator_unrelated::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename sl_allocator_unrelated::rvalue_reference			rvalue_reference;
				typedef typename sl_allocator_unrelated::const_rvalue_reference		const_rvalue_reference;
#		endif

				typedef typename sl_allocator_unrelated::size_type					size_type;
				typedef typename sl_allocator_unrelated::difference_type			difference_type;

				typedef typename sl_allocator_unrelated::iterator					iterator;
				typedef typename sl_allocator_unrelated::const_iterator				const_iterator;

			private:
				typedef typename sl_allocator_unrelated::node_base					node_base;
				typedef typename sl_allocator_unrelated::node						node;

				friend struct kerbal::container::detail::single_list_node_size_helper<Tp, Allocator>;

			public:
				typedef Allocator														allocator_type;

			private:
				typedef typename sl_allocator_overload::rebind_allocator_type			node_allocator_type;
				typedef typename sl_allocator_overload::rebind_allocator_traits 		node_allocator_traits;

			private:

				using sl_allocator_overload::alloc;

			public:

			//===================
			// construct/copy/destroy

#		if __cplusplus < 201103L

				single_list();

#		else

				single_list() = default;

#		endif

				KERBAL_CONSTEXPR20
				explicit
				single_list(const Allocator& alloc) KERBAL_CONDITIONAL_NOEXCEPT(
						sl_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						sl_allocator_unrelated::is_nothrow_default_constructible::value
				);

				KERBAL_CONSTEXPR20
				single_list(const single_list & src);

				KERBAL_CONSTEXPR20
				single_list(const single_list & src, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				explicit
				single_list(size_type n);

				KERBAL_CONSTEXPR20
				single_list(size_type n, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				single_list(size_type n, const_reference val);

				KERBAL_CONSTEXPR20
				single_list(size_type n, const_reference val, const Allocator& alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				single_list(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				single_list(InputIterator first, InputIterator last, const Allocator& alloc,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				single_list(single_list && src) KERBAL_CONDITIONAL_NOEXCEPT(
						sl_allocator_overload::is_nothrow_constructible_from_allocator_rvalue_reference::value &&
						sl_allocator_unrelated::is_nothrow_move_constructible::value
				);

				KERBAL_CONSTEXPR20
				single_list(single_list && src, const Allocator& alloc)  KERBAL_CONDITIONAL_NOEXCEPT(
						sl_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						sl_allocator_unrelated::template is_nothrow_move_constructible_using_allocator<node_allocator_type>::value
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				single_list(std::initializer_list<value_type> src);

				KERBAL_CONSTEXPR20
				single_list(std::initializer_list<value_type> src, const Allocator& alloc);

#		else

				template <typename Up>
				single_list(const kerbal::assign::assign_list<Up> & src);

				template <typename Up>
				single_list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc);

#		endif

				KERBAL_CONSTEXPR20
				~single_list();

			//===================
			// assign

				KERBAL_CONSTEXPR20
				single_list& operator=(const single_list & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				single_list& operator=(single_list && src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->assign(kerbal::compatibility::move(src)))
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				single_list& operator=(std::initializer_list<value_type> src);

#		else

				template <typename Up>
				single_list& operator=(const kerbal::assign::assign_list<Up> & src);

#		endif

				KERBAL_CONSTEXPR20
				void assign(const single_list & src);

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
				void assign(single_list&& src) KERBAL_CONDITIONAL_NOEXCEPT(
						sl_allocator_unrelated::template is_nothrow_move_assign_using_allocator<node_allocator_type>::value
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> src);

#		else

				template <typename Up>
				void assign(const kerbal::assign::assign_list<Up> & src);

#		endif

			//===================
			// element access

				using sl_allocator_unrelated::front;
				using sl_allocator_unrelated::back;

			//===================
			// iterator

				using sl_allocator_unrelated::begin;
				using sl_allocator_unrelated::end;

				using sl_allocator_unrelated::cbegin;
				using sl_allocator_unrelated::cend;

				using sl_allocator_unrelated::nth;
				using sl_allocator_unrelated::index_of;

			//===================
			// capacity

				using sl_allocator_unrelated::empty;
				using sl_allocator_unrelated::size;

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
				iterator erase(const_iterator pos);

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator first, const_iterator last);

				KERBAL_CONSTEXPR20
				void clear() KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<sl_allocator_unrelated>()->clear_using_allocator(
								kerbal::utility::declthis<single_list>()->alloc()
						))
				);

			//===================
			// operation

				KERBAL_CONSTEXPR20
				void resize(size_type count);

				KERBAL_CONSTEXPR20
				void resize(size_type count, const_reference value);

				KERBAL_CONSTEXPR20
				void swap(single_list & with) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(sl_allocator_overload::k_swap_allocator_if_propagate(
								kerbal::utility::declval<sl_allocator_overload&>(), kerbal::utility::declval<sl_allocator_overload&>()
						)) &&
						noexcept(sl_type_unrelated::k_swap_type_unrelated(
								kerbal::utility::declval<sl_type_unrelated&>(), kerbal::utility::declval<sl_type_unrelated&>()
						))
				);

				using sl_allocator_unrelated::iter_swap;

				using sl_allocator_unrelated::reverse;

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
				void splice(const_iterator pos, single_list & other) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, single_list & other, const_iterator opos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, single_list & other, const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, single_list && other) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, single_list && other, const_iterator opos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, single_list && other, const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

#		endif

				KERBAL_CONSTEXPR20
				single_list& operator+=(const single_list& with);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				single_list& operator+=(single_list&& with);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				single_list& operator+=(std::initializer_list<value_type> with);

#		else

				single_list& operator+=(const kerbal::assign::assign_list<value_type> & with);

#		endif

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Alloc =
					std::allocator<typename kerbal::iterator::iterator_traits<InputIterator>::value_type> >
		single_list(InputIterator, InputIterator, Alloc = Alloc())
				-> single_list<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Alloc>;

		template <typename Tp, typename Alloc = std::allocator<Tp> >
		single_list(std::initializer_list<Tp> src, Alloc = Alloc()) -> single_list<Tp, Alloc>;

#	endif


		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator> operator+(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs);

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator> operator+(const single_list<Tp, Allocator> & lhs, single_list<Tp, Allocator> && rhs);

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator> operator+(single_list<Tp, Allocator> && lhs, const single_list<Tp, Allocator> & rhs);

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		single_list<Tp, Allocator> operator+(single_list<Tp, Allocator> && lhs, single_list<Tp, Allocator> && rhs);

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator==(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::compare::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator!=(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::compare::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::compare::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::compare::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<=(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::compare::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>=(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::compare::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

	namespace algorithm
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(kerbal::container::single_list<Tp, Allocator> & a, kerbal::container::single_list<Tp, Allocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Tp, typename Allocator>
	KERBAL_CONSTEXPR20
	void swap(kerbal::container::single_list<Tp, Allocator> & a, kerbal::container::single_list<Tp, Allocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_SINGLE_LIST_SINGLE_LIST_DECL_HPP
