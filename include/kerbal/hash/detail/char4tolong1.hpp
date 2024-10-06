/**
 * @file       char4tolong1.hpp
 * @brief
 * @date       2024-10-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_DETAIL_CHAR4TOLONG1_HPP
#define KERBAL_HASH_DETAIL_CHAR4TOLONG1_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>
#include <cstdlib>


namespace kerbal
{

	namespace hash
	{

		namespace detail
		{

			template <int byte_order>
			KERBAL_CONSTEXPR
			kerbal::compatibility::uint32_t
			char4tolong1(const kerbal::compatibility::uint8_t c[4]) KERBAL_NOEXCEPT;

			template <>
			KERBAL_CONSTEXPR
			inline
			kerbal::compatibility::uint32_t
			char4tolong1<LITTLE_ENDIAN>(const kerbal::compatibility::uint8_t c[4]) KERBAL_NOEXCEPT
			{
				return (c[0] << 24u) | (c[1] << 16u) | (c[2] << 8u) | c[3];
			}

			template <>
			KERBAL_CONSTEXPR
			inline
			kerbal::compatibility::uint32_t
			char4tolong1<BIG_ENDIAN>(const kerbal::compatibility::uint8_t c[4]) KERBAL_NOEXCEPT
			{
				return (c[3] << 24u) | (c[2] << 16u) | (c[1] << 8u) | c[0];
			}

		} // namespace detail

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_DETAIL_CHAR4TOLONG1_HPP
