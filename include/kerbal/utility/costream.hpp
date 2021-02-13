/**
 * @file		costream.hpp
 * @brief
 * @date		2018年2月27日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_UTILITY_COSTREAM_HPP_
#define INCLUDE_KERBAL_UTILITY_COSTREAM_HPP_

#include <iostream>

#ifdef _WIN32
#	define NOMINMAX
#	include <windows.h>
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/config/compiler_id.hpp>

namespace kerbal
{
	namespace utility
	{
		namespace costream
		{
			class Color_t
			{
				public:
					const int ID;

					KERBAL_CONSTEXPR Color_t(int ID = -1) :
							ID(ID)
					{
					}

					KERBAL_CONSTEXPR bool operator==(const Color_t & with) const
					{
						return this->ID == with.ID;
					}

					KERBAL_CONSTEXPR bool operator!=(const Color_t & with) const
					{
						return this->ID != with.ID;
					}

			}
#		if __cplusplus >= 201103L && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC
			constexpr
#		else
			const
#		endif

			INIT(-1),
#ifdef _WIN32
			BLACK(0), BLUE(1), GREEN(2), LAKE_BLUE(3), RED(4), PURPLE(5), YELLOW(6), WHITE(7),
			GREY(8), LIGHT_BLUE(9), LIGHT_GREEN(10), LIGHT_LIGHT_GREEN(11),
			LIGHT_RED(12), LIGHT_PURPLE(13), LIGHT_YELLOW(14), BRIGHT_WHITE(15);
#endif

#ifdef __linux
			BLACK(0),RED(1),GREEN(2),YELLOW(3),BLUE(4),PURPLE(5),LIGHT_BLUE(104),WHITE(7),

			LIGHT_RED(101),LIGHT_GREEN(102),LIGHT_YELLOW(103),LAKE_BLUE(6),LIGHT_PURPLE(105),
			GREY(107),
			LIGHT_LIGHT_GREEN(106),
			BRIGHT_WHITE(107);
#endif

			template <std::ostream& bind_ostream>
			class costream
			{
				protected:
#ifdef _WIN32
					struct Init_bakup
					{
							const HANDLE handle;
							const WORD init_color;
							const WORD init_background, init_foreground;

							WORD get_init_color()
							{
								CONSOLE_SCREEN_BUFFER_INFO csbi;
								GetConsoleScreenBufferInfo(handle, &csbi);
								return csbi.wAttributes;
							}

							Init_bakup(DWORD handle) :
									handle(::GetStdHandle(handle)), init_color(get_init_color()),
									init_background(init_color >> 4),
									init_foreground(init_color % 16)
							{
							}

							~Init_bakup()
							{
								SetConsoleTextAttribute(handle, init_color);
							}

					}static const bakup;
#endif //WIN32

					const Color_t foreground, background;

				public:
					KERBAL_CONSTEXPR costream(Color_t foreground = INIT, Color_t background = INIT) :
							foreground(foreground), background(background)
					{
					}

					template <class Type>
					const costream& operator<<(const Type & src) const
					{
#ifdef _WIN32
						HANDLE handle = bakup.handle;
						WORD colorOld = bakup.init_color;
						WORD color = (
								this->background == INIT ?
										bakup.init_background : this->background.ID) * 16
								+ (this->foreground == INIT ?
										bakup.init_foreground : this->foreground.ID);
						SetConsoleTextAttribute(handle, color);
						bind_ostream << src;
						SetConsoleTextAttribute(handle, colorOld);

#endif //WIN32

#ifdef __linux
						if(this->foreground != INIT) {
							if(this->foreground.ID > 100) {
								bind_ostream << "\033[1m";
								bind_ostream << "\033[" << this->foreground.ID - 70 << "m";
							} else {
								bind_ostream << "\033[" << 30 + this->foreground.ID << "m";
							}

						}

						if(this->background != INIT) {

							if(this->background.ID >= 100) {
								bind_ostream << "\033[" << this->background.ID - 60 << "m";
							} else {
								bind_ostream << "\033[" << 40 + this->background.ID << "m";
							}
						}

						bind_ostream << src <<"\033[0m";
#endif

						return *this;
					}

					const costream& operator<<(std::ostream& (*__pf)(std::ostream&)) const
					{
						__pf(bind_ostream);
						return *this;
					}
			};

#ifdef _WIN32
			template <std::ostream& bind_ostream>
			const typename costream<bind_ostream>::Init_bakup costream<bind_ostream>::bakup(
			STD_OUTPUT_HANDLE);

			template <>
			const typename costream<std::cerr>::Init_bakup costream<std::cerr>::bakup(
			STD_ERROR_HANDLE);
#endif //WIN32

//			costream<std::cerr> ccerr(LIGHT_RED, INIT);

			const Color_t color_test_arr[] = {
				BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, LIGHT_BLUE, WHITE, LIGHT_RED, LIGHT_GREEN,
				LIGHT_YELLOW, LAKE_BLUE, LIGHT_PURPLE, GREY, LIGHT_LIGHT_GREEN, BRIGHT_WHITE };

		}/* namespace costream */

	}/* namespace utility */

}/* namespace kerbal */

#endif /* INCLUDE_KERBAL_UTILITY_COSTREAM_HPP_ */
