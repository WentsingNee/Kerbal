/**
 * @file       runtimer_timer.hpp
 * @brief
 * @date       2019-9-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

 // originate from file exe_serve.hpp

#ifndef KERBAL_TEST_RUNTIME_TIMER_HPP_
#define KERBAL_TEST_RUNTIME_TIMER_HPP_

#include <kerbal/compatibility/tick_count.h>
#include <kerbal/utility/noncopyable.hpp>

namespace kerbal
{
	namespace test
	{

		class runtime_timer: kerbal::utility::noncopyable
		{
			protected:
				const unsigned long start_time;

			public:

				runtime_timer() :
						start_time(GetTickCount())
				{
				}

				unsigned long count() const
				{
					unsigned long time_cost = ::GetTickCount() - this->start_time;
					return time_cost;
				}
		};

	} //namespace test

} //namespace kerbal


#endif	/* End KERBAL_TEST_RUNTIME_TIMER_HPP_ */
