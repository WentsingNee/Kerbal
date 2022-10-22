/**
 * @file       invoke.hpp
 * @brief
 * @date       2021-11-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_HPP
#define KERBAL_FUNCTION_INVOKE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_member_function_pointer.hpp>
#include <kerbal/type_traits/is_member_object_pointer.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/forward.hpp>


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



		namespace detail
		{

			template <typename Ver, typename Fun, typename ... Args>
			struct invoke_result_helper;

			template <typename Fun, typename ... Args>
			struct invoke_result_helper<INVOKE_OVERLOAD_VER_CALLABLE, Fun, Args...>
			{
					typedef decltype(
						kerbal::utility::declval<Fun>()(kerbal::utility::declval<Args>()...)
					) type;
			};

			template <typename MemObjPtr, typename T, typename ... Args>
			struct invoke_result_helper<INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr, T, Args...>
			{
					typedef decltype(
						kerbal::utility::declval<T>().*(kerbal::utility::declval<MemObjPtr>())
					) type;
			};

			template <typename MemFunPtr, typename T, typename ... Args>
			struct invoke_result_helper<INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr, T, Args...>
			{
					typedef decltype(
						(kerbal::utility::declval<T>().*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...)
					) type;
			};

		} // namespace detail


		template <typename Fun, typename ... Args>
		struct invoke_result :
				detail::invoke_result_helper<typename detail::invoke_overload_selector<Fun, Args...>::type, Fun, Args...>
		{
		};



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

			template <typename MemFunPtr, typename T, typename ... Args>
			struct invoke_is_nothrow_helper<INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr, T, Args...>
			{
					typedef kerbal::type_traits::bool_constant<
						noexcept(
							(kerbal::utility::declval<T>().*kerbal::utility::declval<MemFunPtr>())
								(kerbal::utility::declval<Args>()...)
						)
					> type;
			};

		} // namespace detail


		template <typename Fun, typename ... Args>
		struct invoke_is_nothrow :
				detail::invoke_is_nothrow_helper<typename detail::invoke_overload_selector<Fun, Args...>::type, Fun, Args...>::type
		{
		};



		namespace detail
		{

			template <typename Fun, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<Fun, Args&&...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_CALLABLE, Fun && f, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_is_nothrow<Fun, Args&&...>::value
					))
			{
				return kerbal::utility::forward<Fun>(f)(
						kerbal::utility::forward<Args>(args)...);
			}

			template <typename MemObjPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<MemObjPtr, T&&, Args&&...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, T&& o, Args&& ...)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_is_nothrow<MemObjPtr, T&&, Args&&...>::value
					))
			{
				KERBAL_STATIC_ASSERT(sizeof...(Args) >= 0, "Wrong Args num");
				return kerbal::utility::forward<T>(o).*mem_obj_ptr;
			}

			template <typename MemFunPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<MemFunPtr, T&&, Args&&...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, T&& o, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_is_nothrow<MemFunPtr, T&&, Args&&...>::value
					))
			{
				return (kerbal::utility::forward<T>(o).*mem_fun_ptr)(
						kerbal::utility::forward<Args>(args)...);
			}

		} // namespace detail


		template <typename Fun, typename ... Args>
		KERBAL_CONSTEXPR
		typename invoke_result<Fun&&, Args&&...>::type
		invoke(Fun && f, Args&& ... args)
				KERBAL_CONDITIONAL_NOEXCEPT((
					invoke_is_nothrow<Fun&&, Args&&...>::value
				))
		{
			typedef typename detail::invoke_overload_selector<Fun&&, Args&&...>::type VER;
			return detail::invoke_helper(VER(), kerbal::utility::forward<Fun>(f), kerbal::utility::forward<Args>(args)...);
		}

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_HPP
