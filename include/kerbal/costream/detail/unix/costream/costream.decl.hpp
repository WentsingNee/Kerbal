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

#include <kerbal/costream/detail/unix/costream/costream.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/costream/detail/unix/palette.hpp>

#include <iostream>


namespace kerbal
{

	namespace costream
	{

		namespace detail
		{

			namespace unix
			{

				class costream
				{
					protected:
						std::ostream & k_bind_ostream;
						palette k_foreground, k_background;

					public:
						KERBAL_CONSTEXPR
						costream(
							std::ostream & bind_ostream,
							palette foreground = INIT_PALETTE,
							palette background = INIT_PALETTE
						);

						template <typename T>
						costream & operator<<(const T & src);

						costream & operator<<(std::ostream & (* pf)(std::ostream &));
				};

			} // namespace unix

		} // namespace detail

	} // namespace costream

} // namespace kerbal

#endif // KERBAL_COSTREAM_UNIX_COSTREAM_COSTREAM_DECL_HPP
