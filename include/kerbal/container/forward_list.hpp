/**
 * @file       forward_list.hpp
 * @brief
 * @date       2021-01-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FORWARD_LIST_HPP
#define KERBAL_CONTAINER_FORWARD_LIST_HPP

#include <kerbal/container/fwd/forward_list.fwd.hpp>

#include <kerbal/container/detail/single_list_node.hpp>
#include <kerbal/container/detail/forward_list_iterator.hpp>
#include <kerbal/container/detail/forward_list_base.hpp>

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/ilist.hpp>
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
#	include <type_traits>
#endif

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <memory_resource>
#	endif
#endif

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		class forward_list:
				protected kerbal::container::detail::fl_allocator_overload<Tp, Allocator>,
				protected kerbal::container::detail::fl_allocator_unrelated<Tp>
		{
			private:
				typedef kerbal::container::detail::fl_type_unrelated						fl_type_unrelated;
				typedef kerbal::container::detail::fl_allocator_overload<Tp, Allocator>		fl_allocator_overload;
				typedef kerbal::container::detail::fl_allocator_unrelated<Tp>				fl_allocator_unrelated;

			public:
				typedef typename fl_allocator_unrelated::value_type					value_type;
				typedef typename fl_allocator_unrelated::const_type					const_type;
				typedef typename fl_allocator_unrelated::reference					reference;
				typedef typename fl_allocator_unrelated::const_reference			const_reference;
				typedef typename fl_allocator_unrelated::pointer					pointer;
				typedef typename fl_allocator_unrelated::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename fl_allocator_unrelated::rvalue_reference			rvalue_reference;
				typedef typename fl_allocator_unrelated::const_rvalue_reference		const_rvalue_reference;
#		endif

				typedef typename fl_allocator_unrelated::size_type					size_type;
				typedef typename fl_allocator_unrelated::difference_type			difference_type;

				typedef typename fl_allocator_unrelated::iterator					iterator;
				typedef typename fl_allocator_unrelated::const_iterator				const_iterator;

			private:
				typedef typename fl_allocator_unrelated::node_base					node_base;
				typedef typename fl_allocator_unrelated::node						node;

			public:
				typedef kerbal::type_traits::integral_constant<size_t, sizeof(node)>	NODE_SIZE;

			public:
				typedef Allocator															allocator_type;

			private:
				typedef kerbal::memory::allocator_traits<allocator_type>					tp_allocator_traits;
				typedef typename fl_allocator_overload::node_allocator_type					node_allocator_type;
				typedef typename tp_allocator_traits::template rebind_traits<node>::other	node_allocator_traits;

			private:

				using fl_allocator_overload::alloc;

			public:

			//===================
			// construct/copy/destroy

#		if __cplusplus < 201103L

				forward_list();

#		else

				forward_list() = default;

#		endif

				KERBAL_CONSTEXPR20
				explicit
				forward_list(const Allocator& alloc) KERBAL_CONDITIONAL_NOEXCEPT((
						std::is_nothrow_constructible<fl_allocator_overload, const Allocator&>::value &&
						std::is_nothrow_default_constructible<fl_allocator_unrelated>::value
				));

				KERBAL_CONSTEXPR20
				forward_list(const forward_list & src);

				KERBAL_CONSTEXPR20
				forward_list(const forward_list & src, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				explicit
				forward_list(size_type n);

				KERBAL_CONSTEXPR20
				forward_list(size_type n, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				forward_list(size_type n, const_reference val);

				KERBAL_CONSTEXPR20
				forward_list(size_type n, const_reference val, const Allocator& alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				forward_list(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				forward_list(InputIterator first, InputIterator last, const Allocator& alloc,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list(forward_list && src) KERBAL_NOEXCEPT((
						std::is_nothrow_constructible<fl_allocator_overload, node_allocator_type &&>::value &&
						std::is_nothrow_constructible<fl_allocator_unrelated, fl_allocator_unrelated &&>::value
				));

				KERBAL_CONSTEXPR20
				forward_list(forward_list && src, const Allocator& alloc);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list(std::initializer_list<value_type> src);

				KERBAL_CONSTEXPR20
				forward_list(std::initializer_list<value_type> src, const Allocator& alloc);

#		else

				template <typename Up>
				forward_list(const kerbal::assign::assign_list<Up> & src);

				template <typename Up>
				forward_list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc);

#		endif

				KERBAL_CONSTEXPR20
				~forward_list();

			//===================
			// assign

				KERBAL_CONSTEXPR20
				forward_list& operator=(const forward_list & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list& operator=(forward_list && src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<forward_list>()->assign(kerbal::compatibility::move(src)))
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list& operator=(std::initializer_list<value_type> src);

#		else

				template <typename Up>
				forward_list& operator=(const kerbal::assign::assign_list<Up> & src);

#		endif

				KERBAL_CONSTEXPR20
				void assign(const forward_list & src);

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
				void assign(forward_list&& src) KERBAL_CONDITIONAL_NOEXCEPT(noexcept(
						kerbal::utility::declthis<fl_allocator_unrelated>()->assign_using_allocator(
								kerbal::utility::declthis<forward_list>()->alloc(),
								kerbal::compatibility::move(kerbal::utility::declval<forward_list &&>().alloc()),
								kerbal::utility::declval<fl_allocator_unrelated &&>()
						)
				));

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> src);

#		else

				template <typename Up>
				void assign(const kerbal::assign::assign_list<Up> & src);

#		endif

			//===================
			// iterator

				using fl_allocator_unrelated::before_begin;
				using fl_allocator_unrelated::cbefore_begin;

				using fl_allocator_unrelated::begin;
				using fl_allocator_unrelated::end;

				using fl_allocator_unrelated::cbegin;
				using fl_allocator_unrelated::cend;

				using fl_allocator_unrelated::nth;
				using fl_allocator_unrelated::index_of;

			//===================
			// capacity

				using fl_allocator_unrelated::empty;
				using fl_allocator_unrelated::size;

				KERBAL_CONSTEXPR
				size_type max_size() const KERBAL_NOEXCEPT
				{
					return node_allocator_traits::max_size(this->alloc());
				}

			//===================
			// element access

				using fl_allocator_unrelated::front;

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
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
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
				iterator insert_after(const_iterator pos, const_reference val);

				KERBAL_CONSTEXPR20
				iterator insert_after(const_iterator pos, size_type n, const_reference val);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						iterator
				>::type
				insert_after(const_iterator pos, InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert_after(const_iterator pos, rvalue_reference val);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert_after(const_iterator pos, std::initializer_list<value_type> src);

#		else

				template <typename Up>
				iterator insert_after(const_iterator pos, const kerbal::assign::assign_list<Up> & src);

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				iterator emplace_after(const_iterator pos, Args&& ... args);

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator emplace_after(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

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
				iterator erase_after(const_iterator pos);

				KERBAL_CONSTEXPR20
				iterator erase_after(const_iterator first, const_iterator last);

				KERBAL_CONSTEXPR20
				void clear() KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<fl_allocator_unrelated>()->clear_using_allocator(
								kerbal::utility::declthis<forward_list>()->alloc()
						))
				);

			//===================
			// operation

				KERBAL_CONSTEXPR20
				void resize(size_type count);

				KERBAL_CONSTEXPR20
				void resize(size_type count, const_reference value);

				KERBAL_CONSTEXPR20
				void swap(forward_list & with) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(fl_allocator_overload::_K_swap_allocator_if_propagate(
								kerbal::utility::declval<fl_allocator_overload&>(), kerbal::utility::declval<fl_allocator_overload&>()
						)) &&
						noexcept(fl_type_unrelated::_K_swap_type_unrelated(
								kerbal::utility::declval<fl_type_unrelated&>(), kerbal::utility::declval<fl_type_unrelated&>()
						))
				);

				KERBAL_CONSTEXPR20
				void iter_swap_after(const_iterator a, const_iterator b) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void reverse_after(const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

				using fl_type_unrelated::reverse;

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void merge(forward_list & other, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void merge(forward_list & other);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void sort_after(const_iterator first, const_iterator last, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void sort_after(const_iterator first, const_iterator last);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void sort(BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void sort();

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_after_if(const_iterator first, const_iterator last, UnaryPredicate predicate);

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_if(UnaryPredicate predicate);

				KERBAL_CONSTEXPR20
				size_type remove_after(const_iterator first, const_iterator last, const_reference val);

				KERBAL_CONSTEXPR20
				size_type remove(const_reference val);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last, BinaryPredict equal_to);

				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last);

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				size_type unique(BinaryPredict equal_to);

				KERBAL_CONSTEXPR20
				size_type unique();

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list & other) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list & other, const_iterator opos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list & other, const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Alloc =
					std::allocator<typename kerbal::iterator::iterator_traits<InputIterator>::value_type> >
		forward_list(InputIterator, InputIterator, Alloc = Alloc())
				-> forward_list<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Alloc>;

		template <typename Tp, typename Alloc = std::allocator<Tp> >
		forward_list(std::initializer_list<Tp> src, Alloc = Alloc()) -> forward_list<Tp, Alloc>;

#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename Tp>
			using forward_list = kerbal::container::forward_list<Tp, std::pmr::polymorphic_allocator<Tp> >;
		}

#	endif

#	endif


		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator==(const forward_list<Tp, Allocator> & lhs, const forward_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator!=(const forward_list<Tp, Allocator> & lhs, const forward_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<(const forward_list<Tp, Allocator> & lhs, const forward_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>(const forward_list<Tp, Allocator> & lhs, const forward_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<=(const forward_list<Tp, Allocator> & lhs, const forward_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>=(const forward_list<Tp, Allocator> & lhs, const forward_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

	namespace algorithm
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(kerbal::container::forward_list<Tp, Allocator> & a, kerbal::container::forward_list<Tp, Allocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Tp, typename Allocator>
	KERBAL_CONSTEXPR20
	void swap(kerbal::container::forward_list<Tp, Allocator> & a, kerbal::container::forward_list<Tp, Allocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#include <kerbal/container/impl/forward_list.impl.hpp>

#endif // KERBAL_CONTAINER_FORWARD_LIST_HPP
