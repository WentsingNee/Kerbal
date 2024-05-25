/**
 * @file       invoke_overload_ver_selector.cxx98.part.hpp
 * @brief
 * @date       2023-10-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_OVERLOAD_VER_SELECTOR_CXX98_PART_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_OVERLOAD_VER_SELECTOR_CXX98_PART_HPP

#include <kerbal/function/invoke/detail/invoke_overload_ver.hpp>

#include <kerbal/tmp/tppter.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_member_function_pointer.hpp>
#include <kerbal/type_traits/is_member_object_pointer.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>

#include <kerbal/macro/macro_concat.hpp>
#include <kerbal/macro/ppexpand.hpp>


namespace kerbal
{

	namespace function
	{

		namespace detail
		{


#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) typename = kerbal::tmp::tppter

			template <
				typename Fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, 20),
				typename = kerbal::tmp::tppter
			>
			struct invoke_overload_ver_selector;

#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL

			template <typename Fun>
			struct invoke_overload_ver_selector<Fun>
			{
					typedef kerbal::function::detail::INVOKE_OVERLOAD_VER_CALLABLE type;
			};

#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Args, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Args, i)
#	define TBODY(i) \
			template <typename Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_DECL, i)> \
			struct invoke_overload_ver_selector<Arg0, KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_USE, i)> \
			{ \
				private: \
					typedef typename kerbal::type_traits::remove_cvref<Arg0>::type arg0_remove_cvref_type; \
 \
				public: \
					typedef typename kerbal::type_traits::conditional< \
						kerbal::type_traits::is_member_object_pointer<arg0_remove_cvref_type>::value, \
						kerbal::function::detail::INVOKE_OVERLOAD_VER_MEM_OBJ, \
						typename kerbal::type_traits::conditional< \
							kerbal::type_traits::is_member_function_pointer<arg0_remove_cvref_type>::value, \
							kerbal::function::detail::INVOKE_OVERLOAD_VER_MEM_FUN, \
							kerbal::function::detail::INVOKE_OVERLOAD_VER_CALLABLE \
						>::type \
					>::type type; \
			}; \

			KERBAL_PPEXPAND_N(TBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef TARGS_DECL
#	undef TARGS_USE
#	undef TBODY

		} // namespace detail

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_OVERLOAD_VER_SELECTOR_CXX98_PART_HPP
