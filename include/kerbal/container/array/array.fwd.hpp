/**
 * @file       array.fwd.hpp
 * @brief
 * @date       2020-11-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ARRAY_ARRAY_FWD_HPP
#define KERBAL_CONTAINER_ARRAY_ARRAY_FWD_HPP

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		template <typename Tp, std::size_t N>
		class array;

		namespace detail
		{

			template <typename Tp>
			class arr_iter;

			template <typename Tp>
			class arr_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_ARRAY_ARRAY_FWD_HPP
