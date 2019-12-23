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
		struct is_unbounded_array : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_unbounded_array<Tp[]> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename>
		struct is_bounded_array : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp, size_t N>
		struct is_bounded_array<Tp[N]> : kerbal::type_traits::true_type
		{
		};

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
		template <typename Tp, size_t i = 0>
		struct extent;

		MODULE_EXPORT
		template <typename Tp>
		struct extent<Tp, 0>: kerbal::type_traits::integral_constant<size_t, 0>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct extent<Tp[], 0> : kerbal::type_traits::integral_constant<size_t, 0>
		{
		};

		MODULE_EXPORT
		template <typename Tp, size_t i>
		struct extent<Tp[], i> : kerbal::type_traits::extent<Tp, i - 1>
		{
		};

		MODULE_EXPORT
		template <typename Tp, size_t N>
		struct extent<Tp[N], 0> : kerbal::type_traits::integral_constant<size_t, N>
		{
		};

		MODULE_EXPORT
		template <typename Tp, size_t N, size_t i>
		struct extent<Tp[N], i> : kerbal::type_traits::extent<Tp, i - 1>
		{
		};


		/// rank
		MODULE_EXPORT
		template <typename >
		struct rank: kerbal::type_traits::integral_constant<size_t, 0>
		{
		};

		MODULE_EXPORT
		template <typename Tp, size_t N>
		struct rank<Tp[N]> : kerbal::type_traits::integral_constant<
										size_t,
										1 + rank<Tp>::value
								>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct rank<Tp[]> : kerbal::type_traits::integral_constant<
										size_t,
										1 + rank<Tp>::value
								>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_extent
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp, size_t N>
		struct remove_extent<Tp[N]>
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_extent<Tp[]>
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_all_extents
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp, size_t N>
		struct remove_all_extents<Tp[N]> : kerbal::type_traits::remove_all_extents<Tp>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_all_extents<Tp[]> : kerbal::type_traits::remove_all_extents<Tp>
		{
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_ARRAY_TRAITS_HPP_ */
