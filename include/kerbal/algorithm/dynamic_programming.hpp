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

#ifndef KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP_
#define KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP_

#include <kerbal/algorithm/binary_type_predicate.hpp>
#include <kerbal/algorithm/modifiers.hpp>
#include <kerbal/algorithm/search.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/data_struct/nonmember_container_access.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <cstddef>
#include <functional>
#include <vector>

namespace kerbal
{

	namespace algorithm
	{

		// warning: dp buffer must have a length >= distance(a_first, a_last) + 1
		template <typename ForwardIterator1, typename InputIterator2,
					typename BinaryPredicate, typename BufferIterator>
		KERBAL_CONSTEXPR14
		size_t longest_common_subsequence(ForwardIterator1 a_first, ForwardIterator1 a_last,
											InputIterator2 b_first, InputIterator2 b_last, BinaryPredicate equal_to,
											BufferIterator dp)
		{
			typedef ForwardIterator1 iterator1;
			typedef InputIterator2 iterator2;

			BufferIterator dp_back_iter(kerbal::iterator::next(dp, std::distance(a_first, a_last)));
			kerbal::algorithm::fill(dp, kerbal::iterator::next(dp_back_iter),
									static_cast<size_t>(0));

			for (iterator2 i(b_first); i != b_last; ++i) {
				size_t dp_i1_j1 = 0;

				BufferIterator k(dp);
				BufferIterator k_next(kerbal::iterator::next(dp));
				for (iterator1 j(a_first); j != a_last; ++j) {
					if (equal_to(*j, *i)) {
						size_t tmp = *k_next;
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
			return *dp_back_iter;
		}

		template <typename ForwardIterator1, typename InputIterator2, typename BinaryPredicate>
		size_t longest_common_subsequence(ForwardIterator1 a_first, ForwardIterator1 a_last,
										InputIterator2 b_first, InputIterator2 b_last, BinaryPredicate equal_to)
		{
			typedef typename kerbal::iterator::iterator_traits<ForwardIterator1>::difference_type difference_type;
			difference_type buffer_size_need(kerbal::iterator::distance(a_first, a_last) + 1);
			if (buffer_size_need > 128) {
				std::vector<size_t> dp(buffer_size_need);
				return kerbal::algorithm::longest_common_subsequence(a_first, a_last, b_first, b_last, equal_to, dp.begin());
			} else {
				size_t dp[128];
				return kerbal::algorithm::longest_common_subsequence(a_first, a_last, b_first, b_last, equal_to, dp);
			}
		}

		template <typename ForwardIterator1, typename InputIterator2>
		size_t longest_common_subsequence(ForwardIterator1 a_first, ForwardIterator1 a_last,
											InputIterator2 b_first, InputIterator2 b_last)
		{
			typedef typename std::iterator_traits<ForwardIterator1>::value_type value_type1;
			typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;
			return kerbal::algorithm::longest_common_subsequence(a_first, a_last, b_first, b_last,
					kerbal::algorithm::binary_type_equal_to<value_type1, value_type2>());
		}




		template <typename InputIterator, typename BinaryPredicate, typename Container, typename BackInserter>
		KERBAL_CONSTEXPR14
		size_t __longest_increasing_subsequence(InputIterator first, InputIterator last,
												BinaryPredicate cmp, Container & buffer, BackInserter back_inserter)
		{
			if (first == last) {
				return 0;
			}

			typedef InputIterator iterator;
			struct iter_cmp
			{
					BinaryPredicate cmp;

					KERBAL_CONSTEXPR
					iter_cmp(BinaryPredicate cmp) :
								cmp(cmp)
					{
					}

					KERBAL_CONSTEXPR
					bool operator()(iterator a, iterator b)
					{
						return this->cmp(*a, *b);
					}
			} _iter_cmp(cmp);

			*back_inserter = first; ++back_inserter;
			size_t index_of_back = 0;

			++first;
			for (; first != last; ++first) {
				if (cmp(buffer[index_of_back], *first)) {
					*back_inserter = first; ++back_inserter; ++index_of_back;
				} else {
					*kerbal::algorithm::ordered_range_lower_bound(
							kerbal::data_struct::begin(buffer), kerbal::data_struct::end(buffer), first, _iter_cmp) = first;
				}
			}
			return index_of_back + 1;
		}

		template <typename InputIterator, typename BinaryPredicate, typename Container>
		size_t longest_increasing_subsequence(InputIterator first, InputIterator last,
												BinaryPredicate cmp, Container & buffer)
		{
			return kerbal::algorithm::__longest_increasing_subsequence(first, last, cmp, buffer, std::back_inserter(buffer));
		}

		//warning: buffer must have a length >= distance(first, last)
		template <typename InputIterator, typename BinaryPredicate, typename Container>
		KERBAL_CONSTEXPR14
		size_t longest_increasing_subsequence(InputIterator first, InputIterator last,
												BinaryPredicate cmp, InputIterator buffer[])
		{
			return kerbal::algorithm::__longest_increasing_subsequence(first, last, cmp, buffer, buffer);
		}

		template <typename InputIterator, typename BinaryPredicate>
		size_t __longest_increasing_subsequence(InputIterator first, InputIterator last,
													BinaryPredicate cmp, std::input_iterator_tag)
		{
			typedef InputIterator iterator;
			std::vector<iterator> buffer;
			buffer.reserve(128);
			return kerbal::algorithm::longest_increasing_subsequence(first, last, cmp, buffer);
		}

		template <typename RandomAccessIterator, typename BinaryPredicate>
		size_t __longest_increasing_subsequence(RandomAccessIterator first, RandomAccessIterator last,
													BinaryPredicate cmp, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			difference_type buffer_size_need(kerbal::iterator::distance(first, last));
			if (buffer_size_need > 128) {
				std::vector<iterator> buffer;
				buffer.reserve(buffer_size_need);
				return kerbal::algorithm::longest_increasing_subsequence(first, last, cmp, buffer);
			} else {
				iterator buffer[128];
				return kerbal::algorithm::longest_increasing_subsequence(first, last, cmp, buffer);
			}
		}

		template <typename InputIterator, typename BinaryPredicate>
		size_t longest_increasing_subsequence(InputIterator first, InputIterator last, BinaryPredicate cmp)
		{
			return kerbal::algorithm::__longest_increasing_subsequence(first, last, cmp, kerbal::iterator::iterator_category(first));
		}

		template <typename InputIterator>
		size_t longest_increasing_subsequence(InputIterator first, InputIterator last)
		{
			typedef InputIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::longest_increasing_subsequence(first, last, std::less<value_type>());
		}




		template <typename ForwardIterator1, typename InputIterator2, typename BinaryPredicate>
		size_t edit_distance(ForwardIterator1 a_first, ForwardIterator1 a_last,
								InputIterator2 b_first, InputIterator2 b_last, BinaryPredicate equal)
		{
			typedef ForwardIterator1 iterator1;
			typedef InputIterator2 iterator2;

			typedef std::vector<size_t> dp_type;
			dp_type dp(std::distance(a_first, a_last) + 1);
			for (size_t i = 0; i < dp.size(); ++i) {
				dp[i] = i;
			}

			size_t i_index = 0;
			for (; b_first != b_last; ++b_first) {
				size_t dp_i1_j1 = i_index;
				++i_index;

				dp_type::iterator k_prev = dp.begin();
				dp_type::iterator k = dp.begin() + 1;
				*k_prev = i_index;

				for (iterator1 j = a_first; j != a_last; ++j) {
					size_t modify = dp_i1_j1 + (equal(*j, *b_first) == true ? 0 : 1);
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

			return dp.back();
		}

		template <typename ForwardIterator1, typename InputIterator2>
		size_t edit_distance(ForwardIterator1 a_first, ForwardIterator1 a_last,
								InputIterator2 b_first, InputIterator2 b_last)
		{
			typedef typename std::iterator_traits<ForwardIterator1>::value_type value_type1;
			typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;
			return edit_distance(a_first, a_last, b_first, b_last,
					kerbal::algorithm::binary_type_equal_to<value_type1, value_type2>());
		}

	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP_ */
