/**
 * @file       lazy_promise_type.decl.hpp
 * @brief
 * @date       2023-08-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_LAZY_DETAIL_LAZY_PROMISE_TYPE_DECL_HPP
#define KERBAL_COROUTINE_LAZY_DETAIL_LAZY_PROMISE_TYPE_DECL_HPP

#include <kerbal/coroutine/detail/exp_compat.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/optional/optional.hpp>
#include <kerbal/utility/forward.hpp>


namespace kerbal
{

	namespace coroutine
	{

		namespace detail
		{

			struct llazy_promise_type_base
			{

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

			};



			template <typename T>
			class lazy_promise_type;


			template <typename T>
			class lazy_promise_type :
				public kerbal::coroutine::detail::llazy_promise_type_base
			{
					typedef kerbal::coroutine::lazy<T> lazy;
					friend lazy;
					typedef costd::coroutine_handle<lazy_promise_type> coroutine_handle;

				private:
					kerbal::optional::optional<T> k_returned_value;

				public:

					template <typename U>
					void return_value(U && value);

					lazy get_return_object();

					T & get_return_value() KERBAL_NOEXCEPT;
			};

			template <>
			class lazy_promise_type<void> :
				public kerbal::coroutine::detail::llazy_promise_type_base
			{
					typedef kerbal::coroutine::lazy<void> lazy;
					friend lazy;
					typedef costd::coroutine_handle<lazy_promise_type> coroutine_handle;

				public:
					static
					void return_void() KERBAL_NOEXCEPT;

					lazy get_return_object();

					void get_return_value() KERBAL_NOEXCEPT;
			};

		} // namespace detail

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_LAZY_DETAIL_LAZY_PROMISE_TYPE_DECL_HPP
