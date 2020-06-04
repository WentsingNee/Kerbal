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
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
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

#include <kerbal/container/impl/list_iterator.impl.hpp>
#include <kerbal/container/impl/list_node.impl.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator = std::allocator<Tp> >
		class list
		{
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

			private:
				typedef kerbal::container::detail::list_node_base				node_base;
				typedef kerbal::container::detail::list_node<value_type>		node;

				typedef kerbal::memory::allocator_traits<Allocator>								tp_allocator_traits;
				typedef typename tp_allocator_traits::template rebind_alloc<node>::other		node_allocator_type;
				typedef typename tp_allocator_traits::template rebind_traits<node>::other		node_allocator_traits;

			private:
				node_base head_node;
				node_allocator_type alloc;

				struct release_uninit_res
				{
						node_allocator_type& alloc;

						KERBAL_CONSTEXPR
						explicit release_uninit_res(node_allocator_type& alloc) KERBAL_NOEXCEPT :
								alloc(alloc)
						{
						}

						KERBAL_CONSTEXPR14
						void operator()(node *p) KERBAL_NOEXCEPT
						{
							node_allocator_traits::deallocate(this->alloc, p, 1);
						}
				};

			public:
				KERBAL_CONSTEXPR20
				list() KERBAL_CONDITIONAL_NOEXCEPT(
						std::is_nothrow_default_constructible<node_allocator_type>::value
				);

				KERBAL_CONSTEXPR20
				explicit list(const Allocator& alloc) KERBAL_CONDITIONAL_NOEXCEPT(
						std::is_nothrow_copy_constructible<node_allocator_type>::value
				);

				KERBAL_CONSTEXPR20
				list(const list & src);

				KERBAL_CONSTEXPR20
				list(const list & src, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				explicit list(size_type n, const Allocator& alloc = Allocator());

				KERBAL_CONSTEXPR20
				list(size_type n, const_reference val, const Allocator& alloc = Allocator());

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				list(InputIterator first, InputIterator last, const Allocator& alloc = Allocator(),
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list(list && src);

				KERBAL_CONSTEXPR20
				list(list && src, const Allocator& alloc);

				KERBAL_CONSTEXPR20
				list(std::initializer_list<value_type> src, const Allocator& alloc = Allocator());

#		endif

				KERBAL_CONSTEXPR20
				~list() KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->clear())
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
						noexcept(kerbal::utility::declthis<list>()->assign(std::move(src)))
				);

				KERBAL_CONSTEXPR20
				list& operator=(std::initializer_list<value_type> src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(src))
				);

#		endif

				KERBAL_CONSTEXPR20
				void assign(const list & src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<list>()->assign(src.cbegin(), src.cend()))
				);

				KERBAL_CONSTEXPR20
				void assign(size_type count, const_reference val);

				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				KERBAL_CONSTEXPR20
				assign(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(list&& src);

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> src);

#		endif

			//===================
			//element access

				KERBAL_CONSTEXPR20
				reference front() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_reference front() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				reference back() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_reference back() const KERBAL_NOEXCEPT;

			//===================
			//iterator

				KERBAL_CONSTEXPR20
				iterator begin() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				iterator end() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_iterator begin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_iterator end() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_iterator cbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_iterator cend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				reverse_iterator rbegin() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				reverse_iterator rend() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_reverse_iterator rend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_reverse_iterator crend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				iterator nth(size_type index) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				const_iterator nth(size_type index) const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				size_type index_of(iterator it) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				size_type index_of(const_iterator it) const KERBAL_NOEXCEPT;

			//===================
			//capacity

				KERBAL_CONSTEXPR20
				bool empty() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				size_type size() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT
				{
					return static_cast<size_type>(-1);
				}

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

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, std::initializer_list<value_type> src);

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
				void clear() KERBAL_CONDITIONAL_NOEXCEPT(noexcept(
						kerbal::utility::declthis<list>()->erase(
								kerbal::utility::declthis<list>()->cbegin(), kerbal::utility::declthis<list>()->cend()
						)
				));

				KERBAL_CONSTEXPR20
				void resize(size_type count);

				KERBAL_CONSTEXPR20
				void resize(size_type count, const_reference value);

				KERBAL_CONSTEXPR20
				void swap(list & ano);

				KERBAL_CONSTEXPR20
				size_type remove(const_reference val);

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_if(UnaryPredicate predicate);

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list& other) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list& other, const_iterator opos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list& other, const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void splice(const_iterator pos, list&& other) KERBAL_NOEXCEPT;

