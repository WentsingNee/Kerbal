/**
 * @file       try_test_is_trivially_move_assignable.guess.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_ASSIGNABLE_TRY_TEST_IS_TRIVIALLY_MOVE_ASSIGNABLE_GUESS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_ASSIGNABLE_TRY_TEST_IS_TRIVIALLY_MOVE_ASSIGNABLE_GUESS_PART_HPP

#if KERBAL_TYPE_TRAITS_DEBUG_WARNING
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "try_test_is_trivially_move_assignable is implemented under limited speculation mode")
#	else
#		warning "Kerbal Warning: " "try_test_is_trivially_move_assignable is implemented under limited speculation mode"
#	endif
#endif


#include <kerbal/type_traits/is_enum.hpp>
#include <kerbal/type_traits/is_fundamental.hpp>
#include <kerbal/type_traits/is_member_pointer.hpp>
#include <kerbal/type_traits/is_move_assignable.hpp>
#include <kerbal/type_traits/is_pointer.hpp>
#include <kerbal/type_traits/remove_reference.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T>
			struct try_test_is_trivially_move_assignable_helper :
					kerbal::type_traits::tribool_disjunction<
						kerbal::type_traits::try_test_is_enum<T>,
						kerbal::type_traits::is_fundamental<T>,
						kerbal::type_traits::is_member_pointer<T>,
						kerbal::type_traits::is_pointer<T>,
						kerbal::type_traits::tribool_unspecified
					>::result
			{
			};

		} // namespace detail


		template <typename T>
		struct try_test_is_trivially_move_assignable :
				kerbal::type_traits::tribool_conjunction<
					kerbal::type_traits::try_test_is_move_assignable<T>,
					kerbal::type_traits::detail::try_test_is_trivially_move_assignable_helper<
						typename kerbal::type_traits::remove_reference<T>::type
					>
				>::result
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_ASSIGNABLE_TRY_TEST_IS_TRIVIALLY_MOVE_ASSIGNABLE_GUESS_PART_HPP
