#ifndef _STRING_SERVE_H_
#define _STRING_SERVE_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace _String
{
#if __cplusplus < 201103L //C++0x
	string to_string(double x);
#endif //C++0x
}

using namespace _String;

#endif	/* End _STRING_H_ */
