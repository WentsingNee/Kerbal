/**
 * @file       new_allocator.impl.hpp
 * @brief
 * @date       2023-07-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_NEW_ALLOCATOR_NEW_ALLOCATOR_IMPL_HPP
#define KERBAL_MEMORY_ALLOCATOR_NEW_ALLOCATOR_NEW_ALLOCATOR_IMPL_HPP

#include <kerbal/memory/allocator/new_allocator/new_allocator.decl.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/bad_array_new_length.hpp>
#include <kerbal/memory/basic_t.hpp>
#include <kerbal/memory/new/basic_new.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#if __cplusplus > 201703L
#	include <kerbal/compatibility/is_constant_evaluated.hpp>

#	if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
#		include <memory>
#	endif
#endif

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		inline
		typename
		new_allocator<void>::pointer
		new_allocator<void>::
		allocate(size_type n)
		{
			return ::operator new(n, kerbal::memory::basic_t());
		}

		inline
		void
		new_allocator<void>::
		deallocate(pointer p) KERBAL_NOEXCEPT
		{
			::operator delete(p, kerbal::memory::basic_t());
		}

		inline
		void
		new_allocator<void>::
		deallocate(pointer p, size_type /*n*/) KERBAL_NOEXCEPT
		{
			::operator delete(p, kerbal::memory::basic_t());
		}

		template <typename T>
		KERBAL_CONSTEXPR20
		typename
		new_allocator<T>::pointer
		new_allocator<T>::
		allocate(size_type n)
		{

#	if __cplusplus > 201703L
#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
			if (KERBAL_IS_CONSTANT_EVALUATED()) {
				return std::allocator<T>().allocate(n);
			}
#		endif
#	endif

			if (n > MAX_SIZE::value) {
				kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_array_new_length>::throw_this_exception();
			}
			return static_cast<pointer>(::operator new(n * sizeof(value_type), kerbal::memory::basic_t()));
		}


		template <typename T>
		KERBAL_CONSTEXPR20
		void
		new_allocator<T>::
		deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
		{

#	if __cplusplus > 201703L
#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
			if (KERBAL_IS_CONSTANT_EVALUATED()) {
				if (p != NULL) {
					std::allocator<T>().deallocate(p, n);
				}
				return;
			}
#		endif
#	endif

			::operator delete(p, kerbal::memory::basic_t());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_NEW_ALLOCATOR_NEW_ALLOCATOR_IMPL_HPP
