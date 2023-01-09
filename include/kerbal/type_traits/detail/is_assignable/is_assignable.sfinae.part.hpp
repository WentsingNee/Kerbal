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

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC || __cplusplus >= 201103L

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_reference.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/yes_no_type.hpp>
#include <kerbal/utility/declval.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T, typename U>
			struct is_assignable_helper
			{
				private:
					template <typename T2, typename U2>
					static kerbal::type_traits::no_type test(...);

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC

					template <typename T2, typename U2>
					static kerbal::type_traits::yes_type test(char(*)[sizeof(
							kerbal::utility::declval<T2>() = kerbal::utility::declval<U2>(),
							0
					)]);

#else

					template <typename T2, typename U2>
					static kerbal::type_traits::yes_type test(char *, decltype(
							kerbal::utility::declval<T2>() = kerbal::utility::declval<U2>(),
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
				kerbal::type_traits::conjunction<
					kerbal::type_traits::is_reference<T>,
					typename kerbal::type_traits::detail::is_assignable_helper<T, U>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#define KERBAL_HAS_IS_ASSIGNABLE_SUPPORT 1

#endif // #if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC || __cplusplus >= 201103L

#endif // #ifndef KERBAL_HAS_IS_ASSIGNABLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_IS_ASSIGNABLE_SFINAE_PART_HPP
