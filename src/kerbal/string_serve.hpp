/**
 * @file string_serve.hpp
 * @date 2017-4-17
 * @author ÄßÎÄÇä
 */

#ifndef _STRING_SERVE_HPP_
#define _STRING_SERVE_HPP_

#include <string>
#include <sstream>

#define STR1(R)  #R
#define STR2(R)  STR1(R)

namespace kerbal
{
	namespace string_serve
	{

#	if __cplusplus < 201103L //C++0x
		template <typename _Tp>
		std::string to_string(const _Tp & x)
		{
			std::ostringstream ss;
			ss << x;
			return ss.str();
		}

//		std::string to_string(double x);
//
//		std::string to_string(float x);
//
//		std::string to_string(int x);
#	endif //C++0x

	}
/* namespace string_serve */

}/* namespace kerbal */

#endif	/* End _STRING_SERVE_HPP_ */
