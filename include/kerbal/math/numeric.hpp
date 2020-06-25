/**
 * @file string_serve.hpp
 * @date 2017-4-17
 * @author 倪文卿
 */

#ifndef _STRING_SERVE_HPP_
#define _STRING_SERVE_HPP_

#include <string>
#include <sstream>

#define STR1(R)  #R
#define MACRO_INT_TO_STR(R)  STR1(R)

namespace kerbal
{
	namespace math
	{
		namespace numeric
		{

#	if __cplusplus < 201103L //C++0x

			template <typename _Tp>
			inline std::string to_string(const _Tp & x)
			{
				std::ostringstream ss;
				ss << x;
				return ss.str();
			}

			inline std::string to_string(double x)
			{
				std::ostringstream ss;
				ss << x;
				return ss.str();
			}

			inline std::string to_string(float x)
			{
				std::ostringstream ss;
				ss << x;
				return ss.str();
			}

			inline std::string to_string(int x)
			{
				std::ostringstream ss;
				ss << x;
				return ss.str();
			}

#	else

			using std::to_string;

#	endif //C++0x


		} /* namespace numeric */

	} /* namespace math */

}/* namespace kerbal */

#endif	/* End _STRING_SERVE_HPP_ */
