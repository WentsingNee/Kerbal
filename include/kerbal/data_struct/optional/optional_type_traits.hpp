/*
 * optional_type_traits.hpp
 *
 *  Created on: 2018年10月28日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP_

#include <kerbal/data_struct/optional/optional_settings.hpp>
#include <kerbal/type_traits/type_traits_details/conditional.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>

#if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL==1
#	include <kerbal/data_struct/optional/std_optional_type_traits.hpp>
#endif

#if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL==1
#	include <kerbal/data_struct/optional/boost_optional_type_traits.hpp>
#endif

namespace kerbal
{
	namespace data_struct
	{
		template <typename>
		struct optional;

		///@private
		template <typename Type>
		struct __is_kerbal_optional_helper: kerbal::type_traits::false_type
		{
		};

		///@private
		template <typename Type>
		struct __is_kerbal_optional_helper<kerbal::data_struct::optional<Type> > : kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_kerbal_optional: __is_kerbal_optional_helper<typename kerbal::type_traits::remove_cvref<Type>::type>
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
		struct kerbal_optional_traits<kerbal::data_struct::optional<Type> >
		{
				typedef typename kerbal::data_struct::optional<Type>::value_type value_type;
				typedef typename kerbal::data_struct::optional<Type>::reference reference;
				typedef typename kerbal::data_struct::optional<Type>::const_reference const_reference;
				typedef typename kerbal::data_struct::optional<Type>::pointer pointer;
				typedef typename kerbal::data_struct::optional<Type>::const_pointer const_pointer;

#	if __cplusplus >= 201103L
				typedef typename kerbal::data_struct::optional<Type>::rvalue_reference rvalue_reference;
				typedef typename kerbal::data_struct::optional<Type>::const_rvalue_reference const_rvalue_reference;
#	endif

		};

		template <typename Type>
		struct optional_traits;

		template <typename Type>
		struct optional_traits<kerbal::data_struct::optional<Type> > : public kerbal::data_struct::kerbal_optional_traits<kerbal::data_struct::optional<Type> >
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

	} /* namespace data_struct */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP_ */
