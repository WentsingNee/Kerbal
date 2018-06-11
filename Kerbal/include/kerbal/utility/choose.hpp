/**
 * @file		choose.hpp
 * @brief
 * @date		2017年7月8日 (2018年6月10日 第二版)
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_UTILITY_CHOOSE_HPP_
#define INCLUDE_KERBAL_UTILITY_CHOOSE_HPP_

#include <stdarg.h>
#include <cctype>

#if __cplusplus >= 201103L //c++0x
#	include <initializer_list>
#endif //c++0x

namespace kerbal
{
	namespace utility
	{
		namespace choose
		{

			template <typename Type>
			struct va_list_type_traits
			{
					typedef Type type;
			};

			template <>
			struct va_list_type_traits<char>
			{
					typedef int type;
			};
			template <>
			struct va_list_type_traits<unsigned char>
			{
					typedef int type;
			};
			template <>
			struct va_list_type_traits<signed char>
			{
					typedef int type;
			};
			template <>
			struct va_list_type_traits<short>
			{
					typedef int type;
			};
			template <>
			struct va_list_type_traits<unsigned short>
			{
					typedef int type;
			};

			template <>
			struct va_list_type_traits<float>
			{
					typedef double type;
			};

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
					va_arg(arg_ptr, va_list_type_traits<T>::type);
				}
				va_end(arg_ptr);
				return va_arg(arg_ptr, va_list_type_traits<T>::type);

				/*
				 * 为何要为 [signed/unsigned] char, [unsigned] short, float 类型单独提供 va_list_type_traits, 请参考:
				 * http://www.cppblog.com/ownwaterloo/archive/2009/04/21/unacceptable_type_in_va_arg.html
				 */
			}

#		if __cplusplus >= 201103L //c++0x

			/*
			 * choose 为 C++ 11 准备的新特性: 初始化列表风格的 choose 函数
			 */
			template <class T>
			T choose(size_t index, std::initializer_list<T> src)
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
			T choose_c11(size_t index, const T & head, Args && ... args)
			{
				if (index > sizeof...(Args)) {
					throw std::out_of_range("index is out of range");
				}

				std::initializer_list<const T *> list = {&head, &args...};
				return *(list.begin()[index]);
			}

#		endif //c++0x

		}/* Namespace choose */

	}/* Namespace utility */

}/* Namespace kerbal */

#endif /* INCLUDE_KERBAL_UTILITY_CHOOSE_HPP_ */
