/*
 * choose.hpp
 *
 *  Created on: 2017年7月8日
 *      Author: Peter
 *      Fuction: 提供对 choose 函数的支持
 */

#ifndef CHOOSE_HPP_
#define CHOOSE_HPP_

#include <stdarg.h>
#include <kerbal/compatibility/except_C++0x.hpp>

#if __cplusplus >= 201103L //c++0x
# include <initializer_list>
#endif //c++0x

namespace kerbal
{
	namespace choose
	{
		/* 声明 */

		/*
		 * choose: 可变参数表风格的 choose 函数
		 */
		template <class T>
		T choose(size_t index, const T& value0, ...);

#if __cplusplus >= 201103L //C++0x
		/*
		 * choose 为 C++ 11 准备的新特性: 初始化列表风格的 choose 函数
		 */
		template <class T>
		T choose(size_t index, std::initializer_list<T> src) throw (std::out_of_range);

		/*
		 * choose_c11 为 C++ 11 准备的新特性: 可变参数模板风格的 choose 函数
		 */
		template <class T, class ...Args>
		T choose_c11(size_t index, const T & head, Args && ... args) throw (std::out_of_range);
#endif

		/* 实现 */

		/*
		 * choose: 可变参数表风格的 choose 函数的实现
		 */
		template <class T>
		T choose(size_t index, const T& value0, ...)
		{
			if (index == 0) {
				return value0;
			}

			va_list arg_ptr; //指向参数的指针
			va_start(arg_ptr, value0);

			for (size_t i = 1; i < index; ++i) {
				va_arg(arg_ptr, T);
			}
			va_end(arg_ptr);
			return va_arg(arg_ptr, T);
		}

		/*
		 * 为何要为 [signed/unsigned]char , [unsigned]short , float 类型单独写 choose 函数, 请参考:
		 * http://www.cppblog.com/ownwaterloo/archive/2009/04/21/unacceptable_type_in_va_arg.html
		 */

		char choose(size_t index, char value0, ...);
		unsigned char choose(size_t index, unsigned char value0, ...);
		signed char choose(size_t index, signed char value0, ...);

		short choose(size_t index, short value0, ...);
		unsigned short choose(size_t index, unsigned short value0, ...);

		float choose(size_t index, float value0, ...);

#if __cplusplus >= 201103L //C++0x
		/*
		 * choose 为 C++ 11 准备的新特性: 初始化列表风格的 choose 函数
		 */
		template <class T>
		T choose(size_t index, std::initializer_list<T> src) throw (std::out_of_range)
		{
			if (index >= src.size()) {
				throw std::out_of_range("index is out of range");
			}
			return src.begin()[index];
		}

		/*
		 * choose_c11 为 C++ 11 准备的新特性: 可变参数模板风格的 choose 函数
		 */
		template <typename T, typename ...Args>
		T choose_c11(size_t index, const T & head, Args && ... args) throw (std::out_of_range)
		{
			if (index > sizeof...(Args)) {
				throw std::out_of_range("index is out of range");
			}

			std::initializer_list<const T *> list = { &head, &args... };
			return *(list.begin()[index]);
		}
#endif

	}/* Namespace choose */

}/* Namespace kerbal */

#endif /* End CHOOSE_HPP_ */
