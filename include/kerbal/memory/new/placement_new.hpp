/**
 * @file       placement_new.hpp
 * @brief
 * @date       2021-07-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_NEW_PLACEMENT_NEW_HPP
#define KERBAL_MEMORY_NEW_PLACEMENT_NEW_HPP

#include <kerbal/config/compiler_id.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		struct placement_t
		{
		};

	} // namespace memory

} // namespace kerbal



#if (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU) || (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG)
[[gnu::always_inline]]
#endif
inline
KERBAL_CONSTEXPR
void *
operator new(std::size_t /*size*/, kerbal::memory::placement_t, void * p) KERBAL_NOEXCEPT
{
	return p;
}


#if (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU) || (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG)
[[gnu::always_inline]]
#endif
inline
KERBAL_CONSTEXPR14
void operator delete(void*, kerbal::memory::placement_t, void*) KERBAL_NOEXCEPT
{
}


#endif // KERBAL_MEMORY_NEW_PLACEMENT_NEW_HPP
