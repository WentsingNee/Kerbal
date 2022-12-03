/**
 * @file       xmod.hpp
 * @brief
 * @date       2024-04-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_XMOD_HPP
#define KERBAL_SMATH_XMOD_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename ResultType, ResultType Mod, bool /* Mod == 0 */>
			struct xmod_helper;

			template <typename ResultType, ResultType Mod>
			struct xmod_helper<ResultType, Mod, true>
			{
					KERBAL_CONSTEXPR
					static
					ResultType f(ResultType x) KERBAL_NOEXCEPT
					{
						return x;
					}
			};

			template <typename ResultType, ResultType Mod>
			struct xmod_helper<ResultType, Mod, false>
			{
					KERBAL_CONSTEXPR
					static
					ResultType f(ResultType x) KERBAL_NOEXCEPT
					{
						return x % Mod;
					}
			};

		} // namespace detail


		template <typename ResultType, ResultType Mod>
		struct xmod :
			kerbal::smath::detail::xmod_helper<
				ResultType, Mod,
				Mod == 0
			>
		{
		};

	} // namespace smath

} // namespace kerbal

#endif // KERBAL_SMATH_XMOD_HPP
