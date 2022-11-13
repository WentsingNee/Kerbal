/**
 * @file       bitarray.hpp
 * @brief
 * @date       2022-11-12
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
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>
#include <climits>

#include <kerbal/numeric/bit/bitarray/bitarray.plain.hpp>


#ifndef KERBAL_NUMERIC_ENABLE_BITARRAY_IE_OPTIMISE

#	if __BMI2__ || __AVX2__ || __SSE2__ || __MMX__ || __ARM_NEON
#		define KERBAL_NUMERIC_ENABLE_BITARRAY_IE_OPTIMISE 1
#	else
#		define KERBAL_NUMERIC_ENABLE_BITARRAY_IE_OPTIMISE 0
#	endif

#endif


#if KERBAL_NUMERIC_ENABLE_BITARRAY_IE_OPTIMISE

#	if __BMI2__
#		include <kerbal/numeric/bit/bitarray/bitarray.bmi2.hpp>
#	endif

#	if __AVX2__
#		include <kerbal/numeric/bit/bitarray/bitarray.avx2.hpp>
#	endif

#	if __SSE2__
#		include <kerbal/numeric/bit/bitarray/bitarray.sse2.hpp>
#	endif

#	if __MMX__
#		include <kerbal/numeric/bit/bitarray/bitarray.mmx.hpp>
#	endif

//#	if __ARM_FEATURE_SVE
//#		include <kerbal/numeric/bit/bitarray/bitarray.sve.hpp>
//#	endif

#	if __ARM_NEON
#		include <kerbal/numeric/bit/bitarray/bitarray.neon.hpp>
#	endif

#endif

#undef EACH


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

#if KERBAL_NUMERIC_ENABLE_BITARRAY_IE_OPTIMISE

			inline
			kerbal::numeric::bitarray_result<kerbal::compatibility::uint8_t>::type
			bitarray_simd_dispatch(kerbal::compatibility::uint8_t x) KERBAL_NOEXCEPT
			{
#		if __BMI2__
				return bmi2::bitarray(x);
#		elif __SSE2__
				return sse2::bitarray(x);
#		elif __MMX__
				return mmx::bitarray(x);
#		elif __ARM_NEON
				return neon::bitarray(x);
#		else
				return plain::bitarray(x);
#		endif
			}

			inline
			kerbal::numeric::bitarray_result<kerbal::compatibility::uint16_t>::type
			bitarray_simd_dispatch(kerbal::compatibility::uint16_t x) KERBAL_NOEXCEPT
			{
#		if __BMI2__
				return bmi2::bitarray(x);
#		elif __SSE2__
				return sse2::bitarray(x);
#		elif __ARM_NEON
				return neon::bitarray(x);
#		else
				return plain::bitarray(x);
#		endif
			}

			inline
			kerbal::numeric::bitarray_result<kerbal::compatibility::uint32_t>::type
			bitarray_simd_dispatch(kerbal::compatibility::uint32_t x) KERBAL_NOEXCEPT
			{
#		if __BMI2__
				return bmi2::bitarray(x);
#		elif __AVX2__
				return avx2::bitarray(x);
#		else
				return plain::bitarray(x);
#		endif
			}

			inline
			kerbal::numeric::bitarray_result<kerbal::compatibility::uint64_t>::type
			bitarray_simd_dispatch(kerbal::compatibility::uint64_t x) KERBAL_NOEXCEPT
			{
				return plain::bitarray(x);
			}


			template <typename T>
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, 8>) KERBAL_NOEXCEPT
			{
				return bitarray_simd_dispatch(static_cast<kerbal::compatibility::uint8_t>(x));
			}

			template <typename T>
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, 16>) KERBAL_NOEXCEPT
			{
				return bitarray_simd_dispatch(static_cast<kerbal::compatibility::uint16_t>(x));
			}

			template <typename T>
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, 32>) KERBAL_NOEXCEPT
			{
				return bitarray_simd_dispatch(static_cast<kerbal::compatibility::uint32_t>(x));
			}

			template <typename T>
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, 64>) KERBAL_NOEXCEPT
			{
				return bitarray_simd_dispatch(static_cast<kerbal::compatibility::uint64_t>(x));
			}

			template <typename T, std::size_t Size>
			KERBAL_CONSTEXPR14
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, Size>) KERBAL_NOEXCEPT
			{
				return plain::bitarray<T>(x);
			}

#endif // KERBAL_NUMERIC_ENABLE_BITARRAY_IE_OPTIMISE


			template <typename T>
			class bitarray_helper
			{
				protected:

#if KERBAL_NUMERIC_ENABLE_BITARRAY_IE_OPTIMISE

					static
					typename kerbal::numeric::bitarray_result<T>::type
					fix_integer_type_dispatch(T x) KERBAL_NOEXCEPT
					{
						return bitarray_fix_integer_type_convert<T>(x, kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(T)>());
					}

					KERBAL_CONSTEXPR14
					static
					typename kerbal::numeric::bitarray_result<T>::type
					is_constant_evaluated_handler(T x) KERBAL_NOEXCEPT
					{

#	if __cplusplus >= 201402L

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						return KERBAL_IS_CONSTANT_EVALUATED() ?
								plain::bitarray<T>(x) :
								fix_integer_type_dispatch(x);
#		else
						return plain::bitarray<T>(x);
#		endif

#	else
						return fix_integer_type_dispatch(x);
#	endif

					}

#endif

				public:

					KERBAL_CONSTEXPR14
					static
					typename kerbal::numeric::bitarray_result<T>::type
					bitarray(T x) KERBAL_NOEXCEPT
					{
#if KERBAL_NUMERIC_ENABLE_BITARRAY_IE_OPTIMISE
						return is_constant_evaluated_handler(x);
#else
						return plain::bitarray(x);
#endif
					}

			};

		} // namespace detail


		template <typename T>
		KERBAL_CONSTEXPR14
		typename kerbal::numeric::bitarray_result<T>::type
		bitarray(T x) KERBAL_NOEXCEPT
		{
			return detail::bitarray_helper<T>::bitarray(x);
		}

	} // namespace numeric

} // namespace kerbal


#endif // KERBAL_NUMERIC_BIT_BITARRAY_HPP
