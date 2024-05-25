/**
 * @file       throw_this_exception.hpp
 * @brief      
 * @date       2019-7-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_THROW_THIS_EXCEPTION_HPP
#define KERBAL_UTILITY_THROW_THIS_EXCEPTION_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if !KERBAL_HAS_EXCEPTIONS_SUPPORT
#	include <cstdlib> // std::abort
#endif

namespace kerbal
{

	namespace utility
	{

		template <typename Exception>
		class throw_this_exception_helper
		{
			public:

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

#		if __cplusplus >= 201103L

					template <typename ... Args>
					[[noreturn]]
					static
					void throw_this_exception(Args && ... args)
					{
						throw Exception(kerbal::utility::forward<Args>(args)...);
					}

#		else

#				define EMPTY
#				define REMAINF(exp) exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					static \
					void throw_this_exception(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
					{ \
						throw Exception(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
					} \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef REMAINF
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

#	else // no exception

#		if __cplusplus >= 201103L

					template <typename ... Args>
					[[noreturn]]
					static
					void throw_this_exception(Args && ...) noexcept
					{
						std::abort();
					}

#		else

#				define EMPTY
#				define REMAINF(exp) exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) &
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					static \
					void throw_this_exception(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) KERBAL_NOEXCEPT \
					{ \
						std::abort(); \
					} \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef REMAINF
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#		endif

#	endif

		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_THROW_THIS_EXCEPTION_HPP
