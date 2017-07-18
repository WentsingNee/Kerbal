#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <windows.h>
#include <typeinfo>
#include <algorithm>

#include "advanced_math_private.h"
#include "String_serve.h"
#include "math\basic_math.h"
#include "exe_serve.h"
#include "Spherical.h"
#include "Complex.h"
#include "math\statistics.h"
#include "math\randnum.h"
#include "array_serve.h"
#include "math\big.h"
#include "math\integral.h"
#include "math\Matrix.h"
#include "math\Complexor.h"
#include "sort.h"
#include "choose.hpp"
#include "math\Mapminmax.hpp"
#include "rangerecord.hpp"

using namespace std;

double fun(double x)
{
	return sin(x);
}

#define is_debug true

int main()
{
	program_start(is_debug);

//	Matrix m = { 1, 2, 3, 4 };
//	m.print();
//	Matrix n = { 11, 22, 33 };
//	m = n;
//	m.print();
//
//	for (auto i : range(10000000)) {
//		m + n;
//	}

	/*int n = 2;
	 unsigned long t = GetTickCount();
	 while (n--) {
	 int row = rand_between(3, 3);
	 int column = row;
	 Matrix m(row, column, false);
	 for (int i = 0; i < row; i++) {
	 for (int j = 0; j < column; j++) {
	 m[i][j] = (int) rand_between(-10, 10);
	 //m.set_element(i, j, rand_between(-10, 10));
	 }
	 }
	 m.print();

	 Matrix after(optimize_rows(m));
	 after.print();

	 cout << m.Det() << endl;
	 cout << after.Det() << endl;

	 //		try {
	 //			eqution(m).print();
	 //		} catch (const invalid_argument &exct) {
	 //			cerr << exct.what() << endl;
	 //		}
	 cout << GetTickCount() - t << endl;
	 }*/
//	double s;
//	int di;
//	while (cin >> s >> di) {
//		cout << float_num(s, di) << endl;
//	}
//	double x = 5.0;
//	double y = -3.4;
//	cout << fmod(x, y) << endl;
//	cout << remainder(x, y) << endl;
//	cout << baremainder(x, y) << endl;
//printf("%.35f\n", rand_ave(true));
//	double a[100000];
//	a[0] = 0.0;
//	for (int i = 1; i < arraylen(a); i++)
//		a[i] = normdist_noise(a[i - 1], 0.1, 0);
//	print_array_to_file(a, "\n", "rand.dat", false);
//	//int a[2][3] = { 1, 2, 3, 4, 5, 6 };
//	//Array_2d<int> arr(a, 2, 0);
//	//arr.print();
//	string s = "+5-i 6 8 9 ";
//	stringstream ss;
//	ss << s;
//	Complex c1, c2;
//	ss >> c1 >> c2;
//	//cout << c1 << endl;
//	//cout << c2 << endl;
	program_will_end();
//system("pause");
	return 0;
}
