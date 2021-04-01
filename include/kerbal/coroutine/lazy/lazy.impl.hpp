/**
 * @file       lazy.impl.hpp
 * @brief
 * @date       2021-08-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_LAZY_LAZY_IMPL_HPP
#define KERBAL_COROUTINE_LAZY_LAZY_IMPL_HPP

#include <kerbal/coroutine/config.hpp>

#if KERBAL_SUPPORT_COROUTINE

#include <kerbal/coroutine/lazy/lazy.decl.hpp>
#include <kerbal/coroutine/lazy/detail/lazy_promise_type.impl.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/coroutine/done_coroutine.hpp>
#include <kerbal/coroutine/lazy/bad_lazy.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

		template <typename T>
		lazy<T>::
		lazy(coroutine_handle && handle) KERBAL_NOEXCEPT :
			k_handle(handle)
		{
		}

		template <typename T>
		lazy<T>::
		lazy(lazy && src) KERBAL_NOEXCEPT :
			k_handle(src.k_handle)
		{
			src.k_handle = nullptr;
		}

		template <typename T>
		lazy<T>::
		~lazy()
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
		}

		template <typename T>
		lazy<T> &
		lazy<T>::
		operator=(lazy && src) KERBAL_NOEXCEPT
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
			this->k_handle = src.k_handle;
			src.k_handle = NULL;
			return *this;
		}

		template <typename T>
		void
		lazy<T>::
		empty_generator_check() const
		{
			if (!this->k_handle) {
				kerbal::utility::throw_this_exception_helper<kerbal::coroutine::bad_lazy>::throw_this_exception();
			}
		}

		template <typename T>
		void
		lazy<T>::
		done_generator_check() const
		{
			if (this->k_handle.done()) {
				kerbal::utility::throw_this_exception_helper<kerbal::coroutine::done_coroutine>::throw_this_exception();
			}
		}

		template <typename T>
		T
		lazy<T>::
		operator()()
		{
			this->empty_generator_check();
			this->done_generator_check();
			this->k_handle.resume();
			return this->k_handle.promise().get_return_value();
		}

		template <typename T>
		void
		lazy<T>::
		swap(lazy & with) KERBAL_NOEXCEPT
		{
			kerbal::algorithm::swap(this->k_handle, with.k_handle);
		}

	} // namespace coroutine

} // namespace kerbal

#endif

#endif // KERBAL_COROUTINE_LAZY_LAZY_IMPL_HPP
