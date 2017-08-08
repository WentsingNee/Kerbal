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
#include "Spherical.h"
#include "math\Complex.hpp"

#include "array_serve.hpp"
#include "math\statistics.hpp"
#include "math\randnum.hpp"
#include "math\Matrix.hpp"
#include "choose.hpp"
#include "exe_serve.hpp"
#include "math/basic_math.hpp"
#include "math/big.hpp"
#include "math/Complexor.hpp"
#include "math/integral.hpp"
#include "math\Mapminmax.hpp"
#include "rangerecord.hpp"
#include "sort.hpp"
#include "String_serve.hpp"

using namespace std;

double fun(double x)
{
	return sin(x);
}

#define is_debug true

int main()
{
	program_start(is_debug);

	cout << __cplusplus << endl;

	Matrix a = { { 1, 2, 3 }, { 4, 5, 6 }, { 4, 5, 5 } };
	a.save("biout.matrix");

	for (int i = 0; i < a.get_row(); i++) {
		for (int j = 0; j < a.get_column(); j++) {
			print_16(a[i][j]);
		}
	}

	Matrix b = load_from("biout.matrix");
	b.print();
	b = optimize_rows(a);
	b.print();

//	for (auto i : range(1, 10, 2)) {
//		cout << i << endl;
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
	program_will_end();
//	system("pause");
	return 0;
}
