/**
 * @file       library.decl.unix.part.hpp
 * @brief
 * @date       2024-09-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_DYNL_LIBRARY_DETAIL_UNIX_LIBRARY_DECL_UNIX_PART_HPP
#define KERBAL_DYNL_LIBRARY_DETAIL_UNIX_LIBRARY_DECL_UNIX_PART_HPP

#include <kerbal/dynl/library/library.fwd.hpp>

#include <kerbal/utility/noncopyable.hpp>


namespace kerbal
{

	namespace dynl
	{

		class library :
			private kerbal::utility::noncopyable,
			private kerbal::utility::noncopyassignable
		{
			private:
				void * k_handle;

			public:
				library(char const * filename);

				~library();

				template <typename T>
				T find_symbol(char const * symbol) const;
		};

	} // namespace dynl

} // namespace kerbal

#endif // KERBAL_DYNL_LIBRARY_DETAIL_UNIX_LIBRARY_DECL_UNIX_PART_HPP
