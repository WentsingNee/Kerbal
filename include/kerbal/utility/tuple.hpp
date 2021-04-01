/**
 * @file       tuple.hpp
 * @brief
 * @date       2020-07-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_TUPLE_HPP
#define KERBAL_UTILITY_TUPLE_HPP

#if __cplusplus < 201103L
#	include <kerbal/utility/detail/tuple_cxx98.hpp>
#else
#	include <kerbal/utility/detail/tuple_cxx11.hpp>
#endif

#endif // KERBAL_UTILITY_TUPLE_HPP
