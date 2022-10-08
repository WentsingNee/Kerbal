/**
 * @file       cuda.hpp
 * @brief
 * @date       2022-09-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_CUDA_HPP
#define KERBAL_CONFIG_CUDA_HPP

#if KERBAL_HAS_CUDA_SUPPORT

#	define KERBAL_CUDA_DEVICE		__device__
#	define KERBAL_CUDA_HOST			__host__

#else

#	define KERBAL_CUDA_DEVICE
#	define KERBAL_CUDA_HOST

#endif


#ifndef NDEBUG

#include <cstdio>

#	define KERBAL_CUDA_CHECK(call) do { \
		const cudaError_t error = call; \
		if (error) { \
			printf("error: %s:%d, ", __FILE__, __LINE__); \
			printf("code:%d, reason: %s\n", error, cudaGetErrorString(error)); \
		} \
	} while(false)

#else

#	define KERBAL_CUDA_CHECK(call) do { \
		call; \
	} while(false)

#endif

#endif // KERBAL_CONFIG_CUDA_HPP
