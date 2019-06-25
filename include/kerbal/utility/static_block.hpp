/*
 * static_block.hpp
 *
 *  Created on: 2018年9月11日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_UTILITY_STATIC_BLOCK_HPP_
#define INCLUDE_KERBAL_UTILITY_STATIC_BLOCK_HPP_

#ifdef __KERBAL_STATIC_BLOCK_TITLE
#	undef __KERBAL_STATIC_BLOCK_TITLE
#endif

#ifdef __KERBAL_STATIC_BLOCK_HELPER
#	undef __KERBAL_STATIC_BLOCK_HELPER
#endif

#ifdef KERBAL_STATIC_BLOCK
#	undef KERBAL_STATIC_BLOCK
#endif


#define __KERBAL_STATIC_BLOCK_TITLE(LINE) \
static bool __kerbal_static_block_flag_ ## LINE = false; \
if ((__kerbal_static_block_flag_ ## LINE == false) ? \
	(__kerbal_static_block_flag_ ## LINE = true) : \
	false \
	)

#define __KERBAL_STATIC_BLOCK_HELPER(LINE)  __KERBAL_STATIC_BLOCK_TITLE(LINE)
#define KERBAL_STATIC_BLOCK  __KERBAL_STATIC_BLOCK_HELPER(__LINE__)


#endif /* INCLUDE_KERBAL_UTILITY_STATIC_BLOCK_HPP_ */
