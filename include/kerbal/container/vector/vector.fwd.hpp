/**
 * @file       vector.fwd.hpp
 * @brief
 * @date       2020-08-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_VECTOR_VECTOR_FWD_HPP
#define KERBAL_CONTAINER_VECTOR_VECTOR_FWD_HPP


#include <kerbal/config/modules/modules.hpp>

#if KERBAL_ENABLE_MODULES
module;
#endif


#include <kerbal/config/modules/include_header_begin.part.hpp>


#include <kerbal/container/detail/vector_base/vector_base.fwd.hpp>

#include <memory>

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <memory_resource>
#	endif
#endif


#include <kerbal/config/modules/include_header_end.part.hpp>


#if KERBAL_ENABLE_MODULES
export module kerbal.container.vector.fwd;
#endif


namespace kerbal
{

	namespace container
	{

		KERBAL_MODULE_EXPORT
		template <typename T, typename Allocator = std::allocator<T> >
		class vector;


#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)

		namespace pmr
		{

			KERBAL_MODULE_EXPORT
			template <typename T>
			using vector = kerbal::container::vector<T, std::pmr::polymorphic_allocator<T> >;

		}

#	endif
#endif


	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_VECTOR_VECTOR_FWD_HPP
