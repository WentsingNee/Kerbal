#ifndef EXE_SERVE_HPP_
#define EXE_SERVE_HPP_

#include <string>
#include "tick_count.h"

#include "../advanced_math_private.h"

extern unsigned long start_time;
extern bool debug;

void program_start(bool is_debug);
unsigned long show_time_cost();
void program_will_end();

template <class T> std::string bit_of(const T &a);
template <class T> std::string ocx_of(const T &a);
inline std::string get_user_name();
inline int get_processors_number();

template <class T>
std::string bit_of(const T &a)
{
	std::string result = "";
	char *p = (char *) (&a) + sizeof(T) / sizeof(char);
	while (p != (char *) (&a)) {
		--p;
		for (int j = 8 * sizeof(char) - 1; j >= 0; j--) {
			if ((*p >> j) & 1) {
				result += '1';
			} else {
				result += '0';
			}
		}
		result += " ";
	}
	return result;
}

std::string bit_of(const char * const a);
inline std::string bit_of(const std::string &a)
{
	return bit_of(a.c_str());
}

std::string ocx_of(const char * const a);
inline std::string ocx_of(const std::string &a)
{
	return ocx_of(a.c_str());
}

inline void get_16(char *buffer, const char src)
{
	unsigned char tmp = src;
	tmp >>= 4;
	buffer[0] = char(tmp > 9 ? tmp + 55 : tmp + '0'); //55 means 'A'-10

	tmp = src;
	tmp <<= 4;
	tmp >>= 4;
	buffer[1] = char(tmp > 9 ? tmp + 55 : tmp + '0');
	buffer[2] = '\0';
}

template <class T>
std::string ocx_of(const T &a)
{
	char buffer[10];
	std::string result = "";
	char * p = (char *) (&a) + sizeof(T) / sizeof(char);
	while (p != (char *) (&a)) {
		--p;
		get_16(buffer, *p);
		(result += buffer) += " ";
	}
	return result;
}

#ifdef __linux
inline std::string get_user_name()
{
	return std::string(getpwuid(getuid())->pw_name);
}
#endif

#if (defined __WINDOWS_) || (defined _WIN32)
//#pragma comment(lib,"Advapi32.lib")
inline std::string get_user_name()
{
	char strBuffer[256] = { 0 };
	unsigned long dwSize = 256;
	GetUserName(strBuffer, &dwSize);

	return std::string(strBuffer);
}
#endif

#ifdef __linux
#include<unistd.h>
inline int get_processors_number()
{
	//TODO
	int num=get_nprocs_conf();
	return num;
}
#endif

#if (defined __WINDOWS_) || (defined _WIN32)
inline int get_processors_number()
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
}
#endif

class Object
{
	public:
		virtual ~Object()
		{
		}

		bool is_const()
		{
			return false;
		}

		bool is_const() const
		{
			return true;
		}

		virtual bool eaual(const Object &with) = 0;
};

#endif	/* End EXE_SERVE_HPP_ */
