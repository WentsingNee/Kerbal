/**
 * @file		dynamic_programming.hpp
 * @brief
 * @date		2018年4月23日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP_
#define INCLUDE_KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP_

#include <algorithm>
#include <vector>
#include <functional>
#include <cctype>

#include "binary_type_operator.hpp"

namespace kerbal
{
	namespace algorithm
	{
		template <typename ForwardIterator1, typename InputIterator2, typename CompareFunction>
		size_t LCS_n(ForwardIterator1 a_begin, size_t a_len, InputIterator2 b_begin, size_t b_len, CompareFunction cmp)
		{
			typedef ForwardIterator1 iterator1;
			typedef InputIterator2 iterator2;

			typedef std::vector<size_t> dp_type;
			dp_type dp(a_len + 1, 0);

			iterator2 & i = b_begin;
			for (size_t i_index = 0; true;) {
				size_t dp_i1_j1 = 0;

				iterator1 j = a_begin;
				for (size_t j_index = 0; j_index < a_len; ++j_index) {
					if (cmp(*j, *i)) {
						size_t tmp = dp[j_index + 1];
						dp[j_index + 1] = dp_i1_j1 + 1;
						dp_i1_j1 = tmp;
					} else {
						dp_i1_j1 = dp[j_index + 1];
						if (dp[j_index] > dp[j_index + 1]) {
							dp[j_index + 1] = dp[j_index];
						}
					}
					++j;
				}
				++i_index;
				if (i_index < b_len) {
					++i;
				} else {
					break;
				}
			}
			return dp.back();
		}

		template <typename ForwardIterator1, typename InputIterator2>
		size_t LCS_n(ForwardIterator1 a_begin, size_t a_len, InputIterator2 b_begin, size_t b_len)
		{
			typedef typename std::iterator_traits<ForwardIterator1>::value_type value_type1;
			typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;
			return LCS_n(a_begin, a_len, b_begin, b_len,
					kerbal::algorithm::binary_type_equal_to<value_type1, value_type2>());
		}

		template <typename ForwardIterator1, typename InputIterator2, typename CompareFunction>
		size_t LCS(ForwardIterator1 a_begin, ForwardIterator1 a_end, InputIterator2 b_begin, InputIterator2 b_end, CompareFunction cmp)
		{
			typedef ForwardIterator1 iterator1;
			typedef InputIterator2 iterator2;

			typedef std::vector<size_t> dp_type;
			dp_type dp(std::distance(a_begin, a_end) + 1, 0);

			for (iterator2 i = b_begin; i != b_end; ++i) {
				size_t dp_i1_j1 = 0;

				dp_type::iterator k = dp.begin();
				dp_type::iterator k_next = dp.begin() + 1;
				for (iterator1 j = a_begin; j != a_end; ++j) {
					if (cmp(*j, *i)) {
						size_t tmp = *k_next;
						*k_next = dp_i1_j1 + 1;
						dp_i1_j1 = tmp;
					} else {
						dp_i1_j1 = *k_next;
						if (*k > *k_next) {
							*k_next = *k;
						}
					}
					++k;
					++k_next;
				}

			}
			return dp.back();
		}

		template <typename ForwardIterator1, typename InputIterator2>
		size_t LCS(ForwardIterator1 a_begin, ForwardIterator1 a_end, InputIterator2 b_begin, InputIterator2 b_end)
		{
			typedef typename std::iterator_traits<ForwardIterator1>::value_type value_type1;
			typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;
			return LCS(a_begin, a_end, b_begin, b_end,
					kerbal::algorithm::binary_type_equal_to<value_type1, value_type2>());
		}

		template <typename InputIterator, typename CompareFunction>
		size_t LIS(InputIterator begin, InputIterator end, CompareFunction cmp)
		{
			if (begin == end) {
				return 0;
			}

			typedef InputIterator iterator;
			struct iter_cmp
			{
					CompareFunction cmp;

					iter_cmp(CompareFunction cmp) :
							cmp(cmp)
					{
					}
					;
					bool operator()(iterator a, iterator b)
					{
						return cmp(*a, *b);
					}
			} _iter_cmp(cmp);

			std::vector<iterator> low;
			low.push_back(begin);
			++begin;
			for (; begin != end; ++begin) {
				if (cmp(*low.back(), *begin)) {
					low.push_back(begin);
				} else {
					*std::lower_bound(low.begin(), low.end(), begin, _iter_cmp) = begin;
				}
			}
			return low.size();
		}

		template <typename InputIterator>
		size_t LIS(InputIterator begin, InputIterator end)
		{
			typedef typename std::iterator_traits<InputIterator>::value_type value_type;
			return LIS(begin, end, std::less<value_type>());
		}

		template <typename ForwardIterator1, typename InputIterator2, typename Compare>
		size_t edit_distance(ForwardIterator1 a_begin, ForwardIterator1 a_end, InputIterator2 b_begin, InputIterator2 b_end, Compare equal)
		{
			typedef ForwardIterator1 iterator1;
			typedef InputIterator2 iterator2;

			typedef std::vector<size_t> dp_type;
			dp_type dp(std::distance(a_begin, a_end) + 1);
			for (size_t i = 0; i < dp.size(); ++i) {
				dp[i] = i;
			}

			size_t i_index = 0;
			for (iterator2 & i = b_begin; i != b_end; ++i) {
				size_t dp_i1_j1 = i_index;
				++i_index;

				dp_type::iterator k_prev = dp.begin();
				dp_type::iterator k = dp.begin() + 1;
				*k_prev = i_index;

				for (iterator1 j = a_begin; j != a_end; ++j) {
					size_t modify = dp_i1_j1 + (equal(*j, *i) == true ? 0 : 1);
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
		size_t edit_distance(ForwardIterator1 a_begin, ForwardIterator1 a_end, InputIterator2 b_begin, InputIterator2 b_end)
		{
			typedef typename std::iterator_traits<ForwardIterator1>::value_type value_type1;
			typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;
			return edit_distance(a_begin, a_end, b_begin, b_end,
					kerbal::algorithm::binary_type_equal_to<value_type1, value_type2>());
		}

		template <typename ForwardIterator1, typename InputIterator2, typename Compare>
		size_t edit_distance_n(ForwardIterator1 a_begin, size_t a_len, InputIterator2 b_begin, size_t b_len, Compare equal)
		{
			typedef ForwardIterator1 iterator1;
			typedef InputIterator2 iterator2;

			typedef std::vector<size_t> dp_type;
			dp_type dp(a_len + 1);
			for (size_t i = 0; i < dp.size(); ++i) {
				dp[i] = i;
			}

			size_t i_index = 0;
			for (iterator2 & i = b_begin; true;) {
				size_t dp_i1_j1 = i_index;
				++i_index;

				dp_type::iterator k_prev = dp.begin();
				dp_type::iterator k = dp.begin() + 1;
				*k_prev = i_index;

				iterator1 j = a_begin;
				for (size_t j_index = 0; j_index < a_len; ++j_index) {
					size_t modify = dp_i1_j1 + (equal(*j, *i) == true ? 0 : 1);
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
					++j;
				}

				if (i_index < b_len) {
					++i;
				} else {
					break;
				}
			}

			return dp.back();
		}

		template <typename ForwardIterator1, typename InputIterator2>
		size_t edit_distance_n(ForwardIterator1 a_begin, size_t a_len, InputIterator2 b_begin, size_t b_len)
		{
			typedef typename std::iterator_traits<ForwardIterator1>::value_type value_type1;
			typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;
			return edit_distance_n(a_begin, a_len, b_begin, b_len,
					kerbal::algorithm::binary_type_equal_to<value_type1, value_type2>());
		}

	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* INCLUDE_KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP_ */
