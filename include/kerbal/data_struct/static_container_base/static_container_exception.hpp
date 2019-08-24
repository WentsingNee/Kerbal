/*
 * static_container_exception.hpp
 *
 *  Created on: 2019-4-20
 *      Author: peter
 */

#ifndef ERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_CONTAINER_EXCEPTION_HPP_
#define ERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_CONTAINER_EXCEPTION_HPP_

#include <stdexcept>
#include <kerbal/utility/throw_this_exception.hpp>

namespace kerbal
{
	namespace data_struct
	{

		class static_container_empty_exception:
				public kerbal::utility::throw_this_exception_helper<static_container_empty_exception>,
				public std::logic_error
		{
			public:
				static_container_empty_exception() :
						std::logic_error("the static container is empty")
				{
				}
		};

		class static_container_full_exception:
				public kerbal::utility::throw_this_exception_helper<static_container_full_exception>,
				public std::logic_error
		{
			public:
				static_container_full_exception() :
						std::logic_error("the static container is full")
				{
				}

				explicit static_container_full_exception(std::size_t max_capacity) :
						std::logic_error("the static container is full")
				{
				}
		};

	} // namespace data_struct

} // namespace kerbal

#endif /* ERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_CONTAINER_EXCEPTION_HPP_ */
