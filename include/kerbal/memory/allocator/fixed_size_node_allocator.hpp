/**
 * @file       fixed_size_node_allocator.hpp
 * @brief
 * @date       2021-03-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_HPP

#include <kerbal/autonm/forward_list.hpp>
#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/container/detail/single_list_node.hpp>
#include <kerbal/container/detail/forward_list_base.hpp>
#include <kerbal/memory/allocator/detail/cxx98_allocator_base.hpp>
#include <kerbal/memory/new/over_aligned_new.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/noncopyable.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename Tp>
			union embedded
			{
				private:
					typedef  kerbal::container::detail::sl_node_base sl_node_base;

					typename kerbal::type_traits::aligned_storage<sizeof(sl_node_base), KERBAL_ALIGNOF(sl_node_base)>::type _K_node;
					typename kerbal::type_traits::aligned_storage<sizeof(Tp), KERBAL_ALIGNOF(Tp)>::type _K_val;

				public:
					sl_node_base& node()
					{
						return reinterpret_cast<sl_node_base&>(*this);
					}
			};

			template <typename Tp, std::size_t N>
			struct block
			{
					typedef typename kerbal::autonm::forward_list<block*, void>::auto_node auto_node;

					auto_node _K_block_ptr_node;
					embedded<Tp> _K_embedded_node[N];
			};

		} // namespace detail

		template <typename Tp>
		class fixed_size_node_allocator:
				private kerbal::utility::noncopyable,
				public kerbal::memory::detail::cxx98_allocator_base<Tp>
		{
			public:
				typedef Tp							value_type;
				typedef value_type*					pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef kerbal::type_traits::true_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::false_type		is_always_equal;
				typedef kerbal::container::detail::sl_node_base		fl_node_base;

			private:
				typedef kerbal::type_traits::integral_constant<std::size_t, 16> BLOCK_LENGTH;
				typedef kerbal::memory::detail::block<Tp, BLOCK_LENGTH::value> block_type;

			private:
				kerbal::autonm::forward_list<block_type*, void>		_K_allocated_ptr_list;
				kerbal::container::detail::fl_type_unrelated		_K_embedded_buffer_list;

			public:

#			if __cplusplus < 201103L

				fixed_size_node_allocator() KERBAL_NOEXCEPT
				{
				}

#			else

				fixed_size_node_allocator() = default;

				fixed_size_node_allocator(fixed_size_node_allocator && src) KERBAL_NOEXCEPT
						: _K_allocated_ptr_list(kerbal::compatibility::move(src)._K_allocated_ptr_list),
						  _K_embedded_buffer_list(kerbal::compatibility::move(src)._K_embedded_buffer_list)
				{
				}

#			endif

				template <typename Up>
				fixed_size_node_allocator(const fixed_size_node_allocator<Up> &) KERBAL_NOEXCEPT
				{
				}

				~fixed_size_node_allocator() KERBAL_NOEXCEPT
				{
					typedef typename kerbal::autonm::forward_list<block_type*, void>::const_iterator const_iterator;

					const_iterator it(_K_allocated_ptr_list.begin());
					const_iterator const end(_K_allocated_ptr_list.end());
					while (it != end) {
						const_iterator next(it);
						++next;
						block_deallocate(*it);
						it = next;
					}
				}

				pointer allocate(size_type n)
				{
					if (n != 1) {
						return size_over_large_allocate(n);
					}

					if (_K_embedded_buffer_list.empty()) {
						block_type * block_ptr = block_allocate();
						block_ptr->_K_block_ptr_node.value = block_ptr;
						for (std::size_t i = 0; i < BLOCK_LENGTH::value - 1; ++i) {
							block_ptr->_K_embedded_node[i].node().next = &block_ptr->_K_embedded_node[i + 1].node();
						}
						block_ptr->_K_embedded_node[BLOCK_LENGTH::value - 1].node().next = NULL;
						_K_embedded_buffer_list._K_hook_node_after(
								_K_embedded_buffer_list.basic_before_begin(),
								&block_ptr->_K_embedded_node[0].node(),
								&block_ptr->_K_embedded_node[BLOCK_LENGTH::value - 1].node());
						_K_allocated_ptr_list.push_front(block_ptr->_K_block_ptr_node);
					}

					fl_node_base * p_node = _K_embedded_buffer_list._K_unhook_node_after(_K_embedded_buffer_list.basic_before_begin());
					return reinterpret_cast<pointer>(p_node);
				}

				void deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
				{
					if (n != 1) {
						size_over_large_deallocate(p, n);
						return;
					}

					fl_node_base * p_node = reinterpret_cast<fl_node_base *>(p);
					_K_embedded_buffer_list._K_hook_node_after(_K_embedded_buffer_list.basic_before_begin(), p_node);
				}

			private:

				static pointer size_over_large_allocate(size_type n)
				{
					void * p = ::operator new[](n * sizeof(value_type), kerbal::memory::align_val_t(KERBAL_ALIGNOF(value_type)));
					return static_cast<pointer>(p);
				}

				static void size_over_large_deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
				{
					::operator delete[](p, n * sizeof(value_type), kerbal::memory::align_val_t(KERBAL_ALIGNOF(value_type)));
				}

				static block_type * block_allocate()
				{
					void * p = ::operator new(sizeof(block_type), kerbal::memory::align_val_t(KERBAL_ALIGNOF(block_type)));
					return static_cast<block_type*>(p);
				}

				static void block_deallocate(block_type * p) KERBAL_NOEXCEPT
				{
					::operator delete(p, sizeof(block_type), kerbal::memory::align_val_t(KERBAL_ALIGNOF(block_type)));
				}

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_HPP
