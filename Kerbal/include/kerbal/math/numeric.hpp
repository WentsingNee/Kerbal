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

			template <class T>
			std::string bit_of(const T &a)
			{
				std::string result = "";
				char *p = (char *) (&a) + sizeof(T) / sizeof(char);
				while (p != (char *) (&a)) {
					--p;
					for (int j = 8 * sizeof(char) - 1; j >= 0; j--) {
						if ((*p >> j) & 1) {
							result += '1';
						} else {
							result += '0';
						}
					}
					result += " ";
				}
				return result;
			}

			inline std::string bit_of(const char * a)
			{
				std::string result = "";
				for (const char *p = a; *p; ++p) {
					for (int j = 7; j >= 0; --j) {
						if ((*p >> j) & 1) {
							result += '1';
						} else {
							result += '0';
						}
					}
					result += " ";
				}
				return result;
			}

			inline std::string bit_of(const std::string &a)
			{
				return bit_of(a.c_str());
			}

			inline std::string ocx_of(char src)
			{
				std::string buffer(2, '\0');

				unsigned char tmp = src;
				tmp >>= 4;
				buffer[0] = char(tmp > 9 ? tmp + 55 : tmp + '0'); //55 means 'A'-10

				tmp = src;
				tmp &= 0x0f;
				buffer[1] = char(tmp > 9 ? tmp + 55 : tmp + '0');
				return buffer;
			}

			inline std::string ocx_of(const char * a)
			{
				std::string result = "";
				const char *p = a;
				while (*p) {
					(result += ocx_of(*p)) += " ";
					++p;
				}
				return result;
			}

			inline std::string ocx_of(const std::string &a)
			{
				return ocx_of(a.c_str());
			}

			template <class T>
			std::string ocx_of(const T &a)
			{
				std::string result = "";
				char * p = (char *) (&a) + sizeof(T) / sizeof(char);
				while (p != (char *) (&a)) {
					--p;
					(result += ocx_of(*p)) += " ";
				}
				return result;
			}

		} /* namespace numeric */

	} /* namespace math */

}/* namespace kerbal */

#endif	/* End _STRING_SERVE_HPP_ */
