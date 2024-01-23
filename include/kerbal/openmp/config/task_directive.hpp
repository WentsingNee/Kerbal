/**
 * @file       task_directive.hpp
 * @brief
 * @date       2024-01-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPENMP_CONFIG_TASK_DIRECTIVE_HPP
#define KERBAL_OPENMP_CONFIG_TASK_DIRECTIVE_HPP

#include <omp.h>


#ifndef KERBAL_OMP_HAS_TASK_DIRECTIVE_SUPPORT
#	if _OPENMP > 200203L
#		define KERBAL_OMP_HAS_TASK_DIRECTIVE_SUPPORT 1
#	else
#		define KERBAL_OMP_HAS_TASK_DIRECTIVE_SUPPORT 0
#	endif
#endif


#endif // KERBAL_OPENMP_CONFIG_TASK_DIRECTIVE_HPP
