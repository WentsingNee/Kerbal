/**
 * @file       colors.hpp
 * @brief
 * @date       2020-04-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COSTREAM_COLORS_HPP
#define KERBAL_COSTREAM_COLORS_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{

	namespace costream
	{

		class color
		{
			public:
				const int ID;

				KERBAL_CONSTEXPR
				explicit color(int ID = -1) KERBAL_NOEXCEPT :
						ID(ID)
				{
				}

				KERBAL_CONSTEXPR
				bool operator==(const color & with) const KERBAL_NOEXCEPT
				{
					return this->ID == with.ID;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const color & with) const KERBAL_NOEXCEPT
				{
					return this->ID != with.ID;
				}

		}

KERBAL_CONSTEXPR const

#ifdef _WIN32
			INIT(-1),
			BLACK(0), BLUE(1), GREEN(2), LAKE_BLUE(3), RED(4), PURPLE(5), YELLOW(6), WHITE(7),
			GREY(8), LIGHT_BLUE(9), LIGHT_GREEN(10), LIGHT_LIGHT_GREEN(11),
			LIGHT_RED(12), LIGHT_PURPLE(13), LIGHT_YELLOW(14), BRIGHT_WHITE(15);
#endif

#ifdef __linux
			INIT(-1),
			BLACK(0),RED(1),GREEN(2),YELLOW(3),BLUE(4),PURPLE(5),LIGHT_BLUE(104),WHITE(7),

			LIGHT_RED(101),LIGHT_GREEN(102),LIGHT_YELLOW(103),LAKE_BLUE(6),LIGHT_PURPLE(105),
			GREY(107),
			LIGHT_LIGHT_GREEN(106),
			BRIGHT_WHITE(107);
#endif


	} // namespace costream

} // namespace kerbal

#endif // KERBAL_COSTREAM_COLORS_HPP
