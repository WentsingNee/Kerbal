/**
 * @file       bitarray.mmx.hpp
 * @brief
 * @date       2022-11-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_MMX_HPP
#define KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_MMX_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>

#include <kerbal/numeric/bit/bitarray/bitarray.plain.hpp>

#include <mmintrin.h>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace mmx
			{

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint8_t>::type
				bitarray(kerbal::compatibility::uint8_t x)
				{
					typedef kerbal::compatibility::uint8_t T;

					unsigned long long u = x * 0x0101010101010101ull;
					u &= 0x0102040810204080ull;
					__m64 mm_x = _mm_cvtsi64_m64(u); // MMX
					mm_x = _mm_cmpeq_pi8(mm_x, _mm_set1_pi8(0)); // MMX
					mm_x = _mm_andnot_si64(mm_x, _mm_set1_pi8(1)); // MMX

					typename kerbal::numeric::bitarray_result<T>::type r;
					reinterpret_cast<__m64&>(r) = mm_x; // MMX
					return r;
				}

			} // namespace mmx

		} // namespace detail

	} // namespace numeric

} // namespace kerbal


#endif // KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_MMX_HPP
