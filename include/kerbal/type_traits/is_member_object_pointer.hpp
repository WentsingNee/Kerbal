/**
 * @file       is_member_object_pointer.hpp
 * @brief
 * @date       2022-11-25
 * @author     Peter
 * @remark     split up from kerbal/type_traits/member_pointer_deduction.hpp, 2019-7-3
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
#define KERBAL_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/is_member_pointer.hpp>
#include <kerbal/type_traits/is_member_function_pointer.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename T>
		struct is_member_object_pointer :
				kerbal::type_traits::bool_constant<
					kerbal::type_traits::is_member_pointer<T>::value &&
					!kerbal::type_traits::is_member_function_pointer<T>::value
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
