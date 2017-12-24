/*
 * dbstream.hpp
 *
 *  Created on: 2017Äê9ÔÂ2ÈÕ
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

			class Dbstream
			{
				protected:
					bool new_line;
					std::ostream * out;

					friend inline Dbstream& endl(Dbstream& __dbs);

				public:
					Dbstream();
					void why_cannot_use();
					Dbstream& operator<<(Dbstream& (*f)(Dbstream& __os));

					template <class T>
					Dbstream& operator<<(const T &src);
			};

			extern Dbstream cdb;

			template <class T>
			Dbstream& Dbstream::operator<<(const T &src)
			{
				if (debug) {
					if (this->new_line) {
						*out << "- ";
						this->new_line = false;
					}
					*out << src;
				}
				return *this;
			}

			inline Dbstream& endl(Dbstream& __dbs)
			{
				if (debug) {
					if (__dbs.new_line) {
						*__dbs.out << "- ";
					}

					__dbs.new_line = true;
					*__dbs.out << std::endl;

				}
				return __dbs;
			}

		} /* namespace dbstream */

	} /* namespace utility */

} /* namespace kerbal */

#endif /* DBSTREAM_HPP_ */
