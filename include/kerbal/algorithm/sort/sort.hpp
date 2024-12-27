/**
 * @file       sort.hpp
 * @brief
 * @date       2020-07-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_SORT_HPP
#define KERBAL_ALGORITHM_SORT_SORT_HPP

#include <kerbal/algorithm/sort/intro_sort.hpp>
#include <kerbal/algorithm/sort/pigeonhole_sort.hpp>
#include <kerbal/algorithm/sort/radix_sort.hpp>
#include <kerbal/algorithm/sort/stable_sort.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compare/std_compare/std_compare.fwd.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator, typename Compare>
			struct sort_overload_policy_helper
			{
					typedef ForwardIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

					typedef kerbal::type_traits::bool_constant<
						kerbal::iterator::is_forward_compatible_iterator<iterator>::value &&
						kerbal::algorithm::is_pigeonhole_sort_acceptable_type<value_type>::value &&
						(
							kerbal::type_traits::is_same<Compare, std::less<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, std::less_equal<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, kerbal::compare::less<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, kerbal::compare::less_equal<value_type> >::value
						)
					> IS_PIGEONHOLE_SORT_ASC;

					typedef kerbal::type_traits::bool_constant<
						kerbal::iterator::is_forward_compatible_iterator<iterator>::value &&
						kerbal::algorithm::is_pigeonhole_sort_acceptable_type<value_type>::value &&
						(
							kerbal::type_traits::is_same<Compare, std::greater<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, std::greater_equal<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, kerbal::compare::greater<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, kerbal::compare::greater_equal<value_type> >::value
						)
					> IS_PIGEONHOLE_SORT_DESC;

					typedef kerbal::type_traits::bool_constant<
						kerbal::iterator::is_forward_compatible_iterator<iterator>::value &&
						kerbal::algorithm::is_radix_sort_acceptable_type<value_type>::value &&
						(
							kerbal::type_traits::is_same<Compare, std::less<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, std::less_equal<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, kerbal::compare::less<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, kerbal::compare::less_equal<value_type> >::value
						)
					> IS_RADIX_SORT_ASC;

					typedef kerbal::type_traits::bool_constant<
						kerbal::iterator::is_forward_compatible_iterator<iterator>::value &&
						kerbal::algorithm::is_radix_sort_acceptable_type<value_type>::value &&
						(
							kerbal::type_traits::is_same<Compare, std::greater<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, std::greater_equal<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, kerbal::compare::greater<value_type> >::value ||
							kerbal::type_traits::is_same<Compare, kerbal::compare::greater_equal<value_type> >::value
						)
					> IS_RADIX_SORT_DESC;

					typedef kerbal::type_traits::bool_constant<
						kerbal::iterator::is_random_access_compatible_iterator<iterator>::value
					> IS_INTRO_SORT;

					typedef
					typename kerbal::type_traits::conditional<
						IS_PIGEONHOLE_SORT_ASC::value,
						kerbal::type_traits::integral_constant<std::size_t, 0>,
						typename kerbal::type_traits::conditional<
							IS_PIGEONHOLE_SORT_DESC::value,
							kerbal::type_traits::integral_constant<std::size_t, 1>,
							typename kerbal::type_traits::conditional<
								IS_RADIX_SORT_ASC::value,
								kerbal::type_traits::integral_constant<std::size_t, 2>,
								typename kerbal::type_traits::conditional<
									IS_RADIX_SORT_DESC::value,
									kerbal::type_traits::integral_constant<std::size_t, 3>,
									typename kerbal::type_traits::conditional<
										IS_INTRO_SORT::value,
										kerbal::type_traits::integral_constant<std::size_t, 4>,
										kerbal::type_traits::integral_constant<std::size_t, 5>
									>::type
								>::type
							>::type
						>::type
					>::type
					policy;

			};

			template <typename ForwardIterator, typename Compare>
			struct sort_overload_policy :
				sort_overload_policy_helper<ForwardIterator, Compare>::policy
			{
			};

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void sort(
				ForwardIterator first, ForwardIterator last, Compare,
				kerbal::type_traits::integral_constant<std::size_t, 0>
			)
			{
				kerbal::algorithm::pigeonhole_sort(first, last, kerbal::type_traits::false_type());
			}

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void sort(
				ForwardIterator first, ForwardIterator last, Compare,
				kerbal::type_traits::integral_constant<std::size_t, 1>
			)
			{
				kerbal::algorithm::pigeonhole_sort(first, last, kerbal::type_traits::true_type());
			}

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void sort(
				ForwardIterator first, ForwardIterator last, Compare compare,
				kerbal::type_traits::integral_constant<std::size_t, 2>
			)
			{
#	if __cplusplus >= 201402L
#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				if (KERBAL_IS_CONSTANT_EVALUATED()) {
					kerbal::algorithm::intro_sort(first, last, compare);
				} else {
					kerbal::algorithm::radix_sort(first, last, kerbal::type_traits::false_type());
				}
#		else
				kerbal::algorithm::intro_sort(first, last, compare);
#		endif
#	else
				kerbal::algorithm::radix_sort(first, last, kerbal::type_traits::false_type());
#	endif
			}

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void sort(
				ForwardIterator first, ForwardIterator last, Compare compare,
				kerbal::type_traits::integral_constant<std::size_t, 3>
			)
			{
#	if __cplusplus >= 201402L
#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				if (KERBAL_IS_CONSTANT_EVALUATED()) {
					kerbal::algorithm::intro_sort(first, last, compare);
				} else {
					kerbal::algorithm::radix_sort(first, last, kerbal::type_traits::true_type());
				}
#		else
				kerbal::algorithm::intro_sort(first, last, compare);
#		endif
#	else
				kerbal::algorithm::radix_sort(first, last, kerbal::type_traits::true_type());
#	endif
			}

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void sort(
				ForwardIterator first, ForwardIterator last, Compare compare,
				kerbal::type_traits::integral_constant<std::size_t, 4>
			)
			{
				kerbal::algorithm::intro_sort(first, last, compare);
			}

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void sort(
				ForwardIterator first, ForwardIterator last, Compare compare,
				kerbal::type_traits::integral_constant<std::size_t, 5>
			)
			{
#	if __cplusplus >= 201402L
#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				if (KERBAL_IS_CONSTANT_EVALUATED()) {
					kerbal::algorithm::intro_sort(first, last, compare);
				} else {
					kerbal::algorithm::stable_sort(first, last, compare);
				}
#		else
				kerbal::algorithm::intro_sort(first, last, compare);
#		endif
#	else
				kerbal::algorithm::stable_sort(first, last, compare);
#	endif
			}

		} // namespace detail

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void sort(ForwardIterator first, ForwardIterator last, Compare compare)
		{
			typedef ForwardIterator iterator;

			kerbal::algorithm::detail::sort(
				first, last, compare,
				kerbal::algorithm::detail::sort_overload_policy<iterator, Compare>()
			);
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::sort(first, last, kerbal::compare::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_SORT_HPP
