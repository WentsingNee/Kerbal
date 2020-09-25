/**
 * @file       disable_warning.hpp
 * @brief
 * @date       2020-08-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPENMP_DISABLE_WARNING_HPP
#define KERBAL_OPENMP_DISABLE_WARNING_HPP

#if !defined(_OPENMP)
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "openMP is disable")
#	else
#		warning "Kerbal Warning: " "openMP is disable"
#	endif

#endif

#endif // KERBAL_OPENMP_DISABLE_WARNING_HPP
