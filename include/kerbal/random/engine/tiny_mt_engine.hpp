/**
 * @file       tiny_mt_engine.hpp
 * @brief
 * @date       tiny_mt_engine.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_TINY_MT_ENGINE_HPP
#define KERBAL_RANDOM_ENGINE_TINY_MT_ENGINE_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>

//#include </usr/local/include/c++/v1/random>
#include <random>


namespace kerbal
{

	namespace random
	{

		class tiny_mt32
		{
				typedef kerbal::compatibility::uint32_t uint32_t;

				uint32_t mat1;
				uint32_t mat2;
				uint32_t tmat;
				uint32_t status[4];

				tiny_mt32(uint32_t seed)
				{
				}
		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_TINY_MT_ENGINE_HPP
