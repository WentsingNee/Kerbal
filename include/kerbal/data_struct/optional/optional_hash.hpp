/*
 * optional_hash.hpp
 *
 *  Created on: 2018年11月7日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_HASH_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_HASH_HPP_

#include <cstddef>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/data_struct/optional/optional_type_traits.hpp>
#include <kerbal/data_struct/hash.hpp>

namespace kerbal
{

	namespace data_struct
	{

		template <typename OptionalType, typename ValueTypeBindHash, size_t NulloptHash>
		struct optional_hash
		{
				size_t operator()(const OptionalType & val) const
				{
					if (val.has_value()) {
						return ValueTypeBindHash()(val.ignored_get());
					} else {
						return NulloptHash;
					}
				}
		};

		template <typename>
		struct optional;

		template <typename ValueType>
		struct hash<optional<ValueType> > :
				public optional_hash<optional<ValueType>, hash<ValueType>, static_cast<size_t>(-3333)>
		{
		};

	} /* namespace data_struct */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_HASH_HPP_ */
