/**
 * @file       is_constructible.sfinae98.part.hpp
 * @brief
 * @date       2023-05-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_IS_CONSTRUCTIBLE_SFINAE98_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_IS_CONSTRUCTIBLE_SFINAE98_PART_HPP

#ifndef KERBAL_HAS_IS_CONSTRUCTIBLE_SUPPORT

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC
#	define KERBAL_HAS_IS_CONSTRUCTIBLE_SUPPORT 1
#endif



#if KERBAL_HAS_IS_CONSTRUCTIBLE_SUPPORT

#include <kerbal/macro/macro_concat.hpp>
#include <kerbal/macro/ppexpand.hpp>
#include <kerbal/tmp/tppter.hpp>

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_unbounded_array.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_reference.hpp>
#include <kerbal/type_traits/yes_no_type.hpp>
#include <kerbal/utility/declval.hpp>

#include <new>
#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE2(i) kerbal::utility::declval<KERBAL_MACRO_CONCAT(Arg, i)>()
#	define TARGS_USE3(i) typename kerbal::type_traits::remove_reference<KERBAL_MACRO_CONCAT(Arg, i)>::type *

#	define TBODY(i) \
			template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			struct KERBAL_MACRO_CONCAT(is_constructible_helper_, i) \
			{ \
				private: \
					template <typename T2> \
					static kerbal::type_traits::no_type test(...); \
 \
					template <typename T2> \
					static kerbal::type_traits::yes_type test(char(*)[sizeof( \
						new (kerbal::utility::declval<void *>()) T2(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE2, i)), \
						0 \
					)]); \
 \
				public: \
					typedef kerbal::type_traits::bool_constant< \
						sizeof(test<T>(NULL)) == sizeof(kerbal::type_traits::yes_type) \
					> type; \
			}; \
 \
			template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			struct KERBAL_MACRO_CONCAT(is_constructible_helper_, i)<T & KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)> \
			{ \
					typedef kerbal::type_traits::conjunction< \
						kerbal::type_traits::bool_constant<i == 1>, \
						typename KERBAL_MACRO_CONCAT(is_constructible_helper_, i)<T * KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE3, i)>::type \
					> type; \
			}; \

			KERBAL_PPEXPAND_N(TBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(TBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef TARGS_USE2
#	undef TARGS_USE3
#	undef TBODY

		} // namespace detail


#	define EMPTY
#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i) = kerbal::tmp::tppter
#	define TARGS_DECL2(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)

		template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, 20), typename = kerbal::tmp::tppter>
		struct is_constructible;

#	define TBODY(i) \
		template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL2, i)> \
		struct is_constructible<T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)> : \
			kerbal::type_traits::conjunction< \
				kerbal::type_traits::negation< \
					kerbal::type_traits::is_unbounded_array<T> \
				>, \
				typename kerbal::type_traits::detail::KERBAL_MACRO_CONCAT(is_constructible_helper_, i)<T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)>::type \
			> \
		{ \
		}; \

		KERBAL_PPEXPAND_N(TBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(TBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL
#	undef TARGS_DECL2
#	undef TARGS_USE
#	undef TBODY

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_HAS_IS_CONSTRUCTIBLE_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_CONSTRUCTIBLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_IS_CONSTRUCTIBLE_SFINAE98_PART_HPP
