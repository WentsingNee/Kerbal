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

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>


namespace kerbal
{

	namespace numeric
	{

# if CHAR_BIT != 8

		template <typename Unsigned>
		KERBAL_CONSTEXPR14
		int __popcount(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			int cnt = 0;
			while (x) {
				x &= x - 1;
				++cnt;
			}
			return cnt;
		}

# else

		namespace detail
		{

			template <typename T, int W>
			struct _0x3333_loop;

			template <typename T>
			struct _0x3333_loop<T, 1> :
					public kerbal::type_traits::integral_constant<T, 0x33>
			{
			};

			template <typename T, int W>
			struct _0x3333_loop :
					public kerbal::type_traits::integral_constant<
							T,
							_0x3333_loop<T, W - 1>::value + (static_cast<T>(0x33) << (W - 1) * 8)
					>
			{
			};

			template <typename T>
			struct _0x3333 :
					public _0x3333_loop<T, sizeof(T)>
			{
			};


			template <typename T, int W>
			struct _0x5555_loop;

			template <typename T>
			struct _0x5555_loop<T, 1> :
					public kerbal::type_traits::integral_constant<T, 0x55>
			{
			};

			template <typename T, int W>
			struct _0x5555_loop :
					public kerbal::type_traits::integral_constant<
							T,
							_0x5555_loop<T, W - 1>::value + (static_cast<T>(0x55) << (W - 1) * 8)
					>
			{
			};

			template <typename T>
			struct _0x5555 :
					public _0x5555_loop<T, sizeof(T)>
			{
			};


			template <typename T, int W>
			struct _0x0f0f_loop;

			template <typename T>
			struct _0x0f0f_loop<T, 1> :
					public kerbal::type_traits::integral_constant<T, 0x0f>
			{
			};

			template <typename T, int W>
			struct _0x0f0f_loop :
					public kerbal::type_traits::integral_constant<
							T,
							_0x0f0f_loop<T, W - 1>::value + (static_cast<T>(0xf) << (W - 1) * 8)
					>
			{
			};

			template <typename T>
			struct _0x0f0f :
					public _0x0f0f_loop<T, sizeof(T)>
			{
			};


			template <typename T, int W>
			struct _0x0101_loop;

			template <typename T>
			struct _0x0101_loop<T, 1> :
					public kerbal::type_traits::integral_constant<T, 0x01>
			{
			};

			template <typename T, int W>
			struct _0x0101_loop :
					public kerbal::type_traits::integral_constant<
							T,
							_0x0101_loop<T, W - 1>::value + (static_cast<T>(1) << (W - 1) * 8)
					>
			{
			};

			template <typename T>
			struct _0x0101 :
					public _0x0101_loop<T, sizeof(T)>
			{
			};

		} // namespace detail


		// optimized-swar algorithm
		template <typename Unsigned>
		KERBAL_CONSTEXPR14
		int __popcount(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			x = x - ((x >> 1) & detail::_0x5555<Unsigned>::value);
			// x = (x & detail::_0x5555<Unsigned>::value) + ((x >> 1) & detail::_0x5555<Unsigned>::value);

			x = (x & detail::_0x3333<Unsigned>::value) + ((x >> 2) & detail::_0x3333<Unsigned>::value);

			x = ((x >> 4) + x) & detail::_0x0f0f<Unsigned>::value;
			// x = (x & detail::_0x0f0f<Unsigned>::value) + ((x >> 4) & detail::_0x0f0f<Unsigned>::value);

			x = static_cast<Unsigned>(x * detail::_0x0101<Unsigned>::value) >> (8 * (sizeof(Unsigned) - 1));
			return x;
		}


#endif


#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_popcount)
#			define KERBAL_BUILTIN_POPCOUNT(x) __builtin_popcount(x)
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


#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_popcountl)
#			define KERBAL_BUILTIN_POPCOUNTL(x) __builtin_popcountl(x)
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


#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_popcountll)
#			define KERBAL_BUILTIN_POPCOUNTLL(x) __builtin_popcountll(x)
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


#	if defined(KERBAL_BUILTIN_POPCOUNT)

		KERBAL_CONSTEXPR
		inline
		int __popcount(unsigned int x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			return KERBAL_BUILTIN_POPCOUNT(x);
		}

#	endif


#	if defined(KERBAL_BUILTIN_POPCOUNTL)

		KERBAL_CONSTEXPR
		inline
		int __popcount(unsigned long x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			return KERBAL_BUILTIN_POPCOUNTL(x);
		}

#	endif


#	if defined(KERBAL_BUILTIN_POPCOUNTLL)

		KERBAL_CONSTEXPR
		inline
		int __popcount(unsigned long long x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			return KERBAL_BUILTIN_POPCOUNTLL(x);
		}

#	endif

		template <typename Signed>
		KERBAL_CONSTEXPR
		int __popcount(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
			return __popcount(static_cast<unsigned_t>(x), kerbal::type_traits::false_type());
		}

		/**
		 * Counts the number of 1 bits in the value of x.
		 */
		template <typename Tp>
		KERBAL_CONSTEXPR
		int popcount(Tp x) KERBAL_NOEXCEPT
		{
			return kerbal::numeric::__popcount(x, kerbal::type_traits::is_signed<Tp>());
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_POPCOUNT_HPP
