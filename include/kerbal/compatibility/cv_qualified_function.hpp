/**
 * @file       cv_qualified_function.hpp
 * @brief
 * @date       2021-12-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_CV_QUALIFIED_FUNCTION_HPP
#define KERBAL_COMPATIBILITY_CV_QUALIFIED_FUNCTION_HPP

#ifndef KERBAL_HAS_CV_QUALIFIED_FUNCTION_SUPPORT

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>


#	if __cplusplus < 201103L

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#			if KERBAL_GNU_VERSION_MEETS(4, 9, 0)
#				define KERBAL_HAS_CV_QUALIFIED_FUNCTION_SUPPORT 1
#			endif
#		elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			if KERBAL_MSVC_VERSION_MEETS(18, 0, 0)
#				define KERBAL_HAS_CV_QUALIFIED_FUNCTION_SUPPORT 1
#			endif
#		else
#			define KERBAL_HAS_CV_QUALIFIED_FUNCTION_SUPPORT 1
#		endif

#	else

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#			if KERBAL_GNU_VERSION_MEETS(4, 9, 0)
#				define KERBAL_HAS_CV_QUALIFIED_FUNCTION_SUPPORT 1
#			endif
#		else
#			 define KERBAL_HAS_CV_QUALIFIED_FUNCTION_SUPPORT 1
#		endif

#	endif

#	ifndef KERBAL_HAS_CV_QUALIFIED_FUNCTION_SUPPORT
#		define KERBAL_HAS_CV_QUALIFIED_FUNCTION_SUPPORT 0
#	endif

#endif

#endif // KERBAL_COMPATIBILITY_CV_QUALIFIED_FUNCTION_HPP
