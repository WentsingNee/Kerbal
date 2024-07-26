/**
 * @file       is_optional.hpp
 * @brief
 * @date       2018-10-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_IS_OPTIONAL_HPP
#define KERBAL_OPTIONAL_IS_OPTIONAL_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/optional/optional/optional.fwd.hpp>

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_cv.hpp>


namespace kerbal
{

	namespace optional
	{

		namespace detail
		{

			template <typename T>
			struct k_is_optional_helper:
				kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct k_is_optional_helper<kerbal::optional::optional<T> > :
				kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_optional:
			kerbal::optional::detail::k_is_optional_helper<
				typename kerbal::type_traits::remove_cv<T>::type
			>
		{
		};

	} // namespace optional

} // namespace kerbal

#endif // KERBAL_OPTIONAL_IS_OPTIONAL_HPP