#		endif

				KERBAL_CONSTEXPR20
				list& operator+=(const list& with);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				list& operator+=(list&& with);

				KERBAL_CONSTEXPR20
				list& operator+=(std::initializer_list<value_type> with);

#		endif

				template <typename , typename >
				KERBAL_CONSTEXPR20
				friend
				list operator+(const list& lhs, const list& rhs);

#		if __cplusplus >= 201103L

				template <typename , typename >
				KERBAL_CONSTEXPR20
				friend
				list operator+(const list& lhs, list&& rhs);

				template <typename , typename >
				KERBAL_CONSTEXPR20
				friend
				list operator+(list&& lhs, const list& rhs);

				template <typename , typename >
				KERBAL_CONSTEXPR20
				friend
				list operator+(list&& lhs, list&& rhs);

#		endif

			//===================
			//private

			private:
				KERBAL_CONSTEXPR14
				void __init_node_base() KERBAL_NOEXCEPT
				{
					this->head_node.prev = &this->head_node;
					this->head_node.next = &this->head_node;
				}

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				node* __build_new_node_helper(kerbal::type_traits::false_type, Args&& ... args);

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				node* __build_new_node_helper(kerbal::type_traits::true_type, Args&& ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(node_allocator_traits::allocate(kerbal::utility::declthis<list>()->alloc, 1))
						)
				;

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				node* __build_new_node(Args&& ... args);

#		else

				node* __build_new_node();

				template <typename Arg0>
				node* __build_new_node(const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				node* __build_new_node(const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				node* __build_new_node(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				std::pair<node*, node*> __build_n_new_nodes_unguarded(size_type n, Args&& ...args);

#		else

				std::pair<node*, node*> __build_n_new_nodes_unguarded(size_type n);

				template <typename Arg0>
				std::pair<node*, node*> __build_n_new_nodes_unguarded(size_type n, const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				std::pair<node*, node*> __build_n_new_nodes_unguarded(size_type n, const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				std::pair<node*, node*> __build_n_new_nodes_unguarded(size_type n, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#		endif

				/*
				 * @warning Especial case: first == last
				 */
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						std::pair<node*, node*>
				>::type
				KERBAL_CONSTEXPR20
				__build_new_nodes_range_unguarded(InputIterator first, InputIterator last);

				KERBAL_CONSTEXPR20
				void __destroy_node(node_base * p_node_base)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(node_allocator_traits::destroy(kerbal::utility::declthis<list>()->alloc, kerbal::utility::declval<node*>())) &&
								noexcept(node_allocator_traits::deallocate(kerbal::utility::declthis<list>()->alloc, kerbal::utility::declval<node*>(), 1))
						)
				;

				KERBAL_CONSTEXPR20
				void __consecutive_destroy_node(node_base * start)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::utility::declthis<list>()->__destroy_node(kerbal::utility::declval<node_base*>()))
						)
				;

				KERBAL_CONSTEXPR20
				static void __hook_node(const_iterator pos, node_base * p) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				static void __hook_node(const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				static void __swap_with_empty(list& not_empty_list, list& empty_list) KERBAL_NOEXCEPT;

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Alloc =
					std::allocator<typename kerbal::iterator::iterator_traits<InputIterator>::value_type> >
		list(InputIterator, InputIterator, Alloc = Alloc())
				-> list<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Alloc>;

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
		bool operator==(const list<Tp, Allocator> & lhs, const list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator!=(const list<Tp, Allocator> & lhs, const list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<(const list<Tp, Allocator> & lhs, const list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>(const list<Tp, Allocator> & lhs, const list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator<=(const list<Tp, Allocator> & lhs, const list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		bool operator>=(const list<Tp, Allocator> & lhs, const list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/list.impl.hpp>

#endif // KERBAL_CONTAINER_LIST_HPP
