/**
 * @file       countl_zero.plain.part.hpp
 * @brief
 * @date       2024-04-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_DETAIL_COUNTL_ZERO_COUNTL_ZERO_PLAIN_PART_HPP
#define KERBAL_NUMERIC_BIT_DETAIL_COUNTL_ZERO_COUNTL_ZERO_PLAIN_PART_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace plain
			{

				template <typename Unsigned>
				KERBAL_CONSTEXPR14
				int countl_zero(Unsigned x) KERBAL_NOEXCEPT
				{
					KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "x should be unsigned");
					typedef kerbal::type_traits::integral_constant<int, CHAR_BIT * sizeof(x)> DIGIT;
					typedef kerbal::type_traits::integral_constant<Unsigned, (static_cast<Unsigned>(1u) << (DIGIT::value - 1)) - 1> MASK;
//					std::cout << MASK::value << std::endl;
					int i = 0;
					while (i < DIGIT::value) {
//						std::cout << "*" << (x | MASK::value) << std::endl;
						if ((x | MASK::value) != MASK::value) {
							break;
						}
//						std::cout << "*" << x << std::endl;
						x <<= 1;
						++i;
					}
					return i;
				}

			} // namespace plain

		} // namespace detail

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_DETAIL_COUNTL_ZERO_COUNTL_ZERO_PLAIN_PART_HPP
