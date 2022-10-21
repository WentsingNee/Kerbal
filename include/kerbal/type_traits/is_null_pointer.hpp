/**
 * @file       is_null_pointer.hpp
 * @brief
 * @date       2022-10-21
 * @author     Peter
 * @remark     split up from kerbal/type_traits/fundamental_deduction.hpp, 2019-5-9
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_NULL_POINTER_HPP
#define KERBAL_TYPE_TRAITS_IS_NULL_POINTER_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/type_traits/remove_cv.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus >= 201103L

		namespace detail
		{

			template <typename T>
			struct is_null_pointer_helper : kerbal::type_traits::false_type
			{
			};

			template <>
			struct is_null_pointer_helper<decltype(nullptr)> : kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		MODULE_EXPORT
		template <typename T>
		struct is_null_pointer :
				kerbal::type_traits::detail::is_null_pointer_helper<
					typename kerbal::type_traits::remove_cv<T>::type
				>
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_NULL_POINTER_HPP
