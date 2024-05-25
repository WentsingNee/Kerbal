/**
 * @file       optional_hash_template.part.hpp
 * @brief
 * @date       2018-11-7
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_HASH_TEMPLATE_PART_HPP
#define KERBAL_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_HASH_TEMPLATE_PART_HPP

#include <kerbal/optional/optional/optional.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/hash/hash.hpp>

#include <cstddef>


namespace kerbal
{

	namespace optional
	{

		template <typename OptionalType, typename ValueTypeHash, std::size_t NulloptHash>
		struct optional_hash_template
		{
				KERBAL_CONSTEXPR
				std::size_t operator()(const OptionalType & opt) const
				{
					return
						opt.has_value() ?
						ValueTypeHash()(opt.ignored_get()) :
						NulloptHash;
				}
		};

	} // namespace optional

} // namespace kerbal

#endif // KERBAL_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_HASH_TEMPLATE_PART_HPP
