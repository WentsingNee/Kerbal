/**
 * @file       config.hpp
 * @brief
 * @date       2021-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_DETAIL_CONFIG_HPP
#define KERBAL_COROUTINE_DETAIL_CONFIG_HPP

#define KERBAL_COROUTINE_STD_LIB_ID_STD			0
#define KERBAL_COROUTINE_STD_LIB_ID_STD_EXP		1

#if __has_include(<coroutine>)

#	include <coroutine>
#	define KERBAL_COROUTINE_STD_LIB_ID		KERBAL_COROUTINE_STD_LIB_ID_STD

#elif __has_include(<experimental/coroutine>)

#	include <experimental/coroutine>
#	define KERBAL_COROUTINE_STD_LIB_ID		KERBAL_COROUTINE_STD_LIB_ID_STD_EXP

#endif


namespace kerbal
{

	namespace coroutine
	{

#	if KERBAL_COROUTINE_STD_LIB_ID == KERBAL_COROUTINE_STD_LIB_ID_STD

		namespace costd = std;

		template <typename Promise>
		const costd::coroutine_handle<Promise> &
		exp_coroutine_handle_remove_const(const costd::coroutine_handle<Promise> & handle)
		{
			return handle;
		}

#	elif KERBAL_COROUTINE_STD_LIB_ID == KERBAL_COROUTINE_STD_LIB_ID_STD_EXP

		namespace costd = std::experimental;

		template <typename Promise>
		costd::coroutine_handle<Promise> &
		exp_coroutine_handle_remove_const(const costd::coroutine_handle<Promise> & handle)
		{
			return const_cast<costd::coroutine_handle<Promise> &>(handle);
		}

#	endif

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_DETAIL_CONFIG_HPP
