/**
 * @file       endian.hpp
 * @brief
 * @date       2024-10-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ENDIAN_HPP
#define KERBAL_ENDIAN_HPP

#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace config
	{

		enum endian
		{
				ENDIAN_LITTLE = 4321,
				ENDIAN_BIG = 1234,
		};

		namespace detail
		{

			inline
			endian basic_dynamic_endian() KERBAL_NOEXCEPT
			{
				return ENDIAN_LITTLE;
			}

		} // namespace detail

	} // namespace config

} // namespace kerbal

#endif // KERBAL_ENDIAN_HPP
