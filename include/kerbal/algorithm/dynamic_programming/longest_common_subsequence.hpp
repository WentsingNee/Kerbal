/**
 * @file       longest_common_subsequence.hpp
 * @brief
 * @date       2023-04-02
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_LONGEST_COMMON_SUBSEQUENCE_HPP
#define KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_LONGEST_COMMON_SUBSEQUENCE_HPP

#include <kerbal/algorithm/modifier/fill.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename BinaryTypeEqualTo>
			struct reverse_compare
			{
				private:
					BinaryTypeEqualTo & predict;

				public:
					KERBAL_CONSTEXPR
					explicit reverse_compare(BinaryTypeEqualTo & predict) :
							predict(predict)
					{
					}

#	if __cplusplus >= 201103L

					template <typename U, typename T>
					KERBAL_CONSTEXPR
					bool operator()(U && lhs, T && rhs) const
					{
						return predict(kerbal::utility::forward<T>(rhs), kerbal::utility::forward<U>(lhs));
					}

#	else

					template <typename U, typename T>
					KERBAL_CONSTEXPR
					bool operator()(const U & lhs, const T & rhs) const
					{
						return predict(rhs, lhs);
					}

#	endif

			};


			/**
			 *
			 * @warning Buffer must have the size >= distance(a_first, a_last) + 1 and set each element to zero
			 */
			template <typename ForwardIterator1, typename InputIterator2,
					typename BinaryTypeEqualTo, typename ForwardBufferIterator>
			KERBAL_CONSTEXPR14
			std::size_t lcs_afford_buffer(ForwardIterator1 a_first, ForwardIterator1 a_last,
										  InputIterator2 b_first, InputIterator2 b_last, BinaryTypeEqualTo equal_to,
										  ForwardBufferIterator buffer_first,
										  typename kerbal::iterator::iterator_traits<ForwardIterator1>::difference_type len_a)
			{
				typedef ForwardIterator1 iterator1;
				typedef InputIterator2 iterator2;
				typedef ForwardBufferIterator buffer_iterator;

				buffer_iterator k(buffer_first);
				for (iterator2 i(b_first); i != b_last; ++i) {
					std::size_t dp_i1_j1 = 0; // dp[i - 1][j - 1]

					k = buffer_first;
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
				return *k;
			}

			template <typename ForwardIterator1, typename InputIterator2, typename BinaryTypeEqualTo>
			KERBAL_CONSTEXPR20
			std::size_t lcs(ForwardIterator1 a_first, ForwardIterator1 a_last,
							InputIterator2 b_first, InputIterator2 b_last,
							BinaryTypeEqualTo equal_to
			)
			{
				typedef ForwardIterator1 iterator1;
				typedef typename kerbal::iterator::iterator_traits<iterator1>::difference_type difference_type1;

				difference_type1 len_a(kerbal::iterator::distance(a_first, a_last));

				if (len_a < 128) {
					std::size_t buffer[128] = {};
					return lcs_afford_buffer(a_first, a_last, b_first, b_last, equal_to, static_cast<std::size_t *>(buffer), len_a);
				} else {
					std::size_t buffer_size = len_a + 1;
					std::size_t * buffer = new std::size_t[buffer_size];
					try {
						kerbal::algorithm::fill(buffer, buffer + buffer_size, static_cast<std::size_t>(0));
						std::size_t ret = lcs_afford_buffer(a_first, a_last, b_first, b_last, equal_to, static_cast<std::size_t *>(buffer), len_a);
						delete[] buffer;
						return ret;
					} catch (...) {
						delete[] buffer;
						throw;
					}
				}

			}

			template <typename InputIterator1, typename ForwardIterator2, typename BinaryTypeEqualTo>
			std::size_t lcs_category_dispatch(InputIterator1 a_first, InputIterator1 a_last,
											  ForwardIterator2 b_first, ForwardIterator2 b_last,
											  BinaryTypeEqualTo equal_to,
											  std::input_iterator_tag a_tag, std::forward_iterator_tag b_tag
			)
			{
				return kerbal::algorithm::detail::lcs(b_first, b_last, a_first, a_last,
													  kerbal::algorithm::detail::reverse_compare<BinaryTypeEqualTo>(equal_to));
			}

			template <typename InputIterator1, typename ForwardIterator2>
			std::size_t lcs_category_dispatch(InputIterator1 a_first, InputIterator1 a_last,
											  ForwardIterator2 b_first, ForwardIterator2 b_last,
											  std::input_iterator_tag a_tag, std::forward_iterator_tag b_tag
			)
			{
				typedef InputIterator1 iterator1;
				typedef ForwardIterator2 iterator2;
				typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
				typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;

				return kerbal::algorithm::detail::lcs(b_first, b_last, a_first, a_last, kerbal::compare::binary_type_equal_to<value_type2, value_type1>());
			}

			template <typename ForwardIterator1, typename InputIterator2, typename BinaryTypeEqualTo>
			std::size_t lcs_category_dispatch(ForwardIterator1 a_first, ForwardIterator1 a_last,
											  InputIterator2 b_first, InputIterator2 b_last,
											  BinaryTypeEqualTo equal_to,
											  std::forward_iterator_tag a_tag, std::input_iterator_tag b_tag
			)
			{
				return kerbal::algorithm::detail::lcs(a_first, a_last, b_first, b_last, equal_to);
			}

			template <typename ForwardIterator1, typename InputIterator2>
			std::size_t lcs_category_dispatch(ForwardIterator1 a_first, ForwardIterator1 a_last,
											  InputIterator2 b_first, InputIterator2 b_last,
											  std::forward_iterator_tag a_tag, std::input_iterator_tag b_tag
			)
			{
				typedef ForwardIterator1 iterator1;
				typedef InputIterator2 iterator2;
				typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
				typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;

				return kerbal::algorithm::detail::lcs(a_first, a_last, b_first, b_last, kerbal::compare::binary_type_equal_to<value_type1, value_type2>());
			}

			template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryTypeEqualTo>
			std::size_t lcs_category_dispatch(ForwardIterator1 a_first, ForwardIterator1 a_last,
											  ForwardIterator2 b_first, ForwardIterator2 b_last,
											  BinaryTypeEqualTo equal_to,
											  std::forward_iterator_tag a_tag, std::forward_iterator_tag b_tag
			)
			{
				return kerbal::algorithm::detail::lcs(a_first, a_last, b_first, b_last, equal_to);
			}

			template <typename ForwardIterator1, typename ForwardIterator2>
			std::size_t lcs_category_dispatch(ForwardIterator1 a_first, ForwardIterator1 a_last,
											  ForwardIterator2 b_first, ForwardIterator2 b_last,
											  std::forward_iterator_tag a_tag, std::forward_iterator_tag b_tag
			)
			{
				typedef ForwardIterator1 iterator1;
				typedef ForwardIterator2 iterator2;
				typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
				typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;

				return kerbal::algorithm::detail::lcs(a_first, a_last, b_first, b_last, kerbal::compare::binary_type_equal_to<value_type1, value_type2>());
			}

			template <typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryTypeEqualTo>
			std::size_t lcs_category_dispatch(RandomAccessIterator1 a_first, RandomAccessIterator1 a_last,
											  RandomAccessIterator2 b_first, RandomAccessIterator2 b_last,
											  BinaryTypeEqualTo equal_to,
											  std::random_access_iterator_tag a_tag, std::random_access_iterator_tag b_tag
			)
			{
				typedef RandomAccessIterator1 iterator1;
				typedef RandomAccessIterator2 iterator2;
				typedef typename kerbal::iterator::iterator_traits<iterator1>::difference_type difference_type1;
				typedef typename kerbal::iterator::iterator_traits<iterator2>::difference_type difference_type2;

				difference_type1 len_a(kerbal::iterator::distance(a_first, a_last));
				difference_type2 len_b(kerbal::iterator::distance(b_first, b_last));

				if (len_a < len_b) {
					return kerbal::algorithm::detail::lcs(a_first, a_last, b_first, b_last, equal_to);
				} else {
					return kerbal::algorithm::detail::lcs(b_first, b_last, a_first, a_last,
														  kerbal::algorithm::detail::reverse_compare<BinaryTypeEqualTo>(equal_to));
				}
			}

			template <typename RandomAccessIterator1, typename RandomAccessIterator2>
			std::size_t lcs_category_dispatch(RandomAccessIterator1 a_first, RandomAccessIterator1 a_last,
											  RandomAccessIterator2 b_first, RandomAccessIterator2 b_last,
											  std::random_access_iterator_tag a_tag, std::random_access_iterator_tag b_tag
			)
			{
				typedef RandomAccessIterator1 iterator1;
				typedef RandomAccessIterator2 iterator2;
				typedef typename kerbal::iterator::iterator_traits<iterator1>::difference_type difference_type1;
				typedef typename kerbal::iterator::iterator_traits<iterator2>::difference_type difference_type2;
				typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
				typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;

				difference_type1 len_a(kerbal::iterator::distance(a_first, a_last));
				difference_type2 len_b(kerbal::iterator::distance(b_first, b_last));

				if (len_a < len_b) {
					return kerbal::algorithm::detail::lcs(a_first, a_last, b_first, b_last, kerbal::compare::binary_type_equal_to<value_type1, value_type2>());
				} else {
					return kerbal::algorithm::detail::lcs(b_first, b_last, a_first, a_last, kerbal::compare::binary_type_equal_to<value_type2, value_type1>());
				}
			}

		} // namespace detail


		template <typename InputIterator1, typename InputIterator2, typename BinaryTypeEqualTo>
		std::size_t longest_common_subsequence(InputIterator1 a_first, InputIterator1 a_last,
											   InputIterator2 b_first, InputIterator2 b_last,
											   BinaryTypeEqualTo equal_to)
		{
			KERBAL_STATIC_ASSERT((
					kerbal::iterator::is_forward_compatible_iterator<InputIterator1>::value ||
					kerbal::iterator::is_forward_compatible_iterator<InputIterator2>::value
			), "Either the first iterator or the second iterator should be forward iterator");

			return kerbal::algorithm::detail::lcs_category_dispatch(
					a_first, a_last, b_first, b_last, equal_to,
					kerbal::iterator::iterator_category(a_first),
					kerbal::iterator::iterator_category(b_first)
			);
		}


		template <typename InputIterator1, typename InputIterator2>
		std::size_t longest_common_subsequence(InputIterator1 a_first, InputIterator1 a_last,
											   InputIterator2 b_first, InputIterator2 b_last)
		{
			KERBAL_STATIC_ASSERT((
					kerbal::iterator::is_forward_compatible_iterator<InputIterator1>::value ||
					kerbal::iterator::is_forward_compatible_iterator<InputIterator2>::value
			), "Either the first iterator or the second iterator should be forward iterator");

			return kerbal::algorithm::detail::lcs_category_dispatch(
					a_first, a_last, b_first, b_last,
					kerbal::iterator::iterator_category(a_first),
					kerbal::iterator::iterator_category(b_first)
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_DYNAMIC_PROGRAMMING_LONGEST_COMMON_SUBSEQUENCE_HPP
