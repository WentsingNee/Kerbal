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

		template <typename Type>
		struct Transmit<Type&> : public Transmit_optimize_enable<Type&>
		{
		};

		template <typename Type>
		struct Transmit<const Type&> : public Transmit_optimize_enable<const Type&>
		{
		};

		template <>
		struct Transmit<char> : public Transmit_optimize_enable<char>
		{
		};

		template <>
		struct Transmit<signed char> : public Transmit_optimize_enable<signed char>
		{
		};

		template <>
		struct Transmit<unsigned char> : public Transmit_optimize_enable<unsigned char>
		{
		};

		template <>
		struct Transmit<short> : public Transmit_optimize_enable<short>
		{
		};

		template <>
		struct Transmit<unsigned short> : public Transmit_optimize_enable<unsigned short>
		{
		};

		template <>
		struct Transmit<int> : public Transmit_optimize_enable<int>
		{
		};

		template <>
		struct Transmit<unsigned int> : public Transmit_optimize_enable<unsigned int>
		{
		};

		template <>
		struct Transmit<float> : public Transmit_optimize_enable<float>
		{
		};

		template <>
		struct Transmit<unsigned float> : public Transmit_optimize_enable<unsigned float>
		{
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TRANSMIT_HPP_ */
