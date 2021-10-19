/**
 * @file       countr_zero.hpp
 * @brief
 * @date       2021-10-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_COUNTR_ZERO_HPP
#define KERBAL_NUMERIC_BIT_COUNTR_ZERO_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>


#ifndef KERBAL_HAS_BUILTIN_COUNTR_ZERO

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_ctz)
#			define KERBAL_BUILTIN_COUNTR_ZERO(x) __builtin_ctz(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_ctz)
#			define KERBAL_BUILTIN_COUNTR_ZERO(x) __builtin_ctz(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_ctz)
#			define KERBAL_BUILTIN_COUNTR_ZERO(x) __builtin_ctz(x)
#		endif
#	endif

#	if defined(KERBAL_BUILTIN_COUNTR_ZERO)
#		define KERBAL_HAS_BUILTIN_COUNTR_ZERO 1
#	else
#		define KERBAL_HAS_BUILTIN_COUNTR_ZERO 0
#	endif

#endif



#ifndef KERBAL_HAS_BUILTIN_COUNTR_ZEROL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_ctzl)
#			define KERBAL_BUILTIN_COUNTR_ZEROL(x) __builtin_ctzl(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_ctzl)
#			define KERBAL_BUILTIN_COUNTR_ZEROL(x) __builtin_ctzl(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_ctzl)
#			define KERBAL_BUILTIN_COUNTR_ZEROL(x) __builtin_ctzl(x)
#		endif
#	endif

#	if defined(KERBAL_BUILTIN_COUNTR_ZEROL)
#		define KERBAL_HAS_BUILTIN_COUNTR_ZEROL 1
#	else
#		define KERBAL_HAS_BUILTIN_COUNTR_ZEROL 0
#	endif

#endif



#ifndef KERBAL_HAS_BUILTIN_COUNTR_ZEROLL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_ctzll)
#			define KERBAL_BUILTIN_COUNTR_ZEROLL(x) __builtin_ctzll(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_ctzll)
#			define KERBAL_BUILTIN_COUNTR_ZEROLL(x) __builtin_ctzll(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_ctzll)
#			define KERBAL_BUILTIN_COUNTR_ZEROLL(x) __builtin_ctzll(x)
#		endif
#	endif

#	if defined(KERBAL_BUILTIN_COUNTR_ZEROLL)
#		define KERBAL_HAS_BUILTIN_COUNTR_ZEROLL 1
#	else
#		define KERBAL_HAS_BUILTIN_COUNTR_ZEROLL 0
#	endif

#endif


#if CHAR_BIT == 8
#	include <kerbal/numeric/bit/detail/single_bit_bsearch.hpp>
#endif


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int countr_zero_plain(Unsigned x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<int, CHAR_BIT * sizeof(x)> DIGIT;
				int i = 0;
				while (i < DIGIT::value) {
					if (x % 2 == 1) {
						break;
					}
					x >>= 1;
					++i;
				}
				return i;
			}


#	if CHAR_BIT != 8

			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int countr_zero_impl(Unsigned x) KERBAL_NOEXCEPT
			{
				return countr_zero_plain(x);
			}

#	else

			template <typename Unsigned>
			KERBAL_CONSTEXPR
			typename kerbal::type_traits::enable_if<
					single_bit_bsearch_depth<CHAR_BIT * sizeof(Unsigned)>::value != -1,
					int
			>::type
			countr_zero_impl(Unsigned x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(Unsigned)> DIGIT;
				typedef single_bit_bsearch_depth<DIGIT::value> N;
				return single_bit_bsearch<Unsigned, N::value - 1>::f(x & (-x));
			}

			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			typename kerbal::type_traits::enable_if<
					single_bit_bsearch_depth<CHAR_BIT * sizeof(Unsigned)>::value == -1,
					int
			>::type
			countr_zero_impl(Unsigned x) KERBAL_NOEXCEPT
			{
				return countr_zero_plain(x);
			}

#	endif



			template <typename Unsigned>
			KERBAL_CONSTEXPR
			int countr_zero_builtin_handler(Unsigned x) KERBAL_NOEXCEPT
			{
				return countr_zero_impl(x);
			}

#	if KERBAL_HAS_BUILTIN_COUNTR_ZERO

			KERBAL_CONSTEXPR
			inline
			int countr_zero_builtin_handler(unsigned int x) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_COUNTR_ZERO(x);
			}

			KERBAL_CONSTEXPR
			inline
			int countr_zero_builtin_handler(unsigned short x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned short)> S;
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
				KERBAL_STATIC_ASSERT(S::value <= I::value, "digits of unsigned short type is greater than that of unsigned int type");
				return S::value == I::value ?
						KERBAL_BUILTIN_COUNTR_ZERO(x) :
						KERBAL_BUILTIN_COUNTR_ZERO(static_cast<unsigned int>(1u) << S::value | static_cast<unsigned int>(x));
			}

			KERBAL_CONSTEXPR
			inline
			int countr_zero_builtin_handler(unsigned char x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned char)> C;
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
				KERBAL_STATIC_ASSERT(C::value <= I::value, "digits of unsigned char type is greater than that of unsigned int type");
				return C::value == I::value ?
						KERBAL_BUILTIN_COUNTR_ZERO(x) :
						KERBAL_BUILTIN_COUNTR_ZERO(static_cast<unsigned int>(1u) << C::value | static_cast<unsigned int>(x));
			 }

#	endif

#	if KERBAL_HAS_BUILTIN_COUNTR_ZEROL

			KERBAL_CONSTEXPR
			inline
			int countr_zero_builtin_handler(unsigned long x) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_COUNTR_ZEROL(x);
			}

#	endif

#	if KERBAL_HAS_BUILTIN_COUNTR_ZEROLL

			KERBAL_CONSTEXPR
			inline
			int countr_zero_builtin_handler(unsigned long long x) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_COUNTR_ZEROLL(x);
			}

#	endif


			template <typename Unsigned>
			KERBAL_CONSTEXPR
			int countr_zero_sign_handler(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return countr_zero_builtin_handler(x);
			}

			template <typename Signed>
			KERBAL_CONSTEXPR
			int countr_zero_sign_handler(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
				return countr_zero_sign_handler(static_cast<unsigned_t>(x), kerbal::type_traits::false_type());
			}

		} // namespace detail


		template <typename Tp>
		KERBAL_CONSTEXPR
		int countr_zero(Tp x) KERBAL_NOEXCEPT
		{
			return x == 0 ?
				   sizeof(Tp) * CHAR_BIT :
				   kerbal::numeric::detail::countr_zero_sign_handler(x, kerbal::type_traits::is_signed<Tp>());
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_COUNTR_ZERO_HPP
