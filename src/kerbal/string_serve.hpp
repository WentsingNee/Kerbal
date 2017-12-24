#ifndef _STRING_SERVE_HPP_
#define _STRING_SERVE_HPP_

#include <string>

namespace kerbal
{
	namespace string_serve
	{

#	if __cplusplus < 201103L //C++0x
	std::string to_string(double x);
#	endif //C++0x

}
/* namespace string_serve */
using namespace string_serve;

}/* namespace kerbal */

#endif	/* End _STRING_SERVE_HPP_ */
