/**
 * @file       avl_base.impl.hpp
 * @brief
 * @date       2020-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_BASE_IMPL_HPP

#include <kerbal/container/detail/avl_base/avl_base.decl.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/minmax.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_function.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>
#include <kerbal/utility/compressed_pair.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/iterator/move_iterator.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if !KERBAL_HAS_EXCEPTIONS_SUPPORT
#	include <kerbal/memory/bad_alloc.hpp>
#	include <kerbal/utility/throw_this_exception.hpp>
#endif

#include <typeinfo>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <kerbal/type_traits/is_trivially_destructible.hpp>
#		include <memory_resource>
#	endif
#endif

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			KERBAL_CONSTEXPR14
			inline
			void
			avl_type_unrelated::
			k_left_rotate(node_base * g, node_base * p) KERBAL_NOEXCEPT
			{
				/*
						 a
						 |
						 g                         a
						  \                        |
						   p                       p
						 /   \                   /   \
					  [l]     [r]               g     [r]
												 \
												  [l]
				 */

				node_base * l = p->left;

				g->right = l;
				set_parent_ignore_null(l, g);

				p->left = g;
				g->parent = p;
			}

			KERBAL_CONSTEXPR14
			inline
			void
			avl_type_unrelated::
			k_right_rotate(node_base * g, node_base * p) KERBAL_NOEXCEPT
			{
				/*
							 a
							 |
							 g                     a
							/                      |
						   p                       p
						 /   \                   /   \
					  [l]     [r]             [l]     g
													 /
												  [r]
				 */

				node_base * r = p->right;

				g->left = r;
				set_parent_ignore_null(r, g);

				p->right = g;
				g->parent = p;
			}

			KERBAL_CONSTEXPR14
			inline
			void
			avl_type_unrelated::
			k_emplace_rebalance(head_node * p_head) KERBAL_NOEXCEPT
			{
				while (p_head != &this->k_head) {
					node_base * p_base = p_head->as_node_base();
					node_base::height_t height_of_left = node_base::height_of(p_base->left);
					node_base::height_t height_of_right = node_base::height_of(p_base->right);
					node_base::height_t new_height = 1 + kerbal::compare::max(height_of_left, height_of_right);
					if (p_base->height == new_height) {
						break;
					}
					p_base->height = new_height;

					node_base * p = NULL;
					if (height_of_left > height_of_right + 1) { // bfactor > +1
						node_base * & left = p;
						left = p_base->left;
						if (node_base::height_of(left->left) < node_base::height_of(left->right)) {
							node_base * new_left = left->right;
							k_left_rotate(left, new_left);
							p_base->left = new_left;
							new_left->parent = p_base;
							left->update_height();
							left = new_left;
						}
						p_head = p_base->parent;
						k_right_rotate(p_base, left);
					} else if (height_of_right > height_of_left + 1) { // bfactor < -1
						node_base * & right = p;
						right = p_base->right;
						if (node_base::height_of(right->left) > node_base::height_of(right->right)) {
							node_base * new_right = right->left;
							k_right_rotate(right, new_right);
							p_base->right = new_right;
							new_right->parent = p_base;
							right->update_height();
							right = new_right;
						}
						p_head = p_base->parent;
						k_left_rotate(p_base, right);
					} else {
						p_head = p_base->parent;
						continue;
					}
					if (p_head->left == p_base) {
						p_head->left = p;
					} else {
						p_head->as_node_base()->right = p;
					}
					p->parent = p_head;
					p_base->update_height();
					p->update_height(p->left->height, p->right->height); // <=> p->update_height(); p's sons both not NULL
					break;
				}
			}

			KERBAL_CONSTEXPR14
			inline
			void
			avl_type_unrelated::
			k_remove_rebalance(head_node * p_head) KERBAL_NOEXCEPT
			{
				bool not_reach_head = p_head != &this->k_head;
				while (not_reach_head) {
					node_base * p_base = p_head->as_node_base();
					node_base::height_t height_of_left = node_base::height_of(p_base->left);
					node_base::height_t height_of_right = node_base::height_of(p_base->right);
					p_base->update_height(height_of_left, height_of_right);

					node_base * p = NULL;
					if (height_of_left > height_of_right + 1) { // bfactor > +1
						node_base * & left = p;
						left = p_base->left;
						if (node_base::height_of(left->left) < node_base::height_of(left->right)) {
							node_base * new_left = left->right;
							k_left_rotate(left, new_left);
							p_base->left = new_left;
							new_left->parent = p_base;
							left->update_height();
							left = new_left;
						}
						p_head = p_base->parent;
						k_right_rotate(p_base, left);
					} else if (height_of_right > height_of_left + 1) { // bfactor < -1
						node_base * & right = p;
						right = p_base->right;
						if (node_base::height_of(right->left) > node_base::height_of(right->right)) {
							node_base * new_right = right->left;
							k_right_rotate(right, new_right);
							p_base->right = new_right;
							new_right->parent = p_base;
							right->update_height();
							right = new_right;
						}
						p_head = p_base->parent;
						k_left_rotate(p_base, right);
					} else {
						p_head = p_base->parent;
						not_reach_head = p_head != &this->k_head;
						continue;
					}
					if (p_head->left == p_base) {
						p_head->left = p;
						not_reach_head = p_head != &this->k_head;
					} else {
						p_head->as_node_base()->right = p;
						not_reach_head = true;
					}
					p->parent = p_head;
					p_base->update_height();
					p->update_height(p->left->height, p->right->height); // <=> p->update_height(); p's sons both not NULL
				}
			}

			KERBAL_CONSTEXPR14
			inline
			avl_type_unrelated::node_base *
			avl_type_unrelated::
			k_unhook_node_and_get_successor_right_not_null(node_base * p_base) KERBAL_NOEXCEPT
			{
				node_base * replacer = p_base->right;
				head_node * parent = p_base->parent;
				head_node * start = replacer;
				if (replacer->left != get_avl_vnull_node()) {
					head_node * replacer_parent = p_base;
					do {
						replacer_parent = replacer;
						replacer = replacer->left;
					} while (replacer->left != get_avl_vnull_node());

					start = replacer_parent;
					set_parent_ignore_null(replacer->right, replacer_parent);
					replacer_parent->left = replacer->right;

					// adjust right
					replacer->right = p_base->right;
					p_base->right->parent = replacer;
				}

				// adjust parent
				replacer->parent = parent;
				if (p_base == parent->left) {
					parent->left = replacer;
				} else {
					parent->as_node_base()->right = replacer;
				}

				// adjust left
				replacer->left = p_base->left;
				set_parent_ignore_null(p_base->left, replacer);

				k_remove_rebalance(start);
				return replacer;
			}

			KERBAL_CONSTEXPR14
			inline
			avl_type_unrelated::head_node *
			avl_type_unrelated::
			k_unhook_node_and_get_successor_right_null(node_base * p_base) KERBAL_NOEXCEPT
			{
				node_base * replacer = p_base->left;
				head_node * parent = p_base->parent;
				head_node * successor = parent;
				set_parent_ignore_null(replacer, parent);

				if (p_base == parent->left) {
					parent->left = replacer;
				} else {
					parent->as_node_base()->right = replacer;
					bool at_left = false;
					do {
						head_node * g = successor->as_node_base()->parent;
						at_left = (successor == g->left);
						successor = g;
					} while (!at_left);
				}
				k_remove_rebalance(parent);
				return successor;
			}

			KERBAL_CONSTEXPR14
			inline
			void
			avl_type_unrelated::
			k_unhook_node_right_null(node_base * p_base) KERBAL_NOEXCEPT
			{
				node_base * replacer = p_base->left;
				head_node * parent = p_base->parent;
				set_parent_ignore_null(replacer, parent);

				if (p_base == parent->left) {
					parent->left = replacer;
				} else {
					parent->as_node_base()->right = replacer;
				}
				k_remove_rebalance(parent);
			}

			KERBAL_CONSTEXPR14
			inline
			avl_type_unrelated::head_node *
			avl_type_unrelated::
			k_unhook_node_and_get_successor(node_base * p_base) KERBAL_NOEXCEPT
			{
				head_node * p_next = NULL;
				if (p_base->right != get_avl_vnull_node()) {
					p_next = this->k_unhook_node_and_get_successor_right_not_null(p_base);
				} else {
					p_next = this->k_unhook_node_and_get_successor_right_null(p_base);
				}
				--this->k_size;
				return p_next;
			}

			KERBAL_CONSTEXPR14
			inline
			void
			avl_type_unrelated::
			k_unhook_node(node_base * p_base) KERBAL_NOEXCEPT
			{
				if (p_base->right != get_avl_vnull_node()) {
					this->k_unhook_node_and_get_successor_right_not_null(p_base);
				} else {
					this->k_unhook_node_right_null(p_base);
				}
				--this->k_size;
			}


			template <typename Extract, typename KeyCompare>
			struct avl_stateless_comparable:
				kerbal::type_traits::tribool_conjunction<
					typename kerbal::type_traits::tribool_disjunction<
						kerbal::type_traits::try_test_is_empty<Extract>,
						kerbal::type_traits::is_function<Extract>
					>::result,
					typename kerbal::type_traits::tribool_disjunction<
						kerbal::type_traits::try_test_is_empty<KeyCompare>,
						kerbal::type_traits::is_function<KeyCompare>
					>::result
				>::result::IS_TRUE
			{
			};


		//===================
		// operation

			KERBAL_CONSTEXPR14
			inline
			void
			avl_type_unrelated::
			k_swap(avl_type_unrelated & lhs, avl_type_unrelated & rhs) KERBAL_NOEXCEPT
			{
				kerbal::algorithm::swap(lhs.k_head.left, rhs.k_head.left);
				set_parent_ignore_null(lhs.k_head.left, &lhs.k_head);
				set_parent_ignore_null(rhs.k_head.left, &rhs.k_head);
				kerbal::algorithm::swap(lhs.k_size, rhs.k_size);
			}



		//===================
		// construct/copy/destroy

