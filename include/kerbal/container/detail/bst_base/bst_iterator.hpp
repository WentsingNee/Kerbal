/**
 * @file       bst_iterator.hpp
 * @brief
 * @date       2024-05-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_BST_BASE_BST_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_BST_BASE_BST_ITERATOR_HPP

#include <kerbal/container/detail/bst_base/bst_node.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename VNULL_HELPER>
			class bst_iter_type_unrelated:
				// forward iterator interface
				public kerbal::operators::equality_comparable<bst_iter_type_unrelated<VNULL_HELPER> >, // it != jt
				public kerbal::operators::incrementable<bst_iter_type_unrelated<VNULL_HELPER> >, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<bst_iter_type_unrelated<VNULL_HELPER> > // it--
			{
				private:
					friend class kerbal::container::detail::bst_kiter_type_unrelated<VNULL_HELPER>;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef bst_head_node<VNULL_HELPER>						head_node;
					typedef head_node *										ptr_to_head_node;
					ptr_to_head_node current;

				protected:
					KERBAL_CONSTEXPR
					bst_iter_type_unrelated(ptr_to_head_node current) KERBAL_NOEXCEPT :
						current(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR14
					bst_iter_type_unrelated & operator++() KERBAL_NOEXCEPT
					{
						current = this->current->as_node_base()->inorder_next();
						return *this;
					}

					KERBAL_CONSTEXPR14
					bst_iter_type_unrelated & operator--() KERBAL_NOEXCEPT
					{
						current = this->current->inorder_prev();
						return *this;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator==(
						const bst_iter_type_unrelated & lhs,
						const bst_iter_type_unrelated & rhs
					) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

			};


			template <typename VNULL_HELPER>
			class bst_kiter_type_unrelated:
				// forward iterator interface
				public kerbal::operators::equality_comparable<bst_kiter_type_unrelated<VNULL_HELPER> >, // it != jt
				public kerbal::operators::incrementable<bst_kiter_type_unrelated<VNULL_HELPER> >, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<bst_kiter_type_unrelated<VNULL_HELPER> > // it--
			{
				private:
					typedef bst_iter_type_unrelated<VNULL_HELPER> basic_iterator;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef bst_head_node<VNULL_HELPER>						head_node;
					typedef const head_node *								const_ptr_to_head_node;
					const_ptr_to_head_node current;

				protected:
					KERBAL_CONSTEXPR
					explicit bst_kiter_type_unrelated(const_ptr_to_head_node current) KERBAL_NOEXCEPT :
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
					bst_kiter_type_unrelated & operator++() KERBAL_NOEXCEPT
					{
						current = this->current->as_node_base()->inorder_next();
						return *this;
					}

					KERBAL_CONSTEXPR14
					bst_kiter_type_unrelated & operator--() KERBAL_NOEXCEPT
					{
						current = this->current->inorder_prev();
						return *this;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator==(
						const bst_kiter_type_unrelated & lhs,
						const bst_kiter_type_unrelated & rhs
					) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					KERBAL_CONSTEXPR14
					basic_iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return basic_iterator(const_cast<head_node *>(this->current));
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_BST_BASE_BST_ITERATOR_HPP
