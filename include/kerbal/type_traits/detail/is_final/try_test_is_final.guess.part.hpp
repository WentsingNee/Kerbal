/**
 * @file       try_test_is_final.guess.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_FINAL_TRY_TEST_IS_FINAL_GUESS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_FINAL_TRY_TEST_IS_FINAL_GUESS_PART_HPP

#if KERBAL_TYPE_TRAITS_DEBUG_WARNING
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "try_test_is_final is implemented under limited speculation mode")
#	else
#		warning "Kerbal Warning: " "try_test_is_final is implemented under limited speculation mode"
#	endif
#endif


#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_class.hpp>
#include <kerbal/type_traits/is_union.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct try_test_is_final :
			kerbal::type_traits::conditional<
				typename kerbal::type_traits::tribool_disjunction<
					kerbal::type_traits::try_test_is_class<T>,
					kerbal::type_traits::try_test_is_union<T>
				>::result::IS_FALSE::value,
				kerbal::type_traits::tribool_false,
				kerbal::type_traits::tribool_unspecified
			>::type
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_FINAL_TRY_TEST_IS_FINAL_GUESS_PART_HPP
