/*
 * choose.cpp
 *
 *  Created on: 2017Äê7ÔÂ8ÈÕ
 *      Author: Peter
 *      Fuction:
 */

#include <iostream>
#include "choose.hpp"

using namespace std;

char choose(int index, char value0, ...) throw (invalid_argument)
{
	va_list arg_ptr;
	va_start(arg_ptr, value0);
	char result = choose_int(index, value0, arg_ptr);
	va_end(arg_ptr);
	return result;
}

unsigned char choose(int index, unsigned char value0, ...) throw (invalid_argument)
{
	va_list arg_ptr;
	va_start(arg_ptr, value0);
	unsigned char result = choose_int(index, value0, arg_ptr);
	va_end(arg_ptr);
	return result;
}

signed char choose(int index, signed char value0, ...) throw (invalid_argument)
{
	va_list arg_ptr;
	va_start(arg_ptr, value0);
	signed char result = choose_int(index, value0, arg_ptr);
	va_end(arg_ptr);
	return result;
}

short choose(int index, short value0, ...) throw (invalid_argument)
{
	va_list arg_ptr;
	va_start(arg_ptr, value0);
	short result = choose_int(index, value0, arg_ptr);
	va_end(arg_ptr);
	return result;
}

unsigned short choose(int index, unsigned short value0, ...) throw (invalid_argument)
{
	va_list arg_ptr;
	va_start(arg_ptr, value0);
	unsigned short result = choose_int(index, value0, arg_ptr);
	va_end(arg_ptr);
	return result;
}

float choose(int index, float value0, ...) throw (invalid_argument)
{
	va_list arg_ptr;
	va_start(arg_ptr, value0);
	float result = choose_float(index, value0, arg_ptr);
	va_end(arg_ptr);
	return result;
}

