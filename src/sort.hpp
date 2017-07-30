#ifndef _SORT_H_
#define _SORT_H_

//#pragma message(__DATE__ "  " __TIME__"  正在编译"__FILE__)

#include <iostream>
#include <windows.h>
//#include "array_serve.h"

using namespace std;

template <class T> unsigned long bubble_sort(T a[], unsigned int len, bool order); //order为真从小到大，为假从大到小
template <class T> unsigned long merge_sort(T a[], unsigned int len, bool order); //order为真从小到大，为假从大到小

template <class T>
unsigned long bubble_sort(T a[], unsigned int len, bool order)
{
	unsigned long k = GetTickCount();
	bool swit = true;

	for (register int i = 1; i < len && swit; i++) {
		swit = false;
		for (register int j = 0; j < len - i; j++) {
			if (order == (a[j] > a[j + 1])) {
				swit = true;
				swap(a[j], a[j + 1]);
			}
		}
	}

	return (GetTickCount() - k);
}

template <class T>
void merge(T* a, int len, bool order, T* temp) //order为真从小到大，为假从大到小
{
	if (len > 2) {
		merge(a, len / 2, order, temp);
		merge(a + len / 2, len - len / 2, order, temp + len / 2);

		int pb = 0;
		int end1 = len / 2 - 1, end2 = len - 1;
		int p1 = 0, p2 = end1 + 1;
		while (p1 <= end1 && p2 <= end2) {
			if (order == (a[p1] < a[p2])) {
				temp[pb++] = a[p1++];
			} else {
				temp[pb++] = a[p2++];
			}
		}
		while (p1 <= end1) {
			temp[pb++] = a[p1++];
		}
		while (p2 <= end2) {
			temp[pb++] = a[p2++];
		}

		memcpy(a, temp, (end2 + 1) * sizeof(temp[0]));
		//print_array(temp, (end2 + 1));
	} else if (len == 2) {
		if (order == (a[0] > a[1])) {
			swap(a[0], a[1]);
		}
	}
}

template <class T>
unsigned long merge_sort(T a[], int len, bool order) //order为真从小到大，为假从大到小
{
	unsigned long k = GetTickCount();
	T *temp = NULL;
//	if (len > 1) {
//		merge(a, 0, len - 1, temp, order);
//	}

	if (len > 2) {
		temp = new T[len];

		merge(a, len, order, temp); //不要再改成两条了！！！

		delete[] temp;

	} else if (len == 2) {
		if (order == (a[0] > a[1])) {
			swap(a[0], a[1]);
		}
	}

	return (GetTickCount() - k);
}

#endif	/* End _SORT_H_ */
