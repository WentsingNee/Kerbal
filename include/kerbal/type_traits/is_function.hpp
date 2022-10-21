/**
 * @file       is_function.hpp
 * @brief
 * @date       2019-6-25
 * @author     Peter
 * @remark     renamed from function_deduction.hpp
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_FUNCTION_HPP
#define KERBAL_TYPE_TRAITS_IS_FUNCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_const.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_function :
				kerbal::type_traits::bool_constant<
					!kerbal::type_traits::is_const<const T>::value
				>
		{
		};

		template <typename T>
		struct is_function<T &> :
				kerbal::type_traits::false_type
		{
		};

#	if __cplusplus >= 201103L

		template <typename T>
		struct is_function<T &&> :
				kerbal::type_traits::false_type
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_FUNCTION_HPP
