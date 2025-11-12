/**
 * @file       costream.hpp
 * @brief
 * @date       2023-9-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COSTREAM_WIN_COSTREAM_HPP
#define KERBAL_COSTREAM_WIN_COSTREAM_HPP

#ifndef NOMINMAX
#	define NOMINMAX
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/linked_stack.hpp>
#include <kerbal/costream/detail/win/palette.hpp>

#include <iostream>

#include <windows.h>


namespace kerbal
{

	namespace costream
	{

		namespace detail
		{

			namespace win
			{

				struct console_color_config
				{
						HANDLE handle;
						WORD init_color;
						WORD init_background, init_foreground;

						static WORD
						get_init_color()
						{
							CONSOLE_SCREEN_BUFFER_INFO csbi;
							GetConsoleScreenBufferInfo(handle, &csbi);
							return csbi.wAttributes;
						}
				};

				inline
				kerbal::container::linked_stack<console_color_config> &
				get_config_stack()
				{
					static kerbal::container::linked_stack<console_color_config> st;
					return st;
				}

				inline
				void
				stash_config();

				class costream
				{
					protected:
						struct init_backup
						{

								init_bakup(DWORD handle) :
									handle(::GetStdHandle(handle)),
									init_color(get_init_color()),
									init_background(init_color >> 4),
									init_foreground(init_color % 16)
								{
								}

								~init_backup()
								{
									SetConsoleTextAttribute(handle, init_color);
								}

						} static const k_backup;

						std::ostream & k_bind_ostream;
						palette k_foreground, k_background;

					public:
						KERBAL_CONSTEXPR
						costream(
							std::ostream & bind_ostream,
							palette foreground = INIT_PALETTE,
							palette background = INIT_PALETTE
						) :
							k_bind_ostream(bind_ostream),
							k_foreground(foreground),
							k_background(background)
						{
						}

						template <class T>
						costream &
						operator<<(const T & src)
						{
							HANDLE handle = bakup.handle;
							WORD colorOld = bakup.init_color;
							WORD color = (
								this->k_background == INIT_PALETTE ?
								bakup.init_background :
								this->k_background.ID
							) * 16 + (
								this->k_foreground == INIT_PALETTE ?
								bakup.init_foreground :
								this->k_foreground.ID
							);
							SetConsoleTextAttribute(handle, color);
							this->k_bind_ostream << src;
							SetConsoleTextAttribute(handle, colorOld);

							return *this;
						}

						costream &
						operator<<(std::ostream& (*pf)(std::ostream&))
						{
							pf(this->k_bind_ostream);
							return *this;
						}
				};

				costream::init_backup const
				costream::k_backup(
					STD_OUTPUT_HANDLE
				);

			} // namespace win

		} // namespace detail

	} // namespace costream

} // namespace kerbal

#endif // KERBAL_COSTREAM_WIN_COSTREAM_HPP
