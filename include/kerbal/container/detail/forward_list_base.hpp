/**
 * @file       forward_list_base.hpp
 * @brief
 * @date       2021-01-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_HPP

#include <kerbal/container/fwd/forward_list.fwd.hpp>

#include <kerbal/container/detail/single_list_node.hpp>
#include <kerbal/container/detail/forward_list_iterator.hpp>

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

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class fl_type_unrelated
			{
				public:
					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef kerbal::container::detail::sl_node_base					node_base;
					typedef kerbal::container::detail::fl_iter_type_unrelated		basic_iterator;
					typedef kerbal::container::detail::fl_kiter_type_unrelated		basic_const_iterator;

				protected:
					node_base head_node;

				public:
				//===================
				// construct/copy/destroy

#			if __cplusplus < 201103L

					fl_type_unrelated() KERBAL_NOEXCEPT
					{
					}

#			else

					fl_type_unrelated() noexcept = default;

					// pre-cond: fl_type_unrelated manage same type
					KERBAL_CONSTEXPR14
					fl_type_unrelated(fl_type_unrelated && src) KERBAL_NOEXCEPT
					{
						head_node.next = src.head_node.next;
						src.head_node.next = NULL;
					}

#			endif

				//===================
				// iterator

					KERBAL_CONSTEXPR14
					basic_iterator basic_before_begin() KERBAL_NOEXCEPT
					{
						return basic_iterator(&this->head_node);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_before_begin() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(&this->head_node);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_cbefore_begin() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(&this->head_node);
					}

					KERBAL_CONSTEXPR14
					basic_iterator basic_begin() KERBAL_NOEXCEPT
					{
						return basic_iterator(this->head_node.next);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_begin() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(this->head_node.next);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_cbegin() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(this->head_node.next);
					}

					KERBAL_CONSTEXPR14
					basic_iterator basic_end() KERBAL_NOEXCEPT
					{
						return basic_iterator(NULL);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_end() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(NULL);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_cend() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(NULL);
					}

				//===================
				// capacity

					KERBAL_CONSTEXPR14
					bool empty() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					size_type size() const KERBAL_NOEXCEPT;

				//===================
				// operation

					KERBAL_CONSTEXPR14
					static void _K_iter_swap_after(basic_const_iterator a, basic_const_iterator b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static void _K_reverse_after(basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void reverse() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static void _K_splice_after(basic_const_iterator pos, fl_type_unrelated & other) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static void _K_splice_after(basic_const_iterator pos, basic_const_iterator opos) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static void _K_splice_after(basic_const_iterator pos, basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT;

				//===================
				// private

					KERBAL_CONSTEXPR14
					static void _K_hook_node_after(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static void _K_hook_node_after(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static node_base * _K_unhook_node_after(basic_const_iterator pos) KERBAL_NOEXCEPT;

					// pre-cond: first != last;
					KERBAL_CONSTEXPR14
					static node_base * _K_unhook_node_after(basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT;

					// pre-cond: lhs and rhs are lists of same type
					KERBAL_CONSTEXPR14
					static void _K_swap_type_unrelated(fl_type_unrelated & lhs, fl_type_unrelated & rhs) KERBAL_NOEXCEPT;

			};

			template <typename Tp>
			class fl_allocator_unrelated:
					protected kerbal::container::detail::fl_type_unrelated
			{
				private:
					typedef kerbal::container::detail::fl_type_unrelated		super;
					typedef kerbal::container::detail::fl_type_unrelated		fl_type_unrelated;

				public:
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

					typedef fl_type_unrelated::size_type				size_type;
					typedef fl_type_unrelated::difference_type			difference_type;

					typedef kerbal::container::detail::fl_iter<Tp>		iterator;
					typedef kerbal::container::detail::fl_kiter<Tp>		const_iterator;

					typedef fl_type_unrelated::node_base				node_base;
					typedef kerbal::container::detail::sl_node<Tp>		node;


				public:

#			if __cplusplus >= 201103L

					fl_allocator_unrelated() = default;

					// pre-cond: allocator allows
					KERBAL_CONSTEXPR14
					fl_allocator_unrelated(fl_allocator_unrelated && src) KERBAL_NOEXCEPT;

#			endif

				//===================
				// iterator

					KERBAL_CONSTEXPR14
					iterator before_begin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator before_begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator cbefore_begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					iterator begin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator cbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					iterator end() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator end() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator cend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					iterator nth(size_type index) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator nth(size_type index) const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					size_type index_of(iterator it) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					size_type index_of(const_iterator it) const KERBAL_NOEXCEPT;

				//===================
				// capacity

					using fl_type_unrelated::empty;
					using fl_type_unrelated::size;

					KERBAL_CONSTEXPR
					size_type max_size() const KERBAL_NOEXCEPT
					{
						return static_cast<size_type>(-1) / sizeof(node);
					}

				//===================
				// element access

					KERBAL_CONSTEXPR14
					reference front() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reference front() const KERBAL_NOEXCEPT;

				//===================
				// erase

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static iterator _K_erase_after(NodeAllocator & alloc, const_iterator pos);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static iterator _K_erase_after(NodeAllocator & alloc, const_iterator first, const_iterator last);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void _K_clear(NodeAllocator & alloc) KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declthis<fl_allocator_unrelated>()->_K_consecutive_destroy_node(
									alloc,
									kerbal::utility::declthis<fl_allocator_unrelated>()->head_node.next,
									NULL
							))
					);

				//===================
				// operation

					KERBAL_CONSTEXPR14
					static void _K_iter_swap_after(const_iterator a, const_iterator b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static void _K_reverse_after(const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

					using fl_type_unrelated::reverse;

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> MERGE_VER_NOTHROW;

#				if __cpp_exceptions
					typedef kerbal::type_traits::integral_constant<int, 1> MERGE_VER_MAY_THROW;
#				endif

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					void _K_merge_impl(fl_allocator_unrelated & other, BinaryPredict cmp, MERGE_VER_NOTHROW) KERBAL_NOEXCEPT;

#				if __cpp_exceptions
					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					void _K_merge_impl(fl_allocator_unrelated & other, BinaryPredict cmp, MERGE_VER_MAY_THROW);
#				endif


				public:
					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					void _K_merge(fl_allocator_unrelated & other, BinaryPredict cmp);

					KERBAL_CONSTEXPR14
					void _K_merge(fl_allocator_unrelated & other);

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> MSM_VER_NOTHROW;

#				if __cpp_exceptions
					typedef kerbal::type_traits::integral_constant<int, 1> MSM_VER_MAY_THROW;
#				endif

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static const_iterator _K_merge_sort_merge_after_impl(const_iterator before_first, const_iterator before_mid, const_iterator before_last, BinaryPredict cmp, MSM_VER_NOTHROW);

#				if __cpp_exceptions
					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static const_iterator _K_merge_sort_merge_after_impl(const_iterator before_first, const_iterator before_mid, const_iterator before_last, BinaryPredict cmp, MSM_VER_MAY_THROW);
#				endif

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static const_iterator _K_merge_sort_merge_after(const_iterator before_first, const_iterator before_mid, const_iterator last, BinaryPredict cmp);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static const_iterator _K_merge_sort_n_after(const_iterator before_first, size_type n, BinaryPredict cmp);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static void _K_merge_sort_after(const_iterator first, const_iterator last, BinaryPredict cmp);

				public:

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static void _K_sort_after(const_iterator first, const_iterator last, BinaryPredict cmp);

					KERBAL_CONSTEXPR14
					static void _K_sort_after(const_iterator first, const_iterator last);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					void _K_sort(BinaryPredict cmp);

					KERBAL_CONSTEXPR14
					void _K_sort();

				private:

					struct remove_predict
					{
							const_reference val;

							KERBAL_CONSTEXPR14
							explicit remove_predict(const_reference val) KERBAL_NOEXCEPT
									: val(val)
							{
							}

							KERBAL_CONSTEXPR14
							bool operator()(const_reference with) const
									KERBAL_CONDITIONAL_NOEXCEPT(
											noexcept(val == with)
									)
							{
								return val == with;
							}
					};

				public:

					template <typename NodeAllocator, typename UnaryPredicate>
					KERBAL_CONSTEXPR20
					static size_type _K_remove_after_if(NodeAllocator & alloc, const_iterator first, const_iterator last, UnaryPredicate predicate);

					template <typename NodeAllocator, typename UnaryPredicate>
					KERBAL_CONSTEXPR20
					size_type _K_remove_if(NodeAllocator & alloc, UnaryPredicate predicate);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static size_type _K_remove_after(NodeAllocator & alloc, const_iterator first, const_iterator last, const_reference val);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					size_type _K_remove(NodeAllocator & alloc, const_reference val);

					template <typename NodeAllocator, typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static size_type _K_unique(NodeAllocator & alloc, const_iterator first, const_iterator last, BinaryPredict equal_to);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static size_type _K_unique(NodeAllocator & alloc, const_iterator first, const_iterator last);

					template <typename NodeAllocator, typename BinaryPredict>
					KERBAL_CONSTEXPR20
					size_type _K_unique(NodeAllocator & alloc, BinaryPredict equal_to);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					size_type _K_unique(NodeAllocator & alloc);


				//===================
				// private

				protected:

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
					static void _K_destroy_node(NodeAllocator & alloc, node_base * p_node_base) KERBAL_NOEXCEPT;

				private:
					typedef kerbal::type_traits::integral_constant<int, 0>		CNSCTV_DES_VER_DEFAULT;
					typedef kerbal::type_traits::integral_constant<int, 1>		CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE;
					typedef kerbal::type_traits::integral_constant<int, 2>		CNSCTV_DES_VER_NO_DESTROY;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void _K_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * first, node_base * last, CNSCTV_DES_VER_DEFAULT) KERBAL_NOEXCEPT;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void _K_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * first, node_base * last, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE) KERBAL_NOEXCEPT;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void _K_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * first, node_base * last, CNSCTV_DES_VER_NO_DESTROY) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void _K_consecutive_destroy_node(NodeAllocator & alloc, node_base * first, node_base * last) KERBAL_NOEXCEPT;

#			if __cplusplus >= 201703L
#				if __has_include(<memory_resource>)

					template <typename Node>
					KERBAL_CONSTEXPR20
					static void _K_consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * first, node_base * last) KERBAL_NOEXCEPT;

#				endif
#			endif

			};


			template <typename Tp, typename Allocator>
			struct fl_node_allocator_helper
			{
				private:
					typedef kerbal::container::detail::fl_allocator_unrelated<Tp>		fl_allocator_unrelated;
					typedef typename fl_allocator_unrelated::value_type					value_type;
					typedef typename fl_allocator_unrelated::node						node;

				public:
					typedef kerbal::memory::allocator_traits<Allocator>							tp_allocator_traits;
					typedef typename tp_allocator_traits::template rebind_alloc<node>::other	node_allocator_type;
					typedef typename tp_allocator_traits::template rebind_traits<node>::other	node_allocator_traits;
			};


			template <typename Tp, typename Allocator>
			class fl_allocator_overload:
					private kerbal::utility::member_compress_helper<
							typename fl_node_allocator_helper<Tp, Allocator>::node_allocator_type
					>
			{
				private:
					typedef kerbal::utility::member_compress_helper<
							typename fl_node_allocator_helper<Tp, Allocator>::node_allocator_type
					> super;

				private:
					typedef kerbal::container::detail::fl_node_allocator_helper<Tp, Allocator>
																						fl_node_allocator_helper;

				protected:
					typedef typename fl_node_allocator_helper::tp_allocator_traits		tp_allocator_traits;
					typedef typename fl_node_allocator_helper::node_allocator_type		node_allocator_type;
					typedef typename fl_node_allocator_helper::node_allocator_traits	node_allocator_traits;

				protected:

					KERBAL_CONSTEXPR
					fl_allocator_overload()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<super>::value
								)
							: super(kerbal::utility::in_place_t())
					{
					}

					KERBAL_CONSTEXPR
					explicit
					fl_allocator_overload(const Allocator & allocator)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, const Allocator&>::value)
								)
							: super(kerbal::utility::in_place_t(), allocator)
					{
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR
					explicit
					fl_allocator_overload(Allocator && allocator)
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
					_K_swap_allocator_impl(fl_allocator_overload & ano) KERBAL_NOEXCEPT
					{
					}

					template <bool propagate_on_container_swap>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<propagate_on_container_swap>::type
					_K_swap_allocator_impl(fl_allocator_overload & ano)
					{
						kerbal::algorithm::swap(this->alloc(), ano.alloc());
					}

				protected:

					KERBAL_CONSTEXPR20
					void _K_swap_allocator_if_propagate(fl_allocator_overload & ano)
					{
						typedef typename node_allocator_traits::propagate_on_container_swap propagate_on_container_swap;
						this->_K_swap_allocator_impl<propagate_on_container_swap::value>(ano);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/forward_list_base.impl.hpp>

#endif // KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_HPP
