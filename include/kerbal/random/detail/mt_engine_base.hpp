/**
 * @file       mt_engine_base.hpp
 * @brief
 * @date       2021-10-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MERSENNE_TWISTER_ENGINE_BASE_HPP
#define KERBAL_RANDOM_DETAIL_MERSENNE_TWISTER_ENGINE_BASE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>
#include <climits>


#ifndef KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE

#	if __AVX512F__ || __AVX2__ || __SSE2__
#		define KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE 1
#	else
#		define KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE 0
#	endif

#endif


#if KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE

#	if __AVX512F__
#		include <immintrin.h>
#	endif

#	if __AVX2__
#		include <immintrin.h>
#	endif

#	if __SSE2__
#		include <emmintrin.h>
#	endif

#endif


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

#		define EACH1(i) \
				do { \
					result_type y = (mt[i] & UPPER_MASK::value) | (mt[(i) + 1] & LOWER_MASK::value); \
					mt[i] = mt[(i) + M] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0); \
				} while (0)

#		define EACH2(i) \
				do { \
					result_type y = (mt[i] & UPPER_MASK::value) | (mt[(i) + 1] & LOWER_MASK::value); \
					mt[i] = mt[(i) - (NPM::value)] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0); \
				} while (0)


#	if KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE && __AVX512F__

			namespace avx512f
			{

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
				void mt_twist(kerbal::compatibility::uint32_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 512 / 32> STEP;
					const __m512i zmm_UPPER_MASK = _mm512_set1_epi32(UPPER_MASK::value); // AVX512F
					const __m512i zmm_ZERO = _mm512_set1_epi32(0); // AVX512F
					const __m512i zmm_ONE = _mm512_set1_epi32(1); // AVX512F
					const __m512i zmm_A = _mm512_set1_epi32(A); // AVX512F

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m512i zmm_mti = _mm512_loadu_si512(&mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_loadu_si512(&mt[i + 1]); // AVX512F

					/*
						__m512i zmm_y = _mm512_or_si512( // AVX512F
								_mm512_and_si512(zmm_UPPER_MASK, zmm_mti), // AVX512F
								_mm512_andnot_si512(zmm_UPPER_MASK, zmm_mtip1)); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						__m512i zmm_y = _mm512_ternarylogic_epi32(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010

						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi32(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi32(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi32(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_loadu_si512(&mt[i + M]); // AVX512F

					/*
						zmm_y = _mm512_xor_si512(zmm_y, zmm_mag_mask); // AVX512F
						zmm_mti = _mm512_xor_si512(zmm_y, zmm_mtipm); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						zmm_mti = _mm512_ternarylogic_epi32(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110

						_mm512_storeu_si512(&mt[i], zmm_mti); // AVX512F
					}

					while (i < NPM::value) {
						EACH1(i);
						++i;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m512i zmm_mti = _mm512_loadu_si512(&mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_loadu_si512(&mt[i + 1]); // AVX512F

					/*
						__m512i zmm_y = _mm512_or_si512( // AVX512F
								_mm512_and_si512(zmm_UPPER_MASK, zmm_mti), // AVX512F
								_mm512_andnot_si512(zmm_UPPER_MASK, zmm_mtip1)); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						__m512i zmm_y = _mm512_ternarylogic_epi32(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010

						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi32(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi32(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi32(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_loadu_si512(&mt[i - (NPM::value)]); // AVX512F

					/*
						zmm_y = _mm512_xor_si512(zmm_y, zmm_mag_mask); // AVX512F
						zmm_mti = _mm512_xor_si512(zmm_y, zmm_mtipm); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						zmm_mti = _mm512_ternarylogic_epi32(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110

						_mm512_storeu_si512(&mt[i], zmm_mti); // AVX512F
					}

					while (i < N - 1) {
						EACH2(i);
						++i;
					}

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint64_t A>
				void mt_twist(kerbal::compatibility::uint64_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 512 / 64> STEP;
					const __m512i zmm_UPPER_MASK = _mm512_set1_epi64(UPPER_MASK::value); // AVX512F
					const __m512i zmm_ZERO = _mm512_set1_epi64(0); // AVX512F
					const __m512i zmm_ONE = _mm512_set1_epi64(1); // AVX512F
					const __m512i zmm_A = _mm512_set1_epi64(A); // AVX512F

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m512i zmm_mti = _mm512_loadu_si512(&mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_loadu_si512(&mt[i + 1]); // AVX512F

					/*
						__m512i zmm_y = _mm512_or_si512( // AVX512F
								_mm512_and_si512(zmm_UPPER_MASK, zmm_mti), // AVX512F
								_mm512_andnot_si512(zmm_UPPER_MASK, zmm_mtip1)); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						__m512i zmm_y = _mm512_ternarylogic_epi64(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010

						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi64(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi64(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi64(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_loadu_si512(&mt[i + M]); // AVX512F

					/*
						zmm_y = _mm512_xor_si512(zmm_y, zmm_mag_mask); // AVX512F
						zmm_mti = _mm512_xor_si512(zmm_y, zmm_mtipm); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						zmm_mti = _mm512_ternarylogic_epi64(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110

						_mm512_storeu_si512(&mt[i], zmm_mti); // AVX512F
					}

					while (i < NPM::value) {
						EACH1(i);
						++i;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m512i zmm_mti = _mm512_loadu_si512(&mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_loadu_si512(&mt[i + 1]); // AVX512F

					/*
						__m512i zmm_y = _mm512_or_si512( // AVX512F
								_mm512_and_si512(zmm_UPPER_MASK, zmm_mti), // AVX512F
								_mm512_andnot_si512(zmm_UPPER_MASK, zmm_mtip1)); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						__m512i zmm_y = _mm512_ternarylogic_epi64(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010

						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi64(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi64(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi64(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_loadu_si512(&mt[i - (NPM::value)]); // AVX512F

					/*
						zmm_y = _mm512_xor_si512(zmm_y, zmm_mag_mask); // AVX512F
						zmm_mti = _mm512_xor_si512(zmm_y, zmm_mtipm); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						zmm_mti = _mm512_ternarylogic_epi64(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110

						_mm512_storeu_si512(&mt[i], zmm_mti); // AVX512F
					}

					while (i < N - 1) {
						EACH2(i);
						++i;
					}

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}


			} // namespace avx512f

#	endif

#	if KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE && __AVX2__

			namespace avx2
			{

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
				void mt_twist(kerbal::compatibility::uint32_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 256 / 32> STEP;
					const __m256i ymm_UPPER_MASK = _mm256_set1_epi32(UPPER_MASK::value); // AVX
					const __m256i ymm_ZERO = _mm256_set1_epi32(0); // AVX
					const __m256i ymm_ONE = _mm256_set1_epi32(1); // AVX
					const __m256i ymm_A = _mm256_set1_epi32(A); // AVX

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi32(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi32(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi32(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + M])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(&mt[i]), ymm_mti); // AVX
					}

					while (i < NPM::value) {
						EACH1(i);
						++i;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi32(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi32(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi32(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i - (NPM::value)])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(&mt[i]), ymm_mti); // AVX
					}

					while (i < N - 1) {
						EACH2(i);
						++i;
					}

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint64_t A>
				void mt_twist(kerbal::compatibility::uint64_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 256 / 64> STEP;
					const __m256i ymm_UPPER_MASK = _mm256_set1_epi64x(UPPER_MASK::value); // AVX
					const __m256i ymm_ZERO = _mm256_set1_epi64x(0); // AVX
					const __m256i ymm_ONE = _mm256_set1_epi64x(1); // AVX
					const __m256i ymm_A = _mm256_set1_epi64x(A); // AVX

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + M])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(&mt[i]), ymm_mti); // AVX
					}

					while (i < NPM::value) {
						EACH1(i);
						++i;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i - (NPM::value)])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(&mt[i]), ymm_mti); // AVX
					}

					while (i < N - 1) {
						EACH2(i);
						++i;
					}

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}


			} // namespace avx2

#	endif

#	if KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE && __SSE2__

			namespace sse2
			{

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
				void mt_twist(kerbal::compatibility::uint32_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;
					const __m128i xmm_UPPER_MASK = _mm_set1_epi32(UPPER_MASK::value); // SSE2
					const __m128i xmm_ZERO = _mm_set1_epi32(0); // SSE2
					const __m128i xmm_ONE = _mm_set1_epi32(1); // SSE2
					const __m128i xmm_A = _mm_set1_epi32(A); // SSE2

					unsigned int i = 0; // Note: gcc unreasonable warning: iteration 4611686018427387903 invokes undefined behavior [-Waggressive-loop-optimizations]
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
								_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
								_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi32(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i + M])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i*>(&mt[i]), xmm_mti); // SSE2
					}

					while (i < NPM::value) {
						EACH1(i);
						++i;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
								_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
								_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi32(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i - (NPM::value)])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i*>(&mt[i]), xmm_mti); // SSE2
					}

					while (i < N - 1) {
						EACH2(i);
						++i;
					}

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint64_t A>
				void mt_twist(kerbal::compatibility::uint64_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 64> STEP;
					const __m128i xmm_UPPER_MASK = _mm_set1_epi64x(UPPER_MASK::value); // SSE2
					const __m128i xmm_ZERO = _mm_set1_epi64x(0); // SSE2
					const __m128i xmm_ONE = _mm_set1_epi64x(1); // SSE2
					const __m128i xmm_A = _mm_set1_epi64x(A); // SSE2

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
								_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
								_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi64(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi64(xmm_mag_mask, xmm_ONE) SSE4.1
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi64(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i + M])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i*>(&mt[i]), xmm_mti); // SSE2
					}

					while (i < NPM::value) {
						EACH1(i);
						++i;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
								_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
								_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi64(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi64(xmm_mag_mask, xmm_ONE) SSE4.1
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi64(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i - (NPM::value)])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i*>(&mt[i]), xmm_mti); // SSE2
					}

					while (i < N - 1) {
						EACH2(i);
						++i;
					}

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

			} // namespace sse2

#	endif


			namespace plain
			{

				template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
				KERBAL_CONSTEXPR14
				void mt_twist(UIntType mt[N]) KERBAL_NOEXCEPT
				{
					typedef UIntType result_type;
					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					std::size_t i = 0;

					for (; i < NPM::value; ++i) {
						result_type y = (mt[i] & UPPER_MASK::value) | (mt[i + 1] & LOWER_MASK::value);
						mt[i] = mt[i + M] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
					}
					for (; i < N - 1; ++i) {
						result_type y = (mt[i] & UPPER_MASK::value) | (mt[i + 1] & LOWER_MASK::value);
						mt[i] = mt[i - (NPM::value)] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
					}
					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
				}

			} // namespace plain


#if KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE

			template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
			void mt_twist_simd_dispatch(kerbal::compatibility::uint32_t mt[N]) KERBAL_NOEXCEPT
			{
#		if __AVX512F__
				avx512f::mt_twist<N, M, R, A>(mt);
#		elif __AVX2__
				avx2::mt_twist<N, M, R, A>(mt);
#		elif __SSE2__
				sse2::mt_twist<N, M, R, A>(mt);
#		else
				plain::mt_twist<kerbal::compatibility::uint32_t, N, M, R, A>(mt);
#		endif
			}

			template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint64_t A>
			void mt_twist_simd_dispatch(kerbal::compatibility::uint64_t mt[N]) KERBAL_NOEXCEPT
			{
#		if __AVX512F__
				avx512f::mt_twist<N, M, R, A>(mt);
#		elif __AVX2__
				avx2::mt_twist<N, M, R, A>(mt);
#		elif __SSE2__
				sse2::mt_twist<N, M, R, A>(mt);
#		else
				plain::mt_twist<kerbal::compatibility::uint64_t, N, M, R, A>(mt);
#		endif
			}


			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
			void mt_twist_fix_integer_type_convert(UIntType mt[N], kerbal::type_traits::integral_constant<std::size_t, 32>) KERBAL_NOEXCEPT
			{
				mt_twist_simd_dispatch<N, M, R, A>(reinterpret_cast<kerbal::compatibility::uint32_t*>(mt));
			}

			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
			void mt_twist_fix_integer_type_convert(UIntType mt[N], kerbal::type_traits::integral_constant<std::size_t, 64>) KERBAL_NOEXCEPT
			{
				mt_twist_simd_dispatch<N, M, R, A>(reinterpret_cast<kerbal::compatibility::uint64_t*>(mt));
			}

			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A, std::size_t Size>
			KERBAL_CONSTEXPR14
			void mt_twist_fix_integer_type_convert(UIntType mt[N], kerbal::type_traits::integral_constant<std::size_t, Size>) KERBAL_NOEXCEPT
			{
				plain::mt_twist<UIntType, N, M, R, A>(mt);
			}


			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
			void mt_twist_fix_interger_type_dispatch(UIntType mt[N]) KERBAL_NOEXCEPT
			{
				mt_twist_fix_integer_type_convert<UIntType, N, M, R, A>(mt, kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(UIntType)>());
			}


			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
			KERBAL_CONSTEXPR14
			void mt_twist_is_constant_evaluated_handler(UIntType mt[N]) KERBAL_NOEXCEPT
			{

#	if __cplusplus >= 201402L

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				KERBAL_IS_CONSTANT_EVALUATED() ?
						plain::mt_twist<UIntType, N, M, R, A>(mt) :
						mt_twist_fix_interger_type_dispatch<UIntType, N, M, R, A>(mt);
#		else
				plain::mt_twist<UIntType, N, M, R, A>(mt);
#		endif

#	else
				mt_twist_fix_interger_type_dispatch<UIntType, N, M, R, A>(mt);
#	endif

			}

#endif // KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE


			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
			class mt_engine_twist_helper
			{
				protected:
					typedef UIntType result_type;

					KERBAL_CONSTEXPR14
					static void twist(result_type mt[N]) KERBAL_NOEXCEPT
					{
#if KERBAL_RANDOM_ENABLE_MT_ENGINE_TWIST_SIMD_OPTIMISE
						mt_twist_is_constant_evaluated_handler<result_type, N, M, R, A>(mt);
#else
						plain::mt_twist<result_type, N, M, R, A>(mt);
#endif
					}

			};

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_ENGINE_BASE_HPP
