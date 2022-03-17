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

#ifndef KERBAL_HASH_TABLE_BASE_FWD_HPP
#define KERBAL_HASH_TABLE_BASE_FWD_HPP

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Extract, typename HashCachePolicy>
			class hash_table_base;

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

#endif // KERBAL_HASH_TABLE_BASE_FWD_HPP
