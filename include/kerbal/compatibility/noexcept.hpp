/*
 * noexcept.hpp
 *
 *  Created on: 2019年5月11日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_COMPATIBILITY_NOEXCEPT_HPP_
#define INCLUDE_KERBAL_COMPATIBILITY_NOEXCEPT_HPP_

#ifndef KERBAL_NOEXCEPT
#	if __cplusplus >= 201103L
#		define KERBAL_NOEXCEPT noexcept
#	else
#		define KERBAL_NOEXCEPT throw()
#	endif
#endif


#ifndef KERBAL_CONDITIONAL_NOEXCEPT
#	if __cplusplus >= 201103L
#		define KERBAL_CONDITIONAL_NOEXCEPT(cond) noexcept(cond)
#	else
#		define KERBAL_CONDITIONAL_NOEXCEPT(cond)
#	endif
#endif

#endif /* INCLUDE_KERBAL_COMPATIBILITY_NOEXCEPT_HPP_ */
