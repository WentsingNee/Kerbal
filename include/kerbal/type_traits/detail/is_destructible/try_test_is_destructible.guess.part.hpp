/**
 * @file       try_test_is_destructible.guess.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_DESTRUCTIBLE_TRY_TEST_IS_DESTRUCTIBLE_GUESS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_DESTRUCTIBLE_TRY_TEST_IS_DESTRUCTIBLE_GUESS_PART_HPP

#if KERBAL_TYPE_TRAITS_DEBUG_WARNING
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "try_test_is_destructible is implemented under limited speculation mode")
#	else
#		warning "Kerbal Warning: " "try_test_is_destructible is implemented under limited speculation mode"
#	endif
#endif


#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_enum.hpp>
#include <kerbal/type_traits/is_function.hpp>
#include <kerbal/type_traits/is_fundamental.hpp>
#include <kerbal/type_traits/is_member_pointer.hpp>
#include <kerbal/type_traits/is_pointer.hpp>
#include <kerbal/type_traits/is_reference.hpp>
#include <kerbal/type_traits/is_unbounded_array.hpp>
#include <kerbal/type_traits/is_void.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T>
			struct try_test_is_destructible_helper :
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
		struct try_test_is_destructible :
			kerbal::type_traits::conditional<
				kerbal::type_traits::tribool_disjunction<
					kerbal::type_traits::is_function<T>,
					kerbal::type_traits::is_unbounded_array<T>,
					kerbal::type_traits::is_void<T>
				>::result::IS_TRUE::value,
				kerbal::type_traits::tribool_false,
				typename kerbal::type_traits::tribool_disjunction<
					kerbal::type_traits::is_reference<T>,
					kerbal::type_traits::detail::try_test_is_destructible_helper<
						typename kerbal::type_traits::remove_all_extents<T>::type
					>
				>::result
			>::type
		{
		};


	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_DESTRUCTIBLE_TRY_TEST_IS_DESTRUCTIBLE_GUESS_PART_HPP
