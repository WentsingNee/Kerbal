/**
 * @file       thread.win.impl.part.hpp
 * @brief
 * @date       2022-09-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_DETAIL_THREAD_WIN_IMPL_PART_HPP
#define KERBAL_PARALLEL_THREAD_DETAIL_THREAD_WIN_IMPL_PART_HPP

#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/decay.hpp>
#include <kerbal/utility/throw_this_exception.hpp>
#include <kerbal/utility/tuple.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <kerbal/parallel/thread/thread.decl.hpp>
#include <kerbal/parallel/thread_create_failed.hpp>

#include <windows.h>
#include <process.h>


namespace kerbal
{

	namespace parallel
	{

		namespace detail
		{

			inline
			void basic_thread_allocator_unrelated::join()
			{
				::WaitForSingleObject(this->native_handle(), INFINITE);
				this->k_th_id = id();
			}

			inline
			void basic_thread_allocator_unrelated::detach()
			{
				this->k_th_id = id();
			}

		} // namespace detail


#	if __cplusplus >= 201103L

		template <typename Allocator>
		template <typename Callable, typename ... Args>
		basic_thread<Allocator>::basic_thread(Callable && fun, Args && ... args) :
			super()
		{
			typedef typename detail::fun_args_pack_type<Callable, Args...>::type fun_args_pack_t;

			typedef typename allocator_traits::template rebind_alloc<fun_args_pack_t>::other rebind_allocator;
			typedef typename allocator_traits::template rebind_traits<fun_args_pack_t>::other rebind_allocator_traits;

			struct helper
			{
					static unsigned int __stdcall start_rtn(void * fun_args_pack_v)
					{
						fun_args_pack_t * fun_args_pack_p = static_cast<fun_args_pack_t *>(fun_args_pack_v);

						rebind_allocator alloc(rebind_alloc<fun_args_pack_t>());

						try {
							basic_thread::apply(
								*fun_args_pack_p,
								kerbal::utility::make_index_sequence<sizeof...(Args)>()
							);
						} catch (...) {
							k_destroy_fun_args_pack(alloc, fun_args_pack_p);
							throw;
						}

						k_destroy_fun_args_pack(alloc, fun_args_pack_p);
						return 0;
					}
			};

			rebind_allocator alloc(rebind_alloc<fun_args_pack_t>());
			fun_args_pack_t * fun_args_pack_p = k_build_fun_args_pack(
				alloc, kerbal::utility::forward<Callable>(fun), kerbal::utility::forward<Args>(args)...
			);

			unsigned thread_id;
			this->k_th_id.native_handle = (HANDLE)::_beginthreadex(NULL, 0, helper::start_rtn, fun_args_pack_p, 0, &thread_id);
			if (this->k_th_id.native_handle == 0) {
				k_destroy_fun_args_pack(alloc, fun_args_pack_p);
				kerbal::utility::throw_this_exception_helper<
					kerbal::parallel::thread_create_failed
				>::throw_this_exception();
			}
		}

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE(i) typename kerbal::type_traits::decay<KERBAL_MACRO_CONCAT(Arg, i)>::type
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FUN_ARGS_PACK_EXPAND_ARG(i) (fun_args_pack_p->template get<(i)>())
#		define FBODY(i) \
		template <typename Allocator> \
		template <typename Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		basic_thread<Allocator>::basic_thread(Callable fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
			super() \
		{ \
			typedef kerbal::utility::tuple< \
				typename kerbal::type_traits::decay<Callable>::type \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i) \
			> fun_args_pack_t; \
 \
			typedef typename allocator_traits::template rebind_alloc<fun_args_pack_t>::other rebind_allocator; \
			typedef typename allocator_traits::template rebind_traits<fun_args_pack_t>::other rebind_allocator_traits; \
 \
			struct helper \
			{ \
					static void * start_rtn(void * fun_args_pack_v) \
					{ \
						fun_args_pack_t * fun_args_pack_p = static_cast<fun_args_pack_t *>(fun_args_pack_v); \
 \
						rebind_allocator alloc(rebind_alloc<fun_args_pack_t>()); \
 \
						try { \
							kerbal::function::invoke_r<void>( \
								fun_args_pack_p->template get<0>() \
								KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, FUN_ARGS_PACK_EXPAND_ARG, i) \
							); \
						} catch (...) { \
							k_destroy_fun_args_pack(alloc, fun_args_pack_p); \
							throw; \
						} \
 \
						k_destroy_fun_args_pack(alloc, fun_args_pack_p); \
						return NULL; \
					} \
			}; \
 \
			rebind_allocator alloc(rebind_alloc<fun_args_pack_t>()); \
			fun_args_pack_t * fun_args_pack_p = k_build_fun_args_pack( \
				alloc, fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
 \
			unsigned thread_id; \
			this->k_th_id.native_handle = (HANDLE)::_beginthreadex(NULL, 0, helper::start_rtn, fun_args_pack_p, 0, &thread_id); \
			if (this->k_th_id.native_handle == 0) { \
				k_destroy_fun_args_pack(alloc, fun_args_pack_p); \
				kerbal::utility::throw_this_exception_helper< \
					kerbal::parallel::thread_create_failed \
				>::throw_this_exception(); \
			} \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef TARGS_USE
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FUN_ARGS_PACK_EXPAND_ARG
#		undef FBODY

#	endif

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_DETAIL_THREAD_WIN_IMPL_PART_HPP
