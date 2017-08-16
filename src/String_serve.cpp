#include "String_serve.hpp"

using namespace std;

namespace _String
{
#if __cplusplus < 201103L //C++0x
string to_string(double x)
{
	stringstream ss;
	string result;
	ss << x;
	ss >> result;
	return result;
}
#endif //C++0x
}

