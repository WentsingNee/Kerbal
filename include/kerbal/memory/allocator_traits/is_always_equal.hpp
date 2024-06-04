/**
 * @file       is_always_equal.hpp
 * @brief
 * @date       2023-04-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_IS_ALWAYS_EQUAL_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_IS_ALWAYS_EQUAL_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#if __cplusplus < 201103L || __cplusplus >= 201703L
#	include <kerbal/memory/allocator/std_allocator/std_allocator.fwd.hpp>
#endif

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_empty.hpp>
#include <kerbal/type_traits/void_type.hpp>


namespace kerbal
{

	namespace memory
	{

		KERBAL_MODULE_EXPORT
		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_is_always_equal :
			kerbal::type_traits::false_type
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <typename Alloc>
		struct allocator_has_def_is_always_equal<
			Alloc,
			typename kerbal::type_traits::void_type<typename Alloc::is_always_equal>::type
		> :
			kerbal::type_traits::true_type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Alloc>
		struct allocator_could_use_is_always_equal :
			kerbal::memory::allocator_has_def_is_always_equal<Alloc>
		{
		};

#	if __cplusplus >= 201703L

		/*KERBAL_MODULE_EXPORT*/
		template <typename T>
		struct allocator_could_use_is_always_equal<std::allocator<T> > :
			kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_could_use_is_always_equal<Alloc>::value>
			struct allocator_is_always_equal_traits_helper:
				kerbal::type_traits::try_test_is_empty<Alloc>::IS_TRUE
			{
			};

			template <typename Alloc>
			struct allocator_is_always_equal_traits_helper<Alloc, true>:
				kerbal::type_traits::bool_constant<
					Alloc::is_always_equal::value
				>
			{
			};

#		if __cplusplus < 201103L

			template <typename T>
			struct allocator_is_always_equal_traits_helper<std::allocator<T>, false> :
				kerbal::type_traits::true_type
			{
			};

#		endif

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_IS_ALWAYS_EQUAL_HPP
