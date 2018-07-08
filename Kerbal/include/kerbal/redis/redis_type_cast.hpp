/*
 * redis_cast.hpp
 *
 *  Created on: 2018年6月7日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_REDIS_TYPE_CAST_HPP_
#define INCLUDE_KERBAL_REDIS_REDIS_TYPE_CAST_HPP_

#include <string>
#include <sstream>
#include <iterator>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif


namespace kerbal
{
	namespace redis
	{

#	if __cplusplus < 201103L

		template <typename CastToType>
		CastToType redisTypeCast(const char * src)
		{
			std::istringstream ss(src);
			return *std::istream_iterator<CastToType>(ss);
		}

#	else

		template <typename CastToType>
		typename std::enable_if<!std::is_const<CastToType>::value, CastToType>::type
		redisTypeCast(const char * src)
		{
			std::istringstream ss(src);
			return *std::istream_iterator<CastToType>(ss);
		}

		template <typename CastToType>
		typename std::enable_if<std::is_const<CastToType>::value, CastToType>::type
		redisTypeCast(const char * src)
		{
			return redisTypeCast<typename std::remove_const<CastToType>::type>(src);
		}

		template <>
		inline std::string redisTypeCast<std::string>(const char * src)
		{
			return src;
		}

		template <>
		inline int redisTypeCast<int>(const char * src)
		{
			return std::stoi(src);
		}
		template <>
		inline unsigned int redisTypeCast<unsigned int>(const char * src)
		{
			return std::stoul(src);
		}

		template <>
		inline long redisTypeCast<long>(const char * src)
		{
			return std::stol(src);
		}
		template <>
		inline unsigned long redisTypeCast<unsigned long>(const char * src)
		{
			return std::stoul(src);
		}

		template <>
		inline long long redisTypeCast<long long>(const char * src)
		{
			return std::stoll(src);
		}
		template <>
		inline unsigned long long redisTypeCast<unsigned long long>(const char * src)
		{
			return std::stoull(src);
		}

		template <>
		inline float redisTypeCast<float>(const char * src)
		{
			return std::stof(src);
		}

		template <>
		inline double redisTypeCast<double>(const char * src)
		{
			return std::stod(src);
		}

		template <>
		inline long double redisTypeCast<long double>(const char * src)
		{
			return std::stold(src);
		}

#	endif //C++11

		template <typename TypeFrom>
		std::string redisCastToString(const TypeFrom & src)
		{
			std::ostringstream ss;
			ss << src;
			return ss.str();
		}

		inline const std::string & redisCastToString(const std::string & src) noexcept
		{
			return src;
		}

		inline std::string redisCastToString(const char * src)
		{
			return src;
		}

	}
}

#endif /* INCLUDE_KERBAL_REDIS_REDIS_TYPE_CAST_HPP_ */
