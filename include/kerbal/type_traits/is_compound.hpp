/**
 * @file       is_compound.hpp
 * @brief
 * @date       2022-10-30
 * @remark     split up from kerbal/type_traits/fundamental_deduction.hpp, 2019-5-9
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_COMPOUND_HPP
#define KERBAL_TYPE_TRAITS_IS_COMPOUND_HPP

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_fundamental.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_compound :
			kerbal::type_traits::bool_constant<!is_fundamental<T>::value>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_COMPOUND_HPP
