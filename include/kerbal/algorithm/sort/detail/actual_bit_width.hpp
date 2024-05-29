/**
 * @file       actual_bit_width.hpp
 * @brief
 * @date       2020-5-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_DETAIL_ACTUAL_BIT_WIDTH_HPP
#define KERBAL_ALGORITHM_SORT_DETAIL_ACTUAL_BIT_WIDTH_HPP

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_cv.hpp>

#include <climits>
#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename T>
			struct actual_bit_width_helper: kerbal::type_traits::integral_constant<std::size_t, sizeof(T) * CHAR_BIT>
			{
			};

			template <>
			struct actual_bit_width_helper<bool>: kerbal::type_traits::integral_constant<std::size_t, 1>
			{
			};

			template <typename T>
			struct actual_bit_width: actual_bit_width_helper<typename kerbal::type_traits::remove_cv<T>::type>
			{
			};

		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_DETAIL_ACTUAL_BIT_WIDTH_HPP
