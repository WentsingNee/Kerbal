/*
 * range.cpp
 *
 *  Created on: 2017年7月17日
 *      Author: Peter
 *      Fuction:
 */

#if __cplusplus < 201103L //C++0x
//# pragma message("range 使用了 C++ 11 新特性, 请打开 C++ 11 选项以便使用这些新特性")
#else

#include "range.hpp"
namespace range
{

	it::it(int now)
	{
		this->now = now;
	}

	int it::operator*() const
	{
		return now;
	}

	it& it::operator++()
	{
		//前自增
		now++;
		return *this;
	}

	bool it::operator!=(const it &with) const
	{
		return this->now != with.now;
	}

	range::range(int to)
	{
		if (to < 0) {
			this->from = to;
			this->to = to;
		} else {
			this->from = 0;
			this->to = to;
		}
	}

	range::range(int from, int to)
	{
		if (from > to) {
			this->from = to;
			this->to = to;
		} else {
			this->from = from;
			this->to = to;
		}
	}

	it range::begin() const
	{
		return it(from);
	}

	it range::end() const
	{
		return it(to);
	}

} /* End of namespace range */

#endif /* End C++0x */
