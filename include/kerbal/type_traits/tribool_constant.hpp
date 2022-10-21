/**
 * @file       tribool_constant.hpp
 * @brief
 * @date       2022-10-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_TRIBOOL_CONSTANT_HPP
#define KERBAL_TYPE_TRAITS_TRIBOOL_CONSTANT_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

		template <int I>
		struct tribool_constant : kerbal::type_traits::integral_constant<int, I>
		{
				KERBAL_STATIC_ASSERT(I == -1 || I == 0 || I == 1, "I is invalid");
		};

		typedef kerbal::type_traits::tribool_constant<-1> tribool_unspecified;
		typedef kerbal::type_traits::tribool_constant<0>  tribool_false;
		typedef kerbal::type_traits::tribool_constant<1>  tribool_true;


		template <typename Arg>
		struct tribool_is_unspecified :
				kerbal::type_traits::bool_constant<Arg::value == -1>
		{
		};

		template <typename Arg>
		struct tribool_is_false :
				kerbal::type_traits::bool_constant<Arg::value == 0>
		{
		};

		template <typename Arg>
		struct tribool_is_true :
				kerbal::type_traits::bool_constant<Arg::value == 1>
		{
		};


		template <typename Arg>
		struct tribool_negation
		{
				typedef tribool_constant<
						Arg::value == -1 ? -1 : !Arg::value
				> result;
		};



#	if __cplusplus >= 201103L

		/**
		 * @details
		 *      if for all of the args, args::value is true (1):
		 *          result is true
		 *      else if for any of the args, args::value is unspecified (-1):
		 *          result is unspecified
		 *      else:
		 *          result is false
		 */
		template <typename ... Args>
		struct tribool_conjunction;

		namespace detail
		{

			// when tribool_conjunction has meet false, decide the remained
			// if unspecified exists in the remained, then the whole result of tribool_conjunction is unspecified
			// otherwise the whole result is false
			template <typename ... Args>
			struct tribool_conjunction_when_has_false;

			template <int Arg0, typename ... Args>
			struct tribool_conjunction_when_has_false_impl;


			template <>
			struct tribool_conjunction_when_has_false<>
			{
					typedef kerbal::type_traits::tribool_false result;
			};

			template <typename Arg0, typename ... Args>
			struct tribool_conjunction_when_has_false<Arg0, Args...> :
					tribool_conjunction_when_has_false_impl<Arg0::value, Args...>
			{
			};


			template <typename ... Args>
			struct tribool_conjunction_when_has_false_impl<-1, Args...>
			{
					typedef kerbal::type_traits::tribool_unspecified result;
			};

			template <typename ... Args>
			struct tribool_conjunction_when_has_false_impl<0, Args...> :
					tribool_conjunction_when_has_false<Args...>
			{
			};

			template <typename ... Args>
			struct tribool_conjunction_when_has_false_impl<1, Args...> :
					tribool_conjunction_when_has_false<Args...>
			{
			};



			template <int Arg0, typename ... Args>
			struct tribool_conjunction_impl;

			template <typename ... Args>
			struct tribool_conjunction_impl<-1, Args...>
			{
					typedef kerbal::type_traits::tribool_unspecified result;
			};

			template <typename ... Args>
			struct tribool_conjunction_impl<0, Args...> : tribool_conjunction_when_has_false<Args...>
			{
			};

			template <typename ... Args>
			struct tribool_conjunction_impl<1, Args...> : tribool_conjunction<Args...>
			{
			};

		} // namespace detail

		template <typename Arg0, typename ... Args>
		struct tribool_conjunction<Arg0, Args...> : detail::tribool_conjunction_impl<Arg0::value, Args...>
		{
		};

		template <>
		struct tribool_conjunction<>
		{
				typedef tribool_true result;
		};

#	else

