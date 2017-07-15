#include "String_serve.h"

using namespace std;

namespace _String
{
#if __cplusplus < 201103L
string to_string(double x)
{
	stringstream ss;
	string result;
	ss << x;
	ss >> result;
	return result;
}
#endif
}

