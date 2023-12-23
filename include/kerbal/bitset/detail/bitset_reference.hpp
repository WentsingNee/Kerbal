/**
 * @file       bitset_reference.hpp
 * @brief
 * @date       2020-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_BITSET_REFERENCE_HPP
#define KERBAL_BITSET_DETAIL_BITSET_REFERENCE_HPP

#include <kerbal/bitset/static_bitset/static_bitset.fwd.hpp>

#include <kerbal/numeric/bit.hpp>

#include <cstddef>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			template <typename Block>
			class bitset_reference
			{
					template <std::size_t N, typename Block2>
					friend class kerbal::bitset::static_bitset;

				private:
					typedef Block													block_type;
					typedef std::size_t												size_type;

				private:
					block_type * _K_p;
					size_type _K_offset;

				private:
					KERBAL_CONSTEXPR
					bitset_reference(block_type * p, size_type offset) KERBAL_NOEXCEPT
							: _K_p(p), _K_offset(offset)
					{
					}

				public:

					KERBAL_CONSTEXPR
					bool test() const KERBAL_NOEXCEPT
					{
						return kerbal::numeric::get_bit(*_K_p, _K_offset);
					}

					KERBAL_CONSTEXPR14
					void reset() const KERBAL_NOEXCEPT
					{
						*_K_p = kerbal::numeric::reset_bit(*_K_p, _K_offset);
					}

					KERBAL_CONSTEXPR14
					void set() const KERBAL_NOEXCEPT
					{
						*_K_p = kerbal::numeric::set_bit(*_K_p, _K_offset);
					}

					KERBAL_CONSTEXPR14
					void set(bool b) const KERBAL_NOEXCEPT
					{
						*_K_p = b ?
								kerbal::numeric::set_bit(*_K_p, _K_offset) :
								kerbal::numeric::reset_bit(*_K_p, _K_offset);
					}

					KERBAL_CONSTEXPR
					operator bool() const KERBAL_NOEXCEPT
					{
						return this->test();
					}

					KERBAL_CONSTEXPR
					const bitset_reference & operator=(bool b) const KERBAL_NOEXCEPT
					{
						return this->set(b);
					}

			};

		} //namespace detail

	} //namespace bitset

} //namespace kerbal

#endif // KERBAL_BITSET_DETAIL_BITSET_REFERENCE_HPP
