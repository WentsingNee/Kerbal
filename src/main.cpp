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

#define is_debug true

/**
 * 主函数
 * @return 返回值
 */
int main()
{
	program_start(is_debug);

//	using namespace std;
	using namespace matrix;
	using namespace complexor;
	using namespace Range;
	using namespace dbstream;
	using namespace complex;
	using namespace statistics;

//	Matrix c(4, 4);
//	Complexor<double> t(1);
//	try {
//		try {
//			try {
//				c * t;
//			} catch (const invalid_argument &e) {
//				RE_THROW(e, "void fun");
//			}
//		} catch (const invalid_argument &e) {
//			RE_THROW(e, "void main");
//		}
//	} catch (const invalid_argument &e) {
//		cerr << e.what() << endl;
//	}


//	Matrix t {
//
//	{ 17, 24, 1, 8, 15 },
//
//	{ 23, 5, 7, 14, 16 },
//
//	{ 4, 6, 13, 20, 22 },
//
//	{ 10, 12, 19, 21, 3 },
//
//	{ 11, 18, 25, 2, 9 } };
//
//	t.print();
//
//	Matrix core = { { 1, 3, 1 }, { 0, 5, 0 }, { 2, 1, 2 } };

//	Matrix t(1500, 1500);
//	Matrix core(100, 100);
//	conv2(core, t, 2); //.print();

	Matrix a = { 0, 1, 2, 3, 4, 5 };
	Matrix core = { -1, -2, -3 };
	conv2(core, a, 2);

	program_will_end();
//	system("pause");
	return 0;
}
