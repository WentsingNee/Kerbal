/**
 * @file       over_aligned_allocator.decl.hpp
 * @brief
 * @date       2023-01-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_DECL_HPP
#define KERBAL_MEMORY_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_DECL_HPP

#include <kerbal/memory/allocator/over_aligned_allocator/over_aligned_allocator.fwd.hpp>

// header(s) for default template argument(s)
#include <kerbal/memory/allocator/malloc_allocator/malloc_allocator.decl.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/config/compiler_id.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/nothrow_t.hpp>
#include <kerbal/memory/pointer_alignment.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		template <typename UpstreamAllocator>
		class over_aligned_allocator<void, UpstreamAllocator> :
				private kerbal::utility::member_compress_helper<UpstreamAllocator>
		{
			private:
				typedef kerbal::utility::member_compress_helper<UpstreamAllocator> upstream_allocator_compress_helper;
				typedef kerbal::memory::allocator_traits<UpstreamAllocator> upstream_allocator_traits;

				KERBAL_STATIC_ASSERT(
						(kerbal::type_traits::is_same<void, typename upstream_allocator_traits::value_type>::value),
						"UpstreamAllocator should be void type allocator"
				);

			public:
				typedef void						value_type;
				typedef value_type *				pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef typename upstream_allocator_traits::propagate_on_container_copy_assignment		propagate_on_container_copy_assignment;
				typedef typename upstream_allocator_traits::propagate_on_container_move_assignment		propagate_on_container_move_assignment;
				typedef typename upstream_allocator_traits::propagate_on_container_swap					propagate_on_container_swap;
				typedef typename upstream_allocator_traits::is_always_equal								is_always_equal;

			protected:
				UpstreamAllocator & upstream_alloc() KERBAL_NOEXCEPT
				{
					return upstream_allocator_compress_helper::member();
				}

				const UpstreamAllocator & upstream_alloc() const KERBAL_NOEXCEPT
				{
					return upstream_allocator_compress_helper::member();
				}

			public:

#		if __cplusplus >= 201103L

				over_aligned_allocator() = default;

#		else

				over_aligned_allocator()
				{
				}

#		endif

				KERBAL_CONSTEXPR
				over_aligned_allocator(const UpstreamAllocator & src) :
						upstream_allocator_compress_helper(kerbal::utility::in_place_t(), src)
				{
				}

				template <typename U>
				KERBAL_CONSTEXPR
				over_aligned_allocator(const over_aligned_allocator<U> & src) :
						upstream_allocator_compress_helper(
							kerbal::utility::in_place_t(),
							static_cast<const over_aligned_allocator<void> &>(src).upstream_alloc()
						)
				{
				}

			private:
				typedef void * void_p;

#		if __cplusplus < 201103L && KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG // clang could not detect private member under cxx98
			public:
				KERBAL_CONSTEXPR14
				size_type minimum_alignment() const KERBAL_NOEXCEPT
				{
					return upstream_allocator_traits::minimum_alignment(upstream_alloc());
				}
#		endif

			private:
				static pointer do_align(pointer p_raw, align_val_t align) KERBAL_NOEXCEPT;

			public:
				pointer allocate(size_type size, align_val_t align, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT;
				pointer allocate(size_type size, align_val_t align);

			public:
				typedef kerbal::type_traits::true_type allow_deallocate_null;

			private:
				void k_deallocate_upstream_allow_deallocate_null(pointer p, size_type size, align_val_t align, kerbal::type_traits::false_type) KERBAL_NOEXCEPT;
				void k_deallocate_upstream_allow_deallocate_null(pointer p, size_type size, align_val_t align, kerbal::type_traits::true_type) KERBAL_NOEXCEPT;

			public:

				void deallocate(pointer p, size_type size, align_val_t align) KERBAL_NOEXCEPT;
				void deallocate(pointer p, size_type size, align_val_t align, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				bool operator!=(const over_aligned_allocator & other) const KERBAL_NOEXCEPT
				{
					return this->upstream_alloc() != other.upstream_alloc();
				}

				KERBAL_CONSTEXPR
				bool operator==(const over_aligned_allocator & other) const KERBAL_NOEXCEPT
				{
					return this->upstream_alloc() == other.upstream_alloc();
				}

				KERBAL_CONSTEXPR14
				void swap(over_aligned_allocator & other) KERBAL_NOEXCEPT
				{
					kerbal::algorithm::swap(this->upstream_alloc(), other.upstream_alloc());
				}

		};


		template <typename T, typename UpstreamAllocator>
		class over_aligned_allocator :
				private kerbal::memory::over_aligned_allocator<void, UpstreamAllocator>
		{
			private:
				typedef kerbal::memory::over_aligned_allocator<void, UpstreamAllocator> super;
				typedef kerbal::memory::allocator_traits<super> super_allocator_traits;

			public:
				typedef T							value_type;
				typedef value_type *				pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef typename super_allocator_traits::propagate_on_container_copy_assignment		propagate_on_container_copy_assignment;
				typedef typename super_allocator_traits::propagate_on_container_move_assignment		propagate_on_container_move_assignment;
				typedef typename super_allocator_traits::propagate_on_container_swap				propagate_on_container_swap;
				typedef typename super_allocator_traits::is_always_equal							is_always_equal;

				template <typename U, typename UpstreamAllocator2>
				friend class kerbal::memory::over_aligned_allocator;

			protected:
				super & void_alloc() KERBAL_NOEXCEPT
				{
					return static_cast<super &>(*this);
				}

				const super & void_alloc() const KERBAL_NOEXCEPT
				{
					return static_cast<const super &>(*this);
				}

			public:

#		if __cplusplus >= 201103L

				over_aligned_allocator() = default;

#		else

				over_aligned_allocator() KERBAL_NOEXCEPT
				{
				}

#		endif

				KERBAL_CONSTEXPR
				over_aligned_allocator(const UpstreamAllocator & src) :
						super(src)
				{
				}

				KERBAL_CONSTEXPR
				over_aligned_allocator(const over_aligned_allocator<void, UpstreamAllocator> & src) :
						super(src)
				{
				}

				template <typename U>
				KERBAL_CONSTEXPR
				over_aligned_allocator(const over_aligned_allocator<U, UpstreamAllocator> & src) :
						super(src.void_alloc())
				{
				}

			public:
				KERBAL_CONSTEXPR14
				size_type minimum_alignment() const KERBAL_NOEXCEPT
				{
					size_type super_ma = super_allocator_traits::minimum_alignment(void_alloc());
					return super_ma > KERBAL_ALIGNOF(value_type) ? super_ma : KERBAL_ALIGNOF(value_type);
				}

				typedef kerbal::type_traits::integral_constant<
						size_type,
						kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(value_type)
				> MAX_SIZE;

				pointer allocate(size_type n, align_val_t align);
				pointer allocate(size_type n, align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT;
				pointer allocate(size_type n);
				pointer allocate(size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT;

				typedef typename super_allocator_traits::allow_deallocate_null allow_deallocate_null;

				void deallocate(pointer p, size_type n, align_val_t align) KERBAL_NOEXCEPT;
				void deallocate(pointer p, size_type n, align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT;
				void deallocate(pointer p, size_type n) KERBAL_NOEXCEPT;
				void deallocate(pointer p, size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				bool operator!=(const over_aligned_allocator & other) const KERBAL_NOEXCEPT
				{
					return this->void_alloc() != other.void_alloc();
				}

				KERBAL_CONSTEXPR
				bool operator==(const over_aligned_allocator & other) const KERBAL_NOEXCEPT
				{
					return this->void_alloc() == other.void_alloc();
				}

				KERBAL_CONSTEXPR14
				void swap(over_aligned_allocator & other) KERBAL_NOEXCEPT
				{
					kerbal::algorithm::swap(this->void_alloc(), other.void_alloc());
				}

		};

	} // namespace memory

	namespace algorithm
	{

		template <typename T, typename UpstreamAllocator>
		KERBAL_CONSTEXPR14
		void swap(
				kerbal::memory::over_aligned_allocator<T, UpstreamAllocator> & lhs,
				kerbal::memory::over_aligned_allocator<T, UpstreamAllocator> & rhs)
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
	KERBAL_CONSTEXPR14
	void swap(
			kerbal::memory::over_aligned_allocator<T, UpstreamAllocator> & lhs,
			kerbal::memory::over_aligned_allocator<T, UpstreamAllocator> & rhs)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(lhs.swap(rhs))
			)
	{
		lhs.swap(rhs);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_MEMORY_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_DECL_HPP
