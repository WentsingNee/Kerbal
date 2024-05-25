/**
 * @file       is_arithmetic.hpp
 * @brief
 * @date       2022-10-30
 * @author     Peter
 * @remark     split up from kerbal/type_traits/fundamental_deduction.hpp, 2019-5-9
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_ARITHMETIC_HPP
#define KERBAL_TYPE_TRAITS_IS_ARITHMETIC_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/is_floating_point.hpp>
#include <kerbal/type_traits/is_integral.hpp>
#include <kerbal/type_traits/logical.hpp>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <class T>
		struct is_arithmetic :
			kerbal::type_traits::disjunction<
				kerbal::type_traits::is_integral<T>,
				kerbal::type_traits::is_floating_point<T>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_ARITHMETIC_HPP
