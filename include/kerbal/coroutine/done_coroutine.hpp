/**
 * @file       done_coroutine.hpp
 * @brief
 * @date       2021-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_DONE_COROUTINE_HPP
#define KERBAL_COROUTINE_DONE_COROUTINE_HPP

#include <kerbal/utility/throw_this_exception.hpp>

#include <stdexcept>


namespace kerbal
{

	namespace coroutine
	{

		class done_coroutine :
			public std::runtime_error
		{
				typedef std::runtime_error super;

			public:
				done_coroutine() :
					super("done coroutine")
				{
				}

			protected:
				explicit
				done_coroutine(const char * msg) :
					super(msg)
				{
				}
		};

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_DONE_COROUTINE_HPP
