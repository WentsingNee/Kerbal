/**
 * @file       costream.unix.part.hpp
 * @brief
 * @date       2023-9-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COSTREAM_DETAIL_COSTREAM_UNIX_PART_HPP
#define KERBAL_COSTREAM_DETAIL_COSTREAM_UNIX_PART_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/costream/palette.hpp>

#include <iostream>


namespace kerbal
{

	namespace costream
	{

		class costream
		{
			protected:
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

				template<class T>
				costream & operator<<(const T & src)
				{
					if (this->k_foreground != kerbal::costream::INIT) {
						if (this->k_foreground.k_color_id > 100) {
							this->k_bind_ostream << "\033[1m";
							this->k_bind_ostream << "\033[" << this->k_foreground.k_color_id - 70 << "m";
						} else {
							this->k_bind_ostream << "\033[" << 30 + this->k_foreground.k_color_id << "m";
						}
					}

					if (this->k_background != kerbal::costream::INIT) {
						if (this->k_background.k_color_id >= 100) {
							this->k_bind_ostream << "\033[" << this->k_background.k_color_id - 60 << "m";
						} else {
							this->k_bind_ostream << "\033[" << 40 + this->k_background.k_color_id << "m";
						}
					}

					this->k_bind_ostream << src << "\033[0m";
					return *this;
				}

				costream & operator<<(std::ostream & (* pf)(std::ostream &))
				{
					pf(this->k_bind_ostream);
					return *this;
				}
		};

	} // namespace costream

} // namespace kerbal

#endif // KERBAL_COSTREAM_DETAIL_COSTREAM_UNIX_PART_HPP
