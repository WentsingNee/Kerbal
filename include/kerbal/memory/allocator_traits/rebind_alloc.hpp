/**
 * @file       rebind_alloc.hpp
 * @brief
 * @date       2023-04-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_REBIND_ALLOC_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_REBIND_ALLOC_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#if __cplusplus >= 201703L
#	include <kerbal/memory/allocator/std_allocator/std_allocator.fwd.hpp>
#endif

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif


namespace kerbal
{

	namespace memory
	{

		KERBAL_MODULE_EXPORT
		template <typename Alloc, typename, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_rebind_alloc :
			kerbal::type_traits::false_type
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <typename Alloc, typename U>
		struct allocator_has_def_rebind_alloc<
			Alloc,
			U,
			typename kerbal::type_traits::void_type<typename Alloc::template rebind<U>::other>::type
		> :
			kerbal::type_traits::true_type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Alloc, typename U>
		struct allocator_could_use_rebind_alloc :
			kerbal::memory::allocator_has_def_rebind_alloc<Alloc, U>
		{
		};

#	if __cplusplus >= 201703L

		/*KERBAL_MODULE_EXPORT*/
		template <typename T, typename U>
		struct allocator_could_use_rebind_alloc<std::allocator<T>, U> :
			kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc, typename U>
			struct pointer_traits_rebind_impl;

#		if __cplusplus >= 201103L

			template <typename T, typename ... Args, typename U, template <typename, typename ...> class AllocTem>
			struct pointer_traits_rebind_impl<AllocTem<T, Args...>, U>
			{
					typedef AllocTem<U, Args...> type;
			};

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL1(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE1(i) KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_DECL2(i) typename
#		define DBODY(i) \
			template < \
				typename T, typename U \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL1, i), \
				template <typename KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL2, i)> \
					class AllocTem \
			> \
			struct pointer_traits_rebind_impl<AllocTem<T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE1, i)>, U> \
			{ \
					typedef AllocTem<U KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE1, i)> type; \
			}; \

			KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL1
#		undef TARGS_USE1
#		undef TARGS_DECL2
#		undef DBODY

#		endif // __cplusplus >= 201103L

			template <
				typename Alloc, typename U,
				bool = kerbal::memory::allocator_could_use_rebind_alloc<Alloc, U>::value
			>
			struct allocator_traits_rebind_alloc_helper : pointer_traits_rebind_impl<Alloc, U>
			{
			};

			template <typename Alloc, typename U>
			struct allocator_traits_rebind_alloc_helper<Alloc, U, true>
			{
					typedef typename Alloc::template rebind<U>::other type;
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_REBIND_ALLOC_HPP
