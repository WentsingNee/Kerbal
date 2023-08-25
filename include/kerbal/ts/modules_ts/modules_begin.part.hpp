/**
 * @file       modules_begin.part.hpp
 * @brief
 * @date       2023-04-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#undef KERBAL_MODULE_EXPORT

#if KERBAL_ENABLE_MODULES_EXPORT && !defined(KERBAL_MODULES_INCLUDE)
#	define KERBAL_MODULE_EXPORT export
#else
#	define KERBAL_MODULE_EXPORT
#endif
