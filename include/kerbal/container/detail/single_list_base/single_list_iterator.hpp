/**
 * @file       single_list_iterator.hpp
 * @brief
 * @date       2020-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_ITERATOR_HPP

#include <kerbal/container/detail/single_list_base/single_list_base.fwd.hpp>
#include <kerbal/container/single_list/single_list.fwd.hpp>

#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class sl_iter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<sl_iter_type_unrelated>, // it != jt
					public kerbal::operators::incrementable<sl_iter_type_unrelated> // it++
			{
				private:
					friend class kerbal::container::detail::sl_type_unrelated;

					friend class kerbal::container::detail::sl_kiter_type_unrelated;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef kerbal::container::detail::sl_node_base			node_base;
					typedef node_base*										ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit sl_iter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					ptr_to_node_base refer_node_ptr() const KERBAL_NOEXCEPT
					{
						return this->current->next;
					}

					KERBAL_CONSTEXPR14
					sl_iter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const sl_iter_type_unrelated & lhs, const sl_iter_type_unrelated & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

			};

			class sl_kiter_type_unrelated:
					//forward iterator interface
					public kerbal::operators::equality_comparable<sl_kiter_type_unrelated>, // it != jt
					public kerbal::operators::incrementable<sl_kiter_type_unrelated> // it++
			{
				private:
					friend class kerbal::container::detail::sl_type_unrelated;

					typedef sl_iter_type_unrelated basic_iterator;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef std::ptrdiff_t									difference_type;

				protected:
					typedef const kerbal::container::detail::sl_node_base		node_base;
					typedef node_base*											ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit sl_kiter_type_unrelated(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:
					KERBAL_CONSTEXPR
					sl_kiter_type_unrelated(const basic_iterator & iter) KERBAL_NOEXCEPT :
							current(iter.current)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					ptr_to_node_base refer_node_ptr() const KERBAL_NOEXCEPT
					{
						return this->current->next;
					}

					KERBAL_CONSTEXPR14
					sl_kiter_type_unrelated& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const sl_kiter_type_unrelated & lhs, const sl_kiter_type_unrelated & rhs) KERBAL_NOEXCEPT
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
			class sl_iter:
					protected sl_iter_type_unrelated,
					//forward iterator interface
					public kerbal::operators::dereferenceable<sl_iter<Tp>, Tp*>, // it->
					public kerbal::operators::equality_comparable<sl_iter<Tp> >, // it != jt
					public kerbal::operators::incrementable<sl_iter<Tp> > // it++
			{
				private:
					typedef sl_iter_type_unrelated super;

					friend class kerbal::container::detail::sl_allocator_unrelated<Tp>;

					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

					friend class sl_kiter<Tp>;

				private:
					typedef kerbal::iterator::iterator_traits<Tp*>			iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit sl_iter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit sl_iter(const detail::sl_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
							super(iter)
					{
					}

				public:
					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return this->refer_node_ptr()->template reinterpret_as<Tp>().value;
					}

					KERBAL_CONSTEXPR14
					sl_iter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const sl_iter & lhs, const sl_iter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super&>(lhs) == static_cast<const super&>(rhs);
					}

			};

			template <typename Tp>
			class sl_kiter:
					protected sl_kiter_type_unrelated,
					//forward iterator interface
					public kerbal::operators::dereferenceable<sl_kiter<Tp>, const Tp*>, // it->
					public kerbal::operators::equality_comparable<sl_kiter<Tp> >, // it != jt
					public kerbal::operators::incrementable<sl_kiter<Tp> > // it++
			{
				private:
					typedef sl_kiter_type_unrelated super;

					friend class kerbal::container::detail::sl_allocator_unrelated<Tp>;

					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

					typedef sl_iter<Tp> iterator;

				private:
					typedef kerbal::iterator::iterator_traits<const Tp*>	iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit sl_kiter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit sl_kiter(const detail::sl_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
							super(iter)
					{
					}

				public:
					KERBAL_CONSTEXPR
					sl_kiter(const iterator & iter) KERBAL_NOEXCEPT :
							super(iter.current)
					{
					}

				public:
					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return this->refer_node_ptr()->template reinterpret_as<Tp>().value;
					}

					KERBAL_CONSTEXPR14
					sl_kiter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const sl_kiter & lhs, const sl_kiter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super&>(lhs) == static_cast<const super&>(rhs);
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

#endif // KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_ITERATOR_HPP
