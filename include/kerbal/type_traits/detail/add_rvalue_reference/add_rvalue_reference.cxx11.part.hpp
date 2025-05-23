/**
 * @file       add_rvalue_reference.cxx11.part.hpp
 * @brief
 * @date       2022-10-29
 * @author     Peter
 * @remark     split up from kerbal/type_traits/reference_deduction.hpp, 2019-4-29
 *             move from kerbal/type_traits/add_rvalue_reference.hpp, 2023-08-25
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_ADD_RVALUE_REFERENCE_ADD_RVALUE_REFERENCE_CXX11_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_ADD_RVALUE_REFERENCE_ADD_RVALUE_REFERENCE_CXX11_PART_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif

#include <kerbal/type_traits/is_referencable.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T, bool IsReferencable = kerbal::type_traits::is_referencable<T>::value>
			struct add_rvalue_reference_helper
			{
					typedef T && type;
			};

			template <typename T>
			struct add_rvalue_reference_helper<T, false>
			{
					typedef T type;
			};

		} // namespace detail

		template <typename T>
		struct add_rvalue_reference :
			kerbal::type_traits::detail::add_rvalue_reference_helper<T>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_ADD_RVALUE_REFERENCE_ADD_RVALUE_REFERENCE_CXX11_PART_HPP
