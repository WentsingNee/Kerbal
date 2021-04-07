/**
 * @file       single_list.hpp
 * @brief
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_SINGLE_LIST_HPP
#define KERBAL_CONTAINER_SINGLE_LIST_HPP

#include <kerbal/container/fwd/single_list.fwd.hpp>

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/declval.hpp>

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

#include <kerbal/container/detail/single_list_base.hpp>
#include <kerbal/container/detail/single_list_iterator.hpp>
#include <kerbal/container/detail/single_list_node.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator = std::allocator<Tp> >
		class single_list:
				protected kerbal::container::detail::sl_allocator_unrelated<Tp>,
				protected kerbal::container::detail::sl_allocator_overload<Tp, Allocator>
		{
			private:
				typedef kerbal::container::detail::sl_type_unrelated						sl_type_unrelated;
				typedef kerbal::container::detail::sl_allocator_unrelated<Tp>				sl_allocator_unrelated;
				typedef kerbal::container::detail::sl_allocator_overload<Tp, Allocator>		sl_allocator_overload;

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

			public:
				typedef kerbal::type_traits::integral_constant<size_t, sizeof(node)>	NODE_SIZE;

			public:
				typedef Allocator															allocator_type;

			private:
				typedef kerbal::memory::allocator_traits<allocator_type>					tp_allocator_traits;
				typedef typename sl_allocator_overload::node_allocator_type					node_allocator_type;
				typedef typename tp_allocator_traits::template rebind_traits<node>::other	node_allocator_traits;

			private:

				using sl_allocator_overload::alloc;

			public:

#		if __cplusplus < 201103L

				single_list();

#		else

				single_list() = default;

#		endif

				KERBAL_CONSTEXPR20
				explicit
				single_list(const Allocator& alloc) KERBAL_CONDITIONAL_NOEXCEPT((
						std::is_nothrow_default_constructible<sl_allocator_unrelated>::value &&
						std::is_nothrow_constructible<sl_allocator_overload, const Allocator&>::value
				));

				KERBAL_CONSTEXPR20
				single_list(const single_list & src);

				KERBAL_CONSTEXPR20
				single_list(const single_list & src, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				explicit
				single_list(size_type n);

				KERBAL_CONSTEXPR20
				explicit
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
				single_list(single_list && src) KERBAL_NOEXCEPT((
						std::is_nothrow_constructible<sl_allocator_overload, node_allocator_type&&>::value
				));

			private:

				KERBAL_CONSTEXPR20
				void move_constructor_with_afforded_allocator_allocator_equal(single_list && src) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void move_constructor_with_afforded_allocator_allocator_not_equal(single_list && src);

				template <bool is_allocator_always_equal>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<!is_allocator_always_equal>::type
				move_constructor_with_afforded_allocator_helper(single_list && src);

				template <bool is_allocator_always_equal>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<is_allocator_always_equal>::type
				move_constructor_with_afforded_allocator_helper(single_list && src) KERBAL_NOEXCEPT;

			public:

				KERBAL_CONSTEXPR20
				single_list(single_list && src, const Allocator& alloc);

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
				~single_list() KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->_K_consecutive_destroy_node(
								kerbal::utility::declthis<single_list>()->alloc(),
								kerbal::utility::declthis<single_list>()->head_node.next
						)) &&
						std::is_nothrow_destructible<sl_allocator_overload>::value
				);

			//===================
			//assign

				KERBAL_CONSTEXPR20
				single_list& operator=(const single_list & src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->assign(src))
				);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				single_list& operator=(single_list && src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->assign(kerbal::compatibility::move(src)))
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				single_list& operator=(std::initializer_list<value_type> src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->assign(src))
				);

#		else

				template <typename Up>
				single_list& operator=(const kerbal::assign::assign_list<Up> & src);

#		endif

				KERBAL_CONSTEXPR20
				void assign(const single_list & src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<single_list>()->assign(src.cbegin(), src.cend()))
				);

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
				void assign(single_list&& src);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> src);

#		else

				template <typename Up>
				void assign(const kerbal::assign::assign_list<Up> & src);

#		endif

			//===================
			//element access

				using sl_allocator_unrelated::front;
				using sl_allocator_unrelated::back;

			//===================
			//iterator

				using sl_allocator_unrelated::begin;
				using sl_allocator_unrelated::end;

				using sl_allocator_unrelated::cbegin;
				using sl_allocator_unrelated::cend;

				using sl_allocator_unrelated::nth;
				using sl_allocator_unrelated::index_of;

			//===================
			//capacity

				using sl_allocator_unrelated::empty;
				using sl_allocator_unrelated::size;
				using sl_allocator_unrelated::max_size;

			//===================
			//insert

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

				reference emplace_front();

				template <typename Arg0>
				reference emplace_front(const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				reference emplace_front(const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				reference emplace_front(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

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

				reference emplace_back();

				template <typename Arg0>
				reference emplace_back(const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				reference emplace_back(const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				reference emplace_back(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

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

				iterator emplace(const_iterator pos);

				template <typename Arg0>
				iterator emplace(const_iterator pos, const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				iterator emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				iterator emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#		endif

			//===================
			//erase

				KERBAL_CONSTEXPR20
				void pop_front();

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator pos);

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator first, const_iterator last);

			//===================
			//operation

				KERBAL_CONSTEXPR20
				void clear() KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::utility::declthis<single_list>()->sl_allocator_unrelated::_K_clear(
								kerbal::utility::declthis<single_list>()->alloc()
						))
				);

				KERBAL_CONSTEXPR20
				void resize(size_type count);

				KERBAL_CONSTEXPR20
				void resize(size_type count, const_reference value);

				KERBAL_CONSTEXPR20
				void swap(single_list & ano);

				using sl_allocator_unrelated::iter_swap_unstable;
				using sl_allocator_unrelated::iter_swap;
				using sl_allocator_unrelated::iter_swap_fast;

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

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Alloc =
					std::allocator<typename kerbal::iterator::iterator_traits<InputIterator>::value_type> >
		single_list(InputIterator, InputIterator, Alloc = Alloc())
				-> single_list<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Alloc>;

		template <typename Tp, typename Alloc = std::allocator<Tp> >
		single_list(std::initializer_list<Tp> src, Alloc = Alloc()) -> single_list<Tp, Alloc>;

#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename Tp>
			using single_list = kerbal::container::single_list<Tp, std::pmr::polymorphic_allocator<Tp> >;
		}

#	endif

#	endif


		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator==(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator!=(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<=(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>=(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/single_list.impl.hpp>

#endif // KERBAL_CONTAINER_SINGLE_LIST_HPP
