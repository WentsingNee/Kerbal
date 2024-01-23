/**
 * @file       try_test_is_abstract.guess.part.hpp
 * @brief
 * @date       2023-05-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_ABSTRACT_TRY_TEST_IS_ABSTRACT_GUESS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_ABSTRACT_TRY_TEST_IS_ABSTRACT_GUESS_PART_HPP

#if KERBAL_TYPE_TRAITS_DEBUG_WARNING
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "try_test_is_abstract is implemented under limited speculation mode")
#	else
#		warning "Kerbal Warning: " "try_test_is_abstract is implemented under limited speculation mode"
#	endif
#endif


#include <kerbal/type_traits/detail/is_enum/is_enum.part.hpp>
#include <kerbal/type_traits/detail/is_union/is_union.part.hpp>

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_class.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct try_test_is_abstract :
				kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_class<T>::IS_FALSE::value,
					kerbal::type_traits::tribool_false,
					kerbal::type_traits::tribool_unspecified
				>::type
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ABSTRACT_TRY_TEST_IS_ABSTRACT_GUESS_PART_HPP
