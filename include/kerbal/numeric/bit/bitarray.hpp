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

#	if __SSE2__
#		define KERBAL_BITARRAY_POLICY_SSE2 1
#	endif

#	if __AVX2__
#		define KERBAL_BITARRAY_POLICY_AVX2 1
#	endif

#	if __AVX512F__
#		define KERBAL_BITARRAY_POLICY_AVX512F 1
#	endif


#include <kerbal/numeric/bit/detail/bitarry/bitarray.plain.hpp>

#	if KERBAL_BITARRAY_POLICY_BMI2
#		include <kerbal/numeric/bit/detail/bitarry/bitarray.bmi2.hpp>
#	endif


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			template <typename T>
			typename kerbal::numeric::bitarray_result<T>::type
			bitarray_ie_dispatch(T x) KERBAL_NOEXCEPT
			{
#		if 0
				// pass
#		elif KERBAL_BITARRAY_POLICY_BMI2
				return bmi2::bitarray(x);
#		else
				return plain::bitarray(x);
#		endif
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
