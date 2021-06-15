/**
 * @file       reference_deduction.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REFERENCE_DEDUCTION_HPP
#define KERBAL_TYPE_TRAITS_REFERENCE_DEDUCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>

namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T, typename = kerbal::type_traits::void_type<>::type>
			struct is_referenceable_helper : kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct is_referenceable_helper<T, typename kerbal::type_traits::void_type<T&>::type> :
					kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		MODULE_EXPORT
		template <typename T>
		struct is_referenceable : kerbal::type_traits::detail::is_referenceable_helper<T>
		{
		};

		MODULE_EXPORT
		template <typename>
		struct is_lvalue_reference : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_lvalue_reference<Tp&> : kerbal::type_traits::true_type
		{
		};

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		template <typename>
		struct is_rvalue_reference : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_rvalue_reference<Tp&&> : kerbal::type_traits::true_type
		{
		};

#	endif

#	if __cplusplus < 201103L

		template <typename Tp>
		struct is_reference : kerbal::type_traits::is_lvalue_reference<Tp>
		{
		};

#	else

		MODULE_EXPORT
		template <typename Tp>
		struct is_reference : kerbal::type_traits::bool_constant<
											kerbal::type_traits::is_lvalue_reference<Tp>::value ||
											kerbal::type_traits::is_rvalue_reference<Tp>::value
									>
		{
		};

#	endif

		MODULE_EXPORT
		template <typename Tp>
		struct remove_reference
		{
			typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_reference<Tp&>
		{
			typedef Tp type;
		};

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		template <typename Tp>
		struct remove_reference<Tp&&>
		{
				typedef Tp type;
		};

#	endif

		MODULE_EXPORT
		/// add_lvalue_reference
		template <typename Tp>
		struct add_lvalue_reference
		{
				typedef Tp& type;
		};

		MODULE_EXPORT
		/// add_lvalue_reference
		template <typename Tp>
		struct add_lvalue_reference<Tp&>
		{
				typedef Tp& type;
		};

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		/// add_rvalue_reference
		template <typename Tp>
		struct add_rvalue_reference
		{
				typedef Tp&& type;
		};

		MODULE_EXPORT
		/// add_rvalue_reference
		template <typename Tp>
		struct add_const_rvalue_reference
		{
				typedef const Tp&& type;
		};

#	endif

		MODULE_EXPORT
		/// add_const_lvalue_reference
		template <typename Tp>
		struct add_const_lvalue_reference
		{
				typedef const Tp& type;
		};

		MODULE_EXPORT
		/// add_const_lvalue_reference
		template <typename Tp>
		struct add_const_lvalue_reference<Tp&>
		{
				typedef Tp& type;
		};

		MODULE_EXPORT
		template <typename From, typename To>
		struct copy_lvalue_reference:
					kerbal::type_traits::conditional<
						kerbal::type_traits::is_lvalue_reference<From>::value,
						typename kerbal::type_traits::add_lvalue_reference<To>::type,
						To
					>
		{
		};

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		template <typename From, typename To>
		struct copy_rvalue_reference:
				kerbal::type_traits::conditional<
						kerbal::type_traits::is_rvalue_reference<From>::value,
						kerbal::type_traits::add_rvalue_reference<To>,
						To
				>
		{
		};

#	endif

//		MODULE_EXPORT
//		template <typename From, typename To>
//		struct copy_const_lvalue_reference:
//				kerbal::type_traits::conditional<
//						kerbal::type_traits::is_const_lvalue_reference<From>::value,
//						kerbal::type_traits::add_const_lvalue_reference<To>,
//						To
//				>
//		{
//		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_REFERENCE_DEDUCTION_HPP
