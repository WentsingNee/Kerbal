/**
 * @file       single_list_base.decl.hpp
 * @brief
 * @date       2020-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_BASE_DECL_HPP

#include <kerbal/container/single_list/single_list.fwd.hpp>

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/declval.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <cstddef>

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <kerbal/type_traits/is_trivially_destructible.hpp>
#		include <kerbal/type_traits/tribool_constant.hpp>
#		include <memory_resource>
#	endif
#endif

#include <kerbal/container/detail/single_list_base/single_list_node.hpp>
#include <kerbal/container/detail/single_list_base/single_list_iterator.hpp>


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

				//===================
				// construct/copy/destroy

					KERBAL_CONSTEXPR14
					sl_type_unrelated() KERBAL_NOEXCEPT
							: head_node(), last_iter(this->basic_begin())
					{
					}

				//===================
				// iterator

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
				// capacity

					KERBAL_CONSTEXPR20
					bool empty() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					size_type size() const KERBAL_NOEXCEPT;

				//===================
				// operation

					KERBAL_CONSTEXPR20
					void k_iter_swap(basic_iterator a, basic_iterator b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void k_reverse(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void reverse() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void k_splice(basic_const_iterator pos, sl_type_unrelated & other) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void k_splice(basic_const_iterator pos, sl_type_unrelated & other, basic_const_iterator opos) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void k_splice(basic_const_iterator pos, sl_type_unrelated & other,
								basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT;

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					void k_splice(basic_const_iterator pos, sl_type_unrelated && other) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void k_splice(basic_const_iterator pos, sl_type_unrelated && other, basic_const_iterator opos) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void k_splice(basic_const_iterator pos, sl_type_unrelated && other,
								basic_const_iterator first, basic_const_iterator last) KERBAL_NOEXCEPT;

#			endif

				//===================
				// private

					KERBAL_CONSTEXPR14
					void k_init_node_base() KERBAL_NOEXCEPT
					{
						this->head_node.next = NULL;
						this->last_iter = this->basic_begin();
					}

					// pre-cond: p->next == NULL;
					KERBAL_CONSTEXPR20
					void k_hook_node_back(node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					static void k_hook_node_not_back(basic_iterator pos, node_base * p) KERBAL_NOEXCEPT;

					// pre-cond: if pos == cend then p->next == NULL;
					KERBAL_CONSTEXPR20
					void k_hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT;

					// pre-cond: back->next == NULL;
					KERBAL_CONSTEXPR20
					void k_hook_node_back(node_base * start, node_base * back) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					static void k_hook_node_not_back(basic_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT;

					// pre-cond: if pos == cend then back->next == NULL;
					KERBAL_CONSTEXPR20
					void k_hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					node_base * k_unhook_node(basic_iterator pos) KERBAL_NOEXCEPT;

					// pre-cond: first != last;
					KERBAL_CONSTEXPR20
					sl_node_base_chain
					k_unhook_node(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT;

					// pre-cond: lhs and rhs are lists of same type
					KERBAL_CONSTEXPR20
					static void k_swap_with_empty(sl_type_unrelated & not_empty_list, sl_type_unrelated & empty_list) KERBAL_NOEXCEPT;

					// pre-cond: lhs and rhs are lists of same type
					KERBAL_CONSTEXPR20
					static void k_swap_type_unrelated(sl_type_unrelated & lhs, sl_type_unrelated & rhs) KERBAL_NOEXCEPT;

			};

			template <typename Tp>
			class sl_allocator_unrelated:
					protected kerbal::container::detail::sl_type_unrelated
			{
				private:
					typedef kerbal::container::detail::sl_type_unrelated		super;
					typedef kerbal::container::detail::sl_type_unrelated		sl_type_unrelated;

					template <typename Up, typename Allocator>
					friend struct sl_typedef_helper;

					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

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

				//===================
				// construct/copy/destroy

#			if __cplusplus >= 201103L

					struct is_nothrow_default_constructible : kerbal::type_traits::true_type
					{
					};

					sl_allocator_unrelated() = default;

#			else

					sl_allocator_unrelated() KERBAL_NOEXCEPT :
							super()
					{
					}

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					sl_allocator_unrelated(NodeAllocator & alloc, size_type n);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					sl_allocator_unrelated(NodeAllocator & alloc, size_type n, const_reference val);

					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					sl_allocator_unrelated(NodeAllocator & alloc, InputIterator first, InputIterator last,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
									, int
							>::type = 0
					);

#			if __cplusplus >= 201103L

					struct is_nothrow_move_constructible : kerbal::type_traits::true_type
					{
					};

					// pre-cond: allocator allows
					KERBAL_CONSTEXPR14
					sl_allocator_unrelated(sl_allocator_unrelated && src) KERBAL_NOEXCEPT;

				private:

					// move construct using allocator, allocator is equal
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_ae(sl_allocator_unrelated && src) KERBAL_NOEXCEPT;

					// move construct using allocator, allocator is not equal
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_ane(NodeAllocator & this_alloc, sl_allocator_unrelated && src);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_helper(NodeAllocator & this_alloc, NodeAllocator && src_alloc, sl_allocator_unrelated && src,
												   kerbal::type_traits::false_type /*is_always_equal*/);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_helper(NodeAllocator & this_alloc, NodeAllocator && src_alloc, sl_allocator_unrelated && src,
												   kerbal::type_traits::true_type /*is_always_equal*/) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					struct is_nothrow_move_constructible_using_allocator :
							kerbal::memory::allocator_traits<NodeAllocator>::is_always_equal
					{
					};

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					sl_allocator_unrelated(NodeAllocator & this_alloc, NodeAllocator && src_alloc, sl_allocator_unrelated && src)
							KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_constructible_using_allocator<NodeAllocator>::value)
					;

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void destroy_using_allocator(NodeAllocator & alloc) KERBAL_NOEXCEPT;


				//===================
				// assign

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void assign_using_allocator(NodeAllocator & alloc, size_type count, const_reference val);

					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign_using_allocator(NodeAllocator & alloc, InputIterator first, InputIterator last);

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> CPYASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> CPYASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> CPYASS_VER_ALWAYS_EQUAL;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & src_alloc, const sl_allocator_unrelated & src, CPYASS_VER_NOT_PROPAGATE);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & src_alloc, const sl_allocator_unrelated & src, CPYASS_VER_PROPAGATE);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(NodeAllocator & alloc, const NodeAllocator & src_alloc, const sl_allocator_unrelated & src, CPYASS_VER_ALWAYS_EQUAL);

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void assign_using_allocator(NodeAllocator & alloc, const NodeAllocator & src_alloc, const sl_allocator_unrelated & src);

