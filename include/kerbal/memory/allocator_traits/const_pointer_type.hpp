/**
 * @file       const_pointer_type.hpp
 * @brief
 * @date       2022-01-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_CONST_POINTER_TYPE_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_CONST_POINTER_TYPE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#if __cplusplus >= 201703L
#	include <kerbal/memory/allocator/std_allocator/std_allocator.fwd.hpp>
#endif

#include <kerbal/memory/allocator_traits/pointer_type.hpp>
#include <kerbal/memory/pointer_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>


namespace kerbal
{

	namespace memory
	{

		KERBAL_MODULE_EXPORT
		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_const_pointer :
			kerbal::type_traits::false_type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Alloc>
		struct allocator_has_def_const_pointer<
			Alloc,
			typename kerbal::type_traits::void_type<typename Alloc::const_pointer>::type
		> :
			kerbal::type_traits::true_type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Alloc>
		struct allocator_could_use_const_pointer_def :
			kerbal::memory::allocator_has_def_const_pointer<Alloc>
		{
		};

#	if __cplusplus >= 201703L

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct allocator_could_use_const_pointer_def<std::allocator<T> > :
			kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <
				typename Alloc,
				bool = kerbal::memory::allocator_could_use_const_pointer_def<Alloc>::value
			>
			struct allocator_const_pointer_traits_helper
			{
				private:
					typedef typename Alloc::value_type value_type;
					typedef typename kerbal::memory::detail::allocator_pointer_traits_helper<Alloc>::type pointer;

				public:
					typedef typename kerbal::memory::pointer_traits<pointer>::template rebind<const value_type>::other type;
			};

			template <typename Alloc>
			struct allocator_const_pointer_traits_helper<Alloc, true>
			{
					typedef typename Alloc::const_pointer type;
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_CONST_POINTER_TYPE_HPP
