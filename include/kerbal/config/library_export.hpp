/**
 * @file       library_export.hpp
 * @brief
 * @date       2020-09-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_LIBRARY_EXPORT_HPP
#define KERBAL_CONFIG_LIBRARY_EXPORT_HPP

#include <kerbal/config/target_type.hpp>

#ifndef KERBAL_LIBRARY_EXPORT
#	if KERBAL_TARGET_TYPE == KERBAL_TARGET_TYPE_HEADER
#		define KERBAL_LIBRARY_EXPORT 1
#	elif KERBAL_TARGET_TYPE == KERBAL_TARGET_TYPE_STATIC || \
		KERBAL_TARGET_TYPE == KERBAL_TARGET_TYPE_SHARED
#		define KERBAL_LIBRARY_EXPORT 0
#	endif
#endif

#ifndef KERBAL_SYMBOL_EXPORT
#	if KERBAL_TARGET_TYPE == KERBAL_TARGET_TYPE_HEADER
#		define KERBAL_SYMBOL_EXPORT inline
#	elif KERBAL_TARGET_TYPE == KERBAL_TARGET_TYPE_STATIC || \
		KERBAL_TARGET_TYPE == KERBAL_TARGET_TYPE_SHARED
#		define KERBAL_SYMBOL_EXPORT
#	endif
#endif

#endif // KERBAL_CONFIG_LIBRARY_EXPORT_HPP
