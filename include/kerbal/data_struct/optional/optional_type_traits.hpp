/*
 * optional_type_traits.hpp
 *
 *  Created on: 2018年10月28日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP_

#include <kerbal/type_traits/type_traits.hpp>

namespace std
{
	template <typename Type>
	class optional;

	struct nullopt_t;

	template <typename Type>
	class hash;

}

namespace boost
{
	template <typename Type>
	class optional;

	class none_t;
}


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

		///@private
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
		struct is_boost_optional: __is_boost_optional_helper<typename kerbal::type_traits::remove_cvref<Type>::type>
		{
		};

		template <typename Type>
		struct is_optional: kerbal::type_traits::conditional<
				is_kerbal_optional<Type>::value || is_std_optional<Type>::value || is_boost_optional<Type>::value,
				kerbal::type_traits::true_type,
				kerbal::type_traits::false_type
			>::type
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
		struct std_optional_traits;

		template <typename Type>
		struct std_optional_traits<std::optional<Type> >
		{
				typedef typename std::optional<Type>::value_type value_type;
				typedef typename std::optional<Type>::reference reference;
				typedef typename std::optional<Type>::const_reference const_reference;
				typedef typename std::optional<Type>::pointer pointer;
				typedef typename std::optional<Type>::const_pointer const_pointer;

#	if __cplusplus >= 201103L
				typedef Type&& rvalue_reference;
				typedef const Type&& const_rvalue_reference;
#	endif

		};

		template <typename Type>
		struct boost_optional_traits;

		template <typename Type>
		struct boost_optional_traits<std::optional<Type> >
		{
				typedef typename boost::optional<Type>::value_type value_type;
				typedef typename boost::optional<Type>::reference reference;
				typedef typename boost::optional<Type>::const_reference const_reference;
				typedef typename boost::optional<Type>::pointer pointer;
				typedef typename boost::optional<Type>::const_pointer const_pointer;

#	if __cplusplus >= 201103L
				typedef Type&& rvalue_reference;
				typedef const Type&& const_rvalue_reference;
#	endif

		};

		template <typename Type>
		struct optional_traits;

		template <typename Type>
		struct optional_traits<kerbal::data_struct::optional<Type> > : public kerbal_optional_traits<kerbal::data_struct::optional<Type> >
		{
		};

		template <typename Type>
		struct optional_traits<std::optional<Type> > : public std_optional_traits<std::optional<Type> >
		{
		};

		template <typename Type>
		struct optional_traits<boost::optional<Type> > : public boost_optional_traits<boost::optional<Type> >
		{
		};

	} /* namespace data_struct */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_TYPE_TRAITS_HPP_ */
