/**
 * @file       is_function_embedded_stored_type.hpp
 * @brief
 * @date       2023-12-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_DETAIL_IS_FUNCTION_EMBEDDED_STORED_TYPE_HPP
#define KERBAL_FUNCTION_DETAIL_IS_FUNCTION_EMBEDDED_STORED_TYPE_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_move_constructible.hpp>
#else
#	include <kerbal/type_traits/is_nothrow_copy_constructible.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace function
	{

		template <typename T, std::size_t Size, std::size_t Align>
		struct is_function_embedded_stored_type :
				kerbal::type_traits::bool_constant<
						sizeof(T) <= Size && KERBAL_ALIGNOF(T) <= Align &&
						kerbal::type_traits::tribool_is_true<
#	if __cplusplus >= 201103L
							kerbal::type_traits::try_test_is_nothrow_move_constructible
#	else
							kerbal::type_traits::try_test_is_nothrow_copy_constructible
#	endif
							<
								typename kerbal::type_traits::remove_all_extents<T>::type
							>
						>::value
				>
		{
		};

	} // namespace function

} // namespace kerbal


#endif // KERBAL_FUNCTION_DETAIL_IS_FUNCTION_EMBEDDED_STORED_TYPE_HPP
