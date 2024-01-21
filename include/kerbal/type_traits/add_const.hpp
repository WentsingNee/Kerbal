/**
 * @file       add_const.hpp
 * @brief
 * @date       2022-10-24
 * @author     Peter
 * @remark     split up from kerbal/type_traits/const_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_ADD_CONST_HPP
#define KERBAL_TYPE_TRAITS_ADD_CONST_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>


KERBAL_MODULE_GLOBAL


KERBAL_EXPORT_MODULE_DECLARE(kerbal.type_traits.add_const)


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct add_const
		{
				typedef const T type;
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_ADD_CONST_HPP
