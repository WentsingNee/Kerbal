#ifndef _SORT_H_
#define _SORT_H_

template <class T> inline void bubble_sort(T *begin, const T *end);
template <class T, class _cmp> void bubble_sort(T *begin, const T *end, _cmp cmp);

template <class T> inline void merge_sort(T *begin, const T *end);
template <class T, class _cmp> void merge_sort(T *begin, const T *end, _cmp cmp);

#include "sort_base.hpp"

#endif	/* End _SORT_H_ */
