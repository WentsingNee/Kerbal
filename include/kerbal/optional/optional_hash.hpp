/**
 * @file       optional_hash.hpp
 * @brief
 * @date       2018-11-7
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_OPTIONAL_HASH_HPP
#define KERBAL_OPTIONAL_OPTIONAL_HASH_HPP

#include <kerbal/hash/hash.hpp>

#include <cstddef>

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
		class optional;

	} // namespace optional

	namespace hash
	{

		template <typename ValueType>
		struct hash<kerbal::optional::optional<ValueType> > :
				public kerbal::optional::optional_hash<
							kerbal::optional::optional<ValueType>,
							kerbal::hash::hash<ValueType>,
							static_cast<size_t>(-3333)
						>
		{
		};

	} // namespace hash

} // namespace kerbal


#endif // KERBAL_OPTIONAL_OPTIONAL_HASH_HPP
