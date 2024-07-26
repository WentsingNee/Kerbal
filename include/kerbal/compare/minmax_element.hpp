/**
 * @file       minmax_element.hpp
 * @brief
 * @date       2024-05-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPARE_MINMAX_ELEMENT_HPP
#define KERBAL_COMPARE_MINMAX_ELEMENT_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#include <cstddef>


namespace kerbal
{

	namespace compare
	{

		namespace detail
		{

			template <typename ForwardIterator, typename BinaryPredicate>
			KERBAL_CONSTEXPR14
			ForwardIterator extreme_element(
				ForwardIterator first, ForwardIterator last, BinaryPredicate pred,
				std::forward_iterator_tag
			)
			{
				typedef ForwardIterator iterator;

				iterator selected(first);
				if (first != last) {
					++first;
					while (first != last) {
						if (pred(*first, *selected)) {
							selected = first;
						}
						++first;
					}
				}
				return selected;
			}

			template <typename RandomAccessIterator, typename BinaryPredicate>
			KERBAL_CONSTEXPR14
			RandomAccessIterator extreme_element(
				RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred,
				std::random_access_iterator_tag
			)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				iterator selected(first);
				if (first != last) {
					++first;

#			define EACH() do { \
						if (pred(*first, *selected)) { \
							selected = first; \
						} \
						++first; \
					} while (false)

					difference_type trip_count(kerbal::iterator::distance(first, last));
					difference_type remain(trip_count & 3);
					for (trip_count >>= 2; trip_count > 0; --trip_count) {
						EACH();
						EACH();
						EACH();
						EACH();
					}

					if (remain >= 2) {
						EACH();
						EACH();
						remain -= 2;
					}
					if (remain >= 1) {
						EACH();
					}

#			undef EACH

				}
				return selected;
			}

		} // namespace detail


		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			return kerbal::compare::detail::extreme_element(
				first, last, pred,
				kerbal::iterator::iterator_category(first)
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::compare::min_element(first, last, kerbal::compare::less<value_type>());
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			return kerbal::compare::detail::extreme_element(
				first, last, pred,
				kerbal::iterator::iterator_category(first)
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::compare::max_element(first, last, kerbal::compare::greater<value_type>());
		}


		namespace detail
		{

			template <typename ForwardIterator, typename BinaryPredicate>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<ForwardIterator, ForwardIterator>
			minmax_element(
				ForwardIterator first, ForwardIterator last, BinaryPredicate pred,
				std::forward_iterator_tag
			)
			{
				typedef ForwardIterator iterator;

				iterator mini(first);
				iterator maxi(first);
				if (first != last) {
					++first;
					while (first != last) {
						if (pred(*first, *mini)) { // *first < *mini
							mini = first;
						} else if (!static_cast<bool>(pred(*first, *maxi))) { // *first >= *maxi
							maxi = first;
						}
						++first;
					}
				}
				return kerbal::utility::make_compressed_pair(mini, maxi);
			}

			template <typename RandomAccessIterator, typename BinaryPredicate>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<RandomAccessIterator, RandomAccessIterator>
			minmax_element(
				RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred,
				std::random_access_iterator_tag
			)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				iterator mini(first);
				iterator maxi(first);
				if (first != last) {
					++first;

#			define EACH() do { \
						if (pred(*first, *mini)) { \
							mini = first; \
						} else if (!static_cast<bool>(pred(*first, *maxi))) { \
							maxi = first; \
						} \
						++first; \
					} while (false)

					difference_type trip_count(kerbal::iterator::distance(first, last));
					difference_type remain(trip_count & 3);
					for (trip_count >>= 2; trip_count > 0; --trip_count) {
						EACH();
						EACH();
						EACH();
						EACH();
					}

					if (remain >= 2) {
						EACH();
						EACH();
						remain -= 2;
					}
					if (remain >= 1) {
						EACH();
					}

#			undef EACH

				}
				return kerbal::utility::make_compressed_pair(mini, maxi);
			}

		} // namespace detail


		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		kerbal::utility::compressed_pair<ForwardIterator, ForwardIterator>
		minmax_element(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			return kerbal::compare::detail::minmax_element(
				first, last, pred,
				kerbal::iterator::iterator_category(first)
			);
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		kerbal::utility::compressed_pair<ForwardIterator, ForwardIterator>
		minmax_element(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::compare::minmax_element(first, last, kerbal::compare::less<value_type>());
		}

	} //namespace compare

} //namespace kerbal

#endif // KERBAL_COMPARE_MINMAX_ELEMENT_HPP
