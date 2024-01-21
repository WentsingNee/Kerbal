/**
 * @file       add_cv.hpp
 * @brief
 * @date       2022-10-24
 * @author     Peter
 * @remark     split up from kerbal/type_traits/cv_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_ADD_CV_HPP
#define KERBAL_TYPE_TRAITS_ADD_CV_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL


KERBAL_EXPORT_MODULE_DECLARE(kerbal.type_traits.add_cv)


#if KERBAL_ENABLE_MODULES

import kerbal.type_traits.add_const;
import kerbal.type_traits.add_volatile;

#else

#include <kerbal/type_traits/add_const.hpp>
#include <kerbal/type_traits/add_volatile.hpp>

#endif


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct add_cv :
			kerbal::type_traits::add_const<
				typename kerbal::type_traits::add_volatile<T>::type
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_ADD_CV_HPP
