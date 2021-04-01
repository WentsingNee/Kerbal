/**
 * @file       over_aligned_new.hpp
 * @brief
 * @date       2021-02-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_NEW_OVER_ALIGNED_NEW_HPP
#define KERBAL_MEMORY_NEW_OVER_ALIGNED_NEW_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/bad_alloc.hpp>
#include <kerbal/memory/new/nothrow_new.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

#ifdef __STDCPP_DEFAULT_NEW_ALIGNMENT__
		typedef kerbal::type_traits::integral_constant<std::size_t, __STDCPP_DEFAULT_NEW_ALIGNMENT__> DEFAULT_ALIGNMENT;
#else
		typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(void*)> DEFAULT_ALIGNMENT;
#endif

		struct align_val_t
		{
				std::size_t val;

				KERBAL_CONSTEXPR
				align_val_t(std::size_t val = kerbal::memory::DEFAULT_ALIGNMENT::value) KERBAL_NOEXCEPT
						: val(val)
				{
				}

				KERBAL_CONSTEXPR
				operator std::size_t() const KERBAL_NOEXCEPT
				{
					return val;
				}
		};

		namespace detail
		{

			KERBAL_CONSTEXPR
			inline
			std::size_t raw_alloc_size_with_align(std::size_t size, kerbal::memory::align_val_t align) KERBAL_NOEXCEPT
			{
				return size + align;
			}

		} // namespace detail

	} // namespace memory

} // namespace kerbal


inline
void * operator new(std::size_t size, kerbal::memory::align_val_t align, kerbal::memory::nothrow_t nothrow_new_tag) KERBAL_NOEXCEPT
{
	if (align <= kerbal::memory::DEFAULT_ALIGNMENT::value) {
		return ::operator new(size, nothrow_new_tag); // kerbal non-throwing new
	}

	void * const p_raw = ::operator new(kerbal::memory::detail::raw_alloc_size_with_align(size, align), nothrow_new_tag); // kerbal non-throwing new

	if (p_raw == NULL) {
		return NULL;
	}

	void ** p = static_cast<void **>(p_raw);
	++p;
	{
		std::size_t z = reinterpret_cast<std::size_t>(p);
		z &= ~(align - 1);
		z += align;
		p = reinterpret_cast<void**>(z);
	}
	*(p - 1) = p_raw;
	return static_cast<void*>(p);
}

inline
void operator delete(void * p, std::size_t size, kerbal::memory::align_val_t align, kerbal::memory::nothrow_t nothrow_new_tag) KERBAL_NOEXCEPT
{
	if (align <= kerbal::memory::DEFAULT_ALIGNMENT::value) {
		::operator delete(p, size, nothrow_new_tag); // kerbal non-throwing delete
		return;
	}

	if (p == NULL) {
		return;
	}

	void * p_raw = *(static_cast<void**>(p) - 1);
	::operator delete(p_raw, kerbal::memory::detail::raw_alloc_size_with_align(size, align), nothrow_new_tag); // kerbal non-throwing delete
}

inline
void * operator new[](std::size_t size, kerbal::memory::align_val_t align, kerbal::memory::nothrow_t nothrow_new_tag) KERBAL_NOEXCEPT
{
	return ::operator new(size, align, nothrow_new_tag);
}

inline
void operator delete[](void * p, std::size_t size, kerbal::memory::align_val_t align, kerbal::memory::nothrow_t nothrow_new_tag) KERBAL_NOEXCEPT
{
	::operator delete(p, size, align, nothrow_new_tag);
}



inline
void * operator new(std::size_t size, kerbal::memory::align_val_t align)
{
	void * p = ::operator new(size, align, kerbal::memory::nothrow_t()); // kerbal aligned non-throwing new
	if (p == NULL) {
		kerbal::memory::bad_alloc::throw_this_exception();
	}
	return p;
}

inline
void operator delete(void * p, std::size_t size, kerbal::memory::align_val_t align) KERBAL_NOEXCEPT
{
	::operator delete(p, size, align, kerbal::memory::nothrow_t()); // kerbal aligned non-throwing delete
}

inline
void * operator new[](std::size_t size, kerbal::memory::align_val_t align)
{
	return ::operator new(size, align);
}

inline
void operator delete[](void * p, std::size_t size, kerbal::memory::align_val_t align) KERBAL_NOEXCEPT
{
	::operator delete(p, size, align);
}


#endif // KERBAL_MEMORY_NEW_OVER_ALIGNED_NEW_HPP
