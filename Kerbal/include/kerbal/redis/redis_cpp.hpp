/*
 * redis_cpp.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef SRC_REDIS_CPP_HPP_
#define SRC_REDIS_CPP_HPP_

#include <iostream>
#include <exception>
#include <memory>
#include <sstream>


#include <boost/format.hpp>
#include <boost/noncopyable.hpp>

#include <hiredis/hiredis.h>
#include <kerbal/redis/redis_type_cast.hpp>
#include <kerbal/redis/context.hpp>
#include <kerbal/redis/redis_exception.hpp>
#include <kerbal/redis/auto_free_reply.hpp>
#include <kerbal/redis/redis_command.hpp>
#include <kerbal/redis/operation.hpp>

#include <kerbal/redis/redisDataStruct/reference_base.hpp>
#include <kerbal/redis/redisDataStruct/variable.hpp>
#include <kerbal/redis/redisDataStruct/list.hpp>

namespace kerbal
{
	namespace redis
	{

	}
}

#endif /* SRC_REDIS_CPP_HPP_ */
