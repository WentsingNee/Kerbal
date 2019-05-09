/*
 * array_traits.hpp
 *
 *  Created on: 2019年5月5日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_ARRAY_TRAITS_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_ARRAY_TRAITS_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <cstddef>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename>
		struct is_array : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_array<Tp[]> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp, size_t N>
		struct is_array<Tp[N]> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename>
		struct array_traits;

		MODULE_EXPORT
		template <typename Tp>
		struct array_traits<Tp[]>
		{
				typedef Tp value_type;
		};

		MODULE_EXPORT
		template <typename Tp, size_t N>
		struct array_traits<Tp[N]> : kerbal::type_traits::array_traits<Tp[]>
		{
				typedef Tp value_type;
#				if __cplusplus >= 201103L
					static constexpr size_t size = N;
#				else
					static const size_t size = N;
#				endif
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_ARRAY_TRAITS_HPP_ */
