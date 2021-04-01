/**
 * @file       lazy_promise_type.impl.hpp
 * @brief
 * @date       2023-08-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_LAZY_DETAIL_LAZY_PROMISE_TYPE_IMPL_HPP
#define KERBAL_COROUTINE_LAZY_DETAIL_LAZY_PROMISE_TYPE_IMPL_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/optional/optional.hpp>
#include <kerbal/utility/forward.hpp>


namespace kerbal
{

	namespace coroutine
	{

		namespace detail
		{

			template <typename T>
			template <typename U>
			void
			lazy_promise_type<T>::
			return_value(U && value)
			{
				k_returned_value.emplace(kerbal::utility::forward<U>(value));
			}

			template <typename T>
			typename
			lazy_promise_type<T>::lazy
			lazy_promise_type<T>::
			get_return_object()
			{
				return lazy(coroutine_handle::from_promise(*this));
			}

			template <typename T>
			T &
			lazy_promise_type<T>::
			get_return_value() KERBAL_NOEXCEPT
			{
				return this->k_returned_value.value();
			}


			inline
			void
			lazy_promise_type<void>::
			return_void() KERBAL_NOEXCEPT
			{
			}

			inline
			lazy_promise_type<void>::lazy
			lazy_promise_type<void>::
			get_return_object()
			{
				return lazy(coroutine_handle::from_promise(*this));
			}

			inline
			void
			lazy_promise_type<void>::
			get_return_value() KERBAL_NOEXCEPT
			{
				return;
			}

		} // namespace detail

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_LAZY_DETAIL_LAZY_PROMISE_TYPE_IMPL_HPP
