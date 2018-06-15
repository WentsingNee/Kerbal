/*
 * redis_type_traits.hpp
 *
 *  Created on: 2018年6月9日
 *      Author: peter
 */

#ifndef KERBAL_INCLUDE_KERBAL_REDIS_REDIS_TYPE_TRAITS_HPP_
#define KERBAL_INCLUDE_KERBAL_REDIS_REDIS_TYPE_TRAITS_HPP_

#include <string>
#include <type_traits>

namespace kerbal
{
	namespace redis
	{
		template <typename Type>
		struct is_redis_excute_allow_type;

		template <typename Type>
		struct is_redis_excute_allow_type
		{
				static constexpr bool value = false;
		};

		template <>
		struct is_redis_excute_allow_type<std::string>
		{
				static constexpr bool value = true;
		};

		template <size_t N>
		struct is_redis_excute_allow_type<char[N]>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<char*>
		{
				static constexpr bool value = true;
		};
		template <size_t N>
		struct is_redis_excute_allow_type<const char[N]>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<const char*>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<int>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<unsigned int>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<long>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<unsigned long>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<long long>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<unsigned long long>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<float>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<double>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_excute_allow_type<long double>
		{
				static constexpr bool value = true;
		};

		template<typename>
		struct is_redis_key_type;

		template <typename Type>
		struct is_redis_key_type
		{
				static constexpr bool value = false;
		};

		template <>
		struct is_redis_key_type<std::string>
		{
				static constexpr bool value = true;
		};

		template <size_t N>
		struct is_redis_key_type<char[N]>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_key_type<char*>
		{
				static constexpr bool value = true;
		};
		template <size_t N>
		struct is_redis_key_type<const char[N]>
		{
				static constexpr bool value = true;
		};
		template <>
		struct is_redis_key_type<const char*>
		{
				static constexpr bool value = true;
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
				std::__and_<std::is_integral<Type>, std::__not_ <std::is_same<Type, bool> > >::value,
				std::true_type,
				std::false_type>::type
		{
		};

		template<typename Type>
		struct CheckIsRealType : public
			std::conditional<
				std::__or_<CheckIsIntegerType<Type>, std::is_floating_point<Type> >::value,
				std::true_type,
				std::false_type>::type
		{
		};
	}
}

#endif /* KERBAL_INCLUDE_KERBAL_REDIS_REDIS_TYPE_TRAITS_HPP_ */
