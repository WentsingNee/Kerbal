/**
 * @file       sign_deduction.hpp
 * @brief
 * @date       2020-4-2
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_SIGN_DEDUCTION_HPP
#define KERBAL_TYPE_TRAITS_SIGN_DEDUCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/copy_cv.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_arithmetic.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_cv.hpp>
#include <kerbal/type_traits/type_identity.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <
				typename T,
				bool = kerbal::type_traits::is_arithmetic<T>::value
			>
			struct is_signed_helper :
				kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct is_signed_helper<T, true> :
				kerbal::type_traits::bool_constant<T(-1) < T(0)>
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_signed :
			kerbal::type_traits::detail::is_signed_helper<T>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_unsigned :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::is_arithmetic<T>,
				kerbal::type_traits::negation<
					kerbal::type_traits::is_signed<T>
				>
			>
		{
		};


		namespace detail
		{

			template <typename T>
			struct make_unsigned_helper :
				kerbal::type_traits::type_identity<T>
			{
			};

			/*template <>
			struct make_unsigned_helper<bool>
			{
			};*/

			template <>
			struct make_unsigned_helper<char> :
				kerbal::type_traits::type_identity<unsigned char>
			{
			};

			template <>
			struct make_unsigned_helper<signed char> :
				kerbal::type_traits::type_identity<unsigned char>
			{
			};

			template <>
			struct make_unsigned_helper<short> :
				kerbal::type_traits::type_identity<unsigned short>
			{
			};

			template <>
			struct make_unsigned_helper<int> :
				kerbal::type_traits::type_identity<unsigned int>
			{
			};

			template <>
			struct make_unsigned_helper<long> :
				kerbal::type_traits::type_identity<unsigned long>
			{
			};

			template <>
			struct make_unsigned_helper<long long> :
				kerbal::type_traits::type_identity<unsigned long long>
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct make_unsigned:
			kerbal::type_traits::copy_cv<
				T,
				typename kerbal::type_traits::detail::make_unsigned_helper<
					typename kerbal::type_traits::remove_cv<T>::type
				>::type
			>
		{
		};



		namespace detail
		{

			template <typename T>
			struct make_signed_helper :
				kerbal::type_traits::type_identity<T>
			{
			};

			template <>
			struct make_signed_helper<char> :
				kerbal::type_traits::type_identity<signed char>
			{
			};

			template <>
			struct make_signed_helper<unsigned char> :
				kerbal::type_traits::type_identity<signed char>
			{
			};

			template <>
			struct make_signed_helper<unsigned short> :
				kerbal::type_traits::type_identity<signed short>
			{
			};

			template <>
			struct make_signed_helper<unsigned int> :
				kerbal::type_traits::type_identity<signed int>
			{
			};

			template <>
			struct make_signed_helper<unsigned long> :
				kerbal::type_traits::type_identity<signed long>
			{
			};

			template <>
			struct make_signed_helper<unsigned long long> :
				kerbal::type_traits::type_identity<signed long long>
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct make_signed:
			kerbal::type_traits::copy_cv<
				T,
				typename kerbal::type_traits::detail::make_signed_helper<
					typename kerbal::type_traits::remove_cv<T>::type
				>::type
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_SIGN_DEDUCTION_HPP
