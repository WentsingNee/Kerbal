/*
 * dbstream.cpp
 *
 *  Created on: 2017年9月2日
 *      Author: Peter
 */

#include "dbstream.hpp"

#include <iostream>

namespace kerbal
{
	namespace utility
	{
		namespace dbstream
		{
			Dbstream cdb;

			Dbstream::Dbstream() :
					new_line(true), out(&std::cout)
			{

			}

			void Dbstream::why_cannot_use()
			{
				if (debug) {
				} else {
					std::cout << "只有在调用program_start函数时,is_debug值传入的是true,调试输出流才会输出信息" << std::endl;
				}
			}

			Dbstream& Dbstream::operator<<(Dbstream& (*f)(Dbstream& __os))
			{
				f(*this);
				return *this;
			}

		} /* namespace dbstream */

	} /* namespace utility */

} /* namespace kerbal */
