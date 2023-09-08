/**
 * @file       add_pointer.hpp
 * @brief
 * @date       2022-10-30
 * @author     Peter
 * @remark     split up from kerbal/type_traits/pointer_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_ADD_POINTER_HPP
#define KERBAL_TYPE_TRAITS_ADD_POINTER_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/type_traits/is_referencable.hpp>
#include <kerbal/type_traits/is_void.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_reference.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T, bool IsPointerable>
			struct add_pointer_impl;

			template <typename T>
			struct add_pointer_impl<T, false>
			{
					typedef T type;
			};

			template <typename T>
			struct add_pointer_impl<T, true>
			{
					typedef T * type;
			};

			template <typename T>
			struct add_pointer_helper :
				add_pointer_impl<
					T,
					kerbal::type_traits::disjunction<
						kerbal::type_traits::is_referencable<T>,
						kerbal::type_traits::is_void<T>
					>::value
				>
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct add_pointer :
			kerbal::type_traits::detail::add_pointer_helper<
				typename kerbal::type_traits::remove_reference<T>::type
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_ADD_POINTER_HPP
