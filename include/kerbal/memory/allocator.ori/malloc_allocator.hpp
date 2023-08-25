/**
 * @file       malloc_allocator.hpp
 * @brief
 * @date       2023-01-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_ORI_MALLOC_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_ORI_MALLOC_ALLOCATOR_HPP

#include <kerbal/memory/allocator/malloc_allocator/malloc_allocator.fwd.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/bad_alloc.hpp>
#include <kerbal/memory/bad_array_new_length.hpp>
#include <kerbal/memory/pointer_alignment.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <cstddef>
#include <cstdlib>


namespace kerbal
{

	namespace memory
	{

		struct nothrow_t
		{
		};



		template <>
		class malloc_allocator<void>
		{
			public:
				typedef void						value_type;
				typedef value_type *				pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef kerbal::type_traits::true_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::true_type		is_always_equal;

			public:

#		if __cplusplus >= 201103L

				malloc_allocator() = default;

#		else

				malloc_allocator() KERBAL_NOEXCEPT
				{
				}

#		endif

				template <typename U>
				KERBAL_CONSTEXPR
				malloc_allocator(const malloc_allocator<U> &) KERBAL_NOEXCEPT
				{
				}

				typedef kerbal::memory::DEFAULT_ALIGNMENT	MINIMUM_ALIGNMENT;

				static pointer allocate(size_type n, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
				{
					void * p = std::malloc(n);
					return p;
				}

				static pointer allocate(size_type n)
				{
					void * p = std::malloc(n);
					if (p == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
					return p;
				}

				typedef kerbal::type_traits::true_type allow_deallocate_null;

				static void deallocate(pointer p) KERBAL_NOEXCEPT
				{
					std::free(p);
				}

				static void deallocate(pointer p, size_type /*n*/) KERBAL_NOEXCEPT
				{
					deallocate(p);
				}

				static void deallocate(pointer p, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
				{
					deallocate(p);
				}

				static void deallocate(pointer p, size_type n, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
				{
					deallocate(p, n);
				}

				KERBAL_CONSTEXPR
				bool operator!=(const malloc_allocator & /*other*/) const KERBAL_NOEXCEPT
				{
					return false;
				}

				KERBAL_CONSTEXPR
				bool operator==(const malloc_allocator & /*other*/) const KERBAL_NOEXCEPT
				{
					return true;
				}

		};


		template <typename T>
		class malloc_allocator
		{
			public:
				typedef T							value_type;
				typedef value_type *				pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef kerbal::type_traits::true_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::true_type		is_always_equal;

			public:

#		if __cplusplus < 201103L

				malloc_allocator() KERBAL_NOEXCEPT
				{
				}

#		else

				malloc_allocator() = default;

#		endif

				template <typename U>
				KERBAL_CONSTEXPR
				malloc_allocator(const malloc_allocator<U> &) KERBAL_NOEXCEPT
				{
				}

			public:
				typedef kerbal::type_traits::integral_constant<
						size_type,
						kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(value_type)
				> MAX_SIZE;

				typedef kerbal::memory::DEFAULT_ALIGNMENT	MINIMUM_ALIGNMENT;

				static pointer allocate(size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
				{
					if (n > MAX_SIZE::value) {
						return NULL;
					}
					void * p = kerbal::memory::malloc_allocator<void>::allocate(n * sizeof(value_type), nothrow);
					return static_cast<pointer>(p);
				}

				static pointer allocate(size_type n)
				{
					if (n > MAX_SIZE::value) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_array_new_length>::throw_this_exception();
					}
					void * p = kerbal::memory::malloc_allocator<void>::allocate(n * sizeof(value_type));
					return static_cast<pointer>(p);
				}

				typedef kerbal::type_traits::true_type allow_deallocate_null;

				static void deallocate(pointer p, size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
				{
					kerbal::memory::malloc_allocator<void>::deallocate(p, n, nothrow);
				}

				static void deallocate(pointer p, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
				{
					kerbal::memory::malloc_allocator<void>::deallocate(p, nothrow);
				}

				static void deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
				{
					kerbal::memory::malloc_allocator<void>::deallocate(p, n);
				}

				static void deallocate(pointer p) KERBAL_NOEXCEPT
				{
					kerbal::memory::malloc_allocator<void>::deallocate(p);
				}

				KERBAL_CONSTEXPR
				bool operator!=(const malloc_allocator & /*other*/) const KERBAL_NOEXCEPT
				{
					return false;
				}

				KERBAL_CONSTEXPR
				bool operator==(const malloc_allocator & /*other*/) const KERBAL_NOEXCEPT
				{
					return true;
				}

		};

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_ALLOCATOR_ORI_MALLOC_ALLOCATOR_HPP
