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

#include <kerbal/optional/fwd/optional.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/hash/hash.hpp>

#include <cstddef>


namespace kerbal
{

	namespace optional
	{

		template <typename OptionalType, typename ValueTypeHash, std::size_t NulloptHash>
		struct optional_hash
		{
				KERBAL_CONSTEXPR
				std::size_t operator()(const OptionalType & opt) const
				{
					return opt.has_value() ?
						   ValueTypeHash()(opt.ignored_get()) :
						   NulloptHash;
				}
		};

	} // namespace optional

	namespace hash
	{

		template <typename T>
		struct hash<kerbal::optional::optional<T> > :
				public kerbal::optional::optional_hash<
							kerbal::optional::optional<T>,
							kerbal::hash::hash<T>,
							static_cast<size_t>(-3333)
						>
		{
		};

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_OPTIONAL_OPTIONAL_HASH_HPP
