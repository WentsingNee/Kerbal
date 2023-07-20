/**
 * @file       fixed_size_node_allocator.impl.hpp
 * @brief
 * @date       2023-07-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_IMPL_HPP
#define KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_IMPL_HPP

#include <kerbal/memory/allocator/fixed_size_node_allocator/fixed_size_node_allocator.decl.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename T, typename UpstreamAllocator>
		fixed_size_node_allocator<T, UpstreamAllocator>::~fixed_size_node_allocator()
		{
			typedef kerbal::memory::allocator_traits<memory_blocks_allocator> allocator_traits;
			typedef typename allocated_blocks_ptr_list_type::const_iterator iterator;
			iterator before_begin = this->k_allocated_blocks_ptr_list.before_begin();
			while (!this->k_allocated_blocks_ptr_list.empty()) {
				iterator cur = this->k_allocated_blocks_ptr_list.begin();
				memory_blocks_type * memory_block = *cur;
				this->k_allocated_blocks_ptr_list.erase_after(before_begin);
				allocator_traits::destroy(memory_block_alloc(), memory_block);
				allocator_traits::deallocate_one(memory_block_alloc(), memory_block);
			}
		}

		template <typename T, typename UpstreamAllocator>
		typename fixed_size_node_allocator<T, UpstreamAllocator>::pointer
		fixed_size_node_allocator<T, UpstreamAllocator>::allocate_one()
		{
			if (this->k_free_list.empty()) {
				memory_blocks_type * allocated_blocks_ptr = this->build_memory_block();
				this->k_allocated_blocks_ptr_list.push_front(allocated_blocks_ptr->k_allocated_blocks_ptr_node);
				this->k_free_list.k_hook_node_after(
						this->k_free_list.basic_before_begin(),
						&allocated_blocks_ptr->k_embedded_block[0].interpret_as_free_list_node(),
						&allocated_blocks_ptr->k_embedded_block[BLOCK_LENGTH::value - 1].interpret_as_free_list_node());
			}

			free_list_node_type * p_free_list_node = this->k_free_list.k_unhook_node_after(this->k_free_list.basic_before_begin());
			return reinterpret_cast<pointer>(p_free_list_node);
		}

		template <typename T, typename UpstreamAllocator>
		typename fixed_size_node_allocator<T, UpstreamAllocator>::pointer
		fixed_size_node_allocator<T, UpstreamAllocator>::allocate(size_type n)
		{
			if (n != 1) {
				return this->size_over_large_allocate(n);
			}

			return this->allocate_one();
		}

		template <typename T, typename UpstreamAllocator>
		void fixed_size_node_allocator<T, UpstreamAllocator>::deallocate_one(pointer p) KERBAL_NOEXCEPT
		{
			free_list_node_type * p_free_list_node = reinterpret_cast<free_list_node_type *>(p);
			k_free_list.k_hook_node_after(k_free_list.basic_before_begin(), p_free_list_node);
		}

		template <typename T, typename UpstreamAllocator>
		void fixed_size_node_allocator<T, UpstreamAllocator>::deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
		{
			if (n != 1) {
				this->size_over_large_deallocate(p, n);
				return;
			}

			this->deallocate_one(p);
		}

		template <typename T, typename UpstreamAllocator>
		typename fixed_size_node_allocator<T, UpstreamAllocator>::pointer
		fixed_size_node_allocator<T, UpstreamAllocator>::size_over_large_allocate(size_type n)
		{
			typedef kerbal::memory::allocator_traits<size_over_large_allocator> allocator_traits;
			return allocator_traits::allocate(this->size_over_large_alloc(), n);
		}

		template <typename T, typename UpstreamAllocator>
		void fixed_size_node_allocator<T, UpstreamAllocator>::size_over_large_deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
		{
			typedef kerbal::memory::allocator_traits<size_over_large_allocator> allocator_traits;
			return allocator_traits::deallocate(this->size_over_large_alloc(), p, n);
		}

		template <typename T, typename UpstreamAllocator>
		void fixed_size_node_allocator<T, UpstreamAllocator>::swap(fixed_size_node_allocator & other)
				KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_swappable::value)
		{
			kerbal::algorithm::swap(this->size_over_large_alloc(), other.size_over_large_alloc());
			kerbal::algorithm::swap(this->memory_block_alloc(), other.memory_block_alloc());
			this->k_allocated_blocks_ptr_list.swap(other.k_allocated_blocks_ptr_list);
			free_list_type::k_swap_type_unrelated(this->k_free_list, other.k_free_list);
		}

		template <typename T, typename UpstreamAllocator>
		typename fixed_size_node_allocator<T, UpstreamAllocator>::memory_blocks_type *
		fixed_size_node_allocator<T, UpstreamAllocator>::build_memory_block()
		{
			typedef kerbal::memory::allocator_traits<memory_blocks_allocator> allocator_traits;
			memory_blocks_type * memory_block = allocator_traits::allocate_one(this->memory_block_alloc());
			allocator_traits::construct(this->memory_block_alloc(), memory_block);
			return memory_block;
		}


	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_IMPL_HPP
