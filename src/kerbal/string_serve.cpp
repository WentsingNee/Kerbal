#include "string_serve.hpp"

#include <sstream>

namespace kerbal
{
	namespace string_serve
	{
#	if __cplusplus < 201103L //C++0x
	std::string to_string(double x)
	{
		std::stringstream ss;
		std::string result;
		ss << x;
		ss >> result;
		return result;
	}
#	endif //C++0x
}
/* namespace string_serve */

}/* namespace kerbal */

