/**
 * @file       std_tuple.fwd.hpp
 * @brief
 * @date       2023-12-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_STD_TUPLE_STD_TUPLE_FWD_HPP
#define KERBAL_UTILITY_STD_TUPLE_STD_TUPLE_FWD_HPP

#if __cplusplus >= 201103L

#include <kerbal/compatibility/namespace_std_scope.hpp>

#include <cstddef>


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T>
	struct tuple_size;


	template <std::size_t I, typename T>
	struct tuple_element;

KERBAL_NAMESPACE_STD_END

#endif


#endif // KERBAL_UTILITY_STD_TUPLE_STD_TUPLE_FWD_HPP
