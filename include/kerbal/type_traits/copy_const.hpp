/**
 * @file       copy_const.hpp
 * @brief
 * @date       2022-10-24
 * @author     Peter
 * @remark     split up from kerbal/type_traits/const_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_COPY_CONST_HPP
#define KERBAL_TYPE_TRAITS_COPY_CONST_HPP

#include <kerbal/type_traits/add_const.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_const.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename From, typename To>
		struct copy_const :
			kerbal::type_traits::conditional<
				kerbal::type_traits::is_const<From>::value,
				typename kerbal::type_traits::add_const<To>::type,
				To
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_COPY_CONST_HPP
