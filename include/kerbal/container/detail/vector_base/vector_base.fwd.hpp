/**
 * @file       vector_base.fwd.hpp
 * @brief
 * @date       2021-08-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_FWD_HPP


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename T>
			class vector_type_only;

			template <typename PointerType>
			class vec_iter;

			template <typename PointerType>
			class vec_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_FWD_HPP
