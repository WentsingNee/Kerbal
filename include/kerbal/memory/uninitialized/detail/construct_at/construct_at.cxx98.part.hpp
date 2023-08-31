/**
 * @file       construct_at.cxx98.part.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @remark     split from <kerbal/memory/uninitalized/construct.hpp>, 2023-08-31
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_CXX98_PART_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_CXX98_PART_HPP

#include <kerbal/macro/macro_concat.hpp>
#include <kerbal/macro/ppexpand.hpp>


namespace kerbal
{

	namespace memory
	{

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		T * construct_at(T * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			::new (const_cast<void*>(static_cast<const volatile void*>(p))) T (KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
			return p; \
		}

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_CXX98_PART_HPP
