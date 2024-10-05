/**
 * @file       endian.hpp
 * @brief
 * @date       2024-10-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_ENDIAN_HPP
#define KERBAL_CONFIG_ENDIAN_HPP

#include <kerbal/config/architecture.hpp>

#if \
	KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_X86 || \
	KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_AMD64
#	include <kerbal/config/detail/endian/endian._1_x86.part.hpp>
#endif


namespace kerbal
{

	namespace config
	{

		typedef kerbal::type_traits::integral_constant<
			kerbal::config::endian,
			KERBAL_BYTE_ORDER
		> KERBAL_BYTE_ORDER_TYPEDEF;

	} // namespace config

} // namespace kerbal

#endif // KERBAL_CONFIG_ENDIAN_HPP
