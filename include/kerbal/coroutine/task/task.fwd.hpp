/**
 * @file       task.fwd.hpp
 * @brief
 * @date       2021-08-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_TASK_TASK_FWD_HPP
#define KERBAL_COROUTINE_TASK_TASK_FWD_HPP

#include <kerbal/coroutine/config.hpp>

#if KERBAL_SUPPORT_COROUTINE


namespace kerbal
{

	namespace coroutine
	{

		template <typename T = void>
		class task;

		template <typename T = void>
		class task_awaiter;

		class bad_task;

	} // namespace coroutine

} // namespace kerbal

#endif

#endif // KERBAL_COROUTINE_TASK_TASK_FWD_HPP
