/**
 * @file       tuple_transform.cxx11.part.hpp
 * @brief
 * @date       2023-10-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_TRANSFORM_CXX11_PART_HPP
#define KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_TRANSFORM_CXX11_PART_HPP

namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename Self, typename F, std::size_t ... Index>
			struct transform_result
			{
					typedef kerbal::utility::tuple<
						decltype(
							f(
								kerbal::type_traits::integral_constant<std::size_t, Index>(),
								kerbal::utility::forward<Self>(self).template get<Index>()
							)
						)...
					> type;
			};

		} // namespace detail

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_TRANSFORM_CXX11_PART_HPP
