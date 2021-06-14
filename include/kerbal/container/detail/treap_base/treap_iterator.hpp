/**
 * @file       treap_iterator.hpp
 * @brief
 * @date       2021-06-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_TREAP_BASE_TREAP_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_TREAP_BASE_TREAP_ITERATOR_HPP

#include <kerbal/container/detail/treap_base/treap.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename W>
			class treap_iter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<treap_iter_type_unrelated<W> >, // it != jt
					public kerbal::operators::incrementable<treap_iter_type_unrelated<W> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<treap_iter_type_unrelated<W> > // it--
			{
				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef kerbal::container::detail::treap_node_base<W>	node_base;
					typedef node_base*										ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					treap_iter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT
							: current(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR14
					treap_iter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->inorder_next();
						return *this;
					}

					KERBAL_CONSTEXPR14
					treap_iter_type_unrelated& operator--() KERBAL_NOEXCEPT
					{
						this->current = this->current->inorder_prev();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const treap_iter_type_unrelated & lhs, const treap_iter_type_unrelated & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

			};

			template <typename W>
			class treap_kiter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<treap_kiter_type_unrelated<W> >, // it != jt
					public kerbal::operators::incrementable<treap_kiter_type_unrelated<W> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<treap_kiter_type_unrelated<W> > // it--
			{
				private:
					typedef treap_iter_type_unrelated basic_iterator;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef const kerbal::container::detail::treap_node_base<W>		node_base;
					typedef node_base*												ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit treap_kiter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:
					KERBAL_CONSTEXPR
					treap_kiter_type_unrelated(const basic_iterator & iter) KERBAL_NOEXCEPT :
							current(iter.current)
					{
					}

				protected:
					KERBAL_CONSTEXPR14
					treap_kiter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->inorder_next();
						return *this;
					}

					KERBAL_CONSTEXPR14
					treap_kiter_type_unrelated& operator--() KERBAL_NOEXCEPT
					{
						this->current = this->current->inorder_prev();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const treap_kiter_type_unrelated & lhs, const treap_kiter_type_unrelated & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					KERBAL_CONSTEXPR14
					basic_iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return basic_iterator(const_cast<kerbal::container::detail::treap_node_base*>(this->current));
					}

			};

			template <typename Tp, typename W>
			class treap_iter:
					treap_iter_type_unrelated<W>,
					//forward iterator interface
					public kerbal::operators::dereferenceable<treap_iter<Tp, W>, Tp*>, // it->
					public kerbal::operators::equality_comparable<treap_iter<Tp, W> >, // it != jt
					public kerbal::operators::incrementable<treap_iter<Tp, W> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<treap_iter<Tp, W> > // it--
			{
				private:
					typedef treap_iter_type_unrelated<W> super;

					friend class treap_kiter<Tp, W>;

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
					explicit treap_iter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

					KERBAL_CONSTEXPR
					explicit treap_iter(const treap_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
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
					treap_iter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const treap_iter & lhs, const treap_iter & rhs) KERBAL_NOEXCEPT
					{
						return (const super&)lhs == (const super&)rhs;
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					treap_iter& operator--() KERBAL_NOEXCEPT
					{
						super::operator--();
						return *this;
					}

			};

			template <typename Tp, typename W>
			class treap_kiter:
					treap_kiter_type_unrelated<W>,
					//forward iterator interface
					public kerbal::operators::dereferenceable<treap_kiter<Tp, W>, const Tp*>, // it->
					public kerbal::operators::equality_comparable<treap_kiter<Tp, W> >, // it != jt
					public kerbal::operators::incrementable<treap_kiter<Tp, W> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<treap_kiter<Tp, W> > // it--
			{
				private:
					typedef treap_kiter_type_unrelated<W> super;

					typedef treap_iter<Tp, W> iterator;

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
					explicit treap_kiter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

					KERBAL_CONSTEXPR
					explicit treap_kiter(const treap_kiter_type_unrelated & iter) KERBAL_NOEXCEPT :
							super(iter)
					{
					}

				public:
					KERBAL_CONSTEXPR
					treap_kiter(const iterator & iter) KERBAL_NOEXCEPT :
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
					treap_kiter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const treap_kiter & lhs, const treap_kiter & rhs) KERBAL_NOEXCEPT
					{
						return (const super&)lhs == (const super&)rhs;
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					treap_kiter& operator--() KERBAL_NOEXCEPT
					{
						super::operator--();
						return *this;
					}

				protected:
					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<kerbal::container::detail::treap_node_base*>(this->current));
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_TREAP_BASE_TREAP_ITERATOR_HPP