#	define TRIBOOL_CONJUNCTION_ARGS_DECL_WITH_DEFAULT(i) typename KERBAL_MACRO_CONCAT(Arg, i) = kerbal::type_traits::tribool_true
#	define TRIBOOL_CONJUNCTION_ARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TRIBOOL_CONJUNCTION_ARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)

		template <typename Arg0 = kerbal::type_traits::tribool_true, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL_WITH_DEFAULT, 20)>
		struct tribool_conjunction;

		namespace detail
		{

			template <typename Arg0 = kerbal::type_traits::tribool_true, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL_WITH_DEFAULT, 20)>
			struct tribool_conjunction_when_has_false;

			template <int Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL_WITH_DEFAULT, 20)>
			struct tribool_conjunction_when_has_false_impl;


			template <typename Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL, 20)>
			struct tribool_conjunction_when_has_false :
					tribool_conjunction_when_has_false_impl<Arg0::value, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)>
			{
			};

			template <>
			struct tribool_conjunction_when_has_false<>
			{
					typedef kerbal::type_traits::tribool_false result;
			};


			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL, 20)>
			struct tribool_conjunction_when_has_false_impl<-1, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)>
			{
					typedef kerbal::type_traits::tribool_unspecified result;
			};

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL, 20)>
			struct tribool_conjunction_when_has_false_impl<0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)> :
					tribool_conjunction_when_has_false<KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)>
			{
			};

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL, 20)>
			struct tribool_conjunction_when_has_false_impl<1, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)> :
					tribool_conjunction_when_has_false<KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)>
			{
			};



			template <int Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL_WITH_DEFAULT, 20)>
			struct tribool_conjunction_impl;

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL, 20)>
			struct tribool_conjunction_impl<
					-1,
					KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)
			>
			{
				typedef kerbal::type_traits::tribool_unspecified result;
			};

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL, 20)>
			struct tribool_conjunction_impl<
					0,
					KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)
			> : tribool_conjunction_when_has_false<KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)>
			{
			};

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL, 20)>
			struct tribool_conjunction_impl<
					1,
					KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)
			> : tribool_conjunction<KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)>
			{
			};

		} // namespace detail

		template <typename Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_DECL, 20)>
		struct tribool_conjunction :
				detail::tribool_conjunction_impl<Arg0::value, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_CONJUNCTION_ARGS_USE, 20)>
		{
		};

		template <>
		struct tribool_conjunction<>
		{
				typedef kerbal::type_traits::tribool_true result;
		};

#	undef TRIBOOL_CONJUNCTION_ARGS_DECL_WITH_DEFAULT
#	undef TRIBOOL_CONJUNCTION_ARGS_DECL
#	undef TRIBOOL_CONJUNCTION_ARGS_USE

#	endif





#	if __cplusplus >= 201103L

		/**
		 * @details
		 *      if for any of args, args::value is true (1):
		 *          result is true
		 *      else if for any of the args, args::value is unspecified (-1):
		 *          result is unspecified
		 *      else:
		 *          result is false
		 */
		template <typename ... Args>
		struct tribool_disjunction;

		namespace detail
		{

			template <typename ... Args>
			struct tribool_disjunction_when_has_unspecified;

			template <int Arg0, typename ... Args>
			struct tribool_disjunction_when_has_unspecified_impl;


			template <>
			struct tribool_disjunction_when_has_unspecified<>
			{
					typedef kerbal::type_traits::tribool_unspecified result;
			};

			template <typename Arg0, typename ... Args>
			struct tribool_disjunction_when_has_unspecified<Arg0, Args...> :
					tribool_disjunction_when_has_unspecified_impl<Arg0::value, Args...>
			{
			};


			template <typename ... Args>
			struct tribool_disjunction_when_has_unspecified_impl<-1, Args...> :
					tribool_disjunction_when_has_unspecified<Args...>
			{
			};

			template <typename ... Args>
			struct tribool_disjunction_when_has_unspecified_impl<0, Args...> :
					tribool_disjunction_when_has_unspecified<Args...>
			{
			};

			template <typename ... Args>
			struct tribool_disjunction_when_has_unspecified_impl<1, Args...>
			{
					typedef kerbal::type_traits::tribool_true result;
			};



			template <int Arg0, typename ... Args>
			struct tribool_disjunction_impl;

			template <typename ... Args>
			struct tribool_disjunction_impl<-1, Args...> : tribool_disjunction_when_has_unspecified<Args...>
			{
			};

			template <>
			struct tribool_disjunction_impl<0>
			{
					typedef kerbal::type_traits::tribool_false result;
			};

			template <typename Arg1, typename ... Args>
			struct tribool_disjunction_impl<0, Arg1, Args...> : tribool_disjunction<Arg1, Args...>
			{
			};

			template <typename ... Args>
			struct tribool_disjunction_impl<1, Args...>
			{
					typedef kerbal::type_traits::tribool_true result;
			};

		} // namespace detail

		template <typename Arg0, typename ... Args>
		struct tribool_disjunction<Arg0, Args...> : detail::tribool_disjunction_impl<Arg0::value, Args...>
		{
		};

		template <>
		struct tribool_disjunction<>
		{
				typedef kerbal::type_traits::tribool_true result;
		};

