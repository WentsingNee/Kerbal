/**
 * @file       std_pair.fwd.hpp
 * @brief
 * @date       2023-12-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_STD_PAIR_STD_PAIR_FWD_HPP
#define KERBAL_UTILITY_STD_PAIR_STD_PAIR_FWD_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename U>
# if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
	struct pair;
# else
	class pair;
# endif

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_UTILITY_STD_PAIR_STD_PAIR_FWD_HPP
