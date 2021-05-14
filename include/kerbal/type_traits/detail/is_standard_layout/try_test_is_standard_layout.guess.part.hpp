/**
 * @file       try_test_is_standard_layout.guess.part.hpp
 * @brief
 * @date       2023-05-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_STANDARD_LAYOUT_TRY_TEST_IS_STANDARD_LAYOUT_GUESS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_STANDARD_LAYOUT_TRY_TEST_IS_STANDARD_LAYOUT_GUESS_PART_HPP

#if KERBAL_TYPE_TRAITS_DEBUG_WARNING
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "try_test_is_standard_layout is implemented under limited speculation mode")
#	else
#		warning "Kerbal Warning: " "try_test_is_standard_layout is implemented under limited speculation mode"
#	endif
#endif


#include <kerbal/type_traits/is_scalar.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T>
			struct try_test_is_standard_layout_helper :
					kerbal::type_traits::try_test_is_scalar<T>
			{
			};

		} // namespace detail

		template <typename T>
		struct try_test_is_standard_layout :
				kerbal::type_traits::detail::try_test_is_standard_layout_helper<
					typename kerbal::type_traits::remove_all_extents<T>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_STANDARD_LAYOUT_TRY_TEST_IS_STANDARD_LAYOUT_GUESS_PART_HPP
