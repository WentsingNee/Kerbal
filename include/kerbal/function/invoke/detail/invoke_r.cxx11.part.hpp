/**
 * @file       invoke_r.cxx11.part.hpp
 * @brief
 * @date       2023-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_R_CXX11_PART_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_R_CXX11_PART_HPP

#include <kerbal/function/invoke/invoke_overload_ver_selector.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/function/invoke/invoke_r_is_nothrow.hpp>
#endif


#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/reference_wrapper.hpp>


namespace kerbal
{

	namespace function
	{

		namespace detail
		{

			template <typename R, typename Fun, typename ... Args>
			KERBAL_CONSTEXPR
			R invoke_r_helper(INVOKE_OVERLOAD_VER_CALLABLE, Fun && f, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_r_is_nothrow<R, Fun, Args&&...>::value
					))
			{
				return static_cast<R>(
					kerbal::utility::forward<Fun>(f)(
						kerbal::utility::forward<Args>(args)...
					)
				);
			}

			template <typename R, typename MemObjPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, T&& o, Args&& ...)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_r_is_nothrow<R, MemObjPtr, T&&, Args&&...>::value
					))
			{
				KERBAL_STATIC_ASSERT(sizeof...(Args) == 0, "Wrong Args num");
				return static_cast<R>(
					kerbal::utility::forward<T>(o).*mem_obj_ptr
				);
			}

			template <typename R, typename MemObjPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, T * p, Args&& ...)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_r_is_nothrow<R, MemObjPtr, T *, Args&&...>::value
					))
			{
				KERBAL_STATIC_ASSERT(sizeof...(Args) == 0, "Wrong Args num");
				return static_cast<R>(
					p->*mem_obj_ptr
				);
			}

			template <typename R, typename MemObjPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, kerbal::utility::reference_wrapper<T> rw, Args&& ...)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_r_is_nothrow<R, MemObjPtr, kerbal::utility::reference_wrapper<T>, Args&&...>::value
					))
			{
				KERBAL_STATIC_ASSERT(sizeof...(Args) == 0, "Wrong Args num");
				return static_cast<R>(
					rw.get().*mem_obj_ptr
				);
			}

			template <typename R, typename MemFunPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, T&& o, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_r_is_nothrow<R, MemFunPtr, T&&, Args&&...>::value
					))
			{
				return static_cast<R>(
					(kerbal::utility::forward<T>(o).*mem_fun_ptr)(
						kerbal::utility::forward<Args>(args)...
					)
				);
			}

			template <typename R, typename MemFunPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, T * p, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_r_is_nothrow<R, MemFunPtr, T *, Args&&...>::value
					))
			{
				return static_cast<R>(
					(p->*mem_fun_ptr)(
						kerbal::utility::forward<Args>(args)...
					)
				);
			}

			template <typename R, typename MemFunPtr, typename T, typename ... Args>
			KERBAL_CONSTEXPR
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, kerbal::utility::reference_wrapper<T> rw, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT((
						invoke_r_is_nothrow<R, MemFunPtr, kerbal::utility::reference_wrapper<T>, Args&&...>::value
					))
			{
				return static_cast<R>(
					(rw.get().*mem_fun_ptr)(
						kerbal::utility::forward<Args>(args)...
					)
				);
			}

		} // namespace detail


		template <typename R, typename Fun, typename ... Args>
		KERBAL_CONSTEXPR
		R invoke_r(Fun && f, Args&& ... args)
				KERBAL_CONDITIONAL_NOEXCEPT((
					invoke_r_is_nothrow<R, Fun&&, Args&&...>::value
				))
		{
			typedef typename kerbal::function::detail::invoke_overload_ver_selector<Fun&&, Args&&...>::type VER;
			return kerbal::function::detail::invoke_r_helper<R>(VER(), kerbal::utility::forward<Fun>(f), kerbal::utility::forward<Args>(args)...);
		}

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_R_CXX11_PART_HPP
