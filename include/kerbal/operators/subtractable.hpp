/**
 * @file       subtractable.hpp
 * @brief
 * @date       2019-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_SUBTRACTABLE_HPP_
#define KERBAL_OPERATORS_SUBTRACTABLE_HPP_

#include <kerbal/compatibility/constexpr.hpp>

namespace kerbal
{
	namespace operators
	{

		template <typename Tp, typename Up>
		struct subtractable
		{
				KERBAL_CONSTEXPR14
				friend Tp operator-(Tp lhs, const Up& rhs)
				{
					lhs -= rhs;
					return lhs;
				}
		};

	} // namespace operators

} // namespace kerbal

#endif /* KERBAL_OPERATORS_SUBTRACTABLE_HPP_ */
