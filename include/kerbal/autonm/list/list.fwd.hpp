/**
 * @file       list.fwd.hpp
 * @brief
 * @date       2021-01-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_LIST_LIST_FWD_HPP
#define KERBAL_AUTONM_LIST_LIST_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>


namespace kerbal
{

	namespace autonm
	{

		namespace detail
		{

			template <typename T>
			class autonm_list_node;

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T, typename SemiAllocator>
		class list;

	} // namespace autonm

} // namespace kerbal

#endif // KERBAL_AUTONM_LIST_LIST_FWD_HPP
