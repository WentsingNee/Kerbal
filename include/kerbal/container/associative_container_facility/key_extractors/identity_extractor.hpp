/**
 * @file       identity_extractor.hpp
 * @brief
 * @date       2020-10-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_IDENTITY_EXTRACTOR_HPP
#define KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_IDENTITY_EXTRACTOR_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace container
	{

		KERBAL_MODULE_EXPORT
		template <typename Key>
		struct identity_extractor;

		KERBAL_MODULE_EXPORT
		template <typename Key>
		struct identity_extractor
		{
			typedef Key value_type;
			typedef Key key_type;

			KERBAL_CONSTEXPR
			key_type &
			operator()(value_type & key) const KERBAL_NOEXCEPT
			{
				return key;
			}

			KERBAL_CONSTEXPR
			const key_type &
			operator()(const value_type & key) const KERBAL_NOEXCEPT
			{
				return key;
			}
		};

		KERBAL_MODULE_EXPORT
		template <typename Key>
		struct identity_extractor<const Key>
		{
			typedef const Key value_type;
			typedef Key key_type;

			KERBAL_CONSTEXPR
			const key_type &
			operator()(value_type & key) const KERBAL_NOEXCEPT
			{
				return key;
			}
		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_IDENTITY_EXTRACTOR_HPP
