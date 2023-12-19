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

#include "../../../compare/binary_type_compare.hpp"


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
			void rb_type_unrelated::rb_adjust_RRb(rb_node_base * g, rb_node_base * p) KERBAL_NOEXCEPT
			{
				bst_node_base * a = g->parent->as_node_base();
				bst_node_base::left_rotate(g, p);
				if (g == a->left) {
					a->left = p;
				} else { // g == a->right
					a->right = p;
				}
				p->parent = a;
				p->set_black();
				g->set_red();
			}

			KERBAL_CONSTEXPR14
			inline
			void rb_type_unrelated::rb_adjust_LLb(rb_node_base * g, rb_node_base * p) KERBAL_NOEXCEPT
			{
				bst_node_base * a = g->parent->as_node_base();
				bst_node_base::right_rotate(g, p);
				if (g == a->left) {
					a->left = p;
				} else { // g == a->right
					a->right = p;
				}
				p->parent = a;
				p->set_black();
				g->set_red();
			}

			KERBAL_CONSTEXPR14
			inline
			void rb_type_unrelated::rb_adjust(rb_node_base * n, rb_node_base * p) KERBAL_NOEXCEPT
			{
				while (n != &this->k_head) {
					if (n == this->k_head.left) {
						n->set_black();
						return;
					}
					if (rb_node_base::is_black(p)) {
						return;
					}

					rb_node_base * g = as_rb_node_base(p->parent);
					rb_node_base * u = NULL;
					if (p == g->left) {
						u = as_rb_node_base(g->right);
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
						u = as_rb_node_base(g->left);
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
					p = as_rb_node_base(n->parent);
				}
			}


			template <typename T>
			template <typename Extract, typename KeyCompare>
			KERBAL_CONSTEXPR14
			typename rb_type_only<T>::unique_insert_r
			rb_type_only<T>::k_hook_node_unique(Extract & e, KeyCompare & kc, node * n)
			{
				rb_node_base * p_base = as_rb_node_base(this->k_head.left);

				if (p_base == get_rb_vnull_node()) {
					this->k_head.left = n;
					n->parent = &this->k_head;
					n->set_black();
					++this->k_cnt;
					return unique_insert_r(n, true);
				}

				const typename Extract::key_type & n_key = e(n->member());

				node * p = static_cast<node *>(p_base);

				while (true) {
					const typename Extract::key_type & p_key = e(p->member());
					if (kc(n_key, p_key)) {
						if (p->left == get_rb_vnull_node()) {
							p->left = n;
							break;
						}
						p = static_cast<node *>(as_rb_node_base(p->left));
					} else if (kc(p_key, n_key)) {
						if (p->right == get_rb_vnull_node()) {
							p->right = n;
							break;
						}
						p = static_cast<node *>(as_rb_node_base(p->right));
					} else {
						delete n;
						return unique_insert_r(p, false);
					}
				}
				n->parent = p;
				++this->k_cnt;
				if (rb_node_base::is_black(p)) {
					return unique_insert_r(n, true);
				}
				rb_adjust(n, p);
				return unique_insert_r(n, true);
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename rb_type_only<T>::rb_normal_result_t
			rb_type_only<T>::rb_normal_impl(const bst_node_base * pbase, const value_type * & mini, const value_type * & maxi, std::size_t & nodes_cnt, std::size_t & black_cnt)
			{
				if (pbase == get_rb_vnull_node()) {
					mini = NULL;
					maxi = NULL;
					black_cnt = 1;
					return RB_NORMAL_RESULT_CORRECT;
				}

				++nodes_cnt;

				const rb_node_base * prb = as_rb_node_base(pbase);
				const node * pnode = static_cast<const node *>(prb);

				// Parent Check

				if (pbase->left != get_rb_vnull_node()) {
					if (pbase->left->parent != pbase) {
						return RB_NORMAL_RESULT_BAD_PARENT;
					}
				}

				if (pbase->right != get_rb_vnull_node()) {
					if (pbase->right->parent != pbase) {
						return RB_NORMAL_RESULT_BAD_PARENT;
					}
				}

				// Recursion on left
				const value_type * lmini = NULL;
				const value_type * lmaxi = NULL;
				std::size_t lblack_cnt = -1;
				rb_normal_result_t lresult = rb_normal_impl(pnode->left, lmini, lmaxi, nodes_cnt, lblack_cnt);
				if (lresult != RB_NORMAL_RESULT_CORRECT) {
					return lresult;
				}

				// Recursion on right
				const value_type * rmini = NULL;
				const value_type * rmaxi = NULL;
				std::size_t rblack_cnt = -1;
				rb_normal_result_t rresult = rb_normal_impl(pnode->right, rmini, rmaxi, nodes_cnt, rblack_cnt);
				if (rresult != RB_NORMAL_RESULT_CORRECT) {
					return rresult;
				}

				kerbal::container::identity_extractor<T> e;
				kerbal::compare::binary_type_less<void, void> kc;

				// BST Check
				const value_type & mid_value = static_cast<const node *>(pbase)->member();
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

				if (rb_node_base::is_black(pbase)) { // p is black
					black_cnt = 1 + lblack_cnt;
				} else { // p is red
					black_cnt = lblack_cnt;
					if (!rb_node_base::is_black(pbase->left)) { // p->left is red
						return RB_NORMAL_RESULT_NEIBOUR_RED;
					}
					if (!rb_node_base::is_black(pbase->right)) { // p->right is red
						return RB_NORMAL_RESULT_NEIBOUR_RED;
					}
				}

				return RB_NORMAL_RESULT_CORRECT;
			}


			template <typename T>
			KERBAL_CONSTEXPR14
			typename rb_type_only<T>::rb_normal_result_t
			rb_type_only<T>::rb_normal() const
			{
				if (this->k_head.left == NULL) {
					return RB_NORMAL_RESULT_CORRECT;
				}
				const bst_node_base * root = this->k_head.left;
				if (!rb_node_base::is_black(root)) {
					return RB_NORMAL_RESULT_ROOT_NOT_BLACK;
				}
				const value_type * mini = NULL;
				const value_type * maxi = NULL;
				std::size_t nodes_cnt = 0;
				std::size_t black_cnt = 0;
				rb_normal_result_t result = rb_normal_impl(root, mini, maxi, nodes_cnt, black_cnt);
				if (this->k_cnt != nodes_cnt) {
					return RB_NORMAL_RESULT_BAD_NODES_CNT;
				}
				return result;
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_IMPL_HPP
