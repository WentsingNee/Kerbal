/**
 * @file       lazy.decl.hpp
 * @brief
 * @date       2021-08-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_LAZY_LAZY_DECL_HPP
#define KERBAL_COROUTINE_LAZY_LAZY_DECL_HPP

#include <kerbal/coroutine/config.hpp>

#if KERBAL_SUPPORT_COROUTINE

#include <kerbal/coroutine/detail/exp_compat.hpp>
#include <kerbal/coroutine/lazy/lazy.fwd.hpp>
#include <kerbal/coroutine/lazy/detail/lazy_promise_type.decl.hpp>

#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

		template <typename T>
		class lazy
		{
			public:
				typedef kerbal::coroutine::detail::lazy_promise_type<T> promise_type;
				friend promise_type;

			private:
				typedef costd::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle k_handle;

			private:
				explicit
				lazy(coroutine_handle && handle) KERBAL_NOEXCEPT;

			public:
				lazy() = default;

				lazy(lazy const &) = delete;

				lazy(lazy && src) KERBAL_NOEXCEPT;

				~lazy();

				lazy & operator=(lazy const &) = delete;

				lazy & operator=(lazy && src) KERBAL_NOEXCEPT;

			protected:
				void empty_generator_check() const;

				void done_generator_check() const;

			public:
				T operator()();

				void swap(lazy & with) KERBAL_NOEXCEPT;

		};

	} // namespace coroutine

} // namespace kerbal

#endif

#endif // KERBAL_COROUTINE_LAZY_LAZY_DECL_HPP
