/**
 * @file       type_traits.hpp
 * @brief
 * @date       2018-6-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP
#define KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#ifdef KERBAL_ENABLE_CLANGPP_MODULES

export module kerbal.type_traits;
export namespace kerbal
{
	namespace type_traits
	{

	}
}

#endif


#include <kerbal/type_traits/type_traits_details/array_traits.hpp>
#include <kerbal/type_traits/type_traits_details/batch_traits.hpp>
#include <kerbal/type_traits/type_traits_details/conditional.hpp>
#include <kerbal/type_traits/type_traits_details/const_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/decay.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/function_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/fundamental_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>
#include <kerbal/type_traits/type_traits_details/is_same.hpp>
#include <kerbal/type_traits/type_traits_details/logical.hpp>
#include <kerbal/type_traits/type_traits_details/member_pointer_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/pointer_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/reference_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/void_type.hpp>
#include <kerbal/type_traits/type_traits_details/volatile_deduction.hpp>

namespace kerbal
{
	namespace type_traits
	{

	}
}

#endif // KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP
