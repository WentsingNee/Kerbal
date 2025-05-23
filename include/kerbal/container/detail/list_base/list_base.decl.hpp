/**
 * @file       list_base.decl.hpp
 * @brief
 * @date       2020-6-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_BASE_DECL_HPP

#include <kerbal/container/list/list.fwd.hpp>
#include <kerbal/memory/allocator/monotonic_allocator/monotonic_allocator.fwd.hpp>

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compare/std_compare/std_compare.fwd.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/function/identity.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_integral.hpp>
#include <kerbal/utility/declval.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <cstddef>

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <kerbal/type_traits/is_trivially_destructible.hpp>
#		include <memory_resource>
#	endif
#endif

#include <kerbal/container/detail/list_base/list_node.hpp>
#include <kerbal/container/detail/list_base/list_iterator.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename T>
			struct is_list_radix_sort_acceptable_type :
				kerbal::type_traits::bool_constant<
					kerbal::type_traits::is_integral<T>::value &&
					sizeof(T) <= 4
				>
			{
			};

			class list_type_unrelated
			{
				private:
					template <typename T>
					friend class list_type_only;

				protected:
					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef kerbal::container::detail::list_node_base					node_base;
					typedef kerbal::container::detail::list_iter_type_unrelated			basic_iterator;
					typedef kerbal::container::detail::list_kiter_type_unrelated		basic_const_iterator;

				protected:
					node_base k_head;

				//===================
				// construct/copy/destroy

#			if __cplusplus >= 201103L

					list_type_unrelated() = default;

#			else

					list_type_unrelated() KERBAL_NOEXCEPT :
						k_head()
					{
					}

#			endif


					KERBAL_CONSTEXPR
					explicit list_type_unrelated(init_list_node_ptr_to_self_tag tag) KERBAL_NOEXCEPT :
						k_head(tag)
					{
					}

				//===================
				// iterator

					KERBAL_CONSTEXPR14
					basic_iterator
					basic_begin() KERBAL_NOEXCEPT
					{
						return basic_iterator(this->k_head.next);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator
					basic_begin() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(this->k_head.next);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator
					basic_cbegin() const KERBAL_NOEXCEPT
					{
						return this->basic_begin();
					}

					KERBAL_CONSTEXPR14
					basic_iterator
					basic_end() KERBAL_NOEXCEPT
					{
						return basic_iterator(&this->k_head);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator
					basic_end() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(&this->k_head);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator
					basic_cend() const KERBAL_NOEXCEPT
					{
						return this->basic_end();
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
					static
					void k_iter_swap(basic_const_iterator a, basic_const_iterator b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_reverse(basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void reverse() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					basic_iterator
					k_rotate(basic_const_iterator first, basic_const_iterator n_first, basic_const_iterator last) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_splice(
						basic_const_iterator pos,
						list_type_unrelated & other
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_splice(
						basic_const_iterator pos,
						basic_const_iterator opos
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_splice(
						basic_const_iterator pos,
						basic_const_iterator first, basic_const_iterator last
					) KERBAL_NOEXCEPT;

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					static
					void k_splice(
						basic_const_iterator pos,
						list_type_unrelated && other
					) KERBAL_NOEXCEPT;

#			endif

					KERBAL_CONSTEXPR14
					static
					void
					k_radix_sort_back_fill(
						kerbal::type_traits::false_type /*unsigned*/,
						basic_const_iterator insert_pos,
						list_type_unrelated buckets[], std::size_t BUCKETS_NUM
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void
					k_radix_sort_back_fill(
						kerbal::type_traits::true_type /*signed*/,
						basic_const_iterator insert_pos,
						list_type_unrelated buckets[], std::size_t BUCKETS_NUM
					) KERBAL_NOEXCEPT;

				//===================
				// private

					KERBAL_CONSTEXPR14
					void k_init_node_base() KERBAL_NOEXCEPT
					{
						this->k_head.prev = &this->k_head;
						this->k_head.next = &this->k_head;
					}

					KERBAL_CONSTEXPR14
					static
					void k_hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					node_base * k_unhook_node(basic_iterator pos) KERBAL_NOEXCEPT;

					// pre-cond: first != last;
					KERBAL_CONSTEXPR14
					static
					list_node_base_chain
					k_unhook_node(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT;

					// pre-cond: `not_empty_list` and `empty_list` are lists of same type
					KERBAL_CONSTEXPR14
					static
					void k_swap_with_empty(
						list_type_unrelated & not_empty_list,
						list_type_unrelated & empty_list
					) KERBAL_NOEXCEPT;

					// pre-cond: lhs and rhs are lists of same type
					KERBAL_CONSTEXPR14
					static
					void k_swap_type_unrelated(
						list_type_unrelated & lhs,
						list_type_unrelated & rhs
					) KERBAL_NOEXCEPT;

			};

			template <typename T>
			class list_type_only :
				protected list_type_unrelated
			{
				private:
					typedef list_type_unrelated			super;
					typedef list_type_unrelated			list_type_unrelated;

					template <typename U, typename Allocator>
					friend struct list_typedef_helper;

					template <typename U, typename Allocator>
					friend class kerbal::container::list;

				protected:
					typedef T							value_type;
					typedef const value_type			const_type;
					typedef value_type &				reference;
					typedef const value_type &			const_reference;
					typedef value_type *				pointer;
					typedef const value_type *			const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type &&				rvalue_reference;
					typedef const value_type &&			const_rvalue_reference;
#			endif

					typedef list_type_unrelated::size_type						size_type;
					typedef list_type_unrelated::difference_type				difference_type;

					typedef kerbal::container::detail::list_iter<T>				iterator;
					typedef kerbal::container::detail::list_kiter<T>			const_iterator;
					typedef kerbal::iterator::reverse_iterator<iterator>		reverse_iterator;
					typedef kerbal::iterator::reverse_iterator<const_iterator>	const_reverse_iterator;

					typedef list_type_unrelated::node_base						node_base;
					typedef kerbal::container::detail::list_node<value_type>	node;


				protected:

				//===================
				// construct/copy/destroy

#			if __cplusplus >= 201103L

					struct is_nothrow_default_constructible :
						kerbal::type_traits::true_type
					{
					};

					list_type_only() = default; // for g++ early version

					using super::super;

#			else

					list_type_only() KERBAL_NOEXCEPT :
						super()
					{
					}

#			endif

#			if __cplusplus >= 201103L

					struct is_nothrow_init_to_self_constructible :
						kerbal::type_traits::true_type
					{
					};

#			else

					explicit
					list_type_only(init_list_node_ptr_to_self_tag tag) KERBAL_NOEXCEPT :
						super(tag)
					{
					}

#			endif

#			if __cplusplus >= 201103L

					struct is_nothrow_move_constructible :
						kerbal::type_traits::true_type
					{
					};

					KERBAL_CONSTEXPR14
					list_type_only(list_type_only && src) KERBAL_NOEXCEPT;

				private:

					// move construct using allocator, allocator is equal
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_ae(list_type_only && src) KERBAL_NOEXCEPT;

					// move construct using allocator, allocator is not equal
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_ane(
						NodeAllocator & this_alloc,
						list_type_only && src
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_helper(
						NodeAllocator & this_alloc,
						NodeAllocator && src_alloc, list_type_only && src,
						kerbal::type_traits::false_type /*is_always_equal*/
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_helper(
						NodeAllocator & this_alloc,
						NodeAllocator && src_alloc, list_type_only && src,
						kerbal::type_traits::true_type /*is_always_equal*/
					) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					struct is_nothrow_move_constructible_using_allocator :
						kerbal::memory::allocator_traits<NodeAllocator>::is_always_equal
					{
					};

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					list_type_only(
						NodeAllocator & this_alloc,
						NodeAllocator && src_alloc, list_type_only && src
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							is_nothrow_move_constructible_using_allocator<NodeAllocator>::value
						)
					;

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					list_type_only(
						NodeAllocator & alloc,
						size_type n
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					list_type_only(
						NodeAllocator & alloc,
						size_type n, const_reference val
					);

					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					list_type_only(
						NodeAllocator & alloc,
						InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_destroy_using_allocator(NodeAllocator & alloc) KERBAL_NOEXCEPT;


				//===================
				// assign

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> CPYASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> CPYASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> CPYASS_VER_ALWAYS_EQUAL;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						NodeAllocator & alloc,
						const NodeAllocator & src_alloc, const list_type_only & src,
						CPYASS_VER_NOT_PROPAGATE
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						NodeAllocator & alloc,
						const NodeAllocator & src_alloc, const list_type_only & src,
						CPYASS_VER_PROPAGATE
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						NodeAllocator & alloc,
						const NodeAllocator & src_alloc, const list_type_only & src,
						CPYASS_VER_ALWAYS_EQUAL
					);

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & alloc,
						const NodeAllocator & src_alloc, const list_type_only & src
					);

#			if __cplusplus >= 201103L

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_move_assign(NodeAllocator & alloc, list_type_only && src) KERBAL_NOEXCEPT;

				private:

					// move assign using allocator, allocator is equal
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ae(NodeAllocator & alloc, list_type_only && src) KERBAL_NOEXCEPT;

					// move assign using allocator, allocator is not equal
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ane(NodeAllocator & alloc, list_type_only && src);

					typedef kerbal::type_traits::integral_constant<int, 0> MOVASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> MOVASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> MOVASS_VER_ALWAYS_EQUAL;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						NodeAllocator & alloc,
						NodeAllocator && src_alloc, list_type_only && src,
						MOVASS_VER_NOT_PROPAGATE
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						NodeAllocator & alloc,
						NodeAllocator && src_alloc, list_type_only && src,
						MOVASS_VER_PROPAGATE
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						NodeAllocator & alloc,
						NodeAllocator && /*src_alloc*/, list_type_only && src,
						MOVASS_VER_ALWAYS_EQUAL
					) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					struct is_nothrow_move_assign_using_allocator :
						kerbal::memory::allocator_traits<NodeAllocator>::is_always_equal
					{
					};

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & alloc,
						NodeAllocator && src_alloc, list_type_only && src
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							is_nothrow_move_assign_using_allocator<NodeAllocator>::value
						)
					;

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & alloc,
						size_type count, const_reference val
					);

					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					k_assign_using_allocator(
						NodeAllocator & alloc,
						InputIterator first, InputIterator last
					);


				//===================
				// element access

					KERBAL_CONSTEXPR20
					reference front() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reference front() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reference back() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reference back() const KERBAL_NOEXCEPT;

				//===================
				// iterator

					KERBAL_CONSTEXPR20
					iterator begin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator cbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					iterator end() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator end() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator cend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reverse_iterator rbegin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reverse_iterator rend() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator rend() const KERBAL_NOEXCEPT;

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
				// capacity

					using list_type_unrelated::empty;
					using list_type_unrelated::size;

				//===================
				// insert

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_emplace_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos,
						Args && ... args
					);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template < \
						typename NodeAllocator \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					static \
					iterator \
					k_emplace_using_allocator( \
						NodeAllocator & alloc, \
						const_iterator pos \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_insert_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos,
						const_reference val
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_insert_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos,
						rvalue_reference val
					);

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_insert_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos,
						size_type n, const_reference val
					);

					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						iterator
					>::type
					k_insert_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos,
						InputIterator first, InputIterator last
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					reference k_emplace_front_using_allocator(NodeAllocator & alloc, Args && ... args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template < \
						typename NodeAllocator \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					reference \
					k_emplace_front_using_allocator( \
						NodeAllocator & alloc \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_push_front_using_allocator(NodeAllocator & alloc, const_reference val);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_push_front_using_allocator(NodeAllocator & alloc, rvalue_reference val);

#			endif

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					reference
					k_emplace_back_using_allocator(
						NodeAllocator & alloc,
						Args && ... args
					);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template < \
						typename NodeAllocator \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					reference \
					k_emplace_back_using_allocator( \
						NodeAllocator & alloc \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_push_back_using_allocator(
						NodeAllocator & alloc,
						const_reference val
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_push_back_using_allocator(
						NodeAllocator & alloc,
						rvalue_reference val
					);

#			endif

				//===================
				// erase

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_erase_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_erase_using_allocator(
						NodeAllocator & alloc,
						const_iterator first, const_iterator last
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_pop_front_using_allocator(NodeAllocator & alloc);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_pop_back_using_allocator(NodeAllocator & alloc);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_clear_using_allocator(NodeAllocator & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								k_erase_using_allocator(
									alloc,
									kerbal::utility::declthis<list_type_only>()->cbegin(),
									kerbal::utility::declthis<list_type_only>()->cend()
								)
							)
						)
					;

				//===================
				// operation

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_resize_using_allocator(NodeAllocator & alloc, size_type count);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_resize_using_allocator(NodeAllocator & alloc, size_type count, const_reference value);

					KERBAL_CONSTEXPR20
					static
					void k_iter_swap(const_iterator a, const_iterator b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					static
					void k_reverse(const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

					using list_type_unrelated::reverse;

					KERBAL_CONSTEXPR20
					iterator rotate(const_iterator first, const_iterator n_first, const_iterator last) KERBAL_NOEXCEPT;

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> MERGE_VER_NOTHROW;

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT
					typedef kerbal::type_traits::integral_constant<int, 1> MERGE_VER_MAY_THROW;
#				endif

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					void k_merge_impl(list_type_only & other, BinaryPredict cmp, MERGE_VER_NOTHROW) KERBAL_NOEXCEPT;

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT
					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					void k_merge_impl(list_type_only & other, BinaryPredict cmp, MERGE_VER_MAY_THROW);
#				endif


				protected:
					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					void k_merge(list_type_only & other, BinaryPredict cmp);

					KERBAL_CONSTEXPR20
					void k_merge(list_type_only & other);

#			if __cplusplus >= 201103L

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					void k_merge(list_type_only && other, BinaryPredict cmp);

					KERBAL_CONSTEXPR20
					void k_merge(list_type_only && other);

#			endif

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> MSM_VER_NOTHROW;

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT
					typedef kerbal::type_traits::integral_constant<int, 1> MSM_VER_MAY_THROW;
#				endif

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					void
					k_merge_sort_merge(
						const_iterator first, const_iterator mid, const_iterator last,
						BinaryPredict cmp,
						MSM_VER_NOTHROW
					);

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT
					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					void
					k_merge_sort_merge(
						const_iterator first, const_iterator mid, const_iterator last,
						BinaryPredict cmp,
						MSM_VER_MAY_THROW
					);
#				endif

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					void
					k_merge_sort_merge(
						const_iterator first, const_iterator mid, const_iterator last,
						BinaryPredict cmp
					);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					const_iterator k_merge_sort_n(const_iterator first, difference_type len, BinaryPredict cmp);

				protected:

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					void k_merge_sort(const_iterator first, const_iterator last, BinaryPredict cmp);


				private:

					template <std::size_t RADIX_BIT_WIDTH>
					KERBAL_CONSTEXPR20
					static
					void k_radix_sort(
						const_iterator first, const_iterator last, kerbal::type_traits::false_type asc,
						kerbal::type_traits::integral_constant<std::size_t, RADIX_BIT_WIDTH>
					) KERBAL_NOEXCEPT;

					template <std::size_t RADIX_BIT_WIDTH>
					KERBAL_CONSTEXPR20
					static
					void k_radix_sort(
						const_iterator first, const_iterator last, kerbal::type_traits::true_type desc,
						kerbal::type_traits::integral_constant<std::size_t, RADIX_BIT_WIDTH>
					) KERBAL_NOEXCEPT;

				protected:

					template <typename Order>
					KERBAL_CONSTEXPR20
					static
					void k_radix_sort(const_iterator first, const_iterator last, Order order) KERBAL_NOEXCEPT;

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_radix_sort(const_iterator first, const_iterator last) KERBAL_NOEXCEPT;


				private:

					template <bool is_radix_sort_acceptable_type, typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, BinaryPredict cmp);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, kerbal::compare::less<value_type> cmp);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, kerbal::compare::greater<value_type> cmp);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, kerbal::compare::less<void> cmp);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, kerbal::compare::greater<void> cmp);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, std::less<value_type> cmp);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, std::greater<value_type> cmp);

