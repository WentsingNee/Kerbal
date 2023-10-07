#include <iostream>

using namespace std;

import kerbal;
//#include <kerbal/container/avl_set.hpp>
//#include <kerbal/container/avl_map.hpp>

int main()
{
	kerbal::container::avl_map<int, int> m;
	m[1] = 0;
	m[2] = 3;

	for (auto [k, v] : m) {
		cout << k << "   " << v << endl;
	}

	int a[] = {1, 2, 3, 4};
	kerbal::container::avl_set s1(a, a + 4);
	kerbal::container::avl_set s2(a, a + 4);
	cout << (s1 == s2) << endl;
}
