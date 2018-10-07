/*
 * static_block.hpp
 *
 *  Created on: 2018年9月11日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_UTILITY_STATIC_BLOCK_HPP_
#define INCLUDE_KERBAL_UTILITY_STATIC_BLOCK_HPP_

#ifdef KERBAL_STATIC_BLOCK_CALL
#	undef KERBAL_STATIC_BLOCK_CALL
#endif

#ifdef KERBAL_STATIC_BLOCK_CALL2
#	undef KERBAL_STATIC_BLOCK_CALL2
#endif

#ifdef KERBAL_STATIC_BLOCK
#	undef KERBAL_STATIC_BLOCK
#endif

#define KERBAL_STATIC_BLOCK_TITLE(LINE) \
	static bool __kerbal_static_block_flag1_ ## LINE = true; \
	bool __kerbal_static_block_flag2_ ## LINE = __kerbal_static_block_flag1_ ## LINE; \
	__kerbal_static_block_flag1_ ## LINE = false; \
	if(__kerbal_static_block_flag2_ ## LINE)


#define KERBAL_STATIC_BLOCK_HELPER(LINE)  KERBAL_STATIC_BLOCK_TITLE(LINE)
#define KERBAL_STATIC_BLOCK  KERBAL_STATIC_BLOCK_HELPER(__LINE__)


#endif /* INCLUDE_KERBAL_UTILITY_STATIC_BLOCK_HPP_ */