#			if __cplusplus >= 201402L

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, std::less<void> cmp);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, std::greater<void> cmp);

#			endif

					template <bool is_radix_sort_acceptable_type, typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<!is_radix_sort_acceptable_type>::type
					k_sort_method_overload(const_iterator first, const_iterator last, BinaryPredict cmp);


				protected:

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					void k_sort(const_iterator first, const_iterator last, BinaryPredict cmp);

					KERBAL_CONSTEXPR20
					static
					void k_sort(const_iterator first, const_iterator last);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					void sort(BinaryPredict cmp);

					KERBAL_CONSTEXPR20
					void sort();

				private:

					struct remove_predict
					{
							const_reference val;

							KERBAL_CONSTEXPR14
							explicit remove_predict(const_reference val) KERBAL_NOEXCEPT :
								val(val)
							{
							}

							KERBAL_CONSTEXPR14
							bool operator()(const_reference with) const
								KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::compare::equal_to<value_type>()(val, with))
								)
							{
								return kerbal::compare::equal_to<value_type>()(val, with);
							}
					};

				protected:

					template <typename NodeAllocator, typename UnaryPredicate>
					KERBAL_CONSTEXPR20
					static
					size_type
					k_remove_if_using_allocator(
						NodeAllocator & alloc,
						const_iterator first, const_iterator last,
						UnaryPredicate predicate
					);

					template <typename NodeAllocator, typename UnaryPredicate>
					KERBAL_CONSTEXPR20
					size_type
					k_remove_if_using_allocator(
						NodeAllocator & alloc,
						UnaryPredicate predicate
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename BinaryPredicate = kerbal::compare::equal_to<>, typename Project = kerbal::function::identity>
					KERBAL_CONSTEXPR20
					size_type k_unique_using_allocator(NodeAllocator & alloc, BinaryPredicate pred = {}, Project proj = {});

#			else

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					size_type
					k_remove_using_allocator(
						NodeAllocator & alloc,
						const_iterator first, const_iterator last,
						const_reference val
					);

					template <typename NodeAllocator, typename BinaryPredicate, typename Project>
					KERBAL_CONSTEXPR20
					size_type k_unique_using_allocator(NodeAllocator & alloc, BinaryPredicate pred, Project proj);

#			endif


#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename BinaryPredicate = kerbal::compare::equal_to<>, typename Project = kerbal::function::identity>
					KERBAL_CONSTEXPR20
					static size_type k_unique_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, BinaryPredicate pred = {}, Project proj = {});

