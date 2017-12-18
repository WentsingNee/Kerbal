#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>

#include "advanced_math_private.h"

#include "kerbal/exe_serve.hpp"
#include "kerbal/sort.hpp"
#include "kerbal/Spherical.hpp"
#include "kerbal/String_serve.hpp"
#include "kerbal/range.hpp"
#include "kerbal/Trexcept.hpp"
#include <iterator>
#include <vector>

#include "kerbal/math/Complex.hpp"
#include "kerbal/array_serve.hpp"
#include "kerbal/math/randnum.hpp"
#include "kerbal/math/Matrix.hpp"
#include "kerbal/math/basic_math.hpp"
#include "kerbal/math/Complexor.hpp"
#include "kerbal/math/integral.hpp"
#include "kerbal/math/Mapminmax.hpp"
#include "kerbal/math/statistics.hpp"

#include "kerbal/choose.hpp"
#include "kerbal/dbstream.hpp"

#define is_debug true

//using namespace kerbal;
using namespace kerbal::Range;
//using namespace kerbal::utility::dbstream;
using namespace kerbal::math::complex;
//using namespace kerbal::math::statistics;
using namespace traceable;

using namespace std;
using namespace kerbal::spherical;

/*
 void conv_test()
 {
 Matrix t {

 { 17, 24, 1, 8, 15 },

 { 23, 5, 7, 14, 16 },

 { 4, 6, 13, 20, 22 },

 { 10, 12, 19, 21, 3 },

 { 11, 18, 25, 2, 9 } };

 t.print();

 Matrix core = { { 1, 3, 1 }, { 0, 5, 0 }, { 2, 1, 2 } };

 //	Matrix t(1500, 1500);
 //	Matrix core(100, 100);
 //	conv2(core, t, 2); //.print();
 //
 //	Matrix a = { 0, 1, 2, 3, 4, 5 };
 //	Matrix core = { -1, -2, -3 };
 conv2(core, t, 2);
 }
 */

using namespace _choose;

int main()
{
	program_start(is_debug);

	cout << _choose::choose(2, 5, 7, 8, 6, 7) << endl;
	cout << _choose::choose_c11(2, 5.5, 7.5, 8.5, 6.5, 17.5) << endl;

	program_will_end();
//	system("pause");
	return 0;
}

