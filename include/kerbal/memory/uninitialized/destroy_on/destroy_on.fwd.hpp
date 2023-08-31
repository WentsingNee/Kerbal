/**
 * @file       destroy_on.fwd.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DESTROY_ON_DESTROY_ON_FWD_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DESTROY_ON_DESTROY_ON_FWD_HPP

#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename T>
		KERBAL_CONSTEXPR14
		void destroy_on(T & plc);

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DESTROY_ON_DESTROY_ON_FWD_HPP
