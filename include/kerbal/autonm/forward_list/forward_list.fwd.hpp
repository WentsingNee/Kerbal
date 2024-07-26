/**
 * @file       forward_list.fwd.hpp
 * @brief
 * @date       2021-01-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_FORWARD_LIST_FORWARD_LIST_FWD_HPP
#define KERBAL_AUTONM_FORWARD_LIST_FORWARD_LIST_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>


namespace kerbal
{

	namespace autonm
	{

		namespace detail
		{

			template <typename T>
			class autonm_sl_node;

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T, typename SemiAllocator>
		class forward_list;

	} // namespace autonm

} // namespace kerbal

#endif // KERBAL_AUTONM_FORWARD_LIST_FORWARD_LIST_FWD_HPP
