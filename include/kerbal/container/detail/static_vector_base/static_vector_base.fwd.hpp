/**
 * @file       static_vector_base.fwd.hpp
 * @brief
 * @date       2023-12-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_BASE_STATIC_VECTOR_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_BASE_STATIC_VECTOR_BASE_FWD_HPP

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp, std::size_t N>
			class static_vector_base;

			template <typename T>
			class sv_iter;

			template <typename T>
			class sv_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_BASE_STATIC_VECTOR_BASE_FWD_HPP
