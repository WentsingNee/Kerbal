/**
 * @file       binary_search_tree_iterator.hpp
 * @brief
 * @date       2020-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_ITERATOR_HPP

#include <kerbal/container/detail/bst_base/binary_search_tree.fwd.hpp>
#include <kerbal/container/detail/bst_base/binary_search_tree_node.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			KERBAL_CONSTEXPR14
			inline
			const bst_node_base*
			inorder_next(const bst_node_base * current) KERBAL_NOEXCEPT
			{
				if (current->right == NULL) {
					const bst_node_base * parent = current->parent;
					while (current != parent->left) { // warning: head doesn't have right domain!
						// is parent's right son
						current = parent;
//						std::cout << "  *" << current->reinterpret_as<int>().value << std::endl;
						parent = parent->parent;
					}
					// is parent's left son
					current = parent;
				} else {
					current = current->right;
					while (current->left != NULL) {
						current = current->left;
					}
				}
				return current;
			}

			KERBAL_CONSTEXPR14
			inline
			bst_node_base*
			inorder_next(bst_node_base * current) KERBAL_NOEXCEPT
			{
				return const_cast<bst_node_base*>(
						inorder_next(
								static_cast<const bst_node_base*>(current)));
			}

			KERBAL_CONSTEXPR14
			inline
			const bst_node_base*
			inorder_prev(const bst_node_base* current) KERBAL_NOEXCEPT
			{
				if (current->left == NULL) {
					const bst_node_base * parent = current->parent;
					while (current == parent->left) { // warning: head doesn't have right domain!
						// is parent's right son
						current = parent;
						parent = parent->parent;
					}
					// is parent's left son
					current = parent;
				} else {
					current = current->left;
					while (current->right != NULL) {
						current = current->right;
					}
				}
				return current;
			}

			KERBAL_CONSTEXPR14
			inline
			bst_node_base*
			inorder_prev(bst_node_base* current) KERBAL_NOEXCEPT
			{
				return const_cast<bst_node_base*>(
						inorder_prev(
								static_cast<const bst_node_base*>(current)));
			}

			class bst_iter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<bst_iter_type_unrelated>, // it != jt
					public kerbal::operators::incrementable<bst_iter_type_unrelated>, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<bst_iter_type_unrelated> // it--
			{
					template <typename Entity, typename Key, typename KeyCompare, typename Extract>
					friend class kerbal::container::detail::bst;

					friend class kerbal::container::detail::bst_kiter_type_unrelated;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef kerbal::container::detail::bst_node_base		node_base;
					typedef node_base*										ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					bst_iter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT
							: current(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR14
					bst_iter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						current = inorder_next(this->current);
						return *this;
					}

					KERBAL_CONSTEXPR14
					bst_iter_type_unrelated& operator--() KERBAL_NOEXCEPT
					{
						current = inorder_prev(this->current);
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const bst_iter_type_unrelated & lhs, const bst_iter_type_unrelated & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

			};

			class bst_kiter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<bst_kiter_type_unrelated>, // it != jt
					public kerbal::operators::incrementable<bst_kiter_type_unrelated>, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<bst_kiter_type_unrelated> // it--
			{
				private:
					template <typename Entity, typename Key, typename KeyCompare, typename Extract>
					friend class kerbal::container::detail::bst;

					typedef bst_iter_type_unrelated basic_iterator;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef const kerbal::container::detail::bst_node_base		node_base;
					typedef node_base*											ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit bst_kiter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:
					KERBAL_CONSTEXPR
					bst_kiter_type_unrelated(const basic_iterator & iter) KERBAL_NOEXCEPT :
							current(iter.current)
					{
					}

				protected:
					KERBAL_CONSTEXPR14
					bst_kiter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						current = inorder_next(this->current);
						return *this;
					}

					KERBAL_CONSTEXPR14
					bst_kiter_type_unrelated& operator--() KERBAL_NOEXCEPT
					{
						current = inorder_prev(this->current);
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const bst_kiter_type_unrelated & lhs, const bst_kiter_type_unrelated & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					KERBAL_CONSTEXPR14
					basic_iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return basic_iterator(const_cast<kerbal::container::detail::bst_node_base*>(this->current));
					}

			};

			template <typename Tp>
			class bst_iter:
					bst_iter_type_unrelated,
					//forward iterator interface
					public kerbal::operators::dereferenceable<bst_iter<Tp>, Tp*>, // it->
					public kerbal::operators::equality_comparable<bst_iter<Tp> >, // it != jt
					public kerbal::operators::incrementable<bst_iter<Tp> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<bst_iter<Tp> > // it--
			{
				private:
					typedef bst_iter_type_unrelated super;

//					friend class kerbal::container::detail::list_allocator_unrelated<Tp>;

					template <typename Entity, typename Key, typename KeyCompare, typename Extract>
					friend class kerbal::container::detail::bst;

					friend class bst_kiter<Tp>;

				private:
					typedef kerbal::iterator::iterator_traits<Tp*>			iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit bst_iter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

					KERBAL_CONSTEXPR
					explicit bst_iter(const bst_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
							super(iter)
					{
					}

				public:
					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return this->current->template reinterpret_as<Tp>().value;
					}

					KERBAL_CONSTEXPR14
					bst_iter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const bst_iter & lhs, const bst_iter & rhs) KERBAL_NOEXCEPT
					{
						return (const super&)lhs == (const super&)rhs;
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					bst_iter& operator--() KERBAL_NOEXCEPT
					{
						super::operator--();
						return *this;
					}

			};

			template <typename Tp>
			class bst_kiter:
					bst_kiter_type_unrelated,
					//forward iterator interface
					public kerbal::operators::dereferenceable<bst_kiter<Tp>, const Tp*>, // it->
					public kerbal::operators::equality_comparable<bst_kiter<Tp> >, // it != jt
					public kerbal::operators::incrementable<bst_kiter<Tp> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<bst_kiter<Tp> > // it--
			{
				private:
					typedef bst_kiter_type_unrelated super;

//					friend class kerbal::container::detail::bst_allocator_unrelated<Tp>;

					template <typename Entity, typename Key, typename KeyCompare, typename Extract>
					friend class kerbal::container::detail::bst;

					typedef bst_iter<Tp> iterator;

				private:
					typedef kerbal::iterator::iterator_traits<const Tp*>	iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit bst_kiter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

					KERBAL_CONSTEXPR
					explicit bst_kiter(const bst_kiter_type_unrelated & iter) KERBAL_NOEXCEPT :
							super(iter)
					{
					}

				public:
					KERBAL_CONSTEXPR
					bst_kiter(const iterator & iter) KERBAL_NOEXCEPT :
							super(iter.current)
					{
					}

				public:
					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return this->current->template reinterpret_as<Tp>().value;
					}

					KERBAL_CONSTEXPR14
					bst_kiter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const bst_kiter & lhs, const bst_kiter & rhs) KERBAL_NOEXCEPT
					{
						return (const super&)lhs == (const super&)rhs;
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					bst_kiter& operator--() KERBAL_NOEXCEPT
					{
						super::operator--();
						return *this;
					}

				protected:
					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<kerbal::container::detail::bst_node_base*>(this->current));
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_ITERATOR_HPP
