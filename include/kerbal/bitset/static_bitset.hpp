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

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/querier.hpp>
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

				typedef typename bitset_size_unrelated::block_width_type		block_width_type;
				typedef kerbal::type_traits::integral_constant<
						block_width_type,
						N / BITS_PER_BLOCK::value + (N % BITS_PER_BLOCK::value != 0)
				>																BLOCK_SIZE;

			private:
				block_type m_block[BLOCK_SIZE::value];

				typedef typename bitset_size_unrelated::ALL_ONE					ALL_ONE;
				typedef kerbal::type_traits::integral_constant<
						block_width_type,
						N % BITS_PER_BLOCK::value
				>																TAIL_SIZE;
				typedef kerbal::type_traits::integral_constant<
						block_width_type,
						BITS_PER_BLOCK::value - TAIL_SIZE::value
				>																WASTE_SIZE;

			public:

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR
				static_bitset() KERBAL_NOEXCEPT
						: m_block{static_cast<block_type>(0)}
				{
				}

#		else

				static_bitset() KERBAL_NOEXCEPT
				{
					kerbal::algorithm::fill(m_block, m_block + BLOCK_SIZE::value, static_cast<block_type>(0));
				}

#		endif

				KERBAL_CONSTEXPR
				size_type size() const KERBAL_NOEXCEPT
				{
					return SIZE::value;
				}

				KERBAL_CONSTEXPR
				block_width_type block_size() const KERBAL_NOEXCEPT
				{
					return BLOCK_SIZE::value;
				}

				KERBAL_CONSTEXPR
				bool test(size_type pos) const KERBAL_NOEXCEPT
				{
					return kerbal::numeric::get_bit(m_block[pos / BITS_PER_BLOCK::value],
													pos % BITS_PER_BLOCK::value);
				}

				KERBAL_CONSTEXPR14
				kerbal::container::array<bool, N>
				bitarray() const KERBAL_NOEXCEPT
				{
					kerbal::container::array<bool, N> r;
					for (size_type i = 0; i < N; ++i) {
						r[i] = test(i);
					}
					return r;
				}

			private:

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<!c, bool>::type
				all_helper() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::all_trunk(m_block, BLOCK_SIZE::value - 1) &&
							(static_cast<block_type>((~m_block[BLOCK_SIZE::value - 1]) <<
									(BITS_PER_BLOCK::value - N % BITS_PER_BLOCK::value)) == 0);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				all_helper() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::all_trunk(m_block, BLOCK_SIZE::value);
				}

			public:

				// Checks if all bits are set to true
				KERBAL_CONSTEXPR14
				bool all() const KERBAL_NOEXCEPT
				{
					return all_helper<IS_DIVISIBLE::value>();
				}

				KERBAL_CONSTEXPR14
				bool all(size_type l, size_type r) const KERBAL_NOEXCEPT;

			private:

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<!c, bool>::type
				any_helper() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::any_trunk(m_block, BLOCK_SIZE::value - 1) ||
							(static_cast<block_type>(m_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value) != 0);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				any_helper() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::any_trunk(m_block, BLOCK_SIZE::value);
				}

			public:

				// Checks if any bits are set to true
				KERBAL_CONSTEXPR14
				bool any() const KERBAL_NOEXCEPT
				{
					return any_helper<IS_DIVISIBLE::value>();
				}

				KERBAL_CONSTEXPR14
				bool any(size_type l, size_type r) const KERBAL_NOEXCEPT;

			private:

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<!c, bool>::type
				none_helper() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::none_trunk(m_block, BLOCK_SIZE::value - 1) &&
							(static_cast<block_type>(m_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value) == 0);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				none_helper() const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::none_trunk(m_block, BLOCK_SIZE::value);
				}

			public:

				// Checks if none of the bits are set to true
				KERBAL_CONSTEXPR14
				bool none() const KERBAL_NOEXCEPT
				{
					return none_helper<IS_DIVISIBLE::value>();
				}

				KERBAL_CONSTEXPR14
				bool none(size_type l, size_type r) const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				static_bitset& reset() KERBAL_NOEXCEPT
				{
					kerbal::algorithm::fill(m_block, m_block + BLOCK_SIZE::value, static_cast<block_type>(0));
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& reset(size_type pos) KERBAL_NOEXCEPT
				{
					size_t idx = pos / BITS_PER_BLOCK::value;
					size_t ofs = pos % BITS_PER_BLOCK::value;
					m_block[idx] = kerbal::numeric::set0(m_block[idx], ofs);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& set() KERBAL_NOEXCEPT
				{
					kerbal::algorithm::fill(m_block, m_block + BLOCK_SIZE::value, ALL_ONE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& set(size_type pos) KERBAL_NOEXCEPT
				{
					size_t idx = pos / BITS_PER_BLOCK::value;
					size_t ofs = pos % BITS_PER_BLOCK::value;
					m_block[idx] = kerbal::numeric::set1(m_block[idx], ofs);
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
					bitset_size_unrelated::flip(m_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& flip(size_type pos) KERBAL_NOEXCEPT
				{
					size_t idx = pos / BITS_PER_BLOCK::value;
					size_t ofs = pos % BITS_PER_BLOCK::value;
					m_block[idx] = kerbal::numeric::flip(m_block[idx], ofs);
					return *this;
				}

			private:
				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<!c, bool>::type
				equals_helper(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::equal_trunk(m_block, rhs.m_block, BLOCK_SIZE::value - 1) &&
							(
								static_cast<block_type>(m_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value) ==
								static_cast<block_type>(rhs.m_block[BLOCK_SIZE::value - 1] << WASTE_SIZE::value)
							);
				}

				template <bool c>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<c, bool>::type
				equals_helper(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return bitset_size_unrelated::equal_trunk(m_block, rhs.m_block, BLOCK_SIZE::value);
				}

			public:
				KERBAL_CONSTEXPR14
				bool operator==(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return equals_helper<IS_DIVISIBLE::value>(rhs);
				}

				KERBAL_CONSTEXPR14
				bool operator!=(const static_bitset & rhs) const KERBAL_NOEXCEPT
				{
					return !(*this == rhs);
				}

				KERBAL_CONSTEXPR14
				static_bitset& operator&=(const static_bitset & ano) KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::bit_and_assign(this->m_block, ano.m_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& operator|=(const static_bitset & ano) KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::bit_or_assign(this->m_block, ano.m_block, BLOCK_SIZE::value);
					return *this;
				}

				KERBAL_CONSTEXPR14
				static_bitset& operator^=(const static_bitset & ano) KERBAL_NOEXCEPT
				{
					bitset_size_unrelated::bit_xor_assign(this->m_block, ano.m_block, BLOCK_SIZE::value);
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
				void swap(static_bitset & ano) KERBAL_NOEXCEPT
				{
					kerbal::algorithm::swap(this->m_block, ano.m_block);
				}

		};

	}

} //namespace kerbal


#endif // KERBAL_BITSET_STATIC_BITSET_HPP
