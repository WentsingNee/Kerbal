/**
 * @file       static_container_trivially_destructible_traits.hpp
 * @brief
 * @date       2020-6-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_STATIC_CONTAINER_TRIVIALLY_DESTRUCTIBLE_TRAITS_HPP
#define KERBAL_CONTAINER_DETAIL_STATIC_CONTAINER_TRIVIALLY_DESTRUCTIBLE_TRAITS_HPP

#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus < 201103L
#	include <kerbal/type_traits/fundamental_deduction.hpp>
#	include <kerbal/type_traits/pointer_deduction.hpp>
#else
#	include <type_traits>
#endif

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

#		if __cplusplus < 201103L

			template <typename RemoveAllExtents_t>
			struct static_container_trivially_destructible_traits_impl:
					kerbal::type_traits::bool_constant<
							kerbal::type_traits::is_fundamental<RemoveAllExtents_t>::value ||
							kerbal::type_traits::is_pointer<RemoveAllExtents_t>::value
					>
			{
			};

#		else

			template <typename RemoveAllExtents_t>
			struct static_container_trivially_destructible_traits_impl:
					kerbal::type_traits::bool_constant<
							std::is_trivially_destructible<RemoveAllExtents_t>::value
					>
			{
			};

#		endif

			template <typename Tp>
			struct static_container_trivially_destructible_traits:
					static_container_trivially_destructible_traits_impl<
							typename kerbal::type_traits::remove_all_extents<Tp>::type
					>
			{
			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_STATIC_CONTAINER_TRIVIALLY_DESTRUCTIBLE_TRAITS_HPP
