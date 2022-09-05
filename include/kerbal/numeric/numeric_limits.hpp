/**
 * @file       numeric_limits.hpp
 * @brief
 * @date       2021-02-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_NUMERIC_LIMITS_HPP
#define KERBAL_NUMERIC_NUMERIC_LIMITS_HPP

#include <kerbal/type_traits/fundamental_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <cfloat>
#include <climits>

#if __cplusplus >= 201103L
#	include <cstdint>
#endif


namespace kerbal
{

	namespace numeric
	{

		template <typename T>
		class numeric_limits;

		namespace detail
		{

			template <bool B>
			struct _K_is_specialized;

			template <>
			struct _K_is_specialized<false>
			{
					typedef kerbal::type_traits::false_type IS_SPECIALIZED;
			};

			template <>
			struct _K_is_specialized<true>
			{
					typedef kerbal::type_traits::true_type IS_SPECIALIZED;
			};


			template <typename T, bool IsSigned = kerbal::type_traits::is_signed<T>::value>
			struct _K_is_signed
			{
					typedef kerbal::type_traits::bool_constant<IsSigned> IS_SIGNED;
			};


			template <typename T>
			struct _K_is_integer
			{
					typedef kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_integral<T>::value
					> IS_INTEGER;
			};


			template <int Digits>
			struct _K_digits
			{
					typedef kerbal::type_traits::integral_constant<
						int, Digits
					> DIGITS;
			};


			template <typename T, T Min>
			struct _K_min
			{
					typedef kerbal::type_traits::integral_constant<
						T, Min
					> MIN;
			};


			template <typename T, T Max>
			struct _K_max
			{
					typedef kerbal::type_traits::integral_constant<
						T, Max
					> MAX;
			};

		}

		template<>
		class numeric_limits<bool> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<bool>
				, public detail::_K_is_integer<bool>
				, public detail::_K_digits<1>
				, public detail::_K_min<bool, false>
				, public detail::_K_max<bool, true>
		{
		};

		template<>
		class numeric_limits<char> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<char>
				, public detail::_K_is_integer<char>
				, public detail::_K_digits<CHAR_BIT - detail::_K_is_signed<char>::IS_SIGNED::value>
				, public detail::_K_min<char, CHAR_MIN>
				, public detail::_K_max<char, CHAR_MAX>
		{
		};

		template<>
		class numeric_limits<signed char> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<signed char>
				, public detail::_K_is_integer<signed char>
				, public detail::_K_digits<CHAR_BIT - 1>
				, public detail::_K_min<signed char, SCHAR_MIN>
				, public detail::_K_max<signed char, SCHAR_MAX>
		{
		};

		template<>
		class numeric_limits<unsigned char> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<unsigned char>
				, public detail::_K_is_integer<unsigned char>
				, public detail::_K_digits<CHAR_BIT>
				, public detail::_K_min<unsigned char, 0>
				, public detail::_K_max<unsigned char, UCHAR_MAX>
		{
		};

		template<>
		class numeric_limits<wchar_t> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<wchar_t>
				, public detail::_K_is_integer<wchar_t>
				, public detail::_K_digits<CHAR_BIT * sizeof(wchar_t) - detail::_K_is_signed<wchar_t>::IS_SIGNED::value>
#		if __cplusplus >= 201103L || defined(WCHAR_MIN)
				, public detail::_K_min<wchar_t, WCHAR_MIN>
#		else
				, public detail::_K_min<wchar_t, static_cast<wchar_t>(1 << (CHAR_BIT * sizeof(wchar_t) - 1))>
#		endif
#		if __cplusplus >= 201103L || defined(WCHAR_MAX)
				, public detail::_K_max<wchar_t, WCHAR_MAX>
#		else
				, public detail::_K_max<wchar_t, static_cast<wchar_t>(~(1 << (CHAR_BIT * sizeof(wchar_t) - 1)))>
#		endif
		{
		};

#	if __cplusplus > 201703L

		template<>
		class numeric_limits<char8_t> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<char8_t>
				, public detail::_K_is_integer<char8_t>
				, public detail::_K_digits<CHAR_BIT>
				, public detail::_K_min<char8_t, 0>
				, public detail::_K_max<char8_t, UCHAR_MAX>
		{
		};

#	endif

#	if __cplusplus >= 201103L

		template<>
		class numeric_limits<char16_t> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<char16_t>
				, public detail::_K_is_integer<char16_t>
				, public detail::_K_digits<CHAR_BIT * sizeof(char16_t)>
				, public detail::_K_min<char16_t, 0>
				, public detail::_K_max<char16_t, UINT_LEAST16_MAX>
		{
		};

		template<>
		class numeric_limits<char32_t> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<char32_t>
				, public detail::_K_is_integer<char32_t>
				, public detail::_K_digits<CHAR_BIT * sizeof(char32_t)>
				, public detail::_K_min<char32_t, 0>
				, public detail::_K_max<char32_t, UINT_LEAST32_MAX>
		{
		};

#	endif

		template<>
		class numeric_limits<short> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<short>
				, public detail::_K_is_integer<short>
				, public detail::_K_digits<CHAR_BIT * sizeof(short) - 1>
				, public detail::_K_min<short, SHRT_MIN>
				, public detail::_K_max<short, SHRT_MAX>
		{
		};

		template<>
		class numeric_limits<unsigned short> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<unsigned short>
				, public detail::_K_is_integer<unsigned short>
				, public detail::_K_digits<CHAR_BIT * sizeof(short)>
				, public detail::_K_min<unsigned short, 0>
				, public detail::_K_max<unsigned short, USHRT_MAX>
		{
		};

		template<>
		class numeric_limits<int> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<int>
				, public detail::_K_is_integer<int>
				, public detail::_K_digits<CHAR_BIT * sizeof(int) - 1>
				, public detail::_K_min<int, INT_MIN>
				, public detail::_K_max<int, INT_MAX>
		{
		};

		template<>
		class numeric_limits<unsigned int> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<unsigned int>
				, public detail::_K_is_integer<unsigned int>
				, public detail::_K_digits<CHAR_BIT * sizeof(int)>
				, public detail::_K_min<unsigned int, 0>
				, public detail::_K_max<unsigned int, UINT_MAX>
		{
		};

		template<>
		class numeric_limits<long> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<long>
				, public detail::_K_is_integer<long>
				, public detail::_K_digits<CHAR_BIT * sizeof(long) - 1>
				, public detail::_K_min<long, LONG_MIN>
				, public detail::_K_max<long, LONG_MAX>
		{
		};

		template<>
		class numeric_limits<unsigned long> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<unsigned long>
				, public detail::_K_is_integer<unsigned long>
				, public detail::_K_digits<CHAR_BIT * sizeof(long)>
				, public detail::_K_min<unsigned long, 0>
				, public detail::_K_max<unsigned long, ULONG_MAX>
		{
		};

		template<>
		class numeric_limits<long long> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<long long>
				, public detail::_K_is_integer<long long>
				, public detail::_K_digits<CHAR_BIT * sizeof(long long) - 1>
				, public detail::_K_min<long long, LLONG_MIN>
				, public detail::_K_max<long long, LLONG_MAX>
		{
		};

		template<>
		class numeric_limits<unsigned long long> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<unsigned long long>
				, public detail::_K_is_integer<unsigned long long>
				, public detail::_K_digits<CHAR_BIT * sizeof(long long)>
				, public detail::_K_min<unsigned long long, 0>
				, public detail::_K_max<unsigned long long, ULLONG_MAX>
		{
		};

		template<>
		class numeric_limits<float> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<float, true>
				, public detail::_K_is_integer<float>
				, public detail::_K_digits<FLT_MANT_DIG>
		{
		};

		template<>
		class numeric_limits<double> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<double, true>
				, public detail::_K_is_integer<double>
				, public detail::_K_digits<DBL_MANT_DIG>
		{
		};

		template<>
		class numeric_limits<long double> :
				  public detail::_K_is_specialized<true>
				, public detail::_K_is_signed<long double, true>
				, public detail::_K_is_integer<long double>
				, public detail::_K_digits<LDBL_MANT_DIG>
		{
		};

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_NUMERIC_LIMITS_HPP
