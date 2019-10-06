/**
 * @file       addressof.hpp
 * @brief      
 * @date       2019-7-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_ADDRESSOF_HPP_
#define KERBAL_UTILITY_ADDRESSOF_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{
	namespace utility
	{
		template <typename Tp>
		Tp* addressof(Tp& arg) KERBAL_NOEXCEPT
		{
			return reinterpret_cast<Tp*>(
					&const_cast<char&>(
							reinterpret_cast<const volatile char&>(arg)));
		}

#	if __cplusplus >= 201103L

		template <typename Tp>
		const Tp* addressof(const Tp&&) = delete;

#	endif

	} // namespace utility

} // namespace kerbal

#endif /* KERBAL_UTILITY_ADDRESSOF_HPP_ */
