/*
 * linux.hpp
 *
 *  Created on: 2018年6月10日
 *      Author: peter
 */

#ifndef KERBAL_INCLUDE_KERBAL_SYSTEM_LINUX_HPP_
#define KERBAL_INCLUDE_KERBAL_SYSTEM_LINUX_HPP_

#ifdef __linux
#include <string>

#include <pwd.h>
#include<unistd.h>

inline std::string get_user_name()
{
	return std::string(getpwuid(getuid())->pw_name);
}

inline int get_processors_number()
{
	unsigned int count = 1;
	count = sysconf(_SC_NPROCESSORS_CONF);
	return count;
}

#endif

#endif /* KERBAL_INCLUDE_KERBAL_SYSTEM_LINUX_HPP_ */
