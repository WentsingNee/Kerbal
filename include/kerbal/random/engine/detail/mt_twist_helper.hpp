/**
 * @file       mt_twist_helper.hpp
 * @brief
 * @date       2021-10-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_HELPER_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_HELPER_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/ignore_unused.hpp>

#include <climits>
#include <cstddef>

#include <kerbal/random/engine/detail/mt_twist/mt_twist.plain.part.hpp>


#ifndef __ARM_NEON

#	include <kerbal/config/compiler_id.hpp>
#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

#		include <kerbal/config/compiler_private.hpp>
#		if KERBAL_MSVC_VERSION_MEETS(19, 0, 0) // msvc2015

#			include <kerbal/config/architecture.hpp>
#			if KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_ARM
#				define __ARM_NEON 1
#			endif
#		endif
#	endif
#endif


#ifndef KERBAL_RANDOM_ENABLE_MT_TWIST_IE_OPTIMISE

#	if __AVX512F__ || __AVX2__ || __SSE4_1__ || __SSE2__ || __ARM_FEATURE_SVE || __ARM_NEON
#		define KERBAL_RANDOM_ENABLE_MT_TWIST_IE_OPTIMISE 1
#	else
#		define KERBAL_RANDOM_ENABLE_MT_TWIST_IE_OPTIMISE 0
#	endif

#endif


#if KERBAL_RANDOM_ENABLE_MT_TWIST_IE_OPTIMISE

#	if __AVX512F__
#		include <kerbal/random/engine/detail/mt_twist/mt_twist.avx512f.part.hpp>
#	endif

#	if __AVX2__
#		include <kerbal/random/engine/detail/mt_twist/mt_twist.avx2.part.hpp>
#	endif

#	if __SSE4_1__
#		include <kerbal/random/engine/detail/mt_twist/mt_twist.sse41.part.hpp>
#	endif

#	if __SSE2__
#		include <kerbal/random/engine/detail/mt_twist/mt_twist.sse2.part.hpp>
#	endif

#	if __ARM_FEATURE_SVE
#		include <kerbal/random/engine/detail/mt_twist/mt_twist.sve.part.hpp>
#	endif

#	if __ARM_NEON
#		include <kerbal/random/engine/detail/mt_twist/mt_twist.neon.part.hpp>
#	endif

#	include <kerbal/random/engine/detail/mt_twist/mt_twist.plain.part.hpp>

#endif


#undef EACH1
#undef EACH2


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

#if KERBAL_RANDOM_ENABLE_MT_TWIST_IE_OPTIMISE

			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
			void mt_twist_fix_integer_simd_dispatch(
				UIntType mt[N],
				kerbal::type_traits::integral_constant<std::size_t, 32>
			) KERBAL_NOEXCEPT
			{
				kerbal::compatibility::uint32_t * mtr = reinterpret_cast<kerbal::compatibility::uint32_t *>(mt);

				kerbal::utility::ignore_unused(mtr);

#		if 0
				// pass
#		elif __AVX512F__
				avx512f::mt_twist<N, M, R, A>(mtr);
#		elif __AVX2__
				avx2::mt_twist<N, M, R, A>(mtr);
#		elif __SSE4_1__
				sse41::mt_twist<N, M, R, A>(mtr);
#		elif __SSE2__
				sse2::mt_twist<N, M, R, A>(mtr);
#		elif __ARM_FEATURE_SVE
				sve::mt_twist<N, M, R, A>(mtr);
#		elif __ARM_NEON
				neon::mt_twist<N, M, R, A>(mtr);
#		else
				plain::mt_twist<kerbal::compatibility::uint32_t, N, M, R, A>(mt);
#		endif
			}

			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
			void mt_twist_fix_integer_simd_dispatch(
				UIntType mt[N],
				kerbal::type_traits::integral_constant<std::size_t, 64>
			) KERBAL_NOEXCEPT
			{
				kerbal::compatibility::uint64_t * mtr = reinterpret_cast<kerbal::compatibility::uint64_t *>(mt);

				kerbal::utility::ignore_unused(mtr);

#		if 0
				// pass
#		elif __AVX512F__
				avx512f::mt_twist<N, M, R, A>(mtr);
#		elif __AVX2__
				avx2::mt_twist<N, M, R, A>(mtr);
#		elif __SSE2__
				sse2::mt_twist<N, M, R, A>(mtr);
#		elif __ARM_FEATURE_SVE
				sve::mt_twist<N, M, R, A>(mtr);
#		elif __ARM_NEON
				neon::mt_twist<N, M, R, A>(mtr);
#		else
				plain::mt_twist<kerbal::compatibility::uint64_t, N, M, R, A>(mt);
#		endif
			}

			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A, std::size_t Size>
			KERBAL_CONSTEXPR14
			void mt_twist_fix_integer_simd_dispatch(
				UIntType mt[N],
				kerbal::type_traits::integral_constant<std::size_t, Size>
			) KERBAL_NOEXCEPT
			{
				plain::mt_twist<UIntType, N, M, R, A>(mt);
			}

#endif // KERBAL_RANDOM_ENABLE_MT_TWIST_IE_OPTIMISE


			template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
			class mt_twist_helper
			{
				protected:
					typedef UIntType result_type;


#if KERBAL_RANDOM_ENABLE_MT_TWIST_IE_OPTIMISE

					static void fix_integer_type_dispatch(UIntType mt[N]) KERBAL_NOEXCEPT
					{
						mt_twist_fix_integer_simd_dispatch<UIntType, N, M, R, A>(
							mt,
							kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(UIntType)>()
						);
					}

					KERBAL_CONSTEXPR14
					static void is_constant_evaluated_handler(UIntType mt[N]) KERBAL_NOEXCEPT
					{

#	if __cplusplus >= 201402L

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						KERBAL_IS_CONSTANT_EVALUATED() ?
							plain::mt_twist<UIntType, N, M, R, A>(mt) :
							fix_integer_type_dispatch(mt);
#		else
						plain::mt_twist<UIntType, N, M, R, A>(mt);
#		endif

#	else
						fix_integer_type_dispatch(mt);
#	endif

					}

#endif


					KERBAL_CONSTEXPR14
					static void twist(result_type mt[N]) KERBAL_NOEXCEPT
					{
#if KERBAL_RANDOM_ENABLE_MT_TWIST_IE_OPTIMISE
						is_constant_evaluated_handler(mt);
#else
						plain::mt_twist<result_type, N, M, R, A>(mt);
#endif
					}

			};

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_HELPER_HPP
