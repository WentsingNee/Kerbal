/**
 * @file       ignore_unused.hpp
 * @brief
 * @date       2020-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_IGNORE_UNUSED_HPP
#define KERBAL_UTILITY_IGNORE_UNUSED_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif


namespace kerbal
{

	namespace utility
	{

#	if __cplusplus >= 201402L

		template <typename ... Args>
		KERBAL_CONSTEXPR14
		void ignore_unused(Args && ...) KERBAL_NOEXCEPT
		{
		}

#	elif __cplusplus >= 201103L

		template <typename ... Args>
		KERBAL_CONSTEXPR
		int ignore_unused(Args && ...) KERBAL_NOEXCEPT
		{
			return 0;
		}

#	else

#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) &
#	define FBODY(i) \
		template <KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_DECL, i)> \
		void ignore_unused(KERBAL_PPEXPAND_WITH_COMMA_N(ARGS_DECL, i)) KERBAL_NOEXCEPT \
		{ \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef FBODY

#	endif

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_IGNORE_UNUSED_HPP
