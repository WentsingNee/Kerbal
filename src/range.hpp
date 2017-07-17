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
