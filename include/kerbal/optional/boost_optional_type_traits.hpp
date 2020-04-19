/**
 * @file       boost_optional_type_traits.hpp
 * @brief
 * @date       2019-5-5
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_BOOST_OPTIONAL_TYPE_TRAITS_HPP_
#define KERBAL_OPTIONAL_BOOST_OPTIONAL_TYPE_TRAITS_HPP_

#include <kerbal/optional/optional_settings.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>

#if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL==1

namespace kerbal
{
	namespace optional
	{

		///@private
		template <typename Type>
		struct __is_boost_optional_helper: kerbal::type_traits::false_type
		{
		};

		///@private
		template <typename Type>
		struct __is_boost_optional_helper<boost::optional<Type> > : kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_boost_optional: __is_boost_optional_helper<typename kerbal::type_traits::remove_cv<Type>::type>
		{
		};

		template <typename Type>
		struct boost_optional_traits;

		template <typename Type>
		struct boost_optional_traits<boost::optional<Type> >
		{
				typedef typename boost::optional<Type>::value_type value_type;
				typedef typename boost::optional<Type>::reference reference;
				typedef typename boost::optional<Type>::const_reference const_reference;
				typedef typename boost::optional<Type>::pointer pointer;
				typedef typename boost::optional<Type>::const_pointer const_pointer;

#			if __cplusplus >= 201103L
				typedef Type&& rvalue_reference;
				typedef const Type&& const_rvalue_reference;
#			endif

		};

	} /* namespace optional */

} /* namespace kerbal */

#endif

#endif /* KERBAL_OPTIONAL_BOOST_OPTIONAL_TYPE_TRAITS_HPP_ */
