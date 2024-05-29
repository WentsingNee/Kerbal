/**
 * @file       countr_zero.gnu_builtin.part.hpp
 * @brief
 * @date       2023-09-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_DETAIL_COUNTR_ZERO_COUNTR_ZERO_GNU_BUILTIN_PART_HPP
#define KERBAL_NUMERIC_BIT_DETAIL_COUNTR_ZERO_COUNTR_ZERO_GNU_BUILTIN_PART_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <kerbal/numeric/bit/detail/countr_zero/countr_zero.bsearch.part.hpp>

#include <climits>
#include <cstddef>


#ifndef KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZERO

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_VERSION_MEETS(4, 8, 0)
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
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZERO 1
#	else
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZERO 0
#	endif

#endif



#ifndef KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZEROL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_VERSION_MEETS(4, 8, 0)
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
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZEROL 1
#	else
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZEROL 0
#	endif

#endif



#ifndef KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZEROLL

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_VERSION_MEETS(4, 8, 0)
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
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZEROLL 1
#	else
#		define KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZEROLL 0
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
				int countr_zero(Unsigned x) KERBAL_NOEXCEPT
				{
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "x should be unsigned");
					return kerbal::numeric::detail::bsearch::countr_zero(x);
				}

#	if KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZERO

				KERBAL_CONSTEXPR
				inline
				int countr_zero(unsigned int x) KERBAL_NOEXCEPT
				{
					return
						x == 0 ?
						sizeof(unsigned int) * CHAR_BIT :
						KERBAL_BUILTIN_COUNTR_ZERO(x)
					;
				}

				KERBAL_CONSTEXPR
				inline
				int countr_zero(unsigned short x) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned short)> S;
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
					KERBAL_STATIC_ASSERT(S::value <= I::value, "digits of unsigned short type is greater than that of unsigned int type");
					return
						S::value == I::value ?
						KERBAL_BUILTIN_COUNTR_ZERO(x) :
						KERBAL_BUILTIN_COUNTR_ZERO(
							(static_cast<unsigned int>(1u) << S::value) | static_cast<unsigned int>(x)
						)
					;
				}

				KERBAL_CONSTEXPR
				inline
				int countr_zero(unsigned char x) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned char)> C;
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
					KERBAL_STATIC_ASSERT(C::value <= I::value, "digits of unsigned char type is greater than that of unsigned int type");
					return
						C::value == I::value ?
						KERBAL_BUILTIN_COUNTR_ZERO(x) :
						KERBAL_BUILTIN_COUNTR_ZERO(
							(static_cast<unsigned int>(1u) << C::value) | static_cast<unsigned int>(x)
						)
					;
				}

#	endif

#	if KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZEROL

				KERBAL_CONSTEXPR
				inline
				int countr_zero(unsigned long x) KERBAL_NOEXCEPT
				{
					return
						x == 0 ?
						sizeof(unsigned long) * CHAR_BIT :
						KERBAL_BUILTIN_COUNTR_ZEROL(x)
					;
				}

#	endif

#	if KERBAL_PRIVATE_HAS_BUILTIN_COUNTR_ZEROLL

				KERBAL_CONSTEXPR
				inline
				int countr_zero(unsigned long long x) KERBAL_NOEXCEPT
				{
					return
						x == 0 ?
						sizeof(unsigned long long) * CHAR_BIT :
						KERBAL_BUILTIN_COUNTR_ZEROLL(x)
					;
				}

#	endif

			} // namespace gnu_builtin

		} // namespace detail

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_DETAIL_COUNTR_ZERO_COUNTR_ZERO_GNU_BUILTIN_PART_HPP
