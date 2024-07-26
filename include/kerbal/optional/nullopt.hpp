/**
 * @file       nullopt.hpp
 * @brief
 * @date       2018-10-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_NULLOPT_HPP
#define KERBAL_OPTIONAL_NULLOPT_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/less_than_comparable.hpp>


namespace kerbal
{

	namespace optional
	{

		KERBAL_MODULE_EXPORT
		struct nullopt_t :
			public kerbal::operators::equality_comparable<nullopt_t>,
			public kerbal::operators::less_than_comparable<nullopt_t>
		{
				KERBAL_CONSTEXPR
				bool operator==(const nullopt_t &) const KERBAL_NOEXCEPT
				{
					return true;
				}

				KERBAL_CONSTEXPR
				bool operator<(const nullopt_t &) const KERBAL_NOEXCEPT
				{
					return false;
				}
		};

#	if __cplusplus >= 201703L
		KERBAL_MODULE_EXPORT
		inline constexpr const nullopt_t nullopt{};
#	elif __cplusplus >= 201103L
		KERBAL_MODULE_EXPORT
		constexpr const nullopt_t nullopt{};
#	else
		KERBAL_MODULE_EXPORT
		static const nullopt_t nullopt;
#	endif

	} // namespace optional

} // namespace kerbal

#endif // KERBAL_OPTIONAL_NULLOPT_HPP
