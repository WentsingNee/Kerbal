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

#include <kerbal/config/modules/modules.hpp>

#if KERBAL_ENABLE_MODULES
module;
#endif


#include <kerbal/config/modules/include_header_begin.part.hpp>

#include <kerbal/type_traits/add_const.hpp>
#include <kerbal/type_traits/add_volatile.hpp>


#include <kerbal/config/modules/include_header_end.part.hpp>


#if KERBAL_ENABLE_MODULES
export module kerbal.type_traits.add_cv;
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
