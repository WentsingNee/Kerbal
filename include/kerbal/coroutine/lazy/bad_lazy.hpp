/**
 * @file       bad_lazy.hpp
 * @brief
 * @date       2023-08-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_LAZY_BAD_LAZY_HPP
#define KERBAL_COROUTINE_LAZY_BAD_LAZY_HPP

#include <stdexcept>


namespace kerbal
{

	namespace coroutine
	{

		class bad_lazy :
			public std::runtime_error
		{
				typedef std::runtime_error super;

			public:
				bad_lazy() :
					super("bad lazy")
				{
				}
		};

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_LAZY_BAD_LAZY_HPP
