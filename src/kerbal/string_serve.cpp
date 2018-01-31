/**
 * @file string_serve.cpp
 * @date 2017-4-20
 * @author ÄßÎÄÇä
 */

#include "string_serve.hpp"

#include <sstream>

namespace kerbal
{
	namespace string_serve
	{
#	if __cplusplus < 201103L //C++0x
	std::string to_string(double x)
	{
		std::ostringstream ss;
		ss << x;
		return ss.str();
	}
	std::string to_string(float x)
	{
		std::ostringstream ss;
		ss << x;
		return ss.str();
	}
	std::string to_string(int x)
	{
		std::ostringstream ss;
		ss << x;
		return ss.str();
	}

#	endif //C++0x
}
/* namespace string_serve */

}/* namespace kerbal */

