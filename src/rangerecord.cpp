/*
 * range.cpp
 *
 *  Created on: 2017年7月17日
 *      Author: Peter
 *      Fuction:
 */

#if __cplusplus < 201103L //C++0x
# pragma message("\n"\
"			* range 使用了 C++ 11 新特性, 请打开 C++ 11 选项以便使用这些新特性"\
)
#else

#include "rangerecord.hpp"
namespace Range
{
	Range_record::Range_record(int to)
	{
		this->from = 0;
		if (to < 0) {
			this->to = to;
		} else {
			this->to = 0;
		}
		this->step = 1;
	}

	Range_record::Range_record(int from, int to, int step)
	{
		this->from = from;
		this->to = to;
		this->step = step;
	}

} /* End of namespace Range */

#endif /* End C++0x */
