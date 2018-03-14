/**
 * @file sort.hpp
 * @date 2017-2-21
 * @author 倪文卿
 */

#ifndef _SORT_H_
#define _SORT_H_

template <class T> inline void bubble_sort(T *begin, const T *end);
template <class T, class _cmp> void bubble_sort(T *begin, const T *end, _cmp cmp);

template <class T> inline void merge_sort(T *begin, const T *end);
template <class T, class _cmp> void merge_sort(T *begin, const T *end, _cmp cmp);

#include <kerbal/algorithm/sort/sort_base.hpp>

#endif	/* End _SORT_H_ */
