/**
 * @file       malloc_allocator.decl.hpp
 * @brief
 * @date       2023-01-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_MALLOC_ALLOCATOR_MALLOC_ALLOCATOR_DECL_HPP
#define KERBAL_MEMORY_ALLOCATOR_MALLOC_ALLOCATOR_MALLOC_ALLOCATOR_DECL_HPP

#include <kerbal/memory/allocator/malloc_allocator/malloc_allocator.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/nothrow_t.hpp>
#include <kerbal/memory/pointer_alignment.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

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

			public:
				KERBAL_CONSTEXPR
				static size_type minimum_alignment() KERBAL_NOEXCEPT
				{
					return kerbal::memory::DEFAULT_ALIGNMENT::value;
				}

				static pointer allocate(size_type n, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT;
				static pointer allocate(size_type n);

				typedef kerbal::type_traits::true_type allow_deallocate_null;

				static void deallocate(pointer p) KERBAL_NOEXCEPT;
				static void deallocate(pointer p, size_type /*n*/) KERBAL_NOEXCEPT;
				static void deallocate(pointer p, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT;
				static void deallocate(pointer p, size_type n, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT;

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

				KERBAL_CONSTEXPR
				static size_type minimum_alignment() KERBAL_NOEXCEPT
				{
					return kerbal::memory::DEFAULT_ALIGNMENT::value;
				}

				static pointer allocate(size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT;
				static pointer allocate(size_type n);

				typedef kerbal::type_traits::true_type allow_deallocate_null;

				static void deallocate(pointer p, size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT;
				static void deallocate(pointer p, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT;
				static void deallocate(pointer p, size_type n) KERBAL_NOEXCEPT;
				static void deallocate(pointer p) KERBAL_NOEXCEPT;

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


#endif // KERBAL_MEMORY_ALLOCATOR_MALLOC_ALLOCATOR_MALLOC_ALLOCATOR_DECL_HPP
