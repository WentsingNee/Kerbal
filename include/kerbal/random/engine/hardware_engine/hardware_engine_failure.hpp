/**
 * @file       hardware_engine_failure.hpp
 * @brief
 * @date       2024-04-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_HARDWARE_ENGINE_HARDWARE_ENGINE_FAILURE_HPP
#define KERBAL_RANDOM_ENGINE_HARDWARE_ENGINE_HARDWARE_ENGINE_FAILURE_HPP

#include <stdexcept>


namespace kerbal
{

	namespace random
	{

		class hardware_engine_failure :
			public std::runtime_error
		{
			public:
				hardware_engine_failure() :
					std::runtime_error("hardware_engine_failure")
				{
				}
		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_HARDWARE_ENGINE_HARDWARE_ENGINE_FAILURE_HPP
