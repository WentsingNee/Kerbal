/**
 * @file sort.hpp
 * @date 2017-2-21
 * @author 倪文卿
 */

#ifndef _SORT_HPP_
#define _SORT_HPP_

namespace kerbal
{
	namespace algorithm
	{
		template <class T>
		inline void bubble_sort(T *begin, const T *end);

		template <class T, class _cmp>
		void bubble_sort(T *begin, const T *end, _cmp cmp);

		template <typename RandomAccessIterator, typename CompareFuntion>
		void merge_sort(RandomAccessIterator begin, RandomAccessIterator end, CompareFuntion cmp);

		template <typename RandomAccessIterator>
		void merge_sort(RandomAccessIterator begin, RandomAccessIterator end);

	}
}

#include <kerbal/algorithm/sort/sort_base.hpp>

#endif	/* End _SORT_HPP_ */
