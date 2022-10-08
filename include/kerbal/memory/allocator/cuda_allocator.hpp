/**
 * @file       cuda_allocator.hpp
 * @brief
 * @date       2023-01-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_CUDA_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_CUDA_ALLOCATOR_HPP

#include <kerbal/config/cuda.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>
#include <cstdio>


namespace kerbal
{

	namespace memory
	{

		template <typename T>
		class cuda_allocator
		{
			public:
				typedef T				value_type;
				typedef std::size_t		size_type;

				cuda_allocator() = default;

				template <typename U>
				KERBAL_CONSTEXPR
				explicit cuda_allocator(const cuda_allocator<U> &) KERBAL_NOEXCEPT
				{
				}

				static T * allocate(size_type n)
				{
					T * p = NULL;
					KERBAL_CUDA_CHECK((cudaMalloc(reinterpret_cast<void **>(&p), n * sizeof(T))));
					printf("allocate %zu x %zu -> %p\n", n, sizeof(T), p);
					return p;
				}

				static void deallocate(T * p, size_type n) KERBAL_NOEXCEPT
				{
					printf("deallocate %zu x %zu <- %p\n", n, sizeof(T), p);
					KERBAL_CUDA_CHECK(cudaFree(p));
				}

				KERBAL_CONSTEXPR
				static void construct(T * /*p*/) KERBAL_NOEXCEPT
				{
				}

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_CUDA_ALLOCATOR_HPP
