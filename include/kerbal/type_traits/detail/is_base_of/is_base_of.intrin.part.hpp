/**
 * @file       is_base_of.intrin.part.hpp
 * @brief
 * @date       2023-04-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_IS_BASE_OF_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_IS_BASE_OF_INTRIN_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_BASE_OF

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_PRIVATE_HAS_INTRINSIC_IS_BASE_OF
#	define KERBAL_SUPPORTS_IS_BASE_OF 1
#endif



#if KERBAL_SUPPORTS_IS_BASE_OF

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename Base, typename Derived>
		struct is_base_of :
			kerbal::type_traits::bool_constant<
				KERBAL_INTRINSIC_IS_BASE_OF(Base, Derived)
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_BASE_OF

#endif // #ifndef KERBAL_SUPPORTS_IS_BASE_OF

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_IS_BASE_OF_INTRIN_PART_HPP
