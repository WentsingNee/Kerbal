/*
 * range.hpp
 *
 *  Created on: 2017年7月17日
 *      Author: Peter
 *      Fuction: 本文件提供了对 range 的支持, 使得可以像 Python 中一样使用 for_each 风格的循环。
 *      		  本文件需要 C++ 11 及以上版本编译器的支持
 *
 *  2018年6月10日 第二版 不再需要 C++ 11 及以上版本编译器的支持，且支持了模板
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

#ifndef KERBAL_INCLUDE_KERBAL_UTILITY_RANGE_HPP_
#define KERBAL_INCLUDE_KERBAL_UTILITY_RANGE_HPP_

#include <exception>

namespace kerbal
{
	namespace utility
	{
		namespace range
		{
			template <typename Type>
			class Range_view;

			template <typename Type>
			inline Range_view<Type> range(Type to)
			{
				return Range_view<Type>(to);
			}

			template <typename Type>
			inline Range_view<Type> range(Type from, Type to)
			{
				return Range_view<Type>(from, to);
			}

			template <typename Type>
			inline Range_view<Type> range(Type from, Type to, Type step)
			{
				return Range_view<Type>(from, to, step);
			}

			template <typename Type>
			class Range_view
			{
				protected:
					typedef struct iterator
					{
						protected:
							friend class Range_view;

							const Range_view * const parent_ptr;
							Type now;

							iterator(const Range_view * const parent_ptr, const Type & now) :
									parent_ptr(parent_ptr), now(now)
							{
							}

						public:
							Type operator*() const
							{
								return now;
							}

							iterator& operator++()
							{
								//前自增
								now += parent_ptr->step;
								return *this;
							}

							bool operator!=(const iterator &with) const
							{
								return with.parent_ptr->whether_in(this->now);
							}

					} iterator;

					const Type from, to, step;

					Range_view(Type to) :
							from(0), to(to), step(1)
					{
					}

					Range_view(Type from, Type to, Type step = 1) :
							from(from), to(to), step(step)
					{
						if (step == 0) {
							throw std::invalid_argument("range() arg 3 must not be zero");
						}
					}

					friend Range_view<Type> range<>(Type to);
					friend Range_view<Type> range<>(Type from, Type to);
					friend Range_view<Type> range<>(Type from, Type to, Type step);

				public:
					iterator begin() const
					{
						if (from == to || (from > to && step > 0) || (from < to && step < 0)) {
							return end();
						}
						return iterator(this, from);
					}

					iterator end() const
					{
						return iterator(this, to);
					}

					bool whether_in(const Type & x) const
					{ //检查游标x是否在范围内
						if (from < to) {
							return (from <= x && x < to);
						} else {
							return (to < x && x <= from);
						}
					}
			};

		} /* namespace range */

	} /* namespace utility */

} /* namespace kerbal */

#endif /* KERBAL_INCLUDE_KERBAL_UTILITY_RANGE_HPP_ */
