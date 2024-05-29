/**
 * @file       runtime_timer.hpp
 * @brief
 * @date       2019-9-28
 * @author     Peter
 * @remark     originate from exe_serve.hpp
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TEST_RUNTIME_TIMER_HPP
#define KERBAL_TEST_RUNTIME_TIMER_HPP

#include <kerbal/compatibility/tick_count.hpp>

#ifndef KERBAL_SUPPORTS_RUNTIME_TIMER

#	if KERBAL_SUPPORTS_TICK_COUNT

#		define KERBAL_SUPPORTS_RUNTIME_TIMER 1


#include <kerbal/utility/noncopyable.hpp>


namespace kerbal
{

	namespace test
	{

		class runtime_timer : kerbal::utility::noncopyable
		{
			protected:
				unsigned long start_time;

			public:

				runtime_timer() :
					start_time(kerbal::compatibility::get_tick_count())
				{
				}

				void refresh()
				{
					start_time = kerbal::compatibility::get_tick_count();
				}

				unsigned long count() const
				{
					unsigned long time_cost = kerbal::compatibility::get_tick_count() - this->start_time;
					return time_cost;
				}
		};

	} //namespace test

} //namespace kerbal


#	else // if KERBAL_SUPPORTS_TICK_COUNT

#		define KERBAL_SUPPORTS_RUNTIME_TIMER 0

#	endif // if KERBAL_SUPPORTS_TICK_COUNT

#endif // if KERBAL_SUPPORTS_RUNTIME_TIMER


#endif // KERBAL_TEST_RUNTIME_TIMER_HPP
