/**
 * @file       costream.impl.hpp
 * @brief
 * @date       2023-9-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COSTREAM_UNIX_COSTREAM_COSTREAM_IMPL_HPP
#define KERBAL_COSTREAM_UNIX_COSTREAM_COSTREAM_IMPL_HPP

#include <kerbal/costream/unix/costream/costream.decl.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/costream/unix/palette.hpp>

#include <iostream>


namespace kerbal
{

	namespace costream
	{

		namespace _unix
		{

			KERBAL_CONSTEXPR
			costream::costream(
					std::ostream & bind_ostream,
					kerbal::costream::_unix::palette foreground,
					kerbal::costream::_unix::palette background
			) :
					k_bind_ostream(bind_ostream),
					k_foreground(foreground),
					k_background(background)
			{
			}

			template <typename T>
			costream & costream::operator<<(const T & src)
			{
				if (this->k_foreground != kerbal::costream::_unix::INIT) {
					if (this->k_foreground.native_id() > 100) {
						this->k_bind_ostream << "\033[1m";
						this->k_bind_ostream << "\033[" << this->k_foreground.native_id() - 70 << "m";
					} else {
						this->k_bind_ostream << "\033[" << 30 + this->k_foreground.native_id() << "m";
					}
				}

				if (this->k_background != kerbal::costream::_unix::INIT) {
					if (this->k_background.native_id() >= 100) {
						this->k_bind_ostream << "\033[" << this->k_background.native_id() - 60 << "m";
					} else {
						this->k_bind_ostream << "\033[" << 40 + this->k_background.native_id() << "m";
					}
				}

				this->k_bind_ostream << src << "\033[0m";
				return *this;
			}

			costream & costream::operator<<(std::ostream & (* pf)(std::ostream &))
			{
				pf(this->k_bind_ostream);
				return *this;
			}

		} // namespace _unix

	} // namespace costream

} // namespace kerbal

#endif // KERBAL_COSTREAM_UNIX_COSTREAM_COSTREAM_IMPL_HPP
