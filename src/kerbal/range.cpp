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

namespace kerbal
{
	namespace Range
	{
		Range_view::iterator::Range_iterator(int now, const Range_view * const parent_ptr) :
				now(now), parent_ptr(parent_ptr)
		{
		}

		int Range_view::iterator::operator*() const
		{
			return now;
		}

		Range_view::iterator& Range_view::iterator::operator++()
		{
			//前自增
			now += parent_ptr->step;
			return *this;
		}

		bool Range_view::iterator::operator!=(const Range_view::iterator &with) const
		{
			return with.parent_ptr->whether_in(this->now);
		}

		Range_view::Range_view(int to) :
				from(0), to(to), step(1)
		{
		}

		Range_view::Range_view(int from, int to, int step) throw (std::invalid_argument) :
				from(from), to(to), step(step)
		{
			if (step == 0) {
				throw std::invalid_argument("range() arg 3 must not be zero");
			}
		}

		Range_view::iterator Range_view::begin() const
		{
			if ((from < to && step < 0) || from == to || (from > to && step > 0)) {
				return end();
			}
			return Range_iterator(from, this);
		}

		Range_view::iterator Range_view::end() const
		{
			return Range_iterator(to, this);
		}

		bool Range_view::whether_in(int x) const
		{ //检查游标x是否在范围内
			if (from < to) {
				return (from <= x && x < to);
			} else {
				return (to < x && x <= from);
			}
		}

	} /* namespace Range */
	using namespace Range;

} /* namespace kerbal */

#endif /* End C++0x */
