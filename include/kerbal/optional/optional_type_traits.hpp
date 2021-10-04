/**
 * @file       optional_type_traits.hpp
 * @brief
 * @date       2018-10-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP
#define KERBAL_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP

#include <kerbal/optional/fwd/optional.fwd.hpp>

#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace optional
	{

		namespace detail
		{

			template <typename T>
			struct _K_is_optional_helper:
					kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct _K_is_optional_helper<kerbal::optional::optional<T> > :
					kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		template <typename T>
		struct is_optional:
				kerbal::optional::detail::_K_is_optional_helper<
						typename kerbal::type_traits::remove_cv<T>::type
				>
		{
		};

	} // namespace optional

} // namespace kerbal

#endif // KERBAL_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP
