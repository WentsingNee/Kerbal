/**
 * @file       default_construct_at.fwd.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_AT_DEFAULT_CONSTRUCT_AT_FWD_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_AT_DEFAULT_CONSTRUCT_AT_FWD_HPP

#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename T>
		KERBAL_CONSTEXPR14
		T * default_construct_at(T * p);

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_AT_DEFAULT_CONSTRUCT_AT_FWD_HPP
