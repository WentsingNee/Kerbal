/**
 * @file       modules.hpp
 * @brief
 * @date       2023-04-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ENABLE_MODULES
#	ifdef __cpp_modules
#		define KERBAL_ENABLE_MODULES 1
#	else
#		define KERBAL_ENABLE_MODULES 0
#	endif
#endif

#if KERBAL_ENABLE_MODULES
#	define KERBAL_MODULE_EXPORT export
#else
#	define KERBAL_MODULE_EXPORT
#endif
