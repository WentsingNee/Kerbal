
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

#include <kerbal/numeric/bit.hpp>

#include <cstddef>

namespace kerbal
{

	namespace bitset
	{

		template <size_t N, typename Block>
		class static_bitset;

		namespace bitset
		{

			template <typename Block>
			class bitset_reference
			{
					template <size_t N, typename Block2>
					friend class static_bitset;

				private:
					Block * M_p;
					size_t M_offset;

				private:
					KERBAL_CONSTEXPR
					bitset_reference(Block * p, size_t offset) KERBAL_NOEXCEPT
							: M_p(p), M_offset(offset)
					{
					}

				public:
					KERBAL_CONSTEXPR
					bool test() const KERBAL_NOEXCEPT
					{
						return kerbal::numeric::get_bit(*M_p, M_offset);
					}

					KERBAL_CONSTEXPR
					operator bool() const KERBAL_NOEXCEPT
					{
						return this->test();
					}

					KERBAL_CONSTEXPR14
					void set() const KERBAL_NOEXCEPT
					{
						*M_p = kerbal::numeric::set_bit(*M_p, M_offset);
					}

					KERBAL_CONSTEXPR14
					void reset() const KERBAL_NOEXCEPT
					{
						*M_p = kerbal::numeric::reset_bit(*M_p, M_offset);
					}

			};

		} //namespace bitset

	} //namespace bitset

} //namespace kerbal

#endif // KERBAL_BITSET_DETAIL_BITSET_REFERENCE_HPP
