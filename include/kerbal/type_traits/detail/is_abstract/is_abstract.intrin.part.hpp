/**
 * @file       is_abstract.intrin.part.hpp
 * @brief
 * @date       2023-05-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_ABSTRACT_IS_ABSTRACT_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_ABSTRACT_IS_ABSTRACT_INTRIN_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_ABSTRACT

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_PRIVATE_HAS_INTRINSIC_IS_ABSTRACT
#	define KERBAL_SUPPORTS_IS_ABSTRACT 1
#endif


#if KERBAL_SUPPORTS_IS_ABSTRACT

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_abstract :
			kerbal::type_traits::bool_constant<KERBAL_INTRINSIC_IS_ABSTRACT(T)>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_ABSTRACT

#endif // #ifndef KERBAL_SUPPORTS_IS_ABSTRACT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ABSTRACT_IS_ABSTRACT_INTRIN_PART_HPP
