/**
 * @file       repeat_byte.hpp
 * @brief
 * @date       2021-10-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_REPEAT_BYTE_HPP
#define KERBAL_NUMERIC_BIT_REPEAT_BYTE_HPP

#include <kerbal/type_traits/integral_constant.hpp>

#include <climits>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			template <typename T, unsigned char B, int i>
			struct repeat_byte_loop;

			template <typename T, unsigned char B>
			struct repeat_byte_loop<T, B, 1> :
				kerbal::type_traits::integral_constant<T, B>
			{
			};

			template <typename T, unsigned char B, int i>
			struct repeat_byte_loop :
				kerbal::type_traits::integral_constant<
					T,
					(repeat_byte_loop<T, B, i - 1>::value << CHAR_BIT) + B
				>
			{
			};

		} // namespace detail

		template <typename T, unsigned char B>
		struct repeat_byte :
			detail::repeat_byte_loop<T, B, sizeof(T)>
		{
		};

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_REPEAT_BYTE_HPP
