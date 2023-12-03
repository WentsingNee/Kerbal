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

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/concepts/config.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/remove_cv.hpp>
#include <kerbal/type_traits/void_type.hpp>

#include <iterator>
#include <cstddef>

#include <kerbal/ts/modules_ts/modules_ts.hpp>


namespace kerbal
{

	namespace iterator
	{

		namespace detail
		{

			template <typename, typename = kerbal::type_traits::void_type<>::type >
			struct iterator_traits_helper
			{
			};

			template <typename Iterator>
			struct iterator_traits_helper<
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

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename Iterator>
		struct iterator_traits :
			kerbal::iterator::detail::iterator_traits_helper<Iterator>
		{
		};

		KERBAL_MODULE_EXPORT
		/// Partial specialization for pointer types.
		template <typename T>
		struct iterator_traits<T *>
		{
				typedef std::random_access_iterator_tag		iterator_category;
				typedef T									value_type;
				typedef std::ptrdiff_t						difference_type;
				typedef T *									pointer;
				typedef T &									reference;
		};

		KERBAL_MODULE_EXPORT
		/// Partial specialization for const pointer types.
		template <typename T>
		struct iterator_traits<const T *>
		{
				typedef std::random_access_iterator_tag		iterator_category;
				typedef T									value_type;
				typedef std::ptrdiff_t						difference_type;
				typedef const T *							pointer;
				typedef const T &							reference;
		};



		namespace detail
		{

			template <typename, typename = kerbal::type_traits::void_type<>::type >
			struct is_iterator_helper : kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct is_iterator_helper<
				T,
				typename kerbal::type_traits::void_type<
					typename kerbal::iterator::iterator_traits<T>::iterator_category,
					typename kerbal::iterator::iterator_traits<T>::value_type,
					typename kerbal::iterator::iterator_traits<T>::difference_type,
					typename kerbal::iterator::iterator_traits<T>::pointer,
					typename kerbal::iterator::iterator_traits<T>::reference
				>::type
			> :
				kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_iterator :
			kerbal::iterator::detail::is_iterator_helper<
				typename kerbal::type_traits::remove_cv<T>::type
			>
		{
		};



		namespace detail
		{

			template <
				typename T, typename RequiredCategory,
				typename = kerbal::type_traits::void_type<>::type
			>
			struct iterator_category_matches_required_helper :
				kerbal::type_traits::false_type
			{
			};

			template <typename T, typename RequiredCategory>
			struct iterator_category_matches_required_helper<
				T,
				RequiredCategory,
				typename kerbal::type_traits::void_type<
					typename kerbal::iterator::iterator_traits<T>::iterator_category
				>::type
			> :
				kerbal::type_traits::is_same<
					typename kerbal::iterator::iterator_traits<T>::iterator_category,
					RequiredCategory
				>
			{
			};

		} // namespace detail

		template <typename T, typename RequiredCategory>
		struct iterator_category_matches_required :
			kerbal::iterator::detail::iterator_category_matches_required_helper<
				typename kerbal::type_traits::remove_cv<T>::type,
				RequiredCategory
			>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_output_iterator :
			kerbal::iterator::detail::iterator_category_matches_required_helper<
				typename kerbal::type_traits::remove_cv<T>::type,
				std::output_iterator_tag
			>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_input_iterator :
			kerbal::iterator::detail::iterator_category_matches_required_helper<
				typename kerbal::type_traits::remove_cv<T>::type,
				std::input_iterator_tag
			>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_forward_iterator :
			kerbal::iterator::detail::iterator_category_matches_required_helper<
				typename kerbal::type_traits::remove_cv<T>::type,
				std::forward_iterator_tag
			>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_bidirectional_iterator :
			kerbal::iterator::detail::iterator_category_matches_required_helper<
				typename kerbal::type_traits::remove_cv<T>::type,
				std::bidirectional_iterator_tag
			>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_random_access_iterator :
			kerbal::iterator::detail::iterator_category_matches_required_helper<
				typename kerbal::type_traits::remove_cv<T>::type,
				std::random_access_iterator_tag
			>
		{
		};

		namespace detail
		{

#	if __cplusplus > 201703L

			template <typename T, typename = kerbal::type_traits::void_type<>::type>
			struct is_contiguous_iterator_check_through_std_iterator_traits :
				kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct is_contiguous_iterator_check_through_std_iterator_traits<
				T,
				typename kerbal::type_traits::void_type<
					typename std::iterator_traits<T>::iterator_concept
				>::type
			> :
				kerbal::type_traits::is_same<
					typename std::iterator_traits<T>::iterator_concept,
					std::contiguous_iterator_tag
				>
			{
			};

			template <typename T, typename = kerbal::type_traits::void_type<>::type>
			struct is_contiguous_iterator_check_through_iterator_concept :
				kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct is_contiguous_iterator_check_through_iterator_concept<
				T,
				typename kerbal::type_traits::void_type<
					typename T::iterator_concept
				>::type
			> :
				kerbal::type_traits::is_same<
					typename T::iterator_concept,
					std::contiguous_iterator_tag
				>
			{
			};

			template <typename T>
			struct is_contiguous_iterator_helper :
				kerbal::type_traits::bool_constant<
					is_contiguous_iterator_check_through_std_iterator_traits<T>::value ||
					is_contiguous_iterator_check_through_iterator_concept<T>::value
				>
			{
			};

#	else

			template <typename T>
			struct is_contiguous_iterator_helper :
				kerbal::type_traits::false_type
			{
			};

#	endif

			template <typename T>
			struct is_contiguous_iterator_helper<T *> :
				kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_contiguous_iterator :
			kerbal::iterator::detail::is_contiguous_iterator_helper<
				typename kerbal::type_traits::remove_cv<T>::type
			>
		{
		};


		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_random_access_compatible_iterator :
			kerbal::iterator::is_random_access_iterator<T>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_bidirectional_compatible_iterator :
			kerbal::type_traits::bool_constant<
				kerbal::iterator::is_random_access_compatible_iterator<T>::value ||
				kerbal::iterator::is_bidirectional_iterator<T>::value
			>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_forward_compatible_iterator :
			kerbal::type_traits::bool_constant<
				kerbal::iterator::is_bidirectional_compatible_iterator<T>::value ||
				kerbal::iterator::is_forward_iterator<T>::value
			>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_input_compatible_iterator :
			kerbal::type_traits::bool_constant<
				kerbal::iterator::is_forward_compatible_iterator<T>::value ||
				kerbal::iterator::is_input_iterator<T>::value
			>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		KERBAL_CONSTEXPR
		typename kerbal::iterator::iterator_traits<T>::iterator_category
		iterator_category(const T &)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(
					typename kerbal::iterator::iterator_traits<T>::iterator_category()
				)
			)
		{
			return typename kerbal::iterator::iterator_traits<T>::iterator_category();
		}

#	if KERBAL_HAS_CONCEPTS_SUPPORT

		template <typename Tp>
		concept input_iterator = kerbal::iterator::is_input_iterator<Tp>::value;

#	endif

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_ITERATOR_TRAITS_HPP
