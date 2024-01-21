/**
 * @file       forward.hpp
 * @brief
 * @date       2020-10-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_FORWARD_HPP
#define KERBAL_UTILITY_FORWARD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL


KERBAL_EXPORT_MODULE_DECLARE(kerbal.utility.forward)


#if __cplusplus >= 201103L
#	include <kerbal/utility/forward/detail/forward.cxx11.part.hpp>
#endif

#endif // KERBAL_UTILITY_FORWARD_HPP
