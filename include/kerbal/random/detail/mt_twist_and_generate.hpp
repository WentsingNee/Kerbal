/**
 * @file       mt_twist_and_generate.hpp
 * @brief
 * @date       2024-05-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_TWIST_AND_GENERATE_HPP
#define KERBAL_RANDOM_DETAIL_MT_TWIST_AND_GENERATE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/ignore_unused.hpp>

#include <climits>
#include <cstddef>

#include <kerbal/random/detail/mt_twist_and_generate/mt_twist_and_generate.plain.part.hpp>


#ifndef KERBAL_RANDOM_ENABLE_MT_TWIST_AND_GENERATE_IE_OPTIMISE

#	if __AVX512F__ || __AVX2__ || __SSE4_1__ || __SSE2__ || __ARM_FEATURE_SVE || __ARM_NEON
#		define KERBAL_RANDOM_ENABLE_MT_TWIST_AND_GENERATE_IE_OPTIMISE 1
#	else
#		define KERBAL_RANDOM_ENABLE_MT_TWIST_AND_GENERATE_IE_OPTIMISE 0
#	endif

#endif


#if KERBAL_RANDOM_ENABLE_MT_TWIST_AND_GENERATE_IE_OPTIMISE

//#	if __AVX512F__
//#		include <kerbal/random/detail/mt_twist_and_generate/mt_twist_and_generate.avx512f.part.hpp>
//#	endif

#	if __AVX2__
#		include <kerbal/random/detail/mt_twist_and_generate/mt_twist_and_generate.avx2.part.hpp>
#	endif

//#	if __SSE4_1__
//#		include <kerbal/random/detail/mt_twist_and_generate/mt_twist_and_generate.sse41.part.hpp>
//#	endif
//
//#	if __SSE2__
//#		include <kerbal/random/detail/mt_twist_and_generate/mt_twist_and_generate.sse2.part.hpp>
//#	endif
//
//#	if __ARM_FEATURE_SVE
//#		include <kerbal/random/detail/mt_twist_and_generate/mt_twist_and_generate.sve.part.hpp>
//#	endif
//
//#	if __ARM_NEON
//#		include <kerbal/random/detail/mt_twist_and_generate/mt_twist_and_generate.neon.part.hpp>
//#	endif

#	include <kerbal/random/detail/mt_twist_and_generate/mt_twist_and_generate.plain.part.hpp>

#endif


#undef EACH1
#undef EACH2
#undef EACH3


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

#if KERBAL_RANDOM_ENABLE_MT_TWIST_AND_GENERATE_IE_OPTIMISE

			template <
				typename UIntType, typename OutputIterator,
				std::size_t N, std::size_t M, std::size_t R, UIntType A,
				std::size_t U, UIntType D,
				std::size_t S, UIntType B,
				std::size_t T, UIntType C,
				std::size_t L
			>
			void mt_twist_and_generate_fix_integer_simd_dispatch(
				UIntType mt[N],
				UIntType * out,
				kerbal::type_traits::integral_constant<std::size_t, 32>
			) KERBAL_NOEXCEPT
			{
				kerbal::compatibility::uint32_t * mtr = reinterpret_cast<kerbal::compatibility::uint32_t *>(mt);
				kerbal::compatibility::uint32_t * outr = reinterpret_cast<kerbal::compatibility::uint32_t *>(out);

				kerbal::utility::ignore_unused(mtr);
				kerbal::utility::ignore_unused(outr);

#		if 0
				// pass
//#		elif __AVX512F__
//				avx512f::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
#		elif __AVX2__
				avx2::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
//#		elif __SSE4_1__
//				sse41::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
//#		elif __SSE2__
//				sse2::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
//#		elif __ARM_FEATURE_SVE
//				sve::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
//#		elif __ARM_NEON
//				neon::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
#		else
				plain::mt_twist_and_generate<kerbal::compatibility::uint32_t, N, M, R, A, U, D, S, B, T, C, L>(mt, outr);
#		endif
			}

			template <
				typename UIntType, typename OutputIterator,
				std::size_t N, std::size_t M, std::size_t R, UIntType A,
				std::size_t U, UIntType D,
				std::size_t S, UIntType B,
				std::size_t T, UIntType C,
				std::size_t L
			>
			void mt_twist_and_generate_fix_integer_simd_dispatch(
				UIntType mt[N],
				UIntType * out,
				kerbal::type_traits::integral_constant<std::size_t, 64>
			) KERBAL_NOEXCEPT
			{
				kerbal::compatibility::uint64_t * mtr = reinterpret_cast<kerbal::compatibility::uint64_t *>(mt);
				kerbal::compatibility::uint64_t * outr = reinterpret_cast<kerbal::compatibility::uint64_t *>(out);

				kerbal::utility::ignore_unused(mtr);
				kerbal::utility::ignore_unused(outr);

#		if 0
				// pass
//#		elif __AVX512F__
//				avx512f::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
#		elif __AVX2__
				avx2::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
//#		elif __SSE2__
//				sse2::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
//#		elif __ARM_FEATURE_SVE
//				sve::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
//#		elif __ARM_NEON
//				neon::mt_twist_and_generate<N, M, R, A, U, D, S, B, T, C, L>(mtr, outr);
#		else
				plain::mt_twist_and_generate<kerbal::compatibility::uint64_t, N, M, R, A, U, D, S, B, T, C, L>(mt, outr);
#		endif
			}

			template <
				typename UIntType, typename OutputIterator,
				std::size_t N, std::size_t M, std::size_t R, UIntType A,
				std::size_t U, UIntType D,
				std::size_t S, UIntType B,
				std::size_t T, UIntType C,
				std::size_t L,
				std::size_t Size
			>
			KERBAL_CONSTEXPR14
			void mt_twist_and_generate_fix_integer_simd_dispatch(
				UIntType mt[N],
				UIntType * out,
				kerbal::type_traits::integral_constant<std::size_t, Size>
			) KERBAL_NOEXCEPT
			{
				plain::mt_twist_and_generate<UIntType, N, M, R, A>(mt, out);
			}

#endif // KERBAL_RANDOM_ENABLE_MT_TWIST_AND_GENERATE_IE_OPTIMISE


			template <
				typename UIntType, typename OutputIterator,
				std::size_t N, std::size_t M, std::size_t R, UIntType A,
				std::size_t U, UIntType D,
				std::size_t S, UIntType B,
				std::size_t T, UIntType C,
				std::size_t L
			>
			class mt_twist_and_generate_helper
			{
				protected:
					typedef UIntType result_type;


#if KERBAL_RANDOM_ENABLE_MT_TWIST_AND_GENERATE_IE_OPTIMISE

					static void fix_integer_type_dispatch(UIntType mt[N], UIntType * out) KERBAL_NOEXCEPT
					{
						mt_twist_and_generate_fix_integer_simd_dispatch<UIntType, N, M, R, A>(
							mt, out,
							kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(UIntType)>()
						);
					}

					KERBAL_CONSTEXPR14
					static void is_constant_evaluated_handler(UIntType mt[N], UIntType * out) KERBAL_NOEXCEPT
					{

#	if __cplusplus >= 201402L

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						KERBAL_IS_CONSTANT_EVALUATED() ?
							plain::mt_twist_and_generate<UIntType, N, M, R, A>(mt, out) :
							fix_integer_type_dispatch(mt, out);
#		else
						plain::mt_twist_and_generate<UIntType, N, M, R, A>(mt, out);
#		endif

#	else
						fix_integer_type_dispatch(mt, out);
#	endif

					}

#endif


					KERBAL_CONSTEXPR14
					static void twist_and_generate(result_type mt[N], UIntType * out) KERBAL_NOEXCEPT
					{
#if KERBAL_RANDOM_ENABLE_MT_TWIST_AND_GENERATE_IE_OPTIMISE
						is_constant_evaluated_handler(mt, out);
#else
						plain::mt_twist_and_generate<result_type, N, M, R, A>(mt, out);
#endif
					}

			};

		} // namespace detail

	} // namespace random

} // namespace kerbal


#endif // KERBAL_RANDOM_DETAIL_MT_TWIST_AND_GENERATE_HPP
