/**
 * @file       reallocable_allocator.hpp
 * @brief
 * @date       2020-08-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_REALLOCABLE_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_REALLOCABLE_ALLOCATOR_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <new>

#include <cstdlib>
#include <cstddef>

#if __cplusplus >= 201103L
#	include <type_traits>
#else
#	include <kerbal/type_traits/array_traits.hpp>
#	include <kerbal/type_traits/fundamental_deduction.hpp>
#	include <kerbal/type_traits/member_pointer_deduction.hpp>
#	include <kerbal/type_traits/pointer_deduction.hpp>
#endif


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

#	if __cplusplus >= 201103L

			template <typename T>
			struct is_trivially_reallocate_type:
					kerbal::type_traits::bool_constant<
						std::is_trivially_copyable<T>::value
					>
			{
			};

#	else

			template <typename T>
			struct is_trivially_reallocate_type_helper:
					kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_fundamental<T>::value ||
						kerbal::type_traits::is_member_pointer<T>::value ||
						kerbal::type_traits::is_pointer<T>::value
					>
			{
			};

			template <typename T>
			struct is_trivially_reallocate_type:
					is_trivially_reallocate_type_helper<
							typename kerbal::type_traits::remove_all_extents<T>::type
					>
			{
			};

#	endif

			template <typename Tp, bool>
			class reallocable_allocator_realloc_overload_helper;

			template <typename Tp>
			class reallocable_allocator_realloc_overload_helper<Tp, true>
			{
				protected:
					typedef Tp					value_type;
					typedef value_type*			pointer;
					typedef std::size_t			size_type;

				public:
					typedef kerbal::type_traits::true_type SUPPORT_REALLOCATE;

				public:
					static pointer reallocate(pointer p, size_type /*n_old*/, size_type n_new)
					{
						p = static_cast<pointer>(::realloc(p, sizeof(value_type) * n_new));
						if (p == NULL) {
							kerbal::utility::throw_this_exception_helper<std::bad_alloc>::throw_this_exception();
						}
						return p;
					}

			};

			template <typename Tp>
			class reallocable_allocator_realloc_overload_helper<Tp, false>
			{
				public:
					typedef kerbal::type_traits::false_type SUPPORT_REALLOCATE;
			};

		} // namespace detail

		template <typename Tp>
		class reallocable_allocator:
				public detail::reallocable_allocator_realloc_overload_helper<
					Tp, detail::is_trivially_reallocate_type<Tp>::value
				>
		{
			public:
				typedef Tp					value_type;
				typedef value_type*			pointer;
				typedef std::size_t			size_type;

				static pointer allocate(size_type n)
				{
					pointer p = static_cast<pointer>(::malloc(sizeof(value_type) * n));
					if (p == NULL) {
						kerbal::utility::throw_this_exception_helper<std::bad_alloc>::throw_this_exception();
					}
					return p;
				}

				static void deallocate(pointer p, size_type /*n*/) KERBAL_NOEXCEPT
				{
					::free(p);
				}

		};

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_ALLOCATOR_REALLOCABLE_ALLOCATOR_HPP