#			if __cplusplus >= 201103L

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_move_assign(NodeAllocator & alloc, sl_allocator_unrelated && src) KERBAL_NOEXCEPT;

				private:

					// move assign using allocator, allocator is equal
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ae(NodeAllocator & alloc, sl_allocator_unrelated && src) KERBAL_NOEXCEPT;

					// move assign using allocator, allocator is not equal
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ane(NodeAllocator & alloc, sl_allocator_unrelated && src);

					typedef kerbal::type_traits::integral_constant<int, 0> MOVASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> MOVASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> MOVASS_VER_ALWAYS_EQUAL;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && src_alloc, sl_allocator_unrelated && src, MOVASS_VER_NOT_PROPAGATE);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && src_alloc, sl_allocator_unrelated && src, MOVASS_VER_PROPAGATE);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(NodeAllocator & alloc, NodeAllocator && /*src_alloc*/, sl_allocator_unrelated && src, MOVASS_VER_ALWAYS_EQUAL) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					struct is_nothrow_move_assign_using_allocator :
							kerbal::memory::allocator_traits<NodeAllocator>::is_always_equal
					{
					};

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void assign_using_allocator(NodeAllocator & alloc, NodeAllocator && src_alloc, sl_allocator_unrelated && src)
							KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_assign_using_allocator<NodeAllocator>::value)
					;

#			endif


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
				// capacity

					using sl_type_unrelated::empty;
					using sl_type_unrelated::size;

				//===================
				// insert

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void push_front_using_allocator(NodeAllocator & alloc, const_reference val);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void push_front_using_allocator(NodeAllocator & alloc, rvalue_reference val);

