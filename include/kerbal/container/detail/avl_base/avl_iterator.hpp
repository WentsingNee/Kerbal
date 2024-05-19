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

			class avl_iter_type_unrelated:
				// forward iterator interface
				public kerbal::operators::equality_comparable<avl_iter_type_unrelated>, // it != jt
				public kerbal::operators::incrementable<avl_iter_type_unrelated>, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<avl_iter_type_unrelated> // it--
			{
				private:
					friend class kerbal::container::detail::avl_kiter_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef kerbal::container::detail::avl_head_node		head_node;
					typedef kerbal::container::detail::avl_node_base		node_base;
					typedef head_node *										ptr_to_head_node;
					ptr_to_head_node current;

				protected:
					KERBAL_CONSTEXPR
					avl_iter_type_unrelated(ptr_to_head_node current) KERBAL_NOEXCEPT :
						current(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR14
					avl_iter_type_unrelated & operator++() KERBAL_NOEXCEPT
					{
						current = this->current->as_node_base()->inorder_next();
						return *this;
					}

					KERBAL_CONSTEXPR14
					avl_iter_type_unrelated & operator--() KERBAL_NOEXCEPT
					{
						current = this->current->inorder_prev();
						return *this;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator==(
						const avl_iter_type_unrelated & lhs,
						const avl_iter_type_unrelated & rhs
					) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

			};

			class avl_kiter_type_unrelated:
				// forward iterator interface
				public kerbal::operators::equality_comparable<avl_kiter_type_unrelated>, // it != jt
				public kerbal::operators::incrementable<avl_kiter_type_unrelated>, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<avl_kiter_type_unrelated> // it--
			{
				private:
					typedef avl_iter_type_unrelated basic_iterator;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef kerbal::container::detail::avl_head_node		head_node;
					typedef kerbal::container::detail::avl_node_base		node_base;
					typedef const head_node *								const_ptr_to_head_node;
					const_ptr_to_head_node current;

				protected:
					KERBAL_CONSTEXPR
					explicit avl_kiter_type_unrelated(const_ptr_to_head_node current) KERBAL_NOEXCEPT :
						current(current)
					{
					}

				public:
					KERBAL_CONSTEXPR
					avl_kiter_type_unrelated(const basic_iterator & iter) KERBAL_NOEXCEPT :
						current(iter.current)
					{
					}

				protected:
					KERBAL_CONSTEXPR14
					avl_kiter_type_unrelated & operator++() KERBAL_NOEXCEPT
					{
						current = this->current->as_node_base()->inorder_next();
						return *this;
					}

					KERBAL_CONSTEXPR14
					avl_kiter_type_unrelated & operator--() KERBAL_NOEXCEPT
					{
						current = this->current->inorder_prev();
						return *this;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator==(
						const avl_kiter_type_unrelated & lhs,
						const avl_kiter_type_unrelated & rhs
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

			template <typename T>
			class avl_iter:
				protected avl_iter_type_unrelated,
				// forward iterator interface
				public kerbal::operators::dereferenceable<avl_iter<T>, T *>, // it->
				public kerbal::operators::equality_comparable<avl_iter<T> >, // it != jt
				public kerbal::operators::incrementable<avl_iter<T> >, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<avl_iter<T> > // it--
			{
				private:
					typedef avl_iter_type_unrelated super;

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
					explicit avl_iter(const avl_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
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
				protected avl_kiter_type_unrelated,
				// forward iterator interface
				public kerbal::operators::dereferenceable<avl_kiter<T>, const T *>, // it->
				public kerbal::operators::equality_comparable<avl_kiter<T> >, // it != jt
				public kerbal::operators::incrementable<avl_kiter<T> >, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<avl_kiter<T> > // it--
			{
				private:
					typedef avl_kiter_type_unrelated super;

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
					explicit avl_kiter(const avl_kiter_type_unrelated & iter) KERBAL_NOEXCEPT :
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
