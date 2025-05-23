/**
 * @file       over.hpp
 * @brief
 * @date       2023-01-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_ORI_OVER_HPP
#define KERBAL_MEMORY_ALLOCATOR_ORI_OVER_HPP

#include <kerbal/memory/allocator/over_aligned_allocator/over_aligned_allocator.fwd.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/bad_alloc.hpp>
#include <kerbal/memory/pointer_alignment.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

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

			private:

				static pointer do_align(pointer p_raw, align_val_t align) KERBAL_NOEXCEPT
				{
					std::size_t p_raw_sz = reinterpret_cast<std::size_t>(p_raw);

					std::size_t pt_sz = kerbal::memory::align_ceil(kerbal::memory::align_ceil(p_raw_sz, KERBAL_ALIGNOF(void_p)) + sizeof(void_p), align);
					std::size_t pu_sz = kerbal::memory::align_floor(pt_sz - sizeof(void_p), KERBAL_ALIGNOF(void_p));

					void_p * pu = reinterpret_cast<void_p *>(pu_sz);
					*pu = p_raw;

					pointer p = reinterpret_cast<pointer>(pt_sz);
					return p;
				}

			public:

				KERBAL_CONSTEXPR14
				size_type minimum_alignment() const KERBAL_NOEXCEPT
				{
					return upstream_allocator_traits::minimum_alignment(upstream_alloc());
				}


				pointer allocate(size_type size, align_val_t align, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
				{
					std::size_t basic_align = upstream_allocator_traits::minimum_alignment(upstream_alloc());

					pointer p_raw = NULL;
					if (align <= basic_align) {
						try {
							p_raw = upstream_allocator_traits::allocate(upstream_alloc(), size);
						} catch (...) {
							return NULL;
						}
						return p_raw;
					}

					std::size_t raw_allocate_size =
							kerbal::memory::alignment_maximum_offset(KERBAL_ALIGNOF(void_p), basic_align) +
									sizeof(void_p) +
							kerbal::memory::alignment_maximum_offset(align.val, KERBAL_ALIGNOF(void_p)) +
							size
					;
					try {
						p_raw = upstream_allocator_traits::allocate(upstream_alloc(), raw_allocate_size);
					} catch (...) {
						return NULL;
					}
					if (p_raw == NULL) {
						return NULL;
					}

					return do_align(p_raw, align);
				}

				pointer allocate(size_type size, align_val_t align)
				{
					std::size_t basic_align = upstream_allocator_traits::minimum_alignment(upstream_alloc());

					pointer p_raw = NULL;
					if (align <= basic_align) {
						p_raw = upstream_allocator_traits::allocate(upstream_alloc(), size);
						return p_raw;
					}

					std::size_t raw_allocate_size =
							kerbal::memory::alignment_maximum_offset(KERBAL_ALIGNOF(void_p), basic_align) +
									sizeof(void_p) +
							kerbal::memory::alignment_maximum_offset(align.val, KERBAL_ALIGNOF(void_p)) +
							size
					;
					p_raw = upstream_allocator_traits::allocate(upstream_alloc(), raw_allocate_size);

					return do_align(p_raw, align);
				}

				pointer allocate(size_type size, size_type align)
				{
					pointer p = allocate(size, align, kerbal::memory::nothrow_t());
					if (p == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
					return p;
				}


			public:
				typedef kerbal::type_traits::true_type allow_deallocate_null;

			private:
				void k_deallocate_upstream_allow_deallocate_null(pointer p, size_type size, align_val_t align, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
				{
					if (p == NULL) {
						return;
					}

					std::size_t basic_align = upstream_allocator_traits::minimum_alignment(upstream_alloc());

					if (align <= basic_align) {
						upstream_allocator_traits::deallocate(upstream_alloc(), p, size);
						return;
					}

					std::size_t raw_allocate_size =
							kerbal::memory::alignment_maximum_offset(KERBAL_ALIGNOF(void_p), basic_align) +
							sizeof(void_p) +
							kerbal::memory::alignment_maximum_offset(align.val, KERBAL_ALIGNOF(void_p)) +
							size
					;
					std::size_t pt_sz = reinterpret_cast<std::size_t>(p);
					std::size_t pu_sz = kerbal::memory::align_floor(pt_sz - sizeof(void_p), KERBAL_ALIGNOF(void_p));
					void_p * pu = reinterpret_cast<void_p *>(pu_sz);
					pointer p_raw = *pu;
					upstream_allocator_traits::deallocate(upstream_alloc(), p_raw, raw_allocate_size);
				}

				void k_deallocate_upstream_allow_deallocate_null(pointer p, size_type size, align_val_t align, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
				{
					pointer p_raw;
					std::size_t raw_allocate_size;

					if (p == NULL) {
						p_raw = p;
						raw_allocate_size = size;
					} else {
						std::size_t basic_align = upstream_allocator_traits::minimum_alignment(upstream_alloc());

						if (align <= basic_align) {
							p_raw = p;
							raw_allocate_size = size;
						} else {
							raw_allocate_size =
									kerbal::memory::alignment_maximum_offset(KERBAL_ALIGNOF(void_p), basic_align) +
									sizeof(void_p) +
									kerbal::memory::alignment_maximum_offset(align.val, KERBAL_ALIGNOF(void_p)) +
									size
							;
							std::size_t pt_sz = reinterpret_cast<std::size_t>(p);
							std::size_t pu_sz = kerbal::memory::align_floor(pt_sz - sizeof(void_p), KERBAL_ALIGNOF(void_p));
							void_p * pu = reinterpret_cast<void_p *>(pu_sz);
							p_raw = *pu;
						}
					}

					upstream_allocator_traits::deallocate(upstream_alloc(), p_raw, raw_allocate_size);
				}

			public:

				void deallocate(pointer p, size_type size, align_val_t align) KERBAL_NOEXCEPT
				{
					this->k_deallocate_upstream_allow_deallocate_null(p, size, align, typename upstream_allocator_traits::allow_deallocate_null());
				}

				void deallocate(pointer p, size_type size, align_val_t align, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
				{
					deallocate(p, size, align);
				}

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


				KERBAL_CONSTEXPR14
				size_type minimum_alignment() const KERBAL_NOEXCEPT
				{
					size_type super_ma = super_allocator_traits::minimum_alignment(void_alloc());
					return super_ma > KERBAL_ALIGNOF(value_type) ? super_ma : KERBAL_ALIGNOF(value_type);
				}

				pointer allocate(size_type n, align_val_t align)
				{
					void * p = super::allocate(n * sizeof(value_type), align);
					return static_cast<pointer>(p);
				}

				pointer allocate(size_type n, align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
				{
					void * p = super::allocate(n * sizeof(value_type), align, nothrow);
					return static_cast<pointer>(p);
				}

				pointer allocate(size_type n)
				{
					return allocate(n, KERBAL_ALIGNOF(value_type));
				}

				pointer allocate(size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
				{
					return allocate(n, KERBAL_ALIGNOF(value_type), nothrow);
				}


				typedef typename super_allocator_traits::allow_deallocate_null allow_deallocate_null;

				void deallocate(pointer p, size_type n, align_val_t align) KERBAL_NOEXCEPT
				{
					super::deallocate(p, n * sizeof(value_type), align);
				}

				void deallocate(pointer p, size_type n, align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
				{
					super::deallocate(p, n * sizeof(value_type), align, nothrow);
				}

				void deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
				{
					deallocate(p, n, KERBAL_ALIGNOF(value_type));
				}

				void deallocate(pointer p, size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
				{
					deallocate(p, n, KERBAL_ALIGNOF(value_type), nothrow);
				}

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
					this->void_alloc().swap(other.void_alloc());
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


#endif // KERBAL_MEMORY_ALLOCATOR_ORI_OVER_HPP
