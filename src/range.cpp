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

#include "range.hpp"
namespace Range
{
	Range_iterator::Range_iterator(int now, const Range_record &parent)
	{
		this->now = now;
		this->parent_ptr = &parent;
	}

	int Range_iterator::operator*() const
	{
		return now;
	}

	Range_iterator& Range_iterator::operator++()
	{
		//前自增
		now += parent_ptr->step;
		return *this;
	}

	bool Range_iterator::operator!=(const Range_iterator &with) const
	{
		return with.parent_ptr->whether_in(this->now);
	}

	Range_record::Range_record(int to)
	{
		this->from = 0;
		this->to = to;
		this->step = 1;
	}

	Range_record::Range_record(int from, int to, int step) throw (std::invalid_argument)
	{
		if (step == 0) {
			throw std::invalid_argument("range() arg 3 must not be zero");
		}
		this->from = from;
		this->to = to;
		this->step = step;
	}

} /* namespace Range */

#endif /* End C++0x */
