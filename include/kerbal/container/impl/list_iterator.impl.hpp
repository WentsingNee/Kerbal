/**
 * @file       list_iterator.impl.hpp
 * @brief
 * @date       2020-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_LIST_ITERATOR_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_LIST_ITERATOR_IMPL_HPP

#include <kerbal/container/impl/list_node.impl.hpp>

#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		class list;

		namespace detail
		{
			template <typename Tp>
			class list_iter;

			template <typename Tp>
			class list_kiter;

			template <typename Tp>
			class list_iter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<list_iter<Tp>, Tp*>, // it->
					public kerbal::operators::equality_comparable<list_iter<Tp> >, // it != jt
					public kerbal::operators::incrementable<list_iter<Tp> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<list_iter<Tp> > // it--
			{
				private:
					template <typename Up, typename Allocator>
					friend class kerbal::container::list;

					friend class list_kiter<Tp>;

				private:
					typedef kerbal::iterator::iterator_traits<Tp*>			iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				private:
					typedef kerbal::container::detail::list_node_base		node_base;
					typedef node_base*										ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit list_iter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
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
					list_iter& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const list_iter & lhs, const list_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					list_iter& operator--() KERBAL_NOEXCEPT
					{
						current = current->prev;
						return *this;
					}

			};

			template <typename Tp>
			class list_kiter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<list_kiter<Tp>, const Tp*>, // it->
					public kerbal::operators::equality_comparable<list_kiter<Tp> >, // it != jt
					public kerbal::operators::incrementable<list_kiter<Tp> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<list_kiter<Tp> > // it--
			{
				private:
					template <typename Up, typename Allocator>
					friend class kerbal::container::list;

					friend class list_kiter<Tp>;

				private:
					typedef kerbal::iterator::iterator_traits<const Tp*>	iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				private:
					typedef const kerbal::container::detail::list_node_base		node_base;
					typedef node_base*											ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit list_kiter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:
					KERBAL_CONSTEXPR
					list_kiter(const list_iter<Tp> & iter) KERBAL_NOEXCEPT :
							current(iter.current)
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
					list_kiter& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const list_kiter & lhs, const list_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					list_kiter& operator--() KERBAL_NOEXCEPT
					{
						current = current->prev;
						return *this;
					}

				protected:
					KERBAL_CONSTEXPR14
					list_iter<Tp>
					cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return list_iter<Tp>(const_cast<kerbal::container::detail::list_node_base*>(this->current));
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_LIST_ITERATOR_IMPL_HPP
