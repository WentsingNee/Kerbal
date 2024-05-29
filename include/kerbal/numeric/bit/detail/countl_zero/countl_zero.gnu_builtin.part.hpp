/**
 * @file       countl_zero.gnu_builtin.part.hpp
 * @brief
 * @date       2024-04-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_DETAIL_COUNTL_ZERO_COUNTL_ZERO_GNU_BUILTIN_PART_HPP
#define KERBAL_NUMERIC_BIT_DETAIL_COUNTL_ZERO_COUNTL_ZERO_GNU_BUILTIN_PART_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <kerbal/numeric/bit/detail/countl_zero/countl_zero.plain.part.hpp>

#include <climits>
#include <cstddef>


#ifndef KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZERO

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_VERSION_MEETS(4, 8, 0)
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
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZERO 1
#	else
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZERO 0
#	endif

#endif



#ifndef KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZEROL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_VERSION_MEETS(4, 8, 0)
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
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZEROL 1
#	else
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZEROL 0
#	endif

#endif



#ifndef KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZEROLL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_VERSION_MEETS(4, 8, 0)
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
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZEROLL 1
#	else
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZEROLL 0
#	endif

#endif


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace gnu_builtin
			{

				template <typename Unsigned>
				KERBAL_CONSTEXPR
				int countl_zero(Unsigned x) KERBAL_NOEXCEPT
				{
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "x should be unsigned");
					return kerbal::numeric::detail::plain::countl_zero(x);
				}

#	if KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZERO

				KERBAL_CONSTEXPR
				inline
				int countl_zero(unsigned int x) KERBAL_NOEXCEPT
				{
					return
						x == 0 ?
						sizeof(unsigned int) * CHAR_BIT :
						KERBAL_BUILTIN_COUNTL_ZERO(x)
					;
				}

				KERBAL_CONSTEXPR
				inline
				int countl_zero(unsigned short x) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned short)> S;
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
					typedef kerbal::type_traits::integral_constant<std::size_t, I::value - S::value> SHIFT;
					KERBAL_STATIC_ASSERT(S::value <= I::value, "digits of unsigned short type is greater than that of unsigned int type");
					return
						S::value == I::value ?
						KERBAL_BUILTIN_COUNTL_ZERO(x) :
						KERBAL_BUILTIN_COUNTL_ZERO(
							(
								(static_cast<unsigned int>(1u) << SHIFT::value) - 1
							) | (
								static_cast<unsigned int>(x) << SHIFT::value
							)
						)
					;
				}

				KERBAL_CONSTEXPR
				inline
				int countl_zero(unsigned char x) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned char)> C;
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
					typedef kerbal::type_traits::integral_constant<std::size_t, I::value - C::value> SHIFT;
					KERBAL_STATIC_ASSERT(C::value <= I::value, "digits of unsigned char type is greater than that of unsigned int type");
					return
						C::value == I::value ?
						KERBAL_BUILTIN_COUNTL_ZERO(x) :
						KERBAL_BUILTIN_COUNTL_ZERO(
							(
								(static_cast<unsigned int>(1u) << SHIFT::value) - 1
							) | (
								static_cast<unsigned int>(x) << SHIFT::value
							)
						)
					;
				}

#	endif

#	if KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZEROL

				KERBAL_CONSTEXPR
				inline
				int countl_zero(unsigned long x) KERBAL_NOEXCEPT
				{
					return
						x == 0 ?
						sizeof(unsigned long) * CHAR_BIT :
						KERBAL_BUILTIN_COUNTL_ZEROL(x)
					;
				}

#	endif

#	if KERBAL_PRIVATE_HAS_BUILTIN_COUNTL_ZEROLL

				KERBAL_CONSTEXPR
				inline
				int countl_zero(unsigned long long x) KERBAL_NOEXCEPT
				{
					return
						x == 0 ?
						sizeof(unsigned long long) * CHAR_BIT :
						KERBAL_BUILTIN_COUNTL_ZEROLL(x)
					;
				}

#	endif

			} // namespace gnu_builtin

		} // namespace detail

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_DETAIL_COUNTL_ZERO_COUNTL_ZERO_GNU_BUILTIN_PART_HPP
