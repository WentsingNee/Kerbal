/*
 * bad_optional_access.hpp
 *
 *  Created on: 2018年10月28日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP_

#include <stdexcept>

namespace kerbal
{
	namespace data_struct
	{

		class bad_optional_access: public std::logic_error
		{
			public:
				bad_optional_access() :
						std::logic_error("Attempted to access the value of an uninitialized optional object.")
				{
				}
		};

	} /* namespace data_struct */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP_ */
