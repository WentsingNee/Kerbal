/*
 * type_traits.hpp
 *
 *  Created on: 2018年10月4日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_REDIS_V2_TYPE_TRAITS_HPP_

#include <string>
#include <iterator>
#include <sstream>
#include <kerbal/type_traits/type_traits.hpp>
#include <kerbal/utility/string_ref.hpp>

namespace kerbal
{

	namespace redis_v2
	{

		template <typename>
		struct __is_redis_key_type_helper : kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_redis_key_type_helper<std::string> : kerbal::type_traits::true_type
		{
		};

		template <size_t N>
		struct __is_redis_key_type_helper<char[N]> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_key_type_helper<char*> : kerbal::type_traits::true_type
		{
		};

		template <size_t N>
		struct __is_redis_key_type_helper<const char[N]> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_key_type_helper<const char*> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_key_type_helper<kerbal::utility::string_ref> : kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_redis_key_type : __is_redis_key_type_helper<typename kerbal::type_traits::remove_cvref<Type>::type>
		{
		};

		template <typename Type>
		struct __is_redis_execute_allow_type_helper : kerbal::type_traits::conditional_boolean<is_redis_key_type<Type>::value>
		{
		};

		template <>
		struct __is_redis_execute_allow_type_helper<int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_execute_allow_type_helper<unsigned int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_execute_allow_type_helper<long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_execute_allow_type_helper<unsigned long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_execute_allow_type_helper<long long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_execute_allow_type_helper<unsigned long long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_execute_allow_type_helper<float> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_execute_allow_type_helper<double> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_redis_execute_allow_type_helper<long double> : kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_redis_execute_allow_type : __is_redis_execute_allow_type_helper<typename kerbal::type_traits::remove_cvref<Type>::type>
		{
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
		struct __is_char_array : __is_char_array_helper<typename kerbal::type_traits::remove_cvref<Type>::type>
		{
		};

		template <typename Type>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<!kerbal::type_traits::is_reference<Type>::value &&
												!kerbal::type_traits::is_const<Type>::value &&
												!kerbal::type_traits::is_volatile<Type>::value &&
												!(__is_char_array<Type>::value), const char *>::type
		placeholder_traits();

		template <typename Type>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<(kerbal::type_traits::is_reference<Type>::value ||
												kerbal::type_traits::is_const<Type>::value ||
												kerbal::type_traits::is_volatile<Type>::value) &&
												!__is_char_array<Type>::value, const char *>::type
		placeholder_traits()
		{
			return placeholder_traits<typename kerbal::type_traits::remove_cv<typename kerbal::type_traits::remove_reference<Type>::type>::type>();
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

		template <typename Type>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<__is_char_array<Type>::value, const char *>::type
		placeholder_traits()
		{
			return placeholder_traits<const char*>();
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

		template <typename ... Args>
		struct is_redis_execute_list :
				kerbal::type_traits::for_all_types<is_redis_execute_allow_type, Args...>
		{
		};

		template <typename ... Args>
		struct is_redis_key_list :
				kerbal::type_traits::for_all_types<is_redis_key_type, Args...>
		{
		};

		template <typename Type0, typename ... Args>
		struct is_none_empty_redis_execute_list :
				kerbal::type_traits::for_all_types<is_redis_execute_allow_type, Type0, Args...>
		{
		};

		template <typename Type0, typename ... Args>
		struct is_none_empty_redis_key_list :
				kerbal::type_traits::for_all_types<is_redis_key_type, Type0, Args...>
		{
		};

#	endif

        template <typename CastToType>
        typename kerbal::type_traits::enable_if<!kerbal::type_traits::is_const<CastToType>::value, CastToType>::type
        redis_type_cast(const char * src)
        {
            std::istringstream ss(src);
            return *std::istream_iterator<CastToType>(ss);
        }

        template <typename CastToType>
        typename kerbal::type_traits::enable_if<kerbal::type_traits::is_const<CastToType>::value, CastToType>::type
        redis_type_cast(const char * src)
        {
            return redis_type_cast<typename kerbal::type_traits::remove_const<CastToType>::type>(src);
        }

        template <>
		inline std::string redis_type_cast<std::string>(const char * src)
		{
			return src;
		}

		template <>
		inline int redis_type_cast<int>(const char * src)
		{
			return std::stoi(src);
		}
		template <>
		inline unsigned int redis_type_cast<unsigned int>(const char * src)
		{
			return std::stoul(src);
		}

		template <>
		inline long redis_type_cast<long>(const char * src)
		{
			return std::stol(src);
		}
		template <>
		inline unsigned long redis_type_cast<unsigned long>(const char * src)
		{
			return std::stoul(src);
		}

		template <>
		inline long long redis_type_cast<long long>(const char * src)
		{
			return std::stoll(src);
		}
		template <>
		inline unsigned long long redis_type_cast<unsigned long long>(const char * src)
		{
			return std::stoull(src);
		}

		template <>
		inline float redis_type_cast<float>(const char * src)
		{
			return std::stof(src);
		}

		template <>
		inline double redis_type_cast<double>(const char * src)
		{
			return std::stod(src);
		}

		template <>
		inline long double redis_type_cast<long double>(const char * src)
		{
			return std::stold(src);
		}


		template <typename TypeFrom>
		std::string redis_cast_to_string(const TypeFrom & src)
		{
			std::ostringstream ss;
			ss << src;
			return ss.str();
		}

		inline const std::string & redis_cast_to_string(const std::string & src) noexcept
		{
			return src;
		}

		inline std::string redis_cast_to_string(const char * src)
		{
			return src;
		}


	} /* namespace redis_v2 */

} /* namespace kerbal */

#endif /* INCLUDE_KERBAL_REDIS_V2_TYPE_TRAITS_HPP_ */
