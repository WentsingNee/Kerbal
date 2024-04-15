/**
 * @file       big_integer.fwd.hpp
 * @brief
 * @date       2024-04-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BIG_BIG_INTEGER_BIG_INTEGER_FWD_HPP
#define KERBAL_BIG_BIG_INTEGER_BIG_INTEGER_FWD_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/container/vector/vector.fwd.hpp>


namespace kerbal
{

	namespace big
	{

		template <typename Unit, typename Container = kerbal::container::vector<Unit> >
		class basic_big_integer;

		typedef basic_big_integer<
			kerbal::compatibility::uint32_t,
			kerbal::container::vector<kerbal::compatibility::uint32_t>
		> big_integer;

	} // namespace big

} // namespace kerbal

#endif // KERBAL_BIG_BIG_INTEGER_BIG_INTEGER_FWD_HPP
