/*
 * mapminmax.cpp
 *
 *  Created on: 2017年7月13日
 *      Author: Peter
 *      Fuction:
 */

#ifndef MAPMINMAX_HPP_
#define MAPMINMAX_HPP_

#include <stdexcept>

namespace kerbal
{
	namespace math
	{
		namespace mapminmax
		{

			void mapminmax(double array[], size_t len);

			/**
			 * @brief 将数组逆归一化
			 * @param array
			 * @throw std::invalid_argument 若该数组未经过 mapminmax 函数的处理, 则抛出此异常
			 */
			void anti_mapminmax(double array[]);

			/**
			 *
			 * @param element
			 * @param reference
			 * @return
			 * @throw std::invalid_argument 若该数组未经过 mapminmax 函数的处理, 则抛出此异常
			 */
			double anti_mapminmax(double element, double reference[]);

			/**
			 * @brief 将一个变量从它自己本身的范围转化到另一个范围。可以为 map(X, x1, y1, x2, y2)
			 * X 为一个需要转化的变量。x1, y1 为这个变量本来的范围。x2, y2 为这个变量要映射到的范围。
			 */
			inline double mapto(double X, double x1, double y1, double x2, double y2)
			{
				return (X - x1) / (y1 - x1) * (y2 - x2) + x2;
			}

		} /* namespace mapminmax */

	} /* namespace math */

} /* namespace kerbal */

#endif /* End MAPMINMAX_HPP_ */
