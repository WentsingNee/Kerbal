/**
 * @file       modules_ts.hpp
 * @brief
 * @date       2018-12-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TS_MODULES_TS_MODULES_TS_HPP
#define KERBAL_TS_MODULES_TS_MODULES_TS_HPP

#ifndef KERBAL_ENABLE_MODULES_EXPORT
#	ifdef __cpp_modules
#		define KERBAL_ENABLE_MODULES_EXPORT 1
#	else
#		define KERBAL_ENABLE_MODULES_EXPORT 0
#	endif
#endif

#if KERBAL_ENABLE_MODULES_EXPORT
#	define KERBAL_MODULE_EXPORT export
#else
#	define KERBAL_MODULE_EXPORT
#endif


#endif // KERBAL_TS_MODULES_TS_MODULES_TS_HPP
