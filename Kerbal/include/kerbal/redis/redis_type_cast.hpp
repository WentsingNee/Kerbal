/*
 * redis_cast.hpp
 *
 *  Created on: 2018年6月7日
 *      Author: peter
 */

#ifndef KERBAL_INCLUDE_KERBAL_REDIS_REDIS_TYPE_CAST_HPP_
#define KERBAL_INCLUDE_KERBAL_REDIS_REDIS_TYPE_CAST_HPP_


namespace kerbal
{
	namespace redis
	{
		template <typename CastToType>
		CastToType redisTypeCast(const char * src)
		{
			std::istringstream ss(src);
			CastToType res;
			ss >> res;
			return res;
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

		template <typename TypeFrom>
		std::string redisCastToString(const TypeFrom & src)
		{
			std::stringstream ss;
			ss << src;
			std::string res;
			ss >> res;
			return res;
		}

		inline const std::string & redisCastToString(const std::string & src)
		{
			return src;
		}

		inline std::string redisCastToString(const char * src)
		{
			return src;
		}


//		template <>
//		const std::string& redisTypeCast<std::string>(const std::string & src)
//		{
//			return src;
//		}
//
//		template <>
//		std::string& redisTypeCast<std::string>(std::string & src)
//		{
//			return src;
//		}

	}
}

#endif /* KERBAL_INCLUDE_KERBAL_REDIS_REDIS_TYPE_CAST_HPP_ */
