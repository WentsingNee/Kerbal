/**
 * @file       try_test_is_assignable.guess.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_TRY_TEST_IS_ASSIGNABLE_GUESS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_TRY_TEST_IS_ASSIGNABLE_GUESS_PART_HPP

#if KERBAL_TYPE_TRAITS_DEBUG_WARNING
#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "try_test_is_assignable is implemented under limited speculation mode")
#	else
#		warning "Kerbal Warning: " "try_test_is_assignable is implemented under limited speculation mode"
#	endif
#endif


#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <typename T, typename U>
		struct try_test_is_assignable :
			kerbal::type_traits::tribool_unspecified
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_TRY_TEST_IS_ASSIGNABLE_GUESS_PART_HPP
