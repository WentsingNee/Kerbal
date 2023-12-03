/**
 * @file       erasable.hpp
 * @brief
 * @date       2023-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ERASABLE_HPP
#define KERBAL_CONTAINER_ERASABLE_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/memory/allocator_traits.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <typename T, typename Allocator = std::allocator<T> >
		concept erasable = requires(Allocator & alloc, T * p) {
			kerbal::memory::allocator_traits<Allocator>::destroy(alloc, p);
		};

	} // namespace container

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONTAINER_ERASABLE_HPP
