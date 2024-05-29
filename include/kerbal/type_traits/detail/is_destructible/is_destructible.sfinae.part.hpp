/**
 * @file       is_destructible.sfinae.part.hpp
 * @brief
 * @date       2023-05-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_DESTRUCTIBLE_IS_DESTRUCTIBLE_SFINAE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_DESTRUCTIBLE_IS_DESTRUCTIBLE_SFINAE_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_DESTRUCTIBLE

#if __cplusplus >= 201103L
#	define KERBAL_SUPPORTS_IS_DESTRUCTIBLE 1
#else
#	include <kerbal/config/compiler_id.hpp>
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC
#		define KERBAL_SUPPORTS_IS_DESTRUCTIBLE 1
#	endif
#endif


#if KERBAL_SUPPORTS_IS_DESTRUCTIBLE

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_function.hpp>
#include <kerbal/type_traits/is_reference.hpp>
#include <kerbal/type_traits/is_unbounded_array.hpp>
#include <kerbal/type_traits/is_void.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>
#include <kerbal/type_traits/yes_no_type.hpp>
#include <kerbal/utility/declval.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T>
			struct is_destructible_helper
			{
				private:
					template <typename T2>
					static kerbal::type_traits::no_type test(...);

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC

					template <typename T2>
					static kerbal::type_traits::yes_type test(char(*)[sizeof(
						kerbal::utility::declval<T2 *>()->~T2(),
						0
					)]);

#else

					template <typename T2>
					static kerbal::type_traits::yes_type test(char *, decltype(
						kerbal::utility::declval<T2 *>()->~T2(),
						0
					) = 0);

#endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<T>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;
			};

		} // namespace detail

		template <typename T>
		struct is_destructible :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::negation<
					kerbal::type_traits::disjunction<
						kerbal::type_traits::is_function<T>,
						kerbal::type_traits::is_unbounded_array<T>,
						kerbal::type_traits::is_void<T>
					>
				>,
				kerbal::type_traits::disjunction<
					kerbal::type_traits::is_reference<T>,
					typename kerbal::type_traits::detail::is_destructible_helper<
						typename kerbal::type_traits::remove_all_extents<T>::type
					>::type
				>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_DESTRUCTIBLE

#endif // #ifndef KERBAL_SUPPORTS_IS_DESTRUCTIBLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_DESTRUCTIBLE_IS_DESTRUCTIBLE_SFINAE_PART_HPP
