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
#include <kerbal/type_traits/remove_cv.hpp>
#include <kerbal/type_traits/type_identity.hpp>

#if __cplusplus >= 201103L
#	include <cstddef>
#	include <type_traits>
#endif

namespace kerbal
{

	namespace type_traits
	{

		template <typename Tp, bool = kerbal::type_traits::is_arithmetic<Tp>::value>
		struct __is_signed_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_signed_helper<Tp, true>: kerbal::type_traits::bool_constant<Tp(-1) < Tp(0)>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_signed: kerbal::type_traits::__is_signed_helper<Tp>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_unsigned: kerbal::type_traits::bool_constant<
									kerbal::type_traits::is_arithmetic<Tp>::value &&
									!(kerbal::type_traits::is_signed<Tp>::value)
							>
		{
		};


		template <typename Tp>
		struct __make_unsigned_helper: kerbal::type_traits::type_identity<Tp>
		{
		};

		/*template <>
		struct __make_unsigned_helper<bool>
		{
		};*/

		template <>
		struct __make_unsigned_helper<char>: kerbal::type_traits::type_identity<unsigned char>
		{
		};

		template <>
		struct __make_unsigned_helper<signed char>: kerbal::type_traits::type_identity<unsigned char>
		{
		};

		template <>
		struct __make_unsigned_helper<short>: kerbal::type_traits::type_identity<unsigned short>
		{
		};

		template <>
		struct __make_unsigned_helper<int>: kerbal::type_traits::type_identity<unsigned int>
		{
		};

		template <>
		struct __make_unsigned_helper<long>: kerbal::type_traits::type_identity<unsigned long>
		{
		};

		template <>
		struct __make_unsigned_helper<long long>: kerbal::type_traits::type_identity<unsigned long long>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct make_unsigned:
				kerbal::type_traits::copy_cv<
						Tp,
						typename kerbal::type_traits::__make_unsigned_helper<
								typename kerbal::type_traits::remove_cv<Tp>::type
						>::type
				>
		{
		};



		template <typename Tp>
		struct __make_signed_helper: kerbal::type_traits::type_identity<Tp>
		{
		};

		template <>
		struct __make_signed_helper<char>: kerbal::type_traits::type_identity<signed char>
		{
		};

		template <>
		struct __make_signed_helper<unsigned char>: kerbal::type_traits::type_identity<signed char>
		{
		};

		template <>
		struct __make_signed_helper<unsigned short>: kerbal::type_traits::type_identity<signed short>
		{
		};

		template <>
		struct __make_signed_helper<unsigned int>: kerbal::type_traits::type_identity<signed int>
		{
		};

		template <>
		struct __make_signed_helper<unsigned long>: kerbal::type_traits::type_identity<signed long>
		{
		};

		template <>
		struct __make_signed_helper<unsigned long long>: kerbal::type_traits::type_identity<signed long long>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct make_signed:
				kerbal::type_traits::copy_cv<
						Tp,
						typename kerbal::type_traits::__make_signed_helper<
								typename kerbal::type_traits::remove_cv<Tp>::type
						>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_SIGN_DEDUCTION_HPP
