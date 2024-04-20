/**
 * @file       bad_cuda_alloc.hpp
 * @brief
 * @date       2024-04-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_BAD_CUDA_ALLOC_HPP
#define KERBAL_MEMORY_BAD_CUDA_ALLOC_HPP

#include <kerbal/compatibility/noexcept.hpp>

#include <exception>


namespace kerbal
{

	namespace memory
	{

		class bad_cuda_alloc :
			public std::exception
		{
			public:
				virtual
				const char * what() const KERBAL_NOEXCEPT
				{
					return "bad cuda alloc";
				}
		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_BAD_CUDA_ALLOC_HPP
