/**
 * @file		type_traits.hpp
 * @brief
 * @date		2018年6月23日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_

#include <kerbal/compatibility/compatibility_macro.hpp>

namespace kerbal
{
	namespace type_traits
	{

#	if __cplusplus < 201103L

		struct false_type
		{
				enum
				{
					value = 0
				};
		};

		struct true_type
		{
				enum
				{
					value = 1
				};
		};

#	else

		struct false_type
		{
			static constexpr bool value = false;
		};

		struct true_type
		{
			static constexpr bool value = true;
		};

#	endif

		template <typename Type, Type val>
		struct integral_constant
		{
#			if __cplusplus >= 201103L
				static constexpr Type value = val;
#			else
				static const Type value = val;
#			endif

				typedef Type value_type;
				typedef integral_constant<Type, val> type;

				KERBAL_CONSTEXPR operator value_type() const
				{
					return value;
				}
		};

		template <bool condition, typename Tp = void>
		struct enable_if
		{
		};

		template <typename Tp>
		struct enable_if<true, Tp>
		{
				typedef Tp type;
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_ */
