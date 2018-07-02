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
#include <kerbal/redis/united_string_helper.hpp>

namespace kerbal
{
	namespace redis
	{
		struct true_type
		{
				static constexpr bool value = true;
		};

		struct false_type
		{
				static constexpr bool value = false;
		};

		template <typename Type>
		struct is_redis_excute_allow_type;

		template <typename Type>
		struct is_redis_excute_allow_type: public false_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<std::string> : public true_type
		{
		};
		template <>
		struct is_redis_excute_allow_type<RedisUnitedStringHelper> : public true_type
		{
		};

		template <size_t N>
		struct is_redis_excute_allow_type<char[N]> : public true_type
		{
		};
		template <>
		struct is_redis_excute_allow_type<char*> : public true_type
		{
		};
		template <size_t N>
		struct is_redis_excute_allow_type<const char[N]> : public true_type
		{
		};
		template <>
		struct is_redis_excute_allow_type<const char*> : public true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<int> : public true_type
		{
		};
		template <>
		struct is_redis_excute_allow_type<unsigned int> : public true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<long> : public true_type
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<unsigned long> : public true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<long long> : public true_type
		{
		};
		template <>
		struct is_redis_excute_allow_type<unsigned long long> : public true_type
		{
		};

		template <>
		struct is_redis_excute_allow_type<float> : public true_type
		{
		};
		template <>
		struct is_redis_excute_allow_type<double> : public true_type
		{
		};
		template <>
		struct is_redis_excute_allow_type<long double> : public true_type
		{
		};

		template<typename>
		struct is_redis_key_type;

		template <typename Type>
		struct is_redis_key_type: public false_type
		{
		};

		template <>
		struct is_redis_key_type<std::string> : public true_type
		{
		};

		template <size_t N>
		struct is_redis_key_type<char[N]> : public true_type
		{
		};
		template <>
		struct is_redis_key_type<char*> : public true_type
		{
		};
		template <size_t N>
		struct is_redis_key_type<const char[N]> : public true_type
		{
		};
		template <>
		struct is_redis_key_type<const char*> : public true_type
		{
		};
		template <>
		struct is_redis_key_type<RedisUnitedStringHelper> : public true_type
		{
		};


		template <typename >
		struct placeholder_traits;

		template <>
		struct placeholder_traits<std::string>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%s";
#	else
				static constexpr char value[] = "%s";
#	endif
		};

		template <>
		struct placeholder_traits<const char *>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%s";
#	else
				static constexpr char value[] = "%s";
#	endif
		};

		template <size_t N>
		struct placeholder_traits<char[N]>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%s";
#	else
				static constexpr char value[] = "%s";
#	endif
		};

		template <size_t N>
		struct placeholder_traits<const char[N]>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%s";
#	else
				static constexpr char value[] = "%s";
#	endif
		};

		template <>
		struct placeholder_traits<int>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%d";
#	else
				static constexpr char value[] = "%d";
#	endif
		};
		template <>
		struct placeholder_traits<unsigned int>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%u";
#	else
				static constexpr char value[] = "%u";
#	endif
		};

		template <>
		struct placeholder_traits<long>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%ld";
#	else
				static constexpr char value[] = "%ld";
#	endif
		};
		template <>
		struct placeholder_traits<unsigned long>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%lu";
#	else
				static constexpr char value[] = "%lu";
#	endif
		};

		template <>
		struct placeholder_traits<long long>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%lld";
#	else
				static constexpr char value[] = "%lld";
#	endif
		};
		template <>
		struct placeholder_traits<unsigned long long>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%llu";
#	else
				static constexpr char value[] = "%llu";
#	endif
		};

		template <>
		struct placeholder_traits<float>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%f";
#	else
				static constexpr char value[] = "%f";
#	endif
		};
		template <>
		struct placeholder_traits<double>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%f";
#	else
				static constexpr char value[] = "%f";
#	endif
		};
		template <>
		struct placeholder_traits<long double>
		{
#	if __cplusplus < 201703L
				static constexpr const char * value = "%f";
#	else
				static constexpr char value[] = "%f";
#	endif
		};

		template<typename Type>
		struct CheckIsIntegerType : public
			std::conditional<
				std::is_integral<Type>::value && !std::is_same<Type, bool>::value ,
				true_type,
				false_type>::type
		{
		};

		template<typename Type>
		struct CheckIsRealType : public
			std::conditional<
				CheckIsIntegerType<Type>::value || std::is_floating_point<Type>::value,
				true_type,
				false_type>::type
		{
		};
	}
}

#endif /* INCLUDE_KERBAL_REDIS_REDIS_TYPE_TRAITS_HPP_ */
