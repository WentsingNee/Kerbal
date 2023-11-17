/**
 * @file       member_pointer_remove_object.hpp
 * @brief
 * @date       2023-11-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_MEMBER_POINTER_REMOVE_OBJECT_HPP
#define KERBAL_TYPE_TRAITS_MEMBER_POINTER_REMOVE_OBJECT_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename >
			struct member_pointer_remove_object_helper;

			template <typename T, typename U>
			struct member_pointer_remove_object_helper<T U::*>
			{
				typedef T type;
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct member_pointer_remove_object :
				kerbal::type_traits::detail::member_pointer_remove_object_helper<
					typename kerbal::type_traits::remove_cv<T>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_MEMBER_POINTER_REMOVE_OBJECT_HPP
