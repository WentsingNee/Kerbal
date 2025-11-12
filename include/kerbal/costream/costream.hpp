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

#ifndef KERBAL_COSTREAM_COSTREAM_HPP
#define KERBAL_COSTREAM_COSTREAM_HPP

#include <kerbal/config/system.hpp>

#if KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX || KERBAL_SYSTEM == KERBAL_SYSTEM_APPLE


#	include <kerbal/costream/detail/unix/costream.hpp>
#	include <kerbal/costream/detail/unix/palette.hpp>

#	define KERBAL_HAS_COSTREAM_SUPPORT 1


namespace kerbal
{

	namespace costream
	{

		using namespace kerbal::costream::detail::unix;

	} // namespace costream

} // namespace kerbal


#elif KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS


#	include <kerbal/costream/detail/win/costream.hpp>
#	include <kerbal/costream/detail/win/palette.hpp>

#	define KERBAL_HAS_COSTREAM_SUPPORT 1


namespace kerbal
{

	namespace costream
	{

		using namespace kerbal::costream::detail::win;

	} // namespace costream

} // namespace kerbal


#else
#	define KERBAL_HAS_COSTREAM_SUPPORT 0
#endif

#endif // KERBAL_COSTREAM_COSTREAM_HPP