#			else

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					size_type
					k_remove_using_allocator(
						NodeAllocator & alloc,
						const_reference val
					);

					template <typename NodeAllocator, typename BinaryPredicate>
					KERBAL_CONSTEXPR20
					static
					size_type
					k_unique_using_allocator(
						NodeAllocator & alloc,
						const_iterator first, const_iterator last,
						BinaryPredicate pred
					);

					template <typename NodeAllocator, typename BinaryPredicate>
					KERBAL_CONSTEXPR20
					size_type
					k_unique_using_allocator(
						NodeAllocator & alloc,
						BinaryPredicate pred
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					size_type
					k_unique_using_allocator(
						NodeAllocator & alloc,
						const_iterator first, const_iterator last
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					size_type
					k_unique_using_allocator(NodeAllocator & alloc);

					template <typename NodeAllocator, typename BinaryPredicate, typename Project>
					KERBAL_CONSTEXPR20
					static size_type k_unique_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, BinaryPredicate pred, Project proj);

#			endif


					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					void k_set_difference(list_type_only & l1, const list_type_only & l2, list_type_only & lto, BinaryPredict cmp);

					KERBAL_CONSTEXPR20
					static
					void k_set_difference(list_type_only & l1, const list_type_only & l2, list_type_only & lto);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					void k_set_intersection(list_type_only & l1, list_type_only & l2, list_type_only & lto, BinaryPredict cmp);

					KERBAL_CONSTEXPR20
					static
					void k_set_intersection(list_type_only & l1, list_type_only & l2, list_type_only & lto);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					void k_set_symmetric_difference(list_type_only & l1, list_type_only & l2, list_type_only & lto, BinaryPredict cmp);

					KERBAL_CONSTEXPR20
					static
					void k_set_symmetric_difference(list_type_only & l1, list_type_only & l2, list_type_only & lto);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					void k_set_union(list_type_only & l1, list_type_only & l2, list_type_only & lto, BinaryPredict cmp);

					KERBAL_CONSTEXPR20
					static
					void k_set_union(list_type_only & l1, list_type_only & l2, list_type_only & lto);

				//===================
				// private

#			if __cplusplus >= 201103L

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT

					template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<!nothrow_while_construct, node *>::type
					k_build_new_node_impl(NodeAllocator & alloc, Args && ... args);

					template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<nothrow_while_construct, node *>::type
					k_build_new_node_impl(NodeAllocator & alloc, Args && ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::allocator_traits<NodeAllocator>::allocate_one(alloc))
						)
					;

