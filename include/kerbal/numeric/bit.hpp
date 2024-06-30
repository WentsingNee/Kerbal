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

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/array.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>
#include <cstddef>

#include <kerbal/numeric/bit/bitarray.hpp>
#include <kerbal/numeric/bit/countr_zero.hpp>
#include <kerbal/numeric/bit/popcount.hpp>
#include <kerbal/numeric/bit/single_bit_bsearch.hpp>


namespace kerbal
{

	namespace numeric
	{

		template <typename T>
		struct octarray_result_len :
			kerbal::type_traits::integral_constant<std::size_t, sizeof(T) * CHAR_BIT / 3 + (sizeof(T) * CHAR_BIT % 3 != 0)>
		{
		};

		template <typename T>
		struct octarray_result
		{
				typedef kerbal::container::array<char, octarray_result_len<T>::value> type;
		};

		template <typename T>
		KERBAL_CONSTEXPR14
		typename kerbal::numeric::octarray_result<T>::type
		octarray(T x) KERBAL_NOEXCEPT
		{
			typedef kerbal::numeric::octarray_result_len<T> OCT_ARRAY_LEN;
			typename kerbal::numeric::octarray_result<T>::type r
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

		template <typename T>
		struct hexarray_result_len :
			kerbal::type_traits::integral_constant<std::size_t, sizeof(T) * CHAR_BIT / 4 + (sizeof(T) * CHAR_BIT % 4 != 0)>
		{
		};

		template <typename T>
		struct hexarray_result
		{
				typedef kerbal::container::array<char, hexarray_result_len<T>::value> type;
		};

		template <typename T>
		KERBAL_CONSTEXPR14
		typename kerbal::numeric::hexarray_result<T>::type
		hexarray(T x) KERBAL_NOEXCEPT
		{
			typedef hexarray_result_len<T> HEX_ARRAY_LEN;
			typename kerbal::numeric::hexarray_result<T>::type r
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

			template <typename Unsigned>
			KERBAL_CONSTEXPR
			bool ispow2_helper(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return x != 0 && ((x & (x - 1)) == 0);
			}

			template <typename Signed>
			KERBAL_CONSTEXPR
			bool ispow2_helper(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				return x > 0 && ((x & (x - 1)) == 0);
			}

		} // namespace detail

		template <typename T>
		KERBAL_CONSTEXPR
		bool ispow2(T x) KERBAL_NOEXCEPT
		{
			return kerbal::numeric::detail::ispow2_helper(x, kerbal::type_traits::is_signed<T>());
		}



		namespace detail
		{

			template <typename Unsigned>
			KERBAL_CONSTEXPR
			bool has_single_bit_helper(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return x != 0 && ((x & (x - 1)) == 0);
			}

			template <typename Signed>
			KERBAL_CONSTEXPR14
			bool has_single_bit_helper(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
				unsigned_t ux = static_cast<unsigned_t>(x);
				return has_single_bit_helper(ux, kerbal::type_traits::false_type());
			}

		} // namespace detail

		template <typename T>
		KERBAL_CONSTEXPR
		bool has_single_bit(T x) KERBAL_NOEXCEPT
		{
			return kerbal::numeric::detail::has_single_bit_helper(x, kerbal::type_traits::is_signed<T>());
		}



		/**
		 * Generate 00...0011...11 (n 1 right)
		 *
		 * @warning Undefined behaviour if n < 0 or n > sizeof(T) * CHAR_BIT.
		 */
		template <typename T>
		KERBAL_CONSTEXPR
		T mask(std::size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return
				n == sizeof(unsigned_t) * CHAR_BIT ?
				~static_cast<unsigned_t>(0) :
				~(static_cast<unsigned_t>(~static_cast<unsigned_t>(0)) << n)
			;
		}

		template <typename T>
		KERBAL_CONSTEXPR
		T flip(T x, std::size_t pos) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return x ^ (static_cast<unsigned_t>(1) << pos);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		T flip_left_n(T x, std::size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return x ^ ~kerbal::numeric::mask<unsigned_t>(sizeof(unsigned_t) * CHAR_BIT - n);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		T flip_right_n(T x, std::size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return x ^ kerbal::numeric::mask<unsigned_t>(n);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		T reset_bit(T x, std::size_t pos) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return x & ~(static_cast<unsigned_t>(1) << pos);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		T reset_left_n(T x, std::size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return x & kerbal::numeric::mask<unsigned_t>(sizeof(unsigned_t) * CHAR_BIT - n);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		T reset_right_n(T x, std::size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return x & ~kerbal::numeric::mask<unsigned_t>(n);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		T set_bit(T x, std::size_t pos) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return x | (static_cast<unsigned_t>(1) << pos);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		T set_left_n(T x, std::size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return x | ~kerbal::numeric::mask<unsigned_t>(sizeof(unsigned_t) * CHAR_BIT - n);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		T set_right_n(T x, std::size_t n) KERBAL_NOEXCEPT
		{
			typedef typename kerbal::type_traits::make_unsigned<T>::type unsigned_t;
			return x | kerbal::numeric::mask<unsigned_t>(n);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool get_bit(T x, std::size_t pos) KERBAL_NOEXCEPT
		{
			return (x >> pos) & 1;
		}



		namespace detail
		{

			template <typename Signed>
			KERBAL_CONSTEXPR
			Signed rotl_helper(Signed x, int s, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(Signed) * CHAR_BIT> BIT_WIDTH;
#		define ux static_cast<unsigned_t>(x)
				return
					s == 0 ?
					x :
					(
						s > 0 ?
						(ux << s | (ux >> (BIT_WIDTH::value - s))) :
						(ux >> -s | (ux << (BIT_WIDTH::value - (-s)))) // rotr(x, -s)
					)
				;
#		undef ux
			}

			template <typename Unsigned>
			KERBAL_CONSTEXPR
			Unsigned rotl_helper(Unsigned x, int s, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(Unsigned) * CHAR_BIT> BIT_WIDTH;
				return
					s == 0 ?
					x :
					(x << s | (x >> (BIT_WIDTH::value - s)))
				;
			}

		} // namespace detail

		template <typename T>
		KERBAL_CONSTEXPR
		T rotl(T x, int s) KERBAL_NOEXCEPT
		{
			return kerbal::numeric::detail::rotl_helper(x, s % (sizeof(T) * CHAR_BIT), kerbal::type_traits::is_signed<T>());
		}

		namespace detail
		{

			template <typename Signed>
			KERBAL_CONSTEXPR
			Signed rotr_helper(Signed x, int s, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
#		define ux static_cast<unsigned_t>(x)
				return
					s == 0 ?
					x :
					(
						s > 0 ?
						(ux >> s | (ux << ((sizeof(Signed) * CHAR_BIT) - s))) :
						(ux << -s | (ux >> ((sizeof(Signed) * CHAR_BIT) - (-s)))) // rotl(x, -s)
					)
				;
#		undef ux
			}

			template <typename Unsigned>
			KERBAL_CONSTEXPR
			Unsigned rotr_helper(Unsigned x, int s, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				return
					s == 0 ?
					x :
					(x >> s | (x << ((sizeof(Unsigned) * CHAR_BIT) - s)))
				;
			}

		} // namespace detail

		template <typename T>
		KERBAL_CONSTEXPR
		T rotr(T x, int s) KERBAL_NOEXCEPT
		{
			return kerbal::numeric::detail::rotr_helper(
				x,
				s % (sizeof(T) * CHAR_BIT),
				kerbal::type_traits::is_signed<T>()
			);
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_HPP
