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

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/smath/max_sa_sb.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>

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
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					kerbal::type_traits::aligned_storage<
						sizeof(bitarray_result_t),
						kerbal::smath::max_sa_sb<
							std::size_t,
							KERBAL_ALIGNOF(bitarray_result_t),
							KERBAL_ALIGNOF(uint64_t)
						>::value
					>::type as;

					__m64 const mm_ALL_ZERO = _mm_set1_pi8(0); // MMX
					__m64 const mm_ALL_ONE = _mm_set1_pi8(1); // MMX
					__m64 const mm_andmask = _mm_set_pi8(
						1u << 0, 1u << 1, 1u << 2, 1u << 3,
						1u << 4, 1u << 5, 1u << 6, 1u << 7
					); // MMX

					__m64 mm_x = _mm_set1_pi8(x); // MMX
					mm_x = _mm_and_si64(mm_x, mm_andmask); // MMX
					mm_x = _mm_cmpeq_pi8(mm_x, mm_ALL_ZERO); // MMX
					mm_x = _mm_andnot_si64(mm_x, mm_ALL_ONE); // MMX
					reinterpret_cast<__m64 &>(as) = mm_x; // MMX
					return reinterpret_cast<const bitarray_result_t &>(as);
				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint16_t>::type
				bitarray(kerbal::compatibility::uint16_t x)
				{
					typedef kerbal::compatibility::uint16_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					kerbal::type_traits::aligned_storage<
						sizeof(bitarray_result_t),
						kerbal::smath::max_sa_sb<
							std::size_t,
							KERBAL_ALIGNOF(bitarray_result_t),
							KERBAL_ALIGNOF(uint64_t)
						>::value
					>::type as;

					__m64 const mm_ALL_ZERO = _mm_set1_pi8(0);
					__m64 const mm_ALL_ONE = _mm_set1_pi8(1);
					__m64 const mm_andmask = _mm_set_pi8(
							1u << 0, 1u << 1, 1u << 2, 1u << 3,
							1u << 4, 1u << 5, 1u << 6, 1u << 7
					); // MMX

					__m64 mm_x;

					mm_x = _mm_set1_pi8(x & 0xFF); // MMX
					mm_x = _mm_and_si64(mm_x, mm_andmask); // MMX
					mm_x = _mm_cmpeq_pi8(mm_x, mm_ALL_ZERO); // MMX
					mm_x = _mm_andnot_si64(mm_x, mm_ALL_ONE); // MMX
					reinterpret_cast<__m64 *>(&as)[1] = mm_x; // MMX

					mm_x = _mm_set1_pi8(x >> 8); // MMX
					mm_x = _mm_and_si64(mm_x, mm_andmask); // MMX
					mm_x = _mm_cmpeq_pi8(mm_x, mm_ALL_ZERO); // MMX
					mm_x = _mm_andnot_si64(mm_x, mm_ALL_ONE); // MMX
					reinterpret_cast<__m64 *>(&as)[0] = mm_x; // MMX

					return reinterpret_cast<const bitarray_result_t &>(as);
				}

			} // namespace mmx

		} // namespace detail

	} // namespace numeric

} // namespace kerbal


#endif // KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_MMX_HPP
