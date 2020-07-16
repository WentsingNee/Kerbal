/**
 * @file       macro_concat.hpp
 * @brief
 * @date       2020-04-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MACRO_MACRO_CONCAT_HPP
#define KERBAL_MACRO_MACRO_CONCAT_HPP

#define __KERBAL_MACRO_CONCAT_HELPER(a, b) a##b
#define KERBAL_MACRO_CONCAT(a, b) __KERBAL_MACRO_CONCAT_HELPER(a, b)

#endif // KERBAL_MACRO_MACRO_CONCAT_HPP
