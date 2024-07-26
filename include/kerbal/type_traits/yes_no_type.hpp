/**
 * @file       yes_no_type.hpp
 * @brief
 * @date       2023-05-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_YES_NO_TYPE_HPP
#define KERBAL_TYPE_TRAITS_YES_NO_TYPE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		struct no_type
		{
			char c[1];
		};

		KERBAL_MODULE_EXPORT
		struct yes_type
		{
			char c[2];
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_YES_NO_TYPE_HPP
