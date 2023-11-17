/**
 * @file       avl_multi_index_policy.hpp
 * @brief
 * @date       2023-11-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_POLICY_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_POLICY_HPP

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/function/invoke.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Extractor, typename Compare, bool IsUnique>
			struct avl_multi_index_policy
			{
					typedef Entity	entity;
					typedef Extractor	extractor;
					typedef typename kerbal::function::invoke_result<extractor, const Entity &>::type	key_type;
					typedef Compare		key_compare;
					typedef kerbal::type_traits::integral_constant<bool, IsUnique> is_unique;
			};

			template <typename Policy>
			struct avl_multi_index_policy_traits
			{
					typedef typename Policy::extractor		extractor;
					typedef typename Policy::key_type		key_type;
					typedef typename Policy::key_compare	key_compare;
					typedef typename Policy::is_unique		is_unique;
			};

		} // namespace detail


		template <typename Entity, typename Extractor, typename Compare = kerbal::compare::less<void>, bool IsUnique = true>
		struct avl_multi_index_make_policy
		{
				typedef kerbal::container::detail::avl_multi_index_policy<Entity, Extractor, Compare, IsUnique> type;
		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_POLICY_HPP
