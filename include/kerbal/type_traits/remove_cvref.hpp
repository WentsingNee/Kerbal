/**
 * @file       remove_cvref.hpp
 * @brief
 * @date       2022-10-24
 * @remark     split up from kerbal/type_traits/cv_deduction.hpp, 2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REMOVE_CVREF_HPP
#define KERBAL_TYPE_TRAITS_REMOVE_CVREF_HPP

#include <kerbal/type_traits/remove_cv.hpp>
#include <kerbal/type_traits/remove_reference.hpp>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct remove_cvref :
				kerbal::type_traits::remove_cv<
					typename kerbal::type_traits::remove_reference<T>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_REMOVE_CVREF_HPP