#	if __cplusplus < 201103L

			template <typename Entity>
			avl_type_only<Entity>::
			avl_type_only() KERBAL_NOEXCEPT
			{
			}

#	endif


			template <typename Entity>
			template <typename UnaryOperation, typename NodeAllocator>
			KERBAL_CONSTEXPR14
			void
			avl_type_only<Entity>::
			k_trans_clone(NodeAllocator & this_alloc, head_node * parent, node * src_node, bool which)
			{
				while (src_node != get_avl_vnull_node()) {
					node * pnew = k_build_new_node(this_alloc, UnaryOperation::f(src_node->member()));
					if (!which) {
						parent->left = pnew;
					} else {
						parent->as_node_base()->right = pnew;
					}
					pnew->parent = parent;
					pnew->height = src_node->height;
					k_trans_clone<UnaryOperation>(this_alloc, pnew, node::reinterpret_as(src_node->right), true);

					parent = pnew;
					src_node = node::reinterpret_as(src_node->left);
					which = false;
				}
			}

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR14
			void
			avl_type_only<Entity>::
			k_clone(NodeAllocator & this_alloc, head_node * parent, node * src_node)
			{
				this->k_trans_clone<identity>(this_alloc, parent, src_node, false);
			}

#		if __cplusplus >= 201103L

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR14
			void
			avl_type_only<Entity>::
			k_move_clone(NodeAllocator & this_alloc, head_node * parent, node * src_node)
			{
				this->k_trans_clone<cast_to_rvalue>(this_alloc, parent, src_node, false);
			}

#		endif

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_copy_cnstrct_impl(
				NodeAllocator & this_alloc, Extract & /*this_e*/, KeyCompare & /*this_kc*/,
				const avl_type_only & src,
				COPY_CNSTRCT_VER_CLONE
			)
			{
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#	endif
					this->k_clone(this_alloc, &this->k_head, node::reinterpret_as(src.k_head.left));
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					this->k_destroy_using_allocator(this_alloc);
					throw;
				}
#	endif

				this->k_size = src.k_size;
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_copy_cnstrct_impl(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				const avl_type_only & src,
				COPY_CNSTRCT_VER_INSERT
			)
			{
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#	endif
					this->k_insert_using_allocator(this_alloc, this_e, this_kc, src.cbegin(), src.cend());
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					this->k_destroy_using_allocator(this_alloc);
					throw;
				}
#	endif
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			avl_type_only<Entity>::
			avl_type_only(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				const avl_type_only & src
			)
			{
//				typedef typename kerbal::type_traits::conditional<
//					avl_stateless_comparable<Extract, KeyCompare>::value,
//					COPY_CNSTRCT_VER_CLONE,
//					COPY_CNSTRCT_VER_INSERT
//				>::type VER;

				typedef COPY_CNSTRCT_VER_CLONE VER;

				this->k_copy_cnstrct_impl(
					this_alloc, this_e, this_kc,
					src,
					VER()
				);
			}


