/**
 * @file       dynamic_programming.hpp
 * @brief
 * @date       2018-4-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP
#define KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP

#include <kerbal/algorithm/binary_search/lower_bound.hpp>
#include <kerbal/algorithm/modifier/fill.hpp>
#include <kerbal/algorithm/modifier/iota.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/iterator/general_back_inserter.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		// warning: Buffer must have the size >= distance(a_first, a_last) + 1
		template <
			typename ForwardIterator1, typename InputIterator2,
			typename BinaryTypeEqualTo, typename ForwardBufferIterator
		>
		KERBAL_CONSTEXPR14
		std::size_t longest_common_subsequence(
			ForwardIterator1 a_first, ForwardIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			BinaryTypeEqualTo equal_to,
			ForwardBufferIterator buffer_first
		)
		{
			typedef ForwardIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef ForwardBufferIterator buffer_iterator;

			buffer_iterator buffer_back_iter(
				kerbal::iterator::next(buffer_first, kerbal::iterator::distance(a_first, a_last))
			);
			kerbal::algorithm::fill(buffer_first,
				kerbal::iterator::next(buffer_back_iter), static_cast<std::size_t>(0)
			);

			for (iterator2 i(b_first); i != b_last; ++i) {
				std::size_t dp_i1_j1 = 0; // dp[i - 1][j - 1]

				buffer_iterator k(buffer_first);
				buffer_iterator k_next(kerbal::iterator::next(buffer_first));
				for (iterator1 j(a_first); j != a_last; ++j) {
					if (equal_to(*j, *i)) {
						std::size_t tmp = *k_next;
						*k_next = dp_i1_j1 + 1;
						dp_i1_j1 = tmp;
					} else {
						dp_i1_j1 = *k_next;
						if (*k > *k_next) {
							*k_next = *k;
						}
					}
					k = k_next;
					++k_next;
				}

			}
			return *buffer_back_iter;
		}

		template <typename ForwardIterator1, typename InputIterator2, typename BinaryTypeEqualTo>
		std::size_t longest_common_subsequence(
			ForwardIterator1 a_first, ForwardIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			BinaryTypeEqualTo equal_to
		)
		{
			typedef typename kerbal::iterator::iterator_traits<ForwardIterator1>::difference_type difference_type;
			difference_type buffer_size_need(kerbal::iterator::distance(a_first, a_last) + 1);
			if (buffer_size_need > 128) {
				kerbal::container::vector<std::size_t> buffer(buffer_size_need);
				return kerbal::algorithm::longest_common_subsequence(
					a_first, a_last,
					b_first, b_last,
					equal_to, buffer.begin()
				);
			} else {
				std::size_t buffer[128];
				return kerbal::algorithm::longest_common_subsequence(
					a_first, a_last,
					b_first, b_last,
					equal_to, buffer + 0
				);
			}
		}

		template <typename ForwardIterator1, typename InputIterator2>
		std::size_t longest_common_subsequence(
			ForwardIterator1 a_first, ForwardIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		)
		{
			typedef typename std::iterator_traits<ForwardIterator1>::value_type value_type1;
			typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;
			return kerbal::algorithm::longest_common_subsequence(
				a_first, a_last, b_first, b_last,
				kerbal::compare::binary_type_equal_to<value_type1, value_type2>()
			);
		}




		namespace detail
		{

			template <typename ForwardIterator, typename Compare, typename Container, typename BackInserter>
			KERBAL_CONSTEXPR14
			std::size_t longest_increasing_subsequence_helper(
				ForwardIterator first, ForwardIterator last, Compare cmp,
				Container & buffer, BackInserter back_inserter
			)
			{
				if (first == last) {
					return 0;
				}

				typedef ForwardIterator iterator;
				struct iter_cmp
				{
						Compare cmp;

						KERBAL_CONSTEXPR
						iter_cmp(Compare cmp) :
							cmp(cmp)
						{
						}

						KERBAL_CONSTEXPR14
						bool operator()(iterator a, iterator b)
						{
							return this->cmp(*a, *b);
						}
				} _iter_cmp(cmp);

				*back_inserter = first; ++back_inserter;
				std::size_t index_of_back = 0;

				++first;
				for (; first != last; ++first) {
					if (cmp(buffer[index_of_back], *first)) {
						*back_inserter = first; ++back_inserter; ++index_of_back;
					} else {
						*kerbal::algorithm::lower_bound(
							kerbal::container::begin(buffer), kerbal::container::end(buffer), first, _iter_cmp
						) = first;
					}
				}
				return index_of_back + 1;
			}

		} // namespace detail

		//warning: buffer must have capacity >= distance(first, last)
		template <typename ForwardIterator, typename Compare, typename Container>
		KERBAL_CONSTEXPR14
		std::size_t longest_increasing_subsequence(
			ForwardIterator first, ForwardIterator last, Compare cmp,
			Container & buffer
		)
		{
			return kerbal::algorithm::detail::longest_increasing_subsequence_helper(
				first, last, cmp, buffer, kerbal::iterator::general_inserter(buffer)
			);
		}

		template <typename ForwardIterator, typename Compare>
		std::size_t longest_increasing_subsequence(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type buffer_size_need(kerbal::iterator::distance(first, last));
			if (buffer_size_need > 32) {
				kerbal::container::vector<iterator> buffer;
				buffer.reserve(buffer_size_need);
				return kerbal::algorithm::longest_increasing_subsequence(first, last, cmp, buffer);
			} else {
				iterator buffer[32];
				return kerbal::algorithm::longest_increasing_subsequence(first, last, cmp, buffer);
			}
		}

		template <typename ForwardIterator>
		std::size_t longest_increasing_subsequence(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::longest_increasing_subsequence(first, last, kerbal::compare::less<value_type>());
		}



		// warning: buffer must have the size >= std::distance(a_first, a_last) + 1
		template <typename ForwardIterator1, typename InputIterator2,
					typename BinaryTypeEqualTo, typename ForwardBufferIterator>
		KERBAL_CONSTEXPR14
		std::size_t edit_distance(
			ForwardIterator1 a_first, ForwardIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			BinaryTypeEqualTo equal, ForwardBufferIterator buffer_first
		)
		{
			typedef ForwardIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef ForwardBufferIterator buffer_iterator;

			buffer_iterator buffer_back_iter(kerbal::iterator::next(buffer_first, kerbal::iterator::distance(a_first, a_last)));
			kerbal::algorithm::iota(buffer_first, kerbal::iterator::next(buffer_back_iter), static_cast<std::size_t>(0));

			std::size_t i_index = 0;
			for (; b_first != b_last; ++b_first) {
				std::size_t dp_i1_j1 = i_index;
				++i_index;

				buffer_iterator k_prev(buffer_first);
				buffer_iterator k(kerbal::iterator::next(buffer_first));
				*k_prev = i_index;

				for (iterator1 j(a_first); j != a_last; ++j) {
					std::size_t modify = dp_i1_j1 + (equal(*j, *b_first) ? 0 : 1);
					dp_i1_j1 = *k;

					if (*k_prev < *k) {
						*k = *k_prev;
					}
					++(*k);

					if (modify < *k) {
						*k = modify;
					}

					k_prev = k;
					++k;
				}
			}

			return *buffer_back_iter;
		}

		template <typename ForwardIterator1, typename InputIterator2, typename BinaryTypeEqualTo>
		std::size_t edit_distance(
			ForwardIterator1 a_first, ForwardIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			BinaryTypeEqualTo equal
		)
		{
			typedef typename kerbal::iterator::iterator_traits<ForwardIterator1>::difference_type difference_type;

			difference_type buffer_size_need(kerbal::iterator::distance(a_first, a_last) + 1);
			if (buffer_size_need > 32) {
				kerbal::container::vector<std::size_t> buffer(buffer_size_need);
				return kerbal::algorithm::edit_distance(a_first, a_last, b_first, b_last, equal, buffer.begin());
			} else {
				std::size_t buffer[32];
				return kerbal::algorithm::edit_distance(a_first, a_last, b_first, b_last, equal, buffer + 0);
			}
		}

		template <typename ForwardIterator1, typename InputIterator2>
		std::size_t edit_distance(
			ForwardIterator1 a_first, ForwardIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last
		)
		{
			typedef typename std::iterator_traits<ForwardIterator1>::value_type value_type1;
			typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;
			return kerbal::algorithm::edit_distance(
				a_first, a_last, b_first, b_last,
				kerbal::compare::binary_type_equal_to<value_type1, value_type2>()
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP
