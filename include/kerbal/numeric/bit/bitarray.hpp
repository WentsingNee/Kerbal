/**
 * @file       bitarray.hpp
 * @brief
 * @date       2021-10-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_BITARRAY_HPP
#define KERBAL_NUMERIC_BIT_BITARRAY_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/array.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


#ifndef KERBAL_BITARRAY_POLICY
#endif


#	if __BMI2__
#		define KERBAL_BITARRAY_POLICY_BMI2 1
#	endif

#	if __SSE2__
#		define KERBAL_BITARRAY_POLICY_SSE2 1
#	endif

#	if __AVX2__
#		define KERBAL_BITARRAY_POLICY_AVX2 1
#	endif

#	if __AVX512F__
#		define KERBAL_BITARRAY_POLICY_AVX512F 1
#	endif


#	if KERBAL_BITARRAY_POLICY_BMI2
#		include <immintrin.h>
#	endif


namespace kerbal
{

	namespace numeric
	{

		template <typename T>
		struct bitarray_result_len:
				kerbal::type_traits::integral_constant<std::size_t, sizeof(T) * CHAR_BIT>
		{
		};

		template <typename T>
		struct bitarray_result
		{
				typedef kerbal::container::array<bool, bitarray_result_len<T>::value> type;
		};

		namespace detail
		{

			template <typename T>
			KERBAL_CONSTEXPR14
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_plain(T x) KERBAL_NOEXCEPT
			{
				typedef kerbal::numeric::bitarray_result_len<T> BIT_ARRAY_LEN;
				typename kerbal::numeric::bitarray_result<T>::type r
#		if __cplusplus >= 201402L
				= {}
#		endif
				;

				for (typename BIT_ARRAY_LEN::value_type i = 0; i < BIT_ARRAY_LEN::value; ++i) {
					r[BIT_ARRAY_LEN::value - 1 - i] = ((x >> i) & 1);
				}
				return r;
			}


#		if KERBAL_BITARRAY_POLICY_BMI2

			namespace bmi2
			{

#		define EACH(i) \
				do { \
					unsigned char b = x >> (((sizeof(Unsigned) - 1) - (i)) * CHAR_BIT); \
					kerbal::compatibility::uint64_t t = _pdep_u64(static_cast<kerbal::compatibility::uint64_t>(b), MASK); \
					t = __bswap_64(t); \
					*(reinterpret_cast<kerbal::compatibility::uint64_t*>(static_cast<void*>(&r[(i) * CHAR_BIT]))) = t; \
				} while(0)

				typename bitarray_result<kerbal::compatibility::uint8_t>::type
				inline
				bitarray(kerbal::compatibility::uint8_t x) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint8_t Unsigned;
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;

					EACH(0);

					return r;
				}

				typename bitarray_result<kerbal::compatibility::uint16_t>::type
				inline
				bitarray(kerbal::compatibility::uint16_t x) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint16_t Unsigned;
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;

					EACH(0);
					EACH(1);

					return r;
				}

				typename bitarray_result<kerbal::compatibility::uint32_t>::type
				inline
				bitarray(kerbal::compatibility::uint32_t x) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Unsigned;
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;

					EACH(0);
					EACH(1);
					EACH(2);
					EACH(3);

					return r;
				}

				typename bitarray_result<kerbal::compatibility::uint64_t>::type
				inline
				bitarray(kerbal::compatibility::uint64_t x) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t Unsigned;
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;

					EACH(0);
					EACH(1);
					EACH(2);
					EACH(3);
					EACH(4);
					EACH(5);
					EACH(6);
					EACH(7);

					return r;
				}

				template <typename Unsigned>
				typename bitarray_result<Unsigned>::type
				bitarray(Unsigned x) KERBAL_NOEXCEPT
				{
					const kerbal::compatibility::uint64_t MASK = 0x0101010101010101;

					typename bitarray_result<Unsigned>::type r;
					for (std::size_t i = 0; i < sizeof(Unsigned); ++i) {
						EACH(i);
					}
					return r;
				}

#		undef EACH

			} // namespace bmi2

#		endif // KERBAL_BITARRAY_POLICY_BMI2


			template <typename T>
			KERBAL_CONSTEXPR14
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_is_constant_evaluate_aspect(T x) KERBAL_NOEXCEPT
			{
#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				if (KERBAL_IS_CONSTANT_EVALUATED()) {
					return bitarray_plain(x);
				} else {

				}
#		else
				return bitarray_plain(x);
#		endif
			}


		} // namespace detail


		template <typename T>
		KERBAL_CONSTEXPR14
		typename kerbal::numeric::bitarray_result<T>::type
		bitarray(T x) KERBAL_NOEXCEPT
		{
			typedef kerbal::numeric::bitarray_result_len<T> BIT_ARRAY_LEN;
			typename kerbal::numeric::bitarray_result<T>::type r
#		if __cplusplus >= 201402L
				= {}
#		endif
			;

			for (typename BIT_ARRAY_LEN::value_type i = 0; i < BIT_ARRAY_LEN::value; ++i) {
				r[BIT_ARRAY_LEN::value - 1 - i] = ((x >> i) & 1);
			}
			return r;
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_BITARRAY_HPP
