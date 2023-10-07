/**
 * @file       minimum_alignment.hpp
 * @brief
 * @date       2023-06-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits/size_type.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>
#include <kerbal/utility/declval.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type >
		struct allocator_has_mem_minimum_alignment: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_mem_minimum_alignment<Alloc, typename kerbal::type_traits::void_type<
#	if __cplusplus >= 201103L // compatible with msvc
				decltype(
					kerbal::utility::declval<const Alloc&>().minimum_alignment()
				)
#	else
				kerbal::type_traits::integral_constant<
					std::size_t,
					sizeof(
						kerbal::utility::declval<const Alloc&>().minimum_alignment()
					)
				>
#	endif
		>::type >: kerbal::type_traits::true_type
		{
		};


		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_VER_NONE;
			typedef kerbal::type_traits::integral_constant<int, 1> ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_VER_STATIC;
			typedef kerbal::type_traits::integral_constant<int, 2> ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_VER_MEM;

			template <typename Alloc>
			struct allocator_traits_minimum_alignment_ver :
					kerbal::type_traits::conditional<
						kerbal::memory::allocator_has_mem_minimum_alignment<Alloc>::value,
						ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_VER_MEM,
						ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_VER_NONE
					>::type
			{
			};



			template <typename Alloc, int = kerbal::memory::detail::allocator_traits_minimum_alignment_ver<Alloc>::value>
			struct allocator_traits_minimum_alignment_helper;

			template <typename Alloc>
			struct allocator_traits_minimum_alignment_helper<Alloc, ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_VER_NONE::value>
			{
				private:
					typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type		size_type;

				public:
					KERBAL_CONSTEXPR14
					static size_type minimum_alignment(const Alloc & /*alloc*/) KERBAL_NOEXCEPT
					{
						return size_type(1u);
					}
			};

			template <typename Alloc>
			struct allocator_traits_minimum_alignment_helper<Alloc, ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_VER_STATIC::value>
			{
				private:
					typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type		size_type;

				public:
					KERBAL_CONSTEXPR14
					static size_type minimum_alignment(const Alloc & /*alloc*/) KERBAL_NOEXCEPT
					{
						return Alloc::MINIMUM_ALIGNMENT::value;
					}
			};

			template <typename Alloc>
			struct allocator_traits_minimum_alignment_helper<Alloc, ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_VER_MEM::value>
			{
				private:
					typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type		size_type;

				public:
					KERBAL_CONSTEXPR14
					static size_type minimum_alignment(const Alloc & alloc) KERBAL_NOEXCEPT
					{
						return alloc.minimum_alignment();
					}
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_MINIMUM_ALIGNMENT_HPP
