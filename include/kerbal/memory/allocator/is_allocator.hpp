/**
 * @file       is_allocator.hpp
 * @brief
 * @date       2023-08-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_IS_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_IS_ALLOCATOR_HPP

#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/void_type.hpp>
#include <kerbal/type_traits/yes_no_type.hpp>
#include <kerbal/utility/declval.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename T, typename = void>
			struct is_allocator_allocator_traits_valid_helper : kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct is_allocator_allocator_traits_valid_helper<
					T,
					typename kerbal::type_traits::void_type<
						typename T::value_type,
						typename kerbal::memory::allocator_traits<T>::size_type,
						typename kerbal::memory::allocator_traits<T>::pointer
					>::type
			> : kerbal::type_traits::true_type
			{
			};

			template <typename T>
			struct is_allocator_has_allocate_impl
			{
				private:
					template <typename T2>
					static kerbal::type_traits::no_type test(...);

					template <typename T2>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
							kerbal::utility::declval<T2&>().allocate(
								kerbal::utility::declval<
									typename kerbal::memory::allocator_traits<T2>::size_type
								>()
							),
							0
					)]);

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<T>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;
			};

			template <typename T>
			struct is_allocator_has_allocate_helper :
					is_allocator_has_allocate_impl<T>::type
			{
			};

			template <typename T>
			struct is_allocator_has_deallocate_impl
			{
				private:
					template <typename T2>
					static kerbal::type_traits::no_type test(...);

					template <typename T2>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
							kerbal::utility::declval<T2&>().deallocate(
								kerbal::utility::declval<
									typename kerbal::memory::allocator_traits<T2>::pointer
								>(),
								kerbal::utility::declval<
									typename kerbal::memory::allocator_traits<T2>::size_type
								>()
							),
							0
					)]);

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<T>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;
			};

			template <typename T>
			struct is_allocator_has_deallocate_helper :
					is_allocator_has_deallocate_impl<T>::type
			{
			};

		} // namespace detail

		template <typename T>
		struct is_allocator :
				kerbal::type_traits::conjunction<
					kerbal::memory::detail::is_allocator_allocator_traits_valid_helper<T>,
					kerbal::memory::detail::is_allocator_has_allocate_helper<T>,
					kerbal::memory::detail::is_allocator_has_deallocate_helper<T>
				>
		{
		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_IS_ALLOCATOR_HPP
