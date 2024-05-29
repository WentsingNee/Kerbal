/**
 * @file       is_constructible.sfinae11.part.hpp
 * @brief
 * @date       2023-05-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_IS_CONSTRUCTIBLE_SFINAE11_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_IS_CONSTRUCTIBLE_SFINAE11_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_CONSTRUCTIBLE

#if __cplusplus >= 201103L
#	define KERBAL_SUPPORTS_IS_CONSTRUCTIBLE 1
#endif



#if KERBAL_SUPPORTS_IS_CONSTRUCTIBLE

#include <kerbal/config/compiler_id.hpp>

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_unbounded_array.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_reference.hpp>
#include <kerbal/type_traits/yes_no_type.hpp>
#include <kerbal/utility/declval.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			struct is_constructible_placement_new_helper
			{
			};

		} // namespace detail

	} // namespace type_traits

} // namespace kerbal


void * operator new(std::size_t sz, kerbal::type_traits::detail::is_constructible_placement_new_helper, void *);
void * operator new[](std::size_t sz, kerbal::type_traits::detail::is_constructible_placement_new_helper, void *);


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T, typename ... Args>
			struct is_constructible_impl
			{
				private:
					template <typename T2>
					static kerbal::type_traits::no_type test(...);

					template <typename T2>
					static kerbal::type_traits::yes_type test(char *, decltype(
						::new (
							kerbal::type_traits::detail::is_constructible_placement_new_helper(),
							kerbal::utility::declval<void *>()
						) T2(
							kerbal::utility::declval<Args>()...
						),
						0
					) = 0);

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<T>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;
			};

			template <typename T, typename ... Args>
			struct is_constructible_helper :
				is_constructible_impl<T, Args...>::type
			{
			};

			template <typename T, typename U>
			struct is_constructible_helper<T &, U> :
				is_constructible_impl<T *, typename kerbal::type_traits::remove_reference<U>::type *>::type
			{
			};

			template <typename T, typename U>
			struct is_constructible_helper<T &, U &&> :
				kerbal::type_traits::false_type
			{
			};

			template <typename T, typename ... Args>
			struct is_constructible_helper<T &, Args...> :
				kerbal::type_traits::false_type
			{
			};

			template <typename T, typename U>
			struct is_constructible_helper<T &&, U> :
				is_constructible_impl<
					T *,
					typename kerbal::type_traits::remove_reference<U>::type *
				>::type
			{
			};

			template <typename T, typename ... Args>
			struct is_constructible_helper<T &&, Args...> :
				kerbal::type_traits::false_type
			{
			};

		} // namespace detail

		template <typename T, typename ... Args>
		struct is_constructible :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::negation<
					kerbal::type_traits::is_unbounded_array<T>
				>,
				kerbal::type_traits::detail::is_constructible_helper<T, Args...>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_CONSTRUCTIBLE

#endif // #ifndef KERBAL_SUPPORTS_IS_CONSTRUCTIBLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_IS_CONSTRUCTIBLE_SFINAE11_PART_HPP
