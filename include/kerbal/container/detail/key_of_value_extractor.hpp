/**
 * @file       key_of_value_extractor.hpp
 * @brief
 * @date       2020-10-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_KEY_OF_VALUE_EXTRACTOR_HPP
#define KERBAL_CONTAINER_DETAIL_KEY_OF_VALUE_EXTRACTOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Key>
			struct identity_extractor
			{
				typedef Key value_type;
				typedef Key key_type;

				KERBAL_CONSTEXPR14
				key_type& operator()(value_type & key) const KERBAL_NOEXCEPT
				{
					return key;
				}

				KERBAL_CONSTEXPR14
				const key_type& operator()(const value_type & key) const KERBAL_NOEXCEPT
				{
					return key;
				}
			};

			template <typename KVPair, typename Key>
			struct default_map_key_extractor
			{
					typedef KVPair value_type;
					typedef Key key_type;

					KERBAL_CONSTEXPR14
					key_type& operator()(value_type & p) const KERBAL_NOEXCEPT
					{
						return p.first;
					}

					KERBAL_CONSTEXPR14
					const key_type& operator()(const value_type & p) const KERBAL_NOEXCEPT
					{
						return p.first;
					}
			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_KEY_OF_VALUE_EXTRACTOR_HPP
