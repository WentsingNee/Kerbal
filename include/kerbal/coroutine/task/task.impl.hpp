/**
 * @file       task.impl.hpp
 * @brief
 * @date       2021-08-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_TASK_TASK_IMPL_HPP
#define KERBAL_COROUTINE_TASK_TASK_IMPL_HPP

#include <kerbal/coroutine/config.hpp>

#if KERBAL_SUPPORT_COROUTINE

#include <kerbal/coroutine/task/task.decl.hpp>

#include <kerbal/coroutine/done_coroutine.hpp>


namespace kerbal
{

	namespace coroutine
	{

		namespace detail
		{

		//===================
		// task_promise

			template <typename T>
			template <typename U>
			void
			task_promise<T>::
			return_value(U && value)
			{
				k_value.emplace(kerbal::utility::forward<U>(value));
			}

			template <typename T>
			T const &
			task_promise<T>::
			get() const
			{
				return k_value.value();
			}

			template <typename T>
			bool
			task_promise<T>::
			ready() const
			{
				return k_value.has_value();
			}

			template <typename T>
			task<T>
			task_promise<T>::
			get_return_object()
			{
				return task<T>(task<T>::coroutine_handle::from_promise(*this));
			}



		//===================
		// task_promise<void>

			inline
			task_promise<void>::
			task_promise() KERBAL_NOEXCEPT :
				k_ready(false)
			{
			}

			inline
			void
			task_promise<void>::
			return_void()
			{
				k_ready = true;
			}

			inline
			void
			task_promise<void>::
			get() const
			{
			}

			inline
			bool
			task_promise<void>::
			ready() const
			{
				return k_ready;
			}

			inline
			task<void>
			task_promise<void>::
			get_return_object()
			{
				return task<void>(task<void>::coroutine_handle::from_promise(*this));
			}

		} // namespace detail



	//===================
	// task_awaiter

		template <typename T>
		task_awaiter<T>::
		task_awaiter(const task * task) :
			k_task(task)
		{
		}

		template <typename T>
		bool
		task_awaiter<T>::
		await_ready() const KERBAL_NOEXCEPT
		{
			return k_task->k_handle.promise().ready();
		}

		template <typename T>
		void
		task_awaiter<T>::
		await_suspend(costd::coroutine_handle<> h) const KERBAL_NOEXCEPT
		{
		}

		template <typename T>
		T const &
		task_awaiter<T>::
		await_resume() const
		{
			return k_task->k_handle.promise().get();
		}



	//===================
	// task_awaiter<void>

		inline
		task_awaiter<void>::
		task_awaiter(task const * task) :
			k_task(task)
		{
		}

		inline
		bool
		task_awaiter<void>::
		await_ready() const KERBAL_NOEXCEPT
		{
			return k_task->k_handle.promise().ready();
		}

		inline
		void
		task_awaiter<void>::
		await_suspend(costd::coroutine_handle<> h) const KERBAL_NOEXCEPT
		{
		}

		inline
		void
		task_awaiter<void>::
		await_resume() const
		{
		}



	//===================
	// task<T>

		template <typename T>
		task<T>::
		task(coroutine_handle && handle) KERBAL_NOEXCEPT :
			k_handle(handle)
		{
		}

		template <typename T>
		task<T>::
		task(task && src) KERBAL_NOEXCEPT :
			k_handle(src.k_handle)
		{
			src.k_handle = nullptr;
		}

		template <typename T>
		task<T>::
		~task()
		{
			if (k_handle) {
				k_handle.destroy();
			}
		}

		template <typename T>
		task<T> &
		task<T>::
		operator=(task && src) KERBAL_NOEXCEPT
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
			this->k_handle = src.k_handle;
			src.k_handle = nullptr;
			return *this;
		}

		template <typename T>
		task_awaiter<T>
		task<T>::
		operator co_await() const
		{
			return task_awaiter<T>(this);
		}

		template <typename T>
		void
		task<T>::
		operator()()
		{
			if (!k_handle) {
				kerbal::utility::throw_this_exception_helper<bad_task>::throw_this_exception();
			}
			if (k_handle.done()) {
				kerbal::utility::throw_this_exception_helper<done_coroutine>::throw_this_exception();
			}
			k_handle.resume();
		}

		template <typename T>
		bool
		task<T>::
		ready() const
		{
			return k_handle.promise().ready();
		}

//		template <typename T>
//		task<void>
//		task<T>::
//		wait_ready() const
//		{
//			while (!this->ready()) {
//				co_await costd::suspend_always{};
//			}
//		}

		template <typename T>
		void
		task<T>::
		swap(task & with) KERBAL_NOEXCEPT
		{
			kerbal::algorithm::swap(this->k_handle, with.k_handle);
		}



	//===================
	// task<void>

		inline
		task<void>::
		task(coroutine_handle && handle) KERBAL_NOEXCEPT :
			k_handle(handle)
		{
		}

		inline
		task<void>::
		task(task && src) KERBAL_NOEXCEPT :
			k_handle(src.k_handle)
		{
			src.k_handle = nullptr;
		}

		inline
		task<void>::
		~task()
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
		}

		inline
		task<void> &
		task<void>::
		operator=(task && src) KERBAL_NOEXCEPT
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
			this->k_handle = src.k_handle;
			src.k_handle = nullptr;
			return *this;
		}

		inline
		task_awaiter<void>
		task<void>::
		operator co_await() const
		{
			return task_awaiter<void>(this);
		}

		inline
		void
		task<void>::
		operator()()
		{
			if (!this->k_handle) {
				kerbal::utility::throw_this_exception_helper<bad_task>::throw_this_exception();
			}
			if (this->k_handle.done()) {
				kerbal::utility::throw_this_exception_helper<done_coroutine>::throw_this_exception();
			}
			this->k_handle.resume();
		}

		inline
		bool
		task<void>::
		ready() const
		{
			return this->k_handle.promise().ready();
		}

		inline
		void
		task<void>::
		swap(task & with) KERBAL_NOEXCEPT
		{
			kerbal::algorithm::swap(this->k_handle, with.k_handle);
		}

	} // namespace coroutine

} // namespace kerbal

#endif

#endif // KERBAL_COROUTINE_TASK_TASK_IMPL_HPP
