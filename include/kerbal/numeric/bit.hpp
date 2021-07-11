/**
 * @file       bit.hpp
 * @brief
 * @date       2019-9-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_HPP
#define KERBAL_NUMERIC_BIT_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/architecture.hpp>
#include <kerbal/config/compiler_id.hpp>
#include <kerbal/container/array.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>


#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#	if KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_X86 || KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_AMD64
#		include <immintrin.h>
#		define KERBAL_X86_POPCNTU32_INTRINSIC 1
#		define KERBAL_X86_POPCNTU64_INTRINSIC 1
#	endif
#endif


namespace kerbal
{

	namespace numeric
	{

		template <typename Tp>
		struct bitarray_result_len:
				kerbal::type_traits::integral_constant<size_t, sizeof(Tp) * CHAR_BIT>
		{
		};

		template <typename Tp>
		KERBAL_CONSTEXPR14
		kerbal::container::array<bool, bitarray_result_len<Tp>::value>
		bitarray(Tp x) KERBAL_NOEXCEPT
		{
			typedef bitarray_result_len<Tp> BIT_ARRAY_LEN;
			kerbal::container::array<bool, BIT_ARRAY_LEN::value> r
#		if __cplusplus >= 201402L
				= {}
#		endif
			;

			for (typename BIT_ARRAY_LEN::value_type i = 0; i < BIT_ARRAY_LEN::value; ++i) {
				r[BIT_ARRAY_LEN::value - 1 - i] = ((x >> i) & 1);
			}
			return r;
		}

		template <typename Tp>
		struct octarray_result_len:
				kerbal::type_traits::integral_constant<size_t, sizeof(Tp) * CHAR_BIT / 3 + (sizeof(Tp) * CHAR_BIT % 3 != 0)>
		{
		};

		template <typename Tp>
		KERBAL_CONSTEXPR14
		kerbal::container::array<char, octarray_result_len<Tp>::value>
		octarray(Tp x) KERBAL_NOEXCEPT
		{
			typedef octarray_result_len<Tp> OCT_ARRAY_LEN;
			kerbal::container::array<char, OCT_ARRAY_LEN::value> r
#		if __cplusplus >= 201402L
				= {}
#		endif
			;

			for (typename OCT_ARRAY_LEN::value_type i = 0; i < OCT_ARRAY_LEN::value; ++i) {
				char current = (x >> (i * 3)) & 7;
				current += '0';
				r[OCT_ARRAY_LEN::value - 1 - i] = current;
			}
			return r;
		}

		template <typename Tp>
		struct hexarray_result_len:
				kerbal::type_traits::integral_constant<size_t, sizeof(Tp) * CHAR_BIT / 4 + (sizeof(Tp) * CHAR_BIT % 4 != 0)>
		{
		};

		template <typename Tp>
		KERBAL_CONSTEXPR14
		kerbal::container::array<char, hexarray_result_len<Tp>::value>
		hexarray(Tp x) KERBAL_NOEXCEPT
		{
			typedef hexarray_result_len<Tp> HEX_ARRAY_LEN;
			kerbal::container::array<char, HEX_ARRAY_LEN::value> r
#		if __cplusplus >= 201402L
				= {}
#		endif
			;

			for (typename HEX_ARRAY_LEN::value_type i = 0; i < HEX_ARRAY_LEN::value; ++i) {
				char current = (x >> (i * 4)) & 0xf;
				if (current < 10) {
					current += '0';
				} else {
					current += 'a' - 10;
				}
				r[HEX_ARRAY_LEN::value - 1 - i] = current;
			}
			return r;
		}


		namespace detail
		{

# if CHAR_BIT != 8

			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int __basic_popcount(Unsigned x) KERBAL_NOEXCEPT
			{
				int cnt = 0;
				while (x) {
					x &= x - 1;
					++cnt;
				}
				return cnt;
			}

# else

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
							(_0x3333_loop<T, W - 1>::value << CHAR_BIT) + _0x3333_loop<T, 1>::value
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
							(_0x5555_loop<T, W - 1>::value << CHAR_BIT) + _0x5555_loop<T, 1>::value
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
							(_0x0f0f_loop<T, W - 1>::value << CHAR_BIT) + _0x0f0f_loop<T, 1>::value
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
							(_0x0101_loop<T, W - 1>::value << CHAR_BIT) + _0x0101_loop<T, 1>::value
					>
			{
			};

			template <typename T>
			struct _0x0101 :
					public _0x0101_loop<T, sizeof(T)>
			{
			};

#endif

			// optimized-swar algorithm
			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int __basic_popcount(Unsigned x) KERBAL_NOEXCEPT
			{
				x = x - ((x >> 1) & detail::_0x5555<Unsigned>::value);
				// x = (x & detail::_0x5555<Unsigned>::value) + ((x >> 1) & detail::_0x5555<Unsigned>::value);

				x = (x & detail::_0x3333<Unsigned>::value) + ((x >> 2) & detail::_0x3333<Unsigned>::value);

				x = ((x >> 4) + x) & detail::_0x0f0f<Unsigned>::value;
				// x = (x & detail::_0x0f0f<Unsigned>::value) + ((x >> 4) & detail::_0x0f0f<Unsigned>::value);

				x = static_cast<Unsigned>(x * detail::_0x0101<Unsigned>::value) >> (8 * (sizeof(Unsigned) - 1));
				return x;
			}


			template <typename Unsigned>
			KERBAL_CONSTEXPR14
			int __popcount(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return __basic_popcount(x);
			}

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		if (KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_X86 && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_AMD64) || (defined(__POPCNT__))
#			define KERBAL_GNU_TRY_BUILTIN_POPCOUNT_INTRINSICS 1
#		endif
#	endif


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



#	if KERBAL_HAS_BUILTIN_POPCOUNT

			KERBAL_CONSTEXPR
			inline
			int __popcount(unsigned int x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_POPCOUNT(x);
			}

#	elif KERBAL_X86_POPCNTU32_INTRINSIC

			KERBAL_CONSTEXPR14
			inline
			int __popcount(unsigned int x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
#		if __cplusplus >= 201402L
#			if KERBAL_HAS_KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					return KERBAL_IS_CONSTANT_EVALUATED() ? __basic_popcount(x) : _mm_popcnt_u32(x);
#			else
					return __basic_popcount(x);
#			endif
#		else
				return _mm_popcnt_u32(x);
#		endif
			}

#	endif


#	if KERBAL_HAS_BUILTIN_POPCOUNTL

			KERBAL_CONSTEXPR
			inline
			int __popcount(unsigned long x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return KERBAL_BUILTIN_POPCOUNTL(x);
			}

#	endif


#	if KERBAL_HAS_BUILTIN_POPCOUNTLL

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

		} // namespace detail

		/**
		 * Counts the number of 1 bits in the value of x.
		 */
		template <typename Tp>
		KERBAL_CONSTEXPR
		int popcount(Tp x) KERBAL_NOEXCEPT
		{
			return kerbal::numeric::detail::__popcount(x, kerbal::type_traits::is_signed<Tp>());
		}



		template <typename Unsigned>
		KERBAL_CONSTEXPR
		bool __ispow2(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			return x != 0 && ((x & (x - 1)) == 0);
		}

		template <typename Signed>
		KERBAL_CONSTEXPR
		bool __ispow2(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			return x > 0 && ((x & (x - 1)) == 0);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		bool ispow2(Tp x) KERBAL_NOEXCEPT
		{
			return __ispow2(x, kerbal::type_traits::is_signed<Tp>());
		}



		template <typename Unsigned>
		KERBAL_CONSTEXPR
		bool __has_single_bit(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			return x != 0 && ((x & (x - 1)) == 0);
		}

		template <typename Signed>
		KERBAL_CONSTEXPR14
		bool __has_single_bit(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
			unsigned_t u = static_cast<unsigned_t>(x);
			return __has_single_bit(u, kerbal::type_traits::false_type());
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		bool has_single_bit(Tp x) KERBAL_NOEXCEPT
		{
			return __has_single_bit(x, kerbal::type_traits::is_signed<Tp>());
		}



		/**
		 * Generate 00...0011...11 (n 1 right)
		 *
		 * @warning Undefined behaviour if n < 0 or n > sizeof(Tp) * CHAR_BIT.
		 */
		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp mask(size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return n == sizeof(unsigned_t) * CHAR_BIT ?
					~static_cast<unsigned_t>(0) :
					~(static_cast<unsigned_t>(~static_cast<unsigned_t>(0)) << n);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp flip(Tp x, size_t pos) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return x ^ (static_cast<unsigned_t>(1) << pos);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp flip_left_n(Tp x, size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return x ^ ~kerbal::numeric::mask<unsigned_t>(sizeof(unsigned_t) * CHAR_BIT - n);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp flip_right_n(Tp x, size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return x ^ kerbal::numeric::mask<unsigned_t>(n);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp reset_bit(Tp x, size_t pos) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return x & ~(static_cast<unsigned_t>(1) << pos);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp reset_left_n(Tp x, size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return x & kerbal::numeric::mask<unsigned_t>(sizeof(unsigned_t) * CHAR_BIT - n);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp reset_right_n(Tp x, size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return x & ~kerbal::numeric::mask<unsigned_t>(n);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp set_bit(Tp x, size_t pos) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return x | (static_cast<unsigned_t>(1) << pos);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp set_left_n(Tp x, size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return x | ~kerbal::numeric::mask<unsigned_t>(sizeof(unsigned_t) * CHAR_BIT - n);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp set_right_n(Tp x, size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Tp>::type unsigned_t;
			return x | kerbal::numeric::mask<unsigned_t>(n);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		bool get_bit(Tp x, size_t pos) KERBAL_NOEXCEPT
		{
			return (x >> pos) & 1;
		}



		template <typename Signed>
		KERBAL_CONSTEXPR
		Signed __rotl(Signed x, int s, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof(Signed) * CHAR_BIT> BIT_WIDTH;
#	define __u static_cast<unsigned_t>(x)
			return s == 0 ?
					x :
					s > 0 ?
					(__u << s | (__u >> (BIT_WIDTH::value - s))) :
					(__u >> -s | (__u << (BIT_WIDTH::value - (-s)))); // rotr(x, -s);
#	undef __u
		}

		template <typename Unsigned>
		KERBAL_CONSTEXPR
		Unsigned __rotl(Unsigned x, int s, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			typedef kerbal::type_traits::integral_constant<size_t, sizeof(Unsigned) * CHAR_BIT> BIT_WIDTH;
			return s == 0 ?
					 x :
					 (x << s | (x >> (BIT_WIDTH::value - s)));
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp rotl(Tp x, int s) KERBAL_NOEXCEPT
		{
			return __rotl(x, s % (sizeof(Tp) * CHAR_BIT), kerbal::type_traits::is_signed<Tp>());
		}

		template <typename Signed>
		KERBAL_CONSTEXPR
		Signed __rotr(Signed x, int s, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
			return s == 0 ?
					x :
					s > 0 ?
					(static_cast<unsigned_t>(x) >> s | (static_cast<unsigned_t>(x) << ((sizeof(Signed) * CHAR_BIT) - s))) :
					(static_cast<unsigned_t>(x) << -s | (static_cast<unsigned_t>(x) >> ((sizeof(Signed) * CHAR_BIT) - (-s)))); // rotl(x, -s);
		}

		template <typename Unsigned>
		KERBAL_CONSTEXPR
		Unsigned __rotr(Unsigned x, int s, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			return s == 0 ?
					 x :
					 (x >> s | (x << ((sizeof(Unsigned) * CHAR_BIT) - s)));
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		Tp rotr(Tp x, int s) KERBAL_NOEXCEPT
		{
			return __rotr(x, s % (sizeof(Tp) * CHAR_BIT), kerbal::type_traits::is_signed<Tp>());
		}


#	if CHAR_BIT != 8

		template <typename Unsigned>
		KERBAL_CONSTEXPR14
		int _K_countr_zero(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
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

#	else

		namespace detail
		{

			template <typename Unsigned, int I, int J>
			struct _K_countr_zero_find_1_mask_loop;

			template <typename Unsigned, int I>
			struct _K_countr_zero_find_1_mask_loop<Unsigned, I, 0> :
					kerbal::type_traits::integral_constant<Unsigned, 0>
			{
			};

			template <typename Unsigned, int I, int J>
			struct _K_countr_zero_find_1_mask_loop :
					kerbal::type_traits::integral_constant<
							Unsigned,
							_K_countr_zero_find_1_mask_loop<Unsigned, I, J - 1>::value |
									(((static_cast<Unsigned>(~(J - 1)) & (static_cast<Unsigned>(1) << I)) != 0) ?
									static_cast<Unsigned>(1) << (J - 1) :
									0)
					>
			{
			};

			template <typename Unsigned, int I>
			struct _K_countr_zero_find_1_mask :
					_K_countr_zero_find_1_mask_loop<Unsigned, I, sizeof(Unsigned) * CHAR_BIT>
			{
			};

			template <std::size_t I>
			struct _K_countr_zero_find_1_mask_N : kerbal::type_traits::integral_constant<int, 0>
			{
			};

			template <>
			struct _K_countr_zero_find_1_mask_N<8> : kerbal::type_traits::integral_constant<int, 3>
			{
			};

			template <>
			struct _K_countr_zero_find_1_mask_N<16> : kerbal::type_traits::integral_constant<int, 4>
			{
			};

			template <>
			struct _K_countr_zero_find_1_mask_N<32> : kerbal::type_traits::integral_constant<int, 5>
			{
			};

			template <>
			struct _K_countr_zero_find_1_mask_N<64> : kerbal::type_traits::integral_constant<int, 6>
			{
			};

			template <>
			struct _K_countr_zero_find_1_mask_N<128> : kerbal::type_traits::integral_constant<int, 7>
			{
			};


			template <typename Unsigned, int I>
			struct _K_countr_zero_find_1;

			template <typename Unsigned>
			struct _K_countr_zero_find_1<Unsigned, 0>
			{
					typedef _K_countr_zero_find_1_mask<Unsigned, 0> MASK;

					KERBAL_CONSTEXPR
					static int f(Unsigned x) KERBAL_NOEXCEPT
					{
						return (x & MASK::value ? 0 : 1);
					}
			};

			template <typename Unsigned, int I>
			struct _K_countr_zero_find_1
			{
					typedef _K_countr_zero_find_1_mask<Unsigned, I> MASK;
					typedef kerbal::type_traits::integral_constant<int, 1u << I> G;

					KERBAL_CONSTEXPR
					static int f(Unsigned x) KERBAL_NOEXCEPT
					{
						return _K_countr_zero_find_1<Unsigned, I - 1>::f(x) + (x & MASK::value ? 0 : G::value);
					}
			};

		} // namespace detail

		template <typename Unsigned>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<
				detail::_K_countr_zero_find_1_mask_N<CHAR_BIT * sizeof(Unsigned)>::value != 0,
				int
		>::type
		_K_countr_zero(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(Unsigned)> DIGIT;
			typedef detail::_K_countr_zero_find_1_mask_N<DIGIT::value> N;
			return detail::_K_countr_zero_find_1<Unsigned, N::value - 1>::f(x & (-x)) + (x == 0);
		}

		template <typename Unsigned>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<
				detail::_K_countr_zero_find_1_mask_N<CHAR_BIT * sizeof(Unsigned)>::value == 0,
				int
		>::type
		_K_countr_zero(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			typedef kerbal::type_traits::integral_constant<int, CHAR_BIT * sizeof(Unsigned)> DIGIT;
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

#	endif



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



#	if KERBAL_HAS_BUILTIN_COUNTR_ZERO

		KERBAL_CONSTEXPR
		inline
		int _K_countr_zero(unsigned int x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			return KERBAL_BUILTIN_COUNTR_ZERO(x);
		}

		KERBAL_CONSTEXPR
		inline
		int _K_countr_zero(unsigned short x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
//			return x == 0 ? CHAR_BIT * sizeof(x) : KERBAL_BUILTIN_COUNTR_ZERO(x);
			typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned short)> S;
			typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
			KERBAL_STATIC_ASSERT(S::value <= I::value, "digits of short type is greater than that of int type");
			return S::value == I::value ?
					KERBAL_BUILTIN_COUNTR_ZERO(x) :
					KERBAL_BUILTIN_COUNTR_ZERO(static_cast<unsigned int>(1u) << S::value | static_cast<unsigned int>(x));
		}

		KERBAL_CONSTEXPR
		inline
		int _K_countr_zero(unsigned char x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
//			return x == 0 ? CHAR_BIT * sizeof(x) : KERBAL_BUILTIN_COUNTR_ZERO(x);
			 typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned char)> C;
			 typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(unsigned int)> I;
			 KERBAL_STATIC_ASSERT(C::value <= I::value, "");
			 return C::value == I::value ?
					KERBAL_BUILTIN_COUNTR_ZERO(x) :
			 		KERBAL_BUILTIN_COUNTR_ZERO(static_cast<unsigned int>(1u) << C::value | static_cast<unsigned int>(x));
		 }

#	endif


#	if KERBAL_HAS_BUILTIN_COUNTR_ZEROL

		KERBAL_CONSTEXPR
		inline
		int _K_countr_zero(unsigned long x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			return KERBAL_BUILTIN_COUNTR_ZEROL(x);
		}

#	endif


#	if KERBAL_HAS_BUILTIN_COUNTR_ZEROLL

		KERBAL_CONSTEXPR
		inline
		int _K_countr_zero(unsigned long long x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
		{
			return KERBAL_BUILTIN_COUNTR_ZEROLL(x);
		}

#	endif


		template <typename Signed>
		KERBAL_CONSTEXPR
		int _K_countr_zero(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
			return _K_countr_zero(static_cast<unsigned_t>(x), kerbal::type_traits::false_type());
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		int countr_zero(Tp x) KERBAL_NOEXCEPT
		{
			return _K_countr_zero(x, kerbal::type_traits::is_signed<Tp>());
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_HPP
