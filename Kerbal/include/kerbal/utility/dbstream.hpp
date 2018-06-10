/*
 * dbstream.hpp
 *
 *  Created on: 2017年9月2日
 *      Author: Peter
 */

#ifndef DBSTREAM_HPP_
#define DBSTREAM_HPP_

#include <iostream>

extern bool debug;

namespace kerbal
{
	namespace utility
	{
		namespace dbstream
		{

			template <std::ostream & out = std::cout>
			class Dbstream
			{
				protected:
					bool new_line;

				public:
					Dbstream() :
							new_line(true)
					{
					}

					Dbstream& operator<<(Dbstream& (*f)(Dbstream& __os))
					{
						f(*this);
						return *this;
					}

					template <class T>
					Dbstream& operator<<(const T &src)
					{
						if (debug) {
							if (this->new_line) {
								out << "- ";
								this->new_line = false;
							}
							out << src;
						}
						return *this;
					}

					Dbstream& operator<<(std::ostream& (*__pf)(std::ostream&))
					{
						if (debug) {
							if (this->new_line) {
								out << "- ";
								this->new_line = false;
							}
							__pf(out);
							new_line = true;
						}
						return *this;
					}
			};

		} /* namespace dbstream */

	} /* namespace utility */

} /* namespace kerbal */

#endif /* DBSTREAM_HPP_ */
