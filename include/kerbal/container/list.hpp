/**
 * @file       list.hpp
 * @brief
 * @date       2020-02-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_LIST_HPP
#define KERBAL_CONTAINER_LIST_HPP

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/declval.hpp>

#include <memory>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <memory_resource>
#	endif
#endif

#include <kerbal/container/detail/list_base.hpp>
#include <kerbal/container/detail/list_iterator.hpp>
#include <kerbal/container/detail/list_node.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator = std::allocator<Tp> >
		class list:
				protected kerbal::container::detail::list_allocator_unrelated<Tp>,
				protected kerbal::container::detail::list_allocator_overload<Tp, Allocator>
		{
			private:
				typedef kerbal::container::detail::list_type_unrelated						list_type_unrelated;
				typedef kerbal::container::detail::list_allocator_unrelated<Tp>				list_allocator_unrelated;
				typedef kerbal::container::detail::list_allocator_overload<Tp, Allocator>	list_allocator_overload;

			public:
				typedef typename list_allocator_unrelated::value_type					value_type;
				typedef typename list_allocator_unrelated::const_type					const_type;
				typedef typename list_allocator_unrelated::reference					reference;
				typedef typename list_allocator_unrelated::const_reference				const_reference;
				typedef typename list_allocator_unrelated::pointer						pointer;
				typedef typename list_allocator_unrelated::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename list_allocator_unrelated::rvalue_reference				rvalue_reference;
				typedef typename list_allocator_unrelated::const_rvalue_reference		const_rvalue_reference;
#		endif

				typedef typename list_allocator_unrelated::size_type					size_type;
				typedef typename list_allocator_unrelated::difference_type				difference_type;

				typedef typename list_allocator_unrelated::iterator						iterator;
				typedef typename list_allocator_unrelated::const_iterator				const_iterator;
				typedef typename list_allocator_unrelated::reverse_iterator				reverse_iterator;
				typedef typename list_allocator_unrelated::const_reverse_iterator		const_reverse_iterator;

			private:
				typedef typename list_allocator_unrelated::node_base					node_base;
				typedef typename list_allocator_unrelated::node							node;

			public:
				typedef kerbal::type_traits::integral_constant<size_t, sizeof(node)>	NODE_SIZE;

			public:
				typedef Allocator														allocator_type;

			private:
				typedef typename list_allocator_overload::tp_allocator_traits			tp_allocator_traits;
				typedef typename list_allocator_overload::node_allocator_type			node_allocator_type;
				typedef typename list_allocator_overload::node_allocator_traits			node_allocator_traits;

			private:

				using list_allocator_overload::alloc;

			public:
				KERBAL_CONSTEXPR20
				list() KERBAL_CONDITIONAL_NOEXCEPT(
						std::is_nothrow_default_constructible<list_allocator_unrelated>::value &&
						std::is_nothrow_default_constructible<list_allocator_overload>::value
				);

				KERBAL_CONSTEXPR20
				explicit list(const Allocator& alloc) KERBAL_CONDITIONAL_NOEXCEPT((
						std::is_nothrow_default_constructible<list_allocator_unrelated>::value &&
						std::is_nothrow_constructible<list_allocator_overload, const Allocator&>::value
				));

				KERBAL_CONSTEXPR20
				list(const list & src);

				KERBAL_CONSTEXPR20
				list(const list & src, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				explicit list(size_type n);

				KERBAL_CONSTEXPR20
				explicit list(size_type n, const Allocator& alloc);

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
				list(list && src) KERBAL_NOEXCEPT((
						std::is_nothrow_constructible<list_allocator_overload, node_allocator_type&&>::value
				));

			private:

				KERBAL_CONSTEXPR20
				void move_constructor_with_afforded_allocator_allocator_equal(list && src) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void move_constructor_with_afforded_allocator_allocator_not_equal(list && src);

				template <bool is_allocator_always_equal>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<!is_allocator_always_equal>::type
				move_constructor_with_afforded_allocator_helper(list && src);

				template <bool is_allocator_always_equal>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<is_allocator_always_equal>::type
				move_constructor_with_afforded_allocator_helper(list && src) KERBAL_NOEXCEPT;

			public:

				KERBAL_CONSTEXPR20
				list(list && src, const Allocator& alloc);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list(std::initializer_list<value_type> src);

				KERBAL_CONSTEXPR20
				list(std::initializer_list<value_type> src, const Allocator& alloc);

#		else

				template <typename Up>
				list(const kerbal::assign::assign_list<Up> & src);

				template <typename Up>
				list(const kerbal::assign::assign_list<Up> & src, const Allocator& alloc);

#		endif

				KERBAL_CONSTEXPR20
				~list() KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->_K_consecutive_destroy_node(
								kerbal::utility::declthis<list>()->alloc(),
								kerbal::utility::declthis<list>()->head_node.next
						)) &&
						std::is_nothrow_destructible<list_allocator_overload>::value
				);

			//===================
			//assign

				KERBAL_CONSTEXPR20
				list& operator=(const list & src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(src))
				);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator=(list && src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(kerbal::compatibility::move(src)))
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator=(std::initializer_list<value_type> src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(src))
				);

#		else

				template <typename Up>
				list& operator=(const kerbal::assign::assign_list<Up> & src);

#		endif

				KERBAL_CONSTEXPR20
				void assign(const list & src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(src.cbegin(), src.cend()))
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
				void assign(list&& src);

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

				using list_type_unrelated::empty;
				using list_type_unrelated::size;
				using list_allocator_unrelated::max_size;

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
				void pop_back();

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator pos);

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator first, const_iterator last);

			//===================
			//operation

				KERBAL_CONSTEXPR20
				void clear() KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->erase(
								kerbal::utility::declthis<list>()->cbegin(), kerbal::utility::declthis<list>()->cend()
						))
				);

				KERBAL_CONSTEXPR20
				void resize(size_type count);

				KERBAL_CONSTEXPR20
				void resize(size_type count, const_reference value);

				KERBAL_CONSTEXPR20
				void swap(list & ano);

				using list_allocator_unrelated::iter_swap_unstable;
				using list_allocator_unrelated::iter_swap;
				using list_allocator_unrelated::iter_swap_fast;

				using list_allocator_unrelated::reverse;
				using list_allocator_unrelated::reverse_unstable;
				using list_allocator_unrelated::reverse_fast;

				using list_allocator_unrelated::rotate;

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void merge(list & other, BinaryPredict cmp);

				KERBAL_CONSTEXPR20
				void merge(list & other);

				using list_allocator_unrelated::sort;

				KERBAL_CONSTEXPR20
				size_type remove(const_reference val);

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_if(UnaryPredicate predicate);

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list & other) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list & other, const_iterator opos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list & other, const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list&& other) KERBAL_NOEXCEPT;

#		endif

				KERBAL_CONSTEXPR20
				list& operator+=(const list& with);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator+=(list&& with);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator+=(std::initializer_list<value_type> with);

#		else

				list& operator+=(const kerbal::assign::assign_list<value_type> & with);

#		endif

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Alloc =
					std::allocator<typename kerbal::iterator::iterator_traits<InputIterator>::value_type> >
		list(InputIterator, InputIterator, Alloc = Alloc())
				-> list<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Alloc>;

		template <typename Tp, typename Alloc = std::allocator<Tp> >
		list(std::initializer_list<Tp> src, Alloc = Alloc()) -> list<Tp, Alloc>;

#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename Tp>
			using list = kerbal::container::list<Tp, std::pmr::polymorphic_allocator<Tp> >;
		}

#	endif

#	endif


		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(const list<Tp, Allocator>& lhs, const list<Tp, Allocator>& rhs);

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(const list<Tp, Allocator>& lhs, list<Tp, Allocator>&& rhs);

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator>&& lhs, const list<Tp, Allocator>& rhs);

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		list<Tp, Allocator> operator+(list<Tp, Allocator>&& lhs, list<Tp, Allocator>&& rhs);

#	endif

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator==(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator!=(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<=(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>=(const list<Tp, Allocator> & lhs, const list<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/list.impl.hpp>

#endif // KERBAL_CONTAINER_LIST_HPP
