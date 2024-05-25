/**
 * @file       remove_all_pointers.hpp
 * @brief
 * @date       2022-10-30
 * @author     Peter
 * @remark     split up from kerbal/type_traits/pointer_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REMOVE_ALL_POINTERS_HPP
#define KERBAL_TYPE_TRAITS_REMOVE_ALL_POINTERS_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_pointer.hpp>
#include <kerbal/type_traits/remove_pointer.hpp>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct remove_all_pointers:
			kerbal::type_traits::conditional<
				kerbal::type_traits::is_pointer<T>::value,
				kerbal::type_traits::remove_all_pointers<
					typename kerbal::type_traits::remove_pointer<T>::type
				>,
				kerbal::type_traits::remove_pointer<T>
			>::type
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_REMOVE_ALL_POINTERS_HPP
