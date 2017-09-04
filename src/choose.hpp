/*
 * choose.hpp
 *
 *  Created on: 2017年7月8日
 *      Author: Peter
 *      Fuction: 提供对 choose 函数的支持
 */

#ifndef CHOOSE_HPP_
#define CHOOSE_HPP_

#include <iostream>
#include <cstdarg>
#include "except_C++0x.hpp"

#if __cplusplus >= 201103L //C++0x
# include <initializer_list>
#endif /* End C++0x */

namespace _choose
{
	namespace
	{
		using namespace std;
	}

	//声明
	template <class T> T choose(int index, T value0, ...) throw (invalid_argument);

#if __cplusplus >= 201103L //C++0x
	/*  choose 为 C++ 11 准备的新特性: 初始化列表风格的 choose 函数*/
	template <class T> T choose(int index, initializer_list<T> src) throw (invalid_argument, out_of_range);

	/*	choose_c11 为 C++ 11 准备的新特性: 可变参数模板风格的 choose 函数*/
	template <class T, class ...Args> T choose_c11(int index, T head, Args ... args) throw (invalid_argument, out_of_range);
#endif

	/*	实现 */
	template <class T>
	T choose(int index, T value0, ...) throw (invalid_argument)
	{
		if (index < 0) {
			throw invalid_argument("index<0");
		} else if (index == 0) {
			return value0;
		}

		va_list arg_ptr; //指向参数的指针
		va_start(arg_ptr, value0);

		for (int i = 1; i < index; i++) {
			va_arg(arg_ptr, T);
		}
		va_end(arg_ptr);
		return va_arg(arg_ptr, T);
	}

	/*
	 * 为何要为 [signed/unsigned]char , [unsigned]short , float 类型单独写 choose 函数, 请参考:
	 * http://www.cppblog.com/ownwaterloo/archive/2009/04/21/unacceptable_type_in_va_arg.html
	 */
	namespace
	{
		template <class T>
		T choose_int(int index, const T &value0, va_list &arg_ptr) throw (invalid_argument)
		{
			if (index < 0) {
				throw invalid_argument("index<0");
			} else if (index == 0) {
				return value0;
			}

			for (int i = 1; i < index; i++) {
				va_arg(arg_ptr, int);
			}
			return va_arg(arg_ptr, int);
		}

		template <class T>
		T choose_float(int index, const T &value0, va_list &arg_ptr) throw (invalid_argument)
		{
			if (index < 0) {
				throw invalid_argument("index<0");
			} else if (index == 0) {
				return value0;
			}

			for (int i = 1; i < index; i++) {
				va_arg(arg_ptr, double);
			}
			return va_arg(arg_ptr, double);
		}
	}

	char choose(int index, char value0, ...) throw (invalid_argument);
	unsigned char choose(int index, unsigned char value0, ...) throw (invalid_argument);
	signed char choose(int index, signed char value0, ...) throw (invalid_argument);

	short choose(int index, short value0, ...) throw (invalid_argument);
	unsigned short choose(int index, unsigned short value0, ...) throw (invalid_argument);

	float choose(int index, float value0, ...) throw (invalid_argument);

#if __cplusplus >= 201103L //C++0x
//choose 为 C++ 11 准备的新特性: 初始化列表风格的 choose 函数
	template <class T>
	T choose(int index, initializer_list<T> src) throw (invalid_argument, out_of_range)
	{
		if (index < 0) {
			throw invalid_argument("index<0");
		} else if (index >= src.size()) {
			throw out_of_range("index is out of range");
		}
		return *(src.begin() + index);
	}
#endif //C++0x

#if __cplusplus >= 201103L //C++0x
//choose_c11 为 C++ 11 准备的新特性: 可变参数模板风格的 choose 函数
	namespace //匿名命名空间内的内容对文件外不可见
	{
		int choose_unpack(int total)
		{ //递归终止函数
			std::cerr << "end" << std::endl;
			return 0;
		}

		template <class T, class ...Args>
		T choose_unpack(int total, T head, Args ... rest)
		{ //展开函数
			if (total == 0) {
				return head;
			} else {
				return (T) choose_unpack(total - 1, rest...);
			}
		}
	}/* Namespace */

	template <class T, class ...Args>
	T choose_c11(int index, T head, Args ... args) throw (invalid_argument, out_of_range)
	{
		if (index < 0) {
			throw invalid_argument("index<0");
		} else if (index > (int) sizeof...(Args)) {
			throw out_of_range("index is out of range");
		} else if (index == 0) {
			return head;
		}
		return choose_unpack(index - 1, args...);
	}
#endif

}/* Namespace _choose */

#endif /* End CHOOSE_HPP_ */
