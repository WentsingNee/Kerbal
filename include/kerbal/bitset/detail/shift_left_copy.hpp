/**
 * @file       shift_left_copy.hpp
 * @brief
 * @date       2022-11-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_SHIFT_LEFT_COPY_HPP
#define KERBAL_BITSET_DETAIL_SHIFT_LEFT_COPY_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/ignore_unused.hpp>

#include <cstddef>
#include <climits>

#include <kerbal/bitset/detail/shift_left_copy/shift_left_copy.plain.hpp>


#ifndef KERBAL_BITSET_ENABLE_SHIFT_LEFT_COPY_IE_OPTIMISE

#	if __AVX512F__ || __AVX2__ || __SSE4_1__ || __ARM_FEATURE_SVE || __ARM_NEON
#		define KERBAL_BITSET_ENABLE_SHIFT_LEFT_COPY_IE_OPTIMISE 1
#	else
#		define KERBAL_BITSET_ENABLE_SHIFT_LEFT_COPY_IE_OPTIMISE 0
#	endif

#endif


#if KERBAL_BITSET_ENABLE_SHIFT_LEFT_COPY_IE_OPTIMISE

//#	if __AVX512F__
//#		include <kerbal/bitset/detail/shift_left_copy/shift_left_copy.avx512f.hpp>
//#	endif

#	if __AVX2__
#		include <kerbal/bitset/detail/shift_left_copy/shift_left_copy.avx2.hpp>
#	endif

//#	if __SSE4_1__
//#		include <kerbal/bitset/detail/shift_left_copy/shift_left_copy.sse41.hpp>
//#	endif
//
//#	if __ARM_FEATURE_SVE
//#		include <kerbal/bitset/detail/shift_left_copy/shift_left_copy.sve.hpp>
//#	endif
//
//#	if __ARM_NEON
//#		include <kerbal/bitset/detail/shift_left_copy/shift_left_copy.neon.hpp>
//#	endif

#endif

#undef EACH


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

#if KERBAL_BITSET_ENABLE_SHIFT_LEFT_COPY_IE_OPTIMISE

			template <typename BlockType>
			void shift_left_copy_fix_integer_simd_dispatch(const BlockType block[], std::size_t n, std::size_t inner_ofs, BlockType out[], kerbal::type_traits::integral_constant<std::size_t, 32>) KERBAL_NOEXCEPT
			{
				const kerbal::compatibility::uint32_t * blockr = reinterpret_cast<const kerbal::compatibility::uint32_t *>(block);
				kerbal::compatibility::uint32_t * outr = reinterpret_cast<kerbal::compatibility::uint32_t *>(out);

				kerbal::utility::ignore_unused(blockr);
				kerbal::utility::ignore_unused(outr);

#		if 0
				// pass
//#		elif __AVX512F__
//				avx512f::shift_left_copy(blockr, n, inner_ofs, outr);
//#		elif __AVX2__
//				avx2::shift_left_copy(blockr, n, inner_ofs, outr);
//#		elif __SSE4_1__
//				sse2::shift_left_copy(blockr, n, inner_ofs, outr);
//#		elif __ARM_FEATURE_SVE
//				sve::shift_left_copy(blockr, n, inner_ofs, outr);
//#		elif __ARM_NEON
//				neon::shift_left_copy(blockr, n, inner_ofs, outr);
#		else
				plain::shift_left_copy(block, n, inner_ofs, out);
#		endif
			}

			template <typename BlockType>
			void shift_left_copy_fix_integer_simd_dispatch(const BlockType block[], std::size_t n, std::size_t inner_ofs, BlockType out[], kerbal::type_traits::integral_constant<std::size_t, 64>) KERBAL_NOEXCEPT
			{
				const kerbal::compatibility::uint64_t * blockr = reinterpret_cast<const kerbal::compatibility::uint64_t *>(block);
				kerbal::compatibility::uint64_t * outr = reinterpret_cast<kerbal::compatibility::uint64_t *>(out);

				kerbal::utility::ignore_unused(blockr);
				kerbal::utility::ignore_unused(outr);

#		if 0
				// pass
//#		eliif __AVX512F__
//				avx512f::shift_left_copy(reinterpret_cast<const kerbal::compatibility::uint64_t *>(block), n, inner_ofs, reinterpret_cast<const kerbal::compatibility::uint64_t *>(out));
#		elif __AVX2__
				avx2::shift_left_copy(blockr, n, inner_ofs, outr);
//#		elif __SSE4_1__
//				sse2::shift_left_copy(blockr, n, inner_ofs, outr);
//#		elif __ARM_FEATURE_SVE
//				sve::shift_left_copy(blockr, n, inner_ofs, outr);
//#		elif __ARM_NEON
//				neon::shift_left_copy(blockr, n, inner_ofs, outr);
#		else
				plain::shift_left_copy(blockr, n, inner_ofs, outr);
#		endif
			}

			template <typename BlockType, std::size_t Size>
			KERBAL_CONSTEXPR14
			void shift_left_copy_fix_integer_simd_dispatch(const BlockType block[], std::size_t n, std::size_t inner_ofs, BlockType out[], kerbal::type_traits::integral_constant<std::size_t, Size>) KERBAL_NOEXCEPT
			{
				plain::shift_left_copy<BlockType>(block, n, inner_ofs, out);
			}

#endif // KERBAL_BITSET_ENABLE_SHIFT_LEFT_COPY_IE_OPTIMISE


			template <typename BlockType>
			class shift_left_copy_helper
			{
				protected:

#if KERBAL_BITSET_ENABLE_SHIFT_LEFT_COPY_IE_OPTIMISE

					static void fix_integer_type_dispatch(const BlockType block[], std::size_t n, std::size_t inner_ofs, BlockType out[]) KERBAL_NOEXCEPT
					{
						shift_left_copy_fix_integer_simd_dispatch<BlockType>(block, n, inner_ofs, out, kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(BlockType)>());
					}

					KERBAL_CONSTEXPR14
					static void is_constant_evaluated_handler(const BlockType block[], std::size_t n, std::size_t inner_ofs, BlockType out[]) KERBAL_NOEXCEPT
					{

#	if __cplusplus >= 201402L

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						KERBAL_IS_CONSTANT_EVALUATED() ?
								plain::shift_left_copy<BlockType>(block, n, inner_ofs, out) :
								fix_integer_type_dispatch(block, n, inner_ofs, out);
#		else
						plain::shift_left_copy<BlockType>(block, n, inner_ofs, out);
#		endif

#	else
						fix_integer_type_dispatch(block, n, inner_ofs, out);
#	endif

					}

#endif


					KERBAL_CONSTEXPR14
					static void shift_left_copy(const BlockType block[], std::size_t n, std::size_t inner_ofs, BlockType out[]) KERBAL_NOEXCEPT
					{
#if KERBAL_BITSET_ENABLE_SHIFT_LEFT_COPY_IE_OPTIMISE
						is_constant_evaluated_handler(block, n, inner_ofs, out);
#else
						plain::shift_left_copy(block, n, inner_ofs, out);
#endif
					}

			};

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_SHIFT_LEFT_COPY_HPP
