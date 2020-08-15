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

#ifndef KERBAL_CONTAINER_DETAIL_SINGLE_LIST_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_SINGLE_LIST_ITERATOR_HPP

#include <kerbal/container/detail/single_list_node.hpp>

#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		class single_list;

		namespace detail
		{
			template <typename Tp>
			class sl_iter;

			template <typename Tp>
			class sl_kiter;

			template <typename Tp>
			class sl_iter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<sl_iter<Tp>, Tp*>, // it->
					public kerbal::operators::equality_comparable<sl_iter<Tp> >, // it != jt
					public kerbal::operators::incrementable<sl_iter<Tp> > // it++
			{
				private:
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

				private:
					typedef kerbal::container::detail::sl_node_base			node_base;
					typedef node_base*										ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit sl_iter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

					KERBAL_CONSTEXPR
					ptr_to_node_base refer_node_ptr() const KERBAL_NOEXCEPT
					{
						return this->current->next;
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
						this->current = this->current->next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const sl_iter & lhs, const sl_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.refer_node_ptr() == rhs.refer_node_ptr();
					}

			};

			template <typename Tp>
			class sl_kiter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<sl_kiter<Tp>, const Tp*>, // it->
					public kerbal::operators::equality_comparable<sl_kiter<Tp> >, // it != jt
					public kerbal::operators::incrementable<sl_kiter<Tp> > // it++
			{
				private:
					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

					friend class sl_iter<Tp>;

				private:
					typedef kerbal::iterator::iterator_traits<const Tp*>	iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				private:
					typedef const kerbal::container::detail::sl_node_base		node_base;
					typedef node_base*											ptr_to_node_base;
					ptr_to_node_base current;

				protected:
					KERBAL_CONSTEXPR
					explicit sl_kiter(ptr_to_node_base current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:
					KERBAL_CONSTEXPR
					sl_kiter(const sl_iter<Tp> & iter) KERBAL_NOEXCEPT :
							current(iter.current)
					{
					}

				public:
					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return this->current->next->template reinterpret_as<Tp>().value;
					}

					KERBAL_CONSTEXPR14
					sl_kiter& operator++() KERBAL_NOEXCEPT
					{
						this->current = this->current->next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const sl_kiter & lhs, const sl_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

				protected:
					KERBAL_CONSTEXPR14
					sl_iter<Tp>
					cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return sl_iter<Tp>(const_cast<kerbal::container::detail::sl_node_base*>(this->current));
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_SINGLE_LIST_ITERATOR_HPP
