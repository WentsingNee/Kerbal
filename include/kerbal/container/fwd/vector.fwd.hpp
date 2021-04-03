/**
 * @file       vector.fwd.hpp
 * @brief
 * @date       2020-08-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FWD_VECTOR_FWD_HPP
#define KERBAL_CONTAINER_FWD_VECTOR_FWD_HPP

#include <memory>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator = std::allocator<Tp> >
		class vector;

		namespace detail
		{

			template <typename Tp>
			class vector_allocator_unrelated;

			template <typename Allocator>
			class vector_allocator_overload;

			template <typename Tp>
			class vec_iter;

			template <typename Tp>
			class vec_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_FWD_VECTOR_FWD_HPP
