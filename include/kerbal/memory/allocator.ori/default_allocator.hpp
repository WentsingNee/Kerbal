/**
 * @file       default_allocator.hpp
 * @brief
 * @date       2021-01-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_ORI_DEFAULT_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_ORI_DEFAULT_ALLOCATOR_HPP

#include <kerbal/memory/allocator/default_allocator/default_allocator.fwd.hpp>

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/memory/allocator/malloc_allocator.hpp>
#include <kerbal/memory/allocator/over_aligned_allocator.hpp>
#include <kerbal/memory/pointer_alignment.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

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

		template <typename T>
		class default_allocator
		{
			public:
				typedef T							value_type;
				typedef value_type *				pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef kerbal::type_traits::true_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::true_type		is_always_equal;

			private:
				typedef kerbal::memory::over_aligned_allocator<value_type, kerbal::memory::malloc_allocator<void> > upstream_allocator;

			public:

#		if __cplusplus < 201103L

				default_allocator() KERBAL_NOEXCEPT
				{
				}

#		else

				default_allocator() = default;

#		endif

				template <typename U>
				KERBAL_CONSTEXPR
				default_allocator(const default_allocator<U> &) KERBAL_NOEXCEPT
				{
				}


				KERBAL_CONSTEXPR14
				size_type minimum_alignment() const KERBAL_NOEXCEPT
				{
					upstream_allocator up_alloc;
					return up_alloc.minimum_alignment();
				}

				KERBAL_CONSTEXPR20
				static pointer allocate(size_type n)
				{

#		if __cplusplus > 201703L
#			if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						return std::allocator<T>().allocate(n);
					}
#			endif
#		endif

					upstream_allocator up_alloc;
					return up_alloc.allocate(n);
				}


				typedef typename upstream_allocator::allow_deallocate_null allow_deallocate_null;

				KERBAL_CONSTEXPR20
				static void deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
				{

#		if __cplusplus > 201703L
#			if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						if (p != NULL) {
							std::allocator<T>().deallocate(p, n);
						}
						return;
					}
#			endif
#		endif

					upstream_allocator up_alloc;
					up_alloc.deallocate(p, n);
				}

				KERBAL_CONSTEXPR
				bool operator!=(const default_allocator & /*other*/) const KERBAL_NOEXCEPT
				{
					return false;
				}

				KERBAL_CONSTEXPR
				bool operator==(const default_allocator & /*other*/) const KERBAL_NOEXCEPT
				{
					return true;
				}

		};

		template <>
		class default_allocator<void>
		{
			public:
				typedef void						value_type;
				typedef value_type*					pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef kerbal::type_traits::true_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::true_type		is_always_equal;

			private:
				typedef kerbal::memory::over_aligned_allocator<value_type, kerbal::memory::malloc_allocator<void> > over_aligned_allocator;

			public:

#		if __cplusplus >= 201103L

				default_allocator() = default;

#		else

				default_allocator() KERBAL_NOEXCEPT
				{
				}

#		endif

				template <typename U>
				KERBAL_CONSTEXPR
				default_allocator(const default_allocator<U> &) KERBAL_NOEXCEPT
				{
				}


				typedef kerbal::memory::malloc_allocator<void>::MINIMUM_ALIGNMENT MINIMUM_ALIGNMENT;

				static pointer allocate(size_type n)
				{
					return kerbal::memory::malloc_allocator<void>::allocate(n);
				}

				static pointer allocate(size_type n, kerbal::memory::align_val_t align)
				{
					over_aligned_allocator over_aligned_alloc;
					return over_aligned_alloc.allocate(n, align);
				}


				typedef typename kerbal::memory::malloc_allocator<void>::allow_deallocate_null allow_deallocate_null;

				static void deallocate(pointer p) KERBAL_NOEXCEPT
				{
					kerbal::memory::malloc_allocator<void>::deallocate(p);
				}

				static void deallocate(pointer p, size_type /*n*/) KERBAL_NOEXCEPT
				{
					kerbal::memory::malloc_allocator<void>::deallocate(p);
				}

				static void deallocate(pointer p, size_type n, kerbal::memory::align_val_t align)
				{
					over_aligned_allocator over_aligned_alloc;
					over_aligned_alloc.deallocate(p, n, align);
				}

				KERBAL_CONSTEXPR
				bool operator!=(const default_allocator & /*other*/) const KERBAL_NOEXCEPT
				{
					return false;
				}

				KERBAL_CONSTEXPR
				bool operator==(const default_allocator & /*other*/) const KERBAL_NOEXCEPT
				{
					return true;
				}

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_ORI_DEFAULT_ALLOCATOR_HPP
