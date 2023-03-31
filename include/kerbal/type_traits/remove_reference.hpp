/**
 * @file       remove_reference.hpp
 * @brief
 * @date       2022-10-29
 * @author     Peter
 * @remark     split up from kerbal/type_traits/reference_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REMOVE_REFERENCE_HPP
#define KERBAL_TYPE_TRAITS_REMOVE_REFERENCE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct remove_reference
		{
			typedef T type;
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct remove_reference<T &>
		{
			typedef T type;
		};

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct remove_reference<T &&>
		{
				typedef T type;
		};

#	endif

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_REMOVE_REFERENCE_HPP
