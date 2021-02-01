/**
 * @file       single_list_base.hpp
 * @brief
 * @date       2020-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_HPP

#include <kerbal/container/fwd/single_list.fwd.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#include <cstddef>
#include <utility> // std::pair

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <memory_resource>
#	endif
#endif

#include <kerbal/container/detail/single_list_node.hpp>
#include <kerbal/container/detail/single_list_iterator.hpp>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class sl_type_unrelated
			{
				protected:
					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef kerbal::container::detail::sl_node_base					node_base;
					typedef kerbal::container::detail::sl_iter_type_unrelated		basic_iterator;
					typedef kerbal::container::detail::sl_kiter_type_unrelated		basic_const_iterator;

				protected:
					node_base head_node;
					basic_iterator last_iter;

					KERBAL_CONSTEXPR14
					sl_type_unrelated() KERBAL_NOEXCEPT
							: head_node(), last_iter(this->basic_begin())
					{
					}

					KERBAL_CONSTEXPR14
					basic_iterator basic_begin() KERBAL_NOEXCEPT
					{
						return basic_iterator(&this->head_node);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_begin() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(&this->head_node);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_cbegin() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(&this->head_node);
					}

					KERBAL_CONSTEXPR14
					basic_iterator basic_end() KERBAL_NOEXCEPT
					{
						return basic_iterator(this->last_iter);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_end() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(this->last_iter);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_cend() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(this->last_iter);
					}

				//===================
				//capacity

					KERBAL_CONSTEXPR20
					bool empty() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					size_type size() const KERBAL_NOEXCEPT;

				//===================
				//operation

					KERBAL_CONSTEXPR20
					void iter_swap(basic_iterator a, basic_iterator b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void reverse(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void reverse() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void splice(basic_const_iterator pos, sl_type_unrelated & other) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void splice(basic_const_iterator pos, sl_type_unrelated & other, basic_const_iterator opos) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void splice(basic_const_iterator pos, sl_type_unrelated & other,
								basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT;

				//===================
				//private

					// pre-cond: p->next == NULL;
					KERBAL_CONSTEXPR20
					void _K_hook_node_back(node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					static void _K_hook_node_not_back(basic_iterator pos, node_base * p) KERBAL_NOEXCEPT;

					// pre-cond: if pos == cend then p->next == NULL;
					KERBAL_CONSTEXPR20
					void _K_hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT;

					// pre-cond: back->next == NULL;
					KERBAL_CONSTEXPR20
					void _K_hook_node_back(node_base * start, node_base * back) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					static void _K_hook_node_not_back(basic_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT;

					// pre-cond: if pos == cend then back->next == NULL;
					KERBAL_CONSTEXPR20
					void _K_hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					node_base * _K_unhook_node(basic_iterator pos) KERBAL_NOEXCEPT;

					// pre-cond: first != last;
					KERBAL_CONSTEXPR20
					std::pair<node_base *, node_base *>
					_K_unhook_node(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT;

					// pre-cond: lhs and rhs are lists of same type
					KERBAL_CONSTEXPR20
					static void _K_swap_with_empty(sl_type_unrelated & not_empty_list, sl_type_unrelated & empty_list) KERBAL_NOEXCEPT;

					// pre-cond: lhs and rhs are lists of same type
					KERBAL_CONSTEXPR20
					static void _K_swap_type_unrelated(sl_type_unrelated & lhs, sl_type_unrelated & rhs) KERBAL_NOEXCEPT;

			};

			template <typename Tp>
			class sl_allocator_unrelated:
					protected kerbal::container::detail::sl_type_unrelated
			{
				private:
					typedef kerbal::container::detail::sl_type_unrelated		super;
					typedef kerbal::container::detail::sl_type_unrelated		sl_type_unrelated;

					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

					template <typename Up, typename Allocator>
					friend struct sl_node_allocator_helper;

				protected:
					typedef Tp							value_type;
					typedef const value_type			const_type;
					typedef value_type&					reference;
					typedef const value_type&			const_reference;
					typedef value_type*					pointer;
					typedef const value_type*			const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type&&				rvalue_reference;
					typedef const value_type&&			const_rvalue_reference;
#			endif

					typedef sl_type_unrelated::size_type					size_type;
					typedef sl_type_unrelated::difference_type				difference_type;

					typedef kerbal::container::detail::sl_iter<Tp>			iterator;
					typedef kerbal::container::detail::sl_kiter<Tp>			const_iterator;

					typedef sl_type_unrelated::node_base					node_base;
					typedef kerbal::container::detail::sl_node<value_type>	node;


				protected:

#			if __cplusplus >= 201103L

					using super::super;

#			else

					sl_allocator_unrelated() KERBAL_NOEXCEPT
							: super()
					{
					}

#			endif

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
					iterator nth(size_type index) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator nth(size_type index) const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					size_type index_of(iterator it) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					size_type index_of(const_iterator it) const KERBAL_NOEXCEPT;

				//===================
				//capacity

					KERBAL_CONSTEXPR
					size_type max_size() const KERBAL_NOEXCEPT
					{
						return static_cast<size_type>(-1);
					}

				//===================
				//operation

					KERBAL_CONSTEXPR20
					void iter_swap_unstable(iterator a, iterator b);

					KERBAL_CONSTEXPR20
					void iter_swap(iterator a, iterator b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void iter_swap_fast(iterator a, iterator b);

					KERBAL_CONSTEXPR20
					void reverse(iterator first, iterator last) KERBAL_NOEXCEPT;

#			if __cplusplus >= 201103L

#				if __cpp_exceptions

					template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<!nothrow_while_construct, node*>::type
					_K_build_new_node_impl(NodeAllocator & alloc, Args&& ... args);

					template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<nothrow_while_construct, node*>::type
					_K_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::memory::allocator_traits<NodeAllocator>::allocate(alloc, 1))
							)
					;

#				endif

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static node* _K_build_new_node(NodeAllocator & alloc, Args&& ... args);

#			else

					template <typename NodeAllocator>
					static node* _K_build_new_node(NodeAllocator & alloc);

					template <typename NodeAllocator, typename Arg0>
					static node* _K_build_new_node(NodeAllocator & alloc, const Arg0& arg0);

					template <typename NodeAllocator, typename Arg0, typename Arg1>
					static node* _K_build_new_node(NodeAllocator & alloc, const Arg0& arg0, const Arg1& arg1);

					template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
					static node* _K_build_new_node(NodeAllocator & alloc, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#			endif

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					std::pair<node*, node*> _K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, Args&& ...args);

#			else

					template <typename NodeAllocator>
					static
					std::pair<node*, node*> _K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n);

					template <typename NodeAllocator, typename Arg0>
					static
					std::pair<node*, node*> _K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0& arg0);

					template <typename NodeAllocator, typename Arg0, typename Arg1>
					static
					std::pair<node*, node*> _K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0& arg0, const Arg1& arg1);

					template <typename NodeAllocator, typename Arg0, typename Arg1, typename Arg2>
					static
					std::pair<node*, node*> _K_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#			endif

					/*
					 * @warning Especial case: first == last
					 */
					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							std::pair<node*, node*>
					>::type
					_K_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					std::pair<node*, node*>
					_K_build_new_nodes_range_unguarded_move(NodeAllocator & alloc, iterator first, iterator last);

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void _K_destroy_node(NodeAllocator & alloc, node_base * p_node_base)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::memory::allocator_traits<NodeAllocator>::destroy(alloc, kerbal::utility::declval<node*>())) &&
								noexcept(kerbal::memory::allocator_traits<NodeAllocator>::deallocate(alloc, kerbal::utility::declval<node*>(), 1))
							)
					;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void _K_consecutive_destroy_node(NodeAllocator & alloc, node_base * start)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::utility::declthis<sl_allocator_unrelated>()->_K_destroy_node(alloc, kerbal::utility::declval<node_base *>()))
							)
					;

