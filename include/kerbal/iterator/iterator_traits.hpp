/**
 * @file       iterator_traits.hpp
 * @brief
 * @date       2019-5-19
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_ITERATOR_TRAITS_HPP_
#define KERBAL_ITERATOR_ITERATOR_TRAITS_HPP_

#include <iterator>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>
#include <kerbal/type_traits/type_traits_details/is_same.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/pointer_deduction.hpp>

#include <kerbal/ts/modules_ts/modules_ts.hpp>

namespace kerbal
{
	namespace iterator
	{

		// _GLIBCXX_RESOLVE_LIB_DEFECTS
		// 2408. SFINAE-friendly common_type/iterator_traits is missing in C++14
		template <typename _Iterator, typename = kerbal::type_traits::__void_type<>::type >
		struct __iterator_traits
		{
		};

		template <typename Iterator>
		struct __iterator_traits<Iterator,
			typename kerbal::type_traits::__void_type<
				typename Iterator::iterator_category,
				typename Iterator::value_type,
				typename Iterator::difference_type,
				typename Iterator::pointer,
				typename Iterator::reference
			>::type
		>
		{
				typedef typename Iterator::iterator_category iterator_category;
				typedef typename Iterator::value_type value_type;
				typedef typename Iterator::difference_type difference_type;
				typedef typename Iterator::pointer pointer;
				typedef typename Iterator::reference reference;
		};

		MODULE_EXPORT
		template <typename Iterator>
		struct iterator_traits: public __iterator_traits<Iterator>
		{
		};

		MODULE_EXPORT
		/// Partial specialization for pointer types.
		template <typename _Tp>
		struct iterator_traits<_Tp*>
		{
				typedef std::random_access_iterator_tag iterator_category;
				typedef _Tp value_type;
				typedef std::ptrdiff_t difference_type;
				typedef _Tp* pointer;
				typedef _Tp& reference;
		};

		MODULE_EXPORT
		/// Partial specialization for const pointer types.
		template <typename _Tp>
		struct iterator_traits<const _Tp*>
		{
				typedef std::random_access_iterator_tag iterator_category;
				typedef _Tp value_type;
				typedef std::ptrdiff_t difference_type;
				typedef const _Tp* pointer;
				typedef const _Tp& reference;
		};

		template <typename, typename Enable = void>
		struct __is_output_iterator: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_output_iterator<Tp,
				typename kerbal::type_traits::enable_if<
					kerbal::type_traits::is_same<
						typename kerbal::iterator::iterator_traits<Tp>::iterator_category,
						typename std::output_iterator_tag
					>::value
				>::type> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_output_iterator: __is_output_iterator<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};

		template <typename, typename Enable = void>
		struct __is_input_iterator: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_input_iterator<Tp,
				typename kerbal::type_traits::enable_if<
					kerbal::type_traits::is_same<
						typename kerbal::iterator::iterator_traits<Tp>::iterator_category,
						typename std::input_iterator_tag
					>::value
				>::type> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_input_iterator: __is_input_iterator<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};

		template <typename, typename Enable = void>
		struct __is_forward_iterator: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_forward_iterator<Tp,
				typename kerbal::type_traits::enable_if<
					kerbal::type_traits::is_same<
						typename kerbal::iterator::iterator_traits<Tp>::iterator_category,
						typename std::forward_iterator_tag
					>::value
				>::type> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_forward_iterator: __is_forward_iterator<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};

		template <typename, typename Enable = void>
		struct __is_bidirectional_iterator: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_bidirectional_iterator<Tp,
				typename kerbal::type_traits::enable_if<
					kerbal::type_traits::is_same<
						typename kerbal::iterator::iterator_traits<Tp>::iterator_category,
						typename std::bidirectional_iterator_tag
					>::value
				>::type> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_bidirectional_iterator: __is_bidirectional_iterator<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};

		template <typename, typename Enable = void>
		struct __is_random_access_iterator: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_random_access_iterator<Tp,
				typename kerbal::type_traits::enable_if<
					kerbal::type_traits::is_same<
						typename kerbal::iterator::iterator_traits<Tp>::iterator_category,
						typename std::random_access_iterator_tag
					>::value
				>::type> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_random_access_iterator: __is_random_access_iterator<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_random_access_compatible_iterator: is_random_access_iterator<Tp>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_birectional_compatible_iterator:
				kerbal::type_traits::conditional_boolean<
					is_random_access_compatible_iterator<Tp>::value ||
					is_bidirectional_iterator<Tp>::value
				>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_forward_compatible_iterator:
				kerbal::type_traits::conditional_boolean<
					is_birectional_compatible_iterator<Tp>::value ||
					is_forward_iterator<Tp>::value
				>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_input_compatible_iterator:
				kerbal::type_traits::conditional_boolean<
					is_forward_compatible_iterator<Tp>::value ||
					is_input_iterator<Tp>::value
				>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_iterator:
				kerbal::type_traits::conditional_boolean<
					is_input_compatible_iterator<Tp>::value ||
					is_output_iterator<Tp>::value
				>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		inline
		KERBAL_CONSTEXPR
		typename kerbal::iterator::iterator_traits<Tp>::iterator_category
		iterator_category(const Tp&) KERBAL_CONDITIONAL_NOEXCEPT(noexcept(typename kerbal::iterator::iterator_traits<Tp>::iterator_category()))
		{
			return typename kerbal::iterator::iterator_traits<Tp>::iterator_category();
		}

	} // namespace iterator

} // namespace kerbal

#endif /* KERBAL_ITERATOR_ITERATOR_TRAITS_HPP_ */
