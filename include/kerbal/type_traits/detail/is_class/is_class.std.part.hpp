/**
 * @file       is_class.std.part.hpp
 * @brief
 * @date       2023-04-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_CLASS_IS_CLASS_STD_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_CLASS_IS_CLASS_STD_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_CLASS

#if __cplusplus >= 201103L
#	define KERBAL_SUPPORTS_IS_CLASS 1
#endif



#if KERBAL_SUPPORTS_IS_CLASS

#include <kerbal/type_traits/integral_constant.hpp>

#include <type_traits>


#if KERBAL_TYPE_TRAITS_DEBUG_WARNING

#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "can not detect the builtin is_class function, <type_traits> header has been included")
#	else
#		warning "Kerbal Warning: " "can not detect the builtin is_class function, <type_traits> header has been included"
#	endif

#endif


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_class :
			kerbal::type_traits::bool_constant<std::is_class<T>::value>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_CLASS

#endif // #ifndef KERBAL_SUPPORTS_IS_CLASS

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_CLASS_IS_CLASS_STD_PART_HPP
