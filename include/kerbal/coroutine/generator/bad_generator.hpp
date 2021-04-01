/**
 * @file       bad_generator.hpp
 * @brief
 * @date       2023-08-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_GENERATOR_BAD_GENERATOR_HPP
#define KERBAL_COROUTINE_GENERATOR_BAD_GENERATOR_HPP

#include <kerbal/coroutine/generator/generator.fwd.hpp>

#include <stdexcept>


namespace kerbal
{

	namespace coroutine
	{

		class bad_generator :
			public std::runtime_error
		{
				typedef std::runtime_error super;

			public:
				bad_generator() :
					super("bad generator")
				{
				}

			protected:
				explicit bad_generator(char const * msg) :
					super(msg)
				{
				}
		};

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_GENERATOR_BAD_GENERATOR_HPP
