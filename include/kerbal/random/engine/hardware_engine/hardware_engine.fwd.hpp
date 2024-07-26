/**
 * @file       hardware_engine.fwd.hpp
 * @brief
 * @date       2024-04-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_HARDWARE_ENGINE_HARDWARE_ENGINE_FWD_HPP
#define KERBAL_RANDOM_ENGINE_HARDWARE_ENGINE_HARDWARE_ENGINE_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/fixed_width_integer.hpp> // explicit import


namespace kerbal
{

	namespace random
	{

		KERBAL_MODULE_EXPORT
		template <typename ResultType>
		class hardware_engine;

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_HARDWARE_ENGINE_HARDWARE_ENGINE_FWD_HPP
