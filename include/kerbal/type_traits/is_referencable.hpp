/**
 * @file       is_referencable.hpp
 * @brief
 * @date       2022-10-29
 * @author     Peter
 * @remark     split up from kerbal/type_traits/reference_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_REFERENCABLE_HPP
#define KERBAL_TYPE_TRAITS_IS_REFERENCABLE_HPP

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <
				typename T,
				typename = kerbal::type_traits::void_type<>::type
			>
			struct is_referencable_helper :
				kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct is_referencable_helper<
				T,
				typename kerbal::type_traits::void_type<T &>::type
			> :
				kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		template <typename T>
		struct is_referencable :
			kerbal::type_traits::detail::is_referencable_helper<T>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_REFERENCABLE_HPP
