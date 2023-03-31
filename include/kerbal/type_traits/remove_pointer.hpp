/**
 * @file       remove_pointer.hpp
 * @brief
 * @date       2022-10-30
 * @author     Peter
 * @remark     split up from kerbal/type_traits/pointer_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REMOVE_POINTER_HPP
#define KERBAL_TYPE_TRAITS_REMOVE_POINTER_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/remove_cv.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T, typename >
			struct remove_pointer_helper
			{
					typedef T type;
			};

			template <typename T, typename U>
			struct remove_pointer_helper<T, U*>
			{
					typedef U type;
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct remove_pointer :
				kerbal::type_traits::detail::remove_pointer_helper<
					T, typename kerbal::type_traits::remove_cv<T>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_REMOVE_POINTER_HPP
