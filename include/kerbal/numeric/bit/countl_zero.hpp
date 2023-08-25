/**
 * @file       countl_zero.hpp
 * @brief
 * @date       countl_zero.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_COUNTL_ZERO_HPP
#define KERBAL_NUMERIC_BIT_COUNTL_ZERO_HPP

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


#ifndef KERBAL_HAS_BUILTIN_COUNTL_ZERO

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_clz)
#			define KERBAL_BUILTIN_COUNTL_ZERO(x) __builtin_clz(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_clz)
#			define KERBAL_BUILTIN_COUNTL_ZERO(x) __builtin_clz(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_clz)
#			define KERBAL_BUILTIN_COUNTL_ZERO(x) __builtin_clz(x)
#		endif
#	endif

#	if defined(KERBAL_BUILTIN_COUNTL_ZERO)
#		define KERBAL_HAS_BUILTIN_COUNTL_ZERO 1
#	else
#		define KERBAL_HAS_BUILTIN_COUNTL_ZERO 0
#	endif

#endif



#ifndef KERBAL_HAS_BUILTIN_COUNTL_ZEROL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_clzl)
#			define KERBAL_BUILTIN_COUNTL_ZEROL(x) __builtin_clzl(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_clzl)
#			define KERBAL_BUILTIN_COUNTL_ZEROL(x) __builtin_clzl(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_clzl)
#			define KERBAL_BUILTIN_COUNTL_ZEROL(x) __builtin_clzl(x)
#		endif
#	endif

#	if defined(KERBAL_BUILTIN_COUNTL_ZEROL)
#		define KERBAL_HAS_BUILTIN_COUNTL_ZEROL 1
#	else
#		define KERBAL_HAS_BUILTIN_COUNTL_ZEROL 0
#	endif

#endif



#ifndef KERBAL_HAS_BUILTIN_COUNTL_ZEROLL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_clzll)
#			define KERBAL_BUILTIN_COUNTL_ZEROLL(x) __builtin_clzll(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_clzll)
#			define KERBAL_BUILTIN_COUNTL_ZEROLL(x) __builtin_clzll(x)
#		endif
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_clzll)
#			define KERBAL_BUILTIN_COUNTL_ZEROLL(x) __builtin_clzll(x)
#		endif
#	endif

#	if defined(KERBAL_BUILTIN_COUNTL_ZEROLL)
#		define KERBAL_HAS_BUILTIN_COUNTL_ZEROLL 1
#	else
#		define KERBAL_HAS_BUILTIN_COUNTL_ZEROLL 0
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
			int countl_zero_plain(Unsigned x) KERBAL_NOEXCEPT
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
			int countl_zero_impl(Unsigned x) KERBAL_NOEXCEPT
			{
				return countl_zero_plain(x);
			}

#	else

			template <typename Unsigned>
			KERBAL_CONSTEXPR
			typename kerbal::type_traits::enable_if<
					single_bit_bsearch_depth<CHAR_BIT * sizeof(Unsigned)>::value != -1,
					int
			>::type
			countl_zero_impl(Unsigned x) KERBAL_NOEXCEPT
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
			countl_zero_impl(Unsigned x) KERBAL_NOEXCEPT
			{
				return countl_zero_plain(x);
			}

#	endif



			template <typename Unsigned>
			KERBAL_CONSTEXPR
			int countl_zero_builtin_handler(Unsigned x) KERBAL_NOEXCEPT
			{
				return countl_zero_impl(x);
			}

#	if KERBAL_HAS_BUILTIN_COUNTL_ZERO

			KERBAL_CONSTEXPR
			inline
			int countl_zero_builtin_handler(unsigned int x) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_COUNTL_ZERO(x);
			}

			KERBAL_CONSTEXPR
			inline
			int countl_zero_builtin_handler(unsigned short x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned short)> S;
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
				KERBAL_STATIC_ASSERT(S::value <= I::value, "digits of unsigned short type is greater than that of unsigned int type");
				return S::value == I::value ?
						KERBAL_BUILTIN_COUNTL_ZERO(x) :
						KERBAL_BUILTIN_COUNTL_ZERO(static_cast<unsigned int>(1u) << S::value | static_cast<unsigned int>(x));
			}

			KERBAL_CONSTEXPR
			inline
			int countl_zero_builtin_handler(unsigned char x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned char)> C;
				typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
				KERBAL_STATIC_ASSERT(C::value <= I::value, "digits of unsigned char type is greater than that of unsigned int type");
				return C::value == I::value ?
						KERBAL_BUILTIN_COUNTL_ZERO(x) :
						KERBAL_BUILTIN_COUNTL_ZERO(static_cast<unsigned int>(1u) << C::value | static_cast<unsigned int>(x));
			 }

#	endif

#	if KERBAL_HAS_BUILTIN_COUNTL_ZEROL

			KERBAL_CONSTEXPR
			inline
			int countl_zero_builtin_handler(unsigned long x) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_COUNTL_ZEROL(x);
			}

#	endif

#	if KERBAL_HAS_BUILTIN_COUNTL_ZEROLL

			KERBAL_CONSTEXPR
			inline
			int countl_zero_builtin_handler(unsigned long long x) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_COUNTL_ZEROLL(x);
			}

#	endif


			template <typename Unsigned>
			KERBAL_CONSTEXPR
			int countl_zero_sign_handler(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return countl_zero_builtin_handler(x);
			}

			template <typename Signed>
			KERBAL_CONSTEXPR
			int countl_zero_sign_handler(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
				return countl_zero_sign_handler(static_cast<unsigned_t>(x), kerbal::type_traits::false_type());
			}

		} // namespace detail


		template <typename Tp>
		KERBAL_CONSTEXPR
		int countl_zero(Tp x) KERBAL_NOEXCEPT
		{
			return x == 0 ?
				   sizeof(Tp) * CHAR_BIT :
				   kerbal::numeric::detail::countl_zero_sign_handler(x, kerbal::type_traits::is_signed<Tp>());
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_COUNTL_ZERO_HPP
