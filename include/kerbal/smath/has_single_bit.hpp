/**
 * @file       has_single_bit.hpp
 * @brief
 * @date       2024-03-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_HAS_SINGLE_BIT_HPP
#define KERBAL_SMATH_HAS_SINGLE_BIT_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>


namespace kerbal
{

	namespace smath
	{

		template <typename Unsigned, Unsigned x>
		struct has_single_bit :
				kerbal::type_traits::bool_constant<
					x != 0 && ((x & (x - 1)) == 0)
				>
		{
			private:
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "Type should be unsigned");
		};

	} // namespace smath

} // namespace kerbal

#endif // KERBAL_SMATH_HAS_SINGLE_BIT_HPP
