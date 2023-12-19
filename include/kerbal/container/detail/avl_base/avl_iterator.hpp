/**
 * @file       avl_iterator.hpp
 * @brief
 * @date       2020-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_ITERATOR_HPP

#include <kerbal/container/detail/bst_base/bst_iterator.hpp>
#include <kerbal/container/detail/avl_base/avl_node.hpp>

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

			template <typename T>
			class avl_iter:
				bst_iter_type_unrelated<avl_vnull_node_helper<> >,
				// forward iterator interface
				public kerbal::operators::dereferenceable<avl_iter<T>, T *>, // it->
				public kerbal::operators::equality_comparable<avl_iter<T> >, // it != jt
				public kerbal::operators::incrementable<avl_iter<T> >, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<avl_iter<T> > // it--
			{
				private:
					typedef bst_iter_type_unrelated<avl_vnull_node_helper<> > super;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

					typedef kerbal::container::detail::avl_node<T> node;
					friend class avl_kiter<T>;

				private:
					typedef kerbal::iterator::iterator_traits<T *>			iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit avl_iter(ptr_to_head_node current) KERBAL_NOEXCEPT :
						super(current)
					{
					}

					KERBAL_CONSTEXPR
					explicit avl_iter(const bst_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
						super(iter)
					{
					}

				public:
					//===================
					// forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return node::reinterpret_as(this->current)->member();
					}

					KERBAL_CONSTEXPR14
					avl_iter & operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator==(const avl_iter & lhs, const avl_iter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super &>(lhs) == static_cast<const super &>(rhs);
					}

					//===================
					// bidirectional iterator interface

					KERBAL_CONSTEXPR14
					avl_iter & operator--() KERBAL_NOEXCEPT
					{
						super::operator--();
						return *this;
					}

			};

			template <typename T>
			class avl_kiter:
				bst_kiter_type_unrelated<avl_vnull_node_helper<> >,
				// forward iterator interface
				public kerbal::operators::dereferenceable<avl_kiter<T>, const T *>, // it->
				public kerbal::operators::equality_comparable<avl_kiter<T> >, // it != jt
				public kerbal::operators::incrementable<avl_kiter<T> >, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<avl_kiter<T> > // it--
			{
				private:
					typedef bst_kiter_type_unrelated<avl_vnull_node_helper<> > super;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

					typedef kerbal::container::detail::avl_node<T> node;
					typedef avl_iter<T> iterator;

				private:
					typedef kerbal::iterator::iterator_traits<const T *>	iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit avl_kiter(const_ptr_to_head_node current) KERBAL_NOEXCEPT :
						super(current)
					{
					}

					KERBAL_CONSTEXPR
					explicit avl_kiter(const bst_kiter_type_unrelated & iter) KERBAL_NOEXCEPT :
						super(iter)
					{
					}

				public:
					KERBAL_CONSTEXPR
					avl_kiter(const iterator & iter) KERBAL_NOEXCEPT :
						super(iter.current)
					{
					}

				public:
					//===================
					// forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return node::reinterpret_as(this->current)->member();
					}

					KERBAL_CONSTEXPR14
					avl_kiter & operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator==(const avl_kiter & lhs, const avl_kiter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super &>(lhs) == static_cast<const super &>(rhs);
					}

					//===================
					// bidirectional iterator interface

					KERBAL_CONSTEXPR14
					avl_kiter & operator--() KERBAL_NOEXCEPT
					{
						super::operator--();
						return *this;
					}

				protected:
					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<head_node *>(this->current));
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_ITERATOR_HPP
