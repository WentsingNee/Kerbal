/**
 * @file       void_pointer_type.hpp
 * @brief
 * @date       2022-01-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_VOID_POINTER_TYPE_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_VOID_POINTER_TYPE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

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
		struct allocator_has_def_void_pointer :
			kerbal::type_traits::false_type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Alloc>
		struct allocator_has_def_void_pointer<
			Alloc,
			typename kerbal::type_traits::void_type<typename Alloc::void_pointer>::type
		> :
			kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <
				typename Alloc,
				bool = kerbal::memory::allocator_has_def_void_pointer<Alloc>::value
			>
			struct allocator_void_pointer_traits_helper
			{
				private:
					typedef typename kerbal::memory::detail::allocator_pointer_traits_helper<Alloc>::type pointer;

				public:
					typedef typename kerbal::memory::pointer_traits<pointer>::template rebind<void>::other type;
			};

			template <typename Alloc>
			struct allocator_void_pointer_traits_helper<Alloc, true>
			{
					typedef typename Alloc::void_pointer type;
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_VOID_POINTER_TYPE_HPP
