/**
 * @file       lazy.hpp
 * @brief
 * @date       2021-03-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_LAZY_HPP
#define KERBAL_COROUTINE_LAZY_HPP

#include <kerbal/coroutine/detail/config.hpp>
#include <kerbal/coroutine/done_coroutine.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/optional/optional.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/reference_wrapper.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <stdexcept>


namespace kerbal
{

	namespace coroutine
	{

		template <typename T = void>
		class lazy;

		namespace detail
		{

			struct lazy_promise_type_base
			{
					static co_ns::suspend_always initial_suspend() KERBAL_NOEXCEPT
					{
						return {};
					}

					static co_ns::suspend_always final_suspend() KERBAL_NOEXCEPT
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
				typedef co_ns::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle _K_handle;

			public:
				class promise_type : public detail::lazy_promise_type_base
				{
						friend class lazy;

					private:
						kerbal::optional::optional<T> _K_return_v;

					public:
						void return_value(const T & value)
						{
							_K_return_v = value;
						}

						void return_value(T && value)
						{
							_K_return_v = kerbal::compatibility::move(value);
						}

						template <typename U>
						void return_value(U && value)
						{
							_K_return_v.emplace(kerbal::utility::forward<U>(value));
						}

						auto get_return_object()
						{
							return lazy(coroutine_handle::from_promise(*this));
						}
				};

			private:
				explicit
				lazy(coroutine_handle && handle) KERBAL_NOEXCEPT
						: _K_handle(handle)
				{
				}

			public:

				lazy() = default;

				lazy(lazy && src) KERBAL_NOEXCEPT
						: _K_handle(src._K_handle)
				{
					src._K_handle = nullptr;
				}

				~lazy() KERBAL_NOEXCEPT
				{
					if (_K_handle) {
						_K_handle.destroy();
					}
				}

				lazy & operator=(const lazy &) = delete;

				lazy & operator=(lazy && src) KERBAL_NOEXCEPT
				{
					if (this->_K_handle) {
						this->_K_handle.destroy();
					}
					this->_K_handle = src._K_handle;
					src._K_handle = nullptr;
					return *this;
				}

				T operator()() const
				{
					if (!_K_handle) {
						kerbal::utility::throw_this_exception_helper<bad_lazy>::throw_this_exception();
					}
					if (_K_handle.done()) {
						kerbal::utility::throw_this_exception_helper<done_coroutine>::throw_this_exception();
					}
					exp_coroutine_handle_remove_const(_K_handle).resume();
					return _K_handle.promise()._K_return_v.value();
				}

		};


		template <typename T>
		class lazy<T&>
		{
			public:
				class promise_type;

			private:
				typedef co_ns::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle _K_handle;

			public:
				class promise_type : public detail::lazy_promise_type_base
				{
						friend class lazy;

					private:
						T * _K_return_v = nullptr;

					public:
						void return_value(T & value) KERBAL_NOEXCEPT
						{
							_K_return_v = &value;
						}

						void return_value(T && value) = delete;

						auto get_return_object()
						{
							return lazy(coroutine_handle::from_promise(*this));
						}
				};

			private:
				explicit
				lazy(coroutine_handle && handle) KERBAL_NOEXCEPT
						: _K_handle(handle)
				{
				}

			public:

				lazy() = default;

				lazy(lazy && src) KERBAL_NOEXCEPT
						: _K_handle(src._K_handle)
				{
					src._K_handle = nullptr;
				}

				~lazy() KERBAL_NOEXCEPT
				{
					if (_K_handle) {
						_K_handle.destroy();
					}
				}

				lazy & operator=(const lazy &) = delete;

				lazy & operator=(lazy && src) KERBAL_NOEXCEPT
				{
					if (this->_K_handle) {
						this->_K_handle.destroy();
					}
					this->_K_handle = src._K_handle;
					src._K_handle = nullptr;
					return *this;
				}

				T& operator()() const
				{
					if (!_K_handle) {
						kerbal::utility::throw_this_exception_helper<bad_lazy>::throw_this_exception();
					}
					if (_K_handle.done()) {
						kerbal::utility::throw_this_exception_helper<done_coroutine>::throw_this_exception();
					}
					exp_coroutine_handle_remove_const(_K_handle).resume();
					return *_K_handle.promise()._K_return_v;
				}

		};


		template <>
		class lazy<void>
		{
			public:
				class promise_type;

			private:
				typedef co_ns::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle _K_handle;

			public:
				class promise_type : public detail::lazy_promise_type_base
				{
					public:
						static void return_void() KERBAL_NOEXCEPT
						{
						}

						auto get_return_object()
						{
							return lazy(coroutine_handle::from_promise(*this));
						}
				};

			private:
				explicit
				lazy(coroutine_handle && handle) KERBAL_NOEXCEPT
						: _K_handle(handle)
				{
				}

			public:

				lazy() = default;

				lazy(lazy && src) KERBAL_NOEXCEPT
						: _K_handle(src._K_handle)
				{
					src._K_handle = nullptr;
				}

				~lazy() KERBAL_NOEXCEPT
				{
					if (_K_handle) {
						_K_handle.destroy();
					}
				}

				lazy & operator=(const lazy &) = delete;

				lazy & operator=(lazy && src) KERBAL_NOEXCEPT
				{
					if (this->_K_handle) {
						this->_K_handle.destroy();
					}
					this->_K_handle = src._K_handle;
					src._K_handle = nullptr;
					return *this;
				}

				void operator()() const
				{
					if (!_K_handle) {
						kerbal::utility::throw_this_exception_helper<bad_lazy>::throw_this_exception();
					}
					if (_K_handle.done()) {
						kerbal::utility::throw_this_exception_helper<done_coroutine>::throw_this_exception();
					}
					exp_coroutine_handle_remove_const(_K_handle).resume();
				}

		};

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_LAZY_HPP
