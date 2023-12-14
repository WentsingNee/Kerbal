/**
 * @file       bitset.hpp
 * @brief
 * @date       2023-12-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_BITSET_HPP
#define KERBAL_BITSET_BITSET_HPP

#include <kerbal/bitset/bitset/bitset.fwd.hpp>
#include <kerbal/bitset/detail/bitset_size_unrelated.hpp>
#include <kerbal/container/detail/container_allocator_overload.hpp>

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/algorithm/modifier/fill.hpp>
#include <kerbal/compare/minmax.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/numeric/bit.hpp>

#include <cstddef>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			template <typename Block>
			class bitset_block_only :
				private kerbal::bitset::detail::bitset_size_unrelated<Block>
			{
				private:
					typedef kerbal::bitset::detail::bitset_size_unrelated<Block>	bitset_size_unrelated;

					using bitset_size_unrelated::ALL_ONE;
					typedef typename bitset_size_unrelated::BITS_PER_BLOCK			BITS_PER_BLOCK;

				public:
					typedef Block block_type;
					typedef std::size_t size_type;
					typedef std::size_t block_size_type;

				private:
					block_type * k_block;
					size_type k_size_of_bits;

				private:
					KERBAL_CONSTEXPR20
					static
					block_size_type k_size_of_blocks(size_type size_in_bits) KERBAL_NOEXCEPT
					{
						return size_in_bits / BITS_PER_BLOCK::value + (size_in_bits % BITS_PER_BLOCK::value != 0);
					}

				public:
					KERBAL_CONSTEXPR20
					bitset_block_only() KERBAL_NOEXCEPT :
						k_block(NULL), k_size_of_bits(0)
					{
					}

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					bitset_block_only(Allocator & alloc, size_type size_in_bits, bool value)
					{
						typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
						this->k_size_of_bits = size_in_bits;
						block_size_type size_of_blocks = this->block_size();
						this->k_block = allocator_traits::allocate(alloc, size_of_blocks);
						if (value) {
							kerbal::algorithm::fill(this->k_block, this->k_block + size_of_blocks, ALL_ONE::value);
						} else {
							kerbal::algorithm::fill(this->k_block, this->k_block + size_of_blocks, 0);
						}
					}

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					bitset_block_only(Allocator & alloc, const bitset_block_only & src)
					{
						typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
						this->k_size_of_bits = src.k_size_of_bits;
						block_size_type size_of_blocks = this->block_size();
						this->k_block = allocator_traits::allocate(alloc, size_of_blocks);
						kerbal::algorithm::copy(src.k_block, src.k_block + size_of_blocks, this->k_block);
					}

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void destroy_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT
					{
						typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
						if (allocator_traits::allow_deallocate_null::value || this->k_block != NULL) {
							block_size_type size_of_blocks = this->block_size();
							allocator_traits::deallocate(alloc, this->k_block, size_of_blocks);
						}
					}

					KERBAL_CONSTEXPR20
					size_type size() const KERBAL_NOEXCEPT
					{
						return this->k_size_of_bits;
					}

					KERBAL_CONSTEXPR20
					block_size_type block_size() const KERBAL_NOEXCEPT
					{
						return k_size_of_blocks(this->k_size_of_bits);
					}

				private:
					KERBAL_CONSTEXPR20
					size_type tail_size() const KERBAL_NOEXCEPT
					{
						return this->k_size_of_bits % BITS_PER_BLOCK::value;
					}

					KERBAL_CONSTEXPR20
					size_type waste_size() const KERBAL_NOEXCEPT
					{
						size_type tail_size = this->tail_size();
						return tail_size == 0 ? 0 : BITS_PER_BLOCK::value - tail_size;
					}

				public:

					KERBAL_CONSTEXPR
					const block_type * data() const KERBAL_NOEXCEPT
					{
						return this->k_block;
					}

					KERBAL_CONSTEXPR14
					block_type * mutable_data() KERBAL_NOEXCEPT
					{
						return this->k_block;
					}

				public:

					template <typename Func>
					KERBAL_CONSTEXPR14
					void for_each(Func f) const
					{
						for (size_type i = 0; i < this->size(); ++i) {
							f(i, this->test(i));
						}
					}

					template <typename Func>
					KERBAL_CONSTEXPR14
					void for_each(size_type left, size_type len, Func f) const
					{
						size_type right = kerbal::compare::min(this->size(), left + len);
						for (size_type i = left; i < right; ++i) {
							f(i, this->test(i));
						}
					}

				private:

					template <bool c>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<!c, bool>::type
					k_all_impl() const KERBAL_NOEXCEPT
					{
						return
							bitset_size_unrelated::all_chunk(k_block, block_size() - 1) &&
							(
								static_cast<block_type>(
									static_cast<block_type>(~k_block[block_size() - 1]) <<
										this->waste_size()
								) == 0
							);
					}

					template <bool c>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<c, bool>::type
					k_all_impl() const KERBAL_NOEXCEPT
					{
						return bitset_size_unrelated::all_chunk(k_block, block_size());
					}

				public:

					// Checks if all bits are set to true
					KERBAL_CONSTEXPR14
					bool all() const KERBAL_NOEXCEPT
					{
						if (this->block_size() % BITS_PER_BLOCK::value == 0) {
							return this->k_all_impl<true>();
						} else {
							return this->k_all_impl<false>();
						}
					}

					KERBAL_CONSTEXPR20
					bool test(size_type pos) const KERBAL_NOEXCEPT
					{
						return kerbal::numeric::get_bit(
							this->k_block[pos / BITS_PER_BLOCK::value],
							pos % BITS_PER_BLOCK::value
						);
					}

					KERBAL_CONSTEXPR20
					void reset(size_type pos) KERBAL_NOEXCEPT
					{
						block_size_type idx = pos / BITS_PER_BLOCK::value;
						block_size_type ofs = pos % BITS_PER_BLOCK::value;
						k_block[idx] = kerbal::numeric::reset_bit(k_block[idx], ofs);
					}

					KERBAL_CONSTEXPR20
					void set(size_type pos) KERBAL_NOEXCEPT
					{
						block_size_type idx = pos / BITS_PER_BLOCK::value;
						block_size_type ofs = pos % BITS_PER_BLOCK::value;
						k_block[idx] = kerbal::numeric::set_bit(k_block[idx], ofs);
					}

			};

		} // namespace detail

		template <typename Block, typename Allocator>
		class bitset :
			private kerbal::container::detail::container_allocator_overload<Allocator>,
			public kerbal::bitset::detail::bitset_block_only<Block>
		{
			private:
				typedef kerbal::container::detail::container_allocator_overload<Allocator> container_allocator_overload;
				typedef kerbal::bitset::detail::bitset_block_only<Block> bitset_block_only;

			public:
				typedef typename container_allocator_overload::allocator_type	allocator_type;
				typedef typename bitset_block_only::size_type					size_type;
				typedef typename bitset_block_only::block_size_type				block_size_type;

			private:
				using container_allocator_overload::alloc;

			public:

#		if __cplusplus >= 201103L

				bitset() = default;

#		else

				bitset()
				{
				}

#		endif

				KERBAL_CONSTEXPR20
				explicit bitset(const allocator_type & alloc) :
					container_allocator_overload(alloc)
				{
				}

				KERBAL_CONSTEXPR20
				explicit bitset(size_type size) :
					bitset_block_only(this->alloc(), size, false)
				{
				}

				KERBAL_CONSTEXPR20
				explicit bitset(size_type size, const allocator_type & alloc) :
					container_allocator_overload(alloc),
					bitset_block_only(this->alloc(), size, false)
				{
				}

				KERBAL_CONSTEXPR20
				bitset(const bitset & src) :
					bitset_block_only(this->alloc(), static_cast<const bitset_block_only &>(src))
				{
				}

				KERBAL_CONSTEXPR20
				bitset(const bitset & src, const allocator_type & alloc) :
					container_allocator_overload(alloc),
					bitset_block_only(this->alloc(), static_cast<const bitset_block_only &>(src))
				{
				}

				KERBAL_CONSTEXPR20
				~bitset()
				{
					this->bitset_block_only::destroy_using_allocator(this->alloc());
				}


				using bitset_block_only::size;
				using bitset_block_only::block_size;

				using bitset_block_only::all;

				using bitset_block_only::test;
				using bitset_block_only::set;
				using bitset_block_only::reset;

		};

	} // namespace bitset

} // namespace kerbal

#endif // KERBAL_BITSET_BITSET_HPP
