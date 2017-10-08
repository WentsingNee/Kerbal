#ifndef _SORT_H_
#define _SORT_H_

//#pragma message(__DATE__ "  " __TIME__"  正在编译"__FILE__)

template <class T, class _cmp> void bubble_sort(T a[], unsigned int len, _cmp cmp);
template <class T> void merge_sort(T a[], unsigned int len, bool order); //order为真从小到大，为假从大到小

template <class T, class _cmp>
void bubble_sort(T a[], unsigned int len, _cmp cmp)
{
	bool swit = true;

	for (int i = 1; i < len && swit; i++) {
		swit = false;
		for (int j = 0; j < len - i; j++) {
			if (!cmp(a[j], a[j + 1])) {
				swit = true;
				swap(a[j], a[j + 1]);
			}
		}
	}
}

template <class T>
void merge(T* a, int len, bool order, T* temp) //order为真从小到大，为假从大到小
{
	const int half_len = len / 2;
	if (half_len) {
		merge(a, half_len, order, temp);
		merge(a + half_len, len - half_len, order, temp + half_len);

		int pb = 0;
		int end1 = half_len - 1, end2 = len - 1;
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
void merge_sort(T a[], int len, bool order) //order为真从小到大，为假从大到小
{
	if (len > 2) {
		T *temp = new T[len];

		merge(a, len, order, temp); //不要再改成两条了！！！

		delete[] temp;

	} else if (len == 2) {
		if (order == (a[0] > a[1])) {
			swap(a[0], a[1]);
		}
	}
}

#endif	/* End _SORT_H_ */
