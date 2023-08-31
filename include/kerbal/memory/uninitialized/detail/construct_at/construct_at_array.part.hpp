/**
 * @file       construct_at_array.part.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_ARRAY_PART_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_ARRAY_PART_HPP

#include <kerbal/memory/uninitialized/uninitialized_value_construct/uninitialized_value_construct.fwd.hpp>
#include <kerbal/memory/uninitialized/uninitialized_copy/uninitialized_copy.fwd.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/memory/uninitialized/uninitialized_move/uninitialized_move.fwd.hpp>
#endif

#include <kerbal/compatibility/constexpr.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		T (* construct_at(T (*p) [N])) [N]
		{
			kerbal::memory::uninitialized_value_construct(*p, *p + N);
			return p;
		}

		template <typename T, typename Up, std::size_t N>
		KERBAL_CONSTEXPR14
		T (* construct_at(T (*p) [N], Up (&val) [N])) [N]
		{
			kerbal::memory::uninitialized_copy(val + 0, val + N, *p + 0);
			return p;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Up, std::size_t N>
		KERBAL_CONSTEXPR14
		T (* construct_at(T (*p) [N], Up (&&val) [N])) [N]
		{
			kerbal::memory::uninitialized_move(val + 0, val + N, *p + 0);
			return p;
		}

#	endif

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_ARRAY_PART_HPP
