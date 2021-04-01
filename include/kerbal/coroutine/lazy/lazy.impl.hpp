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

#include <kerbal/coroutine/detail/config.hpp>
#include <kerbal/coroutine/lazy/lazy.decl.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/coroutine/done_coroutine.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

	//===================
	// lazy

		template <typename T>
		lazy<T>::lazy(coroutine_handle && handle) KERBAL_NOEXCEPT
				: k_handle(handle)
		{
		}

		template <typename T>
		lazy<T>::lazy(lazy && src) KERBAL_NOEXCEPT
				: k_handle(src.k_handle)
		{
			src.k_handle = nullptr;
		}

		template <typename T>
		lazy<T>::~lazy() KERBAL_NOEXCEPT
		{
			if (k_handle) {
				k_handle.destroy();
			}
		}

		template <typename T>
		lazy<T> & lazy<T>::operator=(lazy && src) KERBAL_NOEXCEPT
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
			this->k_handle = src.k_handle;
			src.k_handle = NULL;
			return *this;
		}

		template <typename T>
		T lazy<T>::operator()()
		{
			if (!k_handle) {
				kerbal::utility::throw_this_exception_helper<bad_lazy>::throw_this_exception();
			}
			if (k_handle.done()) {
				kerbal::utility::throw_this_exception_helper<done_coroutine>::throw_this_exception();
			}
			k_handle.resume();
			return k_handle.promise().k_returned_value.value();
		}

		template <typename T>
		void lazy<T>::swap(lazy & with) KERBAL_NOEXCEPT
		{
			kerbal::algorithm::swap(this->k_handle, with.k_handle);
		}



	//===================
	// lazy<void>

		inline
		lazy<void>::lazy(coroutine_handle && handle) KERBAL_NOEXCEPT
				: k_handle(handle)
		{
		}

		inline
		lazy<void>::lazy(lazy && src) KERBAL_NOEXCEPT
				: k_handle(src.k_handle)
		{
			src.k_handle = nullptr;
		}

		inline
		lazy<void>::~lazy() KERBAL_NOEXCEPT
		{
			if (k_handle) {
				k_handle.destroy();
			}
		}

		inline
		lazy<void> & lazy<void>::operator=(lazy && src) KERBAL_NOEXCEPT
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
			this->k_handle = src.k_handle;
			src.k_handle = NULL;
			return *this;
		}

		inline
		void lazy<void>::operator()()
		{
			if (!k_handle) {
				kerbal::utility::throw_this_exception_helper<bad_lazy>::throw_this_exception();
			}
			if (k_handle.done()) {
				kerbal::utility::throw_this_exception_helper<done_coroutine>::throw_this_exception();
			}
			k_handle.resume();
		}

		inline
		void lazy<void>::swap(lazy & with) KERBAL_NOEXCEPT
		{
			kerbal::algorithm::swap(this->k_handle, with.k_handle);
		}

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_LAZY_LAZY_IMPL_HPP
