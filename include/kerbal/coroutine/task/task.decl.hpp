/**
 * @file       task.decl.hpp
 * @brief
 * @date       2021-08-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_TASK_TASK_DECL_HPP
#define KERBAL_COROUTINE_TASK_TASK_DECL_HPP

#include <kerbal/coroutine/config.hpp>

#if KERBAL_SUPPORT_COROUTINE

#include <kerbal/coroutine/detail/exp_compat.hpp>
#include <kerbal/coroutine/task/task.fwd.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/optional/optional.hpp>

#include <stdexcept>


namespace kerbal
{

	namespace coroutine
	{

		class bad_task :
			public std::runtime_error
		{
				typedef std::runtime_error super;

			public:
				bad_task() :
					super("bad task")
				{
				}
		};



		namespace detail
		{

			class task_promise_base
			{
				public:

					static
					costd::suspend_never
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

			};

			template <typename T>
			class task_promise :
				public task_promise_base
			{
					friend class kerbal::coroutine::task<T>;

				private:
					kerbal::optional::optional<T> k_value;

				public:

					template <typename U>
					void return_value(U && value);

					T const & get() const;

					bool ready() const;

					task<T> get_return_object();

			};



			template <>
			class task_promise<void> :
				public task_promise_base
			{
				private:
					bool k_ready;

				public:

					task_promise() KERBAL_NOEXCEPT;

					void return_void();

					void get() const;

					bool ready() const;

					task<void> get_return_object();

			};

		} // namespace detail



		template <typename T>
		class task_awaiter
		{
				friend class kerbal::coroutine::task<T>;

			private:
				typedef kerbal::coroutine::task<T> task;
//				typedef typename task::promise_type promise;
				task const * k_task;

				task_awaiter(task const * task);

			public:
				bool await_ready() const KERBAL_NOEXCEPT;

				void await_suspend(costd::coroutine_handle<> h) const KERBAL_NOEXCEPT;

				T const & await_resume() const;
		};



		template <>
		class task_awaiter<void>
		{
				friend class kerbal::coroutine::task<void>;

			private:
				typedef kerbal::coroutine::task<void> task;
//				typedef typename task::promise_type promise;
				task const * k_task;

				task_awaiter(task const * task);

			public:
				bool await_ready() const KERBAL_NOEXCEPT;

				void await_suspend(costd::coroutine_handle<> h) const KERBAL_NOEXCEPT;

				void await_resume() const;
		};



		template <typename T>
		class task
		{
			public:
				typedef kerbal::coroutine::detail::task_promise<T> promise_type;
				friend class kerbal::coroutine::task_awaiter<T>;
				friend class kerbal::coroutine::detail::task_promise<T>;

			private:
				typedef costd::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle k_handle;

			private:
				explicit
				task(coroutine_handle && handle) KERBAL_NOEXCEPT;

			public:
				task() = default;

				task(task const &) = delete;

				task(task && src) KERBAL_NOEXCEPT;

				~task();

				task & operator=(task const &) = delete;

				task & operator=(task && src) KERBAL_NOEXCEPT;

				task_awaiter<T> operator co_await() const;

				void operator()();

				bool ready() const;

				kerbal::optional::optional<T> get() const
				{
					return k_handle.promise().k_value;
				}

//				task<void> wait_ready() const;

				void swap(task & with) KERBAL_NOEXCEPT;

		};



		template <>
		class task<void>
		{
			public:
				typedef kerbal::coroutine::detail::task_promise<void> promise_type;
				friend class kerbal::coroutine::task_awaiter<void>;
				friend class kerbal::coroutine::detail::task_promise<void>;

			private:
				typedef costd::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle k_handle;

			private:
				explicit
				task(coroutine_handle && handle) KERBAL_NOEXCEPT;

			public:
				task() = default;

				task(task const &) = delete;

				task(task && src) KERBAL_NOEXCEPT;

				~task();

				task & operator=(task const &) = delete;

				task & operator=(task && src) KERBAL_NOEXCEPT;

				task_awaiter<void> operator co_await() const;

				void operator()();

				bool ready() const;

				void swap(task & with) KERBAL_NOEXCEPT;

		};

	} // namespace coroutine

} // namespace kerbal

#endif

#endif // KERBAL_COROUTINE_TASK_TASK_DECL_HPP
