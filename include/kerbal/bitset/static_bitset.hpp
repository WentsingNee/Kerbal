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

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
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

		/*
		 *  [63 ... 0] [127 ... 64] [191 ... 128] [255 ... 192]
		 */
		template <size_t N, typename Block = KERBAL_BITSET_DEFAULT_BLOCK_TYPE>
		class static_bitset: protected detail::bitset_size_unrelated<Block>
		{
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Block>::value, "Block must be unsigned type");

			private:
				typedef detail::bitset_size_unrelated<Block> bitset_size_unrelated;

			public:
				typedef Block													block_type;
				typedef typename bitset_size_unrelated::BITS_PER_BLOCK			BITS_PER_BLOCK;

				typedef size_t													size_type;
				typedef kerbal::type_traits::integral_constant<size_type, N>	SIZE;

				typedef kerbal::type_traits::bool_constant<
						N % BITS_PER_BLOCK::value == 0
				>																IS_DIVISIBLE;

				typedef typename bitset_size_unrelated::block_size_type		block_size_type;
				typedef kerbal::type_traits::integral_constant<
						block_size_type,
						N / BITS_PER_BLOCK::value + (N % BITS_PER_BLOCK::value != 0)
				>																BLOCK_SIZE;

			private:
				block_type _K_block[BLOCK_SIZE::value];

				typedef typename bitset_size_unrelated::ALL_ONE					ALL_ONE;
				typedef kerbal::type_traits::integral_constant<
						block_size_type,
						N % BITS_PER_BLOCK::value
				>																TAIL_SIZE;
				typedef kerbal::type_traits::integral_constant<
						block_size_type,
						BITS_PER_BLOCK::value - TAIL_SIZE::value
				>																WASTE_SIZE;

			public:

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR
				static_bitset() KERBAL_NOEXCEPT
						: _K_block{static_cast<block_type>(0)}
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
					return kerbal::numeric::get_bit(_K_block[pos / BITS_PER_BLOCK::value],
													pos % BITS_PER_BLOCK::value);
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
					return this->_K_block;
				}

				KERBAL_CONSTEXPR14
				block_type * mutable_data() KERBAL_NOEXCEPT
				{
					return this->_K_block;
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
					size_type right = (SIZE::value - left < len) ? SIZE::value : (left + len);
					for (size_type i = left; i < right; ++i) {
						f(i, this->test(i));
					}
				}

			private:

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<!c, bool>::type
				_K_all_impl() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::all_chunk(_K_block, BLOCK_SIZE::value - 1) &&
							(static_cast<block_type>((~_K_block[BLOCK_SIZE::value - 1]) << WASTE_SIZE::value) == 0);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				_K_all_impl() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::all_chunk(_K_block, BLOCK_SIZE::value);
				}

			public:

				// Checks if all bits are set to true
				KERBAL_CONSTEXPR14
				bool all() const KERBAL_NOEXCEPT
				{
					return _K_all_impl<IS_DIVISIBLE::value>();
				}

				KERBAL_CONSTEXPR14
				bool all(size_type left, size_type len) const KERBAL_NOEXCEPT
				{
					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						if ((~_K_block[idx_left] >> ofs_left) != 0) { // if any left t(BITS_PER_BLOCK::value - ofs_left) bits of _K_block[idx_left] is false
							return false;
						}
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						if (!bitset_size_unrelated::all_chunk(_K_block + chunk_left, chunk_size)) {
							return false;
						}
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							const block_type & remain_block = _K_block[chunk_left + chunk_size];
							if ((~remain_block << (BITS_PER_BLOCK::value - remain)) != 0) { // if any right remain bits of remain_block is false
								return false;
							}
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left);
							// 0000 111 00000000
							//      len ofs_left
							if ((~_K_block[idx_left] & mask) != 0) {
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
				_K_any_impl() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::any_chunk(_K_block, BLOCK_SIZE::value - 1) ||
							(static_cast<block_type>(_K_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value) != 0);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				_K_any_impl() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::any_chunk(_K_block, BLOCK_SIZE::value);
				}

			public:

				// Checks if any bits are set to true
				KERBAL_CONSTEXPR14
				bool any() const KERBAL_NOEXCEPT
				{
					return _K_any_impl<IS_DIVISIBLE::value>();
				}

				KERBAL_CONSTEXPR14
				bool any(size_type left, size_type len) const KERBAL_NOEXCEPT
				{
					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						if ((_K_block[idx_left] >> ofs_left) != 0) { // if any left t(BITS_PER_BLOCK::value - ofs_left) bits of _K_block[idx_left] is true
							return true;
						}
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						if (bitset_size_unrelated::any_chunk(_K_block + chunk_left, chunk_size)) {
							return true;
						}
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							const block_type & remain_block = _K_block[chunk_left + chunk_size];
							if ((remain_block << (BITS_PER_BLOCK::value - remain)) != 0) { // if any right remain bits of remain_block is true
								return true;
							}
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left);
							// 0000 111 00000000
							//      len ofs_left
							if ((_K_block[idx_left] & mask) != 0) {
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
				_K_count_impl() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::count_chunk(_K_block, BLOCK_SIZE::value - 1) +
						   kerbal::numeric::popcount(static_cast<block_type>(_K_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value));
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, size_type>::type
				_K_count_impl() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::count_chunk(_K_block, BLOCK_SIZE::value);
				}

			public:

				KERBAL_CONSTEXPR14
				size_type count() const KERBAL_NOEXCEPT
				{
					return _K_count_impl<IS_DIVISIBLE::value>();
				}

				KERBAL_CONSTEXPR14
				static_bitset& reset() KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::reset_chunk(_K_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& reset(size_type pos) KERBAL_NOEXCEPT
				{
					block_size_type idx = pos / BITS_PER_BLOCK::value;
					block_size_type ofs = pos % BITS_PER_BLOCK::value;
					_K_block[idx] = kerbal::numeric::reset_bit(_K_block[idx], ofs);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& reset(size_type left, size_type len) KERBAL_NOEXCEPT
				{
					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						_K_block[idx_left] = kerbal::numeric::reset_left_n(_K_block[idx_left], t);
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						bitset_size_unrelated::reset_chunk(_K_block + chunk_left, chunk_size);
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							block_type & remain_block = _K_block[chunk_left + chunk_size];
							remain_block = kerbal::numeric::reset_right_n(remain_block, remain);
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(~static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left));
							// 1111 000 11111111
							//      len ofs_left
							_K_block[idx_left] &= mask;
						}
					}

					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& set() KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::set_chunk(_K_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& set(size_type pos) KERBAL_NOEXCEPT
				{
					block_size_type idx = pos / BITS_PER_BLOCK::value;
					block_size_type ofs = pos % BITS_PER_BLOCK::value;
					_K_block[idx] = kerbal::numeric::set_bit(_K_block[idx], ofs);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& set(size_type left, size_type len, bool value) KERBAL_NOEXCEPT
				{
					if (value == false) {
						this->reset(left, len);
						return *this;
					}

					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						_K_block[idx_left] = kerbal::numeric::set_left_n(_K_block[idx_left], t);
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						bitset_size_unrelated::set_chunk(_K_block + chunk_left, chunk_size);
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							block_type & remain_block = _K_block[chunk_left + chunk_size];
							remain_block = kerbal::numeric::set_right_n(remain_block, remain);
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left);
							// 0000 111 00000000
							//      len ofs_left
							_K_block[idx_left] |= mask;
						}
					}

					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& set(size_type pos, bool value) KERBAL_NOEXCEPT
				{
					if (value) {
						this->set(pos);
					} else {
						this->reset(pos);
					}
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& flip() KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::flip_chunk(_K_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& flip(size_type pos) KERBAL_NOEXCEPT
				{
					block_size_type idx = pos / BITS_PER_BLOCK::value;
					block_size_type ofs = pos % BITS_PER_BLOCK::value;
					_K_block[idx] = kerbal::numeric::flip(_K_block[idx], ofs);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& flip(size_type left, size_type len) KERBAL_NOEXCEPT
				{
					block_size_type idx_left = left / BITS_PER_BLOCK::value;
					block_size_type ofs_left = left % BITS_PER_BLOCK::value;
					size_type t = BITS_PER_BLOCK::value - ofs_left;
					if (len > t) {
						_K_block[idx_left] = kerbal::numeric::flip_left_n(_K_block[idx_left], t);
						len -= t;
						block_size_type chunk_left = idx_left + 1;
						size_type chunk_size = len / BITS_PER_BLOCK::value;
						bitset_size_unrelated::flip_chunk(_K_block + chunk_left, chunk_size);
						if ((chunk_left + chunk_size) < BLOCK_SIZE::value) {
							size_type remain = len % BITS_PER_BLOCK::value;
							block_type & remain_block = _K_block[chunk_left + chunk_size];
							remain_block = kerbal::numeric::flip_right_n(remain_block, remain);
						}
					} else {
						if (len != 0) {
							block_type mask = static_cast<block_type>(kerbal::numeric::mask<block_type>(len) << ofs_left);
							// 0000 111 00000000
							//      len ofs_left
							_K_block[idx_left] ^= mask;
						}
					}

					return *this;
				}

			private:
				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<!c, bool>::type
				_K_equals_impl(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::equal_chunk(_K_block, rhs._K_block, BLOCK_SIZE::value - 1) &&
							(
								static_cast<block_type>(_K_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value) ==
								static_cast<block_type>(rhs._K_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value)
							);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				_K_equals_impl(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::equal_chunk(_K_block, rhs._K_block, BLOCK_SIZE::value);
				}

			public:
				KERBAL_CONSTEXPR14
				bool operator==(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return _K_equals_impl<IS_DIVISIBLE::value>(rhs);
				}

				KERBAL_CONSTEXPR14
				bool operator!=(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return !(*this == rhs);
				}

				KERBAL_CONSTEXPR14
				static_bitset& operator&=(const static_bitset & ano) KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::bit_and_assign(this->_K_block, ano._K_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& operator|=(const static_bitset & ano) KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::bit_or_assign(this->_K_block, ano._K_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& operator^=(const static_bitset & ano) KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::bit_xor_assign(this->_K_block, ano._K_block, BLOCK_SIZE::value);
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
						r._K_block[i] = ~this->_K_block[i];
					}
					return r;
				}

				KERBAL_CONSTEXPR14
				static_bitset& operator<<=(size_type n) KERBAL_NOEXCEPT
				{
					if (n >= SIZE::value) {
						this->reset();
					} else {
						if (n % BITS_PER_BLOCK::value == 0) {
							block_size_type shift_block_cnt = n / BITS_PER_BLOCK::value;
							kerbal::algorithm::copy(this->_K_block + shift_block_cnt, this->_K_block + BLOCK_SIZE::value, this->_K_block);
						} else {
							for (size_type i = 0; i < SIZE::value - n; ++i) {
								this->set(i, this->test(i + n));
							}
						}
						this->reset(SIZE::value - n, n);
					}
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& operator>>=(size_type n) KERBAL_NOEXCEPT
				{
					if (n >= SIZE::value) {
						this->reset();
					} else {
						if (n % BITS_PER_BLOCK::value == 0) {
							block_size_type shift_block_cnt = n / BITS_PER_BLOCK::value;
							kerbal::algorithm::copy_backward(this->_K_block, this->_K_block + (BLOCK_SIZE::value - shift_block_cnt), this->_K_block + BLOCK_SIZE::value);
						} else {
							size_type i = SIZE::value - n;
							while (i != 0) {
								--i;
								this->set(i + n, this->test(i));
							}
						}
						this->reset(0, n);
					}
					return *this;
				}

				KERBAL_CONSTEXPR14
				void swap(static_bitset & ano) KERBAL_NOEXCEPT
				{
					kerbal::algorithm::swap(this->_K_block, ano._K_block);
				}

		};

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_STATIC_BITSET_HPP
