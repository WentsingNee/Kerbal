/**
 * @file       ignore_unused.hpp
 * @brief
 * @date       2020-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_IGNORE_UNUSED_HPP
#define KERBAL_UTILITY_IGNORE_UNUSED_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{

	namespace utility
	{

		template <typename Tp>
		KERBAL_CONSTEXPR14
		void ignore_unused(const Tp &) KERBAL_NOEXCEPT
		{
		}

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_IGNORE_UNUSED_HPP