#				endif

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					node * k_build_new_node(
						NodeAllocator & alloc,
						Args && ... args
					);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template < \
						typename NodeAllocator \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					static \
					node * k_build_new_node( \
						NodeAllocator & alloc \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#			endif

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					list_node_chain<T>
					k_build_n_new_nodes_unguarded(
						NodeAllocator & alloc,
						size_type n, Args && ... args
					);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static \
					list_node_chain<T> \
					k_build_n_new_nodes_unguarded( \
						NodeAllocator & alloc, \
						size_type n \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#			endif

					/*
					 * @warning Especial case: first == last
					 */
					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						list_node_chain<T>
					>::type
					k_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_destroy_node(NodeAllocator & alloc, node_base * p_node_base)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::allocator_traits<NodeAllocator>::destroy(
									alloc,
									kerbal::utility::declval<typename kerbal::memory::allocator_traits<NodeAllocator>::pointer>()
								)
							) &&
							noexcept(
								kerbal::memory::allocator_traits<NodeAllocator>::deallocate_one(
									alloc,
									kerbal::utility::declval<typename kerbal::memory::allocator_traits<NodeAllocator>::pointer>()
								)
							)
						)
					;

				private:
					typedef kerbal::type_traits::integral_constant<int, 0>		CNSCTV_DES_VER_DEFAULT;
					typedef kerbal::type_traits::integral_constant<int, 1>		CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE;
					typedef kerbal::type_traits::integral_constant<int, 2>		CNSCTV_DES_VER_NO_DESTROY;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node_impl(
						NodeAllocator & alloc,
						node_base * start,
						CNSCTV_DES_VER_DEFAULT
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(k_destroy_node(alloc, kerbal::utility::declval<node_base *>()))
						)
					;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node_impl(
						NodeAllocator & alloc,
						node_base * start,
						CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::allocator_traits<NodeAllocator>::destroy(
									alloc,
									kerbal::utility::declval<typename kerbal::memory::allocator_traits<NodeAllocator>::pointer>()
								)
							)
						)
					;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node_impl(
						NodeAllocator & alloc,
						node_base * start,
						CNSCTV_DES_VER_NO_DESTROY
					) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node(
						NodeAllocator & alloc,
						node_base * start
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT()))
						)
					;

					template <typename U, typename UpstreamAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node(
						kerbal::memory::monotonic_allocator<U, UpstreamAllocator> & alloc,
						node_base * start
					);

#			if __cplusplus >= 201703L
#				if __has_include(<memory_resource>)

					template <typename Node>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node(
						std::pmr::polymorphic_allocator<Node> & alloc,
						node_base * start
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							(
								!kerbal::type_traits::try_test_is_trivially_destructible<T>::IS_TRUE::value ?
								noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE())) :
								true
							) &&
							noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT()))
						)
					;

#				endif
#			endif

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_BASE_DECL_HPP
