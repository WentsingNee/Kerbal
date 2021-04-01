/**
 * @file       generator.impl.hpp
 * @brief
 * @date       2021-08-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_GENERATOR_GENERATOR_IMPL_HPP
#define KERBAL_COROUTINE_GENERATOR_GENERATOR_IMPL_HPP

#include <kerbal/coroutine/config.hpp>

#if KERBAL_SUPPORT_COROUTINE

#include <kerbal/coroutine/generator/generator.decl.hpp>
#include <kerbal/coroutine/generator/detail/generator_iterator.impl.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/coroutine/done_coroutine.hpp>

#include <memory>

#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

		template <typename T, typename Allocator>
		generator<T, Allocator>::
		generator(coroutine_handle && handle) KERBAL_NOEXCEPT :
			k_handle(handle)
		{
		}

		template <typename T, typename Allocator>
		generator<T, Allocator>::
		generator(generator && src) KERBAL_NOEXCEPT :
			k_handle(src.k_handle)
		{
			src.k_handle = nullptr;
		}

		template <typename T, typename Allocator>
		generator<T, Allocator>::
		~generator()
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
		}

		template <typename T, typename Allocator>
		generator<T, Allocator> &
		generator<T, Allocator>::
		operator=(generator && src) KERBAL_NOEXCEPT
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
			this->k_handle = src.k_handle;
			src.k_handle = nullptr;
			return *this;
		}

		template <typename T, typename Allocator>
		void
		generator<T, Allocator>::
		empty_generator_check() const
		{
			if (this->empty()) {
				kerbal::utility::throw_this_exception_helper<bad_generator>::throw_this_exception();
			}
		}

		template <typename T, typename Allocator>
		void
		generator<T, Allocator>::
		done_generator_check() const
		{
			if (this->done()) {
				kerbal::utility::throw_this_exception_helper<done_coroutine>::throw_this_exception();
			}
		}

		template <typename T, typename Allocator>
		T const &
		generator<T, Allocator>::
		operator()()
		{
			empty_generator_check();
			this->k_handle.resume();
			done_generator_check();
			return this->k_handle.promise().k_yielded.value();
		}

		template <typename T, typename Allocator>
		typename
		generator<T, Allocator>::iterator
		generator<T, Allocator>::
		begin()
		{
			return iterator(this);
		}

		template <typename T, typename Allocator>
		typename
		generator<T, Allocator>::iterator
		generator<T, Allocator>::
		end() KERBAL_NOEXCEPT
		{
			return iterator(nullptr);
		}

		template <typename T, typename Allocator>
		bool
		generator<T, Allocator>::
		empty() const KERBAL_NOEXCEPT
		{
			return !static_cast<bool>(this->k_handle);
		}

		template <typename T, typename Allocator>
		bool
		generator<T, Allocator>::
		done() const
		{
			this->empty_generator_check();
			return this->k_handle.done();
		}

		template <typename T, typename Allocator>
		void
		generator<T, Allocator>::
		swap(generator & with) KERBAL_NOEXCEPT
		{
			kerbal::algorithm::swap(this->k_handle, with.k_handle);
		}

	} // namespace coroutine

} // namespace kerbal

#endif

#endif // KERBAL_COROUTINE_GENERATOR_GENERATOR_IMPL_HPP
