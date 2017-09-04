#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>

#include "advanced_math_private.h"
#include "math\Complex.hpp"

#include "array_serve.hpp"
#include "math\statistics.hpp"
#include "math\randnum.hpp"
#include "math\Matrix.hpp"
#include "choose.hpp"
#include "exe_serve.hpp"
#include "math\basic_math.hpp"
#include "math\big.hpp"
#include "math\Complexor.hpp"
#include "math\integral.hpp"
#include "math\Mapminmax.hpp"
#include "sort.hpp"
#include "Spherical.hpp"
#include "String_serve.hpp"
#include "Dbstream.hpp"
#include "range.hpp"

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

	using namespace matrix;
	using namespace complexor;
	using namespace Range;
	using namespace dbstream;

//	Matrix a = { { 1, 2, 3 }, { 4, 5, 6 }, { 4, 5, 5 } };
//	a.save("biout.matrix");
//
//	for (int i = 0; i < a.get_row(); i++) {
//		for (int j = 0; j < a.get_column(); j++) {
//			print_16(a[i][j]);
//		}
//	}
//
//	Matrix b = load_from("biout.matrix");
//	b.print();
//	b = optimize_rows(a);
//	b.print();

//	for (auto i : range(1, 10, 2)) {
//		cout << i << endl;
//	}

	double x = 5.0;

	while (1) {
		double x = rand_between(-10, 10);
		double y = rand_between(-10, 10);
		cout << setw(20) << x << setw(20) << y << setw(20) << fmod(x, y) << setw(20) << remainder(x, y) << setw(20)
				<< baremainder(x, y) << endl;
	}
	program_will_end();
//	system("pause");
	return 0;
}
