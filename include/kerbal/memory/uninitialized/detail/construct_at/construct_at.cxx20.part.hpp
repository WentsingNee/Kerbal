/**
 * @file       construct_at.cxx20.part.hpp
 * @brief
 * @date       2023-08-31
 * @remark     split from <kerbal/memory/uninitalized/construct.hpp>, 2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_CXX20_PART_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_CXX20_PART_HPP

#if __cplusplus <= 201703L
#	error This file requires compiler and library support for the ISO C++ 2020 standard.
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/forward.hpp>

#include <memory>


namespace kerbal
{

	namespace memory
	{

		template <typename T, typename ... Args>
		KERBAL_CONSTEXPR20
		T * construct_at(T * p, Args&& ... args)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(std::construct_at(p, kerbal::utility::forward<Args>(args)...))
				)
		{
			return std::construct_at(p, kerbal::utility::forward<Args>(args)...);
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_CXX20_PART_HPP
