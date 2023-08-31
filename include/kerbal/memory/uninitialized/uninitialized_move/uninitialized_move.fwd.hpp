/**
 * @file       uninitialized_move.fwd.hpp
 * @brief
 * @date       2023-10-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_MOVE_UNINITIALIZED_MOVE_FWD_HPP
#define KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_MOVE_UNINITIALIZED_MOVE_FWD_HPP

#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to);

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_MOVE_UNINITIALIZED_MOVE_FWD_HPP
