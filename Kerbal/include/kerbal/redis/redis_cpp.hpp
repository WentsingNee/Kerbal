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

#include "context.hpp"
#include "redis_exception.hpp"
#include "auto_free_reply.hpp"
#include "redis_command.hpp"
#include "operation.hpp"

#include "redisDataStruct/variable.hpp"
#include "redisDataStruct/list.hpp"

namespace kerbal
{
	namespace redis
	{

	}
}





#endif /* SRC_REDIS_CPP_HPP_ */
