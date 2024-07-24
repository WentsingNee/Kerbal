/**
 * @file       costream.hpp
 * @brief
 * @date       2018-2-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_COSTREAM_HPP
#define KERBAL_UTILITY_COSTREAM_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/system.hpp>

#if KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#	include <windows.h>
#endif

#include <kerbal/compatibility/constexpr.hpp>

#include <iostream>


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

					KERBAL_CONSTEXPR
					Color_t(int ID = -1) :
						ID(ID)
					{
					}

					KERBAL_CONSTEXPR
					bool operator==(const Color_t & with) const
					{
						return this->ID == with.ID;
					}

					KERBAL_CONSTEXPR
					bool operator!=(const Color_t & with) const
					{
						return this->ID != with.ID;
					}

			}
#		if __cplusplus >= 201103L && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC
			constexpr
#		else
			const
#		endif

			INIT(-1)
#if   KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS
			, BLACK(0), BLUE(1), GREEN(2), LAKE_BLUE(3), RED(4), PURPLE(5), YELLOW(6), WHITE(7),
			  GREY(8), LIGHT_BLUE(9), LIGHT_GREEN(10), LIGHT_LIGHT_GREEN(11),
			  LIGHT_RED(12), LIGHT_PURPLE(13), LIGHT_YELLOW(14), BRIGHT_WHITE(15);
#elif KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX
			, BLACK(0),RED(1),GREEN(2),YELLOW(3),BLUE(4),PURPLE(5),LIGHT_BLUE(104),WHITE(7),

			  LIGHT_RED(101),LIGHT_GREEN(102),LIGHT_YELLOW(103),LAKE_BLUE(6),LIGHT_PURPLE(105),
			  GREY(107),
			  LIGHT_LIGHT_GREEN(106),
			  BRIGHT_WHITE(107);
#else
			;
#endif

			template <std::ostream & bind_ostream>
			class costream
			{
				protected:
#if KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS
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
#endif // KERBAL_SYSTEM_WINDOWS

					const Color_t foreground, background;

				public:
					KERBAL_CONSTEXPR costream(Color_t foreground = INIT, Color_t background = INIT) :
						foreground(foreground), background(background)
					{
					}

					template <class Type>
					const costream & operator<<(const Type & src) const
					{
#if KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS
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

#endif // KERBAL_SYSTEM_WINDOWS

#if KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX
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

					const costream & operator<<(std::ostream & (* pf)(std::ostream &)) const
					{
						pf(bind_ostream);
						return *this;
					}
			};

#if KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS
			template <std::ostream & bind_ostream>
			const typename costream<bind_ostream>::Init_bakup costream<bind_ostream>::bakup(
			STD_OUTPUT_HANDLE);

			template <>
			const typename costream<std::cerr>::Init_bakup costream<std::cerr>::bakup(
			STD_ERROR_HANDLE);
#endif // KERBAL_SYSTEM_WINDOWS

//			costream<std::cerr> ccerr(LIGHT_RED, INIT);ßß

		} // namespace costream

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_COSTREAM_HPP
