/**
 * @file       type_chooser.hpp
 * @brief      
 * @date       2019年5月14日
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */
#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_TYPE_CHOOSER_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_TYPE_CHOOSER_HPP_


#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <cstddef>

namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		template <size_t N, typename Type0, typename ... Args>
		struct type_chooser;

		MODULE_EXPORT
		template <typename Type0, typename ... Args>
		struct type_chooser<0, Type0, Args...>
		{
				typedef Type0 type;
		};

		MODULE_EXPORT
		template <size_t N, typename Type0, typename ... Args>
		struct type_chooser
		{
				static_assert(N <= sizeof...(Args), "N is larger than the number of template type arguments");
				typedef typename type_chooser<N - 1, Args...>::type type;
		};

#	endif

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_TYPE_CHOOSER_HPP_ */
