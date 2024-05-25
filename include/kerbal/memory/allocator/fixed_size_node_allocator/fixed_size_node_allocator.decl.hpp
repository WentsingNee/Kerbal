/**
 * @file       fixed_size_node_allocator.decl.hpp
 * @brief
 * @date       2021-03-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_DECL_HPP
#define KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_DECL_HPP

#include <kerbal/memory/allocator/fixed_size_node_allocator/fixed_size_node_allocator.fwd.hpp>

// header(s) for default template argument(s)
#include <kerbal/memory/allocator/default_allocator/default_allocator.decl.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/autonm/forward_list.hpp>
#include <kerbal/autonm/semi_allocator/discard_deallocate_semi_allocator.hpp>
#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/detail/container_rebind_allocator_overload.hpp>
#include <kerbal/container/detail/single_list_base/single_list_node.hpp>
#include <kerbal/container/detail/forward_list_base.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/noncopyable.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <std::size_t Size, std::size_t Align>
			union embedded_block
			{
				private:
					typedef kerbal::container::detail::sl_node_base free_list_node;

					typename kerbal::type_traits::aligned_storage<
						sizeof(free_list_node),
						KERBAL_ALIGNOF(free_list_node)
					>::type k_free_list_node;

					typename kerbal::type_traits::aligned_storage<Size, Align>::type k_data;

				public:
					free_list_node & interpret_as_free_list_node()
					{
						return reinterpret_cast<free_list_node &>(this->k_free_list_node);
					}
			};

			template <typename T, std::size_t N>
			struct fsn_alloc_memory_blocks
			{
					typedef typename kerbal::autonm::forward_list<
						fsn_alloc_memory_blocks *,
						kerbal::autonm::discard_deallocate_semi_allocator<fsn_alloc_memory_blocks *>
					>::auto_node auto_node;

					auto_node k_allocated_blocks_ptr_node;
					embedded_block<sizeof(T), KERBAL_ALIGNOF(T)> k_embedded_block[N];

					fsn_alloc_memory_blocks() KERBAL_NOEXCEPT :
						k_allocated_blocks_ptr_node(kerbal::utility::in_place_t(), this)
					{
						for (std::size_t i = 0; i < N - 1; ++i) {
							this->k_embedded_block[i].interpret_as_free_list_node().next =
								&this->k_embedded_block[i + 1].interpret_as_free_list_node();
						}
						this->k_embedded_block[N - 1].interpret_as_free_list_node().next = NULL;
					}
			};

			template <typename T, typename UpstreamAllocator>
			struct fixed_size_node_allocator_typedef_helper
			{
					typedef T							value_type;
					typedef value_type *				pointer;

					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef kerbal::type_traits::integral_constant<std::size_t, 512>					BLOCK_LENGTH;
					typedef kerbal::memory::detail::fsn_alloc_memory_blocks<value_type, BLOCK_LENGTH::value>
																										memory_blocks_type;
					typedef kerbal::autonm::forward_list<
						memory_blocks_type *,
						kerbal::autonm::discard_deallocate_semi_allocator<memory_blocks_type *>
					>																					allocated_blocks_ptr_list_type;
					typedef kerbal::container::detail::sl_node_base										free_list_node_type;
					typedef kerbal::container::detail::fl_type_unrelated 								free_list_type;

					typedef kerbal::container::detail::container_rebind_allocator_overload<
						UpstreamAllocator,
						value_type
					>																					size_over_large_allocator_rebind_overload;

					typedef kerbal::container::detail::container_rebind_allocator_overload<
						UpstreamAllocator,
						memory_blocks_type
					>																					memory_blocks_allocator_rebind_overload;

			};

		} // namespace detail


		template <typename T, typename UpstreamAllocator>
		class fixed_size_node_allocator :
			private kerbal::utility::noncopyassignable,
			protected kerbal::memory::detail::fixed_size_node_allocator_typedef_helper<
				T, UpstreamAllocator
			>::size_over_large_allocator_rebind_overload,
			protected kerbal::memory::detail::fixed_size_node_allocator_typedef_helper<
				T, UpstreamAllocator
			>::memory_blocks_allocator_rebind_overload
		{
			private:
				typedef kerbal::memory::detail::fixed_size_node_allocator_typedef_helper<T, UpstreamAllocator> typedef_helper;

			public:
				typedef typename typedef_helper::value_type			value_type;
				typedef typename typedef_helper::pointer			pointer;

				typedef typename typedef_helper::size_type			size_type;
				typedef typename typedef_helper::difference_type	difference_type;

				template <typename U>
				struct rebind
				{
					private:
						typedef kerbal::memory::allocator_traits<UpstreamAllocator> upstream_allocator_traits;
						typedef typename upstream_allocator_traits::template rebind_alloc<U>::other upstream_rebind_allocator;

					public:
						typedef fixed_size_node_allocator<U, upstream_rebind_allocator> other;
				};

				typedef kerbal::type_traits::false_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::true_type		propagate_on_container_swap;
				typedef kerbal::type_traits::false_type		is_always_equal;

			private:
				typedef typename typedef_helper::BLOCK_LENGTH				BLOCK_LENGTH;
				typedef typename typedef_helper::memory_blocks_type			memory_blocks_type;
				typedef typename typedef_helper::allocated_blocks_ptr_list_type
																			allocated_blocks_ptr_list_type;
				typedef typename typedef_helper::free_list_node_type		free_list_node_type;
				typedef typename typedef_helper::free_list_type				free_list_type;

				typedef typename typedef_helper::size_over_large_allocator_rebind_overload
						size_over_large_allocator_rebind_overload;

				typedef typename size_over_large_allocator_rebind_overload::rebind_allocator_type
						size_over_large_allocator;

				typedef typename typedef_helper::memory_blocks_allocator_rebind_overload
						memory_blocks_allocator_rebind_overload;

				typedef typename memory_blocks_allocator_rebind_overload::rebind_allocator_type
						memory_blocks_allocator;

			protected:

				allocated_blocks_ptr_list_type		k_allocated_blocks_ptr_list;
				free_list_type						k_free_list;


			protected:

				size_over_large_allocator &
				size_over_large_alloc() KERBAL_NOEXCEPT
				{
					return size_over_large_allocator_rebind_overload::alloc();
				}

				const size_over_large_allocator &
				size_over_large_alloc() const KERBAL_NOEXCEPT
				{
					return size_over_large_allocator_rebind_overload::alloc();
				}

				memory_blocks_allocator &
				memory_block_alloc() KERBAL_NOEXCEPT
				{
					return memory_blocks_allocator_rebind_overload::alloc();
				}

				const memory_blocks_allocator &
				memory_block_alloc() const KERBAL_NOEXCEPT
				{
					return memory_blocks_allocator_rebind_overload::alloc();
				}

#		if __cplusplus >= 201103L

			public:

				typedef kerbal::type_traits::bool_constant<
					noexcept(
						kerbal::algorithm::swap(
							kerbal::utility::declval<size_over_large_allocator &>(),
							kerbal::utility::declval<size_over_large_allocator &>()
						)
					) &&
					noexcept(
						kerbal::algorithm::swap(
							kerbal::utility::declval<memory_blocks_allocator &>(),
							kerbal::utility::declval<memory_blocks_allocator &>()
						)
					)
				> is_nothrow_swappable;

#		endif


			public:

#		if __cplusplus >= 201103L

				fixed_size_node_allocator() = default;

#		else

				fixed_size_node_allocator() KERBAL_NOEXCEPT
				{
				}

#		endif

				fixed_size_node_allocator(const fixed_size_node_allocator & src) KERBAL_NOEXCEPT :
					size_over_large_allocator_rebind_overload(src.size_over_large_alloc()),
					memory_blocks_allocator_rebind_overload(src.memory_block_alloc())
				{
				}

#		if __cplusplus >= 201103L

				typedef is_nothrow_swappable is_nothrow_move_constructible;

				fixed_size_node_allocator(fixed_size_node_allocator && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_constructible::value) :
					fixed_size_node_allocator()
				{
					this->swap(src);
				}

#		endif

				template <typename U, typename UpstreamAllocator2>
				fixed_size_node_allocator(const fixed_size_node_allocator<U, UpstreamAllocator2> &) KERBAL_NOEXCEPT
				{
				}

				~fixed_size_node_allocator();

#		if __cplusplus >= 201103L

				typedef is_nothrow_swappable is_nothrow_move_assignable;

				fixed_size_node_allocator & operator=(fixed_size_node_allocator && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_assignable::value)
				{
					this->swap(src);
					return *this;
				}

#		endif

			public:
				pointer allocate_one();
				pointer allocate(size_type n);

				typedef kerbal::type_traits::false_type allow_deallocate_null;

				void deallocate_one(pointer p) KERBAL_NOEXCEPT;
				void deallocate(pointer p, size_type n) KERBAL_NOEXCEPT;

				bool operator!=(const fixed_size_node_allocator & other) const KERBAL_NOEXCEPT
				{
					return this != &other;
				}

				bool operator==(const fixed_size_node_allocator & other) const KERBAL_NOEXCEPT
				{
					return this == &other;
				}

				void swap(fixed_size_node_allocator & other)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_swappable::value)
				;

			private:
				pointer size_over_large_allocate(size_type n);

				void size_over_large_deallocate(pointer p, size_type n) KERBAL_NOEXCEPT;

				memory_blocks_type * build_memory_block();

		};

	} // namespace memory

	namespace algorithm
	{

		template <typename T, typename UpstreamAllocator>
		void swap(
			kerbal::memory::fixed_size_node_allocator<T, UpstreamAllocator> & lhs,
			kerbal::memory::fixed_size_node_allocator<T, UpstreamAllocator> & rhs
		)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(lhs.swap(rhs))
			)
		{
			lhs.swap(rhs);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename UpstreamAllocator>
	void swap(
		kerbal::memory::fixed_size_node_allocator<T, UpstreamAllocator> & lhs,
		kerbal::memory::fixed_size_node_allocator<T, UpstreamAllocator> & rhs
	)
		KERBAL_CONDITIONAL_NOEXCEPT(
			noexcept(lhs.swap(rhs))
		)
	{
		lhs.swap(rhs);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_DECL_HPP
