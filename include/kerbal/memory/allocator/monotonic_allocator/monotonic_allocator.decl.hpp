/**
 * @file       monotonic_allocator.decl.hpp
 * @brief
 * @date       2022-04-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_MONOTONIC_ALLOCATOR_MONOTONIC_ALLOCATOR_DECL_HPP
#define KERBAL_MEMORY_ALLOCATOR_MONOTONIC_ALLOCATOR_MONOTONIC_ALLOCATOR_DECL_HPP

#include <kerbal/memory/allocator/monotonic_allocator/monotonic_allocator.fwd.hpp>

#include <kerbal/autonm/forward_list.hpp>
#include <kerbal/autonm/semi_allocator/discard_deallocate_semi_allocator.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/detail/container_allocator_overload.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/pointer_alignment.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#include <kerbal/type_traits/is_nothrow_copy_constructible.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_move_constructible.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			struct mono_alloc_memory_block
			{
					void * gross_buffer;
					std::size_t gross_size_in_bytes;

					KERBAL_CONSTEXPR
					mono_alloc_memory_block(void * gross_buffer, std::size_t gross_size_in_bytes) KERBAL_NOEXCEPT :
							gross_buffer(gross_buffer), gross_size_in_bytes(gross_size_in_bytes)
					{
					}
			};


			template <typename T>
			struct monotonic_allocator_alignof_t :
					kerbal::type_traits::integral_constant<std::size_t, KERBAL_ALIGNOF(T)>
			{
			};

			template <>
			struct monotonic_allocator_alignof_t<void> :
					kerbal::memory::DEFAULT_ALIGNMENT
			{
			};

			template <typename T>
			struct monotonic_allocator_sizeof_t :
					kerbal::type_traits::integral_constant<std::size_t, sizeof(T)>
			{
			};

			template <>
			struct monotonic_allocator_sizeof_t<void> :
					kerbal::type_traits::integral_constant<std::size_t, 1>
			{
			};

			template <typename T, typename UpstreamAllocator>
			struct monotonic_allocator_typedef_helper
			{
					typedef T							value_type;
					typedef value_type *				pointer;

					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef kerbal::memory::detail::mono_alloc_memory_block		memory_block;
					typedef kerbal::autonm::forward_list<memory_block, kerbal::autonm::discard_deallocate_semi_allocator<memory_block> >
																				auto_list;
					typedef auto_list::auto_node								auto_node;

					typedef kerbal::container::detail::container_allocator_overload<
							UpstreamAllocator
					>															upstream_allocator_overload;

			};

		} // namespace detail



		template <typename T, typename UpstreamAllocator>
		class monotonic_allocator :
				private kerbal::utility::noncopyassignable,
				protected kerbal::memory::detail::monotonic_allocator_typedef_helper<T, UpstreamAllocator>::upstream_allocator_overload
		{
			private:
				typedef kerbal::memory::detail::monotonic_allocator_typedef_helper<T, UpstreamAllocator> typedef_helper;

				KERBAL_STATIC_ASSERT((
						kerbal::type_traits::is_same<
							typename kerbal::memory::allocator_traits<UpstreamAllocator>::value_type,
							void
						>::value
				), "allocator_traits<UpstreamAllocator>::value_type must be void");

				typedef typename typedef_helper::memory_block		memory_block;
				typedef typename typedef_helper::auto_list			auto_list;
				typedef typename typedef_helper::auto_node			auto_node;

				typedef typename typedef_helper::upstream_allocator_overload			upstream_allocator_overload;
				typedef typename upstream_allocator_overload::allocator_type			upstream_allocator;

				typedef kerbal::memory::detail::monotonic_allocator_alignof_t<T>		ALIGNOF_T;
				typedef kerbal::memory::detail::monotonic_allocator_sizeof_t<T>			SIZEOF_T;

			public:
				typedef typename typedef_helper::value_type			value_type;
				typedef typename typedef_helper::pointer			pointer;

				typedef typename typedef_helper::size_type			size_type;
				typedef typename typedef_helper::difference_type	difference_type;

				typedef kerbal::type_traits::false_type		propagate_on_container_copy_assignment;
				typedef kerbal::type_traits::false_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::true_type		propagate_on_container_swap;
				typedef kerbal::type_traits::false_type		is_always_equal;

			protected:
				auto_list		k_list;
				pointer			k_current_pure_buffer_head;
				size_type		k_current_used_in_bytes;
				pointer			k_current_buffer_end;


			protected:

				upstream_allocator &
				upstream_alloc() KERBAL_NOEXCEPT
				{
					return upstream_allocator_overload::alloc();
				}

				const upstream_allocator &
				upstream_alloc() const KERBAL_NOEXCEPT
				{
					return upstream_allocator_overload::alloc();
				}

			public:

#	if __cplusplus >= 201103L

				typedef kerbal::type_traits::tribool_constant<
						noexcept(
							upstream_allocator_overload::k_swap_allocator_if_propagate(
								kerbal::utility::declval<upstream_allocator_overload &>(),
								kerbal::utility::declval<upstream_allocator_overload &>()
							)
						)
				> try_test_is_nothrow_swappable;

#	else
				typedef kerbal::type_traits::tribool_unspecified try_test_is_nothrow_swappable;
#	endif


			public:

				monotonic_allocator() KERBAL_NOEXCEPT;

				typedef kerbal::type_traits::try_test_is_nothrow_copy_constructible<
						upstream_allocator_overload
				> try_test_is_nothrow_copy_constructible;

				monotonic_allocator(const monotonic_allocator & src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::type_traits::tribool_is_true<try_test_is_nothrow_copy_constructible>::value
						)
				;

#		if __cplusplus >= 201103L

				typedef try_test_is_nothrow_swappable try_test_is_nothrow_move_constructible;

				monotonic_allocator(monotonic_allocator && src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::type_traits::tribool_is_true<try_test_is_nothrow_move_constructible>::value
						)
				;

#		endif

				typedef kerbal::type_traits::try_test_is_nothrow_default_constructible<
						upstream_allocator_overload
				> try_test_is_nothrow_constructible_from_other;

				template <typename U, typename UpstreamAllocator2>
				monotonic_allocator(const monotonic_allocator<U, UpstreamAllocator2> &)
						KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::type_traits::tribool_is_true<try_test_is_nothrow_constructible_from_other>::value
						)
				;

				~monotonic_allocator();

#		if __cplusplus >= 201103L

				typedef try_test_is_nothrow_swappable try_test_is_nothrow_move_assignable;

				monotonic_allocator & operator=(monotonic_allocator && src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::type_traits::tribool_is_true<try_test_is_nothrow_move_assignable>::value
						)
				;

#		endif


			protected:

				size_type get_next_pure_buffer_size() const;

				void fill_buffer(size_type next_pure_buffer_size);

			public:

				typedef kerbal::type_traits::integral_constant<
						size_type,
						kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(value_type)
				> MAX_SIZE;

				typedef ALIGNOF_T MINIMUM_ALIGNMENT;

				pointer allocate(size_type n);

				pointer allocate(size_type n, kerbal::memory::align_val_t align);

				typedef kerbal::type_traits::true_type allow_deallocate_null;

				void deallocate(pointer /*p*/, size_type /*n*/) KERBAL_NOEXCEPT
				{
					// do nothing
				}

				void deallocate(pointer /*p*/, size_type /*n*/, kerbal::memory::align_val_t /*align*/) KERBAL_NOEXCEPT
				{
					// do nothing
				}

				bool operator!=(const monotonic_allocator & other) const KERBAL_NOEXCEPT
				{
					return this != &other;
				}

				bool operator==(const monotonic_allocator & other) const KERBAL_NOEXCEPT
				{
					return this == &other;
				}

				void swap(monotonic_allocator & other)
						KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::type_traits::tribool_is_true<try_test_is_nothrow_swappable>::value
						)
				;

		};

	} // namespace memory

	namespace algorithm
	{

		template <typename T, typename UpstreamAllocator>
		void swap(
				kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & lhs,
				kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & rhs
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
			kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & lhs,
			kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & rhs
	)
	KERBAL_CONDITIONAL_NOEXCEPT(
		noexcept(lhs.swap(rhs))
	)
	{
		lhs.swap(rhs);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_MEMORY_ALLOCATOR_MONOTONIC_ALLOCATOR_MONOTONIC_ALLOCATOR_DECL_HPP
