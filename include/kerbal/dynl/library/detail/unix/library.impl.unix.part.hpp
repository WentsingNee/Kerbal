/**
 * @file       library.impl.unix.part.hpp
 * @brief
 * @date       2024-09-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_DYNL_LIBRARY_DETAIL_UNIX_LIBRARY_IMPL_UNIX_PART_HPP
#define KERBAL_DYNL_LIBRARY_DETAIL_UNIX_LIBRARY_IMPL_UNIX_PART_HPP

#include <kerbal/dynl/library/library.decl.hpp>

#include <dlfcn.h>


namespace kerbal
{

	namespace dynl
	{

		inline
		library::
		library(char const * filename)
		{
			k_handle = dlopen(filename, RTLD_LAZY);
		}

		inline
		library::
		~library()
		{
			if (this->k_handle) {
				dlclose(this->k_handle);
			}
		}

		template <typename T>
		T
		library::
		find_symbol(char const * symbol) const
		{
			return reinterpret_cast<T>(
				dlsym(this->k_handle, symbol)
			);
		}

	} // namespace dynl

} // namespace kerbal

#endif // KERBAL_DYNL_LIBRARY_DETAIL_UNIX_LIBRARY_IMPL_UNIX_PART_HPP
