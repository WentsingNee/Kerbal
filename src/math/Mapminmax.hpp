/*
 * Mapminmax.hpp
 *
 *  Created on: 2017年7月13日
 *      Author: Peter
 *      Fuction: 本文件提供了对数据归一化与逆归一化的支持
 */

#ifndef MAPMINMAX_HPP_
#define MAPMINMAX_HPP_

#include <vector>
#include "statistics.hpp"

namespace statistics
{
	class Record
	{
		public:
			double* p;
			int len;
			double max;
			double min;

			Record(double *p, int len, double max, double min)
			{
				this->p = p;
				this->len = len;
				this->max = max;
				this->min = min;
			}
	};

	class Mapminmax
	{
		protected:
			static std::vector<Record> arr_record;
		public:
			static void mapminmax(double a[], int len);
			static void anti_mapminmax(double a[]);		//数据逆归一化
			static double anti_mapminmax(double a, double reference[]) throw (std::invalid_argument);
	};

	inline void mapminmax(double a[], int len)
	{
		//数据归一化
		Mapminmax::mapminmax(a, len);
	}

	inline void anti_mapminmax(double a[])
	{
		//数据逆归一化
		Mapminmax::anti_mapminmax(a);
	}

	inline double anti_mapminmax(double a, double reference[]) throw (std::invalid_argument)
	{
		return Mapminmax::anti_mapminmax(a, reference);
	}

	inline double map(double X, double x1, double y1, double x2, double y2)
	{
//	map的作用是将一个变量从它自己本身的范围转化到另一个范围。可以为map(X,x1,y1,x2,y2)
//	X为一个需要转化的变量。x1,y1为这个变量本来的范围。x2,y2为这个变量要映射到得范围。
		return (X - x1) / (y1 - x1) * (y2 - x2) + x2;
	}

} /* namespace statistics */

#endif /* End MAPMINMAX_HPP_ */
