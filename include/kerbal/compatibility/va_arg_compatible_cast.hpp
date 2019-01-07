/*
 * va_arg_compatible_cast.hpp
 *
 *  Created on: 2018年12月2日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_COMPATIBILITY_VA_ARG_COMPATIBLE_CAST_HPP_
#define INCLUDE_KERBAL_COMPATIBILITY_VA_ARG_COMPATIBLE_CAST_HPP_

#include <kerbal/compatibility/compatibility_macro.hpp>
#include <kerbal/utility/string_ref.hpp>
#include <kerbal/type_traits/type_traits.hpp>
#include <string>

namespace kerbal
{

	namespace compatibility
	{

//		template <typename T>
//		const T& va_arg_compatible_cast(const T& t);

		template <typename T>
		KERBAL_CONSTEXPR
//		typename kerbal::type_traits::enable_if<
//							kerbal::type_traits::is_arithmetic<T>::value || kerbal::type_traits::is_pointer<T>::value,
//						const T&>::type
		const T &
		va_arg_compatible_cast(const T& t) KERBAL_NOEXCEPT
		{
			return t;
		}

		template <size_t N>
		KERBAL_CONSTEXPR const char* va_arg_compatible_cast(const char (&s)[N]) KERBAL_NOEXCEPT
		{
		    return s;
		}

		inline const char * va_arg_compatible_cast(const std::string & s) KERBAL_NOEXCEPT
		{
			return s.c_str();
		}

		inline const char * va_arg_compatible_cast(const kerbal::utility::string_ref & s) KERBAL_NOEXCEPT
		{
			return s.c_str();
		}

#if __cplusplus >= 201103L

		template <typename T>
		constexpr
//		typename kerbal::type_traits::enable_if<
//							kerbal::type_traits::is_arithmetic<T>::value || kerbal::type_traits::is_pointer<T>::value,
//						T&&>::type
		T&&
		va_arg_compatible_cast(T&& t) noexcept
		{
			return std::forward<T>(t);
		}

		constexpr void * va_arg_compatible_cast(std::nullptr_t) noexcept
		{
			return NULL;
		}

		inline const char * va_arg_compatible_cast(std::string&& s) noexcept
		{
			return s.c_str();
		}

		inline const char * va_arg_compatible_cast(kerbal::utility::string_ref&& s) noexcept
		{
			return s.c_str();
		}

#endif

	}
}



#endif /* INCLUDE_KERBAL_COMPATIBILITY_VA_ARG_COMPATIBLE_CAST_HPP_ */
