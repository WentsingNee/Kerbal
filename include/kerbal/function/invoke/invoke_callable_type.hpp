/**
 * @file       invoke_callable_type.hpp
 * @brief
 * @date       2023-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_INVOKE_CALLABLE_TYPE_HPP
#define KERBAL_FUNCTION_INVOKE_INVOKE_CALLABLE_TYPE_HPP

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_member_function_pointer.hpp>
#include <kerbal/type_traits/is_member_object_pointer.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>


namespace kerbal
{

	namespace function
	{

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> INVOKE_OVERLOAD_VER_CALLABLE;
			typedef kerbal::type_traits::integral_constant<int, 1> INVOKE_OVERLOAD_VER_MEM_OBJ;
			typedef kerbal::type_traits::integral_constant<int, 2> INVOKE_OVERLOAD_VER_MEM_FUN;

			template <typename Fun, typename ... Args>
			struct invoke_overload_selector;

			template <typename Fun>
			struct invoke_overload_selector<Fun>
			{
					typedef INVOKE_OVERLOAD_VER_CALLABLE type;
			};

			template <typename Arg0, typename Arg1, typename ... Args>
			struct invoke_overload_selector<Arg0, Arg1, Args...>
			{
				private:
					typedef typename kerbal::type_traits::remove_cvref<Arg0>::type arg0_remove_cvref_type;

				public:
					typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::is_member_object_pointer<arg0_remove_cvref_type>::value,
						INVOKE_OVERLOAD_VER_MEM_OBJ,
						typename kerbal::type_traits::conditional<
							kerbal::type_traits::is_member_function_pointer<arg0_remove_cvref_type>::value,
							INVOKE_OVERLOAD_VER_MEM_FUN,
							INVOKE_OVERLOAD_VER_CALLABLE
						>::type
					>::type type;
			};

		} // namespace detail

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_INVOKE_CALLABLE_TYPE_HPP
