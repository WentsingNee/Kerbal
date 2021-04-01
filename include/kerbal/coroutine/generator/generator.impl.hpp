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

#include <kerbal/coroutine/detail/config.hpp>
#include <kerbal/coroutine/generator/generator.decl.hpp>

#include <kerbal/coroutine/done_coroutine.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/optional/optional.hpp>
#include <kerbal/utility/forward.hpp>

#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

		namespace detail
		{

		//===================
		// generator_iterator<T>

			template <typename T>
			generator_iterator<T>::generator_iterator() KERBAL_NOEXCEPT
					: gen(gen)
			{
			}

			template <typename T>
			generator_iterator<T>::generator_iterator(kerbal::coroutine::generator<T> * gen)
					: gen(gen)
			{
				if (this->gen == NULL) {
					return;
				}
				if (this->gen->k_handle == NULL) {
					this->gen = NULL;
					return;
				}
				if (this->gen->k_handle.done()) {
					return;
				}
				if (!this->gen->k_handle.promise().k_yielded.has_value()) {
					gen->k_handle.resume();
				}
			}

			template <typename T>
			bool generator_iterator<T>::k_is_end() const KERBAL_NOEXCEPT
			{
				if (this->gen == NULL) {
					return true;
				}
				return this->gen->k_handle.done();
			}

			template <typename T>
			bool generator_iterator<T>::operator==(const generator_iterator & with) const KERBAL_NOEXCEPT
			{
				if (with.gen == NULL) {
					return this->k_is_end();
				}
				return false;
			}

			template <typename T>
			generator_iterator<T> & generator_iterator<T>::operator++()
			{
				if (this->k_is_end()) {
					kerbal::utility::throw_this_exception_helper<bad_generator>::throw_this_exception();
				}
				gen->k_handle.resume();
				return *this;
			}

			template <typename T>
			const T & generator_iterator<T>::operator*() const
			{
				if (this->k_is_end()) {
					kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception("access to end iterator");
				}
				return gen->k_handle.promise().k_yielded.value();
			}

		} // namespace detail



	//===================
	// generator<T>

		template <typename T>
		generator<T>::generator(coroutine_handle && handle) KERBAL_NOEXCEPT
				: k_handle(handle)
		{
		}

		template <typename T>
		generator<T>::generator(generator && src) KERBAL_NOEXCEPT
				: k_handle(src.k_handle)
		{
			src.k_handle = nullptr;
		}

		template <typename T>
		generator<T>::~generator() KERBAL_NOEXCEPT
		{
			if (k_handle) {
				k_handle.destroy();
			}
		}

		template <typename T>
		generator<T> & generator<T>::operator=(generator && src) KERBAL_NOEXCEPT
		{
			if (this->k_handle) {
				this->k_handle.destroy();
			}
			this->k_handle = src.k_handle;
			src.k_handle = nullptr;
			return *this;
		}

		template <typename T>
		void generator<T>::empty_generator_check() const
		{
			if (!k_handle) {
				kerbal::utility::throw_this_exception_helper<bad_generator>::throw_this_exception();
			}
		}

		template <typename T>
		void generator<T>::done_generator_check() const
		{
			if (k_handle.done()) {
				kerbal::utility::throw_this_exception_helper<done_coroutine>::throw_this_exception();
			}
		}

		template <typename T>
		const T & generator<T>::operator()()
		{
			empty_generator_check();
			k_handle.resume();
			done_generator_check();
			return k_handle.promise().k_yielded.value();
		}

		template <typename T>
		typename generator<T>::iterator
		generator<T>::begin()
		{
			return iterator(this);
		}

		template <typename T>
		typename generator<T>::iterator
		generator<T>::end() KERBAL_NOEXCEPT
		{
			return iterator(nullptr);
		}

		template <typename T>
		void generator<T>::swap(generator & with) KERBAL_NOEXCEPT
		{
			kerbal::algorithm::swap(this->k_handle, with.k_handle);
		}


	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_GENERATOR_GENERATOR_IMPL_HPP