#			endif

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					reference emplace_front_using_allocator(NodeAllocator & alloc, Args&& ... args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					reference emplace_front_using_allocator(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

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
					void push_back_using_allocator(NodeAllocator & alloc, const_reference val);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void push_back_using_allocator(NodeAllocator & alloc, rvalue_reference val);

#			endif

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					reference emplace_back_using_allocator(NodeAllocator & alloc, Args&& ... args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					reference emplace_back_using_allocator(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

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
					iterator insert_using_allocator(NodeAllocator & alloc, const_iterator pos, const_reference val);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					iterator insert_using_allocator(NodeAllocator & alloc, const_iterator pos, size_type n, const_reference val);

					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							iterator
					>::type
					insert_using_allocator(NodeAllocator & alloc, const_iterator pos, InputIterator first, InputIterator last);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					iterator insert_using_allocator(NodeAllocator & alloc, const_iterator pos, rvalue_reference val);

#			endif

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					iterator emplace_using_allocator(NodeAllocator & alloc, const_iterator pos, Args&& ... args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					iterator emplace_using_allocator(NodeAllocator & alloc, const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#			endif

				//===================
				// erase

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void pop_front_using_allocator(NodeAllocator & alloc);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					iterator erase_using_allocator(NodeAllocator & alloc, const_iterator pos);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					iterator erase_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void clear_using_allocator(NodeAllocator & alloc)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::utility::declthis<sl_allocator_unrelated>()->k_consecutive_destroy_node(
											alloc,
											kerbal::utility::declthis<sl_allocator_unrelated>()->head_node.next
									))
							)
					;

				//===================
				// operation

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void resize_using_allocator(NodeAllocator & alloc, size_type count);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void resize_using_allocator(NodeAllocator & alloc, size_type count, const_reference value);

					KERBAL_CONSTEXPR20
					void iter_swap(iterator a, iterator b) KERBAL_NOEXCEPT;

					using sl_type_unrelated::reverse;

					KERBAL_CONSTEXPR20
					void reverse(iterator first, iterator last) KERBAL_NOEXCEPT;

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
											noexcept(kerbal::compare::equal_to<value_type>()(val, with))
									)
							{
								return kerbal::compare::equal_to<value_type>()(val, with);
							}
					};

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					size_type remove_using_allocator(NodeAllocator & alloc, const_reference val);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					size_type remove_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, const_reference val);

					template <typename NodeAllocator, typename UnaryPredicate>
					KERBAL_CONSTEXPR20
					size_type remove_if_using_allocator(NodeAllocator & alloc, UnaryPredicate predicate);

					template <typename NodeAllocator, typename UnaryPredicate>
					KERBAL_CONSTEXPR20
					size_type remove_if_using_allocator(NodeAllocator & alloc, const_iterator first, const_iterator last, UnaryPredicate predicate);


				//===================
				// private

#			if __cplusplus >= 201103L

#				if __cpp_exceptions

					template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<!nothrow_while_construct, node*>::type
					k_build_new_node_impl(NodeAllocator & alloc, Args&& ... args);

					template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<nothrow_while_construct, node*>::type
					k_build_new_node_impl(NodeAllocator & alloc, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::memory::allocator_traits<NodeAllocator>::allocate(alloc, 1))
							)
					;

#				endif

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static node* k_build_new_node(NodeAllocator & alloc, Args&& ... args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static node* k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

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
					sl_node_chain<Tp> k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n, Args&& ...args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static \
					sl_node_chain<Tp> k_build_n_new_nodes_unguarded(NodeAllocator & alloc, size_type n KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

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
							sl_node_chain<Tp>
					>::type
					k_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void k_destroy_node(NodeAllocator & alloc, node_base * p_node_base)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::memory::allocator_traits<NodeAllocator>::destroy(alloc, kerbal::utility::declval<node*>())) &&
								noexcept(kerbal::memory::allocator_traits<NodeAllocator>::deallocate(alloc, kerbal::utility::declval<node*>(), 1))
							)
					;

				private:
					typedef kerbal::type_traits::integral_constant<int, 0>		CNSCTV_DES_VER_DEFAULT;
					typedef kerbal::type_traits::integral_constant<int, 1>		CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE;
					typedef kerbal::type_traits::integral_constant<int, 2>		CNSCTV_DES_VER_NO_DEALLOCATE;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void k_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * start, CNSCTV_DES_VER_DEFAULT)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::utility::declthis<sl_allocator_unrelated>()->k_destroy_node(alloc, kerbal::utility::declval<node_base *>()))
							)
					;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void k_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * start, CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::memory::allocator_traits<NodeAllocator>::destroy(alloc, kerbal::utility::declval<node*>()))
							)
					;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void k_consecutive_destroy_node_impl(NodeAllocator & alloc, node_base * start, CNSCTV_DES_VER_NO_DEALLOCATE) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void k_consecutive_destroy_node(NodeAllocator & alloc, node_base * start)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(k_consecutive_destroy_node_impl(alloc, start, CNSCTV_DES_VER_DEFAULT()))
							)
					;

#			if __cplusplus >= 201703L
#				if __has_include(<memory_resource>)

					template <typename Node>
					KERBAL_CONSTEXPR20
					static void k_consecutive_destroy_node(std::pmr::polymorphic_allocator<Node> & alloc, node_base * start)
							KERBAL_CONDITIONAL_NOEXCEPT(
								(
									!kerbal::type_traits::tribool_is_true<kerbal::type_traits::try_test_is_trivially_destructible<Tp> >::value ?
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

#endif // KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_BASE_DECL_HPP
