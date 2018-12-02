/*
 * query.hpp
 *
 *  Created on: 2018年10月4日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_QUERY_HPP_
#define INCLUDE_KERBAL_REDIS_V2_QUERY_HPP_

#include <sstream>

#include <kerbal/redis_v2/connection.hpp>
#include <kerbal/redis_v2/reply.hpp>
#include <kerbal/redis_v2/type_traits.hpp>
#include <kerbal/utility/string_ref.hpp>
#include <kerbal/compatibility/va_arg_compatible_cast.hpp>

namespace kerbal
{

	namespace redis_v2
	{

		class query : public std::ostringstream
		{
			private:
				typedef std::ostringstream supper_t;

			public:
				query() :
						supper_t()
				{
				}

				query(const char * s) :
						supper_t(s, std::ostringstream::out | std::ostringstream::ate)
				{
				}

				query(const std::string & s) :
						supper_t(s, std::ostringstream::out | std::ostringstream::ate)
				{
				}


#			if __cplusplus >= 201103L
				template <typename ...Args>
				typename kerbal::type_traits::enable_if<is_redis_execute_list<Args...>::value, reply>::type
				execute(const connection & conn, Args && ...args) const
				{
					return conn.execute(this->str(), std::forward<Args>(args)...);
				}
#			endif

		};

	} /* namespace redis_v2 */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_REDIS_V2_QUERY_HPP_ */
