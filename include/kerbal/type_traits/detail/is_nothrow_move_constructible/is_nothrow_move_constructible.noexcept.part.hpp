/**
 * @file       is_nothrow_move_constructible.noexcept.part.hpp
 * @brief
 * @date       2023-08-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_MOVE_CONSTRUCTIBLE_IS_NOTHROW_MOVE_CONSTRUCTIBLE_NOEXCEPT_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_MOVE_CONSTRUCTIBLE_IS_NOTHROW_MOVE_CONSTRUCTIBLE_NOEXCEPT_PART_HPP

#ifndef KERBAL_HAS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_SUPPORT

#include <kerbal/config/exceptions.hpp>

#if !KERBAL_HAS_EXCEPTIONS_SUPPORT

#include <kerbal/type_traits/detail/is_move_constructible/is_move_constructible.part.hpp>

#if KERBAL_HAS_IS_MOVE_CONSTRUCTIBLE_SUPPORT


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_nothrow_move_constructible :
				kerbal::type_traits::is_move_constructible<T>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#define KERBAL_HAS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_SUPPORT 1

#endif // #if KERBAL_HAS_IS_MOVE_CONSTRUCTIBLE_SUPPORT

#endif // #if !KERBAL_HAS_EXCEPTIONS_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_MOVE_CONSTRUCTIBLE_IS_NOTHROW_MOVE_CONSTRUCTIBLE_NOEXCEPT_PART_HPP
