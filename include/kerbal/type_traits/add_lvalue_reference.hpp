/**
 * @file       add_lvalue_reference.hpp
 * @brief
 * @date       2022-10-29
 * @author     Peter
 * @remark     split up from kerbal/type_traits/reference_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
#define KERBAL_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/is_referencable.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T, bool IsReferencable = kerbal::type_traits::is_referencable<T>::value>
			struct add_lvalue_reference_helper
			{
					typedef T & type;
			};

			template <typename T>
			struct add_lvalue_reference_helper<T, false>
			{
					typedef T type;
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct add_lvalue_reference :
				kerbal::type_traits::detail::add_lvalue_reference_helper<T>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct add_lvalue_reference<T &>
		{
				typedef T & type;
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