#	else

#	define TRIBOOL_OR_ARGS_DECL_WITH_DEFAULT(i) typename KERBAL_MACRO_CONCAT(Arg, i) = kerbal::type_traits::tribool_false
#	define TRIBOOL_OR_ARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TRIBOOL_OR_ARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#	define TRIBOOL_OR_ARGS_ALL_FALSE(i) kerbal::type_traits::tribool_false

		template <typename Arg0 = kerbal::type_traits::tribool_true, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL_WITH_DEFAULT, 20)>
		struct tribool_disjunction;

		namespace detail
		{

			template <typename Arg0 = kerbal::type_traits::tribool_false, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL_WITH_DEFAULT, 20)>
			struct tribool_disjunction_when_has_unspecified;

			template <int Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL_WITH_DEFAULT, 20)>
			struct tribool_disjunction_when_has_unspecified_impl;


			template <typename Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL, 20)>
			struct tribool_disjunction_when_has_unspecified :
					tribool_disjunction_when_has_unspecified_impl<Arg0::value, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)>
			{
			};

			template <>
			struct tribool_disjunction_when_has_unspecified<>
			{
					typedef kerbal::type_traits::tribool_unspecified result;
			};


			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL, 20)>
			struct tribool_disjunction_when_has_unspecified_impl<-1, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)> :
					tribool_disjunction_when_has_unspecified<KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)>
			{
			};

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL, 20)>
			struct tribool_disjunction_when_has_unspecified_impl<0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)> :
					tribool_disjunction_when_has_unspecified<KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)>
			{
			};

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL, 20)>
			struct tribool_disjunction_when_has_unspecified_impl<1, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)>
			{
					typedef kerbal::type_traits::tribool_true result;
			};



			template <int Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL_WITH_DEFAULT, 20)>
			struct tribool_disjunction_impl;

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL, 20)>
			struct tribool_disjunction_impl<
					-1,
					KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)
			> : tribool_disjunction_when_has_unspecified<KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)>
			{
			};

			template <>
			struct tribool_disjunction_impl<
					0,
					KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_ALL_FALSE, 20)
			>
			{
					typedef kerbal::type_traits::tribool_false result;
			};

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL, 20)>
			struct tribool_disjunction_impl<
					0,
					KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)
			> : tribool_disjunction<KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)>
			{
			};

			template <KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL, 20)>
			struct tribool_disjunction_impl<
					1,
					KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)
			>
			{
					typedef kerbal::type_traits::tribool_true result;
			};

		} // namespace detail

		template <typename Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_DECL, 20)>
		struct tribool_disjunction :
				detail::tribool_disjunction_impl<Arg0::value, KERBAL_PPEXPAND_WITH_COMMA_N(TRIBOOL_OR_ARGS_USE, 20)>
		{
		};

		template <>
		struct tribool_disjunction<>
		{
				typedef kerbal::type_traits::tribool_true result;
		};

#	undef TRIBOOL_OR_ARGS_DECL_WITH_DEFAULT
#	undef TRIBOOL_OR_ARGS_DECL
#	undef TRIBOOL_OR_ARGS_USE
#	undef TRIBOOL_OR_ARGS_ALL_FALSE

#	endif


	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_TRIBOOL_CONSTANT_HPP
