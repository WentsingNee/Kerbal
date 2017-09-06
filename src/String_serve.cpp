#include "String_serve.hpp"

namespace _String
{
#if __cplusplus < 201103L //C++0x
std::string to_string(double x)
{
	std::stringstream ss;
	std::string result;
	ss << x;
	ss >> result;
	return result;
}
#endif //C++0x
}

