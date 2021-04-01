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
		namespace co_ns = std;

		template <typename Promise>
		const auto &
		exp_coroutine_handle_remove_const(const co_ns::coroutine_handle<Promise> & handle)
		{
			return handle;
		}

#	elif KERBAL_COROUTINE_STD_LIB_ID == KERBAL_COROUTINE_STD_LIB_ID_STD_EXP
		namespace co_ns = std::experimental;

		template <typename Promise>
		auto &
		exp_coroutine_handle_remove_const(const co_ns::coroutine_handle<Promise> & handle)
		{
			return const_cast<co_ns::coroutine_handle<Promise> &>(handle);
		}

#	endif

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_DETAIL_CONFIG_HPP
