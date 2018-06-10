/*
 * type_chooser.hpp
 *
 *  Created on: 2018年6月10日
 *      Author: peter
 */

#ifndef KERBAL_INCLUDE_KERBAL_UTILITY_TYPE_CHOOSER_HPP_
#define KERBAL_INCLUDE_KERBAL_UTILITY_TYPE_CHOOSER_HPP_

namespace kerbal
{
	namespace utility
	{

#	if __cplusplus >= 201103L

		template <unsigned long long N, typename Type0, typename ... Args>
		struct type_chooser;

		template <typename Type0, typename ... Args>
		struct type_chooser<0, Type0, Args...>
		{
				typedef Type0 type;
		};

		template <unsigned long long N, typename Type0, typename ... Args>
		struct type_chooser
		{
				static_assert(N <= sizeof...(Args), "N is larger than the number of template type arguments");
				typedef typename type_chooser<N - 1, Args...>::type type;
		};

#	endif

	}
}

#endif /* KERBAL_INCLUDE_KERBAL_UTILITY_TYPE_CHOOSER_HPP_ */
