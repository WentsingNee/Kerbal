/**
 * @file       array_traits.hpp
 * @brief
 * @date       2019-5-5
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_ARRAY_TRAITS_HPP
#define KERBAL_TYPE_TRAITS_ARRAY_TRAITS_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


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
		template <typename Tp, std::size_t N>
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
		template <typename Tp, std::size_t N>
		struct is_array<Tp[N]> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp, std::size_t i = 0>
		struct extent;

		MODULE_EXPORT
		template <typename Tp>
		struct extent<Tp, 0>: kerbal::type_traits::integral_constant<std::size_t, 0>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct extent<Tp[], 0> : kerbal::type_traits::integral_constant<std::size_t, 0>
		{
		};

		MODULE_EXPORT
		template <typename Tp, std::size_t i>
		struct extent<Tp[], i> : kerbal::type_traits::extent<Tp, i - 1>
		{
		};

		MODULE_EXPORT
		template <typename Tp, std::size_t N>
		struct extent<Tp[N], 0> : kerbal::type_traits::integral_constant<std::size_t, N>
		{
		};

		MODULE_EXPORT
		template <typename Tp, std::size_t N, std::size_t i>
		struct extent<Tp[N], i> : kerbal::type_traits::extent<Tp, i - 1>
		{
		};


		/// rank
		MODULE_EXPORT
		template <typename >
		struct rank: kerbal::type_traits::integral_constant<std::size_t, 0>
		{
		};

		MODULE_EXPORT
		template <typename Tp, std::size_t N>
		struct rank<Tp[N]> : kerbal::type_traits::integral_constant<
										std::size_t,
										1 + rank<Tp>::value
								>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct rank<Tp[]> : kerbal::type_traits::integral_constant<
										std::size_t,
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
		template <typename Tp, std::size_t N>
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
		template <typename Tp, std::size_t N>
		struct remove_all_extents<Tp[N]> : kerbal::type_traits::remove_all_extents<Tp>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_all_extents<Tp[]> : kerbal::type_traits::remove_all_extents<Tp>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_ARRAY_TRAITS_HPP
