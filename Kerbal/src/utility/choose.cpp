/*
 * choose.cpp
 *
 *  Created on: 2017年7月8日
 *      Author: Peter
 *      Fuction:
 */

#include <kerbal/utility/choose.hpp>

#if __cplusplus < 201103L //C++0x
# pragma message("\n\
        * choose 使用了 C++ 11 新特性, 请打开 C++ 11 选项以便使用这些新特性\n\
                * choose 为 C++ 11 准备的新特性: 初始化列表风格的 choose 函数\n\
                * choose_c11 为 C++ 11 准备的新特性: 可变参数模板风格的 choose 函数"\
)
#endif /* End C++0x */

namespace kerbal
{
	namespace choose
	{
		namespace
		{

			int choose_int(size_t index, int value0, va_list &arg_ptr)
			{
				if (index == 0) {
					return value0;
				}

				for (size_t i = 1; i < index; ++i) {
					va_arg(arg_ptr, int);
				}
				return va_arg(arg_ptr, int);
			}

			double choose_float(size_t index, double value0, va_list &arg_ptr)
			{
				if (index == 0) {
					return value0;
				}

				for (size_t i = 1; i < index; ++i) {
					va_arg(arg_ptr, double);
				}
				return va_arg(arg_ptr, double);
			}
		}

		char choose(size_t index, char value0, ...)
		{
			va_list arg_ptr;
			va_start(arg_ptr, value0);
			char result = choose_int(index, value0, arg_ptr);
			va_end(arg_ptr);
			return result;
		}

		unsigned char choose(size_t index, unsigned char value0, ...)
		{
			va_list arg_ptr;
			va_start(arg_ptr, value0);
			unsigned char result = choose_int(index, value0, arg_ptr);
			va_end(arg_ptr);
			return result;
		}

		signed char choose(size_t index, signed char value0, ...)
		{
			va_list arg_ptr;
			va_start(arg_ptr, value0);
			signed char result = choose_int(index, value0, arg_ptr);
			va_end(arg_ptr);
			return result;
		}

		short choose(size_t index, short value0, ...)
		{
			va_list arg_ptr;
			va_start(arg_ptr, value0);
			short result = choose_int(index, value0, arg_ptr);
			va_end(arg_ptr);
			return result;
		}

		unsigned short choose(size_t index, unsigned short value0, ...)
		{
			va_list arg_ptr;
			va_start(arg_ptr, value0);
			unsigned short result = choose_int(index, value0, arg_ptr);
			va_end(arg_ptr);
			return result;
		}

		float choose(size_t index, float value0, ...)
		{
			va_list arg_ptr;
			va_start(arg_ptr, value0);
			float result = choose_float(index, value0, arg_ptr);
			va_end(arg_ptr);
			return result;
		}

	}/* Namespace choose */

}/* Namespace kerbal */

