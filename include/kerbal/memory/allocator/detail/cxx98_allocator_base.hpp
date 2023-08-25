/**
 * @file       cxx98_allocator_base.hpp
 * @brief
 * @date       cxx98_allocator_base.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_DETAIL_CXX98_ALLOCATOR_BASE_HPP
#define KERBAL_MEMORY_ALLOCATOR_DETAIL_CXX98_ALLOCATOR_BASE_HPP

#include <kerbal/memory/allocator_traits.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename Allocator>
			struct cxx98_allocator_base
			{
				private:
					typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				public:
					typedef typename allocator_traits::const_pointer		const_pointer;
					typedef typename allocator_traits::reference			reference;
					typedef typename allocator_traits::const_reference		const_reference;

					template <typename U>
					struct rebind
					{
							typedef typename allocator_traits::template rebind_alloc<U>::other other;
					};
			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal
#endif // KERBAL_MEMORY_ALLOCATOR_DETAIL_CXX98_ALLOCATOR_BASE_HPP
