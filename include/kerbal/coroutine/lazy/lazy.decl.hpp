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

#include <kerbal/coroutine/detail/config.hpp>
#include <kerbal/coroutine/lazy/lazy.fwd.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/optional/optional.hpp>
#include <kerbal/utility/forward.hpp>

#include <stdexcept>
#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

		namespace detail
		{

			struct lazy_promise_type_base
			{

					static costd::suspend_always initial_suspend() KERBAL_NOEXCEPT 
					{
						return {};
					}

					static costd::suspend_always final_suspend() KERBAL_NOEXCEPT
					{
						return {};
					}

					static void unhandled_exception()
					{
						throw;
					}

			};

		} // namespace detail



		class bad_lazy : public std::runtime_error
		{
				typedef std::runtime_error super;

			public:
				bad_lazy() :
						super("bad lazy")
				{
				}
		};



		template <typename T>
		class lazy
		{
			public:
				class promise_type;

			private:
				typedef costd::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle k_handle;

			public:
				class promise_type : public detail::lazy_promise_type_base
				{
						friend class lazy;

					private:
						kerbal::optional::optional<T> k_returned_value;

					public:

						template <typename U>
						void return_value(U && value)
						{
							k_returned_value.emplace(kerbal::utility::forward<U>(value));
						}

						lazy get_return_object()
						{
							return lazy(coroutine_handle::from_promise(*this));
						}
				};

			private:
				explicit
				lazy(coroutine_handle && handle) KERBAL_NOEXCEPT;

			public:
				lazy() = default;

				lazy(const lazy &) = delete;

				lazy(lazy && src) KERBAL_NOEXCEPT;

				~lazy() KERBAL_NOEXCEPT;

				lazy & operator=(const lazy &) = delete;

				lazy & operator=(lazy && src) KERBAL_NOEXCEPT;

				T operator()();

				void swap(lazy & with) KERBAL_NOEXCEPT;

		};



		template <>
		class lazy<void>
		{
			public:
				class promise_type;

			private:
				typedef costd::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle k_handle;

			public:
				class promise_type : public detail::lazy_promise_type_base
				{
					public:
						static void return_void() KERBAL_NOEXCEPT
						{
						}

						lazy get_return_object()
						{
							return lazy(coroutine_handle::from_promise(*this));
						}
				};

			private:
				explicit
				lazy(coroutine_handle && handle) KERBAL_NOEXCEPT;

			public:
				lazy() = default;

				lazy(const lazy &) = delete;

				lazy(lazy && src) KERBAL_NOEXCEPT;

				~lazy() KERBAL_NOEXCEPT;

				lazy & operator=(const lazy &) = delete;

				lazy & operator=(lazy && src) KERBAL_NOEXCEPT;

				void operator()();

				void swap(lazy & with) KERBAL_NOEXCEPT;

		};

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_LAZY_LAZY_DECL_HPP
