/**
 * @file       join_line.hpp
 * @brief
 * @date       2020-07-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MACRO_JOIN_LINE_HPP
#define KERBAL_MACRO_JOIN_LINE_HPP

#include <kerbal/macro/macro_concat.hpp>

#define KERBAL_JOIN_LINE(m) KERBAL_MACRO_CONCAT(m, __LINE__)

#endif // KERBAL_MACRO_JOIN_LINE_HPP
