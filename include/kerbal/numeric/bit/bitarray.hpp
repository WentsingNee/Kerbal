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


#	if __BMI2__
#		define KERBAL_BITARRAY_POLICY_BMI2 1
#	endif

#	if __AVX512F__
#		define KERBAL_BITARRAY_POLICY_AVX512F 1
#	endif

#	if __AVX2__
#		define KERBAL_BITARRAY_POLICY_AVX2 1
#	endif

#	if __SSE2__
#		define KERBAL_BITARRAY_POLICY_SSE2 1
#	endif

#	if __MMX__
#		define KERBAL_BITARRAY_POLICY_MMX 1
#	endif

#	if __ARM_FEATURE_SVE
#		define KERBAL_BITARRAY_POLICY_SVE 1
#	endif

#	if __ARM_NEON
#		define KERBAL_BITARRAY_POLICY_NEON 1
#	endif


#include <kerbal/numeric/bit/detail/bitarray/bitarray.plain.hpp>

#	if KERBAL_BITARRAY_POLICY_BMI2
#		include <kerbal/numeric/bit/detail/bitarry/bitarray.bmi2.hpp>
#	endif

#	if KERBAL_BITARRAY_POLICY_AVX512F
#		include <kerbal/numeric/bit/detail/bitarry/bitarray.avx512f.hpp>
#	endif

#	if KERBAL_BITARRAY_POLICY_AVX2
#		include <kerbal/numeric/bit/detail/bitarray/bitarray.avx2.hpp>
#	endif

#	if KERBAL_BITARRAY_POLICY_SSE2
#		include <kerbal/numeric/bit/detail/bitarray/bitarray.sse2.hpp>
#	endif

#	if KERBAL_BITARRAY_POLICY_MMX
#		include <kerbal/numeric/bit/detail/bitarray/bitarray.mmx.hpp>
#	endif

#	if KERBAL_BITARRAY_POLICY_SVE
#		include <kerbal/numeric/bit/detail/bitarray/bitarray.sve.hpp>
#	endif

#	if KERBAL_BITARRAY_POLICY_NEON
#		include <kerbal/numeric/bit/detail/bitarray/bitarray.neon.hpp>
#	endif

#undef EACH


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			inline
			kerbal::numeric::bitarray_result<kerbal::compatibility::uint8_t>::type
			bitarray_ie_dispatch(kerbal::compatibility::uint8_t x) KERBAL_NOEXCEPT
			{
#		if 0
				// pass
#		elif KERBAL_BITARRAY_POLICY_BMI2
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
			bitarray_ie_dispatch(kerbal::compatibility::uint16_t x) KERBAL_NOEXCEPT
			{
#		if 0
				// pass
#		elif KERBAL_BITARRAY_POLICY_BMI2
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
			kerbal::numeric::bitarray_result<kerbal::compatibility::uint32_t>::type
			bitarray_ie_dispatch(kerbal::compatibility::uint32_t x) KERBAL_NOEXCEPT
			{
#		if 0
				// pass
#		elif KERBAL_BITARRAY_POLICY_BMI2
				return bmi2::bitarray(x);
#		elif __AVX2__
				return avx2::bitarray(x);
#		elif __SSE2__
				return sse2::bitarray(x);
#		else
				return plain::bitarray(x);
#		endif
			}

			inline
			kerbal::numeric::bitarray_result<kerbal::compatibility::uint64_t>::type
			bitarray_ie_dispatch(kerbal::compatibility::uint64_t x) KERBAL_NOEXCEPT
			{
#		if 0
				// pass
#		elif KERBAL_BITARRAY_POLICY_BMI2
				return bmi2::bitarray(x);
#		elif __AVX2__
				return avx2::bitarray(x);
#		else
				return plain::bitarray(x);
#		endif
			}


			template <typename T>
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, 8>) KERBAL_NOEXCEPT
			{
				return bitarray_ie_dispatch(static_cast<kerbal::compatibility::uint8_t>(x));
			}

			template <typename T>
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, 16>) KERBAL_NOEXCEPT
			{
				return bitarray_ie_dispatch(static_cast<kerbal::compatibility::uint16_t>(x));
			}

			template <typename T>
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, 32>) KERBAL_NOEXCEPT
			{
				return bitarray_ie_dispatch(static_cast<kerbal::compatibility::uint32_t>(x));
			}

			template <typename T>
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, 64>) KERBAL_NOEXCEPT
			{
				return bitarray_ie_dispatch(static_cast<kerbal::compatibility::uint64_t>(x));
			}

			template <typename T, std::size_t Size>
			KERBAL_CONSTEXPR14
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_fix_integer_type_convert(T x, kerbal::type_traits::integral_constant<std::size_t, Size>) KERBAL_NOEXCEPT
			{
				return plain::bitarray(x);
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_is_constant_evaluate_aspect(T x) KERBAL_NOEXCEPT
			{
#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				if (KERBAL_IS_CONSTANT_EVALUATED()) {
					return plain::bitarray(x);
				}
				return bitarray_ie_dispatch(x);
#		else
				return plain::bitarray(x);
#		endif
			}


		} // namespace detail


		template <typename T>
		KERBAL_CONSTEXPR14
		typename kerbal::numeric::bitarray_result<T>::type
		bitarray(T x) KERBAL_NOEXCEPT
		{
			return detail::bitarray_is_constant_evaluate_aspect(x);
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_BITARRAY_HPP
