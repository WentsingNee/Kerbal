/**
 * @file       use_args.cxx98.part.hpp
 * @brief
 * @date       2024-10-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_USE_ARGS_USE_ARGS_CXX98_PART_HPP
#define KERBAL_UTILITY_USE_ARGS_USE_ARGS_CXX98_PART_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/macro/macro_concat.hpp>
#include <kerbal/macro/ppexpand.hpp>
#include <kerbal/type_traits/remove_cv.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/tuple.hpp>


namespace kerbal
{

	namespace utility
	{

#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i) = kerbal::tmp::tppter

		template <KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_DECL, 20)> \
		class use_args_t;

#	undef TARGS_DECL


#	define EMPTY
#	define REMAINF(exp) exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)


#	define DBODY(i) \
		template <KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_DECL, i)> \
		struct use_args_t<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> : \
			public kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> \
		{ \
		}; \

		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef REMAINF
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef DBODY

/*
		template <typename ... Args>
		KERBAL_CONSTEXPR14
		use_args_t<typename kerbal::type_traits::remove_cvref<Args>::type...>
		use_args(Args && ... args)
		{
			return use_args_t<typename kerbal::type_traits::remove_cvref<Args>::type...>{
				kerbal::utility::forward<Args>(args)...
			};
		}
*/


		namespace detail
		{

			template <typename T>
			struct is_use_args_t_impl :
				kerbal::type_traits::false_type
			{
			};

/*
			template <typename ... Args>
			struct is_use_args_t_impl<kerbal::utility::use_args_t<Args...> > :
				kerbal::type_traits::true_type
			{
			};
*/

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

#endif // KERBAL_UTILITY_USE_ARGS_USE_ARGS_CXX98_PART_HPP
