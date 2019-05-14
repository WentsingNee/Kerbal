/*
 * constexpr.hpp
 *
 *  Created on: 2019年5月11日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_COMPATIBILITY_CONSTEXPR_HPP_
#define INCLUDE_KERBAL_COMPATIBILITY_CONSTEXPR_HPP_

#ifndef KERBAL_CONSTEXPR
#	if __cplusplus >= 201103L
#		define KERBAL_CONSTEXPR constexpr
#	else
#		define KERBAL_CONSTEXPR
#	endif
#endif

#endif /* INCLUDE_KERBAL_COMPATIBILITY_CONSTEXPR_HPP_ */
