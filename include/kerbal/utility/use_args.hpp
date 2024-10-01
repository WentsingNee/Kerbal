/**
 * @file       use_args.hpp
 * @brief
 * @date       2024-10-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_USE_ARGS_HPP
#define KERBAL_UTILITY_USE_ARGS_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/type_traits/remove_cv.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/tuple.hpp>


namespace kerbal
{

	namespace utility
	{

		template <typename ... Args>
		class use_args_t :
			public kerbal::utility::tuple<Args...>
		{
			private:
				using super = kerbal::utility::tuple<Args...>;
			public:
				using super::super;
		};

		template <typename ... Args>
		KERBAL_CONSTEXPR14
		use_args_t<typename kerbal::type_traits::remove_cvref<Args>::type...>
		use_args(Args && ... args)
		{
			return use_args_t<typename kerbal::type_traits::remove_cvref<Args>::type...>{
				kerbal::utility::forward<Args>(args)...
			};
		}


		namespace detail
		{

			template <typename T>
			struct is_use_args_t_impl :
				kerbal::type_traits::false_type
			{
			};

			template <typename ... Args>
			struct is_use_args_t_impl<kerbal::utility::use_args_t<Args...> > :
				kerbal::type_traits::true_type
			{
			};

		} // namespace detail


		template <typename T>
		struct is_use_args_t :
			kerbal::utility::detail::is_use_args_t_impl<
				typename kerbal::type_traits::remove_cv<T>::type
			>
		{
		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_USE_ARGS_HPP
