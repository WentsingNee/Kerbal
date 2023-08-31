/**
 * @file       uninitialized_default_construct.fwd.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_DEFAULT_CONSTRUCT_UNINITIALIZED_DEFAULT_CONSTRUCT_FWD_HPP
#define KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_DEFAULT_CONSTRUCT_UNINITIALIZED_DEFAULT_CONSTRUCT_FWD_HPP

#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_default_construct(ForwardIterator first, ForwardIterator last);

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_DEFAULT_CONSTRUCT_UNINITIALIZED_DEFAULT_CONSTRUCT_FWD_HPP
