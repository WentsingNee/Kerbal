/**
 * @file       bst_node.hpp
 * @brief
 * @date       2023-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_BST_BASE_BST_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_BST_BASE_BST_NODE_HPP

#include <kerbal/container/detail/bst_base/bst.fwd.hpp>
#include <kerbal/container/detail/avl_base/avl_base.fwd.hpp>
#include <kerbal/container/detail/rb_base/rb_base.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename VNULL_HELPER>
			class bst_head_node
			{
				private:
					friend class kerbal::container::detail::bst_node_base<VNULL_HELPER>;

					friend class kerbal::container::detail::bst_iter_type_unrelated<VNULL_HELPER>;

					friend class kerbal::container::detail::bst_kiter_type_unrelated<VNULL_HELPER>;

				// avl-tree

					friend class kerbal::container::detail::avl_node_base;

					friend class kerbal::container::detail::avl_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				// rb-tree

					friend class kerbal::container::detail::rb_node_base;

					friend class kerbal::container::detail::rb_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::rb_type_only;

				protected:
					typedef kerbal::container::detail::bst_node_base<VNULL_HELPER> bst_node_base;
					bst_node_base * left;

				protected:
					KERBAL_CONSTEXPR
					explicit bst_head_node(bst_node_base * vnull) KERBAL_NOEXCEPT :
						left(vnull)
					{
					}

					KERBAL_CONSTEXPR14
					inline
					bst_node_base *
					as_node_base() KERBAL_NOEXCEPT
					{
						return static_cast<bst_node_base *>(this);
					}

					KERBAL_CONSTEXPR
					inline
					bst_node_base const *
					as_node_base() const KERBAL_NOEXCEPT
					{
						return static_cast<bst_node_base const *>(this);
					}

					KERBAL_CONSTEXPR14
					inline
					bst_head_node const *
					leftest_offspring() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					bst_head_node *
					leftest_offspring() KERBAL_NOEXCEPT
					{
						return const_cast<bst_head_node *>(
							static_cast<bst_head_node const *>(this)->leftest_offspring()
						);
					}

					KERBAL_CONSTEXPR14
					inline
					bst_head_node const *
					inorder_prev() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					inline
					bst_head_node *
					inorder_prev() KERBAL_NOEXCEPT
					{
						return const_cast<bst_head_node *>(
							static_cast<bst_head_node const *>(this)->inorder_prev()
						);
					}

			};



			template <typename VNULL_HELPER>
			class bst_node_base :
				protected kerbal::container::detail::bst_head_node<VNULL_HELPER>
			{
				private:
					friend class kerbal::container::detail::bst_head_node<VNULL_HELPER>;

					friend class kerbal::container::detail::bst_iter_type_unrelated<VNULL_HELPER>;

					friend class kerbal::container::detail::bst_kiter_type_unrelated<VNULL_HELPER>;

				// avl-tree

					friend class kerbal::container::detail::avl_node_base;

					friend class kerbal::container::detail::avl_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				// rb-tree

					friend class kerbal::container::detail::rb_node_base;

					friend class kerbal::container::detail::rb_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::rb_type_only;

				protected:
					typedef class kerbal::container::detail::bst_head_node<VNULL_HELPER> bst_head_node;

					bst_head_node * parent;
					bst_node_base * right;

				protected:
					KERBAL_CONSTEXPR
					explicit bst_node_base(bst_node_base * vnull) KERBAL_NOEXCEPT :
						bst_head_node(vnull), parent(NULL), right(vnull)
					{
					}

					KERBAL_CONSTEXPR14
					bst_node_base const *
					rightest_offspring() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					bst_node_base *
					rightest_offspring() KERBAL_NOEXCEPT
					{
						return const_cast<bst_node_base *>(
							static_cast<bst_node_base const *>(this)->rightest_offspring()
						);
					}

					KERBAL_CONSTEXPR14
					bst_head_node const *
					inorder_next() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					bst_head_node *
					inorder_next() KERBAL_NOEXCEPT
					{
						return const_cast<bst_head_node *>(
							static_cast<bst_node_base const *>(this)->inorder_next()
						);
					}

					KERBAL_CONSTEXPR14
					bst_head_node const *
					postorder_next(bst_head_node const * head) const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					bst_head_node*
					postorder_next(bst_head_node const * head) KERBAL_NOEXCEPT
					{
						return const_cast<bst_head_node *>(
							static_cast<bst_node_base const *>(this)->postorder_next(head)
						);
					}

					KERBAL_CONSTEXPR14
					friend inline
					void set_parent_ignore_null(bst_node_base * p_base, bst_head_node * p_parent)
					{
#	if KERBAL_AVL_ENABLE_VNULL

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							if (p_base == VNULL_HELPER::get_vnull()) {
								return ;
							}
						}
#		endif

						p_base->parent = p_parent;
#	else
						if (p_base != VNULL_HELPER::get_vnull()) {
							p_base->parent = p_parent;
						}
#	endif
					}


					KERBAL_CONSTEXPR14
					static
					void left_rotate(bst_node_base * g, bst_node_base * p) KERBAL_NOEXCEPT
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

						bst_node_base * l = p->left;

						g->right = l;
						set_parent_ignore_null(l, g);

						p->left = g;
						g->parent = p;
					}

					KERBAL_CONSTEXPR14
					static
					void right_rotate(bst_node_base * g, bst_node_base * p) KERBAL_NOEXCEPT
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

						bst_node_base * r = p->right;

						g->left = r;
						set_parent_ignore_null(r, g);

						p->right = g;
						g->parent = p;
					}

			};



			template <typename VNULL_HELPER>
			KERBAL_CONSTEXPR14
			inline
			bst_head_node<VNULL_HELPER> const *
			bst_head_node<VNULL_HELPER>::leftest_offspring() const KERBAL_NOEXCEPT
			{
				bst_head_node const * current = this;
				bst_head_node const * offspring = current->left;
				while (offspring != VNULL_HELPER::get_vnull()) {
					current = offspring;
					offspring = current->left;
				}
				return current;
			}

			template <typename VNULL_HELPER>
			KERBAL_CONSTEXPR14
			inline
			bst_node_base<VNULL_HELPER> const *
			bst_node_base<VNULL_HELPER>::rightest_offspring() const KERBAL_NOEXCEPT
			{
				bst_node_base const * current = this;
				bst_node_base const * offspring = current->right;
				while (offspring != VNULL_HELPER::get_vnull()) {
					current = offspring;
					offspring = current->right;
				}
				return current;
			}

			template <typename VNULL_HELPER>
			KERBAL_CONSTEXPR14
			inline
			bst_head_node<VNULL_HELPER> const *
			bst_head_node<VNULL_HELPER>::inorder_prev() const KERBAL_NOEXCEPT
			{
				bst_head_node const * current = this;
				if (current->left == VNULL_HELPER::get_vnull()) {
					bst_head_node const * ancestor = current->as_node_base()->parent;
					while (current == ancestor->left) { // warning: head doesn't have right domain!
						// is parent's right son
						current = ancestor;
						ancestor = ancestor->as_node_base()->parent;
					}
					// is parent's left son
					current = ancestor;
				} else {
					current = current->left->rightest_offspring();
				}
				return current;
			}

			template <typename VNULL_HELPER>
			KERBAL_CONSTEXPR14
			inline
			typename
			bst_node_base<VNULL_HELPER>::bst_head_node const *
			bst_node_base<VNULL_HELPER>::inorder_next() const KERBAL_NOEXCEPT
			{
				bst_head_node const * current = this;
				if (current->as_node_base()->right == VNULL_HELPER::get_vnull()) {
					bst_head_node const * ancestor = current->as_node_base()->parent;
					while (current != ancestor->left) { // warning: head doesn't have right domain!
						// is parent's right son
						current = ancestor;
						ancestor = current->as_node_base()->parent;
					}
					// is parent's left son
					current = ancestor;
				} else {
					current = current->as_node_base()->right->leftest_offspring();
				}
				return current;
			}

			template <typename VNULL_HELPER>
			KERBAL_CONSTEXPR14
			inline
			typename
			bst_node_base<VNULL_HELPER>::bst_head_node const *
			bst_node_base<VNULL_HELPER>::postorder_next(bst_head_node const * head) const KERBAL_NOEXCEPT
			{
				bst_node_base const * current = this;
				if (current == parent->left) {
					if (parent == head) {
						return head;
					}
					bst_node_base const * brother = parent->as_node_base()->right;
					if (brother == VNULL_HELPER::get_vnull()) {
						return parent;
					}
					brother = static_cast<bst_node_base const *>(brother->leftest_offspring());
					if (brother->right != VNULL_HELPER::get_vnull()) { // correct only under avl
						return brother->right;
					}
					return brother;
				} else {
					return parent;
				}
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_BST_BASE_BST_NODE_HPP
