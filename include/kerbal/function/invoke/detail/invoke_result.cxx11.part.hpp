/**
 * @file       invoke_result.cxx11.part.hpp
 * @brief
 * @date       2023-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_RESULT_CXX11_PART_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_RESULT_CXX11_PART_HPP

#include <kerbal/function/invoke/invoke_overload_ver_selector.hpp>
#include <kerbal/function/invoke/is_invocable.hpp>
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
			struct invoke_result_helper;

			/*
			 * f()
			 */
			template <typename Fun, typename ... Args>
			struct invoke_result_helper<
				INVOKE_OVERLOAD_VER_CALLABLE,
				Fun, Args...
			>
			{
					typedef decltype(
						kerbal::utility::declval<Fun>()(kerbal::utility::declval<Args>()...)
					) type;
			};


			/*
			 * obj.*mem
			 */
			template <typename MemObjPtr, typename TOri, typename T>
			struct invoke_result_helper_of_mem_obj
			{
					typedef decltype(
						kerbal::utility::declval<TOri>().*(kerbal::utility::declval<MemObjPtr>())
					) type;
			};

			/*
			 * obj->*mem
			 */
			template <typename MemObjPtr, typename TOri, typename T>
			struct invoke_result_helper_of_mem_obj<
				MemObjPtr,
				TOri, T *
			>
			{
					typedef decltype(
						kerbal::utility::declval<TOri>()->*(kerbal::utility::declval<MemObjPtr>())
					) type;
			};

			/*
			 * obj.get().*mem
			 */
			template <typename MemObjPtr, typename TOri, typename T>
			struct invoke_result_helper_of_mem_obj<
				MemObjPtr,
				TOri, kerbal::utility::reference_wrapper<T>
			>
			{
					typedef decltype(
						kerbal::utility::declval<TOri>().get().*(kerbal::utility::declval<MemObjPtr>())
					) type;
			};

			template <typename MemObjPtr, typename T, typename ... Args>
			struct invoke_result_helper<
				INVOKE_OVERLOAD_VER_MEM_OBJ,
				MemObjPtr, T, Args...
			> :
				invoke_result_helper_of_mem_obj<
					MemObjPtr,
					T, typename kerbal::type_traits::remove_cvref<T>::type,
					Args...
				>
			{
			};


			/*
			 * obj.*mem()
			 */
			template <typename MemFunPtr, typename TOri, typename T, typename ... Args>
			struct invoke_result_helper_of_mem_fun
			{
					typedef decltype(
						(kerbal::utility::declval<TOri>().*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...)
					) type;
			};

			/*
			 * obj->*mem()
			 */
			template <typename MemFunPtr, typename TOri, typename T, typename ... Args>
			struct invoke_result_helper_of_mem_fun<
				MemFunPtr,
				TOri, T *, Args...
			>
			{
					typedef decltype(
						(kerbal::utility::declval<TOri>()->*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...)
					) type;
			};

			/*
			 * obj.get().*mem()
			 */
			template <typename MemFunPtr, typename TOri, typename T, typename ... Args>
			struct invoke_result_helper_of_mem_fun<
				MemFunPtr,
				TOri, kerbal::utility::reference_wrapper<T>, Args...
			>
			{
					typedef decltype(
						(kerbal::utility::declval<TOri>().get().*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...)
					) type;
			};

			template <typename MemFunPtr, typename T, typename ... Args>
			struct invoke_result_helper<
				INVOKE_OVERLOAD_VER_MEM_FUN,
				MemFunPtr, T, Args...
			> :
				invoke_result_helper_of_mem_fun<
					MemFunPtr,
					T, typename kerbal::type_traits::remove_cvref<T>::type,
					Args...
				>
			{
			};


			template <bool IsInvocable, typename Fun, typename ... Args>
			struct invoke_result_impl
			{
			};

			template <typename Fun, typename ... Args>
			struct invoke_result_impl<true, Fun, Args...> :
				kerbal::function::detail::invoke_result_helper<
					typename kerbal::function::detail::invoke_overload_ver_selector<Fun, Args...>::type, Fun, Args...
				>
			{
			};
	
		} // namespace detail


		template <typename Fun, typename ... Args>
		struct invoke_result :
			kerbal::function::detail::invoke_result_impl<
				kerbal::function::is_invocable<Fun, Args...>::value,
				Fun, Args...
			>
		{
		};
		
	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_RESULT_CXX11_PART_HPP
