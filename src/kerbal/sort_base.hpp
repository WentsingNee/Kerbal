/*
 * sort_base.hpp
 *
 *  Created on: 2017年10月28日
 *      Author: Peter
 */

#ifndef SORT_BASE_HPP_
#define SORT_BASE_HPP_

#include <algorithm>

template <class T>
inline void bubble_sort(T *begin, const T *end)
{
	bubble_sort(begin, end, std::less_equal<T>());
}

template <class T, class _cmp>
void bubble_sort(T *begin, const T *end, _cmp cmp)
{
	bool swit = true;
	const size_t len = std::distance(begin, end);

	for (size_t i = 1; i < len && swit; ++i) {
		swit = false;
		for (T *j = begin; i + j < end; ++j) {
			if (!cmp(*j, *(j + 1))) {
				swit = true;
				std::swap(*j, *(j + 1));
			}
		}
	}
}

template <class T, class _cmp>
void merge(T* begin, const T* end, _cmp cmp, T* temp) //order为真从小到大，为假从大到小
{
	const size_t len = std::distance(begin, end);
	const size_t half_len = len / 2;
	if (half_len) {
		T* mid = begin + half_len;
		merge(begin, mid, cmp, temp);
		merge(mid, end, cmp, temp + half_len);

		T* p_to_tmp = temp;
		const T *p_to_1 = begin;
		const T *p_to_2 = mid;

		while (p_to_1 < mid && p_to_2 < end) {
			if (cmp(*p_to_1, *p_to_2)) {
				*(p_to_tmp++) = *(p_to_1++);
			} else {
				*(p_to_tmp++) = *(p_to_2++);
			}
		}
//		while (p_to_1 < mid) {
//			*(p_to_tmp++) = *(p_to_1++);
//		}
//		while (p_to_2 < end) {
//			*(p_to_tmp++) = *(p_to_2++);
//		}

		//TODO optimize
		if (p_to_1 < mid) {
			std::copy(const_cast<T*>(p_to_1), mid, p_to_tmp);
		} else if (p_to_2 < end) {
			std::copy(const_cast<T*>(p_to_2), const_cast<T*>(end), p_to_tmp + (mid - p_to_1));
		}

		std::copy(temp, temp + len, begin);
	} else if (len == 2) {
//		std::cout << begin[0] << "   " << begin[1] << std::endl;
		if (!cmp(begin[0], begin[1])) {
			std::swap(begin[0], begin[1]);
		}
	}
}

template <class T>
inline void merge_sort(T *begin, const T *end)
{
	merge_sort(begin, end, std::less_equal<T>());
}

template <class T, class _cmp>
void merge_sort(T *begin, const T *end, _cmp cmp)
{
	const size_t len = std::distance(begin, end);
	if (len > 2) {
		T *temp = new T[len];

		merge(begin, end, cmp, temp); //不要再改成两条了！！！

		delete[] temp;

	} else if (len == 2) {
		if (!cmp(begin[0], begin[1])) {
			std::swap(begin[0], begin[1]);
		}
	}
}

#endif /* SORT_BASE_HPP_ */
