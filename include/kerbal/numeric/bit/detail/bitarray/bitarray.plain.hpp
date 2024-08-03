/**
 * @file       bitarray.plain.hpp
 * @brief
 * @date       2022-11-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_DETAIL_BITARRY_BITARRAY_PLAIN_HPP
#define KERBAL_NUMERIC_BIT_DETAIL_BITARRY_BITARRAY_PLAIN_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/array.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <climits>
#include <cstddef>


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

			namespace plain
			{

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

			} // namespace plain

		} // namespace detail

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_DETAIL_BITARRY_BITARRAY_PLAIN_HPP
