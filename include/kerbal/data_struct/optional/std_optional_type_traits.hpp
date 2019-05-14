/*
 * std_optional_type_traits.hpp
 *
 *  Created on: 2019年5月5日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_STD_OPTIONAL_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_STD_OPTIONAL_TYPE_TRAITS_HPP_

#include <kerbal/data_struct/optional/optional_settings.hpp>

#if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL==1

namespace std
{
	template <typename Type>
	class optional;

	struct nullopt_t;

	template <typename Type>
	class hash;

}

namespace kerbal
{
	namespace data_struct
	{

		template <typename Type>
		struct __is_std_optional_helper: kerbal::type_traits::false_type
		{
		};

		///@private
		template <typename Type>
		struct __is_std_optional_helper<std::optional<Type> > : kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_std_optional: __is_std_optional_helper<typename kerbal::type_traits::remove_cvref<Type>::type>
		{
		};

		template <typename Type>
		struct std_optional_traits;

		template <typename Type>
		struct std_optional_traits<std::optional<Type> >
		{
				typedef typename std::optional<Type>::value_type value_type;
				typedef typename std::optional<Type>::reference reference;
				typedef typename std::optional<Type>::const_reference const_reference;
				typedef typename std::optional<Type>::pointer pointer;
				typedef typename std::optional<Type>::const_pointer const_pointer;

#		if __cplusplus >= 201103L
				typedef Type&& rvalue_reference;
				typedef const Type&& const_rvalue_reference;
#		endif

		};

	} /* namespace data_struct */

} /* namespace kerbal */

#endif

#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_STD_OPTIONAL_TYPE_TRAITS_HPP_ */
