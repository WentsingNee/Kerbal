/**
 * @file       rb_base.impl.hpp
 * @brief
 * @date       2023-12-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_IMPL_HPP

#include <kerbal/compare/binary_type_compare.hpp>


#include <kerbal/container/detail/rb_base/rb_base.decl.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			KERBAL_CONSTEXPR14
			inline
			void
			rb_type_unrelated::
			rb_adjust_RRb(rb_node_base * g, rb_node_base * p) KERBAL_NOEXCEPT
			{
				bst_head_node * a = g->parent;
				bst_node_base::left_rotate(g, p);
				if (g == a->left) {
					a->left = p;
				} else { // g == a->right
					a->as_node_base()->right = p;
				}
				p->parent = a;
				p->set_black();
				g->set_red();
			}

			KERBAL_CONSTEXPR14
			inline
			void
			rb_type_unrelated::
			rb_adjust_LLb(rb_node_base * g, rb_node_base * p) KERBAL_NOEXCEPT
			{
				bst_head_node * a = g->parent;
				bst_node_base::right_rotate(g, p);
				if (g == a->left) {
					a->left = p;
				} else { // g == a->right
					a->as_node_base()->right = p;
				}
				p->parent = a;
				p->set_black();
				g->set_red();
			}

			KERBAL_CONSTEXPR14
			inline
			void
			rb_type_unrelated::
			rb_adjust(rb_node_base * n, rb_node_base * p) KERBAL_NOEXCEPT
			{
				while (n != &this->k_head) {
					if (n == this->k_head.left) {
						n->set_black();
						return;
					}
					if (rb_node_base::is_black(p)) {
						return;
					}

					rb_node_base * g = rb_node_base::as(p->parent);
					rb_node_base * u = NULL;
					if (p == g->left) {
						u = rb_node_base::as(g->right);
						if (n == p->left) { // LL
							if (rb_node_base::is_black(u)) { // LLb
								rb_adjust_LLb(g, p);
								return;
							}
							// LLr
						} else { // LR
							if (rb_node_base::is_black(u)) { // LRb
								bst_node_base::left_rotate(p, n);
								g->left = n;
								n->parent = g;
								// LLb
								rb_adjust_LLb(g, n);
								return;
							}
							// LRr
						}
					} else {
						u = rb_node_base::as(g->left);
						if (n == p->left) { // RL
							if (rb_node_base::is_black(u)) { // RLb
								bst_node_base::right_rotate(p, n);
								g->right = n;
								n->parent = g;
								// RRb
								rb_adjust_RRb(g, n);
								return;
							}
							// RLr
						} else { // RR
							if (rb_node_base::is_black(u)) { // RRb
								rb_adjust_RRb(g, p);
								return;
							}
							// RRr
						}
					}

					p->set_black();
					g->set_red();
					u->set_black();
					n = g;
					p = rb_node_base::as(n->parent);
				}
			}

			KERBAL_CONSTEXPR14
			inline
			typename
			rb_type_unrelated::bst_head_node *
			rb_type_unrelated::
			k_unhook_node_and_get_successor(rb_node_base * n) KERBAL_NOEXCEPT
			{
//				if (n == NULL) {
//					return;
//				}
				bst_head_node * next = n->inorder_next();
				if (n->left != get_rb_vnull_node() && n->right != get_rb_vnull_node()) { // two sons
					rb_node_base * replacee = rb_node_base::as(n->right->leftest_offspring());
					k_unhook_node_replace(n, replacee);
				}
				if (n->left != get_rb_vnull_node() && n->right == get_rb_vnull_node()) { // only left son
					bst_head_node * n_parent = n->parent;
					if (n == n_parent->left) {
						n_parent->left = n->left;
					} else {
						n_parent->as_node_base()->right = n->left;
					}
					rb_node_base::as(n->left)->set_black();
					--this->k_cnt;
					return next;
				}
				if (n->left == get_rb_vnull_node() && n->right != get_rb_vnull_node()) { // only right son
					bst_head_node * n_parent = n->parent;
					if (n == n_parent->left) {
						n_parent->left = n->right;
					} else {
						n_parent->as_node_base()->right = n->right;
					}
					rb_node_base::as(n->right)->set_black();
					--this->k_cnt;
					return next;
				}
				// leaf
				bst_head_node * n_parent = n->parent;
				if (n->color == RED::value) { // n is red
					// not use !rb_node_base::is_black(n) because n is always not null
					if (n == n_parent->left) {
						n_parent->left = n->right;
						set_parent_ignore_null(n->right, n_parent);
					} else {
						throw 0;
					}
				} else {
					printf("b\n");
					throw 0;
				}
				--this->k_cnt;
				return next;
			}


		//===================
		// iterator

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::iterator
			rb_type_only<T>::
			begin() KERBAL_NOEXCEPT
			{
				return iterator(this->k_head.leftest_offspring());
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::const_iterator
			rb_type_only<T>::
			begin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_head.leftest_offspring());
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::const_iterator
			rb_type_only<T>::
			cbegin() const KERBAL_NOEXCEPT
			{
				return this->begin();
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::iterator
			rb_type_only<T>::
			end() KERBAL_NOEXCEPT
			{
				return iterator(&this->k_head);
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::const_iterator
			rb_type_only<T>::
			end() const KERBAL_NOEXCEPT
			{
				return const_iterator(&this->k_head);
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::const_iterator
			rb_type_only<T>::
			cend() const KERBAL_NOEXCEPT
			{
				return this->end();
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::reverse_iterator
			rb_type_only<T>::
			rbegin() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->end());
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::const_reverse_iterator
			rb_type_only<T>::
			rbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->end());
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::const_reverse_iterator
			rb_type_only<T>::
			crbegin() const KERBAL_NOEXCEPT
			{
				return this->rbegin();
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::reverse_iterator
			rb_type_only<T>::
			rend() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->begin());
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::const_reverse_iterator
			rb_type_only<T>::
			rend() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->begin());
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::const_reverse_iterator
			rb_type_only<T>::
			crend() const KERBAL_NOEXCEPT
			{
				return this->rend();
			}


			template <typename T>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::iterator
			rb_type_only<T>::
			k_hook_node(Extract & e, KeyCompare & kc, node * n)
			{
				rb_node_base * p_base = rb_node_base::as(this->k_head.left);

				if (p_base == get_rb_vnull_node()) {
					this->k_head.left = n;
					n->parent = &this->k_head;
					n->set_black();
				} else {
					node * p = node::reinterpret_as(p_base);
					{
						const typename Extract::key_type & n_key = e(n->member());
						while (true) {
							const typename Extract::key_type & p_key = e(p->member());
							if (kc(n_key, p_key)) {
								if (p->left == get_rb_vnull_node()) {
									p->left = n;
									break;
								}
								p = node::reinterpret_as(rb_node_base::as(p->left));
							} else {
								if (p->right == get_rb_vnull_node()) {
									p->right = n;
									break;
								}
								p = node::reinterpret_as(rb_node_base::as(p->right));
							}
						}
					}
					n->parent = p;
					if (p->color == RED::value) {
						rb_adjust(n, p);
					}
				}
				++this->k_cnt;
				return iterator(n);
			}

			template <typename T>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::unique_insert_r
			rb_type_only<T>::
			k_hook_node_unique(Extract & e, KeyCompare & kc, node * n)
			{
				rb_node_base * p_base = rb_node_base::as(this->k_head.left);

				if (p_base == get_rb_vnull_node()) {
					this->k_head.left = n;
					n->parent = &this->k_head;
					n->set_black();
				} else {
					node * p = node::reinterpret_as(p_base);
					{
						const typename Extract::key_type & n_key = e(n->member());
						while (true) {
							const typename Extract::key_type & p_key = e(p->member());
							if (kc(n_key, p_key)) {
								if (p->left == get_rb_vnull_node()) {
									p->left = n;
									break;
								}
								p = node::reinterpret_as(rb_node_base::as(p->left));
							} else if (kc(p_key, n_key)) {
								if (p->right == get_rb_vnull_node()) {
									p->right = n;
									break;
								}
								p = node::reinterpret_as(rb_node_base::as(p->right));
							} else {
								return unique_insert_r(iterator(p), false);
							}
						}
					}
					n->parent = p;
					if (p->color == RED::value) {
						rb_adjust(n, p);
					}
				}
				++this->k_cnt;
				return unique_insert_r(iterator(n), true);
			}

			template <typename T>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::rb_normal_result_t
			rb_type_only<T>::
			rb_normal_impl(
				Extract & e, KeyCompare & kc,
				const rb_node_base * pbase,
				const value_type * & mini, const value_type * & maxi,
				std::size_t & nodes_cnt, std::size_t & black_cnt
			)
			{
				if (pbase == get_rb_vnull_node()) {
					mini = NULL;
					maxi = NULL;
					black_cnt = 1;
					return RB_NORMAL_RESULT_CORRECT;
				}

				++nodes_cnt;

				const node * pnode = node::reinterpret_as(pbase);

				// Parent Check

				if (pnode->left != get_rb_vnull_node()) {
					if (pnode->left->parent != pnode) {
						return RB_NORMAL_RESULT_BAD_PARENT;
					}
				}

				if (pnode->right != get_rb_vnull_node()) {
					if (pnode->right->parent != pnode) {
						return RB_NORMAL_RESULT_BAD_PARENT;
					}
				}

				// Recursion on left
				const value_type * lmini = NULL;
				const value_type * lmaxi = NULL;
				std::size_t lblack_cnt = -1;
				rb_normal_result_t lresult = rb_normal_impl(e, kc, rb_node_base::as(pnode->left), lmini, lmaxi, nodes_cnt, lblack_cnt);
				if (lresult != RB_NORMAL_RESULT_CORRECT) {
					return lresult;
				}

				// Recursion on right
				const value_type * rmini = NULL;
				const value_type * rmaxi = NULL;
				std::size_t rblack_cnt = -1;
				rb_normal_result_t rresult = rb_normal_impl(e, kc, rb_node_base::as(pnode->right), rmini, rmaxi, nodes_cnt, rblack_cnt);
				if (rresult != RB_NORMAL_RESULT_CORRECT) {
					return rresult;
				}

				// BST Check
				const value_type & mid_value = pnode->member();
				if (lmaxi != NULL) {
					if (!kc(e(*lmaxi), e(mid_value))) {
						return RB_NORMAL_RESULT_BST_INVALID;
					}
				}

				if (rmini != NULL) {
					if (!kc(e(mid_value), e(*rmini))) {
						return RB_NORMAL_RESULT_BST_INVALID;
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


				// RB Check
				if (lblack_cnt != rblack_cnt) {
					return RB_NORMAL_RESULT_BAD_BLACK_CNT_IN_PATH;
				}

				if (rb_node_base::is_black(pnode)) { // p is black
					black_cnt = 1 + lblack_cnt;
				} else { // p is red
					black_cnt = lblack_cnt;
					if (!rb_node_base::is_black(rb_node_base::as(pnode->left))) { // p->left is red
						return RB_NORMAL_RESULT_NEIBOUR_RED;
					}
					if (!rb_node_base::is_black(rb_node_base::as(pnode->right))) { // p->right is red
						return RB_NORMAL_RESULT_NEIBOUR_RED;
					}
				}

				return RB_NORMAL_RESULT_CORRECT;
			}


			template <typename T>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename
			rb_type_only<T>::rb_normal_result_t
			rb_type_only<T>::
			rb_normal(Extract & e, KeyCompare & kc) const
			{
				const rb_node_base * root = rb_node_base::as(this->k_head.left);

				if (root == get_rb_vnull_node()) {
					return RB_NORMAL_RESULT_CORRECT;
				}

				if (root->color == RED::value) {
					return RB_NORMAL_RESULT_ROOT_NOT_BLACK;
				}
				const value_type * mini = NULL;
				const value_type * maxi = NULL;
				std::size_t nodes_cnt = 0;
				std::size_t black_cnt = 0;

				rb_normal_result_t result = rb_normal_impl(e, kc, root, mini, maxi, nodes_cnt, black_cnt);
				if (result != RB_NORMAL_RESULT_CORRECT) {
					return result;
				}
				if (this->k_cnt != nodes_cnt) { // node count accumulation may broken ahead
					return RB_NORMAL_RESULT_BAD_NODES_CNT;
				}
				return RB_NORMAL_RESULT_CORRECT;
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_IMPL_HPP
