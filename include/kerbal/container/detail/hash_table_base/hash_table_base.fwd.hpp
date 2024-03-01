/**
 * @file       hash_table_base.fwd.hpp
 * @brief
 * @date       2022-03-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_FWD_HPP

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_floating_point.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Entity, typename Hash>
		struct cache_hash_result:
				kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_floating_point<Entity>::value
				>
		{
		};

		namespace detail
		{

			template <typename Entity, typename HashCachePolicy>
			class hash_table_base;


			template <typename HashResult>
			struct not_cache_hash_result_wrapper
			{
			};


			template <typename HashCachePolicy>
			struct hash_cache_policy_traits
			{
					typedef HashCachePolicy hash_result_type;
					typedef kerbal::type_traits::true_type CACHE_HASH_RESULT;
			};

			template <typename HashResult>
			struct hash_cache_policy_traits<not_cache_hash_result_wrapper<HashResult> >
			{
					typedef HashResult hash_result_type;
					typedef kerbal::type_traits::false_type CACHE_HASH_RESULT;
			};


			template <typename Entity>
			class hash_table_node_type_only;

			template <typename Entity, typename HashCachePolicy>
			class hash_table_node;


			template <typename Entity>
			class hash_table_local_iter;

			template <typename Entity>
			class hash_table_local_kiter;

			template <typename Entity>
			class hash_table_iter;

			template <typename Entity>
			class hash_table_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_BASE_FWD_HPP