#			if __cplusplus >= 201703L
#				if __has_include(<memory_resource>)

					template <typename Node>
					KERBAL_CONSTEXPR20
					static void _K_consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * start)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::utility::declthis<sl_allocator_unrelated>()->_K_destroy_node(alloc, kerbal::utility::declval<node_base *>()))
							)
					;

#				endif
#			endif

			};


			template <typename Tp, typename Allocator>
			struct sl_node_allocator_helper
			{
				private:
					typedef kerbal::container::detail::sl_allocator_unrelated<Tp>		sl_allocator_unrelated;
					typedef typename sl_allocator_unrelated::value_type					value_type;
					typedef typename sl_allocator_unrelated::node						node;

				public:
					typedef kerbal::memory::allocator_traits<Allocator>							tp_allocator_traits;
					typedef typename tp_allocator_traits::template rebind_alloc<node>::other	node_allocator_type;
					typedef typename tp_allocator_traits::template rebind_traits<node>::other	node_allocator_traits;
			};


			template <typename Tp, typename Allocator>
			class sl_allocator_overload:
					private kerbal::utility::member_compress_helper<
							typename sl_node_allocator_helper<Tp, Allocator>::node_allocator_type
					>
			{
				private:
					typedef kerbal::utility::member_compress_helper<
							typename sl_node_allocator_helper<Tp, Allocator>::node_allocator_type
					> super;

				private:
					typedef kerbal::container::detail::sl_node_allocator_helper<Tp, Allocator>
							sl_node_allocator_helper;

				protected:
					typedef typename sl_node_allocator_helper::tp_allocator_traits		tp_allocator_traits;
					typedef typename sl_node_allocator_helper::node_allocator_type		node_allocator_type;
					typedef typename sl_node_allocator_helper::node_allocator_traits	node_allocator_traits;

				protected:

					KERBAL_CONSTEXPR
					sl_allocator_overload()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<super>::value
								)
							: super(kerbal::utility::in_place_t())
					{
					}

					KERBAL_CONSTEXPR
					explicit sl_allocator_overload(const Allocator & allocator)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, const Allocator&>::value)
								)
							: super(kerbal::utility::in_place_t(), allocator)
					{
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR
					explicit sl_allocator_overload(Allocator && allocator)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, Allocator&&>::value)
								)
							: super(kerbal::utility::in_place_t(), kerbal::compatibility::move(allocator))
					{
					}

#			endif

					KERBAL_CONSTEXPR14
					node_allocator_type& alloc() KERBAL_NOEXCEPT
					{
						return super::member();
					}

					KERBAL_CONSTEXPR14
					const node_allocator_type& alloc() const KERBAL_NOEXCEPT
					{
						return super::member();
					}

				private:

					template <bool propagate_on_container_swap>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<!propagate_on_container_swap>::type
					_K_swap_allocator_impl(sl_allocator_overload & ano) KERBAL_NOEXCEPT
					{
					}

					template <bool propagate_on_container_swap>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<propagate_on_container_swap>::type
					_K_swap_allocator_impl(sl_allocator_overload & ano)
					{
						kerbal::algorithm::swap(this->alloc(), ano.alloc());
					}

				protected:

					KERBAL_CONSTEXPR20
					void _K_swap_allocator_if_propagate(sl_allocator_overload & ano)
					{
						typedef typename node_allocator_traits::propagate_on_container_swap propagate_on_container_swap;
						this->_K_swap_allocator_impl<propagate_on_container_swap::value>(ano);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/single_list_base.impl.hpp>

#endif // KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_HPP
