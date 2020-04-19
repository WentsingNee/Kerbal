/**
 * @file       optional_hash.hpp
 * @brief
 * @date       2018-11-7
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_OPTIONAL_HASH_HPP_
#define KERBAL_OPTIONAL_OPTIONAL_HASH_HPP_

#include <cstddef>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/optional/optional_type_traits.hpp>
#include <kerbal/hash/hash.hpp>

namespace kerbal
{

	namespace optional
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

	} /* namespace optional */

} /* namespace kerbal */


#endif /* KERBAL_OPTIONAL_OPTIONAL_HASH_HPP_ */
