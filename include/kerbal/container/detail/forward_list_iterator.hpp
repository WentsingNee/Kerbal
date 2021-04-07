/**
 * @file       forward_list_iterator.hpp
 * @brief
 * @date       2021-01-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FORWARD_LIST_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_FORWARD_LIST_ITERATOR_HPP

#include <kerbal/container/fwd/forward_list.fwd.hpp>

#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <kerbal/container/detail/single_list_node.hpp>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class fl_iter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<fl_iter_type_unrelated>, // it != jt
					public kerbal::operators::incrementable<fl_iter_type_unrelated> // it++
			{
				private:
					friend class kerbal::container::detail::fl_type_unrelated;

					friend class kerbal::container::detail::fl_kiter_type_unrelated;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef kerbal::container::detail::sl_node_base			node_base;
					typedef node_base*										ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit fl_iter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				protected:

					KERBAL_CONSTEXPR14
					fl_iter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const fl_iter_type_unrelated & lhs, const fl_iter_type_unrelated & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

			};

			class fl_kiter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<fl_kiter_type_unrelated>, // it != jt
					public kerbal::operators::incrementable<fl_kiter_type_unrelated> // it++
			{
				private:
					friend class kerbal::container::detail::fl_type_unrelated;

					typedef fl_iter_type_unrelated basic_iterator;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef const kerbal::container::detail::sl_node_base		node_base;
					typedef node_base*											ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit fl_kiter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:
					KERBAL_CONSTEXPR
					fl_kiter_type_unrelated(const basic_iterator & iter) KERBAL_NOEXCEPT :
							current(iter.current)
					{
					}

				protected:

					KERBAL_CONSTEXPR14
					fl_kiter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const fl_kiter_type_unrelated & lhs, const fl_kiter_type_unrelated & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					KERBAL_CONSTEXPR14
					basic_iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return basic_iterator(const_cast<kerbal::container::detail::sl_node_base*>(this->current));
					}

			};

			template <typename Tp>
			class fl_iter:
					public fl_iter_type_unrelated,
					//forward iterator interface
					public kerbal::operators::dereferenceable<fl_iter<Tp>, Tp*>, // it->
					public kerbal::operators::equality_comparable<fl_iter<Tp> >, // it != jt
					public kerbal::operators::incrementable<fl_iter<Tp> > // it++
			{
				private:
					typedef fl_iter_type_unrelated super;

					/// forward_list
					friend class kerbal::container::detail::fl_allocator_unrelated<Tp>;

					template <typename Up, typename Allocator>
					friend class kerbal::container::forward_list;

					friend class fl_kiter<Tp>;

				private:
					typedef kerbal::iterator::iterator_traits<Tp*>			iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				public:
					KERBAL_CONSTEXPR
					explicit fl_iter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit fl_iter(const detail::fl_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
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
					fl_iter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const fl_iter & lhs, const fl_iter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super&>(lhs) == static_cast<const super&>(rhs);
					}

			};

			template <typename Tp>
			class fl_kiter:
					public fl_kiter_type_unrelated,
					//forward iterator interface
					public kerbal::operators::dereferenceable<fl_kiter<Tp>, const Tp*>, // it->
					public kerbal::operators::equality_comparable<fl_kiter<Tp> >, // it != jt
					public kerbal::operators::incrementable<fl_kiter<Tp> > // it++
			{
				private:
					typedef fl_kiter_type_unrelated super;

					/// forward_list
					friend class kerbal::container::detail::fl_allocator_unrelated<Tp>;

					template <typename Up, typename Allocator>
					friend class kerbal::container::forward_list;

					typedef fl_iter<Tp> iterator;

				private:
					typedef kerbal::iterator::iterator_traits<const Tp*>	iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				public:
					KERBAL_CONSTEXPR
					explicit fl_kiter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit fl_kiter(const detail::fl_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
							super(iter)
					{
					}

				public:
					KERBAL_CONSTEXPR
					fl_kiter(const iterator & iter) KERBAL_NOEXCEPT :
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
					fl_kiter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const fl_kiter & lhs, const fl_kiter & rhs) KERBAL_NOEXCEPT
					{
						return (const super&)lhs == (const super&)rhs;
					}

				protected:
					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<kerbal::container::detail::sl_node_base*>(this->current));
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_FORWARD_LIST_ITERATOR_HPP