#		if __cplusplus >= 201103L

			template <typename Entity>
			KERBAL_CONSTEXPR20
			avl_type_only<Entity>::avl_type_only(avl_type_only && src) KERBAL_NOEXCEPT :
				avl_type_unrelated(static_cast<avl_type_unrelated &&>(src))
			{
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_move_cnstrct_impl(
				NodeAllocator & /*this_alloc*/, Extract & /*this_e*/, KeyCompare & /*this_kc*/,
				avl_type_only && src,
				MOVE_CNSTRCT_VER_XFER
			) KERBAL_NOEXCEPT
			{
				this->k_head.left = src.k_head.left;
				set_parent_ignore_null(this->k_head.left, &this->k_head);

				src.k_head.left = get_avl_vnull_node();
				this->k_size = src.k_size;
				src.k_size = 0;
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_move_cnstrct_impl(
				NodeAllocator & this_alloc, Extract & /*this_e*/, KeyCompare & /*this_kc*/,
				avl_type_only && src,
				MOVE_CNSTRCT_VER_MOVE_CLONE
			)
			{
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#	endif
					this->k_move_clone(this_alloc, &this->k_head, node::reinterpret_as(src.k_head.left));
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					this->k_destroy_using_allocator(this_alloc);
					throw;
				}
#	endif

				this->k_size = src.k_size;
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_move_cnstrct_impl(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				avl_type_only && src,
				MOVE_CNSTRCT_VER_MOVE_INSERT
			)
			{
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#	endif
					this->k_insert_using_allocator(
						this_alloc, this_e, this_kc,
						kerbal::iterator::make_move_iterator(src.begin()),
						kerbal::iterator::make_move_iterator(src.end())
					);
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					this->k_destroy_using_allocator(this_alloc);
					throw;
				}
#	endif
			}

			// move construct using allocator, allocator is equal
			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			void
			avl_type_only<Entity>::
			k_move_cnstrct_ua_ae(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				avl_type_only && src
			) KERBAL_NOEXCEPT
			{
//				typedef typename kerbal::type_traits::conditional<
//					avl_stateless_comparable<Extract, KeyCompare>::value,
//					MOVE_CNSTRCT_VER_XFER,
//					MOVE_CNSTRCT_VER_MOVE_INSERT
//				>::type VER;

				typedef MOVE_CNSTRCT_VER_XFER VER;

				this->k_move_cnstrct_impl(
					this_alloc, this_e, this_kc,
					kerbal::compatibility::move(src),
					VER()
				);
			}

			// move construct using allocator, allocator is not equal
			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_move_cnstrct_ua_ane(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				avl_type_only && src
			)
			{
//				typedef typename kerbal::type_traits::conditional<
//					avl_stateless_comparable<Extract, KeyCompare>::value,
//					MOVE_CNSTRCT_VER_MOVE_CLONE,
//					MOVE_CNSTRCT_VER_MOVE_INSERT
//				>::type VER;

				typedef MOVE_CNSTRCT_VER_MOVE_CLONE VER;

				this->k_move_cnstrct_impl(
					this_alloc, this_e, this_kc,
					kerbal::compatibility::move(src),
					VER()
				);
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_move_cnstrct_ua_helper(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				NodeAllocator && src_alloc, avl_type_only && src,
				kerbal::type_traits::false_type /*is_always_equal*/
			)
			{
				if (this_alloc != src_alloc) {
					this->k_move_cnstrct_ua_ane(
						this_alloc, this_e, this_kc,
						kerbal::compatibility::move(src)
					);
				} else {
					this->k_move_cnstrct_ua_ae(
						this_alloc, this_e, this_kc,
						kerbal::compatibility::move(src)
					);
				}
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			void
			avl_type_only<Entity>::
			k_move_cnstrct_ua_helper(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				NodeAllocator && /*src_alloc*/, avl_type_only && src,
				kerbal::type_traits::true_type /*is_always_equal*/
			) KERBAL_NOEXCEPT
			{
				this->k_move_cnstrct_ua_ae(
					this_alloc, this_e, this_kc,
					kerbal::compatibility::move(src)
				);
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			avl_type_only<Entity>::
			avl_type_only(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				NodeAllocator && src_alloc, avl_type_only && src
			)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> allocator_traits;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				this->k_move_cnstrct_ua_helper(
					this_alloc, this_e, this_kc,
					kerbal::compatibility::move(src_alloc),
					kerbal::compatibility::move(src),
					is_always_equal()
				);
			}

#		endif


			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
			KERBAL_CONSTEXPR20
			avl_type_only<Entity>::
			avl_type_only(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				InputIterator first, InputIterator last
			)
			{
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#	endif
					this->k_insert_using_allocator(alloc, e, kc, first, last);
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					this->k_destroy_using_allocator(alloc);
					throw;
				}
#	endif
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
			KERBAL_CONSTEXPR20
			avl_type_only<Entity>::
			avl_type_only(
				kerbal::container::unique_tag_t,
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				InputIterator first, InputIterator last
			)
			{
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#	endif
					this->k_insert_unique_using_allocator(alloc, e, kc, first, last);
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					this->k_destroy_using_allocator(alloc);
					throw;
				}
#	endif
			}

#	if __cplusplus >= 201103L

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			avl_type_only<Entity>::
			avl_type_only(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				std::initializer_list<value_type> ilist
			) :
				avl_type_only(alloc, e, kc, ilist.begin(), ilist.end())
			{
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			avl_type_only<Entity>::
			avl_type_only(
				kerbal::container::unique_tag_t unique_tag,
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				std::initializer_list<value_type> ilist
			) :
				avl_type_only(unique_tag, alloc, e, kc, ilist.begin(), ilist.end())
			{
			}

#	else

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			avl_type_only<Entity>::
			avl_type_only(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const kerbal::assign::assign_list<void> & ilist
			)
			{
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
			avl_type_only<Entity>::
			avl_type_only(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const kerbal::assign::assign_list<U> & ilist
			)
			{
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#	endif
					this->k_insert_using_allocator(alloc, e, kc, ilist.cbegin(), ilist.cend());
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					this->k_destroy_using_allocator(alloc);
					throw;
				}
#	endif
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			avl_type_only<Entity>::
			avl_type_only(
				kerbal::container::unique_tag_t /*unique_tag*/,
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const kerbal::assign::assign_list<void> & ilist
			)
			{
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
			avl_type_only<Entity>::
			avl_type_only(
				kerbal::container::unique_tag_t /*unique_tag*/,
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const kerbal::assign::assign_list<U> & ilist
			)
			{
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#	endif
					this->k_insert_unique_using_allocator(alloc, e, kc, ilist.cbegin(), ilist.cend());
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					this->k_destroy_using_allocator(alloc);
					throw;
				}
#	endif
			}

#	endif


			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR14
			void
			avl_type_only<Entity>::
			k_destroy_using_allocator(NodeAllocator & alloc) KERBAL_NOEXCEPT
			{
				k_destroy_node_and_offsprings(alloc, this->k_head.left);
			}


		//===================
		// assign

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_cpy_ass_ua_impl(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				const NodeAllocator & src_alloc, const avl_type_only & src,
				CPYASS_VER_NOT_PROPAGATE
			)
			{
				if (this_alloc != src_alloc) {
					this->k_destroy_using_allocator(this_alloc);

					this->k_head.left = get_avl_vnull_node();
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
					try {
#			endif // if KERBAL_HAS_EXCEPTIONS_SUPPORT
						this->k_clone(this_alloc, &this->k_head, node::reinterpret_as(src.k_head.left));
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
					} catch (...) {
						this->k_destroy_using_allocator(this_alloc);
						this->k_head.left = get_avl_vnull_node();
						this->k_size = 0;
						throw;
					}
#			endif // if KERBAL_HAS_EXCEPTIONS_SUPPORT
					this->k_size = src.k_size;
				} else {
					this->k_assign_using_allocator(this_alloc, this_e, this_kc, src.cbegin(), src.cend());
				}
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_cpy_ass_ua_impl(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				const NodeAllocator & src_alloc, const avl_type_only & src,
				CPYASS_VER_PROPAGATE
			)
			{
				if (this_alloc != src_alloc) {
					this->k_destroy_using_allocator(this_alloc);
					this_alloc = src_alloc;

					this->k_head.left = get_avl_vnull_node();
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
					try {
#			endif // if KERBAL_HAS_EXCEPTIONS_SUPPORT
						this->k_clone(this_alloc, &this->k_head, node::reinterpret_as(src.k_head.left));
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
					} catch (...) {
						this->k_destroy_using_allocator(this_alloc);
						this->k_head.left = get_avl_vnull_node();
						this->k_size = 0;
						throw;
					}
#			endif // if KERBAL_HAS_EXCEPTIONS_SUPPORT
					this->k_size = src.k_size;
				} else {
					this_alloc = src_alloc;
					this->k_assign_using_allocator(this_alloc, this_e, this_kc, src.cbegin(), src.cend());
				}
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_cpy_ass_ua_impl(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				const NodeAllocator & /*src_alloc*/, const avl_type_only & src,
				CPYASS_VER_ALWAYS_EQUAL
			)
			{
				this->k_assign_using_allocator(this_alloc, this_e, this_kc, src.cbegin(), src.cend());
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_assign_using_allocator(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				const NodeAllocator & src_alloc, const avl_type_only & src
			)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> allocator_traits;
				typedef typename allocator_traits::propagate_on_container_copy_assignment propagate;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				typedef typename kerbal::type_traits::conditional<
					is_always_equal::value,
					CPYASS_VER_ALWAYS_EQUAL,
					typename kerbal::type_traits::conditional<
						propagate::value,
						CPYASS_VER_PROPAGATE,
						CPYASS_VER_NOT_PROPAGATE
					>::type
				>::type VER;

				this->k_cpy_ass_ua_impl(this_alloc, this_e, this_kc, src_alloc, src, VER());
			}


#		if __cplusplus >= 201103L

			// move assign using allocator, allocator is equal
			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_mov_ass_ua_ae(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				avl_type_only && src
			) KERBAL_NOEXCEPT
			{
				this->k_destroy_using_allocator(this_alloc);
				this->k_head.left = get_avl_vnull_node();
				this->k_size = 0;
				avl_type_unrelated::k_swap(static_cast<avl_type_unrelated &>(src), static_cast<avl_type_unrelated &>(*this));
			}

			// move assign using allocator, allocator is not equal
			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_mov_ass_ua_ane(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				avl_type_only && src
			)
			{
				this->k_assign_using_allocator(
					this_alloc, this_e, this_kc,
					kerbal::iterator::make_move_iterator(src.begin()),
					kerbal::iterator::make_move_iterator(src.end())
				);
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_mov_ass_ua_impl(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				NodeAllocator && src_alloc, avl_type_only && src,
				MOVASS_VER_NOT_PROPAGATE
			)
			{
				if (this_alloc != src_alloc) {
					this->k_mov_ass_ua_ane(this_alloc, this_e, this_kc, kerbal::compatibility::move(src));
				} else {
					this->k_mov_ass_ua_ae(this_alloc, this_e, this_kc, kerbal::compatibility::move(src));
				}
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_mov_ass_ua_impl(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				NodeAllocator && src_alloc, avl_type_only && src,
				MOVASS_VER_PROPAGATE
			)
			{
				this->k_destroy_using_allocator(this_alloc);
				this->k_head.left = get_avl_vnull_node();
				this->k_size = 0;
				this_alloc = kerbal::compatibility::move(src_alloc);
				avl_type_unrelated::k_swap(static_cast<avl_type_unrelated &>(src), static_cast<avl_type_unrelated &>(*this));
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_mov_ass_ua_impl(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				NodeAllocator && /*src_alloc*/, avl_type_only && src,
				MOVASS_VER_ALWAYS_EQUAL
			) KERBAL_NOEXCEPT
			{
				this->k_mov_ass_ua_ae(this_alloc, this_e, this_kc, kerbal::compatibility::move(src));
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_assign_using_allocator(
				NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
				NodeAllocator && src_alloc, avl_type_only && src
			)
				KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_assign_using_allocator<NodeAllocator>::value)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> allocator_traits;
				typedef typename allocator_traits::propagate_on_container_move_assignment propagate;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				typedef typename kerbal::type_traits::conditional<
					is_always_equal::value,
					MOVASS_VER_ALWAYS_EQUAL,
					typename kerbal::type_traits::conditional<
						propagate::value,
						MOVASS_VER_PROPAGATE,
						MOVASS_VER_NOT_PROPAGATE
					>::type
				>::type VER;

				this->k_mov_ass_ua_impl(
					this_alloc, this_e, this_kc,
					kerbal::compatibility::move(src_alloc),
					kerbal::compatibility::move(src),
					VER()
				);
			}

#		endif


			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_assign_destroy_n(NodeAllocator & alloc, node_base * start, size_type size, head_node * head)
			{
				for (size_type i = 0; i < size; ++i) {
					head_node * next = start->postorder_next(head);
					k_destroy_node(alloc, start);
					start = next->as_node_base();
				}
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_assign_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				InputIterator first, InputIterator last
			)
			{
				if (this->k_head.left == get_avl_vnull_node()) {
					this->k_insert_using_allocator(alloc, e, kc, first, last);
					return;
				}

				// move current tree to tmp
				head_node tmp_head;
				tmp_head.left = this->k_head.left;
				tmp_head.left->parent = &tmp_head;
				this->k_head.left = get_avl_vnull_node();
				size_type tmp_size = this->k_size;
				this->k_size = 0;

				node_base * tmp_it = tmp_head.leftest_offspring();
				if (tmp_it->right != get_avl_vnull_node()) { // only correct under avl
					tmp_it = tmp_it->right;
				}

				// tmp_it advances in post-order

				size_type i = 0;

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif // if KERBAL_HAS_EXCEPTIONS_SUPPORT
					while (i < tmp_size && first != last) { // may throw here
						node * p = node::reinterpret_as(tmp_it);
						++i;
						tmp_it = tmp_it->postorder_next(&tmp_head)->as_node_base();
						k_reuse_node(alloc, p, *first); // may throw here
						this->k_emplace_hook_node(e, kc, p);
						++first; // may throw here
					}
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_assign_destroy_n(alloc, tmp_it, tmp_size - i, &tmp_head);
					throw;
				}
#			endif // if KERBAL_HAS_EXCEPTIONS_SUPPORT

				k_assign_destroy_n(alloc, tmp_it, tmp_size - i, &tmp_head);
				this->k_insert_using_allocator(alloc, e, kc, first, last);
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_assign_unique_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				InputIterator first, InputIterator last
			)
			{
				if (this->k_head.left == get_avl_vnull_node()) {
					this->k_insert_unique_using_allocator(alloc, e, kc, first, last);
					return;
				}

				// move current tree to tmp
				head_node tmp_head;
				tmp_head.left = this->k_head.left;
				tmp_head.left->parent = &tmp_head;
				this->k_head.left = get_avl_vnull_node();
				size_type tmp_size = this->k_size;
				this->k_size = 0;

				node_base * tmp_it = tmp_head.leftest_offspring();
				if (tmp_it->right != get_avl_vnull_node()) { // only correct under avl
					tmp_it = tmp_it->right;
				}


				size_type i = 0;

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif // if KERBAL_HAS_EXCEPTIONS_SUPPORT
					while (i < tmp_size && first != last) { // may throw here
						node * p = node::reinterpret_as(tmp_it);
						++i;
						tmp_it = tmp_it->postorder_next(&tmp_head)->as_node_base();
						head_node * parent_backup = p->parent;
						k_reuse_node(alloc, p, *first); // may throw here
						if (!this->k_emplace_hook_node_unique(e, kc, p).insert_happen()) { // rollback
							--i;
							tmp_it = p;
							p->parent = parent_backup;
						}
						++first; // may throw here
					}
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_assign_destroy_n(alloc, tmp_it, tmp_size - i, &tmp_head);
					throw;
				}
#			endif // if KERBAL_HAS_EXCEPTIONS_SUPPORT

				k_assign_destroy_n(alloc, tmp_it, tmp_size - i, &tmp_head);
				this->k_insert_unique_using_allocator(alloc, e, kc, first, last);
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_assign_sorted_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				InputIterator first, InputIterator last
			)
			{
				iterator it = this->begin();
				iterator end = this->end();

				while (it != end && first != last) {
					*it = first;
					++it;
					++first;
				}

				if (it != end) {
					this->k_erase_using_allocator(alloc, it, end);
				} else {
					this->k_insert_using_allocator(alloc, e, kc, first, last);
				}
			}


		//===================
		// iterator

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename avl_type_only<Entity>::iterator_type_unrelated
			avl_type_only<Entity>::begin_() KERBAL_NOEXCEPT
			{
				return iterator_type_unrelated(this->k_head.leftest_offspring());
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename avl_type_only<Entity>::iterator_type_unrelated
			avl_type_only<Entity>::end_() KERBAL_NOEXCEPT
			{
				return iterator_type_unrelated(&this->k_head);
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			begin() KERBAL_NOEXCEPT
			{
				return iterator(this->k_head.leftest_offspring());
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_head.leftest_offspring());
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			cbegin() const KERBAL_NOEXCEPT
			{
				return this->begin();
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			end() KERBAL_NOEXCEPT
			{
				return iterator(&this->k_head);
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			end() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->k_head);
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			cend() const KERBAL_NOEXCEPT
			{
				return this->end();
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::reverse_iterator
			avl_type_only<Entity>::
			rbegin() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->end());
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_reverse_iterator
			avl_type_only<Entity>::
			rbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->end());
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_reverse_iterator
			avl_type_only<Entity>::
			crbegin() const KERBAL_NOEXCEPT
			{
				return this->rbegin();
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::reverse_iterator
			avl_type_only<Entity>::
			rend() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->begin());
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_reverse_iterator
			avl_type_only<Entity>::
			rend() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->begin());
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_reverse_iterator
			avl_type_only<Entity>::
			crend() const KERBAL_NOEXCEPT
			{
				return this->rend();
			}


		//===================
		// lookup

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			k_find_impl(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				const node_base * cur_base = this->k_head.left;
				while (cur_base != get_avl_vnull_node()) {
					const typename Extract::key_type & cur_key = e(node::reinterpret_as(cur_base)->member());
					if (kc(key, cur_key)) { // key < cur_key
						cur_base = cur_base->left;
					} else if (kc(cur_key, key)) { // cur_key < key
						cur_base = cur_base->right;
					} else {
						return const_iterator(cur_base);
					}
				}
				return this->end();
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			k_find(
				Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			) const
			{
				return this->k_find_impl(e, kc, key);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_find(
				Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			)
			{
				return this->k_find_impl(e, kc, key).cast_to_mutable();
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				typename avl_type_only<Entity>::const_iterator
			>::type
			avl_type_only<Entity>::
			k_find(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				return this->k_find_impl(e, kc, key);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				typename avl_type_only<Entity>::iterator
			>::type
			avl_type_only<Entity>::
			k_find(
				Extract & e, KeyCompare & kc,
				const Key & key
			)
			{
				return this->k_find_impl(e, kc, key).cast_to_mutable();
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::node_base const *
			avl_type_only<Entity>::
			k_lower_bound_helper(
				Extract & e, KeyCompare & kc,
				const Key & key,
				const node_base * cur_base, const node_base * lbound
			)
			{
				while (cur_base != get_avl_vnull_node()) {
					if (kc(e(node::reinterpret_as(cur_base)->member()), key)) { // cur_key < key
						cur_base = cur_base->right;
					} else { // cur_key >= key
						lbound = cur_base;
						cur_base = cur_base->left;
					}
				}
				return lbound;
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::node_base const *
			avl_type_only<Entity>::
			k_upper_bound_helper(
				Extract & e, KeyCompare & kc,
				const Key & key,
				const node_base * cur_base, const node_base * ubound
			)
			{
				while (cur_base != get_avl_vnull_node()) {
					if (kc(key, e(node::reinterpret_as(cur_base)->member()))) { // key < cur_key
						ubound = cur_base;
						cur_base = cur_base->left;
					} else { // key >= cur_key
						cur_base = cur_base->right;
					}
				}
				return ubound;
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			k_lower_bound_impl(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				const node_base * lbound = this->k_head.as_node_base();
				lbound = k_lower_bound_helper(e, kc, key, this->k_head.left, lbound);
				return const_iterator(lbound);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			k_lower_bound(
				Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			) const
			{
				return this->k_lower_bound_impl(e, kc, key);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_lower_bound(
				Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			)
			{
				return this->k_lower_bound_impl(e, kc, key).cast_to_mutable();
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				typename avl_type_only<Entity>::const_iterator
			>::type
			avl_type_only<Entity>::
			k_lower_bound(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				return this->k_lower_bound_impl(e, kc, key);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				typename avl_type_only<Entity>::iterator
			>::type
			avl_type_only<Entity>::
			k_lower_bound(
				Extract & e, KeyCompare & kc,
				const Key & key
			)
			{
				return this->k_lower_bound_impl(e, kc, key).cast_to_mutable();
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			k_upper_bound_impl(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				const node_base * ubound = this->k_head.as_node_base();
				ubound = k_upper_bound_helper(e, kc, key, this->k_head.left, ubound);
				return const_iterator(ubound);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			k_upper_bound(
				Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			) const
			{
				return this->k_upper_bound_impl(e, kc, key);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_upper_bound(
				Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			)
			{
				return this->k_upper_bound_impl(e, kc, key).cast_to_mutable();
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				typename avl_type_only<Entity>::const_iterator
			>::type
			avl_type_only<Entity>::
			k_upper_bound(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				return this->k_upper_bound_impl(e, kc, key);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				typename avl_type_only<Entity>::iterator
			>::type
			avl_type_only<Entity>::
			k_upper_bound(
				Extract & e, KeyCompare & kc,
				const Key & key
			)
			{
				return this->k_upper_bound_impl(e, kc, key).cast_to_mutable();
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<
				typename avl_type_only<Entity>::const_iterator,
				typename avl_type_only<Entity>::const_iterator
			>
			avl_type_only<Entity>::
			k_equal_range_impl(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				const node_base * lbound = this->k_head.as_node_base();
				const node_base * ubound = lbound;
				const node_base * cur_base = this->k_head.left;
				while (cur_base != get_avl_vnull_node()) {
					const typename Extract::key_type & cur_key = e(node::reinterpret_as(cur_base)->member());
					if (kc(key, cur_key)) { // key < cur_key
						lbound = cur_base;
						ubound = cur_base;
						cur_base = cur_base->left;
					} else if (kc(cur_key, key)) { // cur_key < key
						cur_base = cur_base->right;
					} else { // key == cur_key
						lbound = cur_base;
						lbound = k_lower_bound_helper(e, kc, key, cur_base->left, lbound);
						ubound = k_upper_bound_helper(e, kc, key, cur_base->right, ubound);
						break;
					}
				}
				return kerbal::utility::make_compressed_pair(
					const_iterator(lbound), const_iterator(ubound)
				);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<
				typename avl_type_only<Entity>::const_iterator,
				typename avl_type_only<Entity>::const_iterator
			>
			avl_type_only<Entity>::
			k_equal_range(
				Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			) const
			{
				return this->k_equal_range_impl(e, kc, key);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<
				typename avl_type_only<Entity>::iterator,
				typename avl_type_only<Entity>::iterator
			>
			avl_type_only<Entity>::
			k_equal_range(
				Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			)
			{
				kerbal::utility::compressed_pair<const_iterator, const_iterator> range(
					this->k_equal_range_impl(e, kc, key)
				);
				return kerbal::utility::make_compressed_pair(
					range.first().cast_to_mutable(),
					range.second().cast_to_mutable()
				);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				kerbal::utility::compressed_pair<
					typename avl_type_only<Entity>::const_iterator,
					typename avl_type_only<Entity>::const_iterator
				>
			>::type
			avl_type_only<Entity>::
			k_equal_range(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				return this->k_equal_range_impl(e, kc, key);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				kerbal::utility::compressed_pair<
					typename avl_type_only<Entity>::iterator,
					typename avl_type_only<Entity>::iterator
				>
			>::type
			avl_type_only<Entity>::
			k_equal_range(
				Extract & e, KeyCompare & kc,
				const Key & key
			)
			{
				kerbal::utility::compressed_pair<const_iterator, const_iterator> range(
					this->k_equal_range_impl(e, kc, key)
				);
				return kerbal::utility::make_compressed_pair(
					range.first().cast_to_mutable(),
					range.second().cast_to_mutable()
				);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			bool
			avl_type_only<Entity>::
			k_contains_impl(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				const node_base * cur_base = this->k_head.left;
				while (cur_base != get_avl_vnull_node()) {
					const typename Extract::key_type & cur_key = e(node::reinterpret_as(cur_base)->member());
					if (kc(key, cur_key)) { // key < cur_key
						cur_base = cur_base->left;
					} else if (kc(cur_key, key)) { // cur_key < key
						cur_base = cur_base->right;
					} else { // key == cur_key
						return true;
					}
				}
				return false;
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			bool
			avl_type_only<Entity>::
			k_contains(
				Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			) const
			{
				return this->k_contains_impl(e, kc, key);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				bool
			>::type
			avl_type_only<Entity>::
			k_contains(
				Extract & e, KeyCompare & kc,
				const Key & key
			) const
			{
				return this->k_contains_impl(e, kc, key);
			}


		//===================
		// insert

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename UpCaster>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_emplace_hook_node(Extract & e, KeyCompare & kc, node_base * p_node_base, UpCaster up_caster)
			{
				if (this->k_head.left == get_avl_vnull_node()) {
					this->k_head.left = p_node_base;
					p_node_base->parent = &this->k_head;
					++this->k_size;
				} else {
					const typename Extract::key_type & src_key = e(up_caster(p_node_base)->member());

					node_base * cur_base = this->k_head.left;
					while (true) {
						if (
							kc(
								src_key,
								e(up_caster(cur_base)->member())
							)
						) { // src < p->member(), ** may throw here **
							if (cur_base->left == get_avl_vnull_node()) {
								cur_base->left = p_node_base;
								break;
							}
							cur_base = cur_base->left;
						} else {
							if (cur_base->right == get_avl_vnull_node()) {
								cur_base->right = p_node_base;
								break;
							}
							cur_base = cur_base->right;
						}
					}

					p_node_base->parent = cur_base;
					++this->k_size;
					cur_base->height = 2;
					k_emplace_rebalance(cur_base->parent);
				}
				return iterator(p_node_base);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename UpCaster>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_emplace_hook_node_unique(Extract & e, KeyCompare & kc, node_base * p_node_base, UpCaster up_caster)
			{
				if (this->k_head.left == get_avl_vnull_node()) {
					this->k_head.left = p_node_base;
					p_node_base->parent = &this->k_head;
					++this->k_size;
				} else {
					const typename Extract::key_type & src_key = e(up_caster(p_node_base)->member());

					node_base * cur_base = this->k_head.left;
					while (true) {
						const typename Extract::key_type & cur_key = e(up_caster(cur_base)->member());
						if (kc(src_key, cur_key)) { // src_key < cur_key, ** may throw here **
							if (cur_base->left == get_avl_vnull_node()) {
								cur_base->left = p_node_base;
								break;
							}
							cur_base = cur_base->left;
						} else if (kc(cur_key, src_key)) { // cur_key < src_key
							if (cur_base->right == get_avl_vnull_node()) {
								cur_base->right = p_node_base;
								break;
							}
							cur_base = cur_base->right;
						} else { // src_key == cur_key
							return unique_insert_r(iterator(cur_base), false);
						}
					}

					p_node_base->parent = cur_base;
					++this->k_size;
					cur_base->height = 2;
					k_emplace_rebalance(cur_base->parent);
				}
				return unique_insert_r(iterator(p_node_base), true);
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_emplace_ua_aux(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				node * p
			)
			{
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif
					return this->k_emplace_hook_node(e, kc, p);
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_destroy_node(alloc, p);
					throw;
				}
#			endif
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_emplace_unique_ua_aux(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				node * p
			)
			{
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#			endif
					unique_insert_r ret(this->k_emplace_hook_node_unique(e, kc, p));
					if (!ret.insert_happen()) {
						k_destroy_node(alloc, p);
					}
					return ret;
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					k_destroy_node(alloc, p);
					throw;
				}
#			endif
			}

#	if __cplusplus >= 201103L

			template <typename Entity>
			template <
				typename NodeAllocator, typename Extract, typename KeyCompare,
				typename ... Args
			>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_emplace_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				Args && ... args
			)
			{
				node * p = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				return this->k_emplace_ua_aux(alloc, e, kc, p);
			}

			template <typename Entity>
			template <
				typename NodeAllocator, typename Extract, typename KeyCompare,
				typename ... Args
			>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_emplace_unique_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				Args && ... args
			)
			{
				node * p = k_build_new_node(alloc, kerbal::utility::forward<Args>(args)...);
				return this->k_emplace_unique_ua_aux(alloc, e, kc, p);
			}

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename Entity> \
			template < \
				typename NodeAllocator, typename Extract, typename KeyCompare \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
			> \
			typename \
			avl_type_only<Entity>::iterator \
			avl_type_only<Entity>:: \
			k_emplace_using_allocator( \
				NodeAllocator & alloc, Extract & e, KeyCompare & kc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
			) \
			{ \
				node * p = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				return this->k_emplace_ua_aux(alloc, e, kc, p); \
			} \
 \
			template <typename Entity> \
			template < \
				typename NodeAllocator, typename Extract, typename KeyCompare \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
			> \
			typename \
			avl_type_only<Entity>::unique_insert_r \
			avl_type_only<Entity>:: \
			k_emplace_unique_using_allocator( \
				NodeAllocator & alloc, Extract & e, KeyCompare & kc \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
			) \
			{ \
				node * p = k_build_new_node(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				return this->k_emplace_unique_ua_aux(alloc, e, kc, p); \
			} \

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif


			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
#	if __cplusplus >= 201103L
			k_emplace_unique_delay_build(NodeAllocator & alloc, Extract & e, KeyCompare & kc, U && src_key)
#	else
			k_emplace_unique_delay_build(NodeAllocator & alloc, Extract & e, KeyCompare & kc, const U & src_key)
#	endif
			{

#	if __cplusplus >= 201103L
#				define FORWARD(T, arg) kerbal::utility::forward<T>(arg)
#	else
#				define FORWARD(T, arg) arg
#	endif

				node * p = NULL;
				if (this->k_size == 0) {
					p = k_build_new_node(alloc, FORWARD(U, src_key));
					this->k_head.left = p;
					p->parent = &this->k_head;
				} else {
					node_base * cur_base = this->k_head.left;
					while (true) {
						const_reference cur_key = node::reinterpret_as(cur_base)->member();
						if (kc(src_key, cur_key)) { // src_key < cur_key, ** may throw here **
							if (cur_base->left == get_avl_vnull_node()) {
								p = k_build_new_node(alloc, FORWARD(U, src_key));
								cur_base->left = p;
								break;
							}
							cur_base = cur_base->left;
						} else if (kc(cur_key, src_key)) { // cur_key < src_key
							if (cur_base->right == get_avl_vnull_node()) {
								p = k_build_new_node(alloc, FORWARD(U, src_key));
								cur_base->right = p;
								break;
							}
							cur_base = cur_base->right;
						} else {
							return unique_insert_r(iterator(cur_base), false);
						}
					}

					p->parent = cur_base;
					cur_base->height = 2;
					k_emplace_rebalance(cur_base->parent);
				}
				++this->k_size;
				return unique_insert_r(iterator(p), true);
#				undef FORWARD
			}


			template <typename Entity>
			template <typename NodeAllocator, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_emplace_unique_using_allocator(
				NodeAllocator & alloc,
				kerbal::container::identity_extractor<Entity> & e,
				KeyCompare & kc,
				const_reference src_key
			)
			{
				return this->k_emplace_unique_delay_build(alloc, e, kc, src_key);
			}

			template <typename Entity>
			template <typename NodeAllocator, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_emplace_unique_using_allocator(
				NodeAllocator & alloc,
				kerbal::container::identity_extractor<Entity> & e,
				KeyCompare & kc,
				reference src_key
			)
			{
				return this->k_emplace_unique_delay_build(alloc, e, kc, static_cast<const_reference>(src_key));
			}

#	if __cplusplus >= 201103L

			template <typename Entity>
			template <typename NodeAllocator, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_emplace_unique_using_allocator(
				NodeAllocator & alloc,
				kerbal::container::identity_extractor<Entity> & e,
				KeyCompare & kc,
				rvalue_reference src_key
			)
			{
				return this->k_emplace_unique_delay_build(alloc, e, kc, kerbal::compatibility::move(src_key));
			}

#	endif


			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_insert_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const_reference src
			)
			{
				return this->k_emplace_using_allocator(alloc, e, kc, src);
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_insert_unique_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const_reference src
			)
			{
				return this->k_emplace_unique_using_allocator(alloc, e, kc, src);
			}


#	if __cplusplus >= 201103L

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_insert_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				rvalue_reference src
			)
			{
				return this->k_emplace_using_allocator(alloc, e, kc, kerbal::compatibility::move(src));
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_insert_unique_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				rvalue_reference src
			)
			{
				return this->k_emplace_unique_using_allocator(alloc, e, kc, kerbal::compatibility::move(src));
			}

#	endif


			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_insert_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				InputIterator first, InputIterator last
			)
			{
				while (first != last) {
					this->k_insert_using_allocator(alloc, e, kc, *first);
					++first;
				}
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename InputIterator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_insert_unique_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				InputIterator first, InputIterator last
			)
			{
				while (first != last) {
					this->k_insert_unique_using_allocator(alloc, e, kc, *first);
					++first;
				}
			}


#	if __cplusplus >= 201103L

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_insert_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				std::initializer_list<value_type> ilist
			)
			{
				this->k_insert_using_allocator(alloc, e, kc, ilist.begin(), ilist.end());
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_insert_unique_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				std::initializer_list<value_type> ilist
			)
			{
				this->k_insert_unique_using_allocator(alloc, e, kc, ilist.begin(), ilist.end());
			}

#	else

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			void
			avl_type_only<Entity>::
			k_insert_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const kerbal::assign::assign_list<void> & ilist
			)
			{
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
			void
			avl_type_only<Entity>::
			k_insert_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const kerbal::assign::assign_list<U> & ilist
			)
			{
				this->k_insert_using_allocator(alloc, e, kc, ilist.cbegin(), ilist.cend());
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			void
			avl_type_only<Entity>::
			k_insert_unique_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const kerbal::assign::assign_list<void> & ilist
			)
			{
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename U>
			void
			avl_type_only<Entity>::
			k_insert_unique_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const kerbal::assign::assign_list<U> & ilist
			)
			{
				this->k_insert_unique_using_allocator(alloc, e, kc, ilist.cbegin(), ilist.cend());
			}

#	endif


		//===================
		// prepare_insert

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename UpCaster>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::prepare_hook_node_context
			avl_type_only<Entity>::
			k_prepare_hook_node(Extract & e, KeyCompare & kc, node_base * p_node_base, UpCaster up_caster)
			{
				if (this->k_head.left == get_avl_vnull_node()) {
					return prepare_hook_node_context::make_head(&this->k_head.left);
				} else {
					const typename Extract::key_type & src_key = e(up_caster(p_node_base)->member());

					node_base * cur_base = this->k_head.left;
					while (true) {
						if (kc(src_key, e(up_caster(cur_base)->member()))) { // src < p->member(), ** may throw here **
							if (cur_base->left == get_avl_vnull_node()) {
								return prepare_hook_node_context::make_sub(cur_base, &cur_base->left);
							}
							cur_base = cur_base->left;
						} else {
							if (cur_base->right == get_avl_vnull_node()) {
								return prepare_hook_node_context::make_sub(cur_base, &cur_base->right);
							}
							cur_base = cur_base->right;
						}
					}
				}
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_complete_hook_node(const prepare_hook_node_context & context, node_base * p_node_base) KERBAL_NOEXCEPT
			{
				if (context.status == false) {
					*(context.p_insert_pos) = p_node_base;
					p_node_base->parent = &this->k_head;
					++this->k_size;
				} else {
					*(context.p_insert_pos) = p_node_base;
					node_base * cur_base = context.p_pos;
					p_node_base->parent = cur_base;
					++this->k_size;
					cur_base->height = 2;
					k_emplace_rebalance(cur_base->parent);
				}
				return iterator(p_node_base);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare, typename UpCaster>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::prepare_hook_node_unique_context
			avl_type_only<Entity>::
			k_prepare_hook_node_unique(Extract & e, KeyCompare & kc, node_base * p_node_base, UpCaster up_caster)
			{
				if (this->k_head.left == get_avl_vnull_node()) {
					return prepare_hook_node_unique_context::make_head(&this->k_head.left);
				} else {
					const typename Extract::key_type & src_key = e(up_caster(p_node_base)->member());

					node_base * cur_base = this->k_head.left;
					while (true) {
						const typename Extract::key_type & cur_key = e(up_caster(cur_base)->member());
						if (kc(src_key, cur_key)) { // src_key < cur_key, ** may throw here **
							if (cur_base->left == get_avl_vnull_node()) {
								return prepare_hook_node_unique_context::make_sub(cur_base, &cur_base->left);
							}
							cur_base = cur_base->left;
						} else if (kc(cur_key, src_key)) { // cur_key < src_key
							if (cur_base->right == get_avl_vnull_node()) {
								return prepare_hook_node_unique_context::make_sub(cur_base, &cur_base->right);
							}
							cur_base = cur_base->right;
						} else { // src_key == cur_key
							return prepare_hook_node_unique_context::make_duplicate(cur_base);
						}
					}
				}
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_complete_hook_node_unique(const prepare_hook_node_unique_context & context, node_base * p_node_base) KERBAL_NOEXCEPT
			{
				if (context.status == 0) {
					*(context.p_insert_pos) = p_node_base;
					p_node_base->parent = &this->k_head;
					++this->k_size;
				} else { // status == 1
					*(context.p_insert_pos) = p_node_base;
					node_base * cur_base = context.p_pos;
					p_node_base->parent = cur_base;
					++this->k_size;
					cur_base->height = 2;
					k_emplace_rebalance(cur_base->parent);
				}
				return iterator(p_node_base);
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_complete_hook_node_duplicated(const prepare_hook_node_context & context) KERBAL_NOEXCEPT
			{
				return iterator(context.p_pos);
			}

			template <typename Entity>
			KERBAL_CONSTEXPR14
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_complete_hook_node_duplicated(const prepare_hook_node_unique_context & context) KERBAL_NOEXCEPT
			{
				return iterator(context.p_pos);
			}

		//===================
		// erase

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_erase_not_end_using_allocator_unsafe(NodeAllocator & alloc, const_iterator pos) KERBAL_NOEXCEPT
			{
				node_base * cur_base = pos.cast_to_mutable().current->as_node_base();
				iterator ret(this->avl_type_unrelated::k_unhook_node_and_get_successor(cur_base));
				k_destroy_node(alloc, cur_base);
				return ret;
			}

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_erase_using_allocator(
				NodeAllocator & alloc,
				const_iterator pos
			) KERBAL_NOEXCEPT
			{
				if (pos == this->cend()) {
					return this->end();
				}

				return this->k_erase_not_end_using_allocator_unsafe(alloc, pos);
			}

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_erase_using_allocator(
				NodeAllocator & alloc,
				const_iterator first, const_iterator last
			) KERBAL_NOEXCEPT
			{
				while (first != last) {
					first = this->k_erase_not_end_using_allocator_unsafe(alloc, first);
				}
				return first.cast_to_mutable();
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::size_type
			avl_type_only<Entity>::
			k_erase_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const typename Extract::key_type & key
			) KERBAL_NOEXCEPT
			{
				kerbal::utility::compressed_pair<const_iterator, const_iterator> equ_range(
					this->k_equal_range(e, kc, key)
				);
				size_type cnt = 0;
				while (equ_range.first() != equ_range.second()) {
					equ_range.first() = this->k_erase_not_end_using_allocator_unsafe(alloc, equ_range.first());
					++cnt;
				}
				return cnt;
			}

			template <typename Entity>
			template <typename NodeAllocator, typename Extract, typename KeyCompare, typename Key>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::template enable_if_transparent_lookup<
				Extract, KeyCompare, Key,
				typename avl_type_only<Entity>::size_type
			>::type
			avl_type_only<Entity>::
			k_erase_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const Key & key
			) KERBAL_NOEXCEPT
			{
				kerbal::utility::compressed_pair<const_iterator, const_iterator> equ_range(
					this->k_equal_range(e, kc, key)
				);
				size_type cnt = 0;
				while (equ_range.first() != equ_range.second()) {
					equ_range.first() = this->k_erase_not_end_using_allocator_unsafe(alloc, equ_range.first());
					++cnt;
				}
				return cnt;
			}

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_clear_using_allocator(NodeAllocator & alloc) KERBAL_NOEXCEPT
			{
				k_destroy_node_and_offsprings(alloc, this->k_head.left);
				this->k_head.left = get_avl_vnull_node();
				this->k_size = 0;
			}


		//===================
		// replace

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::node *
			avl_type_only<Entity>::
			k_replace_reuse_node(NodeAllocator & alloc, const_iterator replace)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;

				node * p = NULL;
				if (replace == this->cend()) {
					p = node_allocator_traits::allocate_one(alloc);

#		if !KERBAL_HAS_EXCEPTIONS_SUPPORT
					if (p == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
#		endif // KERBAL_HAS_EXCEPTIONS_SUPPORT

				} else {
					p = node::reinterpret_as(replace.cast_to_mutable().current);
					this->k_unhook_node(p);
					node_allocator_traits::destroy(alloc, p);
				}
				return p;
			}

#	if __cplusplus >= 201103L

			template <typename Entity>
			template <
				typename NodeAllocator, typename Extract, typename KeyCompare,
				typename ... Args
			>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::iterator
			avl_type_only<Entity>::
			k_replace_emplace_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const_iterator replace,
				Args && ... args
			)
			{
				node * p = this->k_replace_reuse_node(alloc, replace);
				k_try_construct_node(alloc, p, kerbal::utility::forward<Args>(args)...);
				return this->k_emplace_ua_aux(alloc, e, kc, p);
			}

			template <typename Entity>
			template <
				typename NodeAllocator, typename Extract, typename KeyCompare,
				typename ... Args
			>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_replace_emplace_unique_using_allocator(
				NodeAllocator & alloc, Extract & e, KeyCompare & kc,
				const_iterator replace,
				Args && ... args
			)
			{
				node * p = this->k_replace_reuse_node(alloc, replace);
				k_try_construct_node(alloc, p, kerbal::utility::forward<Args>(args)...);
				return this->k_emplace_unique_ua_aux(alloc, e, kc, p);
			}

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename Entity> \
			template < \
				typename NodeAllocator, typename Extract, typename KeyCompare \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
			> \
			typename \
			avl_type_only<Entity>::iterator \
			avl_type_only<Entity>:: \
			k_replace_emplace_using_allocator( \
				NodeAllocator & alloc, Extract & e, KeyCompare & kc, \
				const_iterator replace \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
			) \
			{ \
				node * p = this->k_replace_reuse_node(alloc, replace); \
				k_try_construct_node(alloc, p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				return this->k_emplace_ua_aux(alloc, e, kc, p); \
			} \
 \
			template <typename Entity> \
			template < \
				typename NodeAllocator, typename Extract, typename KeyCompare \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
			> \
			typename \
			avl_type_only<Entity>::unique_insert_r \
			avl_type_only<Entity>:: \
			k_replace_emplace_unique_using_allocator( \
				NodeAllocator & alloc, Extract & e, KeyCompare & kc, \
				const_iterator replace \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
			) \
			{ \
				node * p = this->k_replace_reuse_node(alloc, replace); \
				k_try_construct_node(alloc, p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				return this->k_emplace_unique_ua_aux(alloc, e, kc, p); \
			} \

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif


		//===================
		// operation

			template <typename Entity>
			template <typename ThisExtract, typename ThisKeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::const_iterator
			avl_type_only<Entity>::
			k_splice(
				ThisExtract & this_e, ThisKeyCompare & this_kc,
				avl_type_only & other, const_iterator other_it
			)
			{
				node * p = node::reinterpret_as(other_it.cast_to_mutable().current);

				avl_head_node * next = NULL;
				if (this->k_size == 0) {
					next = other.k_unhook_node_and_get_successor(p);
					this->k_head.left = p;
					p->left = get_avl_vnull_node();
					p->right = get_avl_vnull_node();
					p->height = 1;
					p->parent = &this->k_head;
				} else {
					const typename ThisExtract::key_type & other_key = this_e(p->member());

					node_base * cur_base = this->k_head.left;
					while (true) {
						if (
							this_kc(
								other_key,
								this_e(node::reinterpret_as(cur_base)->member())
							)
						) { // other < p->member(), ** may throw here **
							if (cur_base->left == get_avl_vnull_node()) {
								next = other.k_unhook_node_and_get_successor(p);
								cur_base->left = p;
								break;
							}
							cur_base = cur_base->left;
						} else {
							if (cur_base->right == get_avl_vnull_node()) {
								next = other.k_unhook_node_and_get_successor(p);
								cur_base->right = p;
								break;
							}
							cur_base = cur_base->right;
						}
					}

					p->left = get_avl_vnull_node();
					p->right = get_avl_vnull_node();
					p->height = 1;
					p->parent = cur_base;
					cur_base->height = 2;
					k_emplace_rebalance(cur_base->parent);
				}
				++this->k_size;
				return const_iterator(next);
			}

			template <typename Entity>
			template <typename ThisExtract, typename ThisKeyCompare>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::unique_insert_r
			avl_type_only<Entity>::
			k_splice_unique(
				ThisExtract & this_e, ThisKeyCompare & this_kc,
				avl_type_only & other, const_iterator other_it
			)
			{
				node * p = node::reinterpret_as(other_it.cast_to_mutable().current);

				avl_head_node * next = NULL;
				if (this->k_size == 0) {
					next = other.k_unhook_node_and_get_successor(p);
					this->k_head.left = p;
					p->left = get_avl_vnull_node();
					p->right = get_avl_vnull_node();
					p->height = 1;
					p->parent = &this->k_head;
				} else {
					const typename ThisExtract::key_type & other_key = this_e(p->member());

					node_base * cur_base = this->k_head.left;
					while (true) {
						const typename ThisExtract::key_type & cur_key = this_e(node::reinterpret_as(cur_base)->member());
						if (this_kc(other_key, cur_key)) { // other < p->member(), ** may throw here **
							if (cur_base->left == get_avl_vnull_node()) {
								next = other.k_unhook_node_and_get_successor(p);
								cur_base->left = p;
								break;
							}
							cur_base = cur_base->left;
						} else if (this_kc(cur_key, other_key)) { // p->member() < other
							if (cur_base->right == get_avl_vnull_node()) {
								next = other.k_unhook_node_and_get_successor(p);
								cur_base->right = p;
								break;
							}
							cur_base = cur_base->right;
						} else {
							return unique_insert_r((++other_it).cast_to_mutable(), false);
						}
					}

					p->left = get_avl_vnull_node();
					p->right = get_avl_vnull_node();
					p->height = 1;
					p->parent = cur_base;
					cur_base->height = 2;
					k_emplace_rebalance(cur_base->parent);
				}
				++this->k_size;
				return unique_insert_r(iterator(next), true);
			}

			template <typename Entity>
			template <typename ThisExtract, typename ThisKeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_merge(
				ThisExtract & this_e, ThisKeyCompare & this_kc,
				avl_type_only & other, const_iterator other_begin, const_iterator other_end
			)
			{
				while (other_begin != other_end) {
					other_begin = this->k_splice(this_e, this_kc, other, other_begin);
				}
			}

			template <typename Entity>
			template <typename ThisExtract, typename ThisKeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_merge_unique(
				ThisExtract & this_e, ThisKeyCompare & this_kc,
				avl_type_only & other, const_iterator other_begin, const_iterator other_end
			)
			{
				while (other_begin != other_end) {
					other_begin = this->k_splice_unique(this_e, this_kc, other, other_begin).position();
				}
			}

			template <typename Entity>
			template <typename ThisExtract, typename ThisKeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_merge(
				ThisExtract & this_e, ThisKeyCompare & this_kc,
				avl_type_only & other
			)
			{
				this->k_merge(this_e, this_kc, other, other.cbegin(), other.cend());
			}

			template <typename Entity>
			template <typename ThisExtract, typename ThisKeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_merge_unique(
				ThisExtract & this_e, ThisKeyCompare & this_kc,
				avl_type_only & other
			)
			{
				this->k_merge_unique(this_e, this_kc, other, other.cbegin(), other.cend());
			}

#		if __cplusplus >= 201103L

			template <typename Entity>
			template <typename ThisExtract, typename ThisKeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_merge(
				ThisExtract & this_e, ThisKeyCompare & this_kc,
				avl_type_only && other
			)
			{
				this->k_merge(this_e, this_kc, other, other.cbegin(), other.cend());
			}

			template <typename Entity>
			template <typename ThisExtract, typename ThisKeyCompare>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_merge_unique(
				ThisExtract & this_e, ThisKeyCompare & this_kc,
				avl_type_only && other
			)
			{
				this->k_merge_unique(this_e, this_kc, other, other.cbegin(), other.cend());
			}

#		endif


			template <typename Entity>
			template <typename F>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			pre_order_impl(const node_base * p_base, F f)
			{
				while (p_base != get_avl_vnull_node()) {
					const node * p = node::reinterpret_as(p_base);
					f(p->member());
					pre_order_impl(p->left, f);
					p_base = p->right;
				}
			}

			template <typename Entity>
			template <typename F>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			pre_order(F f) const
			{
				node_base * p = static_cast<node_base *>(this->k_head.left);
				pre_order_impl(p, f);
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			avl_normal_result_t
			avl_type_only<Entity>::
			avl_normal_impl(
				const node_base * p,
				const value_type * & mini, const value_type * & maxi,
				node_base::height_t & height,
				Extract & e, KeyCompare & kc
			)
			{
				if (p == get_avl_vnull_node()) {
					mini = NULL;
					maxi = NULL;
					height = 0;
					return AVL_NORMAL_RESULT_CORRECT;
				}

				// Sub Trees Check
				const value_type * lmini = NULL;
				const value_type * lmaxi = NULL;
				node_base::height_t lheight = 0;
				avl_normal_result_t lresult = avl_normal_impl(p->left, lmini, lmaxi, lheight, e, kc);
				if (lresult != AVL_NORMAL_RESULT_CORRECT) {
					return lresult;
				}

				const value_type * rmini = NULL;
				const value_type * rmaxi = NULL;
				node_base::height_t rheight = 0;
				avl_normal_result_t rresult = avl_normal_impl(p->right, rmini, rmaxi, rheight, e, kc);
				if (rresult != AVL_NORMAL_RESULT_CORRECT) {
					return rresult;
				}

				// Parent Check
				if (p->left != get_avl_vnull_node()) {
					if (p->left->parent != p) {
						return AVL_NORMAL_RESULT_BAD_PARENT;
					}
				}

				if (p->right != get_avl_vnull_node()) {
					if (p->right->parent != p) {
						return AVL_NORMAL_RESULT_BAD_PARENT;
					}
				}

				// BST Requirement Check
				const value_type & mid_value = node::reinterpret_as(p)->member();
				if (lmaxi != NULL) {
					if (!kc(e(*lmaxi), e(mid_value))) {
						return AVL_NORMAL_RESULT_BST_INVALID;
					}
				}

				if (rmini != NULL) {
					if (!kc(e(mid_value), e(*rmini))) {
						return AVL_NORMAL_RESULT_BST_INVALID;
					}
				}

				if (lmini != NULL) {
					mini = lmini;
				} else {
					mini = &mid_value;
				}
				if (rmaxi != NULL) {
					maxi = rmaxi;
				} else {
					maxi = &mid_value;
				}

				// AVL Balance Requirement Check
				if (lheight > 1 + rheight) {
					return AVL_NORMAL_RESULT_NOT_BALANCED;
				} else if (rheight > 1 + lheight) {
					return AVL_NORMAL_RESULT_NOT_BALANCED;
				}

				height = 1 + kerbal::compare::max(lheight, rheight);
				if (height != p->height) {
					return AVL_NORMAL_RESULT_DEPTH_CACHED_WRONG;
				}

				return AVL_NORMAL_RESULT_CORRECT;
			}

			template <typename Entity>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR20
			avl_normal_result_t
			avl_type_only<Entity>::
			avl_normal(Extract & e, KeyCompare & kc) const
			{
				const value_type * mini = NULL;
				const value_type * maxi = NULL;
				node_base::height_t height = 0;
				return avl_normal_impl(this->k_head.left, mini, maxi, height, e, kc);
			}

			template <typename Entity>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::node_base::height_t
			avl_type_only<Entity>::
			height() const KERBAL_NOEXCEPT
			{
				return node_base::height_of(this->k_head.left);
			}


		//===================
		// private

#	if __cplusplus >= 201103L

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename Entity>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
				!nothrow_while_construct
			>::type
			avl_type_only<Entity>::
			k_try_construct_node_impl(NodeAllocator & alloc, node * p, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				try {
					node_allocator_traits::construct(
						alloc, p, kerbal::utility::in_place_t(),
						kerbal::utility::forward<Args>(args)...
					);
				} catch (...) {
					node_allocator_traits::deallocate_one(alloc, p);
					throw;
				}
			}

			template <typename Entity>
			template <bool nothrow_while_construct, typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
				nothrow_while_construct
			>::type
			avl_type_only<Entity>::
			k_try_construct_node_impl(NodeAllocator & alloc, node * p, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node_allocator_traits::construct(
					alloc, p, kerbal::utility::in_place_t(),
					kerbal::utility::forward<Args>(args)...
				);
			}

			template <typename Entity>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_try_construct_node(NodeAllocator & alloc, node * p, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef kerbal::type_traits::bool_constant<
					noexcept(
						node_allocator_traits::construct(
							alloc, kerbal::utility::declval<node *>(),
							kerbal::utility::in_place_t(),
							kerbal::utility::forward<Args>(args)...
						)
					)
				> nothrow_while_construct;

				k_try_construct_node_impl<nothrow_while_construct::value>(
					alloc, p,
					kerbal::utility::forward<Args>(args)...
				);
			}

#		else // KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename Entity>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_try_construct_node(NodeAllocator & alloc, node * p, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node_allocator_traits::construct(
					alloc, p, kerbal::utility::in_place_t(),
					kerbal::utility::forward<Args>(args)...
				);
			}

#		endif // KERBAL_HAS_EXCEPTIONS_SUPPORT

#	else // __cplusplus >= 201103L

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

#		define FBODY(i) \
			template <typename Entity> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			void \
			avl_type_only<Entity>:: \
			k_try_construct_node(NodeAllocator & alloc, node * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
				try { \
					node_allocator_traits::construct( \
						alloc, p, kerbal::utility::in_place_t() \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
					); \
				} catch (...) { \
					node_allocator_traits::deallocate_one(alloc, p); \
					throw; \
				} \
			} \

#	else // KERBAL_HAS_EXCEPTIONS_SUPPORT

#		define FBODY(i) \
			template <typename Entity> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			void \
			avl_type_only<Entity>:: \
			k_try_construct_node(NodeAllocator & alloc, node * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
				node_allocator_traits::construct( \
					alloc, p, kerbal::utility::in_place_t() \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
				); \
			} \

#	endif // KERBAL_HAS_EXCEPTIONS_SUPPORT

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif // __cplusplus >= 201103L



#	if __cplusplus >= 201103L

			template <typename Entity>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename
			avl_type_only<Entity>::node *
			avl_type_only<Entity>::
			k_build_new_node(NodeAllocator & alloc, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node * p = node_allocator_traits::allocate_one(alloc);

#		if !KERBAL_HAS_EXCEPTIONS_SUPPORT
				if (p == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif // KERBAL_HAS_EXCEPTIONS_SUPPORT

				k_try_construct_node(alloc, p, kerbal::utility::forward<Args>(args)...);
				return p;
			}

#	else // __cplusplus >= 201103L

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

#		define FBODY(i) \
			template <typename Entity> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename \
			avl_type_only<Entity>::node * \
			avl_type_only<Entity>:: \
			k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
				node * p = node_allocator_traits::allocate_one(alloc); \
				k_try_construct_node(alloc, p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				return p; \
			} \

#	else // KERBAL_HAS_EXCEPTIONS_SUPPORT

#		define FBODY(i) \
			template <typename Entity> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename \
			avl_type_only<Entity>::node * \
			avl_type_only<Entity>:: \
			k_build_new_node(NodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
				node * p = node_allocator_traits::allocate_one(alloc); \
				if (p == NULL) { \
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception(); \
				} \
				k_try_construct_node(alloc, p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				return p; \
			} \

#	endif // KERBAL_HAS_EXCEPTIONS_SUPPORT

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif // __cplusplus >= 201103L


#	if __cplusplus >= 201103L

			template <typename Entity>
			template <typename NodeAllocator, typename ... Args>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_reuse_node(NodeAllocator & alloc, node * p, Args && ... args)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				node_allocator_traits::destroy(alloc, p);
				k_try_construct_node(alloc, p, kerbal::utility::forward<Args>(args)...);
			}

#	else // __cplusplus >= 201103L

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
			template <typename Entity> \
			template <typename NodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			void \
			avl_type_only<Entity>:: \
			k_reuse_node(NodeAllocator & alloc, node * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits; \
				node_allocator_traits::destroy(alloc, p); \
				k_try_construct_node(alloc, p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
			} \

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif // __cplusplus >= 201103L



			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_destroy_node(NodeAllocator & alloc, node_base * p_node_base)
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
				typedef typename node_allocator_traits::pointer allocator_pointer_type;

				node * p_node = node::reinterpret_as(p_node_base);
				allocator_pointer_type p_node_act = static_cast<allocator_pointer_type>(p_node);
				node_allocator_traits::destroy(alloc, p_node_act);
				node_allocator_traits::deallocate_one(alloc, p_node_act);
			}


#define AVL_DESTROY 2

#if AVL_DESTROY == 0

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_destroy_node_and_offsprings_impl(
				NodeAllocator & alloc, node_base * start,
				DES_OFF_VER_DEFAULT
			) KERBAL_NOEXCEPT
			{
				if (start == get_avl_vnull_node()) {
					return;
				}

				// p: parent
				// l: left son
				// r: right son
				// u: uncle
				head_node * p = start->as_head();
				head_node * Gg = start->parent;
				while (p != Gg) {
					head_node * u = p->as_node_base()->parent;
					node_base * l = p->left;
					node_base * r = p->as_node_base()->right;
					k_destroy_node(alloc, p->as_node_base());
					if (l != get_avl_vnull_node()) {
						if (r != get_avl_vnull_node()) {
							// l != NULL && r != NULL
							l->parent = r;
							r->parent = u;
						} else {
							// l != NULL && r == NULL
							l->parent = u;
						}
						p = l;
					} else {
						if (r != get_avl_vnull_node()) {
							// l == NULL && r != NULL
							r->parent = u;
							p = r;
						} else {
							// l == NULL && r == NULL
							p = u;
						}
					}
				}
			}

#elif AVL_DESTROY == 1

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_destroy_node_and_offsprings_impl(
				NodeAllocator & alloc, node_base * start,
				DES_OFF_VER_DEFAULT
			) KERBAL_NOEXCEPT
			{
				if (start == get_avl_vnull_node()) {
					return;
				}

				// p: parent
				// l: left son
				// r: right son
				// u: uncle
				head_node * p = start->as_head();
				head_node * Gg = start->parent;
				head_node * u = Gg;
				while (p != Gg) {
					node_base * l = p->left;
					node_base * r = p->as_node_base()->right;
					k_destroy_node(alloc, p->as_node_base());
					if (l != get_avl_vnull_node()) {
						if (r != get_avl_vnull_node()) {
							// l != NULL && r != NULL
							r->parent = u;
							u = r;
						} else {
							// l != NULL && r == NULL
							l->parent = u;
						}
						p = l;
					} else {
						if (r != get_avl_vnull_node()) {
							// l == NULL && r != NULL
							r->parent = u;
							p = r;
						} else {
							// l == NULL && r == NULL
							p = u;
							u = u->as_node_base()->parent;
						}
					}
				}
			}

#else

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_destroy_node_and_offsprings_impl(
				NodeAllocator & alloc, node_base * start,
				DES_OFF_VER_DEFAULT ver
			) KERBAL_NOEXCEPT
			{
				while (start != get_avl_vnull_node()) {
					k_destroy_node_and_offsprings_impl(alloc, start->left, ver);
					node_base * right = start->right;
					k_destroy_node(alloc, start);
					start = right;
				}
			}

#endif

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_destroy_node_and_offsprings_impl(
				NodeAllocator & alloc, node_base * start,
				DES_OFF_VER_DESTROY_BUT_NO_DEALLOCATE ver
			) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;

				while (start != get_avl_vnull_node()) {
					k_destroy_node_and_offsprings_impl(alloc, start->left, ver);
					node_base * right = start->right;

					node * p_node = node::reinterpret_as(start);
					node_allocator_traits::destroy(alloc, p_node);

					start = right;
				}
			}

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_destroy_node_and_offsprings_impl(
				NodeAllocator & /*alloc*/, node_base * /*start*/,
				DES_OFF_VER_NO_DESTROY
			) KERBAL_NOEXCEPT
			{
			}

			template <typename Entity>
			template <typename NodeAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_destroy_node_and_offsprings(
				NodeAllocator & alloc,
				node_base * start
			)
			{
				k_destroy_node_and_offsprings_impl(alloc, start, DES_OFF_VER_DEFAULT());
			}

			template <typename Entity>
			template <typename T, typename UpstreamAllocator>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_destroy_node_and_offsprings(
				kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & alloc,
				node_base * start
			)
			{
				typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<Entity>::IS_TRUE::value,
					DES_OFF_VER_NO_DESTROY,
					DES_OFF_VER_DESTROY_BUT_NO_DEALLOCATE
				>::type VER;
				k_destroy_node_and_offsprings_impl(alloc, start, VER());
			}


#		if __cplusplus >= 201703L
#			if __has_include(<memory_resource>)

			template <typename Entity>
			template <typename Node>
			KERBAL_CONSTEXPR20
			void
			avl_type_only<Entity>::
			k_destroy_node_and_offsprings(
				std::pmr::polymorphic_allocator<Node> & alloc,
				node_base * start
			)
				KERBAL_CONDITIONAL_NOEXCEPT(
					(
						!kerbal::type_traits::try_test_is_trivially_destructible<Entity>::IS_TRUE::value ?
						noexcept(k_destroy_node_and_offsprings_impl(alloc, start, DES_OFF_VER_DESTROY_BUT_NO_DEALLOCATE())) :
						true
					) &&
					noexcept(k_destroy_node_and_offsprings_impl(alloc, start, DES_OFF_VER_DEFAULT()))
				)
			{
				if (typeid(*alloc.resource()) == typeid(std::pmr::monotonic_buffer_resource)) {
					if constexpr (!kerbal::type_traits::try_test_is_trivially_destructible<Entity>::IS_TRUE::value) {
						k_destroy_node_and_offsprings_impl(alloc, start, DES_OFF_VER_DESTROY_BUT_NO_DEALLOCATE());
					}
				} else {
					k_destroy_node_and_offsprings_impl(alloc, start, DES_OFF_VER_DEFAULT());
				}
			}

#			endif
#		endif

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_BASE_IMPL_HPP
