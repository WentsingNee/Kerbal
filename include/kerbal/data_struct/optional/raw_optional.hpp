/*
 * raw_optional.hpp
 *
 *  Created on: 2018年10月26日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_BASE_RAW_OPTIONAL_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_BASE_RAW_OPTIONAL_HPP_

#include <utility>

#include <kerbal/data_struct/raw_storage.hpp>
#include <kerbal/compatibility/compatibility_macro.hpp>


namespace kerbal
{
	namespace data_struct
	{

		template <typename Type>
		struct raw_optional: public kerbal::data_struct::raw_storage<Type>
		{
				raw_optional() KERBAL_NOEXCEPT
				{
				}

				explicit raw_optional(const Type & src)
				{
					this->construct(src);
				}

				template <typename Up>
				explicit raw_optional(const Up & src)
				{
					this->construct(src);
				}

# if __cplusplus >= 201103L

				explicit raw_optional(Type && src)
				{
					this->construct(std::forward<Type>(src));
				}

				template <typename Up>
				explicit raw_optional(Up && src)
				{
					this->construct(std::forward<Up>(src));
				}

# endif

			};

	} /* namespace data_struct */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_BASE_RAW_OPTIONAL_HPP_ */
