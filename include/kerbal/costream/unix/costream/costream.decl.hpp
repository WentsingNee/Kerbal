/**
 * @file       costream.decl.hpp
 * @brief
 * @date       2023-9-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COSTREAM_UNIX_COSTREAM_COSTREAM_DECL_HPP
#define KERBAL_COSTREAM_UNIX_COSTREAM_COSTREAM_DECL_HPP

#include <kerbal/costream/unix/costream/costream.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/costream/unix/palette.hpp>

#include <iostream>


namespace kerbal
{

	namespace costream
	{

		namespace _unix
		{

			class costream
			{
				protected:
					std::ostream & k_bind_ostream;
					kerbal::costream::_unix::palette k_foreground, k_background;

				public:
					KERBAL_CONSTEXPR
					costream(
							std::ostream & bind_ostream,
							kerbal::costream::_unix::palette foreground = kerbal::costream::_unix::INIT,
							kerbal::costream::_unix::palette background = kerbal::costream::_unix::INIT)
					;

					template <typename T>
					costream & operator<<(const T & src);

					costream & operator<<(std::ostream & (* pf)(std::ostream &));
			};

		} // namespace _unix

	} // namespace costream

} // namespace kerbal

#endif // KERBAL_COSTREAM_UNIX_COSTREAM_COSTREAM_DECL_HPP
