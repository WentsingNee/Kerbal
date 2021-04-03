/**
 * @file       binary_search_tree_base.hpp
 * @brief
 * @date       2020-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_BASE_HPP

#include <kerbal/container/detail/bst_base/binary_search_tree.fwd.hpp>
#include <kerbal/container/detail/bst_base/binary_search_tree_node.hpp>
#include <kerbal/container/detail/bst_base/binary_search_tree_iterator.hpp>

#include <kerbal/iterator/reverse_iterator.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Extract, typename KeyCompare>
			class bst
			{
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

					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef kerbal::container::detail::bst_iter<value_type>		iterator;
					typedef kerbal::container::detail::bst_kiter<value_type>	const_iterator;
					typedef kerbal::iterator::reverse_iterator<iterator>		reverse_iterator;
					typedef kerbal::iterator::reverse_iterator<const_iterator>	const_reverse_iterator;

				protected:
					typedef kerbal::container::detail::bst_head_node			head_node;
					typedef kerbal::container::detail::bst_node_base			node_base;
					typedef kerbal::container::detail::bst_node<value_type>		node;

				protected:

					kerbal::container::detail::bst_head_node head;

					KeyCompare kc;

				public:

					~bst()
					{
						this->clear();
					}

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
					reverse_iterator rbegin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reverse_iterator rend() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator rend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator crend() const KERBAL_NOEXCEPT;

				//===================
				//insert

					iterator insert(const_reference src)
					{
						node * v = this->__build_new_node(src);
						if (head.left == NULL) {
							head.left = v;
							v->parent = static_cast<node_base*>(&head);
						} else {
							node_base * p_base = head.left;
							Extract e;

							while (true) {
								if (kc(e(v->value), e(p_base->reinterpret_as<value_type>().value))) { // src < p->value
									if (p_base->left == NULL) {
										p_base->left = v;
										break;
									}
									p_base = p_base->left;
								} else {
									if (p_base->right == NULL) {
										p_base->right = v;
										break;
									}
									p_base = p_base->right;
								}
							}
							v->parent = p_base;
						}
						return iterator(v);
					}

				//===================
				//erase

					KERBAL_CONSTEXPR20
					void clear()
					{
						__destroy_node_and_offsprings(head.left);
						head.left = NULL;
					}

				//===================
				//private

					KERBAL_CONSTEXPR20
					void __destroy_node_and_offsprings(node_base * p);

					KERBAL_CONSTEXPR20
					static const node_base * __leftest_offspring(const node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					static node_base * __leftest_offspring(node_base * p) KERBAL_NOEXCEPT;

					template <typename ... Args>
					node * __build_new_node(Args&& ... args)
					{
						return new node(kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
					}

					void __destroy_node(node_base * p_base)
					{
						node * p = &p_base->reinterpret_as<value_type>();
//						std::cout << "free: " << p->value << std::endl;
						delete p;
					}

					static void __left_roate(node_base * p)
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
						node_base * g = p->parent;
						node_base * a = g->parent;

						g->right = l;
						if (l) {
							l->parent = g;
						}

						p->left = g;
						g->parent = p;

						if (a->left == g) {
							a->left = p;
						} else {
							a->right = p;
						}
						p->parent = a;
					}

					static void __right_roate(node_base * p)
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
						node_base * g = p->parent;
						node_base * a = g->parent;

						g->left = r;
						if (r) {
							r->parent = g;
						}

						p->right = g;
						g->parent = p;

						if (a->left == g) {
							a->left = p;
						} else {
							a->right = p;
						}
						p->parent = a;
					}

					template <typename F>
					void pre_order_impl(node_base * p_base, F f) const
					{
						node * p = static_cast<node*>(p_base);
						if (p == NULL) {
							return;
						}
						f(p->value);
						pre_order_impl(p->left, f);
						pre_order_impl(p->right, f);
					}

					template <typename F>
					void pre_order(F f) const
					{
						node_base * p = static_cast<node_base *>(head.left);
						pre_order_impl(p, f);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/binary_search_tree_base.impl.hpp>

#endif // KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_BASE_HPP
