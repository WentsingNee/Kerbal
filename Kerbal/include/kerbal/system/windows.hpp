/*
 * windows.hpp
 *
 *  Created on: 2018年6月10日
 *      Author: peter
 */

#ifndef KERBAL_INCLUDE_KERBAL_SYSTEM_WINDOWS_HPP_
#define KERBAL_INCLUDE_KERBAL_SYSTEM_WINDOWS_HPP_

#if (defined __WINDOWS_) || (defined _WIN32)
#include <string>

inline std::string get_user_name()
{
	char strBuffer[256] = {0};
	unsigned long dwSize = 256;
	GetUserName(strBuffer, &dwSize);

	return std::string(strBuffer);
}

inline int get_processors_number()
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
}

#endif

#endif /* KERBAL_INCLUDE_KERBAL_SYSTEM_WINDOWS_HPP_ */
