/**
 * @file       avl_base.decl.hpp
 * @brief
 * @date       2020-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_BASE_DECL_HPP

#include <kerbal/container/detail/avl_base/avl_base.fwd.hpp>
#include <kerbal/memory/allocator/monotonic_allocator/monotonic_allocator.fwd.hpp>

#include <kerbal/container/detail/avl_base/avl_node.hpp>
#include <kerbal/container/detail/avl_base/avl_iterator.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/container/associative_container_facility/key_compare_is_transparent.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#endif

#include <cstddef>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <kerbal/type_traits/is_trivially_destructible.hpp>
#		include <memory_resource>
#	endif
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class avl_type_unrelated
			{
				public:
					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

				protected:
					typedef kerbal::container::detail::avl_head_node			head_node;
					typedef kerbal::container::detail::avl_node_base			node_base;

				protected:
					head_node			k_head;
					size_type			k_size;

				protected:
					KERBAL_CONSTEXPR14
					avl_type_unrelated() KERBAL_NOEXCEPT :
						k_size(0u)
					{
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					avl_type_unrelated(avl_type_unrelated && src) KERBAL_NOEXCEPT :
						k_head(0),
						k_size(src.k_size)
					{
						this->k_head.left = src.k_head.left;
						set_parent_ignore_null(this->k_head.left, &this->k_head);

						src.k_head.left = get_avl_vnull_node();
						src.k_size = 0;
					}

#			endif

				public:
					KERBAL_CONSTEXPR14
					bool empty() const KERBAL_NOEXCEPT
					{
						return this->k_size == 0u;
					}

					KERBAL_CONSTEXPR14
					size_type size() const KERBAL_NOEXCEPT
					{
						return this->k_size;
					}

				protected:
					KERBAL_CONSTEXPR14
					static void k_left_rotate(node_base * g, node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static void k_right_rotate(node_base * g, node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void k_emplace_rebalance(head_node * p_head) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void k_remove_rebalance(head_node * p_head) KERBAL_NOEXCEPT;

				private:
					KERBAL_CONSTEXPR14
					node_base * k_unhook_node_and_get_successor_right_not_null(node_base * p_base) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					head_node * k_unhook_node_and_get_successor_right_null(node_base * p_base) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void k_unhook_node_right_null(node_base * p_base) KERBAL_NOEXCEPT;

				protected:
					KERBAL_CONSTEXPR14
					head_node * k_unhook_node_and_get_successor(node_base * p_base) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void k_unhook_node(node_base * p_base) KERBAL_NOEXCEPT;

				//===================
				// operation

					KERBAL_CONSTEXPR14
					static void k_swap(avl_type_unrelated & lhs, avl_type_unrelated & rhs) KERBAL_NOEXCEPT;

			};


			template <typename Entity>
			class avl_type_only : protected avl_type_unrelated
			{
				private:
					typedef avl_type_unrelated super;

					template <typename Entity2, typename Extract, typename KeyCompare, typename Allocator>
					friend struct avl_ordered_typedef_helper;

				public:
					typedef Entity						value_type;
					typedef const value_type			const_type;
					typedef value_type &				reference;
					typedef const value_type &			const_reference;
					typedef value_type *				pointer;
					typedef const value_type *			const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type &&				rvalue_reference;
					typedef const value_type &&			const_rvalue_reference;
#			endif

					typedef super::size_type					size_type;
					typedef super::difference_type				difference_type;

					typedef kerbal::container::detail::avl_iter<value_type>				iterator;
					typedef kerbal::container::detail::avl_kiter<value_type>			const_iterator;
					typedef kerbal::iterator::reverse_iterator<iterator>				reverse_iterator;
					typedef kerbal::iterator::reverse_iterator<const_iterator>			const_reverse_iterator;
					typedef kerbal::container::associative_unique_insert_r<iterator>	unique_insert_r;

				protected:
					typedef super::head_node									head_node;
					typedef super::node_base 									node_base;
					typedef kerbal::container::detail::avl_node<value_type>		node;

				public:

				//===================
				// construct/copy/destroy

#			if __cplusplus >= 201103L
					avl_type_only() = default;
#			else
					avl_type_only() KERBAL_NOEXCEPT;
#			endif


				protected:
					template <typename UnaryOperation, typename NodeAllocator>
					KERBAL_CONSTEXPR14
					void k_trans_clone(NodeAllocator & this_alloc, head_node * parent, node * src_node, bool which);

					struct identity
					{
						KERBAL_CONSTEXPR14
						static const_reference f(const_reference src) KERBAL_NOEXCEPT
						{
							return src;
						}
					};

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					void k_clone(NodeAllocator & this_alloc, head_node * parent, node * src_node);

#			if __cplusplus >= 201103L

					struct cast_to_rvalue
					{
						KERBAL_CONSTEXPR14
						static rvalue_reference f(reference src) KERBAL_NOEXCEPT
						{
							return kerbal::compatibility::move(src);
						}
					};

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					void k_move_clone(NodeAllocator & this_alloc, head_node * parent, node * src_node);

#			endif

				private:
					typedef kerbal::type_traits::integral_constant<int, 0> COPY_CNSTRCT_VER_CLONE;
					typedef kerbal::type_traits::integral_constant<int, 1> COPY_CNSTRCT_VER_INSERT;

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_copy_cnstrct_impl(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						const avl_type_only & src,
						COPY_CNSTRCT_VER_CLONE
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_copy_cnstrct_impl(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						const avl_type_only & src,
						COPY_CNSTRCT_VER_INSERT
					);

				public:
					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					avl_type_only(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						const avl_type_only & src
					);

#			if __cplusplus >= 201103L

				public:
					KERBAL_CONSTEXPR20
					avl_type_only(avl_type_only && src) KERBAL_NOEXCEPT;

				private:
					typedef kerbal::type_traits::integral_constant<int, 0> MOVE_CNSTRCT_VER_XFER;
					typedef kerbal::type_traits::integral_constant<int, 1> MOVE_CNSTRCT_VER_MOVE_CLONE;
					typedef kerbal::type_traits::integral_constant<int, 2> MOVE_CNSTRCT_VER_MOVE_INSERT;

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_impl(
						NodeAllocator & /*this_alloc*/, Extract & /*this_e*/, KeyCompare & /*this_kc*/,
						avl_type_only && src,
						MOVE_CNSTRCT_VER_XFER
					) KERBAL_NOEXCEPT;

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_impl(
						NodeAllocator & this_alloc, Extract & /*this_e*/, KeyCompare & /*this_kc*/,
						avl_type_only && src,
						MOVE_CNSTRCT_VER_MOVE_CLONE
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_impl(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						avl_type_only && src,
						MOVE_CNSTRCT_VER_MOVE_INSERT
					);

					// move construct using allocator, allocator is equal
					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_ae(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						avl_type_only && src
					) KERBAL_NOEXCEPT;

					// move construct using allocator, allocator is not equal
					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_ane(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						avl_type_only && src
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_helper(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						NodeAllocator && src_alloc, avl_type_only && src,
						kerbal::type_traits::false_type /*is_always_equal*/
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_helper(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						NodeAllocator && /*src_alloc*/, avl_type_only && src,
						kerbal::type_traits::true_type /*is_always_equal*/
					) KERBAL_NOEXCEPT;

				public:

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					avl_type_only(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						NodeAllocator && src_alloc, avl_type_only && src
					);

#			endif


					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
					KERBAL_CONSTEXPR20
					avl_type_only(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						InputIterator first, InputIterator last
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
					KERBAL_CONSTEXPR20
					avl_type_only(
						kerbal::container::unique_tag_t,
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						InputIterator first, InputIterator last
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					avl_type_only(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						std::initializer_list<value_type> ilist
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					avl_type_only(
						kerbal::container::unique_tag_t unique_tag,
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						std::initializer_list<value_type> ilist
					);

#			else

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					avl_type_only(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<void> & ilist
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
					avl_type_only(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<U> & ilist
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					avl_type_only(
						kerbal::container::unique_tag_t unique_tag,
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<void> & ilist
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
					avl_type_only(
						kerbal::container::unique_tag_t unique_tag,
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<U> & ilist
					);

#			endif


					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					void k_destroy_using_allocator(NodeAllocator & alloc) KERBAL_NOEXCEPT;


				//===================
				// assign

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> CPYASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> CPYASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> CPYASS_VER_ALWAYS_EQUAL;

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						const NodeAllocator & src_alloc, const avl_type_only & src,
						CPYASS_VER_NOT_PROPAGATE
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						const NodeAllocator & src_alloc, const avl_type_only & src,
						CPYASS_VER_PROPAGATE
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						const NodeAllocator & src_alloc, const avl_type_only & src,
						CPYASS_VER_ALWAYS_EQUAL
					);

				protected:

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						const NodeAllocator & src_alloc, const avl_type_only & src
					);

#			if __cplusplus >= 201103L

				private:

					// move assign using allocator, allocator is equal
					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ae(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						avl_type_only && src
					) KERBAL_NOEXCEPT;

					// move assign using allocator, allocator is not equal
					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ane(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						avl_type_only && src
					);

					typedef kerbal::type_traits::integral_constant<int, 0> MOVASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> MOVASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> MOVASS_VER_ALWAYS_EQUAL;

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						NodeAllocator && src_alloc, avl_type_only && src,
						MOVASS_VER_NOT_PROPAGATE
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						NodeAllocator && src_alloc, avl_type_only && src,
						MOVASS_VER_PROPAGATE
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						NodeAllocator && /*src_alloc*/, avl_type_only && src,
						MOVASS_VER_ALWAYS_EQUAL
					) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					struct is_nothrow_move_assign_using_allocator :
						kerbal::memory::allocator_traits<NodeAllocator>::is_always_equal
					{
					};

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						NodeAllocator && src_alloc, avl_type_only && src
					)
						KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_assign_using_allocator<NodeAllocator>::value)
					;

#			endif

				private:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static void k_assign_destroy_n(NodeAllocator & alloc, node_base * start, size_type size, head_node * head);

				public:

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						InputIterator first, InputIterator last
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
					KERBAL_CONSTEXPR20
					void k_assign_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						InputIterator first, InputIterator last
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						std::initializer_list<value_type> ilist
					)
					{
						this->k_assign_using_allocator(alloc, e, kc, ilist.begin(), ilist.end());
					}

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_assign_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						std::initializer_list<value_type> ilist
					)
					{
						this->k_assign_unique_using_allocator(alloc, e, kc, ilist.begin(), ilist.end());
					}

#			else

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					void k_assign_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<void> & ilist
					)
					{
						this->k_clear_using_allocator(alloc);
					}

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
					void k_assign_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<U> & ilist
					)
					{
						this->k_assign_using_allocator(alloc, e, kc, ilist.cbegin(), ilist.cend());
					}

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					void k_assign_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<void> & ilist
					)
					{
						this->k_clear_using_allocator(alloc);
					}

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
					void k_assign_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<U> & ilist
					)
					{
						this->k_assign_unique_using_allocator(alloc, e, kc, ilist.cbegin(), ilist.cend());
					}

