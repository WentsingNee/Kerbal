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

#include <kerbal/config/modules/modules.hpp>

#if KERBAL_ENABLE_MODULES
module;
#endif


#include <kerbal/config/modules/include_header_begin.part.hpp>
#include <kerbal/config/modules/include_header_end.part.hpp>


#if KERBAL_ENABLE_MODULES
export module kerbal.type_traits.add_const;
#endif


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
