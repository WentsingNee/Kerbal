#ifndef EXE_SERVE_HPP_
#define EXE_SERVE_HPP_

//#pragma message(__DATE__ "  " __TIME__"  正在编译"__FILE__)

#include <iostream>
#include <typeinfo>
#include <cstring>
#include <string>

#include "advanced_math_private.h"

#ifdef __linux
# include <time.h>
# include <unistd.h>
# include <pwd.h>
inline unsigned long GetTickCount()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
#endif //__linux

#if (defined __WINDOWS_) || (defined _WIN32)
# include <windows.h>
#endif // win

extern unsigned long start_time;
extern bool debug;

void program_start(bool is_debug);
unsigned long show_time_cost();
void program_will_end();

enum Type
{
	ty_short,
	ty_unshort,
	ty_int,
	ty_unint,
	ty_long,
	ty_unlong,
	ty_float,
	ty_double,
	ty_longdouble,
	ty_char,
	ty_bool,
	ty_else
};

template <class T> Type get_type(const T &a);
template <class T> bool print_type_infomation(const T &a);
template <class T> std::string bit_of(const T &a);
template <class T> std::string ocx_of(const T &a);
template <class T> inline std::string get_typename(const T &a);
inline std::string get_user_name();
inline int get_processors_number();

template <class T>
Type get_type(const T &a)
{
	Type typerecord;
	if (typeid(a).name() == typeid(short).name()) {
		typerecord = ty_short;
	} else if (typeid(a).name() == typeid(unsigned short).name()) {
		typerecord = ty_unshort;
	} else if (typeid(a).name() == typeid(int).name()) {
		typerecord = ty_int;
	} else if (typeid(a).name() == typeid(unsigned int).name()) {
		typerecord = ty_unint;
	} else if (typeid(a).name() == typeid(long).name()) {
		typerecord = ty_long;
	} else if (typeid(a).name() == typeid(unsigned long).name()) {
		typerecord = ty_unlong;
	} else if (typeid(a).name() == typeid(float).name()) {
		typerecord = ty_float;
	} else if (typeid(a).name() == typeid(double).name()) {
		typerecord = ty_double;
	} else if (typeid(a).name() == typeid(long double).name()) {
		typerecord = ty_longdouble;
	} else if (typeid(a).name() == typeid(char).name()) {
		typerecord = ty_char;
	} else if (typeid(a).name() == typeid(bool).name()) {
		typerecord = ty_bool;
	} else {
		typerecord = ty_else;
	}
	return typerecord;
}

template <class T>
bool print_type_infomation(const T &a)
{
	using namespace std;
	Type typerecord = get_type(a);

	switch (typerecord) {
		case ty_short: {
			cout << "size of short: " << sizeof(T) << endl;
			cout << "smallest range of short: " << (1 << (8 * sizeof(T) - 1)) << endl;
			cout << "biggest range of short: " << (1 << (8 * sizeof(T) - 1)) - 1 << endl;
			break;
		}
		case ty_unshort: {
			cout << "size of unsigned short: " << sizeof(T) << endl;
			cout << "smallest range of unsigned short: " << 0 << endl;
			cout << "biggest range of unsigned short: " << ((T) (-1)) << endl;
			break;
		}
		case ty_int: {
			cout << "size of int: " << sizeof(T) << endl;
			cout << "smallest range of int: " << (1 << (8 * sizeof(T) - 1)) << endl;
			cout << "biggest range of int: " << (1 << (8 * sizeof(T) - 1)) - 1 << endl;
			break;
		}
		case ty_unint: {
			cout << "size of unsigned int: " << sizeof(T) << endl;
			cout << "smallest range of unsigned int: " << 0 << endl;
			cout << "biggest range of unsigned int: " << ((T) (-1)) << endl;
			break;
		}
		case ty_long: {
			cout << "size of long: " << sizeof(T) << endl;
			cout << "smallest range of long: " << (1 << (8 * sizeof(T) - 1)) << endl;
			cout << "biggest range of long: " << (1 << (8 * sizeof(T) - 1)) - 1 << endl;
			break;
		}
		case ty_unlong: {
			cout << "size of unsigned long: " << sizeof(T) << endl;
			cout << "smallest range of unsigned long: " << 0 << endl;
			cout << "biggest range of unsigned long:" << ((T) (-1)) << endl;
			break;
		}
		case ty_float: {
			cout << "size of float: " << sizeof(T) << endl;
			break;
		}
		case ty_double: {
			cout << "size of double: " << sizeof(T) << endl;
			break;
		}
		case ty_char: {
			cout << "size of char: " << sizeof(T) << endl;
			break;
		}
		case ty_bool: {
			cout << "size of bool: " << sizeof(T) << endl;
			break;
		}
		default: {
			cout << "自定义类型" << " size:" << sizeof(T) << endl;
			return false;
		}
	}
	return true;
}

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
	return bit_of(&a[0]);
}

std::string ocx_of(const char * const a);
inline std::string ocx_of(const std::string &a)
{
	return ocx_of(&a[0]);
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

template <class T>
inline std::string get_typename(const T &a)
{
	return std::string(typeid(a).name());
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
