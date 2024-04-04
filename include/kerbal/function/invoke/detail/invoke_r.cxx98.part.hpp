/**
 * @file       invoke_r.cxx98.part.hpp
 * @brief
 * @date       2023-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_R_CXX98_PART_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_R_CXX98_PART_HPP

#include <kerbal/function/invoke/invoke_overload_ver_selector.hpp>

#include <kerbal/compatibility/static_assert.hpp>

#include <kerbal/macro/macro_concat.hpp>
#include <kerbal/macro/ppexpand.hpp>
#include <kerbal/tmp/type_vector.hpp>
#include <kerbal/type_traits/add_const_lvalue_reference.hpp>
#include <kerbal/utility/reference_wrapper.hpp>


namespace kerbal
{

	namespace function
	{

#		define EMPTY
#		define REMAINF(exp) exp
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE(i) typename kerbal::type_traits::add_const_lvalue_reference<KERBAL_MACRO_CONCAT(Arg, i)>::type
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)

#		define FBODY(i) \
		namespace detail \
		{ \
 \
			template <typename R, typename Fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			R invoke_r_helper(INVOKE_OVERLOAD_VER_CALLABLE, Fun f KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				return static_cast<R>( \
					f( \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i) \
					) \
				); \
			} \
 \
			template <typename R, typename MemObjPtr, typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, T & o KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				KERBAL_STATIC_ASSERT(kerbal::tmp::type_vector<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)>::SIZE::value == 0, "Wrong Args num"); \
				return static_cast<R>( \
					o.*mem_obj_ptr \
				); \
			} \
 \
			template <typename R, typename MemObjPtr, typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, T * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				KERBAL_STATIC_ASSERT(kerbal::tmp::type_vector<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)>::SIZE::value == 0, "Wrong Args num"); \
				return static_cast<R>( \
					p->*mem_obj_ptr \
				); \
			} \
 \
			template <typename R, typename MemObjPtr, typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_OBJ, MemObjPtr mem_obj_ptr, kerbal::utility::reference_wrapper<T> rw KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				KERBAL_STATIC_ASSERT(kerbal::tmp::type_vector<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)>::SIZE::value == 0, "Wrong Args num"); \
				return static_cast<R>( \
					rw.get().*mem_obj_ptr \
				); \
			} \
 \
			template <typename R, typename MemFunPtr, typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, T & o KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				return static_cast<R>( \
					(o.*mem_fun_ptr)( \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i) \
					) \
				); \
			} \
 \
			template <typename R, typename MemFunPtr, typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, T * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				return static_cast<R>( \
					(p->*mem_fun_ptr)( \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i) \
					) \
				); \
			} \
 \
			template <typename R, typename MemFunPtr, typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			R invoke_r_helper(INVOKE_OVERLOAD_VER_MEM_FUN, MemFunPtr mem_fun_ptr, kerbal::utility::reference_wrapper<T> rw KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				return static_cast<R>( \
					(rw.get().*mem_fun_ptr)( \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i) \
					) \
				); \
			} \
 \
		} /* namespace detail */ \
 \
		template <typename R, typename Fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		R invoke_r(Fun f KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			typedef typename kerbal::function::detail::invoke_overload_ver_selector<Fun & KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)>::type VER; \
			return kerbal::function::detail::invoke_r_helper<R>(VER(), f KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
		} \


		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef REMAINF
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef TARGS_USE
#		undef ARGS_DECL
#		undef ARGS_USE

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_R_CXX98_PART_HPP
