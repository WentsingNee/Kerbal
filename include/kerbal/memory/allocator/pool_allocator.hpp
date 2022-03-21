/**
 * @file       pool_allocator.hpp
 * @brief
 * @date       2021-01-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_POOL_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_POOL_ALLOCATOR_HPP

#include <kerbal/autonm/forward_list.hpp>
#include <kerbal/autonm/semi_allocator.hpp>
#include <kerbal/container/forward_list.hpp>
#include <kerbal/memory/new/over_aligned_new.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			class pool_allocator_base
			{
				public:
					typedef void*					pointer;
					typedef const void*				const_pointer;
					typedef std::size_t				size_type;
					typedef std::ptrdiff_t			difference_type;

				protected:
					typedef kerbal::autonm::forward_list<
						pointer,
						kerbal::autonm::discard_deallocate_semi_allocator<pointer>
					>																	head_type;
					typedef kerbal::container::detail::fl_type_unrelated				pool_type;
					typedef kerbal::type_traits::integral_constant<std::size_t, 32>		PER;

				protected:
					head_type head;
					pool_type pool;

				public:

					~pool_allocator_base()
					{
						typename head_type::iterator it(head.begin());
						typename head_type::iterator end(head.end());
						while (it != end) {
							::operator delete(*it, );
						}
					}

					pointer allocate(size_type size_required)
					{
						if (size_required % sizeof(void*) != 0) {
							size_required = size_required / sizeof(void*) * sizeof(void*) + 1;
						}
						if (pool.empty()) {
							size_type size_adjusted = size_required + ;
							void * p = ::operator new(size);
							head.push_front(p);

							pool_type::node_base * p_node = p;
							for (size_type i = 0; i + 1 < PER::value; ++i) {
								p_node[i].next = &p_node[i + 1];
							}

						}
						return static_cast<pointer>(operator new(sizeof(value_type) * n));
					}

					void deallocate(pointer p, size_type n)
					{

					}

			};

		} // namespace detail

		template <typename T>
		class pool_allocator :
			protected kerbal::memory::detail::pool_allocator_base
		{
			private:
				typedef kerbal::memory::detail::pool_allocator_base super;
		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_POOL_ALLOCATOR_HPP
