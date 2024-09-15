/**
 * @file       generator_iterator.impl.hpp
 * @brief
 * @date       2023-08-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_GENERATOR_DETAIL_GENERATOR_ITERATOR_IMPL_HPP
#define KERBAL_COROUTINE_GENERATOR_DETAIL_GENERATOR_ITERATOR_IMPL_HPP

#include <kerbal/coroutine/generator/detail/generator_iterator.decl.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/coroutine/generator/bad_generator.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

		namespace detail
		{

			template <typename T>
			generator_iterator<T>::
			generator_iterator() KERBAL_NOEXCEPT :
				k_gen(NULL)
			{
			}

			template <typename T>
			generator_iterator<T>::
			generator_iterator(kerbal::coroutine::generator<T> * gen) :
				k_gen(gen)
			{
				if (this->k_gen == NULL) {
					return;
				}
				if (this->k_gen->k_handle == NULL) {
					this->k_gen = NULL;
					return;
				}
				if (this->k_gen->k_handle.done()) {
					return;
				}
				if (!this->k_gen->k_handle.promise().k_yielded.has_value()) {
					gen->k_handle.resume();
				}
			}

			template <typename T>
			bool
			generator_iterator<T>::
			k_is_end() const KERBAL_NOEXCEPT
			{
				if (this->k_gen == NULL) {
					return true;
				}
				return this->k_gen->k_handle.done();
			}

			template <typename T>
			bool
			generator_iterator<T>::
			operator==(generator_iterator const & with) const KERBAL_NOEXCEPT
			{
				if (with.k_gen == NULL) {
					return this->k_is_end();
				}
				return false;
			}

			template <typename T>
			generator_iterator<T> &
			generator_iterator<T>::
			operator++()
			{
				if (this->k_is_end()) {
					kerbal::utility::throw_this_exception_helper<kerbal::coroutine::bad_generator>::throw_this_exception();
				}
				this->k_gen->k_handle.resume();
				return *this;
			}

			template <typename T>
			T const &
			generator_iterator<T>::
			operator*() const
			{
				if (this->k_is_end()) {
					kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
						+"access to end iterator"
					);
				}
				return this->k_gen->k_handle.promise().k_yielded.value();
			}

		} // namespace detail

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_GENERATOR_DETAIL_GENERATOR_ITERATOR_IMPL_HPP
