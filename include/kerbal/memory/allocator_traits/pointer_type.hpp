/**
 * @file       pointer_type.hpp
 * @brief
 * @date       2022-01-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_POINTER_TYPE_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_POINTER_TYPE_HPP

#if __cplusplus >= 201703L
#	include <kerbal/memory/allocator/std_allocator.fwd.hpp>
#endif

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_pointer: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_pointer<
				Alloc,
				typename kerbal::type_traits::void_type<typename Alloc::pointer>::type
		> :
				kerbal::type_traits::true_type
		{
		};

		template <typename Alloc>
		struct allocator_could_use_pointer_def : kerbal::memory::allocator_has_def_pointer<Alloc>
		{
		};

#	if __cplusplus >= 201703L

		template <typename T>
		struct allocator_could_use_pointer_def<std::allocator<T> >: kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_could_use_pointer_def<Alloc>::value>
			struct allocator_pointer_traits_helper
			{
					typedef typename Alloc::value_type* type;
			};

			template <typename Alloc>
			struct allocator_pointer_traits_helper<Alloc, true>
			{
					typedef typename Alloc::pointer type;
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_POINTER_TYPE_HPP
