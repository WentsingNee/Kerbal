/**
 * @file		system.cpp
 * @brief
 * @date		2018年3月1日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#include <kerbal/system/system.hpp>

#ifdef __linux
std::string get_user_name()
{
	return std::string(getpwuid(getuid())->pw_name);
}
#endif

#if (defined __WINDOWS_) || (defined _WIN32)
//#pragma comment(lib,"Advapi32.lib")
std::string get_user_name()
{
	char strBuffer[256] = { 0 };
	unsigned long dwSize = 256;
	GetUserName(strBuffer, &dwSize);

	return std::string(strBuffer);
}
#endif

#ifdef __linux
#	include<unistd.h>
int get_processors_number()
{
	unsigned int count = 1;
	count = sysconf(_SC_NPROCESSORS_CONF);
	return count;
}

#endif

#if (defined __WINDOWS_) || (defined _WIN32)
int get_processors_number()
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
}
#endif
