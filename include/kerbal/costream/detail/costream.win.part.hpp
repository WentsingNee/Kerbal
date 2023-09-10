/**
 * @file       costream.win.part.hpp
 * @brief
 * @date       2023-9-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COSTREAM_DETAIL_COSTREAM_WIN_PART_HPP
#define KERBAL_COSTREAM_DETAIL_COSTREAM_WIN_PART_HPP

#ifndef NOMINMAX
#	define NOMINMAX
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/linked_stack.hpp>
#include <kerbal/costream/palette.hpp>

#include <iostream>

#include <windows.h>


namespace kerbal
{

	namespace costream
	{

		namespace detail
		{

			struct console_color_config
			{
					HANDLE handle;
					WORD init_color;
					WORD init_background, init_foreground;

					static WORD get_init_color()
					{
						CONSOLE_SCREEN_BUFFER_INFO csbi;
						GetConsoleScreenBufferInfo(handle, &csbi);
						return csbi.wAttributes;
					}

					Init_bakup(DWORD handle) :
							handle(::GetStdHandle(handle)),
							init_color(get_init_color()),
							init_background(init_color >> 4),
							init_foreground(init_color % 16)
					{
					}
			};

			inline kerbal::container::linked_stack<console_color_config> &
			get_config_stack()
			{
				static kerbal::container::linked_stack<console_color_config> st;
				return st;
			}

			inline void stash_config();

		} // namespace detail

		class costream
		{
			protected:
				struct Init_bakup
				{

						~Init_bakup()
						{
							SetConsoleTextAttribute(handle, init_color);
						}

				} static const bakup;

				std::ostream & k_bind_ostream;
				kerbal::costream::palette k_foreground, k_background;

			public:
				KERBAL_CONSTEXPR
				costream(std::ostream & bind_ostream,
						 kerbal::costream::palette foreground = kerbal::costream::INIT,
						 kerbal::costream::palette background = kerbal::costream::INIT) :
						k_bind_ostream(bind_ostream),
						k_foreground(foreground),
						k_background(background)
				{
				}

				template <class T>
				costream & operator<<(const T & src)
				{
					HANDLE handle = bakup.handle;
					WORD colorOld = bakup.init_color;
					WORD color = (
									this->k_background == kerbal::costream::INIT ?
									bakup.init_background :
									this->k_background.ID
								) * 16 + (
									this->k_foreground == kerbal::costream::INIT ?
									bakup.init_foreground :
									this->k_foreground.ID
								);
					SetConsoleTextAttribute(handle, color);
					this->k_bind_ostream << src;
					SetConsoleTextAttribute(handle, colorOld);

					return *this;
				}

				costream & operator<<(std::ostream& (*pf)(std::ostream&))
				{
					pf(this->k_bind_ostream);
					return *this;
				}
		};

		const typename costream::Init_bakup costream::bakup(
				STD_OUTPUT_HANDLE);

	} // namespace costream

} // namespace kerbal

#endif // KERBAL_COSTREAM_DETAIL_COSTREAM_WIN_PART_HPP
