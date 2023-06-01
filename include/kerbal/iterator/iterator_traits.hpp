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
		struct iterator_traits: kerbal::iterator::detail::iterator_traits_helper<Iterator>
		{
		};

		KERBAL_MODULE_EXPORT
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

		KERBAL_MODULE_EXPORT
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



		namespace detail
		{

			template <typename, typename = kerbal::type_traits::void_type<>::type >
			struct is_iterator_helper: kerbal::type_traits::false_type
			{
			};

			template <typename Tp>
			struct is_iterator_helper<
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

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_iterator: kerbal::iterator::detail::is_iterator_helper<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};



		namespace detail
		{

			template <typename Tp, typename RequiredCategory, typename = kerbal::type_traits::void_type<>::type >
			struct iterator_category_matches_required_helper: kerbal::type_traits::false_type
			{
			};

			template <typename Tp, typename RequiredCategory>
			struct iterator_category_matches_required_helper<
					Tp,
					RequiredCategory,
					typename kerbal::type_traits::void_type<
						typename kerbal::iterator::iterator_traits<Tp>::iterator_category
					>::type
				>
				: kerbal::type_traits::is_same<typename kerbal::iterator::iterator_traits<Tp>::iterator_category, RequiredCategory>
			{
			};

		} // namespace detail

		template <typename Tp, typename RequiredCategory>
		struct iterator_category_matches_required:
				kerbal::iterator::detail::iterator_category_matches_required_helper<
					typename kerbal::type_traits::remove_cv<Tp>::type,
					RequiredCategory
				>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_output_iterator:
				kerbal::iterator::detail::iterator_category_matches_required_helper<
					typename kerbal::type_traits::remove_cv<Tp>::type,
					std::output_iterator_tag
				>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_input_iterator:
				kerbal::iterator::detail::iterator_category_matches_required_helper<
					typename kerbal::type_traits::remove_cv<Tp>::type,
					std::input_iterator_tag
				>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_forward_iterator:
				kerbal::iterator::detail::iterator_category_matches_required_helper<
					typename kerbal::type_traits::remove_cv<Tp>::type,
					std::forward_iterator_tag
				>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_bidirectional_iterator:
				kerbal::iterator::detail::iterator_category_matches_required_helper<
					typename kerbal::type_traits::remove_cv<Tp>::type,
					std::bidirectional_iterator_tag
				>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_random_access_iterator:
				kerbal::iterator::detail::iterator_category_matches_required_helper<
					typename kerbal::type_traits::remove_cv<Tp>::type,
					std::random_access_iterator_tag
				>
		{
		};

		namespace detail
		{

#	if __cplusplus > 201703L

			template <typename Tp, typename = kerbal::type_traits::void_type<>::type>
			struct is_contiguous_iterator_check_through_std_iterator_traits: kerbal::type_traits::false_type
			{
			};

			template <typename Tp>
			struct is_contiguous_iterator_check_through_std_iterator_traits<
						Tp,
						typename kerbal::type_traits::void_type<
							typename std::iterator_traits<Tp>::iterator_concept
						>::type
					> :
					kerbal::type_traits::is_same<
						typename std::iterator_traits<Tp>::iterator_concept,
						std::contiguous_iterator_tag
					>
			{
			};

			template <typename Tp, typename = kerbal::type_traits::void_type<>::type>
			struct is_contiguous_iterator_check_through_iterator_concept: kerbal::type_traits::false_type
			{
			};

			template <typename Tp>
			struct is_contiguous_iterator_check_through_iterator_concept<
						Tp,
						typename kerbal::type_traits::void_type<
							typename Tp::iterator_concept
						>::type
					> :
					kerbal::type_traits::is_same<
						typename Tp::iterator_concept,
						std::contiguous_iterator_tag
					>
			{
			};

			template <typename Tp>
			struct is_contiguous_iterator_helper:
					kerbal::type_traits::bool_constant<
						is_contiguous_iterator_check_through_std_iterator_traits<Tp>::value ||
						is_contiguous_iterator_check_through_iterator_concept<Tp>::value
					>
			{
			};

#	else

			template <typename Tp>
			struct is_contiguous_iterator_helper: kerbal::type_traits::false_type
			{
			};

#	endif

			template <typename Tp>
			struct is_contiguous_iterator_helper<Tp*>: kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_contiguous_iterator:
				kerbal::iterator::detail::is_contiguous_iterator_helper<
					typename kerbal::type_traits::remove_cv<Tp>::type
				>
		{
		};


		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_random_access_compatible_iterator: kerbal::iterator::is_random_access_iterator<Tp>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_bidirectional_compatible_iterator:
				kerbal::type_traits::bool_constant<
					kerbal::iterator::is_random_access_compatible_iterator<Tp>::value ||
					kerbal::iterator::is_bidirectional_iterator<Tp>::value
				>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_forward_compatible_iterator:
				kerbal::type_traits::bool_constant<
					kerbal::iterator::is_bidirectional_compatible_iterator<Tp>::value ||
					kerbal::iterator::is_forward_iterator<Tp>::value
				>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_input_compatible_iterator:
				kerbal::type_traits::bool_constant<
					kerbal::iterator::is_forward_compatible_iterator<Tp>::value ||
					kerbal::iterator::is_input_iterator<Tp>::value
				>
		{
		};

		KERBAL_MODULE_EXPORT
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
