/**
 * @file       try_test_is_base_of.guess.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_TRY_TEST_IS_BASE_OF_GUESS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_TRY_TEST_IS_BASE_OF_GUESS_PART_HPP

#if KERBAL_TYPE_TRAITS_DEBUG_WARNING
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "try_test_is_base_of is implemented under limited speculation mode")
#	else
#		warning "Kerbal Warning: " "try_test_is_base_of is implemented under limited speculation mode"
#	endif
#endif


#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_class.hpp>
#include <kerbal/type_traits/is_final.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/remove_cv.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename Base, typename Derived>
			struct try_test_is_base_of_impl :
				kerbal::type_traits::conditional<
					kerbal::type_traits::tribool_conjunction<
						kerbal::type_traits::try_test_is_class<Base>,
						kerbal::type_traits::try_test_is_class<Derived>
					>::result::IS_TRUE::value,
					typename kerbal::type_traits::conditional<
						kerbal::type_traits::is_same<Base, Derived>::value,
						kerbal::type_traits::tribool_true,
						typename kerbal::type_traits::conditional<
							kerbal::type_traits::try_test_is_final<Base>::IS_TRUE::value,
							kerbal::type_traits::tribool_false,
							kerbal::type_traits::tribool_unspecified
						>::type
					>::type,
					kerbal::type_traits::tribool_false
				>::type
			{
			};

		} // namespace detail

		template <typename Base, typename Derived>
		struct try_test_is_base_of :
			kerbal::type_traits::detail::try_test_is_base_of_impl<
				typename kerbal::type_traits::remove_cv<Base>::type,
				typename kerbal::type_traits::remove_cv<Derived>::type
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_TRY_TEST_IS_BASE_OF_GUESS_PART_HPP
