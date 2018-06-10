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

#include <vector>
#include <functional>
#include <cctype>

namespace kerbal
{
	template <typename _Tp, typename _Up = _Tp>
	struct diff_type_equal_to: public std::binary_function<_Tp, _Up, bool>
	{
			bool operator()(const _Tp& __x, const _Up& __y) const
			{
				return __x == __y;
			}
	};
}

namespace kerbal
{
	namespace algorithm
	{
		template <typename RandomAccessIterator, typename RandomAccessIterator2,
				typename CompareFunction>
		size_t __pure_LCS(RandomAccessIterator a_begin, size_t a_len, RandomAccessIterator2 b_begin, size_t b_len, CompareFunction cmp, bool has_switched =
				false)
		{
			typedef RandomAccessIterator it_t1;
			typedef RandomAccessIterator2 it_t2;

			if (a_len > b_len) {
				return __pure_LCS(b_begin, b_len, a_begin, a_len, cmp, true);
			}

			std::vector<size_t> dp(a_len + 1, 0);

			size_t i_index = 0;
			it_t2 i = b_begin;
			for (; i_index != b_len; ++i, ++i_index) {
				size_t dp_i1_j1 = 0;

				it_t1 j = a_begin;
				size_t j_index = 0;
				for (; j_index != a_len; ++j, ++j_index) {
					if (has_switched ? cmp(*i, *j) : cmp(*j, *i)) {
						size_t tmp = dp[j_index + 1];
						dp[j_index + 1] = dp_i1_j1 + 1;
						dp_i1_j1 = tmp;
					} else {
						dp_i1_j1 = dp[j_index + 1];
						if (dp[j_index] > dp[j_index + 1]) {
							dp[j_index + 1] = dp[j_index];
						}
					}
				}

			}
			return dp.back();
		}

		template <typename RandomAccessIterator, typename RandomAccessIterator2>
		size_t __pure_LCS(RandomAccessIterator a_begin, size_t a_len, RandomAccessIterator2 b_begin, size_t b_len)
		{
			return __pure_LCS(a_begin, a_len, b_begin, b_len,
					kerbal::diff_type_equal_to<
							typename std::iterator_traits<RandomAccessIterator>::value_type,
							typename std::iterator_traits<RandomAccessIterator2>::value_type>());
		}

		template <typename RandomAccessIterator, typename RandomAccessIterator2,
				typename CompareFunction>
		size_t LCS(RandomAccessIterator a_begin, RandomAccessIterator a_end, RandomAccessIterator2 b_begin, RandomAccessIterator2 b_end, CompareFunction cmp)
		{
			return __pure_LCS(a_begin, distance(a_begin, a_end), b_begin, distance(b_begin, b_end),
					cmp);
		}

		template <typename RandomAccessIterator, typename RandomAccessIterator2>
		size_t LCS(RandomAccessIterator a_begin, RandomAccessIterator a_end, RandomAccessIterator2 b_begin, RandomAccessIterator2 b_end)
		{
			return __pure_LCS(a_begin, distance(a_begin, a_end), b_begin, distance(b_begin, b_end),
					kerbal::diff_type_equal_to<
							typename std::iterator_traits<RandomAccessIterator>::value_type,
							typename std::iterator_traits<RandomAccessIterator2>::value_type>());
		}


		template<typename ForwardIterator, typename CompareFunction>
		size_t LIS(ForwardIterator begin, ForwardIterator end, CompareFunction cmp)
		{
			typedef ForwardIterator it_t;
			std::vector<size_t> d;

			size_t ans = 0;

			for(it_t i = begin; i != end; ++i) {
				d.push_back(1);

				it_t j = begin;
				std::vector<size_t>::iterator dj = d.begin();
				for(; j != i; ++j, ++dj) {
					if(cmp(*j, *i) && *dj + 1 > d.back()) {
						d.back() = *dj + 1;
					}
				}
				if(d.back() > ans) {
					ans = d.back();
				}
			}
			//	for(auto ele : d) {
			//		std::cout << ele << " ";
			//	}
			//	std::cout << std::endl;
			return ans;
		}

		template<typename ForwardIterator>
		size_t LIS(ForwardIterator begin, ForwardIterator end)
		{
			typedef ForwardIterator it_t;
			typedef typename std::iterator_traits<it_t>::value_type type;
			return LIS(begin, end, std::less<type>());
		}


	}
}

#endif /* INCLUDE_KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_HPP_ */
