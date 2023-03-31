/**
 * @file       void_type.hpp
 * @brief
 * @date       2019-10-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_VOID_TYPE_HPP
#define KERBAL_TYPE_TRAITS_VOID_TYPE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/ppexpand.hpp>
#endif

namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus < 201103L

#	define TARGS_DECL(i) typename = T0

		template <typename T0 = void, KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_DECL, 20)>
		struct void_type
		{
				typedef void type;
		};

#	undef TARGS_DECL

#	else

		KERBAL_MODULE_EXPORT
		template <typename ... Args>
		struct void_type
		{
				typedef void type;
		};

#	endif

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_VOID_TYPE_HPP
