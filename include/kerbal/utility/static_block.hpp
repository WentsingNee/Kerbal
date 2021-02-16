/**
 * @file       static_block.hpp
 * @brief
 * @date       2018-9-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_STATIC_BLOCK_HPP
#define KERBAL_UTILITY_STATIC_BLOCK_HPP

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


#endif // KERBAL_UTILITY_STATIC_BLOCK_HPP
