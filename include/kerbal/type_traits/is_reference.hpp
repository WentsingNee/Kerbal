/**
 * @file       is_reference.hpp
 * @brief
 * @date       2022-10-29
 * @author     Peter
 * @remark     split up from kerbal/type_traits/reference_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_REFERENCE_HPP
#define KERBAL_TYPE_TRAITS_IS_REFERENCE_HPP

#include <kerbal/type_traits/is_lvalue_reference.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_rvalue_reference.hpp>
#	include <kerbal/type_traits/logical.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus < 201103L

		template <typename T>
		struct is_reference : kerbal::type_traits::is_lvalue_reference<T>
		{
		};

#	else

		template <typename T>
		struct is_reference :
			kerbal::type_traits::disjunction<
				kerbal::type_traits::is_lvalue_reference<T>,
				kerbal::type_traits::is_rvalue_reference<T>
			>
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_REFERENCE_HPP
