#ifndef _STRING_SERVE_H_
#define _STRING_SERVE_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace _String
{
#if __cplusplus < 201103L
	string to_string(double x);
#endif
}

using namespace _String;

//#pragma message(__DATE__ "  " __TIME__"  ±àÒëÍê³É"__FILE__)
#endif	/* End _STRING_H_ */
