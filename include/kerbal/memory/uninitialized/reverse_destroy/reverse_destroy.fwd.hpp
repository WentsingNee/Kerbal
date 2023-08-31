/**
 * @file       reverse_destroy.fwd.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_REVERSE_DESTROY_REVERSE_DESTROY_FWD_HPP
#define KERBAL_MEMORY_UNINITIALIZED_REVERSE_DESTROY_REVERSE_DESTROY_FWD_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void reverse_destroy(BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT;

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_REVERSE_DESTROY_REVERSE_DESTROY_FWD_HPP
