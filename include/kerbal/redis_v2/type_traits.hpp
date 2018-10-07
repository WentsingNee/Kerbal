/*
 * type_traits.hpp
 *
 *  Created on: 2018年10月4日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_REDIS_V2_TYPE_TRAITS_HPP_

#include <string>
#include <kerbal/type_traits/type_traits.hpp>

namespace kerbal
{

	namespace redis_v2
	{

		template <typename>
		struct is_redis_key_type : kerbal::type_traits::false_type
		{
		};

		template <typename Type>
		struct is_redis_key_type<Type&> : is_redis_key_type<Type>
		{
		};

#	if __cplusplus >= 201103L

		template <typename Type>
		struct is_redis_key_type<Type&&> : is_redis_key_type<Type>
		{
		};

#	endif

		template <>
		struct is_redis_key_type<std::string> : kerbal::type_traits::true_type
		{
		};

		template <size_t N>
		struct is_redis_key_type<char[N]> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_key_type<char*> : kerbal::type_traits::true_type
		{
		};

		template <size_t N>
		struct is_redis_key_type<const char[N]> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_key_type<const char*> : kerbal::type_traits::true_type
		{
		};

//		template <>
//		struct is_redis_key_type<kerbal::redis::RedisUnitedStringHelper> : kerbal::type_traits::true_type
//		{
//		};


		template <typename Type>
		struct is_redis_execute_allow_type : kerbal::type_traits::conditional<is_redis_key_type<Type>::value,
											kerbal::type_traits::true_type,
											kerbal::type_traits::false_type>::type
		{
		};

		template <typename Type>
		struct is_redis_execute_allow_type<Type&> : is_redis_execute_allow_type<Type>
		{
		};

#	if __cplusplus >= 201103L

		template <typename Type>
		struct is_redis_execute_allow_type<Type&&> : is_redis_execute_allow_type<Type>
		{
		};

#	endif

		template <>
		struct is_redis_execute_allow_type<int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_execute_allow_type<unsigned int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_execute_allow_type<long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_execute_allow_type<unsigned long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_execute_allow_type<long long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_execute_allow_type<unsigned long long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_execute_allow_type<float> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_execute_allow_type<double> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_execute_allow_type<long double> : kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<!kerbal::type_traits::is_reference<Type>::value &&
												!kerbal::type_traits::is_const<Type>::value &&
												!kerbal::type_traits::is_volatile<Type>::value &&
												!kerbal::type_traits::is_char_array<Type>::value, const char *>::type
		placeholder_traits();

		template <typename Type>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<(kerbal::type_traits::is_reference<Type>::value ||
												kerbal::type_traits::is_const<Type>::value ||
												kerbal::type_traits::is_volatile<Type>::value) &&
												!kerbal::type_traits::is_char_array<Type>::value, const char *>::type
		placeholder_traits()
		{
			return placeholder_traits<typename kerbal::type_traits::remove_cv<typename kerbal::type_traits::remove_reference<Type>::type>::type>();
		}

		template <typename Type>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<kerbal::type_traits::is_char_array<Type>::value, const char *>::type
		placeholder_traits()
		{
			return placeholder_traits<const char*>();
		}

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<std::string>()
		{
			return "%s";
		}

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<const char *>()
		{
			return "%s";
		}

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<int>()
		{
			return "%d";
		};
		
		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<unsigned int>()
		{
			return "%u";
		};

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<long>()
		{
			return "%ld";
		};

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<unsigned long>()
		{
			return "%lu";
		};

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<long long>()
		{
			return "%lld";
		};

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<unsigned long long>()
		{
			return "%llu";
		};

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<float>()
		{
			return "%f";
		};

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<double>()
		{
			return "%f";
		};

		template <>
		KERBAL_CONSTEXPR const char * placeholder_traits<long double>()
		{
			return "%f";
		};

#	if __cplusplus < 201103L

#	else

		template <typename Type0, typename ... Args>
		struct is_redis_execute_list :
				kerbal::type_traits::conditional<
						is_redis_execute_allow_type<Type0>::value && is_redis_execute_list<Args...>::value,
						kerbal::type_traits::true_type,
						kerbal::type_traits::false_type
				>::type
		{
		};

		template <typename Type0>
		struct is_redis_execute_list<Type0>: is_redis_execute_allow_type<Type0>
		{
		};

#	endif


	} /* namespace redis_v2 */

} /* namespace kerbal */

#endif /* INCLUDE_KERBAL_REDIS_V2_TYPE_TRAITS_HPP_ */
