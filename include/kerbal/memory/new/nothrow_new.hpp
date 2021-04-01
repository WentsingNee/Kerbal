/**
 * @file       nothrow_new.hpp
 * @brief
 * @date       2021-02-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_NEW_NOTHROW_NEW_HPP
#define KERBAL_MEMORY_NEW_NOTHROW_NEW_HPP

#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>
#include <cstdlib>


namespace kerbal
{

	namespace memory
	{

		struct nothrow_t
		{
		};

	} // namespace memory

} // namespace kerbal


inline
void * operator new(std::size_t size, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
{
	void * p = std::malloc(size);
	return p;
}

inline
void operator delete(void * p, std::size_t /*size*/, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
{
	std::free(p);
}

inline
void * operator new[](std::size_t size, kerbal::memory::nothrow_t nothrow_new_tag) KERBAL_NOEXCEPT
{
	return ::operator new(size, nothrow_new_tag);
}

inline
void operator delete[](void * p, std::size_t size, kerbal::memory::nothrow_t nothrow_new_tag) KERBAL_NOEXCEPT
{
	::operator delete(p, size, nothrow_new_tag);
}


#endif // KERBAL_MEMORY_NEW_NOTHROW_NEW_HPP
