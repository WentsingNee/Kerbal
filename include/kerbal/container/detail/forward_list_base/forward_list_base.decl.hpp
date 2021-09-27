/**
 * @file       forward_list_base.decl.hpp
 * @brief
 * @date       2021-01-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_FORWARD_LIST_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_FORWARD_LIST_BASE_DECL_HPP

#include <kerbal/container/forward_list/forward_list.fwd.hpp>
#include <kerbal/memory/allocator/monotonic_allocator/monotonic_allocator.fwd.hpp>

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compare/std_compare/std_compare.fwd.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>
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
#		include <memory_resource>
#	endif
#endif

#include <kerbal/container/detail/single_list_base/single_list_node.hpp>
#include <kerbal/container/detail/forward_list_base/forward_list_iterator.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename T>
			struct is_forward_list_radix_sort_acceptable_type :
				kerbal::type_traits::bool_constant<
					kerbal::type_traits::is_integral<T>::value &&
					sizeof(T) <= 4
				>
			{
			};

			class fl_type_unrelated
			{
				private:
					template <typename T>
					friend class kerbal::container::detail::fl_type_only;

				public:
					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef kerbal::container::detail::sl_node_base					node_base;
					typedef kerbal::container::detail::fl_iter_type_unrelated		basic_iterator;
					typedef kerbal::container::detail::fl_kiter_type_unrelated		basic_const_iterator;

				protected:
					node_base k_head;

				public:
				//===================
				// construct/copy/destroy

#			if __cplusplus >= 201103L

					fl_type_unrelated() = default;

#			else

					fl_type_unrelated() KERBAL_NOEXCEPT
					{
					}

#			endif

#			if __cplusplus >= 201103L

					// pre-cond: fl_type_unrelated manage same type
					KERBAL_CONSTEXPR14
					fl_type_unrelated(fl_type_unrelated && src) KERBAL_NOEXCEPT
					{
						k_head.next = src.k_head.next;
						src.k_head.next = NULL;
					}

#			endif

				//===================
				// iterator

					KERBAL_CONSTEXPR14
					basic_iterator
					basic_before_begin() KERBAL_NOEXCEPT
					{
						return basic_iterator(&this->k_head);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator
					basic_before_begin() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(&this->k_head);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator
					basic_cbefore_begin() const KERBAL_NOEXCEPT
					{
						return this->basic_before_begin();
					}

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
						return basic_iterator(NULL);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator
					basic_end() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(NULL);
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
					void k_iter_swap_after(basic_const_iterator before_a, basic_const_iterator before_b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_reverse_after(basic_const_iterator before_first, basic_const_iterator last) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void reverse() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_splice_after(
						basic_const_iterator before_pos,
						fl_type_unrelated & other
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_splice_after(
						basic_const_iterator before_pos,
						basic_const_iterator before_opos
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_splice_after(
						basic_const_iterator before_pos,
						basic_const_iterator before_first, basic_const_iterator last
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void
					k_radix_sort_back_fill_after(
						kerbal::type_traits::false_type /*asc*/,
						kerbal::type_traits::false_type /*unsigned*/,
						basic_iterator before_insert_pos,
						fl_type_unrelated buckets[], basic_iterator bucket_backs[], std::size_t BUCKETS_NUM
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void
					k_radix_sort_back_fill_after(
						kerbal::type_traits::true_type /*desc*/,
						kerbal::type_traits::false_type /*unsigned*/,
						basic_iterator before_insert_pos,
						fl_type_unrelated buckets[], basic_iterator bucket_backs[], std::size_t BUCKETS_NUM
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void
					k_radix_sort_back_fill_after(
						kerbal::type_traits::false_type /*asc*/,
						kerbal::type_traits::true_type /*signed*/,
						basic_iterator before_insert_pos,
						fl_type_unrelated buckets[], basic_iterator bucket_backs[], std::size_t BUCKETS_NUM
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void
					k_radix_sort_back_fill_after(
						kerbal::type_traits::true_type /*desc*/,
						kerbal::type_traits::true_type /*signed*/,
						basic_iterator before_insert_pos,
						fl_type_unrelated buckets[], basic_iterator bucket_backs[], std::size_t BUCKETS_NUM
					) KERBAL_NOEXCEPT;

				//===================
				// private

					KERBAL_CONSTEXPR14
					static
					void k_hook_node_after(
						basic_const_iterator before_pos,
						node_base * p
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_hook_node_after(
						basic_const_iterator before_pos,
						node_base * start, node_base * back
					) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					node_base * k_unhook_node_after(
						basic_const_iterator before_pos
					) KERBAL_NOEXCEPT;

					// pre-cond: first != last;
					KERBAL_CONSTEXPR14
					static
					node_base * k_unhook_node_after(
						basic_const_iterator before_first, basic_const_iterator last
					) KERBAL_NOEXCEPT;

					// pre-cond: lhs and rhs are lists of same type
					KERBAL_CONSTEXPR14
					static
					void k_swap_type_unrelated(
						fl_type_unrelated & lhs,
						fl_type_unrelated & rhs
					) KERBAL_NOEXCEPT;

			};

			template <typename T>
			class fl_type_only :
				protected kerbal::container::detail::fl_type_unrelated
			{
				private:
					typedef kerbal::container::detail::fl_type_unrelated		super;
					typedef kerbal::container::detail::fl_type_unrelated		fl_type_unrelated;

				public:
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

					typedef fl_type_unrelated::size_type				size_type;
					typedef fl_type_unrelated::difference_type			difference_type;

					typedef kerbal::container::detail::fl_iter<T>		iterator;
					typedef kerbal::container::detail::fl_kiter<T>		const_iterator;

					typedef fl_type_unrelated::node_base				node_base;
					typedef kerbal::container::detail::sl_node<T>		node;


				public:

#			if __cplusplus >= 201103L

					struct is_nothrow_default_constructible :
						kerbal::type_traits::true_type
					{
					};

					fl_type_only() = default;

#			else

					fl_type_only() KERBAL_NOEXCEPT :
						fl_type_unrelated()
					{
					}

#			endif

#			if __cplusplus >= 201103L

					struct is_nothrow_move_constructible :
						kerbal::type_traits::true_type
					{
					};

					// pre-cond: allocator allows
					KERBAL_CONSTEXPR14
					fl_type_only(fl_type_only && src) KERBAL_NOEXCEPT;

				private:

					// move construct using allocator, allocator is equal
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_ae(fl_type_only && src) KERBAL_NOEXCEPT;

					// move construct using allocator, allocator is not equal
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_ane(
						NodeAllocator & this_alloc,
						fl_type_only && src
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_helper(
						NodeAllocator & this_alloc,
						NodeAllocator && src_alloc, fl_type_only && src,
						kerbal::type_traits::false_type /*is_always_equal*/
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_helper(
						NodeAllocator & this_alloc,
						NodeAllocator && src_alloc, fl_type_only && src,
						kerbal::type_traits::true_type /*is_always_equal*/
					) KERBAL_NOEXCEPT;

				public:

					template <typename NodeAllocator>
					struct is_nothrow_move_constructible_using_allocator :
						kerbal::memory::allocator_traits<NodeAllocator>::is_always_equal
					{
					};

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					fl_type_only(
						NodeAllocator & this_alloc,
						NodeAllocator && src_alloc, fl_type_only && src
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							is_nothrow_move_constructible_using_allocator<NodeAllocator>::value
						)
					;

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					fl_type_only(
						NodeAllocator & alloc,
						size_type n
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					fl_type_only(
						NodeAllocator & alloc,
						size_type n, const_reference val
					);

					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					fl_type_only(
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
						const NodeAllocator & src_alloc, const fl_type_only & src,
						CPYASS_VER_NOT_PROPAGATE
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						NodeAllocator & alloc,
						const NodeAllocator & src_alloc, const fl_type_only & src,
						CPYASS_VER_PROPAGATE
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						NodeAllocator & alloc,
						const NodeAllocator & src_alloc, const fl_type_only & src,
						CPYASS_VER_ALWAYS_EQUAL
					);

				public:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & alloc,
						const NodeAllocator & src_alloc, const fl_type_only & src
					);

#			if __cplusplus >= 201103L

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_move_assign(NodeAllocator & alloc, fl_type_only && src) KERBAL_NOEXCEPT;

				private:

					// move assign using allocator, allocator is equal
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ae(NodeAllocator & alloc, fl_type_only && src) KERBAL_NOEXCEPT;

					// move assign using allocator, allocator is not equal
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ane(NodeAllocator & alloc, fl_type_only && src);

					typedef kerbal::type_traits::integral_constant<int, 0> MOVASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> MOVASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> MOVASS_VER_ALWAYS_EQUAL;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						NodeAllocator & alloc,
						NodeAllocator && src_alloc, fl_type_only && src,
						MOVASS_VER_NOT_PROPAGATE
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						NodeAllocator & alloc,
						NodeAllocator && src_alloc, fl_type_only && src,
						MOVASS_VER_PROPAGATE
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						NodeAllocator & alloc,
						NodeAllocator && /*src_alloc*/, fl_type_only && src,
						MOVASS_VER_ALWAYS_EQUAL
					) KERBAL_NOEXCEPT;

				public:

					template <typename NodeAllocator>
					struct is_nothrow_move_assign_using_allocator :
						kerbal::memory::allocator_traits<NodeAllocator>::is_always_equal
					{
					};

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & alloc,
						NodeAllocator && src_alloc, fl_type_only && src
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

					KERBAL_CONSTEXPR14
					reference front() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reference front() const KERBAL_NOEXCEPT;

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

				//===================
				// lookup

					template <typename UnaryPredict>
					KERBAL_CONSTEXPR14
					static
					const_iterator k_find_before_if_impl(
						const_iterator before_since, const_iterator end,
						UnaryPredict predict
					);

					KERBAL_CONSTEXPR14
					static
					const_iterator k_find_before_impl(
						const_iterator before_since, const_iterator end,
						const_reference target
					);

					template <typename UnaryPredict>
					KERBAL_CONSTEXPR14
					iterator find_before_if(
						UnaryPredict predict,
						const_iterator before_since
					);

					template <typename UnaryPredict>
					KERBAL_CONSTEXPR14
					const_iterator find_before_if(
						UnaryPredict predict,
						const_iterator before_since
					) const;

					template <typename UnaryPredict>
					KERBAL_CONSTEXPR14
					iterator find_before_if(UnaryPredict predict);

					template <typename UnaryPredict>
					KERBAL_CONSTEXPR14
					const_iterator find_before_if(UnaryPredict predict) const;

					KERBAL_CONSTEXPR14
					iterator find_before(
						const_reference target,
						const_iterator before_since
					);

					KERBAL_CONSTEXPR14
					const_iterator find_before(
						const_reference target,
						const_iterator before_since
					) const;

					KERBAL_CONSTEXPR14
					iterator find_before(const_reference target);

					KERBAL_CONSTEXPR14
					const_iterator find_before(const_reference target) const;

				//===================
				// insert

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_emplace_after_using_allocator(
						NodeAllocator & alloc,
						const_iterator before_pos,
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
					k_emplace_after_using_allocator( \
						NodeAllocator & alloc, \
						const_iterator before_pos \
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
					k_insert_after_using_allocator(
						NodeAllocator & alloc,
						const_iterator before_pos,
						const_reference val
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_insert_after_using_allocator(
						NodeAllocator & alloc,
						const_iterator before_pos,
						rvalue_reference val
					);

#			endif

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_insert_after_using_allocator(
						NodeAllocator & alloc,
						const_iterator before_pos,
						size_type n, const_reference val
					);

					template <typename NodeAllocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						iterator
					>::type
					k_insert_after_using_allocator(
						NodeAllocator & alloc,
						const_iterator before_pos,
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

				//===================
				// erase

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_erase_after_using_allocator(
						NodeAllocator & alloc,
						const_iterator before_pos
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					iterator
					k_erase_after_using_allocator(
						NodeAllocator & alloc,
						const_iterator before_first, const_iterator last
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_pop_front_using_allocator(NodeAllocator & alloc);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_clear_using_allocator(NodeAllocator & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<fl_type_only>()->k_consecutive_destroy_node(
									alloc,
									kerbal::utility::declthis<fl_type_only>()->k_head.next,
									NULL
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

					KERBAL_CONSTEXPR14
					static
					void k_iter_swap_after(const_iterator before_a, const_iterator before_b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void k_reverse_after(const_iterator before_first, const_iterator last) KERBAL_NOEXCEPT;

					using fl_type_unrelated::reverse;

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> MERGE_VER_NOTHROW;

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT
					typedef kerbal::type_traits::integral_constant<int, 1> MERGE_VER_MAY_THROW;
#				endif

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					void k_merge_impl(fl_type_only & other, BinaryPredict cmp, MERGE_VER_NOTHROW) KERBAL_NOEXCEPT;

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT
					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					void k_merge_impl(fl_type_only & other, BinaryPredict cmp, MERGE_VER_MAY_THROW);
#				endif


				public:
					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					void k_merge(fl_type_only & other, BinaryPredict cmp);

					KERBAL_CONSTEXPR14
					void k_merge(fl_type_only & other);

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> MSM_VER_NOTHROW;

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT
					typedef kerbal::type_traits::integral_constant<int, 1> MSM_VER_MAY_THROW;
#				endif

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static
					const_iterator
					k_merge_sort_merge_after_impl(
						const_iterator before_first, const_iterator before_mid, const_iterator before_last,
						BinaryPredict cmp,
						MSM_VER_NOTHROW
					);

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT
					template <typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					const_iterator
					k_merge_sort_merge_after_impl(
						const_iterator before_first, const_iterator before_mid, const_iterator before_last,
						BinaryPredict cmp,
						MSM_VER_MAY_THROW
					);
#				endif

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static
					const_iterator
					k_merge_sort_merge_after(
						const_iterator before_first, const_iterator before_mid, const_iterator last,
						BinaryPredict cmp
					);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static
					const_iterator k_merge_sort_n_after(const_iterator before_first, size_type n, BinaryPredict cmp);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static
					void k_merge_sort_after(const_iterator before_first, const_iterator last, BinaryPredict cmp);


				private:

					template <std::size_t RADIX_BIT_WIDTH>
					KERBAL_CONSTEXPR14
					static
					void radix_sort_after(
						const_iterator before_first, const_iterator last, kerbal::type_traits::false_type asc,
						kerbal::type_traits::integral_constant<std::size_t, RADIX_BIT_WIDTH>
					) KERBAL_NOEXCEPT;

					template <std::size_t RADIX_BIT_WIDTH>
					KERBAL_CONSTEXPR14
					static
					void radix_sort_after(
						const_iterator before_first, const_iterator last, kerbal::type_traits::true_type desc,
						kerbal::type_traits::integral_constant<std::size_t, RADIX_BIT_WIDTH>
					) KERBAL_NOEXCEPT;

					template <typename Order>
					KERBAL_CONSTEXPR14
					static
					void radix_sort_after(const_iterator before_first, const_iterator last, Order order) KERBAL_NOEXCEPT;

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					radix_sort_after(const_iterator before_first, const_iterator last) KERBAL_NOEXCEPT;


				private:

					template <bool is_radix_sort_acceptable_type, typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						BinaryPredict cmp
					);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						kerbal::compare::less<value_type> cmp
					);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						kerbal::compare::greater<value_type> cmp
					);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						kerbal::compare::less<void> cmp
					);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						kerbal::compare::greater<void> cmp
					);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						std::less<value_type> cmp
					);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						std::greater<value_type> cmp
					);

#			if __cplusplus >= 201402L

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						std::less<void> cmp
					);

					template <bool is_radix_sort_acceptable_type>
					KERBAL_CONSTEXPR14
					static
					typename kerbal::type_traits::enable_if<is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						std::greater<void> cmp
					);

#			endif

					template <bool is_radix_sort_acceptable_type, typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<!is_radix_sort_acceptable_type>::type
					sort_after_method_overload(
						const_iterator before_first, const_iterator last,
						BinaryPredict cmp
					);

				public:

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					static
					void k_sort_after(const_iterator before_first, const_iterator last, BinaryPredict cmp);

					KERBAL_CONSTEXPR14
					static
					void k_sort_after(const_iterator before_first, const_iterator last);

					template <typename BinaryPredict>
					KERBAL_CONSTEXPR14
					void k_sort(BinaryPredict cmp);

					KERBAL_CONSTEXPR14
					void k_sort();

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

				public:

					template <typename NodeAllocator, typename UnaryPredicate>
					KERBAL_CONSTEXPR20
					static
					size_type
					k_remove_after_if_using_allocator(
						NodeAllocator & alloc,
						const_iterator before_first, const_iterator last,
						UnaryPredicate predicate
					);

					template <typename NodeAllocator, typename UnaryPredicate>
					KERBAL_CONSTEXPR20
					size_type
					k_remove_if_using_allocator(
						NodeAllocator & alloc,
						UnaryPredicate predicate
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					size_type
					k_remove_after_using_allocator(
						NodeAllocator & alloc,
						const_iterator before_first, const_iterator last,
						const_reference val
					);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					size_type
					k_remove_using_allocator(
						NodeAllocator & alloc,
						const_reference val
					);

					template <typename NodeAllocator, typename BinaryPredict>
					KERBAL_CONSTEXPR20
					static
					size_type
					k_unique_using_allocator(
						NodeAllocator & alloc,
						const_iterator first, const_iterator last,
						BinaryPredict equal_to
					);

					template <typename NodeAllocator, typename BinaryPredict>
					KERBAL_CONSTEXPR20
					size_type
					k_unique_using_allocator(
						NodeAllocator & alloc,
						BinaryPredict equal_to
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


				//===================
				// private

				protected:

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
					sl_node_chain<T>
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
					sl_node_chain<T> \
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
						sl_node_chain<T>
					>::type
					k_build_new_nodes_range_unguarded(NodeAllocator & alloc, InputIterator first, InputIterator last);

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_destroy_node(NodeAllocator & alloc, node_base * p_node_base) KERBAL_NOEXCEPT;

				private:
					typedef kerbal::type_traits::integral_constant<int, 0>		CNSCTV_DES_VER_DEFAULT;
					typedef kerbal::type_traits::integral_constant<int, 1>		CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE;
					typedef kerbal::type_traits::integral_constant<int, 2>		CNSCTV_DES_VER_NO_DESTROY;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node_impl(
						NodeAllocator & alloc,
						node_base * first, node_base * last,
						CNSCTV_DES_VER_DEFAULT
					) KERBAL_NOEXCEPT;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node_impl(
						NodeAllocator & alloc,
						node_base * first, node_base * last,
						CNSCTV_DES_VER_DESTROY_BUT_NO_DEALLOCATE
					) KERBAL_NOEXCEPT;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node_impl(
						NodeAllocator & alloc,
						node_base * first, node_base * last,
						CNSCTV_DES_VER_NO_DESTROY
					) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node(
						NodeAllocator & alloc,
						node_base * first, node_base * last
					) KERBAL_NOEXCEPT;

					template <typename U, typename UpstreamAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node(
						kerbal::memory::monotonic_allocator<U, UpstreamAllocator> & alloc,
						node_base * first, node_base * last
					) KERBAL_NOEXCEPT;

#			if __cplusplus >= 201703L
#				if __has_include(<memory_resource>)

					template <typename Node>
					KERBAL_CONSTEXPR20
					static
					void k_consecutive_destroy_node(
						std::pmr::polymorphic_allocator<Node> & alloc,
						node_base * first, node_base * last
					) KERBAL_NOEXCEPT;

#				endif
#			endif

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_FORWARD_LIST_BASE_DECL_HPP
