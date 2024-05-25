/**
 * @file       mt_generate_copy_n_helper.hpp
 * @brief
 * @date       2021-11-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_HELPER_HPP
#define KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_HELPER_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/ignore_unused.hpp>

#include <climits>
#include <cstddef>

#include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.plain.part.hpp>


#ifndef KERBAL_RANDOM_ENABLE_MT_GENERATE_COPY_N_IE_OPTIMISE

#	if __AVX512F__ || __AVX2__ || __SSE2__ || __ARM_FEATURE_SVE || __ARM_NEON
#		define KERBAL_RANDOM_ENABLE_MT_GENERATE_COPY_N_IE_OPTIMISE 1
#	else
#		define KERBAL_RANDOM_ENABLE_MT_GENERATE_COPY_N_IE_OPTIMISE 0
#	endif

#endif


#if KERBAL_RANDOM_ENABLE_MT_GENERATE_COPY_N_IE_OPTIMISE

#	if __AVX512F__
#		include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.avx512f.part.hpp>
#	endif

#	if __AVX2__
#		include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.avx2.part.hpp>
#	endif

#	if __SSE2__
#		include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.sse2.part.hpp>
#	endif

#	if __ARM_FEATURE_SVE
#		include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.sve.part.hpp>
#	endif

#	if __ARM_NEON
#		include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.neon.part.hpp>
#	endif

#	include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.plain.part.hpp>

#endif

#undef EACH


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

#if KERBAL_RANDOM_ENABLE_MT_GENERATE_COPY_N_IE_OPTIMISE

			template <
				typename UIntType,
				std::size_t U, UIntType D,
				std::size_t S, UIntType B,
				std::size_t T, UIntType C,
				std::size_t L
			>
			void mt_generate_copy_n_fix_integer_simd_dispatch(
				const UIntType mt_now[],
				UIntType * out,
				std::size_t n,
				kerbal::type_traits::integral_constant<std::size_t, 32>
			) KERBAL_NOEXCEPT
			{
				const kerbal::compatibility::uint32_t * mt_nowr = reinterpret_cast<const kerbal::compatibility::uint32_t *>(mt_now);
				kerbal::compatibility::uint32_t * outr = reinterpret_cast<kerbal::compatibility::uint32_t *>(out);

				kerbal::utility::ignore_unused(mt_nowr);
				kerbal::utility::ignore_unused(outr);

#		if 0
				// pass
#		elif __AVX512F__
				avx512f::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		elif __AVX2__
				avx2::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		elif __SSE2__
				sse2::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		elif __ARM_FEATURE_SVE
				sve::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		elif __ARM_NEON
				neon::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		else
				plain::mt_generate_copy_n<kerbal::compatibility::uint32_t, kerbal::compatibility::uint32_t *, U, D, S, B, T, C, L>(mt_now, out, n);
#		endif
			}

			template <
				typename UIntType,
				std::size_t U, UIntType D,
				std::size_t S, UIntType B,
				std::size_t T, UIntType C,
				std::size_t L
			>
			void mt_generate_copy_n_fix_integer_simd_dispatch(
				const UIntType mt_now[],
				UIntType * out,
				std::size_t n,
				kerbal::type_traits::integral_constant<std::size_t, 64>
			) KERBAL_NOEXCEPT
			{
				const kerbal::compatibility::uint64_t * mt_nowr = reinterpret_cast<const kerbal::compatibility::uint64_t *>(mt_now);
				kerbal::compatibility::uint64_t * outr = reinterpret_cast<kerbal::compatibility::uint64_t *>(out);

				kerbal::utility::ignore_unused(mt_nowr);
				kerbal::utility::ignore_unused(outr);

#		if 0
				// pass
#		elif __AVX512F__
				avx512f::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		elif __AVX2__
				avx2::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		elif __SSE2__
				sse2::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		elif __ARM_FEATURE_SVE
				sve::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		elif __ARM_NEON
				neon::mt_generate_copy_n<U, D, S, B, T, C, L>(mt_nowr, outr, n);
#		else
				plain::mt_generate_copy_n<kerbal::compatibility::uint64_t, kerbal::compatibility::uint64_t *, U, D, S, B, T, C, L>(mt_now, out, n);
#		endif
			}

			template <
				typename UIntType,
				std::size_t U, UIntType D,
				std::size_t S, UIntType B,
				std::size_t T, UIntType C,
				std::size_t L,
				std::size_t Size
			>
			KERBAL_CONSTEXPR14
			void mt_generate_copy_n_fix_integer_simd_dispatch(
				const UIntType mt_now[],
				UIntType * out,
				std::size_t n,
				kerbal::type_traits::integral_constant<std::size_t, Size>
			) KERBAL_NOEXCEPT
			{
				plain::mt_generate_copy_n<UIntType, UIntType *, U, D, S, B, T, C, L>(mt_now, out, n);
			}

#endif // KERBAL_RANDOM_ENABLE_MT_GENERATE_COPY_N_IE_OPTIMISE


			template <
				typename UIntType,
				std::size_t U, UIntType D,
				std::size_t S, UIntType B,
				std::size_t T, UIntType C,
				std::size_t L
			>
			class mt_generate_copy_n_helper
			{
				protected:
					typedef UIntType result_type;


#if KERBAL_RANDOM_ENABLE_MT_GENERATE_COPY_N_IE_OPTIMISE

					static void fix_integer_type_dispatch(const result_type mt_now[], result_type * out, std::size_t n) KERBAL_NOEXCEPT
					{
						mt_generate_copy_n_fix_integer_simd_dispatch<UIntType, U, D, S, B, T, C, L>(
							mt_now, out, n,
							kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(UIntType)>()
						);
					}

					KERBAL_CONSTEXPR14
					static void is_constant_evaluated_handler(const result_type mt_now[], result_type * out, std::size_t n) KERBAL_NOEXCEPT
					{

#	if __cplusplus >= 201402L

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						KERBAL_IS_CONSTANT_EVALUATED() ?
							void(plain::mt_generate_copy_n<UIntType, result_type *, U, D, S, B, T, C, L>(mt_now, out, n)) :
							fix_integer_type_dispatch(mt_now, out, n);
#		else
						plain::mt_generate_copy_n<UIntType, result_type *, U, D, S, B, T, C, L>(mt_now, out, n);
#		endif

#	else
						fix_integer_type_dispatch(mt_now, out, n);
#	endif

					}

#endif


					KERBAL_CONSTEXPR14
					static result_type * mt_generate_copy_n(const result_type mt_now[], result_type * out, std::size_t n) KERBAL_NOEXCEPT
					{
#if KERBAL_RANDOM_ENABLE_MT_GENERATE_COPY_N_IE_OPTIMISE
						is_constant_evaluated_handler(mt_now, out, n);
						return out + n;
#else
						return plain::mt_generate_copy_n<result_type, result_type *, U, D, S, B, T, C, L>(mt_now, out, n);
#endif
					}


					template <typename OutputIterator>
					KERBAL_CONSTEXPR14
					static OutputIterator mt_generate_copy_n(const result_type mt_now[], OutputIterator out, std::size_t n)
					{
						return plain::mt_generate_copy_n<result_type, OutputIterator, U, D, S, B, T, C, L>(mt_now, out, n);
					}

			};

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_HELPER_HPP
