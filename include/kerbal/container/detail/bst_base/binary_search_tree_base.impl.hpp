/**
 * @file       binary_search_tree_base.impl.hpp
 * @brief
 * @date       2020-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_BASE_IMPL_HPP

#include <kerbal/container/detail/bst_base/binary_search_tree_base.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			//===================
			//iterator

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::iterator
			bst<Entity, Key, KeyCompare, Extract>::begin() KERBAL_NOEXCEPT
			{
				node_base * h = static_cast<node_base*>(&head);
				return iterator(__leftest_offspring(h));
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::iterator
			bst<Entity, Key, KeyCompare, Extract>::end() KERBAL_NOEXCEPT
			{
				return iterator(static_cast<node_base*>(&head));
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::const_iterator
			bst<Entity, Key, KeyCompare, Extract>::begin() const KERBAL_NOEXCEPT
			{
				return this->cbegin();
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::const_iterator
			bst<Entity, Key, KeyCompare, Extract>::end() const KERBAL_NOEXCEPT
			{
				return const_iterator(static_cast<const node_base*>(&head));
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::const_iterator
			bst<Entity, Key, KeyCompare, Extract>::cbegin() const KERBAL_NOEXCEPT
			{
				const node_base * h = static_cast<const node_base*>(&head);
				return const_iterator(__leftest_offspring(h));
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::const_iterator
			bst<Entity, Key, KeyCompare, Extract>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(static_cast<const node_base*>(&head));
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::reverse_iterator
			bst<Entity, Key, KeyCompare, Extract>::rbegin() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->end());
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::reverse_iterator
			bst<Entity, Key, KeyCompare, Extract>::rend() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->begin());
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::const_reverse_iterator
			bst<Entity, Key, KeyCompare, Extract>::rbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->end());
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::const_reverse_iterator
			bst<Entity, Key, KeyCompare, Extract>::rend() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->begin());
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::const_reverse_iterator
			bst<Entity, Key, KeyCompare, Extract>::crbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->cend());
			}

			//===================
			//private

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			void bst<Entity, Key, KeyCompare, Extract>::__destroy_node_and_offsprings(node_base * p)
			{
				// p: parent
				// l: left son
				// r: right son
				// g: grand parent
				while (p != &head) {
					node_base * g = p->parent;
					node_base * l = p->left;
					node_base * r = p->right;
					if (l != NULL) {
						if (r != NULL) {
							// l != NULL && r != NULL
							l->parent = r;
							r->parent = g;
							this->__destroy_node(p);
							p = l;
						} else {
							// l != NULL && r == NULL
							l->parent = g;
							this->__destroy_node(p);
							p = l;
						}
					} else {
						if (r != NULL) {
							// l == NULL && r != NULL
							r->parent = g;
							this->__destroy_node(p);
							p = r;
						} else {
							// l == NULL && r == NULL
							this->__destroy_node(p);
							p = g;
						}
					}
				}
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			const typename bst<Entity, Key, KeyCompare, Extract>::node_base *
			bst<Entity, Key, KeyCompare, Extract>::__leftest_offspring(const node_base * p) KERBAL_NOEXCEPT
			{
				node_base * l = p->left;
				while (l != NULL) {
					p = l;
					l = p->left;
				}
				return p;
			}

			template <typename Entity, typename Key, typename KeyCompare, typename Extract>
			KERBAL_CONSTEXPR20
			typename bst<Entity, Key, KeyCompare, Extract>::node_base *
			bst<Entity, Key, KeyCompare, Extract>::__leftest_offspring(node_base * p) KERBAL_NOEXCEPT
			{
				return const_cast<node_base *>(__leftest_offspring(static_cast<const node_base *>(p)));
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_BASE_IMPL_HPP
