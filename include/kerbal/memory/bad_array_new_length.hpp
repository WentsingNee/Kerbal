/**
 * @file       bad_array_new_length.hpp
 * @brief
 * @date       2023-07-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_BAD_ARRAY_NEW_LENGTH_HPP
#define KERBAL_MEMORY_BAD_ARRAY_NEW_LENGTH_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/bad_alloc.hpp>


namespace kerbal
{

	namespace memory
	{

		class bad_array_new_length :
				public kerbal::memory::bad_alloc
		{
			public:
				virtual const char * what() const KERBAL_NOEXCEPT
				{
					return "bad array new length";
				}
		};

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_BAD_ARRAY_NEW_LENGTH_HPP
