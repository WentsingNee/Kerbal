/**
 * @file       ring_buffer_queue.fwd.hpp
 * @brief
 * @date       2022-03-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_RING_BUFFER_QUEUE_RING_BUFFER_QUEUE_FWD_HPP
#define KERBAL_CONTAINER_RING_BUFFER_QUEUE_RING_BUFFER_QUEUE_FWD_HPP

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <typename T, typename Allocator = std::allocator<T> >
		class ring_buffer_queue;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_RING_BUFFER_QUEUE_RING_BUFFER_QUEUE_FWD_HPP
