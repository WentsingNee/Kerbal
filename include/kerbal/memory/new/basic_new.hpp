/**
 * @file       basic_new.hpp
 * @brief
 * @date       2021-02-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_NEW_BASIC_NEW_HPP
#define KERBAL_MEMORY_NEW_BASIC_NEW_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/bad_alloc.hpp>

#include <cstddef>
#include <cstdlib>


namespace kerbal
{

	namespace memory
	{

		struct basic_t
		{
		};

	} // namespace memory

} // namespace kerbal


inline
void * operator new(std::size_t size, kerbal::memory::basic_t)
{
	void * p = std::malloc(size);
	if (p == NULL) {
		kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
	}
	return p;
}

inline
void operator delete(void * p, std::size_t /*size*/, kerbal::memory::basic_t) KERBAL_NOEXCEPT
{
	std::free(p);
}

inline
void * operator new[](std::size_t size, kerbal::memory::basic_t basic_new_tag)
{
	return ::operator new(size, basic_new_tag);
}

inline
void operator delete[](void * p, std::size_t size, kerbal::memory::basic_t basic_new_tag) KERBAL_NOEXCEPT
{
	::operator delete(p, size, basic_new_tag);
}


#endif // KERBAL_MEMORY_NEW_BASIC_NEW_HPP
