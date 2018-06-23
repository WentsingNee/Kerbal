/**
 * @file		transmit.hpp
 * @brief
 * @date		2018年6月23日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TRANSMIT_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TRANSMIT_HPP_

namespace kerbal
{
	namespace type_traits
	{
		template <typename Type>
		struct Transmit_optimize_enable
		{
				typedef Type type;
		};

		template <typename Type>
		struct Transmit_optimize_disable
		{
				typedef const Type& type;
		};

		template <typename Type>
		struct Transmit;

		template <typename Type>
		struct Transmit: public Transmit_optimize_disable<Type>
		{
		};

		template <typename Type>
		struct Transmit<Type*> : public Transmit_optimize_enable<Type*>
		{
		};

		template <typename Type>
		struct Transmit<const Type*> : public Transmit_optimize_enable<const Type*>
		{
		};

		template <>
		struct Transmit<char>
		{
				typedef char type;
		};

		template <>
		struct Transmit<signed char>
		{
				typedef signed char type;
		};

		template <>
		struct Transmit<unsigned char>
		{
				typedef unsigned char type;
		};

		template <>
		struct Transmit<short>
		{
				typedef short type;
		};

		template <>
		struct Transmit<unsigned short>
		{
				typedef unsigned short type;
		};

		template <>
		struct Transmit<int>
		{
				typedef int type;
		};

		template <>
		struct Transmit<unsigned int>
		{
				typedef unsigned int type;
		};

		template <>
		struct Transmit<float>
		{
				typedef float type;
		};

		template <>
		struct Transmit<unsigned float>
		{
				typedef unsigned int type;
		};

	}
}



#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TRANSMIT_HPP_ */
