#ifndef EXE_SERVE_HPP_
#define EXE_SERVE_HPP_

//#pragma message(__DATE__ "  " __TIME__"  正在编译"__FILE__)

#include <iostream>
#include <typeinfo>
#include <cstring>
#include <windows.h>
#include <string>

#include "advanced_math_private.h"

using namespace std;

void program_start(bool is_debug);
unsigned long show_time_cost();
bool program_will_end();

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
template <class T> void print_bit(const T &a);
template <class T> void print_16(const T &a);
template <class T> string get_typename(const T &a);
string get_user_name();

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
void print_bit(const T &a)
{
	char *p = (char *) (&a) + sizeof(T) / sizeof(char) - sizeof(char);
	for (int i = sizeof(T) / sizeof(char); i >= 1; i--) {
		for (int j = 8 * sizeof(char) - 1; j >= 0; j--) {
			cout << ((*p >> j) & 1);
		}
		cout << " ";
		p--;
	}
	cout << endl;
}

void print_string_bit(char * const a);
void print_string_16(char * const a);
void print_string_bit(string a);
void print_string_16(string a);

template <class T>
void print_16(const T &a)
{
	unsigned char tmp;
	char *p = (char *) (&a) + sizeof(T) / sizeof(char) - sizeof(char);
	for (int i = sizeof(T) / sizeof(char); i >= 1; i--) {
		tmp = *p;
		tmp >>= 4;
		if (tmp > 9) {
			//cout << char('A' + tmp - 10);
			cout << char(tmp + 55);
		} else {
			cout << char(tmp + '0');
		}

		tmp = *p;
		tmp <<= 4;
		tmp >>= 4;
		if (tmp > 9) {
			cout << char(tmp + 55);
		} else {
			cout << char(tmp + '0');
		}
		cout << " ";
		p--;
	}
	cout << endl;
}

template <class T>
string get_typename(const T &a)
{
	return string(typeid(a).name());
}

class Object
{
	protected:
		virtual void Object_init() = 0;
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

};

#endif	/* End EXE_SERVE_HPP_ */
