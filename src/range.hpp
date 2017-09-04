/*
 * range.hpp
 *
 *  Created on: 2017年7月17日
 *      Author: Peter
 *      Fuction: 本文件提供了对 range 的支持, 使得可以像 Python 中一样使用 for_each 风格的循环。
 *      		  本文件需要 C++ 11 及以上版本编译器的支持
 *
 * Python 的循环
 * for i in range(10, 20):
 *     print(i)
 *
 * C++ 11 风格
 * for (int i : range(10, 20)) {
 *     cout << i << endl;
 * }
 *
 *
 * Python 的循环
 * for i in range(10):
 *     print(i)
 *
 * C++ 11 风格
 * for (int i : range(10)) {
 *     cout << i << endl;
 * }
 *
 */

#ifndef RANGE_HPP_
#define RANGE_HPP_

#include "except_C++0x.hpp"

#if __cplusplus >= 201103L //C++0x

namespace Range
{
	class Range_record;
	//供Range_iterator使用的前向引用声明
	class Range_iterator final
	{
			friend class Range_record;
		protected:
			int now;
			const Range_record * parent_ptr;

			Range_iterator(int now, const Range_record &parent);

		public:
			int operator*() const;
			Range_iterator& operator++();
			bool operator!=(const Range_iterator &with) const;
	};

	class Range_record final
	{
		protected:
			friend class Range_iterator;

			int from, to, step;

			Range_record(int to);
			Range_record(int from, int to, int step = 1) throw (std::invalid_argument);

			friend Range_record range(int to);
			friend Range_record range(int from, int to, int step);

		public:
			Range_iterator begin() const
			{
				if ((from < to && step < 0) || from == to || (from > to && step > 0)) {
					return end();
				}
				return Range_iterator(from, *this);
			}

			Range_iterator end() const
			{
				return Range_iterator(to, *this);
			}

			bool whether_in(int x) const
			{ //检查游标x是否在范围内
				if (from < to) {
					return (from <= x && x < to);
				} else {
					return (to < x && x <= from);
				}
			}
	};

	inline Range_record range(int from, int to, int step = 1)
	{
		return Range_record(from, to, step);
	}

	inline Range_record range(int to)
	{
		return Range_record(0, to, 1);
	}

} /* namespace Range */

#endif /* End C++0x */

#endif /* End RANGE_HPP_ */
