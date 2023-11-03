/**
 * @file       is_assignable.sfinae.part.hpp
 * @brief
 * @date       2023-05-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_IS_ASSIGNABLE_SFINAE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_IS_ASSIGNABLE_SFINAE_PART_HPP

#ifndef KERBAL_HAS_IS_ASSIGNABLE_SUPPORT

#if __cplusplus >= 201103L
#	define KERBAL_HAS_IS_ASSIGNABLE_SUPPORT 1
#else
#	include <kerbal/config/compiler_id.hpp>
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC
#		define KERBAL_HAS_IS_ASSIGNABLE_SUPPORT 1
#	endif
#endif



#if KERBAL_HAS_IS_ASSIGNABLE_SUPPORT

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/yes_no_type.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/add_rvalue_reference.hpp>
#else
#	include <kerbal/type_traits/add_lvalue_reference.hpp>
#	include <kerbal/type_traits/is_array.hpp>
#	include <kerbal/type_traits/is_function.hpp>
#	include <kerbal/type_traits/is_reference.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

#	if __cplusplus >= 201103L

			template <typename T>
			struct is_assignable_compat_declval
			{
					static
					typename kerbal::type_traits::add_rvalue_reference<T>::type
					decl();
			};

#	else
			// under C++98, return type of kerbal::utility::declval<T>() will be added with lvalue reference

			template <typename T, bool>
			struct is_assignable_compat_declval_helper;

			template <typename T>
			struct is_assignable_compat_declval_helper<T, false>
			{
					static T decl();
			};

			template <typename T>
			struct is_assignable_compat_declval_helper<T, true>
			{
					static
					typename kerbal::type_traits::add_lvalue_reference<T>::type
					decl();
			};

			template <typename T>
			struct is_assignable_compat_declval :
					is_assignable_compat_declval_helper<
						T,
						kerbal::type_traits::is_array<T>::value ||
						kerbal::type_traits::is_function<T>::value ||
						kerbal::type_traits::is_reference<T>::value
					>
			{
			};

#	endif

			template <typename T, typename U>
			struct is_assignable_helper
			{
				private:

					template <typename T2, typename U2>
					static kerbal::type_traits::no_type test(...);

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC

					template <typename T2, typename U2>
					static kerbal::type_traits::yes_type test(char(*)[sizeof(
							is_assignable_compat_declval<T2>::decl() = is_assignable_compat_declval<U2>::decl(),
							0
					)]);

#else

					template <typename T2, typename U2>
					static kerbal::type_traits::yes_type test(char *, decltype(
							is_assignable_compat_declval<T2>::decl() = is_assignable_compat_declval<U2>::decl(),
							0
					) = 0);

#endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<T, U>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;
			};

		} // namespace detail

		template <typename T, typename U>
		struct is_assignable :
				kerbal::type_traits::detail::is_assignable_helper<T, U>::type
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_HAS_IS_ASSIGNABLE_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_ASSIGNABLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_IS_ASSIGNABLE_SFINAE_PART_HPP
