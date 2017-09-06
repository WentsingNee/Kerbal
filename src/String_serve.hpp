#ifndef _STRING_SERVE_H_
#define _STRING_SERVE_H_

#include <iostream>
#include <string>
#include <sstream>

namespace _String
{
#if __cplusplus < 201103L //C++0x
std::string to_string(double x);
#endif //C++0x
}

#endif	/* End _STRING_H_ */
