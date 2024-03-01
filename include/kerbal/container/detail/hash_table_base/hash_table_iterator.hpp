/**
 * @file       hash_table_iterator.hpp
 * @brief
 * @date       2020-08-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_ITERATOR_HPP

#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>

#include <iterator>

#include <kerbal/container/detail/hash_table_base/hash_table_base.fwd.hpp>
#include <kerbal/container/detail/hash_table_base/hash_table_node.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity>
			class hash_table_iter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<hash_table_iter<Entity>, Entity*>, // it->
					public kerbal::operators::equality_comparable<hash_table_iter<Entity> >, // it != jt
					public kerbal::operators::incrementable<hash_table_iter<Entity> > // it++
			{
				private:
					template <typename Entity2, typename HashCachePolicy>
					friend class kerbal::container::detail::hash_table_base;

					friend class kerbal::container::detail::hash_table_kiter<Entity>;

				protected:
					typedef kerbal::container::detail::hash_table_node_type_unrelated		node_type_unrelated;
					typedef kerbal::container::detail::hash_table_node_type_only<Entity>	node_type_only;
					typedef kerbal::container::detail::hash_table_iter<Entity>				iterator;
					typedef kerbal::container::detail::hash_table_kiter<Entity>				const_iterator;

				protected:
					node_type_unrelated * k_current;

				private:
					typedef kerbal::iterator::iterator_traits<Entity*>	iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				public:
					KERBAL_CONSTEXPR14
					explicit hash_table_iter(node_type_unrelated * current) KERBAL_NOEXCEPT
							: k_current(current)
					{
					}

				public:

				//===================
				// forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return static_cast<node_type_only *>(this->k_current)->member();
					}

					KERBAL_CONSTEXPR14
					hash_table_iter& operator++() KERBAL_NOEXCEPT
					{
						this->k_current = this->k_current->k_next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const hash_table_iter & lhs, const hash_table_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.k_current == rhs.k_current;
					}

			};

			template <typename Entity>
			class hash_table_kiter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<hash_table_kiter<Entity>, Entity const*>, // it->
					public kerbal::operators::equality_comparable<hash_table_kiter<Entity> >, // it != jt
					public kerbal::operators::incrementable<hash_table_kiter<Entity> > // it++
			{
				private:
					template <typename Entity2, typename HashCachePolicy>
					friend class kerbal::container::detail::hash_table_base;

					friend class kerbal::container::detail::hash_table_iter<Entity>;

				protected:
					typedef kerbal::container::detail::hash_table_node_type_unrelated		node_type_unrelated;
					typedef kerbal::container::detail::hash_table_node_type_only<Entity>	node_type_only;
					typedef kerbal::container::detail::hash_table_iter<Entity>				iterator;
					typedef kerbal::container::detail::hash_table_kiter<Entity>				const_iterator;

				protected:
					const node_type_unrelated * k_current;

				private:
					typedef kerbal::iterator::iterator_traits<Entity const*>	iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				public:
					KERBAL_CONSTEXPR14
					explicit hash_table_kiter(const node_type_unrelated * current) KERBAL_NOEXCEPT
							: k_current(current)
					{
					}

				public:

					KERBAL_CONSTEXPR14
					hash_table_kiter(iterator iter) KERBAL_NOEXCEPT
							: k_current(iter.k_current)
					{
					}

				public:

				//===================
				// forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return static_cast<const node_type_only *>(this->k_current)->member();
					}

					KERBAL_CONSTEXPR14
					hash_table_kiter& operator++() KERBAL_NOEXCEPT
					{
						this->k_current = this->k_current->k_next;
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const hash_table_kiter & lhs, const hash_table_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.k_current == rhs.k_current;
					}

					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<node_type_unrelated *>(this->k_current));
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_ITERATOR_HPP
