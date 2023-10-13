/**
 * @file       invoke_overload_ver_selector.cxx11.part.hpp
 * @brief
 * @date       2023-10-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_OVERLOAD_VER_SELECTOR_CXX11_PART_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_OVERLOAD_VER_SELECTOR_CXX11_PART_HPP

#include <kerbal/function/invoke/detail/invoke_overload_ver.hpp>

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_member_function_pointer.hpp>
#include <kerbal/type_traits/is_member_object_pointer.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>


namespace kerbal
{

	namespace function
	{

		namespace detail
		{

			template <typename Fun, typename ... Args>
			struct invoke_overload_ver_selector;

			template <typename Fun>
			struct invoke_overload_ver_selector<Fun>
			{
					typedef kerbal::function::detail::INVOKE_OVERLOAD_VER_CALLABLE type;
			};

			template <typename Arg0, typename Arg1, typename ... Args>
			struct invoke_overload_ver_selector<Arg0, Arg1, Args...>
			{
				private:
					typedef typename kerbal::type_traits::remove_cvref<Arg0>::type arg0_remove_cvref_type;

				public:
					typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::is_member_object_pointer<arg0_remove_cvref_type>::value,
						kerbal::function::detail::INVOKE_OVERLOAD_VER_MEM_OBJ,
						typename kerbal::type_traits::conditional<
							kerbal::type_traits::is_member_function_pointer<arg0_remove_cvref_type>::value,
							kerbal::function::detail::INVOKE_OVERLOAD_VER_MEM_FUN,
							kerbal::function::detail::INVOKE_OVERLOAD_VER_CALLABLE
						>::type
					>::type type;
			};

		} // namespace detail

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_OVERLOAD_VER_SELECTOR_CXX11_PART_HPP
