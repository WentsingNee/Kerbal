/*
 * redis_type_traits.hpp
 *
 *  Created on: 2018年6月9日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_REDIS_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_REDIS_REDIS_TYPE_TRAITS_HPP_

#include <string>
#include <type_traits>
#include <kerbal/type_traits/type_traits.hpp>
#include <kerbal/redis/united_string_helper.hpp>

#include <chrono>

namespace kerbal
{
	namespace redis
	{

		template <typename Type>
		struct is_redis_key_type : kerbal::type_traits::false_type
		{
			using namespace std::chrono;
			auto s = 5min;
		};

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


		template <typename Type>
		struct is_redis_excute_allow_type : kerbal::type_traits::conditional<is_redis_key_type<Type>::value,
											kerbal::type_traits::true_type,
											kerbal::type_traits::false_type>::type
		{
		};

		template <>
		struct is_redis_excute_allow_type<int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<unsigned int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<unsigned long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<long long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<unsigned long long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<float> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<double> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<long double> : kerbal::type_traits::true_type
		{
		};


		template <typename >
		struct placeholder_traits;

		template <>
		struct placeholder_traits<std::string>
		{
				static constexpr char value[] = "%s";
		};

		template <>
		struct placeholder_traits<const char *>
		{
				static constexpr char value[] = "%s";
		};

		template <size_t N>
		struct placeholder_traits<char[N]>
		{
				static constexpr char value[] = "%s";
		};

		template <size_t N>
		struct placeholder_traits<const char[N]>
		{
				static constexpr char value[] = "%s";
		};

		template <>
		struct placeholder_traits<int>
		{
				static constexpr char value[] = "%d";
		};
		template <>
		struct placeholder_traits<unsigned int>
		{
				static constexpr char value[] = "%u";
		};
		template <>
		struct placeholder_traits<long>
		{
				static constexpr char value[] = "%ld";
		};
		template <>
		struct placeholder_traits<unsigned long>
		{
				static constexpr char value[] = "%lu";
		};
		template <>
		struct placeholder_traits<long long>
		{
				static constexpr char value[] = "%lld";
		};
		template <>
		struct placeholder_traits<unsigned long long>
		{
				static constexpr char value[] = "%llu";
		};
		template <>
		struct placeholder_traits<float>
		{
				static constexpr char value[] = "%f";
		};
		template <>
		struct placeholder_traits<double>
		{
				static constexpr char value[] = "%f";
		};
		template <>
		struct placeholder_traits<long double>
		{
				static constexpr char value[] = "%f";
		};

		template<typename Type>
		struct CheckIsIntegerType : public
			std::conditional<
				std::is_integral<Type>::value && !std::is_same<Type, bool>::value ,
				std::true_type,
				std::false_type>::type
		{
		};

		template<typename Type>
		struct CheckIsRealType : public
			std::conditional<
				CheckIsIntegerType<Type>::value || std::is_floating_point<Type>::value,
				std::true_type,
				std::false_type>::type
		{
		};

#	ifdef __cpp_concepts
		template <typename Type>
		concept bool Redis_execute_allowed_type = redis_type_traits<Type>::is_execute_allowed_type;
#	endif

	}
}

#endif /* INCLUDE_KERBAL_REDIS_REDIS_TYPE_TRAITS_HPP_ */
