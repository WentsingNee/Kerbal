/**
 * @file       iterator_traits.hpp
 * @brief
 * @date       2019-5-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_ITERATOR_TRAITS_HPP
#define KERBAL_ITERATOR_ITERATOR_TRAITS_HPP

#include <iterator>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>
#include <kerbal/type_traits/type_traits_details/void_type.hpp>

#include <kerbal/ts/modules_ts/modules_ts.hpp>

namespace kerbal
{

	namespace iterator
	{

		template <typename, typename = kerbal::type_traits::void_type<>::type >
		struct __iterator_traits_helper
		{
		};

		template <typename Iterator>
		struct __iterator_traits_helper<
				Iterator,
				typename kerbal::type_traits::void_type<
					typename Iterator::iterator_category,
					typename Iterator::value_type,
					typename Iterator::difference_type,
					typename Iterator::pointer,
					typename Iterator::reference
				>::type
			>
		{
				typedef typename Iterator::iterator_category	iterator_category;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
		};

		MODULE_EXPORT
		template <typename Iterator>
		struct iterator_traits: kerbal::iterator::__iterator_traits_helper<Iterator>
		{
		};

		MODULE_EXPORT
		/// Partial specialization for pointer types.
		template <typename Tp>
		struct iterator_traits<Tp*>
		{
				typedef std::random_access_iterator_tag		iterator_category;
				typedef Tp									value_type;
				typedef std::ptrdiff_t						difference_type;
				typedef Tp*									pointer;
				typedef Tp&									reference;
		};

		MODULE_EXPORT
		/// Partial specialization for const pointer types.
		template <typename Tp>
		struct iterator_traits<const Tp*>
		{
				typedef std::random_access_iterator_tag		iterator_category;
				typedef Tp									value_type;
				typedef std::ptrdiff_t						difference_type;
				typedef const Tp*							pointer;
				typedef const Tp&							reference;
		};



		template <typename, typename = kerbal::type_traits::void_type<>::type >
		struct __is_iterator_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_iterator_helper<
				Tp,
				typename kerbal::type_traits::void_type<
					typename kerbal::iterator::iterator_traits<Tp>::iterator_category,
					typename kerbal::iterator::iterator_traits<Tp>::value_type,
					typename kerbal::iterator::iterator_traits<Tp>::difference_type,
					typename kerbal::iterator::iterator_traits<Tp>::pointer,
					typename kerbal::iterator::iterator_traits<Tp>::reference
				>::type
			>
			: kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_iterator: kerbal::iterator::__is_iterator_helper<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};



		template <typename>
		struct __is_output_iterator_impl: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_output_iterator_impl<std::output_iterator_tag>: kerbal::type_traits::true_type
		{
		};

		template <typename, typename = kerbal::type_traits::void_type<>::type >
		struct __is_output_iterator_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_output_iterator_helper<
				Tp,
				typename kerbal::type_traits::void_type<
					typename kerbal::iterator::iterator_traits<Tp>::iterator_category
				>::type
			>
			: kerbal::iterator::__is_output_iterator_impl<typename kerbal::iterator::iterator_traits<Tp>::iterator_category>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_output_iterator: kerbal::iterator::__is_output_iterator_helper<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};



		template <typename>
		struct __is_input_iterator_impl: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_input_iterator_impl<std::input_iterator_tag>: kerbal::type_traits::true_type
		{
		};

		template <typename, typename = kerbal::type_traits::void_type<>::type >
		struct __is_input_iterator_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_input_iterator_helper<
				Tp,
				typename kerbal::type_traits::void_type<
					typename kerbal::iterator::iterator_traits<Tp>::iterator_category
				>::type
			>
			: kerbal::iterator::__is_input_iterator_impl<typename kerbal::iterator::iterator_traits<Tp>::iterator_category>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_input_iterator: kerbal::iterator::__is_input_iterator_helper<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};



		template <typename>
		struct __is_forward_iterator_impl: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_forward_iterator_impl<std::forward_iterator_tag>: kerbal::type_traits::true_type
		{
		};

		template <typename, typename = kerbal::type_traits::void_type<>::type >
		struct __is_forward_iterator_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_forward_iterator_helper<
				Tp,
				typename kerbal::type_traits::void_type<
					typename kerbal::iterator::iterator_traits<Tp>::iterator_category
				>::type
			>
			: kerbal::iterator::__is_forward_iterator_impl<typename kerbal::iterator::iterator_traits<Tp>::iterator_category>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_forward_iterator: kerbal::iterator::__is_forward_iterator_helper<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};



		template <typename>
		struct __is_bidirectional_iterator_impl: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_bidirectional_iterator_impl<std::bidirectional_iterator_tag>: kerbal::type_traits::true_type
		{
		};

		template <typename, typename = kerbal::type_traits::void_type<>::type >
		struct __is_bidirectional_iterator_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_bidirectional_iterator_helper<
				Tp,
				typename kerbal::type_traits::void_type<
					typename kerbal::iterator::iterator_traits<Tp>::iterator_category
				>::type
			>
			: kerbal::iterator::__is_bidirectional_iterator_impl<typename kerbal::iterator::iterator_traits<Tp>::iterator_category>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_bidirectional_iterator: kerbal::iterator::__is_bidirectional_iterator_helper<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};



		template <typename>
		struct __is_random_access_iterator_impl: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_random_access_iterator_impl<std::random_access_iterator_tag>: kerbal::type_traits::true_type
		{
		};

		template <typename, typename = kerbal::type_traits::void_type<>::type >
		struct __is_random_access_iterator_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_random_access_iterator_helper<
				Tp,
				typename kerbal::type_traits::void_type<
					typename kerbal::iterator::iterator_traits<Tp>::iterator_category
				>::type
			>
			: kerbal::iterator::__is_random_access_iterator_impl<typename kerbal::iterator::iterator_traits<Tp>::iterator_category>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_random_access_iterator: kerbal::iterator::__is_random_access_iterator_helper<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};



		MODULE_EXPORT
		template <typename Tp>
		struct is_random_access_compatible_iterator: kerbal::iterator::is_random_access_iterator<Tp>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_birectional_compatible_iterator:
				kerbal::type_traits::conditional_boolean<
					kerbal::iterator::is_random_access_compatible_iterator<Tp>::value ||
					kerbal::iterator::is_bidirectional_iterator<Tp>::value
				>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_forward_compatible_iterator:
				kerbal::type_traits::conditional_boolean<
					kerbal::iterator::is_birectional_compatible_iterator<Tp>::value ||
					kerbal::iterator::is_forward_iterator<Tp>::value
				>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_input_compatible_iterator:
				kerbal::type_traits::conditional_boolean<
					kerbal::iterator::is_forward_compatible_iterator<Tp>::value ||
					kerbal::iterator::is_input_iterator<Tp>::value
				>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		inline
		KERBAL_CONSTEXPR
		typename kerbal::iterator::iterator_traits<Tp>::iterator_category
		iterator_category(const Tp&)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(typename kerbal::iterator::iterator_traits<Tp>::iterator_category()))
		{
			return typename kerbal::iterator::iterator_traits<Tp>::iterator_category();
		}

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_ITERATOR_TRAITS_HPP
