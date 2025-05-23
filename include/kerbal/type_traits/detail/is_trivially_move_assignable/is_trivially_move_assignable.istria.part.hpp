/**
 * @file       is_trivially_move_assignable.istria.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_ASSIGNABLE_IS_TRIVIALLY_MOVE_ASSIGNABLE_ISTRIA_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_ASSIGNABLE_IS_TRIVIALLY_MOVE_ASSIGNABLE_ISTRIA_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_ASSIGNABLE

#include <kerbal/type_traits/detail/is_trivially_assignable/is_trivially_assignable.part.hpp>

#if KERBAL_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE
#	define KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_ASSIGNABLE 1
#endif



#if KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_ASSIGNABLE

#include <kerbal/type_traits/add_lvalue_reference.hpp>
#include <kerbal/type_traits/add_rvalue_reference.hpp>
#include <kerbal/type_traits/is_trivially_assignable.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_trivially_move_assignable :
			kerbal::type_traits::is_trivially_assignable<
				typename kerbal::type_traits::add_lvalue_reference<T>::type,
				typename kerbal::type_traits::add_rvalue_reference<T>::type
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_ASSIGNABLE

#endif // #ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_ASSIGNABLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_ASSIGNABLE_IS_TRIVIALLY_MOVE_ASSIGNABLE_ISTRIA_PART_HPP
