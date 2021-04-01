/**
 * @file       new_allocator.hpp
 * @brief
 * @date       2021-01-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_NEW_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_NEW_ALLOCATOR_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/memory/allocator/detail/cxx98_allocator_base.hpp>
#include <kerbal/memory/new/basic_new.hpp>
#include <kerbal/memory/new/over_aligned_new.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		template <typename Tp = void>
		class new_allocator;

		template <typename Tp>
		class new_allocator: public kerbal::memory::detail::cxx98_allocator_base<Tp>
		{
			public:
				typedef Tp							value_type;
				typedef value_type*					pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef kerbal::type_traits::true_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::true_type		is_always_equal;

			public:

#			if __cplusplus < 201103L

				new_allocator() KERBAL_NOEXCEPT
				{
				}

#			else

				new_allocator() = default;

#			endif

				template <typename Up>
				new_allocator(const new_allocator<Up> &) KERBAL_NOEXCEPT
				{
				}

				static pointer allocate(size_type n)
				{
					return static_cast<pointer>(::operator new(sizeof(value_type) * n, kerbal::memory::align_val_t(KERBAL_ALIGNOF(value_type))));
				}

				static void deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
				{
					::operator delete(p, sizeof(value_type) * n, kerbal::memory::align_val_t(KERBAL_ALIGNOF(value_type)));
				}

		};

		template <>
		class new_allocator<void>
		{
			public:
				typedef void						value_type;
				typedef value_type*					pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef kerbal::type_traits::true_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::true_type		is_always_equal;

			public:

#			if __cplusplus < 201103L

				new_allocator() KERBAL_NOEXCEPT
				{
				}

#			else

				new_allocator() = default;

#			endif

				template <typename Up>
				new_allocator(const new_allocator<Up> &) KERBAL_NOEXCEPT
				{
				}

				static pointer allocate(size_type n)
				{
					return static_cast<pointer>(::operator new(n, kerbal::memory::basic_t()));
				}

				static void deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
				{
					::operator delete(p, n, kerbal::memory::basic_t());
				}

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_NEW_ALLOCATOR_HPP
