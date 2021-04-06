/**
 * @file       type_traits.hpp
 * @brief
 * @date       2018-06-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP
#define KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#if KERBAL_ENABLE_MODULES

export module kerbal.type_traits;

#endif


#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/batch_traits.hpp>
#include <kerbal/type_traits/can_be_empty_base.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/const_deduction.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/decay.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/function_deduction.hpp>
#include <kerbal/type_traits/fundamental_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/member_pointer_deduction.hpp>
#include <kerbal/type_traits/pointer_deduction.hpp>
#include <kerbal/type_traits/reference_deduction.hpp>
#include <kerbal/type_traits/type_chooser.hpp>
#include <kerbal/type_traits/void_type.hpp>
#include <kerbal/type_traits/volatile_deduction.hpp>

#endif // KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP
