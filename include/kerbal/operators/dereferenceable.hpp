/**
 * @file       dereferenceable.hpp
 * @brief      
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_DEREFERENCEABLE_HPP
#define KERBAL_OPERATORS_DEREFERENCEABLE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL


#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


KERBAL_EXPORT_MODULE_DECLARE(kerbal.operators.dereferenceable)


#if KERBAL_ENABLE_MODULES

import kerbal.utility.declval;

#else

#include <kerbal/utility/declval.hpp>

#endif


namespace kerbal
{

	namespace operators
	{

		KERBAL_MODULE_EXPORT
		template <typename T, typename Ptr>
		struct dereferenceable
		{
				KERBAL_CONSTEXPR14
				Ptr operator->() const
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							&(*static_cast<const T &>(*
								kerbal::utility::declthis<const dereferenceable>()
							))
						)
					)
				{
					return &(*static_cast<const T &>(*this));
				}
		};

	} // namespace operators

} // namespace kerbal

#endif // KERBAL_OPERATORS_DEREFERENCEABLE_HPP
