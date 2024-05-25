/**
 * @file       is_floating_point.hpp
 * @brief
 * @date       2022-10-30
 * @author     Peter
 * @remark     split up from kerbal/type_traits/fundamental_deduction.hpp, 2019-5-9
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_FLOATING_POINT_HPP
#define KERBAL_TYPE_TRAITS_IS_FLOATING_POINT_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_cv.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename>
			struct is_floating_point_helper : kerbal::type_traits::false_type
			{
			};

			template <>
			struct is_floating_point_helper<float> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_floating_point_helper<double> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_floating_point_helper<long double> : kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_floating_point :
			kerbal::type_traits::detail::is_floating_point_helper<
				typename kerbal::type_traits::remove_cv<T>::type
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_FLOATING_POINT_HPP
