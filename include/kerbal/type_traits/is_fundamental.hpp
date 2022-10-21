/**
 * @file       is_fundamental.hpp
 * @brief
 * @date       2022-10-30
 * @remark     split up from kerbal/type_traits/fundamental_deduction.hpp, 2019-5-9
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_FUNDAMENTAL_HPP
#define KERBAL_TYPE_TRAITS_IS_FUNDAMENTAL_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_arithmetic.hpp>
#include <kerbal/type_traits/is_void.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_null_pointer.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename T>
		struct is_fundamental :
				kerbal::type_traits::bool_constant<
					   kerbal::type_traits::is_arithmetic<T>::value
					|| kerbal::type_traits::is_void<T>::value
#	if __cplusplus >= 201103L
					|| kerbal::type_traits::is_null_pointer<T>::value
#	endif
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_FUNDAMENTAL_HPP
