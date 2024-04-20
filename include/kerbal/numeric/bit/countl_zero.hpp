/**
 * @file       countl_zero.hpp
 * @brief
 * @date       2024-04-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_COUNTL_ZERO_HPP
#define KERBAL_NUMERIC_BIT_COUNTL_ZERO_HPP

#include <kerbal/numeric/bit/detail/countl_zero/countl_zero.gnu_builtin.part.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			template <typename Unsigned>
			KERBAL_CONSTEXPR
			int countl_zero_sign_handler_impl(Unsigned x, kerbal::type_traits::false_type) KERBAL_NOEXCEPT
			{
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "x should be unsigned");
				return kerbal::numeric::detail::gnu_builtin::countl_zero(x);
			}

			template <typename Signed>
			KERBAL_CONSTEXPR
			int countl_zero_sign_handler_impl(Signed x, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
			{
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_signed<Signed>::value, "x should be signed");
				typedef typename kerbal::type_traits::make_unsigned<Signed>::type unsigned_t;
				return countl_zero_sign_handler_impl(static_cast<unsigned_t>(x), kerbal::type_traits::false_type());
			}

			template <typename T>
			KERBAL_CONSTEXPR
			int countl_zero_sign_handler(T x) KERBAL_NOEXCEPT
			{
				return countl_zero_sign_handler_impl(x, kerbal::type_traits::is_signed<T>());
			}

		} // namespace detail


		template <typename T>
		KERBAL_CONSTEXPR
		int countl_zero(T x) KERBAL_NOEXCEPT
		{
			return kerbal::numeric::detail::countl_zero_sign_handler(x);
		}

	} // namespace numeric

} // namespace kerbal

#endif // KERBAL_NUMERIC_BIT_COUNTL_ZERO_HPP
