/**
 * @file       max_sa_sb.hpp
 * @brief
 * @date       2022-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_MAX_SA_SB_HPP
#define KERBAL_SMATH_MAX_SA_SB_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace smath
	{

		KERBAL_MODULE_EXPORT
		template <typename ResultType, ResultType a, ResultType b>
		struct max_sa_sb :
			kerbal::type_traits::integral_constant<ResultType, (a > b ? a : b)>
		{
		};

	} // namespace smath

} // namespace kerbal

#endif // KERBAL_SMATH_MAX_SA_SB_HPP
