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
#include <kerbal/type_traits/cv_deduction.hpp>

#include <climits>

namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename Tp>
			struct __actual_bit_width: kerbal::type_traits::integral_constant<size_t, sizeof(Tp) * CHAR_BIT>
			{
			};

			template <>
			struct __actual_bit_width<bool>: kerbal::type_traits::integral_constant<size_t, 1>
			{
			};

			template <typename Tp>
			struct actual_bit_width: __actual_bit_width<typename kerbal::type_traits::remove_cv<Tp>::type>
			{
			};

		}

	} // namespace algorithm

} // namespace kerbal

#endif //KERBAL_ALGORITHM_SORT_DETAIL_ACTUAL_BIT_WIDTH_HPP
