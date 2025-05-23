/**
 * @file       try_test_is_union.guess.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_UNION_TRY_TEST_IS_UNION_GUESS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_UNION_TRY_TEST_IS_UNION_GUESS_PART_HPP

#if KERBAL_TYPE_TRAITS_DEBUG_WARNING
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "try_test_is_union is implemented under limited speculation mode")
#	else
#		warning "Kerbal Warning: " "try_test_is_union is implemented under limited speculation mode"
#	endif
#endif


#include <kerbal/type_traits/detail/is_class/is_class.part.hpp>
#include <kerbal/type_traits/detail/is_enum/is_enum.part.hpp>

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_array.hpp>
#include <kerbal/type_traits/is_fundamental.hpp>
#include <kerbal/type_traits/is_member_pointer.hpp>
#include <kerbal/type_traits/is_pointer.hpp>
#include <kerbal/type_traits/is_reference.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct try_test_is_union :
			kerbal::type_traits::conditional<
				kerbal::type_traits::disjunction<
#		if KERBAL_SUPPORTS_IS_CLASS
					kerbal::type_traits::is_class<T>,
#		endif
#		if KERBAL_SUPPORTS_IS_ENUM
					kerbal::type_traits::is_enum<T>,
#		endif
					kerbal::type_traits::is_array<T>,
					kerbal::type_traits::is_fundamental<T>,
					kerbal::type_traits::is_member_pointer<T>,
					kerbal::type_traits::is_pointer<T>,
					kerbal::type_traits::is_reference<T>
				>::value,
				kerbal::type_traits::tribool_false,
				kerbal::type_traits::tribool_unspecified
			>::type
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_UNION_TRY_TEST_IS_UNION_GUESS_PART_HPP
