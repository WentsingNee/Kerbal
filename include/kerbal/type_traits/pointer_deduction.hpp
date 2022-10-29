/**
 * @file       pointer_deduction.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_POINTER_DEDUCTION_HPP
#define KERBAL_TYPE_TRAITS_POINTER_DEDUCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/fundamental_deduction.hpp>
#include <kerbal/type_traits/is_referencable.hpp>
#include <kerbal/type_traits/remove_reference.hpp>
#include <kerbal/type_traits/remove_cv.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		template <typename >
		struct __is_pointer_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_pointer_helper<Tp*> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_pointer: kerbal::type_traits::__is_pointer_helper<
										typename kerbal::type_traits::remove_cv<Tp>::type
								>
		{
		};

		template <typename Tp, typename >
		struct __remove_pointer_helper
		{
				typedef Tp type;
		};

		template <typename Tp, typename Up>
		struct __remove_pointer_helper<Tp, Up*>
		{
				typedef Up type;
		};

		MODULE_EXPORT
		/// remove_pointer
		template <typename Tp>
		struct remove_pointer: __remove_pointer_helper<Tp, typename remove_cv<Tp>::type>
		{
		};



		template <typename Tp, bool is_pointer>
		struct __pointer_rank_helper;

		MODULE_EXPORT
		template <typename Tp>
		struct pointer_rank: kerbal::type_traits::__pointer_rank_helper<
				Tp,
				kerbal::type_traits::is_pointer<Tp>::value
		>
		{
		};

		template <typename Tp>
		struct __pointer_rank_helper<Tp, true>:
				kerbal::type_traits::integral_constant<
						std::size_t,
						1 + kerbal::type_traits::pointer_rank<
								typename kerbal::type_traits::remove_pointer<Tp>::type
						>::value
				>
		{
		};

		template <typename Tp>
		struct __pointer_rank_helper<Tp, false>:
				kerbal::type_traits::integral_constant<
						std::size_t,
						0
				>
		{
		};


		namespace detail
		{

			template <typename Tp, bool IsPointerable = kerbal::type_traits::is_referencable<Tp>::value || kerbal::type_traits::is_void<Tp>::value >
			struct add_pointer_helper
			{
					typedef Tp* type;
			};

			template <typename Tp>
			struct add_pointer_helper<Tp, false>
			{
					typedef Tp type;
			};

		} // namespace detail

		MODULE_EXPORT
		template <typename Tp>
		struct add_pointer:
				kerbal::type_traits::detail::add_pointer_helper<
						typename kerbal::type_traits::remove_reference<Tp>::type
				>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_all_pointers:
				kerbal::type_traits::conditional<
					kerbal::type_traits::is_pointer<Tp>::value,
					kerbal::type_traits::remove_all_pointers<
						typename kerbal::type_traits::remove_pointer<Tp>::type
					>,
					kerbal::type_traits::remove_pointer<Tp>
				>::type
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_POINTER_DEDUCTION_HPP
