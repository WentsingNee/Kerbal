/*
 * mapminmax.cpp
 *
 *  Created on: 2017年7月13日
 *      Author: Peter
 *      Fuction:
 */

#ifndef MAPMINMAX_HPP_
#define MAPMINMAX_HPP_

#include "../except_C++0x.hpp"

namespace kerbal
{
	namespace math
	{
		namespace mapminmax
		{

			void mapminmax(double array[], size_t len);
			void anti_mapminmax(double array[]) throw (std::invalid_argument);
			double anti_mapminmax(double element, double reference[]) throw (std::invalid_argument);

			inline double mapto(double X, double x1, double y1, double x2, double y2)
			{
				/*
				 * mapto 的作用是将一个变量从它自己本身的范围转化到另一个范围。可以为map(X,x1,y1,x2,y2)
				 * X为一个需要转化的变量。x1,y1为这个变量本来的范围。x2,y2为这个变量要映射到的范围。
				 *
				 */

				return (X - x1) / (y1 - x1) * (y2 - x2) + x2;
			}

		} /* namespace mapminmax */

	} /* namespace math */

} /* namespace kerbal */

#endif /* End MAPMINMAX_HPP_ */
