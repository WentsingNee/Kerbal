/**
 * @file       invoke_r_is_nothrow.cxx11.part.hpp
 * @brief
 * @date       2023-08-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_R_IS_NOTHROW_CXX11_PART_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_R_IS_NOTHROW_CXX11_PART_HPP

#include <kerbal/function/invoke/invoke_overload_ver_selector.hpp>

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_pointer.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/reference_wrapper.hpp>


namespace kerbal
{

	namespace function
	{

		namespace detail
		{

			template <typename T>
			struct invoke_r_object_type_not_reference_wrapper :
					kerbal::type_traits::conditional<
						kerbal::type_traits::is_pointer<T>::value,
						kerbal::type_traits::integral_constant<int, 1>,
						kerbal::type_traits::integral_constant<int, 0>
					>::type
			{
			};

			template <typename T>
			struct invoke_r_object_type_helper;

			template <typename T>
			struct invoke_r_object_type_helper :
					invoke_r_object_type_not_reference_wrapper<T>
			{
			};

			template <typename T>
			struct invoke_r_object_type_helper<kerbal::utility::reference_wrapper<T> > :
					kerbal::type_traits::integral_constant<int, 2>
			{
			};

			/**
			 *  Object -> 0
			 *  Pointer -> 1
			 *  reference_wrapper -> 2
			 */
			template <typename T>
			struct invoke_r_object_type :
					invoke_r_object_type_helper<typename kerbal::type_traits::remove_cvref<T>::type>
			{
			};

			template <typename Ver, typename R, typename Fun, typename ... Args>
			struct invoke_r_is_nothrow_helper;

			template <typename R, typename Fun, typename ... Args>
			struct invoke_r_is_nothrow_helper<INVOKE_OVERLOAD_VER_CALLABLE, R, Fun, Args...>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							static_cast<R>(
								kerbal::utility::declval<Fun>()(kerbal::utility::declval<Args>()...)
							)
						)
					> type;
			};

			template <int ObjectType, typename R, typename MemObjPtr, typename T>
			struct invoke_r_is_nothrow_helper_of_mem_obj;

			template <typename R, typename MemObjPtr, typename T>
			struct invoke_r_is_nothrow_helper_of_mem_obj<0, R, MemObjPtr, T>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							static_cast<R>(
								kerbal::utility::declval<T>().*kerbal::utility::declval<MemObjPtr>()
							)
						)
					> type;
			};

			template <typename R, typename MemObjPtr, typename P>
			struct invoke_r_is_nothrow_helper_of_mem_obj<1, R, MemObjPtr, P>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							static_cast<R>(
								kerbal::utility::declval<P>()->*kerbal::utility::declval<MemObjPtr>()
							)
						)
					> type;
			};

			template <typename R, typename MemObjPtr, typename Rw>
			struct invoke_r_is_nothrow_helper_of_mem_obj<2, R, MemObjPtr, Rw>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							static_cast<R>(
								kerbal::utility::declval<Rw>().get().*kerbal::utility::declval<MemObjPtr>()
							)
						)
					> type;
			};

			template <typename R, typename MemObjPtr, typename T, typename ... Args>
			struct invoke_r_is_nothrow_helper<INVOKE_OVERLOAD_VER_MEM_OBJ, R, MemObjPtr, T, Args...> :
					invoke_r_is_nothrow_helper_of_mem_obj<
						kerbal::function::detail::invoke_r_object_type<T>::value,
						R, MemObjPtr, T
					>
			{
			};

			template <int ObjectType, typename R, typename MemFunPtr, typename T, typename ... Args>
			struct invoke_r_is_nothrow_helper_of_mem_fun;

			template <typename R, typename MemFunPtr, typename T, typename ... Args>
			struct invoke_r_is_nothrow_helper_of_mem_fun<0, R, MemFunPtr, T, Args...>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							static_cast<R>(
								(kerbal::utility::declval<T>().*kerbal::utility::declval<MemFunPtr>())
									(kerbal::utility::declval<Args>()...)
							)
						)
					> type;
			};

			template <typename R, typename MemFunPtr, typename P, typename ... Args>
			struct invoke_r_is_nothrow_helper_of_mem_fun<1, R, MemFunPtr, P, Args...>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							static_cast<R>(
								(kerbal::utility::declval<P>()->*kerbal::utility::declval<MemFunPtr>())
									(kerbal::utility::declval<Args>()...)
							)
						)
					> type;
			};

			template <typename R, typename MemFunPtr, typename Rw, typename ... Args>
			struct invoke_r_is_nothrow_helper_of_mem_fun<2, R, MemFunPtr, Rw, Args...>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							static_cast<R>(
								(kerbal::utility::declval<Rw>().get().*kerbal::utility::declval<MemFunPtr>())
									(kerbal::utility::declval<Args>()...)
							)
						)
					> type;
			};

			template <typename R, typename MemFunPtr, typename T, typename ... Args>
			struct invoke_r_is_nothrow_helper<INVOKE_OVERLOAD_VER_MEM_FUN, R, MemFunPtr, T, Args...> :
					invoke_r_is_nothrow_helper_of_mem_fun<
						kerbal::function::detail::invoke_r_object_type<T>::value,
						R, MemFunPtr, T, Args...
					>
			{
			};

		} // namespace detail


		template <typename R, typename Fun, typename ... Args>
		struct invoke_r_is_nothrow :
				kerbal::function::detail::invoke_r_is_nothrow_helper<
					typename kerbal::function::detail::invoke_overload_ver_selector<Fun, Args...>::type, R, Fun, Args...
				>::type
		{
		};

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_R_IS_NOTHROW_CXX11_PART_HPP
