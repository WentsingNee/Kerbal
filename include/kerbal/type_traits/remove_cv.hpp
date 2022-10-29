/**
 * @file       remove_cv.hpp
 * @brief
 * @date       2022-10-24
 * @author     Peter
 * @remark     split up from kerbal/type_traits/cv_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REMOVE_CV_HPP
#define KERBAL_TYPE_TRAITS_REMOVE_CV_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/remove_const.hpp>
#include <kerbal/type_traits/remove_volatile.hpp>


namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename T>
		struct remove_cv :
				kerbal::type_traits::remove_const<
					typename kerbal::type_traits::remove_volatile<T>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_REMOVE_CV_HPP
