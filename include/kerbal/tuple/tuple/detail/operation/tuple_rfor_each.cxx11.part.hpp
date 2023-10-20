tuple_for_each.cxx11.part.hpp/**
 * @file       tuple_rfor_each.cxx11.part.hpp
 * @brief
 * @date       2023-10-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_RFOR_EACH_CXX11_PART_HPP
#define KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_RFOR_EACH_CXX11_PART_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/integer_sequence.hpp>
#include <kerbal/utility/ignore_unused.hpp>

#include <initializer_list>

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename Self, typename F, std::size_t ... Index>
			KERBAL_CONSTEXPR
			static
			Self &&
			k_rfor_each_impl(Self && self, F f, kerbal::utility::index_sequence<Index...>)
			{
				typedef typename kerbal::type_traits::remove_cvref<Self>::type Tuple;
				typedef typename Tuple::TUPLE_SIZE N;
				return
					kerbal::utility::ignore_unused(
						std::initializer_list<int>{
							(
								f(
									kerbal::type_traits::integral_constant<std::size_t, N::value - 1 - Index>(),
									kerbal::utility::forward<Self>(self).template get<N::value - 1 - Index>()
								),
								0
							)...
						}
					),
					kerbal::utility::forward<Self>(self);
			}

		} // namespace detail

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_RFOR_EACH_CXX11_PART_HPP
