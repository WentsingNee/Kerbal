#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>

#include "advanced_math_private.h"
#include "math/Complex.hpp"

#include "array_serve.hpp"
#include "math/randnum.hpp"
#include "math/Matrix.hpp"
#include "choose.hpp"
#include "exe_serve.hpp"
#include "math/basic_math.hpp"
#include "math/big.hpp"
#include "math/Complexor.hpp"
#include "math/integral.hpp"
#include "math/Mapminmax.hpp"
#include "sort.hpp"
#include "Spherical.hpp"
#include "String_serve.hpp"
#include "Dbstream.hpp"
#include "range.hpp"
#include "math/statistics.hpp"
#include "math/MulMatrix.hpp"

class A
{
	public:
		A()
		{
			std::cout << "构造" << std::endl;
		}

		~A()
		{
			std::cout << "析构" << std::endl;
		}
	protected:

		A(const A &src)
		{
			std::cout << this << "拷贝构造" << &src << std::endl;
		}
};
double fun(double x)
{
	return sin(x);
}

#define is_debug true

/**
 * 主函数
 * @return 返回值
 */

using namespace complexor;

int main()
{
	program_start(is_debug);

	using namespace std;
	using namespace matrix;
	using namespace complexor;
	using namespace Range;
	using namespace dbstream;
	using namespace complex;

	vector<int> v = { 1, 2, 3 };

	cout << "double" << endl;
	Complexor<double> a(3, [](int i)->double {
		return i/2.0;
	}, true);
	a.print();

	cout << "double" << endl;
	Complexor<double> a2 = a;
	a2.print();

	cout << "double + double" << endl;
	(a + a2).print();

	cout << "int" << endl;
	Complexor<int> b(3, [](int i)->int {
		return i;
	}, true);
	b.print();
	cout << "double * int" << endl;
	cout << dot_product(a, b) << endl;

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

	program_will_end();
//	system("pause");
	return 0;
}
