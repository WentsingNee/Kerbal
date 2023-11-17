/**
 * @file       avl_multi_index_iterator.hpp
 * @brief
 * @date       2023-11-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_ITERATOR_HPP

#include <kerbal/container/detail/avl_multi_index_base/avl_multi_index_base.fwd.hpp>

#include <kerbal/container/detail/avl_base/avl_iterator.hpp>

#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/utility/tuple.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, std::size_t KeyCount, std::size_t I>
			class avl_multi_index_iter :
					private kerbal::container::detail::avl_iter_type_unrelated,
					//forward iterator interface
					public kerbal::operators::dereferenceable<avl_multi_index_iter<Entity, KeyCount, I>, Entity*>, // it->
					public kerbal::operators::equality_comparable<avl_multi_index_iter<Entity, KeyCount, I> >, // it != jt
					public kerbal::operators::incrementable<avl_multi_index_iter<Entity, KeyCount, I> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<avl_multi_index_iter<Entity, KeyCount, I> > // it--
			{
				private:
					typedef avl_iter_type_unrelated super;

					typedef kerbal::container::detail::avl_node_base avl_node_base;
					typedef kerbal::container::detail::avl_multi_index_node<Entity, KeyCount> multi_index_node;

					template <typename Entity2, typename ... PolicyFields>
					friend class kerbal::container::detail::avl_multi_index_base;

					// friend class avl_kiter<T>;

				private:
					typedef Entity	k_value_type;
					typedef kerbal::iterator::iterator_traits<k_value_type*>	iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit avl_multi_index_iter(ptr_to_head_node current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

					KERBAL_CONSTEXPR
					explicit avl_multi_index_iter(const avl_iter_type_unrelated & iter) KERBAL_NOEXCEPT :
							super(iter)
					{
					}

				public:
					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return typename multi_index_node::template up_caster<I>()(
							super::current_as_node_base()
						)->member();
					}

					KERBAL_CONSTEXPR14
					avl_multi_index_iter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const avl_multi_index_iter & lhs, const avl_multi_index_iter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super &>(lhs) == static_cast<const super &>(rhs);
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					avl_multi_index_iter& operator--() KERBAL_NOEXCEPT
					{
						super::operator--();
						return *this;
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_ITERATOR_HPP
