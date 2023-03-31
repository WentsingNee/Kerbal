/**
 * @file       is_integral.hpp
 * @brief
 * @date       2022-10-30
 * @author     Peter
 * @remark     split up from kerbal/type_traits/fundamental_deduction.hpp, 2019-5-9
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_INTEGRAL_HPP
#define KERBAL_TYPE_TRAITS_IS_INTEGRAL_HPP

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
			struct is_integral_helper : kerbal::type_traits::false_type
			{
			};

			template <>
			struct is_integral_helper<bool> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<char> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<signed char> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<unsigned char> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<wchar_t> : kerbal::type_traits::true_type
			{
			};

#	if __cpp_char8_t >= 201811L

			template <>
			struct is_integral_helper<char8_t> : kerbal::type_traits::true_type
			{
			};

#	endif

#	if __cplusplus >= 201103L

			template <>
			struct is_integral_helper<char16_t> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<char32_t> : kerbal::type_traits::true_type
			{
			};

#	endif

			template <>
			struct is_integral_helper<short> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<unsigned short> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<int> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<unsigned int> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<long> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<unsigned long> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<long long> : kerbal::type_traits::true_type
			{
			};

			template <>
			struct is_integral_helper<unsigned long long> : kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_integral :
				kerbal::type_traits::detail::is_integral_helper<
					typename kerbal::type_traits::remove_cv<T>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_INTEGRAL_HPP
