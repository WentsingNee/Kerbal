/**
 * @file       knuth_b_engine.hpp
 * @brief
 * @date       2021-02-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_KNUTH_B_ENGINE_HPP
#define KERBAL_RANDOM_ENGINE_KNUTH_B_ENGINE_HPP

#include <kerbal/random/engine/linear_congruential_engine.hpp>
#include <kerbal/random/engine/shuffle_order_engine.hpp>

namespace kerbal
{

	namespace random
	{

		typedef kerbal::random::shuffle_order_engine<kerbal::random::minstd_rand0, 256> knuth_b;

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_KNUTH_B_ENGINE_HPP
