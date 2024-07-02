/**
 * @file       max_size.hpp
 * @brief
 * @date       2023-06-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_MAX_SIZE_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_MAX_SIZE_HPP

#if __cplusplus >= 201703L
#	include <kerbal/memory/allocator/std_allocator/std_allocator.fwd.hpp>
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits/size_type.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>
#include <kerbal/utility/declval.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
			struct allocator_has_max_size_helper : kerbal::type_traits::false_type
			{
			};

			template <typename Alloc>
			struct allocator_has_max_size_helper<Alloc, typename kerbal::type_traits::void_type<
#	if __cplusplus >= 201103L // compatible with msvc
					decltype(static_cast<std::size_t>(kerbal::utility::declval<const Alloc&>().max_size()))
#	else
					kerbal::type_traits::integral_constant<
						std::size_t,
						sizeof(
							static_cast<std::size_t>(kerbal::utility::declval<const Alloc&>().max_size()),
							0
						)
					>
#	endif
			>::type>: kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		template <typename Alloc>
		struct allocator_has_max_size : kerbal::memory::detail::allocator_has_max_size_helper<Alloc>
		{
		};


		template <typename Alloc>
		struct allocator_could_use_max_size : kerbal::memory::allocator_has_max_size<Alloc>
		{
		};

#	if __cplusplus >= 201703L

		template <typename T>
		struct allocator_could_use_max_size<std::allocator<T> >: kerbal::type_traits::false_type
		{
		};

#	endif


		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_could_use_max_size<Alloc>::value>
			struct allocator_traits_max_size_helper
			{
				private:
					typedef typename Alloc::value_type value_type;
					typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type size_type;

				public:
					KERBAL_CONSTEXPR
					static size_type max_size(const Alloc & /*alloc*/)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(value_type))
							)
					{
						return kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(value_type);
					}
			};

			template <typename Alloc>
			struct allocator_traits_max_size_helper<Alloc, true>
			{
				private:
					typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type size_type;

				public:
					KERBAL_CONSTEXPR
					static size_type max_size(const Alloc & alloc)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::utility::declval<const Alloc&>().max_size())
							)
					{
						return alloc.max_size();
					}
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_MAX_SIZE_HPP
