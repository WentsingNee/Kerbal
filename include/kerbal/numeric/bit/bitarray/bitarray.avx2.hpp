/**
 * @file       bitarray.avx2.hpp
 * @brief
 * @date       2022-11-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_AVX2_HPP
#define KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_AVX2_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/smath/max_sa_sb.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>

#include <kerbal/numeric/bit/bitarray/bitarray.plain.hpp>

#include <immintrin.h>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace avx2
			{

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint32_t>::type
				bitarray(kerbal::compatibility::uint32_t x)
				{
					typedef kerbal::compatibility::uint32_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					__m256i const ymm_shuffle = _mm256_setr_epi8(
							3, 3, 3, 3, 3, 3, 3, 3,
							2, 2, 2, 2, 2, 2, 2, 2,
							1, 1, 1, 1, 1, 1, 1, 1,
							0, 0, 0, 0, 0, 0, 0, 0
					); // AVX
					__m256i const ymm_andmask = _mm256_setr_epi8(
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0
					); // AVX
					__m256i const ymm_ALL_ONE = _mm256_set1_epi8(1); // AVX

					kerbal::type_traits::aligned_storage<
							kerbal::smath::max_sa_sb<std::size_t, sizeof(bitarray_result_t), sizeof(uint64_t)>::value,
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;

					__m256i ymm_x = _mm256_set1_epi32(static_cast<int>(x)); // AVX
					ymm_x = _mm256_shuffle_epi8(ymm_x, ymm_shuffle); // AVX2
					ymm_x = _mm256_and_si256(ymm_x, ymm_andmask); // AVX2
					ymm_x = _mm256_min_epu8(ymm_x, ymm_ALL_ONE); // AVX2
					_mm256_storeu_si256(reinterpret_cast<__m256i*>(&as), ymm_x); // AVX2

					return reinterpret_cast<const bitarray_result_t &>(as);
				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint64_t>::type
				bitarray(kerbal::compatibility::uint64_t x)
				{
					typedef kerbal::compatibility::uint64_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					__m256i const ymm_shuffle = _mm256_setr_epi8(
							3, 3, 3, 3, 3, 3, 3, 3,
							2, 2, 2, 2, 2, 2, 2, 2,
							1, 1, 1, 1, 1, 1, 1, 1,
							0, 0, 0, 0, 0, 0, 0, 0
					); // AVX
					__m256i const ymm_andmask = _mm256_setr_epi8(
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0
					); // AVX
					__m256i const ymm_ALL_ONE = _mm256_set1_epi8(1); // AVX

					kerbal::type_traits::aligned_storage<
							kerbal::smath::max_sa_sb<std::size_t, sizeof(bitarray_result_t), sizeof(uint64_t)>::value,
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;

					__m256i ymm_x = _mm256_set1_epi32(static_cast<int>(x & 0xFFFFFFFF)); // AVX
					ymm_x = _mm256_shuffle_epi8(ymm_x, ymm_shuffle); // AVX2
					ymm_x = _mm256_and_si256(ymm_x, ymm_andmask); // AVX2
					ymm_x = _mm256_min_epu8(ymm_x, ymm_ALL_ONE); // AVX2
					_mm256_storeu_si256(reinterpret_cast<__m256i*>(&as) + 1, ymm_x); // AVX2

					ymm_x = _mm256_set1_epi32(static_cast<int>(x >> 32)); // AVX
					ymm_x = _mm256_shuffle_epi8(ymm_x, ymm_shuffle); // AVX2
					ymm_x = _mm256_and_si256(ymm_x, ymm_andmask); // AVX2
					ymm_x = _mm256_min_epu8(ymm_x, ymm_ALL_ONE); // AVX2
					_mm256_storeu_si256(reinterpret_cast<__m256i*>(&as) + 0, ymm_x); // AVX2

					return reinterpret_cast<const bitarray_result_t &>(as);
				}

			} // namespace avx2

		} // namespace detail

	} // namespace numeric

} // namespace kerbal


#endif // KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_AVX2_HPP
