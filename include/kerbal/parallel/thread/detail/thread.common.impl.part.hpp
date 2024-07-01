/**
 * @file       thread.common.impl.part.hpp
 * @brief
 * @date       2023-07-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_DETAIL_THREAD_COMMON_IMPL_PART_HPP
#define KERBAL_PARALLEL_THREAD_DETAIL_THREAD_COMMON_IMPL_PART_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/config/system.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/remove_const.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <kerbal/parallel/thread/thread.decl.hpp>


namespace kerbal
{

	namespace parallel
	{

#	if __cplusplus >= 201103L

		template <typename Allocator>
		template <typename PackAllocator, typename Callable, typename ... Args>
		typename detail::fun_args_pack_type<Callable, Args...>::type *
		basic_thread<Allocator>::k_build_fun_args_pack(PackAllocator & alloc, Callable && fun, Args && ... args)
		{
			typedef kerbal::memory::allocator_traits<PackAllocator> allocator_traits;
			typedef typename detail::fun_args_pack_type<Callable, Args...>::type fun_args_pack_t;

			fun_args_pack_t * fun_args_pack_p = allocator_traits::allocate(alloc, 1);

			try {
				allocator_traits::construct(
						alloc, fun_args_pack_p,
						kerbal::utility::forward<Callable>(fun),
						kerbal::utility::forward<Args>(args)...
				);
			} catch (...) {
				allocator_traits::deallocate(alloc, fun_args_pack_p, 1);
				throw;
			}

			return fun_args_pack_p;
		}

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
		template <typename Allocator> \
		template <typename PackAllocator, typename Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		typename detail::fun_args_pack_type<Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)>::type * \
		basic_thread<Allocator>::k_build_fun_args_pack(PackAllocator & alloc, Callable fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			typedef kerbal::memory::allocator_traits<PackAllocator> allocator_traits; \
			typedef typename detail::fun_args_pack_type<Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)>::type fun_args_pack_t; \
 \
			fun_args_pack_t * fun_args_pack_p = allocator_traits::allocate(alloc, 1); \
 \
			try { \
				allocator_traits::construct( \
						alloc, fun_args_pack_p, \
						fun \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
				); \
			} catch (...) { \
				allocator_traits::deallocate(alloc, fun_args_pack_p, 1); \
				throw; \
			} \
 \
			return fun_args_pack_p; \
		}

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef TARGS_USE
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif

		template <typename Allocator>
		template <typename PackAllocator, typename FunArgsPack>
		void basic_thread<Allocator>::k_destroy_fun_args_pack(PackAllocator & alloc, FunArgsPack * fun_args_pack_p) KERBAL_NOEXCEPT
		{
			typedef kerbal::memory::allocator_traits<PackAllocator> allocator_traits;
			typedef FunArgsPack fun_args_pack_t;
			KERBAL_STATIC_ASSERT((
					kerbal::type_traits::is_same<
						typename kerbal::type_traits::remove_const<typename allocator_traits::value_type>::type,
						typename kerbal::type_traits::remove_const<fun_args_pack_t>::type
					>::value
			), "types mismatch");

			allocator_traits::destroy(alloc, fun_args_pack_p);
			allocator_traits::deallocate(alloc, fun_args_pack_p, 1);
		}

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_DETAIL_THREAD_COMMON_IMPL_PART_HPP
