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
#include "math/statistics.hpp"
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
#include "math/MulMatrix.hpp"

double fun(double x)
{
	return sin(x);
}

#define is_debug true

/**
 * 主函数
 * @return 返回值
 */
int main()
{
	program_start(is_debug);

	using namespace std;
	using namespace matrix;
	using namespace complexor;
	using namespace Range;
	using namespace dbstream;
	using namespace complex;

	unsigned long t;
	int i = 1;
	cout << "正在计算 1800*1800的矩阵 * 1800*1800 的矩阵" << endl;
	while (1) {
		Matrix a(1800, 1800, []()->double {return rand_between(-500,500);});
		Matrix b(1800, 1800, []()->double {return rand_between(-500,500);});
		cout << "start" << endl;
		t = GetTickCount();
		a * b;
		cout << "第 " << i << " 次计算, 耗时\t" << (GetTickCount() - t) << " ms" << endl;
		i++;
	}

//	Matrix a = { { 1, 5, 0, 7, 4 },
//
//	{ 2, 0, 2, 1, 2 },
//
//	{ 4, 5, 3, 0, 1 } };
//
//	Matrix b = { { 1, 2, 3 }, { 2, 1, 6 } };
//
//	conv2(b, a);

//	cout << __cplusplus << endl;
//
//	unsigned long long t = GetTickCount();
//	try {
//		MulMatrix a(1000, 1000, [](int i,int j)->double {
//			return i*10+j;
//		});
//		cout << "生成矩阵a耗时" << GetTickCount() - t << endl;
//		cout << "矩阵a大小" << (sizeof(a) + a.get_digit_size()) / 1024.0 / 1024.0 << " MB" << endl;
////		a.print();
//
//		t = GetTickCount();
//		MulMatrix b(1000, 1000, [](int i,int j)->double {
//			return i*10+j;
//		});
//		cout << "生成矩阵b耗时" << GetTickCount() - t << endl;
////		b.print();
//
//		t = GetTickCount();
//		{
//			MulMatrix c;
//			c = mul(a, b);
//			cout << "计算c=a*b耗时" << GetTickCount() - t << endl;
//			c = matrix::operator *(a, b);
//			cout << "计算c=a*b耗时" << GetTickCount() - t << endl;
////			c.print();
//		}
//
//	} catch (const exception &e) {
//		cerr << e.what() << endl;
//		throw;
//	}

//	unsigned long long t = GetTickCount();
//	try {
//		MulMatrix a(3000, 3000, []()->double {
//			return rand_between(-100,100);
//		});
//		cout << "生成矩阵a耗时" << GetTickCount() - t << endl;
//		cout << "矩阵a大小" << (sizeof(a) + a.get_digit_size()) / 1024.0 / 1024.0 << " MB" << endl;
//
//		t = GetTickCount();
//		MulMatrix b(3000, 3000, []()->double {
//			return rand_between(-100,100);
//		});
//		cout << "生成矩阵b耗时" << GetTickCount() - t << endl;
//
//		t = GetTickCount();
//		{
//			MulMatrix c;
//			c = mul(a, b);
//			cout << "计算c=a*b耗时" << GetTickCount() - t << endl;
//		}
//
//	} catch (const exception &e) {
//		cerr << e.what() << endl;
//		throw;
//	}

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

//	MulMatrix a(2000, 2000, []()->double {return rand_between(-500,500);});
//	MulMatrix b(2000, 2000, []()->double {return rand_between(-500,500);});
//	MulMatrix c;
//	unsigned long t = GetTickCount();
//	int i = 1;
//	while (1) {
//		c = mul(a, b);
//		cout << i << "\t" << double(GetTickCount() - t) / i << endl;
//		i++;
//	}
	program_will_end();
//	system("pause");
	return 0;
}
