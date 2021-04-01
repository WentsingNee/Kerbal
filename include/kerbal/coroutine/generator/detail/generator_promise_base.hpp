/**
 * @file       generator_promise_base.hpp
 * @brief
 * @date       2023-08-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_GENERATOR_DETAIL_GENERATOR_PROMISE_BASE_HPP
#define KERBAL_COROUTINE_GENERATOR_DETAIL_GENERATOR_PROMISE_BASE_HPP

#include <kerbal/coroutine/detail/exp_compat.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>


namespace kerbal
{

	namespace coroutine
	{

		namespace detail
		{

			class generator_promise_base
			{
				public:
					static
					costd::suspend_always
					initial_suspend() KERBAL_NOEXCEPT
					{
						return {};
					}

					static
					costd::suspend_always
					final_suspend() KERBAL_NOEXCEPT
					{
						return {};
					}

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
					static
					void unhandled_exception()
					{
						throw;
					}
#			endif

					static
					void return_void() KERBAL_NOEXCEPT
					{
					}

			};

		} // namespace detail

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_GENERATOR_DETAIL_GENERATOR_PROMISE_BASE_HPP
