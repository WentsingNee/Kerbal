/**
 * @file       list_iterator.hpp
 * @brief
 * @date       2020-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_ITERATOR_HPP

#include <kerbal/container/detail/list_base/list_base.fwd.hpp>
#include <kerbal/autonm/list/list.fwd.hpp>
#include <kerbal/container/list/list.fwd.hpp>
#include <kerbal/container/detail/list_base/list_node.hpp>

#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class list_iter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<list_iter_type_unrelated>, // it != jt
					public kerbal::operators::incrementable<list_iter_type_unrelated>, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<list_iter_type_unrelated> // it--
			{
				private:
					friend class kerbal::container::detail::list_type_unrelated;

					friend class kerbal::container::detail::list_kiter_type_unrelated;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef kerbal::container::detail::list_node_base		node_base;
					typedef node_base*										ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit list_iter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				protected:

					KERBAL_CONSTEXPR14
					list_iter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->next;
						return *this;
					}

					KERBAL_CONSTEXPR14
					list_iter_type_unrelated& operator--() KERBAL_NOEXCEPT
					{
						this->current = this->current->prev;
						return *this;
					}

					KERBAL_CONSTEXPR
					friend bool operator==(const list_iter_type_unrelated & lhs, const list_iter_type_unrelated & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

			};

			class list_kiter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<list_kiter_type_unrelated>, // it != jt
					public kerbal::operators::incrementable<list_kiter_type_unrelated>, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<list_kiter_type_unrelated> // it--
			{
				private:
					friend class kerbal::container::detail::list_type_unrelated;

					typedef list_iter_type_unrelated basic_iterator;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef const kerbal::container::detail::list_node_base		node_base;
					typedef node_base*											ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit list_kiter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:
					KERBAL_CONSTEXPR
					list_kiter_type_unrelated(const basic_iterator & iter) KERBAL_NOEXCEPT :
							current(iter.current)
					{
					}

				protected:

					KERBAL_CONSTEXPR14
					list_kiter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->next;
						return *this;
					}

					KERBAL_CONSTEXPR14
					list_kiter_type_unrelated& operator--() KERBAL_NOEXCEPT
					{
						this->current = this->current->prev;
						return *this;
					}

					KERBAL_CONSTEXPR
					friend bool operator==(const list_kiter_type_unrelated & lhs, const list_kiter_type_unrelated & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					KERBAL_CONSTEXPR14
					basic_iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return basic_iterator(const_cast<kerbal::container::detail::list_node_base*>(this->current));
					}

			};

			template <typename T>
			class list_iter:
					protected list_iter_type_unrelated,
					//forward iterator interface
					public kerbal::operators::dereferenceable<list_iter<T>, T*>, // it->
					public kerbal::operators::equality_comparable<list_iter<T> >, // it != jt
					public kerbal::operators::incrementable<list_iter<T> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<list_iter<T> > // it--
			{
				private:
					typedef list_iter_type_unrelated super;

					friend class kerbal::container::detail::list_type_only<T>;

					template <typename U, typename Allocator>
					friend class kerbal::container::list;

					template <typename U, typename SemiAllocator>
					friend class kerbal::autonm::list;

					typedef kerbal::container::detail::list_node<T>			node;
					friend class list_kiter<T>;

				private:
					typedef kerbal::iterator::iterator_traits<T*>			iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit list_iter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit list_iter(const list_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
							super(iter)
					{
					}

				public:
					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return node::reinterpret_as(this->current)->member();
					}

					KERBAL_CONSTEXPR14
					list_iter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					KERBAL_CONSTEXPR
					friend bool operator==(const list_iter & lhs, const list_iter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super&>(lhs) == static_cast<const super&>(rhs);
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					list_iter& operator--() KERBAL_NOEXCEPT
					{
						super::operator--();
						return *this;
					}

			};

			template <typename T>
			class list_kiter:
					protected list_kiter_type_unrelated,
					//forward iterator interface
					public kerbal::operators::dereferenceable<list_kiter<T>, const T*>, // it->
					public kerbal::operators::equality_comparable<list_kiter<T> >, // it != jt
					public kerbal::operators::incrementable<list_kiter<T> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<list_kiter<T> > // it--
			{
				private:
					typedef list_kiter_type_unrelated super;

					friend class kerbal::container::detail::list_type_only<T>;

					template <typename U, typename Allocator>
					friend class kerbal::container::list;

					template <typename U, typename SemiAllocator>
					friend class kerbal::autonm::list;

					typedef kerbal::container::detail::list_node<T>			node;
					typedef list_iter<T> iterator;

				private:
					typedef kerbal::iterator::iterator_traits<const T*>		iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit list_kiter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit list_kiter(const list_kiter_type_unrelated & iter) KERBAL_NOEXCEPT :
							super(iter)
					{
					}

				public:
					KERBAL_CONSTEXPR
					list_kiter(const iterator & iter) KERBAL_NOEXCEPT :
							super(iter.current)
					{
					}

				public:
					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return node::reinterpret_as(this->current)->member();
					}

					KERBAL_CONSTEXPR14
					list_kiter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					KERBAL_CONSTEXPR
					friend bool operator==(const list_kiter & lhs, const list_kiter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super&>(lhs) == static_cast<const super&>(rhs);
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					list_kiter& operator--() KERBAL_NOEXCEPT
					{
						super::operator--();
						return *this;
					}

				protected:
					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<kerbal::container::detail::list_node_base*>(this->current));
					}

			};

		} // namespace detail

	} // namespace container

	namespace iterator
	{

		namespace detail
		{

			template <>
			struct reverse_iterator_base_is_inplace<kerbal::container::detail::list_iter_type_unrelated>:
					kerbal::type_traits::true_type
			{
			};

			template <>
			struct reverse_iterator_base_is_inplace<kerbal::container::detail::list_kiter_type_unrelated>:
					kerbal::type_traits::true_type
			{
			};

			template <typename T>
			struct reverse_iterator_base_is_inplace<kerbal::container::detail::list_iter<T> >:
					kerbal::type_traits::true_type
			{
			};

			template <typename T>
			struct reverse_iterator_base_is_inplace<kerbal::container::detail::list_kiter<T> >:
					kerbal::type_traits::true_type
			{
			};

		} // namespace detail

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_ITERATOR_HPP
