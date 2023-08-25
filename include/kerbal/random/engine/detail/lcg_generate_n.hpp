/**
 * @file       lcg_generate_n.hpp
 * @brief
 * @date       lcg_generate_n.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_LCG_GENERATE_N_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_LCG_GENERATE_N_HPP

#include <kerbal/compatibility/alignas.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/smath/multiply_mod_sa_b_sm.hpp>
#include <kerbal/smath/sigma_pow_mod_sa_n_sm.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <immintrin.h>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			template <typename ResultType, ResultType a, ResultType m, std::size_t I>
			struct Aat;

			template <typename ResultType, ResultType a, ResultType m>
			struct Aat<ResultType, a, m, 0> :
					kerbal::type_traits::integral_constant<ResultType, 1>
			{
			};

			template <typename ResultType, ResultType a, ResultType m, std::size_t I>
			struct Aat :
					kerbal::type_traits::integral_constant<ResultType,
							kerbal::smath::multiply_mod_sa_b_sm<ResultType, a, m>::cacl(Aat<ResultType, a, m, I - 1>::value)
					>
			{
			};


			template <typename ResultType, ResultType a, ResultType c, ResultType m, std::size_t I>
			struct Cat;

			template <typename ResultType, ResultType a, ResultType c, ResultType m>
			struct Cat<ResultType, a, c, m, 0> :
					kerbal::type_traits::integral_constant<ResultType, c>
			{
			};

			template <typename ResultType, ResultType a, ResultType c, ResultType m, std::size_t I>
			struct Cat :
					kerbal::type_traits::integral_constant<ResultType,
							kerbal::smath::multiply_mod_sa_b_sm<ResultType, c, m>::cacl(
									kerbal::smath::sigma_pow_mod_sa_n_sm<ResultType, a, m>::cacl(I + 1)
							)
					>
			{
			};


			template <kerbal::compatibility::uint32_t a, kerbal::compatibility::uint32_t m, int>
			struct schrage_dispatch;

			template <kerbal::compatibility::uint32_t a, kerbal::compatibility::uint32_t m>
			struct schrage : schrage_dispatch<
					a, m,
					kerbal::smath::detail::multiply_mod_sa_b_sm_selector<kerbal::compatibility::uint32_t, a, m>::value
			>
			{
			};

			template <kerbal::compatibility::uint32_t a, kerbal::compatibility::uint32_t m>
			struct schrage_dispatch<a, m, 0> // a % m != 0
			{
					static inline __m256i cacl(const __m256i & ymm_b) KERBAL_NOEXCEPT
					{
						typedef kerbal::compatibility::uint32_t ResultType;

						typedef kerbal::type_traits::integral_constant<ResultType, m / a> Q;
						typedef kerbal::type_traits::integral_constant<ResultType, m % a> R;

						typedef kerbal::type_traits::integral_constant<int, 256 / 32> STEP;

						__m256i const ymm_a = _mm256_set1_epi32(a);
						__m256i const ymm_r = _mm256_set1_epi32(R::value);
						__m256i const ymm_m = _mm256_set1_epi32(m);

						kerbal::compatibility::uint32_t bmodq KERBAL_ALIGNAS(32) [STEP::value];
						kerbal::compatibility::uint32_t bdivq KERBAL_ALIGNAS(32) [STEP::value];
						_mm256_store_si256(reinterpret_cast<__m256i *>(&bmodq[0]), ymm_b);
						for (int i = 0; i < STEP::value; ++i) {
							bdivq[i] = bmodq[i] / Q::value;
							bmodq[i] = bmodq[i] % Q::value;
						}

						__m256i ymm_bmodq = _mm256_load_si256(reinterpret_cast<const __m256i *>(&bmodq));
						__m256i ymm_bdivq = _mm256_load_si256(reinterpret_cast<const __m256i *>(&bdivq));

//						ResultType t0 = a::value * (b % Q::value);
//						ResultType t1 =
//								R::value <= Q::value ?
//								R::value * (b / Q::value) :
//								multiply_mod_sa_b_sm_impl<ResultType, R::value, m>::cacl(b / Q::value);
//						return t0 - t1 + (t0 < t1) * m;

						__m256i ymm_t0 = _mm256_mullo_epi32(ymm_a, ymm_bmodq);

						__m256i ymm_t1;
						if (R::value <= Q::value) {
							ymm_t1 = _mm256_mullo_epi32(ymm_r, ymm_bdivq);
						} else {
							ymm_t1 = schrage<R::value, m>::cacl(ymm_bdivq);
						}

						__m256i ymm_result = _mm256_sub_epi32(ymm_t0, ymm_t1);
						__m256i ymm_cmp = _mm256_cmpeq_epi32(
								_mm256_max_epu32(ymm_t0, ymm_t1),
								ymm_t0
						);
						ymm_cmp = _mm256_andnot_si256(ymm_cmp, ymm_m);
						ymm_result = _mm256_add_epi32(ymm_result, ymm_cmp);

						return ymm_result;
					}
			};

			template <kerbal::compatibility::uint32_t a, kerbal::compatibility::uint32_t m>
			struct schrage_dispatch<a, m, 1> // a % m == 0
			{
					static inline __m256i cacl(const __m256i & ymm_b) KERBAL_NOEXCEPT
					{
						typedef kerbal::compatibility::uint32_t ResultType;
						return _mm256_setzero_si256();
					}
			};


			template <kerbal::compatibility::uint32_t a, kerbal::compatibility::uint32_t c, kerbal::compatibility::uint32_t m>
			struct lcg_generate_copy_n_m
			{
					typedef kerbal::compatibility::uint32_t ResultType;

					template <std::size_t I>
					struct Ai : detail::Aat<ResultType, a, m, I>
					{
					};

					template <std::size_t I>
					struct Ci : detail::Cat<ResultType, a, c, m, I>
					{
					};

					static void cacl(ResultType s0, ResultType out[], std::size_t n) // m != 0
					{
						typedef kerbal::type_traits::integral_constant<int, 256 / 32> STEP;

						ResultType tmp[STEP::value] =
						{
							kerbal::smath::add_mod_sm<ResultType, m>::cacl(
									kerbal::smath::multiply_mod_sa_b_sm<ResultType, Ai<1>::value, m>::cacl(s0), Ci<1>::value
							),
							kerbal::smath::add_mod_sm<ResultType, m>::cacl(
									kerbal::smath::multiply_mod_sa_b_sm<ResultType, Ai<2>::value, m>::cacl(s0), Ci<2>::value
							),
							kerbal::smath::add_mod_sm<ResultType, m>::cacl(
									kerbal::smath::multiply_mod_sa_b_sm<ResultType, Ai<3>::value, m>::cacl(s0), Ci<3>::value
							),
							kerbal::smath::add_mod_sm<ResultType, m>::cacl(
									kerbal::smath::multiply_mod_sa_b_sm<ResultType, Ai<4>::value, m>::cacl(s0), Ci<4>::value
							),
							kerbal::smath::add_mod_sm<ResultType, m>::cacl(
									kerbal::smath::multiply_mod_sa_b_sm<ResultType, Ai<5>::value, m>::cacl(s0), Ci<5>::value
							),
							kerbal::smath::add_mod_sm<ResultType, m>::cacl(
									kerbal::smath::multiply_mod_sa_b_sm<ResultType, Ai<6>::value, m>::cacl(s0), Ci<6>::value
							),
							kerbal::smath::add_mod_sm<ResultType, m>::cacl(
									kerbal::smath::multiply_mod_sa_b_sm<ResultType, Ai<7>::value, m>::cacl(s0), Ci<7>::value
							),
							kerbal::smath::add_mod_sm<ResultType, m>::cacl(
									kerbal::smath::multiply_mod_sa_b_sm<ResultType, Ai<8>::value, m>::cacl(s0), Ci<8>::value
							),
						};

						typedef Ai<7> AROUND;
						typedef Ci<7> CROUND;

						__m256i const ymm_C = _mm256_set1_epi32(CROUND::value); // AVX
						__m256i const ymm_M = _mm256_set1_epi32(m); // AVX
						__m256i const ymm_MSC = _mm256_set1_epi32(m - CROUND::value); // AVX
						__m256i const ymm_iota = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7); // AVX

						__m256i ymm_s = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&tmp[0]));

						if (n < STEP::value) {
							__m256i ymm_mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(n), ymm_iota); // AVX2
							_mm256_maskstore_epi32(reinterpret_cast<int *>(&out[0]), ymm_mask, ymm_s);
							return;
						}

						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&out[0]), ymm_s);
						std::size_t i = STEP::value;

						for (; i + STEP::value <= n; i += STEP::value) {
							__m256i ymm_out = schrage<AROUND::value, m>::cacl(ymm_s);

							// add_mod
							// a + c - (a >= m - c) * m
							ymm_s = _mm256_add_epi32(ymm_out, ymm_C);
							__m256i ymm_cmp = _mm256_cmpeq_epi32( // AVX2
									ymm_out,
									_mm256_max_epu32(ymm_out, ymm_MSC) // AVX2
							); // <=> cmpge_epu32
							__m256i ymm_sub = _mm256_and_si256(ymm_cmp, ymm_M);
							ymm_s = _mm256_sub_epi32(ymm_s, ymm_sub);

							_mm256_storeu_si256(reinterpret_cast<__m256i *>(&out[i]), ymm_s);
						}

						int remain = n % STEP::value;
						if (remain != 0) {
							__m256i ymm_out = schrage<AROUND::value, m>::cacl(ymm_s);

							// add_mod
							ymm_s = _mm256_add_epi32(ymm_out, ymm_C);
							__m256i ymm_cmp = _mm256_cmpeq_epi32( // AVX2
									ymm_out,
									_mm256_max_epu32(ymm_out, ymm_MSC) // AVX2
							); // <=> cmpge_epu32
							__m256i ymm_sub = _mm256_and_si256(ymm_cmp, ymm_M);
							ymm_s = _mm256_sub_epi32(ymm_s, ymm_sub);

							__m256i ymm_mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(remain), ymm_iota); // AVX2
							_mm256_maskstore_epi32(reinterpret_cast<int *>(&out[i]), ymm_mask, ymm_s);
						}
					}
			};

			template <kerbal::compatibility::uint32_t a, kerbal::compatibility::uint32_t c, kerbal::compatibility::uint32_t m>
			struct lcg_generate_copy_n
			{
					typedef kerbal::compatibility::uint32_t ResultType;

					template <std::size_t I>
					struct Ai : detail::Aat<ResultType, a, m, I>
					{
					};

					template <std::size_t I>
					struct Ci : detail::Cat<ResultType, a, c, m, I>
					{
					};

					static void cacl(ResultType s0, ResultType out[], std::size_t n) // m == 0
					{
						typedef kerbal::type_traits::integral_constant<int, 256 / 32> STEP;

						__m256i const ymm_A_init = _mm256_setr_epi32(
								Ai<0>::value, Ai<1>::value, Ai<2>::value, Ai<3>::value,
								Ai<4>::value, Ai<5>::value, Ai<6>::value, Ai<7>::value
						); // AVX
						__m256i const ymm_C_init = _mm256_setr_epi32(
								Ci<0>::value, Ci<1>::value, Ci<2>::value, Ci<3>::value,
								Ci<4>::value, Ci<5>::value, Ci<6>::value, Ci<7>::value
						); // AVX
						__m256i const ymm_A = _mm256_set1_epi32(Ai<7>::value);
						__m256i const ymm_C = _mm256_set1_epi32(Ci<7>::value);
						__m256i const ymm_iota = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7); // AVX

						__m256i ymm_s = _mm256_set1_epi32(s0);
						ymm_s = _mm256_mullo_epi32(ymm_s, ymm_A_init);
						ymm_s = _mm256_add_epi32(ymm_s, ymm_C_init);

						if (n < STEP::value) {
							__m256i ymm_mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(n), ymm_iota); // AVX2
							_mm256_maskstore_epi32(reinterpret_cast<int *>(&out[0]), ymm_mask, ymm_s);
							return;
						}

						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&out[0]), ymm_s);
						std::size_t i = STEP::value;

						for (; i + STEP::value <= n; i += STEP::value) {
							ymm_s = _mm256_mullo_epi32(ymm_s, ymm_A);
							ymm_s = _mm256_add_epi32(ymm_s, ymm_C);
							_mm256_storeu_si256(reinterpret_cast<__m256i *>(&out[i]), ymm_s);
						}

						int remain = n % STEP::value;
						if (remain != 0) {
							ymm_s = _mm256_mullo_epi32(ymm_s, ymm_A);
							ymm_s = _mm256_add_epi32(ymm_s, ymm_C);
							__m256i ymm_mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(remain), ymm_iota); // AVX2
							_mm256_maskstore_epi32(reinterpret_cast<int *>(&out[i]), ymm_mask, ymm_s);
						}
					}
			};

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_DETAIL_LCG_GENERATE_N_HPP
