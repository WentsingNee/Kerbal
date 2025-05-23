/**
 * @file       ilist.hpp
 * @brief
 * @date       2020-08-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ASSIGN_ILIST_HPP
#define KERBAL_ASSIGN_ILIST_HPP


#if __cplusplus >= 201103L
#	define KERBAL_ILIST(...) {__VA_ARGS__}
#else
#	include <kerbal/assign/assign_list.hpp>
#	include <kerbal/macro/va_arg_size.hpp>

#	define KERBAL_ILIST(args...) (kerbal::assign::make_assign_list(KERBAL_VA_ARG_SIZE(args)), ##args)
#endif


#endif // KERBAL_ASSIGN_ILIST_HPP
