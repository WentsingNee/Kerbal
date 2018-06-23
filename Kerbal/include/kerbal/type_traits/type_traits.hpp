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

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_ */
