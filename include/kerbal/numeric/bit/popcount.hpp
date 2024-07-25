/**
 * @file       popcount.hpp
 * @brief
 * @date       2021-07-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_POPCOUNT_HPP
#define KERBAL_NUMERIC_BIT_POPCOUNT_HPP

#include <kerbal/config/architecture.hpp>
#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/numeric/bit/repeat_byte.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>
#include <cstddef>


#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#	if (KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_X86 && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_AMD64)
#		define KERBAL_GNU_TRY_BUILTIN_POPCOUNT_INTRINSICS 1
#	elif defined(__POPCNT__)
#		define KERBAL_GNU_TRY_BUILTIN_POPCOUNT_INTRINSICS 1
#	endif
#endif


#ifndef KERBAL_HAS_BUILTIN_POPCOUNT

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_TRY_BUILTIN_POPCOUNT_INTRINSICS
#			if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_popcount)
#				define KERBAL_BUILTIN_POPCOUNT(x) __builtin_popcount(x)
#			endif
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_popcount)
#			define KERBAL_BUILTIN_POPCOUNT(x) __builtin_popcount(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_popcount)
#			define KERBAL_BUILTIN_POPCOUNT(x) __builtin_popcount(x)
#		endif
#	endif

#	if defined(KERBAL_BUILTIN_POPCOUNT)
#		define KERBAL_HAS_BUILTIN_POPCOUNT 1
#	else
#		define KERBAL_HAS_BUILTIN_POPCOUNT 0
#	endif

#endif



#ifndef KERBAL_HAS_BUILTIN_POPCOUNTL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_TRY_BUILTIN_POPCOUNT_INTRINSICS
#			if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_popcountl)
#				define KERBAL_BUILTIN_POPCOUNTL(x) __builtin_popcountl(x)
#			endif
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_popcountl)
#			define KERBAL_BUILTIN_POPCOUNTL(x) __builtin_popcountl(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_popcountl)
#			define KERBAL_BUILTIN_POPCOUNTL(x) __builtin_popcountl(x)
#		endif
#	endif

#	if defined(KERBAL_BUILTIN_POPCOUNTL)
#		define KERBAL_HAS_BUILTIN_POPCOUNTL 1
#	else
#		define KERBAL_HAS_BUILTIN_POPCOUNTL 0
#	endif

#endif



#ifndef KERBAL_HAS_BUILTIN_POPCOUNTLL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_TRY_BUILTIN_POPCOUNT_INTRINSICS
#			if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_popcountll)
#				define KERBAL_BUILTIN_POPCOUNTLL(x) __builtin_popcountll(x)
#			endif
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_popcountll)
#			define KERBAL_BUILTIN_POPCOUNTLL(x) __builtin_popcountll(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_popcountll)
#			define KERBAL_BUILTIN_POPCOUNTLL(x) __builtin_popcountll(x)
#		endif
#	endif

#	if defined(KERBAL_BUILTIN_POPCOUNTLL)
#		define KERBAL_HAS_BUILTIN_POPCOUNTLL 1
#	else
#		define KERBAL_HAS_BUILTIN_POPCOUNTLL 0
#	endif

#endif



#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#	if KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_X86 || KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_AMD64
#		include <nmmintrin.h>
#		define KERBAL_X86_POPCNTU32_INTRINSIC 1
#		if KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_AMD64
#			define KERBAL_X86_POPCNTU64_INTRINSIC 1
#		endif
#	endif
#endif


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int k_popcount_plain(Unsigned x) KERBAL_NOEXCEPT
			{
				int cnt = 0;
				while (x) {
					x &= x - 1;
					++cnt;
				}
				return cnt;
			}

#	if CHAR_BIT != 8

			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int k_basic_popcount(Unsigned x) KERBAL_NOEXCEPT
			{
				return k_popcount_plain(x);
			}

#	else

			// optimized-swar algorithm
			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int k_basic_popcount(Unsigned x) KERBAL_NOEXCEPT
			{
				typedef kerbal::numeric::repeat_byte<Unsigned, 0x55> _0x5555;
				typedef kerbal::numeric::repeat_byte<Unsigned, 0x33> _0x3333;
				typedef kerbal::numeric::repeat_byte<Unsigned, 0x0f> _0x0f0f;
				typedef kerbal::numeric::repeat_byte<Unsigned, 0x01> _0x0101;

				x = x - ((x >> 1) & _0x5555::value);
				// x = (x & _0x5555::value) + ((x >> 1) & _0x5555::value);

				x = (x & _0x3333::value) + ((x >> 2) & _0x3333::value);

				x = ((x >> 4) + x) & _0x0f0f::value;
				// x = (x & _0x0f0f::value) + ((x >> 4) & _0x0f0f::value);

				x = static_cast<Unsigned>(x * _0x0101::value) >> (8 * (sizeof(Unsigned) - 1));
				return static_cast<int>(x);
			}

#	endif



			//==== popcount intrinsic aspect

			template <typename Unsigned, std::size_t BitWidth>
			KERBAL_CONSTEXPR14
			int k_popcount_intrinsic_aspect(Unsigned x, kerbal::type_traits::integral_constant<std::size_t, BitWidth>) KERBAL_NOEXCEPT
			{
				return k_basic_popcount(x);
			}


#	if KERBAL_X86_POPCNTU32_INTRINSIC

			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int k_popcount_intrinsic_aspect(Unsigned x, kerbal::type_traits::integral_constant<std::size_t, 32>) KERBAL_NOEXCEPT
			{
#		if __cplusplus >= 201402L
#			if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				return KERBAL_IS_CONSTANT_EVALUATED() ? k_basic_popcount(x) : _mm_popcnt_u32(x);
#			else
				return k_basic_popcount(x);
#			endif
#		else
				return _mm_popcnt_u32(x);
#		endif
			}

#	endif


#	if KERBAL_X86_POPCNTU64_INTRINSIC

			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int k_popcount_intrinsic_aspect(Unsigned x, kerbal::type_traits::integral_constant<std::size_t, 64>) KERBAL_NOEXCEPT
			{
#		if __cplusplus >= 201402L
#			if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				return KERBAL_IS_CONSTANT_EVALUATED() ? k_basic_popcount(x) : static_cast<int>(_mm_popcnt_u64(x));
#			else
				return k_basic_popcount(x);
#			endif
#		else
				return _mm_popcnt_u64(x);
#		endif
			}

#	endif



			//==== popcount builtin aspect

			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int k_popcount_builtin_aspect(Unsigned x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(Unsigned)> BIT_WIDTH;
				return k_popcount_intrinsic_aspect(x, BIT_WIDTH());
			}


#	if KERBAL_HAS_BUILTIN_POPCOUNT

			KERBAL_CONSTEXPR
			inline
			int k_popcount_builtin_aspect(unsigned int x) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_POPCOUNT(x);
			}

#	endif


#	if KERBAL_HAS_BUILTIN_POPCOUNTL

			KERBAL_CONSTEXPR
			inline
			int k_popcount_builtin_aspect(unsigned long x) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_POPCOUNTL(x);
			}

#	endif


#	if KERBAL_HAS_BUILTIN_POPCOUNTLL

			KERBAL_CONSTEXPR
			inline
			int k_popcount_builtin_aspect(unsigned long long x) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_POPCOUNTLL(x);
			}

#	endif


			//==== popcount sign aspect

			template <typename Unsigned>
			KERBAL_CONSTEXPR
			int k_popcount_sign_aspect(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return k_popcount_builtin_aspect(x);
			}

			template <typename Signed>
			KERBAL_CONSTEXPR
			int k_popcount_sign_aspect(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
				return k_popcount_sign_aspect(static_cast<unsigned_t>(x), kerbal::type_traits::false_type());
			}

		} // namespace detail

		/**
		 * Counts the number of 1 bits in the value of x.
		 */
		template <typename T>
		KERBAL_CONSTEXPR
		int popcount(T x) KERBAL_NOEXCEPT
		{
			return kerbal::numeric::detail::k_popcount_sign_aspect(x, kerbal::type_traits::is_signed<T>());
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_POPCOUNT_HPP
