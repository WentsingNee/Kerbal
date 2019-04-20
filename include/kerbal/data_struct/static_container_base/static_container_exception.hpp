/*
 * static_container_exception.hpp
 *
 *  Created on: 2019年4月20日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_CONTAINER_EXCEPTION_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_CONTAINER_EXCEPTION_HPP_

#include <stdexcept>

namespace kerbal
{
	/**
	 * @brief data structure
	 */
	namespace data_struct
	{

		class static_container_empty_exception : public std::logic_error
		{
			public:
				static_container_empty_exception() :
						std::logic_error("")
				{
				}
		};

		class static_container_full_exception: public std::logic_error
		{
			public:
				static_container_full_exception() :
						std::logic_error("")
				{
				}

				explicit static_container_full_exception(std::size_t max_capacity) :
						std::logic_error("")
				{
				}
		};
	}
}
#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_CONTAINER_EXCEPTION_HPP_ */
