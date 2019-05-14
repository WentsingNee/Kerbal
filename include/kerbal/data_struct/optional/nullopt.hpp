/*
 * nullopt.hpp
 *
 *  Created on: 2018年10月28日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_NULLOPT_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_NULLOPT_HPP_

#include <kerbal/compatibility/compatibility_macro.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>
#include <kerbal/data_struct/optional/optional_settings.hpp>

namespace kerbal
{
	namespace data_struct
	{

		struct nullopt_t;

		template <typename Type>
		struct __is_nullopt_helper: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_nullopt_helper<kerbal::data_struct::nullopt_t > : kerbal::type_traits::true_type
		{
		};

#	if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL==1
		template <>
		struct __is_nullopt_helper<std::nullopt_t > : kerbal::type_traits::true_type
		{
		};
#	endif

#	if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL==1
		template <>
		struct __is_nullopt_helper<boost::none_t > : kerbal::type_traits::true_type
		{
		};
#	endif

		template <typename Type>
		struct is_nullopt: __is_nullopt_helper<typename kerbal::type_traits::remove_cvref<Type>::type>
		{
		};

		struct nullopt_t
		{
		};

#	if __cplusplus < 201103L
		extern const nullopt_t nullopt;
#	else
		constexpr const nullopt_t nullopt;
#	endif

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator==(const kerbal::data_struct::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator!=(const kerbal::data_struct::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator<(const kerbal::data_struct::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator>(const kerbal::data_struct::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator<=(const kerbal::data_struct::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator>=(const kerbal::data_struct::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator==(const NulloptType &, const kerbal::data_struct::nullopt_t &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator!=(const NulloptType &, const kerbal::data_struct::nullopt_t &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator<(const NulloptType &, const kerbal::data_struct::nullopt_t &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator>(const NulloptType &, const kerbal::data_struct::nullopt_t &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator<=(const NulloptType &, const kerbal::data_struct::nullopt_t &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::data_struct::is_nullopt<NulloptType>::value, bool>::type
		operator>=(const NulloptType &, const kerbal::data_struct::nullopt_t &) KERBAL_NOEXCEPT
		{
			return true;
		}


	} /* namespace data_struct */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_NULLOPT_HPP_ */
