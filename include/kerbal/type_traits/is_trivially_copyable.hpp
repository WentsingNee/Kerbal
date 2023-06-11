/**
 * @file       is_trivially_copyable.hpp
 * @brief
 * @date       2023-06-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
#define KERBAL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP

#include <kerbal/type_traits/is_trivially_destructible.hpp>
#include <kerbal/type_traits/is_copy_constructible.hpp>
#include <kerbal/type_traits/is_copy_assignable.hpp>
#include <kerbal/type_traits/is_trivially_copy_constructible.hpp>
#include <kerbal/type_traits/is_trivially_copy_assignable.hpp>
#include <kerbal/type_traits/is_unbounded_array.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_move_constructible.hpp>
#	include <kerbal/type_traits/is_move_assignable.hpp>
#	include <kerbal/type_traits/is_trivially_move_constructible.hpp>
#	include <kerbal/type_traits/is_trivially_move_assignable.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T>
			struct try_test_is_trivially_copyable_helper :
					kerbal::type_traits::tribool_conjunction<
						kerbal::type_traits::try_test_is_trivially_destructible<T>,

						typename kerbal::type_traits::tribool_disjunction<
#			if __cplusplus >= 201103L
							kerbal::type_traits::try_test_is_move_constructible<T>,
							kerbal::type_traits::try_test_is_move_assignable<T>,
#			endif
							kerbal::type_traits::try_test_is_copy_constructible<T>,
							kerbal::type_traits::try_test_is_copy_assignable<T>
						>::result,

						typename kerbal::type_traits::tribool_conjunction<

#			if __cplusplus >= 201103L

							typename kerbal::type_traits::tribool_disjunction<
								typename kerbal::type_traits::tribool_negation<
									kerbal::type_traits::try_test_is_move_constructible<T>
								>::result,
								kerbal::type_traits::try_test_is_trivially_move_constructible<T>
							>::result,

							typename kerbal::type_traits::tribool_disjunction<
								typename kerbal::type_traits::tribool_negation<
									kerbal::type_traits::try_test_is_move_assignable<T>
								>::result,
								kerbal::type_traits::try_test_is_trivially_move_assignable<T>
							>::result,

#			endif

							typename kerbal::type_traits::tribool_disjunction<
								typename kerbal::type_traits::tribool_negation<
									kerbal::type_traits::try_test_is_copy_constructible<T>
								>::result,
								kerbal::type_traits::try_test_is_trivially_copy_constructible<T>
							>::result,

							typename kerbal::type_traits::tribool_disjunction<
								typename kerbal::type_traits::tribool_negation<
									kerbal::type_traits::try_test_is_copy_assignable<T>
								>::result,
								kerbal::type_traits::try_test_is_trivially_copy_assignable<T>
							>::result
						>::result
					>::result
			{
			};

		} // namespace detail


		template <typename T>
		struct try_test_is_trivially_copyable :
				kerbal::type_traits::tribool_conjunction<
					kerbal::type_traits::negation<
						kerbal::type_traits::is_unbounded_array<T>
					>,
					kerbal::type_traits::detail::try_test_is_trivially_copyable_helper<
						typename kerbal::type_traits::remove_all_extents<T>::type
					>
				>::result
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
