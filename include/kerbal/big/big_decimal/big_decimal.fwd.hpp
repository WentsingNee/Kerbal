/**
 * @file       big_decimal.fwd.hpp
 * @brief
 * @date       2024-04-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BIG_BIG_DECIMAL_BIG_DECIMAL_FWD_HPP
#define KERBAL_BIG_BIG_DECIMAL_BIG_DECIMAL_FWD_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/container/vector/vector.fwd.hpp>


namespace kerbal
{

	namespace big
	{

		template <typename Unit, typename Container = kerbal::container::vector<Unit> >
		class basic_big_decimal;

		typedef basic_big_decimal<
			kerbal::compatibility::uint32_t
		> big_decimal;

		typedef basic_big_decimal<
			kerbal::compatibility::uint64_t
		> big_decimal64;

	} // namespace big

} // namespace kerbal

#endif // KERBAL_BIG_BIG_DECIMAL_BIG_DECIMAL_FWD_HPP
