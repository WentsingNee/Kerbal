/**
 * @file       palette.hpp
 * @brief
 * @date       2023-9-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COSTREAM_PALETTE_HPP
#define KERBAL_COSTREAM_PALETTE_HPP

#include <kerbal/config/system.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace costream
	{

		class palette
		{
			public:
				int k_color_id;

				KERBAL_CONSTEXPR
				palette(int color_id = -1) KERBAL_NOEXCEPT :
						k_color_id(color_id)
				{
				}

				KERBAL_CONSTEXPR
				bool operator==(const palette & with) const KERBAL_NOEXCEPT
				{
					return this->k_color_id == with.k_color_id;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const palette & with) const KERBAL_NOEXCEPT
				{
					return this->k_color_id != with.k_color_id;
				}

		};

		KERBAL_CONSTEXPR
		const palette INIT(-1);

#if KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS
		KERBAL_CONSTEXPR
		const palette BLACK(0), BLUE(1), GREEN(2), LAKE_BLUE(3), RED(4), PURPLE(5), YELLOW(6), WHITE(7),
					  GREY(8), LIGHT_BLUE(9), LIGHT_GREEN(10), LIGHT_LIGHT_GREEN(11),
					  LIGHT_RED(12), LIGHT_PURPLE(13), LIGHT_YELLOW(14), BRIGHT_WHITE(15);
#elif KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX
		KERBAL_CONSTEXPR
		const palette BLACK(0), RED(1), GREEN(2), YELLOW(3), BLUE(4), PURPLE(5), LIGHT_BLUE(104), WHITE(7),
					  LIGHT_RED(101), LIGHT_GREEN(102), LIGHT_YELLOW(103), LAKE_BLUE(6), LIGHT_PURPLE(105),
					  GREY(107),
					  LIGHT_LIGHT_GREEN(106),
					  BRIGHT_WHITE(107);
#endif

	} // namespace costream

} // namespace kerbal

#endif // KERBAL_COSTREAM_PALETTE_HPP
