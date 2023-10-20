/**
 * @file       tuple_reverse.cxx11.part.hpp
 * @brief
 * @date       2023-10-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_REVERSE_CXX11_PART_HPP
#define KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_REVERSE_CXX11_PART_HPP

#include <kerbal/tuple/tuple/tuple.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/integer_sequence.hpp>

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename Self, std::size_t ... Index>
			KERBAL_CONSTEXPR
			kerbal::utility::tuple<typename value_type<TUPLE_SIZE::value - 1 - Index>::type...>
			k_reverse_impl(Self && self, kerbal::utility::index_sequence<Index...>)
			{
				return kerbal::utility::tuple<typename value_type<TUPLE_SIZE::value - 1 - Index>::type...>(
					kerbal::utility::forward<Self>(self).template get<TUPLE_SIZE::value - 1 - Index>()...
				);
			}

		} // namespace detail

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_REVERSE_CXX11_PART_HPP
