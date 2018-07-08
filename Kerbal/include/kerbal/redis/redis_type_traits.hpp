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

#if __cplusplus < 201103L
		struct not_redis_key_type
		{
				enum
				{
					is_key_type = 0
				}
		};

		struct redis_key_type
		{
				enum
				{
					is_key_type = 1
				}
		};

		struct execute_disallowed_type: public not_redis_key_type
		{
				enum
				{
					is_execute_allowed_type = 0
				}
		};

		struct execute_allowed_type
		{
				enum
				{
					is_execute_allowed_type = 1
				}
		};

		template <bool is_key_type>
		struct execute_allowed_type;

		template <>
		struct execute_allowed_type<false>: public not_redis_key_type
		{
				enum
				{
					is_execute_allowed_type = 1
				}
		};

		template <>
		struct execute_allowed_type<true>: public redis_key_type
		{
				enum
				{
					is_execute_allowed_type = 1
				}
		};
#else
		struct not_redis_key_type
		{
				static constexpr bool is_key_type = false;
		};

		struct redis_key_type
		{
				static constexpr bool is_key_type = true;
		};

		struct execute_disallowed_type: public not_redis_key_type
		{
				static constexpr bool is_execute_allowed_type = false;
		};

		template <bool is_key_type>
		struct execute_allowed_type;

		template <>
		struct execute_allowed_type<false>: public not_redis_key_type
		{
				static constexpr bool is_execute_allowed_type = true;
		};

		template <>
		struct execute_allowed_type<true>: public redis_key_type
		{
				static constexpr bool is_execute_allowed_type = true;
		};
#endif


#	if __cplusplus < 201703L
		typedef const char * placeholder_type;
#	else
		typedef char placeholder_type[];
#	endif


		struct string_type_placeholder
		{
				static constexpr placeholder_type placeholder = "%s";
		};

		template <typename Type>
		struct redis_type_traits;

#if __cplusplus < 201103L
		template <typename Type>
		struct redis_type_traits : public execute_disallowed_type
		{
		};
#else
		template <typename Type>
		struct redis_type_traits : public std::conditional<std::is_enum<Type>::value,
															redis_type_traits<int>,
															execute_disallowed_type>::type
		{
		};
#endif

		template <typename Type>
		struct redis_type_traits<const Type> : public redis_type_traits<Type>
		{
		};

		template <typename Type>
		struct redis_type_traits<Type&> : public redis_type_traits<Type>
		{
		};

		template <typename Type>
		struct redis_type_traits<const Type&> : public redis_type_traits<Type>
		{
		};

		template <>
		struct redis_type_traits<RedisUnitedStringHelper> : public execute_allowed_type<true>, string_type_placeholder
		{
		};
		template <>
		struct redis_type_traits<std::string> : public execute_allowed_type<true>, string_type_placeholder
		{
		};
		template <>
		struct redis_type_traits<char*> : public execute_allowed_type<true>, string_type_placeholder
		{
		};
		template <>
		struct redis_type_traits<const char*> : public execute_allowed_type<true>, string_type_placeholder
		{
		};
		template <>
		struct redis_type_traits<char[]> : public execute_allowed_type<true>, string_type_placeholder
		{
		};
		template <size_t N>
		struct redis_type_traits<char[N]> : public execute_allowed_type<true>, string_type_placeholder
		{
		};

		template <>
		struct redis_type_traits<bool> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%d";
		};

		template <>
		struct redis_type_traits<char> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%s";
		};
		template <>
		struct redis_type_traits<signed char> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%s";
		};
		template <>
		struct redis_type_traits<unsigned char> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%s";
		};

		template <>
		struct redis_type_traits<int> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%d";
		};
		template <>
		struct redis_type_traits<unsigned int> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%u";
		};

		template <>
		struct redis_type_traits<long> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%ld";
		};
		template <>
		struct redis_type_traits<unsigned long> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%lu";
		};

		template <>
		struct redis_type_traits<long long> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%lld";
		};
		template <>
		struct redis_type_traits<unsigned long long> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%llu";
		};

		template <>
		struct redis_type_traits<float> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%f";
		};
		template <>
		struct redis_type_traits<double> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%f";
		};
		template <>
		struct redis_type_traits<long double> : public execute_allowed_type<false>
		{
				static constexpr placeholder_type placeholder = "%f";
		};


#	ifdef __cpp_concepts
		template <typename Type>
		concept bool Redis_execute_allowed_type = redis_type_traits<Type>::is_execute_allowed_type;
#	endif

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


	}
}

#endif /* INCLUDE_KERBAL_REDIS_REDIS_TYPE_TRAITS_HPP_ */
