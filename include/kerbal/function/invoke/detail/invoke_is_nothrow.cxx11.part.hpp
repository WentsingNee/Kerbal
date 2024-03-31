/**
 * @file       invoke_is_nothrow.cxx11.part.hpp
 * @brief
 * @date       2023-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_IS_NOTHROW_CXX11_PART_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_IS_NOTHROW_CXX11_PART_HPP

#include <kerbal/function/invoke/invoke_overload_ver_selector.hpp>

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/reference_wrapper.hpp>


namespace kerbal
{

	namespace function
	{

		namespace detail
		{

			template <typename Ver, typename Fun, typename ... Args>
			struct invoke_is_nothrow_helper;

			template <typename Fun, typename ... Args>
			struct invoke_is_nothrow_helper<INVOKE_OVERLOAD_VER_CALLABLE, Fun, Args...>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							kerbal::utility::declval<Fun>()(kerbal::utility::declval<Args>()...)
						)
					> type;
			};

			template <typename MemObjPtr, typename T, typename ... Args>
			struct invoke_is_nothrow_helper<INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr, T, Args...>
			{
					typedef kerbal::type_traits::true_type type;
			};

			template <typename MemFunPtr, typename TOri, typename T, typename ... Args>
			struct invoke_is_nothrow_helper_of_mem_fun
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							(kerbal::utility::declval<TOri>().*kerbal::utility::declval<MemFunPtr>())
								(kerbal::utility::declval<Args>()...)
						)
					> type;
			};

			template <typename MemFunPtr, typename TOri, typename T, typename ... Args>
			struct invoke_is_nothrow_helper_of_mem_fun<MemFunPtr, TOri, T *, Args...>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							(kerbal::utility::declval<TOri>()->*kerbal::utility::declval<MemFunPtr>())
								(kerbal::utility::declval<Args>()...)
						)
					> type;
			};

			template <typename MemFunPtr, typename TOri, typename T, typename ... Args>
			struct invoke_is_nothrow_helper_of_mem_fun<MemFunPtr, TOri, kerbal::utility::reference_wrapper<T>, Args...>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							(kerbal::utility::declval<TOri>().get().*kerbal::utility::declval<MemFunPtr>())
								(kerbal::utility::declval<Args>()...)
						)
					> type;
			};

			template <typename MemFunPtr, typename T, typename ... Args>
			struct invoke_is_nothrow_helper<INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr, T, Args...> :
					invoke_is_nothrow_helper_of_mem_fun<
						MemFunPtr,
						T, typename kerbal::type_traits::remove_cvref<T>::type,
						Args...
					>
			{
			};

		} // namespace detail


		template <typename Fun, typename ... Args>
		struct invoke_is_nothrow :
				kerbal::function::detail::invoke_is_nothrow_helper<
					typename kerbal::function::detail::invoke_overload_ver_selector<Fun, Args...>::type, Fun, Args...
				>::type
		{
		};

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_IS_NOTHROW_CXX11_PART_HPP
