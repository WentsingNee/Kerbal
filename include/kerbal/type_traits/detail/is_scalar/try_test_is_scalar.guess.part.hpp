/**
 * @file       try_test_is_scalar.guess.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_SCALAR_TRY_TEST_IS_SCALAR_GUESS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_SCALAR_TRY_TEST_IS_SCALAR_GUESS_PART_HPP

#if KERBAL_TYPE_TRAITS_DEBUG_WARNING
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "try_test_is_scalar is implemented under limited speculation mode")
#	else
#		warning "Kerbal Warning: " "try_test_is_scalar is implemented under limited speculation mode"
#	endif
#endif


#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_array.hpp>
#include <kerbal/type_traits/is_arithmetic.hpp>
#include <kerbal/type_traits/is_enum.hpp>
#include <kerbal/type_traits/is_member_pointer.hpp>
#include <kerbal/type_traits/is_pointer.hpp>
#include <kerbal/type_traits/is_reference.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_null_pointer.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct try_test_is_scalar :
				kerbal::type_traits::conditional<
					kerbal::type_traits::disjunction<
						kerbal::type_traits::is_arithmetic<T>,
						kerbal::type_traits::is_member_pointer<T>,
#				if __cplusplus >= 201103L
						kerbal::type_traits::is_null_pointer<T>,
#				endif
						kerbal::type_traits::is_pointer<T>
					>::value,
					kerbal::type_traits::tribool_true,
					typename kerbal::type_traits::conditional<
						kerbal::type_traits::disjunction<
							kerbal::type_traits::is_array<T>,
							kerbal::type_traits::is_reference<T>
						>::value,
						kerbal::type_traits::tribool_false,
						kerbal::type_traits::try_test_is_enum<T>
					>::type
				>::type
		{
		};


	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_SCALAR_TRY_TEST_IS_SCALAR_GUESS_PART_HPP
