/**
 * @file       std_pmr_allocator.fwd.hpp
 * @brief
 * @date       2023-07-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_STD_PMR_ALLOCATOR_FWD_HPP
#define KERBAL_MEMORY_ALLOCATOR_STD_PMR_ALLOCATOR_FWD_HPP

#include <kerbal/compatibility/namespace_std_scope.hpp>


KERBAL_NAMESPACE_STD_BEGIN

#if __cplusplus >= 201703L

namespace pmr
{

	template <typename T>
	class polymorphic_allocator;

} // namespace pmr

#endif

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_MEMORY_ALLOCATOR_STD_PMR_ALLOCATOR_FWD_HPP
