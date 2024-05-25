/**
 * @file       invoke.cxx11.part.hpp
 * @brief
 * @date       2021-11-17
 * @author     Peter
 * @remark     move from kerbal/function/invoke.hpp, 2023-08-25
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_CXX11_PART_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_CXX11_PART_HPP

#include <kerbal/function/invoke/invoke_overload_ver_selector.hpp>
#include <kerbal/function/invoke/invoke_is_nothrow.hpp>
#include <kerbal/function/invoke/invoke_result.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/reference_wrapper.hpp>


namespace kerbal
{

	namespace function
	{

		namespace detail
		{

			template <typename Fun, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<Fun, Args && ...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_CALLABLE, Fun && f, Args && ... args)
				KERBAL_CONDITIONAL_NOEXCEPT((
					invoke_is_nothrow<Fun, Args &&...>::value
				))
			{
				return kerbal::utility::forward<Fun>(f)(
						kerbal::utility::forward<Args>(args)...);
			}

			template <typename MemObjPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<MemObjPtr, T &&, Args && ...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, T && o, Args && ...)
				KERBAL_CONDITIONAL_NOEXCEPT((
					invoke_is_nothrow<MemObjPtr, T &&, Args &&...>::value
				))
			{
				KERBAL_STATIC_ASSERT(sizeof...(Args) == 0, "Wrong Args num");
				return kerbal::utility::forward<T>(o).*mem_obj_ptr;
			}

			template <typename MemObjPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<MemObjPtr, T *, Args && ...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, T * p, Args && ...)
				KERBAL_CONDITIONAL_NOEXCEPT((
					invoke_is_nothrow<MemObjPtr, T *, Args && ...>::value
				))
			{
				KERBAL_STATIC_ASSERT(sizeof...(Args) == 0, "Wrong Args num");
				return p->*mem_obj_ptr;
			}

			template <typename MemObjPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<MemObjPtr, kerbal::utility::reference_wrapper<T>, Args && ...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, kerbal::utility::reference_wrapper<T> rw, Args && ...)
				KERBAL_CONDITIONAL_NOEXCEPT((
					invoke_is_nothrow<MemObjPtr, kerbal::utility::reference_wrapper<T>, Args && ...>::value
				))
			{
				KERBAL_STATIC_ASSERT(sizeof...(Args) == 0, "Wrong Args num");
				return rw.get().*mem_obj_ptr;
			}

			template <typename MemFunPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<MemFunPtr, T &&, Args && ...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, T && o, Args && ... args)
				KERBAL_CONDITIONAL_NOEXCEPT((
					invoke_is_nothrow<MemFunPtr, T &&, Args &&...>::value
				))
			{
				return (kerbal::utility::forward<T>(o).*mem_fun_ptr)(
					kerbal::utility::forward<Args>(args)...
				);
			}

			template <typename MemFunPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<MemFunPtr, T *, Args && ...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, T * p, Args && ... args)
				KERBAL_CONDITIONAL_NOEXCEPT((
					invoke_is_nothrow<MemFunPtr, T *, Args && ...>::value
				))
			{
				return (p->*mem_fun_ptr)(
					kerbal::utility::forward<Args>(args)...
				);
			}

			template <typename MemFunPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			typename invoke_result<MemFunPtr, kerbal::utility::reference_wrapper<T>, Args && ...>::type
			invoke_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, kerbal::utility::reference_wrapper<T> rw, Args && ... args)
				KERBAL_CONDITIONAL_NOEXCEPT((
					invoke_is_nothrow<MemFunPtr, kerbal::utility::reference_wrapper<T>, Args && ...>::value
				))
			{
				return (rw.get().*mem_fun_ptr)(
					kerbal::utility::forward<Args>(args)...
				);
			}

		} // namespace detail


		template <typename Fun, typename ... Args>
		KERBAL_CONSTEXPR
		typename invoke_result<Fun &&, Args && ...>::type
		invoke(Fun && f, Args && ... args)
			KERBAL_CONDITIONAL_NOEXCEPT((
				invoke_is_nothrow<Fun &&, Args && ...>::value
			))
		{
			typedef typename kerbal::function::detail::invoke_overload_ver_selector<Fun &&, Args && ...>::type VER;
			return kerbal::function::detail::invoke_helper(
				VER(),
				kerbal::utility::forward<Fun>(f),
				kerbal::utility::forward<Args>(args)...
			);
		}

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_CXX11_PART_HPP
