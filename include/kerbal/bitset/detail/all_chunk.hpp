/**
 * @file       all_chunk.hpp
 * @brief
 * @date       2022-11-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_ALL_CHUNK_HPP
#define KERBAL_BITSET_DETAIL_ALL_CHUNK_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/ignore_unused.hpp>

#include <cstddef>
#include <climits>

#include <kerbal/bitset/detail/all_chunk/all_chunk.plain.hpp>


#ifndef KERBAL_BITSET_ENABLE_ALL_CHUNK_IE_OPTIMISE

#	if __AVX512F__ || __AVX2__ || __AVX__ || __SSE4_1__ || __ARM_FEATURE_SVE || __ARM_NEON
#		define KERBAL_BITSET_ENABLE_ALL_CHUNK_IE_OPTIMISE 1
#	else
#		define KERBAL_BITSET_ENABLE_ALL_CHUNK_IE_OPTIMISE 0
#	endif

#endif


#if KERBAL_BITSET_ENABLE_ALL_CHUNK_IE_OPTIMISE

#	if __AVX512F__
#		include <kerbal/bitset/detail/all_chunk/all_chunk.avx512f.hpp>
#	endif

#	if __AVX2__
#		include <kerbal/bitset/detail/all_chunk/all_chunk.avx2.hpp>
#	endif

#	if __AVX__
#		include <kerbal/bitset/detail/all_chunk/all_chunk.avx.hpp>
#	endif

#	if __SSE4_1__
#		include <kerbal/bitset/detail/all_chunk/all_chunk.sse41.hpp>
#	endif

#	if __ARM_FEATURE_SVE
#		include <kerbal/bitset/detail/all_chunk/all_chunk.sve.hpp>
#	endif

#	if __ARM_NEON
#		include <kerbal/bitset/detail/all_chunk/all_chunk.neon.hpp>
#	endif

#endif

#undef EACH


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

#if KERBAL_BITSET_ENABLE_ALL_CHUNK_IE_OPTIMISE

			template <typename BlockType>
			bool all_chunk_fix_integer_simd_dispatch(const BlockType block[], std::size_t n, kerbal::type_traits::integral_constant<std::size_t, 32>) KERBAL_NOEXCEPT
			{
				const kerbal::compatibility::uint32_t * blockr = reinterpret_cast<const kerbal::compatibility::uint32_t *>(block);

				kerbal::utility::ignore_unused(blockr);

#		if 0
				// pass
#		elif __AVX512F__
				return avx512f::all_chunk(blockr, n);
#		elif __AVX2__
				return avx2::all_chunk(blockr, n);
#		elif __AVX__
				return avx::all_chunk(blockr, n);
#		elif __SSE4_1__
				return sse41::all_chunk(blockr, n);
#		elif __ARM_FEATURE_SVE
				return sve::all_chunk(blockr, n);
#		elif __ARM_NEON
				return neon::all_chunk(blockr, n);
#		else
				return plain::all_chunk<BlockType>(block, n);
#		endif
			}

			template <typename BlockType>
			bool all_chunk_fix_integer_simd_dispatch(const BlockType block[], std::size_t n, kerbal::type_traits::integral_constant<std::size_t, 64>) KERBAL_NOEXCEPT
			{
				const kerbal::compatibility::uint64_t * blockr = reinterpret_cast<const kerbal::compatibility::uint64_t *>(block);

				kerbal::utility::ignore_unused(blockr);

#		if 0
				// pass
#		elif __AVX512F__
				return avx512f::all_chunk(blockr, n);
#		elif __AVX2__
				return avx2::all_chunk(blockr, n);
#		elif __AVX__
				return avx::all_chunk(blockr, n);
#		elif __SSE4_1__
				return sse41::all_chunk(blockr, n);
#		elif __ARM_FEATURE_SVE
				return sve::all_chunk(blockr, n);
#		elif __ARM_NEON
				return neon::all_chunk(blockr, n);
#		else
				return plain::all_chunk<BlockType>(block, n);
#		endif
			}

			template <typename BlockType, std::size_t Size>
			KERBAL_CONSTEXPR14
			bool all_chunk_fix_integer_simd_dispatch(const BlockType block[], std::size_t n, kerbal::type_traits::integral_constant<std::size_t, Size>) KERBAL_NOEXCEPT
			{
				return plain::all_chunk<BlockType>(block, n);
			}

#endif // KERBAL_BITSET_ENABLE_ALL_CHUNK_IE_OPTIMISE


			template <typename BlockType>
			class all_chunk_helper
			{
				protected:

#if KERBAL_BITSET_ENABLE_ALL_CHUNK_IE_OPTIMISE

					static bool fix_integer_type_dispatch(const BlockType block[], std::size_t n) KERBAL_NOEXCEPT
					{
						return all_chunk_fix_integer_simd_dispatch<BlockType>(block, n, kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(BlockType)>());
					}

					KERBAL_CONSTEXPR14
					static bool is_constant_evaluated_handler(const BlockType block[], std::size_t n) KERBAL_NOEXCEPT
					{

#	if __cplusplus >= 201402L

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						return KERBAL_IS_CONSTANT_EVALUATED() ?
								plain::all_chunk<BlockType>(block, n) :
								fix_integer_type_dispatch(block, n);
#		else
						return plain::all_chunk<BlockType>(block, n);
#		endif

#	else
						return fix_integer_type_dispatch(block, n);
#	endif

					}

#endif


					KERBAL_CONSTEXPR14
					static bool all_chunk(const BlockType block[], std::size_t n) KERBAL_NOEXCEPT
					{
#if KERBAL_BITSET_ENABLE_ALL_CHUNK_IE_OPTIMISE
						return is_constant_evaluated_handler(block, n);
#else
						return plain::all_chunk(block, n);
#endif
					}

			};

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_ALL_CHUNK_HPP
