/**
 * @file       static_bitset.hpp
 * @brief
 * @date       2020-08-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_STATIC_BITSET_HPP
#define KERBAL_BITSET_STATIC_BITSET_HPP

#include <kerbal/bitset/static_bitset/static_bitset.fwd.hpp>

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/algorithm/modifier/copy_backward.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compare/minmax.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/array.hpp>
#include <kerbal/numeric/bit.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <cstddef>

#include <kerbal/bitset/detail/bitset_size_unrelated.hpp>
#include <kerbal/bitset/detail/default_block_type.hpp>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			template <std::size_t NLong, std::size_t NShort, typename Block>
			KERBAL_CONSTEXPR14
			static_bitset<NLong, Block>
			k_blend_impl1(
				const static_bitset<NLong, Block> & bs1,
				const static_bitset<NShort, Block> & bs2,
				const static_bitset<NShort, Block> & mask
			) KERBAL_NOEXCEPT;

			template <std::size_t NLong, std::size_t NShort, typename Block>
			KERBAL_CONSTEXPR14
			static_bitset<NLong, Block>
			k_blend_impl2(
				const static_bitset<NShort, Block> & bs1,
				const static_bitset<NLong, Block> & bs2,
				const static_bitset<NShort, Block> & mask
			) KERBAL_NOEXCEPT;

		} // namespace detail

		/*
		 *  [63 ... 0] [127 ... 64] [191 ... 128] [255 ... 192]
		 */
		template <std::size_t N, typename Block>
		class static_bitset :
			protected detail::bitset_size_unrelated<Block>
		{
				KERBAL_STATIC_ASSERT(
					kerbal::type_traits::is_unsigned<Block>::value,
					"Block must be unsigned type"
				);

			private:
				typedef detail::bitset_size_unrelated<Block> bitset_size_unrelated;

			public:
				typedef Block													block_type;
				typedef typename bitset_size_unrelated::BITS_PER_BLOCK			BITS_PER_BLOCK;

				typedef std::size_t												size_type;
				typedef kerbal::type_traits::integral_constant<size_type, N>	SIZE;

				typedef kerbal::type_traits::bool_constant<
					N % BITS_PER_BLOCK::value == 0
				>																IS_DIVISIBLE;

				typedef typename bitset_size_unrelated::block_size_type			block_size_type;
				typedef kerbal::type_traits::integral_constant<
					block_size_type,
					N / BITS_PER_BLOCK::value + (N % BITS_PER_BLOCK::value != 0)
				>																BLOCK_SIZE;

			private:
				block_type k_block[BLOCK_SIZE::value];

				typedef typename bitset_size_unrelated::ALL_ONE					ALL_ONE;
				typedef kerbal::type_traits::integral_constant<
					block_size_type,
					N % BITS_PER_BLOCK::value
				>																TAIL_SIZE;
				typedef kerbal::type_traits::integral_constant<
					block_size_type,
					TAIL_SIZE::value == 0 ? 0 : BITS_PER_BLOCK::value - TAIL_SIZE::value
				>																WASTE_SIZE;

			public:

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR
				static_bitset() KERBAL_NOEXCEPT :
					k_block{static_cast<block_type>(0)}
				{
				}

#		else

				static_bitset() KERBAL_NOEXCEPT
				{
					this->reset();
				}

#		endif

				KERBAL_CONSTEXPR
				size_type size() const KERBAL_NOEXCEPT
				{
					return SIZE::value;
				}

				KERBAL_CONSTEXPR
				block_size_type block_size() const KERBAL_NOEXCEPT
				{
					return BLOCK_SIZE::value;
				}

				KERBAL_CONSTEXPR
				bool test(size_type pos) const KERBAL_NOEXCEPT
				{
					return kerbal::numeric::get_bit(
						k_block[pos / BITS_PER_BLOCK::value],
						pos % BITS_PER_BLOCK::value
					);
				}

				KERBAL_CONSTEXPR14
				kerbal::container::array<bool, N>
				bitarray() const KERBAL_NOEXCEPT
				{
					kerbal::container::array<bool, N> r
#				if __cplusplus >= 201402L
						= {}
#				endif
					;

					for (size_type i = 0; i < N; ++i) {
						r[i] = test(i);
					}
					return r;
				}

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
					for (size_type i = 0; i < SIZE::value; ++i) {
						f(i, this->test(i));
					}
				}

				template <typename Func>
				KERBAL_CONSTEXPR14
				void for_each(size_type left, size_type len, Func f) const
				{
					size_type right = kerbal::compare::min(SIZE::value, left + len);
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
						bitset_size_unrelated::all_chunk(k_block, BLOCK_SIZE::value - 1) &&
						(
							static_cast<block_type>(
								static_cast<block_type>(~k_block[BLOCK_SIZE::value - 1])
									<< WASTE_SIZE::value
							) == 0
						);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				k_all_impl() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::all_chunk(k_block, BLOCK_SIZE::value);
				}

			public:

				// Checks if all bits are set to true
				KERBAL_CONSTEXPR14
				bool all() const KERBAL_NOEXCEPT
				{
					return k_all_impl<IS_DIVISIBLE::value>();
				}

				KERBAL_CONSTEXPR14
				bool all(size_type left, size_type len) const KERBAL_NOEXCEPT
				{
					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						if ((~k_block[idx_left] >> ofs_left) != 0) { // if any left t(BITS_PER_BLOCK::value - ofs_left) bits of k_block[idx_left] is false
							return false;
						}
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						if (!bitset_size_unrelated::all_chunk(k_block + chunk_left, chunk_size)) {
							return false;
						}
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							const block_type & remain_block = k_block[chunk_left + chunk_size];
							if ((~remain_block << (BITS_PER_BLOCK::value - remain)) != 0) { // if any right remain bits of remain_block is false
								return false;
							}
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left);
							// 0000 111 00000000
							//      len ofs_left
							if ((~k_block[idx_left] & mask) != 0) {
								return false;
							}
						}
					}

					return true;
				}


			private:

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<!c, bool>::type
				k_any_impl() const KERBAL_NOEXCEPT
				{
					return
						bitset_size_unrelated::any_chunk(k_block, BLOCK_SIZE::value - 1) ||
						(static_cast<block_type>(k_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value) != 0);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				k_any_impl() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::any_chunk(k_block, BLOCK_SIZE::value);
				}

			public:

				// Checks if any bits are set to true
				KERBAL_CONSTEXPR14
				bool any() const KERBAL_NOEXCEPT
				{
					return k_any_impl<IS_DIVISIBLE::value>();
				}

				KERBAL_CONSTEXPR14
				bool any(size_type left, size_type len) const KERBAL_NOEXCEPT
				{
					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						if ((k_block[idx_left] >> ofs_left) != 0) { // if any left t(BITS_PER_BLOCK::value - ofs_left) bits of k_block[idx_left] is true
							return true;
						}
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						if (bitset_size_unrelated::any_chunk(k_block + chunk_left, chunk_size)) {
							return true;
						}
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							const block_type & remain_block = k_block[chunk_left + chunk_size];
							if ((remain_block << (BITS_PER_BLOCK::value - remain)) != 0) { // if any right remain bits of remain_block is true
								return true;
							}
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left);
							// 0000 111 00000000
							//      len ofs_left
							if ((k_block[idx_left] & mask) != 0) {
								return true;
							}
						}
					}

					return false;
				}

				// Checks if none of the bits are set to true
				KERBAL_CONSTEXPR14
				bool none() const KERBAL_NOEXCEPT
				{
					return !this->any();
				}

				KERBAL_CONSTEXPR14
				bool none(size_type left, size_type len) const KERBAL_NOEXCEPT
				{
					return !this->any(left, len);
				}

			private:

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<!c, size_type>::type
				k_count_impl() const KERBAL_NOEXCEPT
				{
					return
						bitset_size_unrelated::count_chunk(k_block, BLOCK_SIZE::value - 1) +
						kerbal::numeric::popcount(
							static_cast<block_type>(k_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value)
						);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, size_type>::type
				k_count_impl() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::count_chunk(k_block, BLOCK_SIZE::value);
				}

			public:

				KERBAL_CONSTEXPR14
				size_type count() const KERBAL_NOEXCEPT
				{
					return k_count_impl<IS_DIVISIBLE::value>();
				}

				KERBAL_CONSTEXPR14
				size_type count(size_type left, size_type len) const KERBAL_NOEXCEPT
				{
					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					size_type cnt = 0;
					if (len > t) {
						cnt += kerbal::numeric::popcount(k_block[idx_left] >> ofs_left);
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						cnt += bitset_size_unrelated::count_chunk(k_block + chunk_left, chunk_size);
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							const block_type & remain_block = k_block[chunk_left + chunk_size];
							cnt += kerbal::numeric::popcount(remain_block << (BITS_PER_BLOCK::value - remain));
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left);
							// 0000 111 00000000
							//      len ofs_left
							cnt += kerbal::numeric::popcount(k_block[idx_left] & mask);
						}
					}

					return cnt;
				}

				KERBAL_CONSTEXPR14
				static_bitset & reset() KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::reset_chunk(k_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & reset(size_type pos) KERBAL_NOEXCEPT
				{
					block_size_type idx = pos / BITS_PER_BLOCK::value;
					block_size_type ofs = pos % BITS_PER_BLOCK::value;
					k_block[idx] = kerbal::numeric::reset_bit(k_block[idx], ofs);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & reset(size_type left, size_type len) KERBAL_NOEXCEPT
				{
					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						k_block[idx_left] = kerbal::numeric::reset_left_n(k_block[idx_left], t);
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						bitset_size_unrelated::reset_chunk(k_block + chunk_left, chunk_size);
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							block_type & remain_block = k_block[chunk_left + chunk_size];
							remain_block = kerbal::numeric::reset_right_n(remain_block, remain);
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(
								~static_cast<block_type>(
									kerbal::numeric::mask<block_type>(len) << ofs_left
								)
							);
							// 1111 000 11111111
							//      len ofs_left
							k_block[idx_left] &= mask;
						}
					}

					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & set() KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::set_chunk(k_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & set(size_type pos) KERBAL_NOEXCEPT
				{
					block_size_type idx = pos / BITS_PER_BLOCK::value;
					block_size_type ofs = pos % BITS_PER_BLOCK::value;
					k_block[idx] = kerbal::numeric::set_bit(k_block[idx], ofs);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & set(size_type left, size_type len, bool value) KERBAL_NOEXCEPT
				{
					if (value == false) {
						this->reset(left, len);
						return *this;
					}

					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						k_block[idx_left] = kerbal::numeric::set_left_n(k_block[idx_left], t);
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						bitset_size_unrelated::set_chunk(k_block + chunk_left, chunk_size);
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							block_type & remain_block = k_block[chunk_left + chunk_size];
							remain_block = kerbal::numeric::set_right_n(remain_block, remain);
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left);
							// 0000 111 00000000
							//      len ofs_left
							k_block[idx_left] |= mask;
						}
					}

					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & set(size_type pos, bool value) KERBAL_NOEXCEPT
				{
					if (value) {
						this->set(pos);
					} else {
						this->reset(pos);
					}
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & flip() KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::flip_chunk(k_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & flip(size_type pos) KERBAL_NOEXCEPT
				{
					block_size_type idx = pos / BITS_PER_BLOCK::value;
					block_size_type ofs = pos % BITS_PER_BLOCK::value;
					k_block[idx] = kerbal::numeric::flip(k_block[idx], ofs);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & flip(size_type left, size_type len) KERBAL_NOEXCEPT
				{
					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						k_block[idx_left] = kerbal::numeric::flip_left_n(k_block[idx_left], t);
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						bitset_size_unrelated::flip_chunk(k_block + chunk_left, chunk_size);
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							block_type & remain_block = k_block[chunk_left + chunk_size];
							remain_block = kerbal::numeric::flip_right_n(remain_block, remain);
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left);
							// 0000 111 00000000
							//      len ofs_left
							k_block[idx_left] ^= mask;
						}
					}

					return *this;
				}

			private:
				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<!c, bool>::type
				k_equals_impl(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return
						bitset_size_unrelated::equal_chunk(k_block, rhs.k_block, BLOCK_SIZE::value - 1) &&
						(
							static_cast<block_type>(k_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value) ==
							static_cast<block_type>(rhs.k_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value)
						);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				k_equals_impl(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::equal_chunk(k_block, rhs.k_block, BLOCK_SIZE::value);
				}

			public:
				KERBAL_CONSTEXPR14
				bool operator==(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return k_equals_impl<IS_DIVISIBLE::value>(rhs);
				}

				KERBAL_CONSTEXPR14
				bool operator!=(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return !(*this == rhs);
				}

				KERBAL_CONSTEXPR14
				static_bitset & operator&=(const static_bitset & ano) KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::bit_and_assign(this->k_block, ano.k_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & operator|=(const static_bitset & ano) KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::bit_or_assign(this->k_block, ano.k_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & operator^=(const static_bitset & ano) KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::bit_xor_assign(this->k_block, ano.k_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				friend
				static_bitset operator&(const static_bitset & lhs, const static_bitset & rhs) KERBAL_NOEXCEPT
				{
					static_bitset r(lhs);
					r &= rhs;
					return r;
				}

				KERBAL_CONSTEXPR14
				friend
				static_bitset operator|(const static_bitset & lhs, const static_bitset & rhs) KERBAL_NOEXCEPT
				{
					static_bitset r(lhs);
					r |= rhs;
					return r;
				}

				KERBAL_CONSTEXPR14
				friend
				static_bitset operator^(const static_bitset & lhs, const static_bitset & rhs) KERBAL_NOEXCEPT
				{
					static_bitset r(lhs);
					r ^= rhs;
					return r;
				}

				KERBAL_CONSTEXPR14
				static_bitset operator~() KERBAL_NOEXCEPT
				{
					static_bitset r;
					for (size_type i = 0; i < BLOCK_SIZE::value; ++i) {
						r.k_block[i] = ~this->k_block[i];
					}
					return r;
				}

				KERBAL_CONSTEXPR14
				static_bitset & operator<<=(size_type n) KERBAL_NOEXCEPT
				{
					if (n >= SIZE::value) {
						this->reset();
					} else {
						if (!IS_DIVISIBLE::value) {
							this->k_block[BLOCK_SIZE::value - 1] =
								kerbal::numeric::reset_left_n(
									this->k_block[BLOCK_SIZE::value - 1],
									WASTE_SIZE::value
								);
						}
						const size_type inner_ofs = n % BITS_PER_BLOCK::value;
						const block_size_type shift_block_cnt = n / BITS_PER_BLOCK::value;
						if (inner_ofs == 0) {
							kerbal::algorithm::copy(this->k_block + shift_block_cnt, this->k_block + BLOCK_SIZE::value, this->k_block);
						} else {
							const size_type ano_ofs = (BITS_PER_BLOCK::value - inner_ofs);
							size_type i = 0;
							size_type j = shift_block_cnt;
							while (j + 1 != BLOCK_SIZE::value) {
								this->k_block[i] = (this->k_block[j] >> inner_ofs) | (this->k_block[j + 1] << ano_ofs);
								++i;
								++j;
							}
							this->k_block[i] = (this->k_block[j] >> inner_ofs);
						}
						bitset_size_unrelated::reset_chunk(this->k_block + (BLOCK_SIZE::value - shift_block_cnt), shift_block_cnt);
					}
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset & operator>>=(size_type n) KERBAL_NOEXCEPT
				{
					if (n >= SIZE::value) {
						this->reset();
					} else {
						const size_type inner_ofs = n % BITS_PER_BLOCK::value;
						const block_size_type shift_block_cnt = n / BITS_PER_BLOCK::value;
						if (inner_ofs == 0) {
							kerbal::algorithm::copy_backward(
								this->k_block,
								this->k_block + (BLOCK_SIZE::value - shift_block_cnt),
								this->k_block + BLOCK_SIZE::value
							);
						} else {
							const size_type ano_ofs = (BITS_PER_BLOCK::value - inner_ofs);
							size_type i = BLOCK_SIZE::value;
							size_type j = i - shift_block_cnt;
							while (j - 1 != 0) {
								--i;
								--j;
								this->k_block[i] = (this->k_block[j] << inner_ofs) | (this->k_block[j - 1] >> ano_ofs);
							}
							this->k_block[shift_block_cnt] = (this->k_block[0] << inner_ofs);
						}
						bitset_size_unrelated::reset_chunk(this->k_block + 0, shift_block_cnt); // this->reset(0, n);
					}
					return *this;
				}

			private:

				template <size_type Len>
				KERBAL_CONSTEXPR14
				static_bitset<Len, Block>
				k_subset_impl(size_type left) const KERBAL_NOEXCEPT
				{
					static_bitset<Len, Block> r;
					typedef typename static_bitset<Len, Block>::BLOCK_SIZE RESULT_BLOC_SIZE;
					const block_size_type shift_block_cnt = left / BITS_PER_BLOCK::value;
					const block_size_type inner_ofs = left % BITS_PER_BLOCK::value;
					if (inner_ofs == 0) {
						kerbal::algorithm::copy(
							this->k_block + shift_block_cnt,
							this->k_block + shift_block_cnt + RESULT_BLOC_SIZE::value,
							r.mutable_data()
						);
					} else {
						const block_size_type ano_ofs = BITS_PER_BLOCK::value - inner_ofs;
						block_size_type i = 0;
						block_size_type j = shift_block_cnt;
						while (i + 1 != RESULT_BLOC_SIZE::value) {
							r.mutable_data()[i] = (this->k_block[j] >> inner_ofs) | (this->k_block[j + 1] << ano_ofs);
							++i;
							++j;
						}
						r.mutable_data()[i] = (this->k_block[j] >> inner_ofs);
					}
					return r;
				}

			public:

				template <size_type Left, size_type Len>
				KERBAL_CONSTEXPR14
				static_bitset<Len, Block>
				subset() const KERBAL_NOEXCEPT
				{
					KERBAL_STATIC_ASSERT(Left < SIZE::value, "Left should < SIZE::value");
					KERBAL_STATIC_ASSERT(Len > 0, "Len should > 0");
					KERBAL_STATIC_ASSERT(Len <= SIZE::value - Left, "Left + Len should <= SIZE::value");
					return this->k_subset_impl<Len>(Left);
				}

				KERBAL_CONSTEXPR14
				void swap(static_bitset & ano) KERBAL_NOEXCEPT
				{
					kerbal::algorithm::swap(this->k_block, ano.k_block);
				}

				template <std::size_t NLong, std::size_t NShort, typename Block2>
				friend
				KERBAL_CONSTEXPR14
				static_bitset<NLong, Block2>
				kerbal::bitset::detail::k_blend_impl1(
					const static_bitset<NLong, Block2> & bs1,
					const static_bitset<NShort, Block2> & bs2,
					const static_bitset<NShort, Block2> & mask
				) KERBAL_NOEXCEPT;

				template <std::size_t NLong, std::size_t NShort, typename Block2>
				friend
				KERBAL_CONSTEXPR14
				static_bitset<NLong, Block2>
				kerbal::bitset::detail::k_blend_impl2(
					const static_bitset<NShort, Block2> & bs1,
					const static_bitset<NLong, Block2> & bs2,
					const static_bitset<NShort, Block2> & mask
				) KERBAL_NOEXCEPT;

		};

		namespace detail
		{

			template <std::size_t N1, std::size_t N2>
			struct static_bitset_blend_min_len :
				kerbal::type_traits::integral_constant<std::size_t, N1 < N2 ? N1 : N2>
			{};

			template <std::size_t N1, std::size_t N2>
			struct static_bitset_blend_max_len :
				kerbal::type_traits::integral_constant<std::size_t, N1 >= N2 ? N1 : N2>
			{};

			// http://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
			template <std::size_t NLong, std::size_t NShort, typename Block>
			KERBAL_CONSTEXPR14
			static_bitset<NLong, Block>
			k_blend_impl1(
				const static_bitset<NLong, Block> & bs1,
				const static_bitset<NShort, Block> & bs2,
				const static_bitset<NShort, Block> & mask
			) KERBAL_NOEXCEPT
			{
				typedef static_bitset<NLong, Block>				LongBs;
				typedef static_bitset<NShort, Block>			ShortBs;
				typedef typename LongBs::block_size_type		block_size_type;
				typedef typename LongBs::block_type				block_type;

				KERBAL_STATIC_ASSERT(NLong >= NShort, "bs1.size() should >= bs2.size()");

				LongBs r;
				block_size_type long_block_size = LongBs::BLOCK_SIZE::value;
				block_size_type short_block_size = ShortBs::BLOCK_SIZE::value;
				for (block_size_type i = 0; i < short_block_size; ++i) {
//					r.k_block[i] =
//						(bs1.k_block[i] & bs2.k_block[i]) |
//						(bs1.k_block[i] & ~mask.k_block[i]) |
//						(bs2.k_block[i] & mask.k_block[i]);
					r.k_block[i] = ((bs1.k_block[i] ^ bs2.k_block[i]) & mask.k_block[i]) ^ bs1.k_block[i];
				}
				if (!ShortBs::IS_DIVISIBLE::value) {
					const block_type BMASK = kerbal::numeric::mask<block_type>(ShortBs::TAIL_SIZE::value);
					r.k_block[short_block_size - 1] =
						(r.k_block[short_block_size - 1] & BMASK) |
						(bs1.k_block[short_block_size - 1] & ~BMASK);
				}
				kerbal::algorithm::copy(
					bs1.k_block + short_block_size,
					bs1.k_block + long_block_size,
					r.k_block + short_block_size
				);
				return r;
			}

			template <std::size_t NLong, std::size_t NShort, typename Block>
			KERBAL_CONSTEXPR14
			static_bitset<NLong, Block>
			k_blend_impl2(
				const static_bitset<NShort, Block> & bs1,
				const static_bitset<NLong, Block> & bs2,
				const static_bitset<NShort, Block> & mask
			) KERBAL_NOEXCEPT
			{
				typedef static_bitset<NLong, Block>				LongBs;
				typedef static_bitset<NShort, Block>			ShortBs;
				typedef typename LongBs::block_size_type		block_size_type;
				typedef typename LongBs::block_type				block_type;

				KERBAL_STATIC_ASSERT(NLong >= NShort, "bs2.size() should >= bs1.size()");

				LongBs r;
				block_size_type long_block_size = LongBs::BLOCK_SIZE::value;
				block_size_type short_block_size = ShortBs::BLOCK_SIZE::value;
				for (block_size_type i = 0; i < short_block_size; ++i) {
//					r.k_block[i] =
//						(bs1.k_block[i] & bs2.k_block[i]) |
//						(bs1.k_block[i] & ~mask.k_block[i]) |
//						(bs2.k_block[i] & mask.k_block[i]);
					r.k_block[i] = ((bs1.k_block[i] ^ bs2.k_block[i]) & mask.k_block[i]) ^ bs1.k_block[i];
				}
				if (!ShortBs::IS_DIVISIBLE::value) {
					const block_type BMASK = kerbal::numeric::mask<block_type>(ShortBs::TAIL_SIZE::value);
					r.k_block[short_block_size - 1] =
						(r.k_block[short_block_size - 1] & BMASK) |
						(bs2.k_block[short_block_size - 1] & ~BMASK);
				}
				kerbal::algorithm::copy(
					bs2.k_block + short_block_size,
					bs2.k_block + long_block_size,
					r.k_block + short_block_size
				);
				return r;
			}

			template <std::size_t N1, std::size_t N2, typename Block>
			KERBAL_CONSTEXPR14
			typename kerbal::type_traits::enable_if<
				N1 >= N2,
				static_bitset<detail::static_bitset_blend_max_len<N1, N2>::value, Block>
			>::type
			k_blend_dispatch(
				const static_bitset<N1, Block> & bs1,
				const static_bitset<N2, Block> & bs2,
				const static_bitset<detail::static_bitset_blend_min_len<N1, N2>::value, Block> & mask
			) KERBAL_NOEXCEPT
			{
				return kerbal::bitset::detail::k_blend_impl1(bs1, bs2, mask);
			}

			template <std::size_t N1, std::size_t N2, typename Block>
			KERBAL_CONSTEXPR14
			typename kerbal::type_traits::enable_if<
				N1 < N2,
				static_bitset<detail::static_bitset_blend_max_len<N1, N2>::value, Block>
			>::type
			k_blend_dispatch(
				const static_bitset<N1, Block> & bs1,
				const static_bitset<N2, Block> & bs2,
				const static_bitset<detail::static_bitset_blend_min_len<N1, N2>::value, Block> & mask
			) KERBAL_NOEXCEPT
			{
				return kerbal::bitset::detail::k_blend_impl2(bs1, bs2, mask);
			}

		} // namespace detail

		/**
		 * select the bits in bs1 or bs2 according to the mask.
		 * @param mask
		 *         requires mask.size() == min(bs1.size(), bs2.size())
		 * @return r
		 *         promise r.size() == max(bs1.size(), bs2.size())
		 * @details
		 *     \f[
		 *         r[i] = \begin{cases}
		 *             bs1[i]& \text{, if } mask[i] == false \\
		 *             bs2[i]& \text{, if } mask[i] == true \\
		 *             longer(bs1, bs2)[i]& \text{, if } i >= min(bs1.size(), bs2.size())
		 *         \end{cases}
		 *     \f]
		 */
		template <std::size_t N1, std::size_t N2, std::size_t NMask, typename Block>
		KERBAL_CONSTEXPR14
		static_bitset<detail::static_bitset_blend_max_len<N1, N2>::value, Block>
		blend(
			const static_bitset<N1, Block> & bs1,
			const static_bitset<N2, Block> & bs2,
			const static_bitset<NMask, Block> & mask
		) KERBAL_NOEXCEPT
		{
			/*
			 *         ┌ bs1[i]               , if mask[i] == false
			 *  r[i] = │ bs2[i]               , if mask[i] == true
			 *         └ longer(bs1, bs2)[i]  , if i >= min(bs1.size(), bs2.size())
			 */
			KERBAL_STATIC_ASSERT(
				(NMask == detail::static_bitset_blend_min_len<N1, N2>::value),
				"mask.size() should == min(bs1.size(), bs2.size())"
			);
			return kerbal::bitset::detail::k_blend_dispatch(bs1, bs2, mask);
		}

	} // namespace bitset


	namespace algorithm
	{

		template <std::size_t N, typename Block>
		KERBAL_CONSTEXPR14
		void swap(
			kerbal::bitset::static_bitset<N, Block> & a,
			kerbal::bitset::static_bitset<N, Block> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <std::size_t N, typename Block>
	KERBAL_CONSTEXPR14
	void swap(
		kerbal::bitset::static_bitset<N, Block> & a,
		kerbal::bitset::static_bitset<N, Block> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_BITSET_STATIC_BITSET_HPP
