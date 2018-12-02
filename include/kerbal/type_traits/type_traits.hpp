/**
 * @file		type_traits.hpp
 * @brief
 * @date		2018年6月23日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_

#include <cstddef>
#include <kerbal/compatibility/compatibility_macro.hpp>

namespace kerbal
{
	namespace type_traits
	{

		template <typename Type, Type val>
		struct integral_constant
		{
#			if __cplusplus >= 201103L
				static constexpr Type value = val;
#			else
				static const Type value = val;
#			endif

				typedef Type value_type;
				typedef integral_constant<Type, val> type;

				KERBAL_CONSTEXPR operator value_type() const
				{
					return value;
				}
		};

		struct false_type : integral_constant<bool, false>
		{
		};

		struct true_type : integral_constant<bool, true>
		{
		};

		template <bool condition, typename Tp = void>
		struct enable_if
		{
		};

		template <typename Tp>
		struct enable_if<true, Tp>
		{
				typedef Tp type;
		};

#	if __cplusplus >= 201103L

		template <unsigned long long N, typename Type0, typename ... Args>
		struct type_chooser;

		template <typename Type0, typename ... Args>
		struct type_chooser<0, Type0, Args...>
		{
				typedef Type0 type;
		};

		template <unsigned long long N, typename Type0, typename ... Args>
		struct type_chooser
		{
				static_assert(N <= sizeof...(Args), "N is larger than the number of template type arguments");
				typedef typename type_chooser<N - 1, Args...>::type type;
		};

#	endif

		template <bool condition, typename TrueType, typename FalseType>
		struct conditional
		{
				typedef TrueType type;
		};

		template <typename TrueType, typename FalseType>
		struct conditional<false, TrueType, FalseType>
		{
				typedef FalseType type;
		};

		template <bool condition>
		struct conditional_boolean : kerbal::type_traits::conditional<condition,
											kerbal::type_traits::true_type,
											kerbal::type_traits::false_type>::type
		{
		};

		template <typename Tp, typename Up>
		struct is_same : kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct is_same<Tp, Tp> : kerbal::type_traits::true_type
		{
		};

		template <typename Tp>
		struct is_reference : kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct is_reference<Tp&> : kerbal::type_traits::true_type
		{
		};

#	if __cplusplus >= 201103L

		template <typename Tp>
		struct is_reference<Tp&&> : kerbal::type_traits::true_type
		{
		};

#	endif

		template <typename Tp>
		struct remove_reference
		{
				typedef Tp type;
		};

		template <typename Tp>
		struct remove_reference<Tp&>
		{
				typedef Tp type;
		};

#	if __cplusplus >= 201103L

		template <typename Tp>
		struct remove_reference<Tp&&>
		{
				typedef Tp type;
		};

#	endif

		template <typename >
		struct is_const: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct is_const<Tp const> : kerbal::type_traits::true_type
		{
		};

		template <typename >
		struct is_volatile: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct is_volatile<Tp volatile> : kerbal::type_traits::true_type
		{
		};

		template <typename Tp>
		struct remove_const
		{
				typedef Tp type;
		};

		template <typename Tp>
		struct remove_const<Tp const>
		{
				typedef Tp type;
		};

		template <typename Tp>
		struct remove_volatile
		{
				typedef Tp type;
		};

		template <typename Tp>
		struct remove_volatile<Tp volatile>
		{
				typedef Tp type;
		};

		template <typename Tp>
		struct remove_cv
		{
				typedef typename remove_const<typename remove_volatile<Tp>::type>::type type;
		};

		template <typename Tp>
		struct remove_cvref
		{
				typedef typename remove_cv<typename remove_reference<Tp>::type>::type type;
		};

		template <typename>
		struct is_array : kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct is_array<Tp[]> : kerbal::type_traits::true_type
		{
		};

		template <typename Tp, size_t N>
		struct is_array<Tp[N]> : kerbal::type_traits::true_type
		{
		};

		template <typename>
		struct array_traits;

		template <typename Tp>
		struct array_traits<Tp[]>
		{
				typedef Tp value_type;
		};

		template <typename Tp, size_t N>
		struct array_traits<Tp[N]> : kerbal::type_traits::array_traits<Tp[]>
		{
				typedef Tp value_type;
#				if __cplusplus >= 201103L
					static constexpr size_t size = N;
#				else
					static const size_t size = N;
#				endif
		};

		///@private
		template <typename>
		struct __is_char_array_helper : kerbal::type_traits::false_type
		{
		};

		///@private
		template <>
		struct __is_char_array_helper<char[]> : kerbal::type_traits::true_type
		{
		};

		///@private
		template <size_t N>
		struct __is_char_array_helper<char[N]> : kerbal::type_traits::true_type
		{
		};

		///@private
		template <size_t N>
		struct __is_char_array_helper<const char[N]> : kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_char_array : __is_char_array_helper<typename kerbal::type_traits::remove_cvref<Type>::type>
		{
		};


		template <typename>
		struct is_floating_point : kerbal::type_traits::false_type
		{
		};

		template <>
		struct is_floating_point<float> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_floating_point<double> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_floating_point<long double> : kerbal::type_traits::true_type
		{
		};

		template <typename>
		struct is_integral : kerbal::type_traits::false_type
		{
		};

		template <>
		struct is_integral<bool> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<char> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<signed char> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<short> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<long long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<unsigned char> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<unsigned short> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<unsigned int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<unsigned long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_integral<unsigned long long> : kerbal::type_traits::true_type
		{
		};

		template<class T>
		struct is_arithmetic: kerbal::type_traits::conditional_boolean<is_integral<T>::value || is_floating_point<T>::value>::type
		{
		};

		template <typename >
		struct __is_pointer_helper: kerbal::type_traits::false_type
		{
		};

		template <typename T>
		struct __is_pointer_helper<T*> : kerbal::type_traits::true_type
		{
		};

		/// is_pointer
		template <typename T>
		struct is_pointer: kerbal::type_traits::__is_pointer_helper<typename kerbal::type_traits::remove_cv<T>::type>::type
		{
		};

#	if __cplusplus >= 201103L

		template <typename ...Args>
		struct __and_;

		template <>
		struct __and_<> : kerbal::type_traits::true_type
		{
		};

		template <typename T>
		struct __and_<T> : kerbal::type_traits::conditional_boolean<T::value>::type
		{
		};

		template <typename T, typename ...Args>
		struct __and_<T, Args...> : kerbal::type_traits::conditional<T::value, __and_ <Args...>, kerbal::type_traits::false_type>::type
		{
		};

		template <typename ...Args>
		struct __or_;

		template <>
		struct __or_<> : kerbal::type_traits::true_type
		{
		};

		template <typename T>
		struct __or_<T> : kerbal::type_traits::conditional_boolean<T::value>::type
		{
		};

		template <typename T, typename ...Args>
		struct __or_<T, Args...> : kerbal::type_traits::conditional<T::value, kerbal::type_traits::true_type, __or_ <Args...>>::type
		{
		};


		template <template <typename> typename Traits, typename ...Types>
		struct for_all_types : kerbal::type_traits::__and_<Traits<Types>...>
		{
		};

		template <template <typename> typename Traits, typename ...Types>
		struct has_types : kerbal::type_traits::__or_<Traits<Types>...>
		{
		};


#	endif

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_ */
