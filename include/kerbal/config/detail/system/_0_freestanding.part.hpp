/**
 * @file       _0_freestanding.part.hpp
 * @brief
 * @date       2021-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_SYSTEM__0_FREESTANDING_PART_HPP
#define KERBAL_CONFIG_DETAIL_SYSTEM__0_FREESTANDING_PART_HPP


#if defined(__STDC_HOSTED__)
#	if __STDC_HOSTED__ == 0
#		if defined(KERBAL_SYSTEM) && KERBAL_SYSTEM != KERBAL_SYSTEM_FREESTANDING
#			warning "Macro KERBAL_SYSTEM has defined!"
#		else
#			define KERBAL_SYSTEM KERBAL_SYSTEM_FREESTANDING
#		endif
#	endif
#endif


#endif // KERBAL_CONFIG_DETAIL_SYSTEM__0_FREESTANDING_PART_HPP
