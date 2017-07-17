/*
 * range.hpp
 *
 *  Created on: 2017年7月17日
 *      Author: Peter
 *      Fuction:
 */

#ifndef RANGE_HPP_
#define RANGE_HPP_

#if __cplusplus < 201103L //C++0x
//# pragma message("range 使用了 C++ 11 新特性, 请打开 C++ 11 选项以便使用这些新特性")
#else

#include <algorithm>

using namespace std;

namespace range
{

	class it final
	{
		protected:
			int now;
			it(int now);
			friend class range;

		public:
			int operator*() const;
			it& operator++(); //前自增
			bool operator!=(const it &with) const;
	};

	class range final
	{
		protected:
			int from, to;
		public:
			range(int to);
			range(int from, int to);

			it begin() const;
			it end() const;
	};

} /* End of namespace range */
using namespace range;

#endif /* End C++0x */

#endif /* End RANGE_HPP_ */