#			endif

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
					KERBAL_CONSTEXPR20
					void k_assign_sorted_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						InputIterator first, InputIterator last
					);


				//===================
				// iterator

				public:

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
					reverse_iterator rbegin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					reverse_iterator rend() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator rend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator crend() const KERBAL_NOEXCEPT;


				//===================
				// capacity

				public:
					using super::empty;
					using super::size;


				//===================
				// lookup

				protected:

					template <
						typename Extract, typename KeyCompare, typename Key,
						typename Result
					>
					struct enable_if_transparent_lookup :
						kerbal::type_traits::enable_if<
							(
								kerbal::container::key_compare_is_transparent<KeyCompare>::value &&
								!kerbal::type_traits::is_same<const Key &, const typename Extract::key_type &>::value &&
								!kerbal::type_traits::is_same<Key, const_iterator>::value &&
								!kerbal::type_traits::is_same<Key, iterator>::value
							),
							Result
						>
					{
					};

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					const_iterator
					k_find_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					const_iterator
					k_find(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					iterator
					k_find(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						const_iterator
					>::type
					k_find(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						iterator
					>::type
					k_find(
						Extract & e, KeyCompare & kc,
						const Key & key
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					static
					const node_base *
					k_lower_bound_helper(
						Extract & e, KeyCompare & kc,
						const Key & key,
						const node_base * p_base, const node_base * lbound
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					static
					const node_base *
					k_upper_bound_helper(
						Extract & e, KeyCompare & kc, const Key & key,
						const node_base * p_base, const node_base * ubound
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					const_iterator
					k_lower_bound_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					const_iterator
					k_lower_bound(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					iterator
					k_lower_bound(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						const_iterator
					>::type
					k_lower_bound(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						iterator
					>::type
					k_lower_bound(
						Extract & e, KeyCompare & kc,
						const Key & key
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					const_iterator
					k_upper_bound_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					const_iterator
					k_upper_bound(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					iterator
					k_upper_bound(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						const_iterator
					>::type
					k_upper_bound(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						iterator
					>::type
					k_upper_bound(
						Extract & e, KeyCompare & kc,
						const Key & key
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<
						const_iterator,
						const_iterator
					>
					k_equal_range_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<
						const_iterator,
						const_iterator
					>
					k_equal_range(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<
						iterator,
						iterator
					>
					k_equal_range(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						kerbal::utility::compressed_pair<
							const_iterator,
							const_iterator
						>
					>::type
					k_equal_range(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						kerbal::utility::compressed_pair<
							iterator,
							iterator
						>
					>::type
					k_equal_range(
						Extract & e, KeyCompare & kc,
						const Key & key
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					bool k_contains_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					bool
					k_contains(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						bool
					>::type
					k_contains(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;


				//===================
				// insert

				protected:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					iterator
					k_emplace_hook_node(Extract & e, KeyCompare & kc, node * p);

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					unique_insert_r
					k_emplace_hook_node_unique(Extract & e, KeyCompare & kc, node * p);

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare
					>
					KERBAL_CONSTEXPR20
					iterator
					k_emplace_ua_aux(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						node * p
					);

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare
					>
					KERBAL_CONSTEXPR20
					unique_insert_r
					k_emplace_unique_ua_aux(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						node * p
					);

				public:

#			if __cplusplus >= 201103L

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare,
						typename ... Args
					>
					KERBAL_CONSTEXPR20
					iterator
					k_emplace_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						Args && ... args
					);

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare,
						typename ... Args
					>
					KERBAL_CONSTEXPR20
					unique_insert_r
					k_emplace_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						Args && ... args
					);

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare,
						typename ... Args
					>
					KERBAL_CONSTEXPR14
					bool
					k_emplace_unique_ua_is_delay_build(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						Args && ... args
					) KERBAL_NOEXCEPT
					{
						return false;
					}

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template < \
						typename NodeAllocator, typename Extract, typename KeyCompare \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					iterator \
					k_emplace_using_allocator( \
						NodeAllocator & alloc, Extract & e, KeyCompare & kc \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \
 \
					template < \
						typename NodeAllocator, typename Extract, typename KeyCompare \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					unique_insert_r \
					k_emplace_unique_using_allocator( \
						NodeAllocator & alloc, Extract & e, KeyCompare & kc \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \
 \
					template < \
						typename NodeAllocator, typename Extract, typename KeyCompare \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					bool \
					k_emplace_unique_ua_is_delay_build( \
						NodeAllocator & alloc, Extract & e, KeyCompare & kc \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					) KERBAL_NOEXCEPT \
					{ \
						return false; \
					} \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#			endif


					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
					KERBAL_CONSTEXPR20
					unique_insert_r
#			if __cplusplus >= 201103L
					k_emplace_unique_delay_build(NodeAllocator & alloc, Extract & e, KeyCompare & kc, U && src_key);
#			else
					k_emplace_unique_delay_build(NodeAllocator & alloc, Extract & e, KeyCompare & kc, const U & src_key);
#			endif

					template <typename NodeAllocator, typename KeyCompare>
					KERBAL_CONSTEXPR20
					unique_insert_r
					k_emplace_unique_using_allocator(
						NodeAllocator & alloc,
						kerbal::container::identity_extractor<Entity> & e,
						KeyCompare & kc,
						const_reference src_key
					);

					template <typename NodeAllocator, typename KeyCompare>
					KERBAL_CONSTEXPR14
					bool
					k_emplace_unique_ua_is_delay_build(
						NodeAllocator & alloc,
						kerbal::container::identity_extractor<Entity> & e,
						KeyCompare & kc,
						const_reference src_key
					) KERBAL_NOEXCEPT
					{
						return true;
					}

					template <typename NodeAllocator, typename KeyCompare>
					KERBAL_CONSTEXPR20
					unique_insert_r
					k_emplace_unique_using_allocator(
						NodeAllocator & alloc,
						kerbal::container::identity_extractor<Entity> & e,
						KeyCompare & kc,
						reference src_key
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename KeyCompare>
					KERBAL_CONSTEXPR20
					unique_insert_r
					k_emplace_unique_using_allocator(
						NodeAllocator & alloc,
						kerbal::container::identity_extractor<Entity> & e,
						KeyCompare & kc,
						rvalue_reference src_key
					);

					template <typename NodeAllocator, typename KeyCompare>
					KERBAL_CONSTEXPR14
					bool
					k_emplace_unique_ua_is_delay_build(
						NodeAllocator & alloc,
						kerbal::container::identity_extractor<Entity> & e,
						KeyCompare & kc,
						rvalue_reference src_key
					) KERBAL_NOEXCEPT
					{
						return true;
					}

#			endif

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					iterator
					k_insert_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const_reference src
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					unique_insert_r
					k_insert_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const_reference src
					);


#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					iterator
					k_insert_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						rvalue_reference src
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					unique_insert_r
					k_insert_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						rvalue_reference src
					);

#			endif


					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
					KERBAL_CONSTEXPR20
					void k_insert_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						InputIterator first, InputIterator last
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
					KERBAL_CONSTEXPR20
					void k_insert_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						InputIterator first, InputIterator last
					);


#			if __cplusplus >= 201103L

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_insert_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						std::initializer_list<value_type> ilist
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					void k_insert_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						std::initializer_list<value_type> ilist
					);

#			else

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					void k_insert_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<void> & ilist
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
					void k_insert_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<U> & ilist
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					void k_insert_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<void> & ilist
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
					void k_insert_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const kerbal::assign::assign_list<U> & ilist
					);

#			endif


				//===================
				// erase

				public:
					/**
					 * @param pos Make sure that pos != this->cend()
					 */
					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					iterator
					k_erase_not_end_using_allocator_unsafe(NodeAllocator & alloc, const_iterator pos) KERBAL_NOEXCEPT;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					iterator
					k_erase_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos
					) KERBAL_NOEXCEPT;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					iterator
					k_erase_using_allocator(
						NodeAllocator & alloc,
						const_iterator first, const_iterator last
					) KERBAL_NOEXCEPT;

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					size_type
					k_erase_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) KERBAL_NOEXCEPT;

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR20
					typename enable_if_transparent_lookup<Extract, KeyCompare, Key, size_type>::type
					k_erase_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const Key & key
					) KERBAL_NOEXCEPT;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void
					k_clear_using_allocator(NodeAllocator & alloc) KERBAL_NOEXCEPT;


				//===================
				// replace

				private:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					node * k_replace_reuse_node(NodeAllocator & alloc, const_iterator replace);

				public:

#			if __cplusplus >= 201103L

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare,
						typename ... Args
					>
					KERBAL_CONSTEXPR20
					iterator
					k_replace_emplace_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const_iterator replace,
						Args && ... args
					);

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare,
						typename ... Args
					>
					KERBAL_CONSTEXPR20
					unique_insert_r
					k_replace_emplace_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const_iterator replace,
						Args && ... args
					);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template < \
						typename NodeAllocator, typename Extract, typename KeyCompare \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					iterator \
					k_replace_emplace_using_allocator( \
						NodeAllocator & alloc, Extract & e, KeyCompare & kc, \
						const_iterator replace \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \
 \
					template < \
						typename NodeAllocator, typename Extract, typename KeyCompare \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					unique_insert_r \
					k_replace_emplace_unique_using_allocator( \
						NodeAllocator & alloc, Extract & e, KeyCompare & kc, \
						const_iterator replace \
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


				//===================
				// operation

					template <typename ThisExtract, typename ThisKeyCompare>
					KERBAL_CONSTEXPR20
					const_iterator
					k_splice(
						ThisExtract & this_e, ThisKeyCompare & this_kc,
						avl_type_only & other, const_iterator other_it
					);

					template <typename ThisExtract, typename ThisKeyCompare>
					KERBAL_CONSTEXPR20
					unique_insert_r
					k_splice_unique(
						ThisExtract & this_e, ThisKeyCompare & this_kc,
						avl_type_only & other, const_iterator other_it
					);

					template <typename ThisExtract, typename ThisKeyCompare>
					KERBAL_CONSTEXPR20
					void k_merge(
						ThisExtract & this_e, ThisKeyCompare & this_kc,
						avl_type_only & other, const_iterator other_begin, const_iterator other_end
					);

					template <typename ThisExtract, typename ThisKeyCompare>
					KERBAL_CONSTEXPR20
					void k_merge_unique(
						ThisExtract & this_e, ThisKeyCompare & this_kc,
						avl_type_only & other, const_iterator other_begin, const_iterator other_end
					);

					template <typename ThisExtract, typename ThisKeyCompare>
					KERBAL_CONSTEXPR20
					void k_merge(
						ThisExtract & this_e, ThisKeyCompare & this_kc,
						avl_type_only & other
					);

					template <typename ThisExtract, typename ThisKeyCompare>
					KERBAL_CONSTEXPR20
					void k_merge_unique(
						ThisExtract & this_e, ThisKeyCompare & this_kc,
						avl_type_only & other
					);

#			if __cplusplus >= 201103L

					template <typename ThisExtract, typename ThisKeyCompare>
					KERBAL_CONSTEXPR20
					void k_merge(
						ThisExtract & this_e, ThisKeyCompare & this_kc,
						avl_type_only && other
					);

					template <typename ThisExtract, typename ThisKeyCompare>
					KERBAL_CONSTEXPR20
					void k_merge_unique(
						ThisExtract & this_e, ThisKeyCompare & this_kc,
						avl_type_only && other
					);

#			endif


					template <typename F>
					KERBAL_CONSTEXPR20
					static
					void pre_order_impl(const node_base * p_base, F f);

					template <typename F>
					KERBAL_CONSTEXPR20
					void pre_order(F f) const;

				private:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					static
					avl_normal_result_t
					avl_normal_impl(
						const node_base * p,
						const value_type * & mini, const value_type * & maxi,
						node_base::height_t & depth,
						Extract & e, KeyCompare & kc
					);

				protected:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR20
					avl_normal_result_t
					avl_normal(Extract & e, KeyCompare & kc) const;

					KERBAL_CONSTEXPR20
					node_base::height_t
					height() const KERBAL_NOEXCEPT;


				//===================
				// private

				protected:

#			if __cplusplus >= 201103L

#				if KERBAL_HAS_EXCEPTIONS_SUPPORT

					template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<!nothrow_while_construct>::type
					k_try_construct_node_impl(NodeAllocator & alloc, node * p, Args && ... args);

					template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					typename kerbal::type_traits::enable_if<nothrow_while_construct>::type
					k_try_construct_node_impl(NodeAllocator & alloc, node * p, Args && ... args);

#				endif

					template <typename NodeAllocator, typename ... Args>
					KERBAL_CONSTEXPR20
					static
					void k_try_construct_node(NodeAllocator & alloc, node * p, Args && ... args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static \
					void k_try_construct_node(NodeAllocator & alloc, node * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \

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
					node *
					k_build_new_node(NodeAllocator & alloc, Args && ... args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static \
					node * \
					k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \

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
					void k_reuse_node(NodeAllocator & alloc, node * p, Args && ... args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static \
					void k_reuse_node(NodeAllocator & alloc, node * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \

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
					void k_destroy_node(NodeAllocator & alloc, node_base * p_base);

				private:
					typedef kerbal::type_traits::integral_constant<int, 0>		DES_OFF_VER_DEFAULT;
					typedef kerbal::type_traits::integral_constant<int, 1>		DES_OFF_VER_DESTROY_BUT_NO_DEALLOCATE;
					typedef kerbal::type_traits::integral_constant<int, 2>		DES_OFF_VER_NO_DESTROY;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_destroy_node_and_offsprings_impl(
						NodeAllocator & alloc, node_base * start,
						DES_OFF_VER_DEFAULT
					) KERBAL_NOEXCEPT;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_destroy_node_and_offsprings_impl(
						NodeAllocator & alloc, node_base * start,
						DES_OFF_VER_DESTROY_BUT_NO_DEALLOCATE
					) KERBAL_NOEXCEPT;

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_destroy_node_and_offsprings_impl(
						NodeAllocator & /*alloc*/, node_base * /*start*/,
						DES_OFF_VER_NO_DESTROY
					) KERBAL_NOEXCEPT;

				protected:

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_destroy_node_and_offsprings(NodeAllocator & alloc, node_base * start);

					template <typename T, typename UpstreamAllocator>
					KERBAL_CONSTEXPR20
					static
					void k_destroy_node_and_offsprings(kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & alloc, node_base * start);


#		if __cplusplus >= 201703L
#			if __has_include(<memory_resource>)

					template <typename Node>
					KERBAL_CONSTEXPR20
					static void k_destroy_node_and_offsprings(std::pmr::polymorphic_allocator<Node> & alloc, node_base * start)
						KERBAL_CONDITIONAL_NOEXCEPT(
							(
								!kerbal::type_traits::try_test_is_trivially_destructible<Entity>::IS_TRUE::value ?
								noexcept(k_destroy_node_and_offsprings_impl(alloc, start, DES_OFF_VER_DESTROY_BUT_NO_DEALLOCATE())) :
								true
							) &&
							noexcept(k_destroy_node_and_offsprings_impl(alloc, start, DES_OFF_VER_DEFAULT()))
						)
					;

#			endif
#		endif

			};


		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_BASE_DECL_HPP
