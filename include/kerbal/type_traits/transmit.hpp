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
		struct transmit_optimize_enable
		{
				typedef Type type;
		};

		template <typename Type>
		struct transmit_optimize_disable
		{
				typedef const Type& type;
		};

		template <typename Type>
		struct transmit;

		template <typename Type>
		struct transmit: public transmit_optimize_disable<Type>
		{
		};

		template <typename Type>
		struct transmit<Type*> : public transmit_optimize_enable<Type*>
		{
		};

		template <typename Type>
		struct transmit<const Type*> : public transmit_optimize_enable<const Type*>
		{
		};

		template <typename Type>
		struct transmit<Type&> : public transmit_optimize_enable<Type&>
		{
		};

		template <typename Type>
		struct transmit<const Type&> : public transmit_optimize_enable<const Type&>
		{
		};

		template <>
		struct transmit<char> : public transmit_optimize_enable<char>
		{
		};

		template <>
		struct transmit<signed char> : public transmit_optimize_enable<signed char>
		{
		};

		template <>
		struct transmit<unsigned char> : public transmit_optimize_enable<unsigned char>
		{
		};

		template <>
		struct transmit<short> : public transmit_optimize_enable<short>
		{
		};

		template <>
		struct transmit<unsigned short> : public transmit_optimize_enable<unsigned short>
		{
		};

		template <>
		struct transmit<int> : public transmit_optimize_enable<int>
		{
		};

		template <>
		struct transmit<unsigned int> : public transmit_optimize_enable<unsigned int>
		{
		};

		template <>
		struct transmit<float> : public transmit_optimize_enable<float>
		{
		};

		template <>
		struct transmit<unsigned float> : public transmit_optimize_enable<unsigned float>
		{
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TRANSMIT_HPP_ */
