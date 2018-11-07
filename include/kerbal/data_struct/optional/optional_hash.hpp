/*
 * optional_hash.hpp
 *
 *  Created on: 2018年11月7日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_HASH_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_HASH_HPP_

namespace kerbal
{

	namespace data_struct
	{

		template <typename>
		struct optional;

		template <typename Type, typename BindHash = std::hash<Type>, size_t NulloptHash = static_cast<size_t>(-3333)>
		struct optional_hash
		{
				size_t operator()(const optional<Type> & val) const
				{
					if (val.has_value()) {
						static const BindHash hs;
						return hs(val.ignored_get());
					} else {
						return NulloptHash;
					}
				}
		};

		template <typename Type, typename BindHash = std::hash<typename optional_traits<Type>::value_type>, size_t NulloptHash = static_cast<size_t>(-3333)>
		struct hash;

		template <typename Type, typename BindHash, size_t NulloptHash>
		struct hash<optional<Type>, BindHash, NulloptHash> : public optional_hash<Type, BindHash, NulloptHash>
		{
		};

	} /* namespace data_struct */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_HASH_HPP_ */
