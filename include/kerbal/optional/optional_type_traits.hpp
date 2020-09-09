/**
 * @file       optional_type_traits.hpp
 * @brief
 * @date       2018-10-28
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP_
#define KERBAL_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP_

#include <kerbal/optional/optional_settings.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL==1
#	include <kerbal/optional/std_optional_type_traits.hpp>
#endif

#if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL==1
#	include <kerbal/optional/boost_optional_type_traits.hpp>
#endif

namespace kerbal
{
	namespace optional
	{
		template <typename>
		class optional;

		///@private
		template <typename Type>
		struct __is_kerbal_optional_helper: kerbal::type_traits::false_type
		{
		};

		///@private
		template <typename Type>
		struct __is_kerbal_optional_helper<kerbal::optional::optional<Type> > : kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_kerbal_optional: __is_kerbal_optional_helper<typename kerbal::type_traits::remove_cv<Type>::type>
		{
		};

		template <typename Type>
		struct is_optional: kerbal::type_traits::conditional_boolean<
					is_kerbal_optional<Type>::value
#	if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL==1
					|| is_std_optional<Type>::value
#	endif
#	if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL==1
					|| is_boost_optional<Type>::value
#	endif
			>
		{
		};


		template <typename Type>
		struct kerbal_optional_traits;

		template <typename Type>
		struct kerbal_optional_traits<kerbal::optional::optional<Type> >
		{
				typedef typename kerbal::optional::optional<Type>::value_type value_type;
				typedef typename kerbal::optional::optional<Type>::reference reference;
				typedef typename kerbal::optional::optional<Type>::const_reference const_reference;
				typedef typename kerbal::optional::optional<Type>::pointer pointer;
				typedef typename kerbal::optional::optional<Type>::const_pointer const_pointer;

#	if __cplusplus >= 201103L
				typedef typename kerbal::optional::optional<Type>::rvalue_reference rvalue_reference;
				typedef typename kerbal::optional::optional<Type>::const_rvalue_reference const_rvalue_reference;
#	endif

		};

		template <typename Type>
		struct optional_traits;

		template <typename Type>
		struct optional_traits<kerbal::optional::optional<Type> > : public kerbal::optional::kerbal_optional_traits<kerbal::optional::optional<Type> >
		{
		};

#	if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL==1
		template <typename Type>
		struct optional_traits<std::optional<Type> > : public std_optional_traits<std::optional<Type> >
		{
		};
#	endif

#	if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL==1
		template <typename Type>
		struct optional_traits<boost::optional<Type> > : public boost_optional_traits<boost::optional<Type> >
		{
		};
#	endif

	} /* namespace optional */

} /* namespace kerbal */


#endif /* KERBAL_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP_ */
