/**
 * @file       avl_multi_index_node.hpp
 * @brief
 * @date       2023-11-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_NODE_HPP

#include <kerbal/container/detail/avl_multi_index_base/avl_multi_index_base.fwd.hpp>

#include <kerbal/container/detail/avl_base/avl_node.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/integer_sequence.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/tuple.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <std::size_t I>
			class avl_multi_index_node_base_adapter :
					public kerbal::container::detail::avl_node_base
			{

				public:
					KERBAL_CONSTEXPR14
					kerbal::container::detail::avl_node_base & super() KERBAL_NOEXCEPT
					{
						return static_cast<kerbal::container::detail::avl_node_base &>(*this);
					}
			};

			template <typename>
			class avl_multi_index_node_base;

			template <std::size_t ... FieldID>
			class avl_multi_index_node_base<kerbal::utility::index_sequence<FieldID...> > :
					public avl_multi_index_node_base_adapter<FieldID>...
			{
				public:
					template <std::size_t I>
					struct super
					{
						typedef avl_multi_index_node_base_adapter<I> type;
					};

				public:
					template <std::size_t I>
					KERBAL_CONSTEXPR14
					kerbal::container::detail::avl_node_base &
					as_avl_node_base_by_id()
					{
						return static_cast<typename super<I>::type &>(*this).super();
					}

					template <std::size_t I>
					struct up_caster
					{
							KERBAL_CONSTEXPR
							avl_multi_index_node_base * operator()(kerbal::container::detail::avl_node_base * p_node_base) KERBAL_NOEXCEPT
							{
								return static_cast<avl_multi_index_node_base_adapter<I> *>(p_node_base);
							}
					};

			};

			template <typename Entity, std::size_t KeyCount>
			class avl_multi_index_node :
					public kerbal::container::detail::avl_multi_index_node_base<kerbal::utility::make_index_sequence<KeyCount> >,
					public kerbal::utility::member_compress_helper<Entity>
			{
				public:
					typedef Entity data;
					typedef kerbal::utility::member_compress_helper<data> member_compress_helper;

				public:
					template <typename ... Args>
					KERBAL_CONSTEXPR
					avl_multi_index_node(Args && ... keys) :
							member_compress_helper(kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(keys)...)
					{
					}

				public:
					using member_compress_helper::member;

					template <std::size_t I>
					struct up_caster
					{
							KERBAL_CONSTEXPR
							avl_multi_index_node * operator()(kerbal::container::detail::avl_node_base * p_node_base) KERBAL_NOEXCEPT
							{
								return static_cast<avl_multi_index_node *>(
									static_cast<avl_multi_index_node_base_adapter<I> *>(p_node_base)
								);
							}
					};
			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_NODE_HPP
