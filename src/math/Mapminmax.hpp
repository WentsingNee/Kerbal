/*
 * Mapminmax.hpp
 *
 *  Created on: 2017年7月13日
 *      Author: Peter
 *      Fuction: 提供了对数据归一化与逆归一化的支持
 */

#ifndef MAPMINMAX_HPP_
#define MAPMINMAX_HPP_

#include <vector>
#include "statistics.h"

using namespace std;

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
			static vector<Record> arr_record;
		public:
			static void mapminmax(double a[], int len);
			static void anti_mapminmax(double a[]);		//数据逆归一化
			static double anti_mapminmax(double a, double reference[]) throw (invalid_argument);
	};

} /* End of namespace statistics */
using namespace statistics;

inline void mapminmax(double a[], int len)		//数据归一化
{
	Mapminmax::mapminmax(a, len);
}

inline void anti_mapminmax(double a[])		//数据逆归一化
{
	Mapminmax::anti_mapminmax(a);
}

inline double anti_mapminmax(double a, double reference[]) throw (invalid_argument)
{
	return Mapminmax::anti_mapminmax(a, reference);
}

#endif /* End MAPMINMAX_HPP_ */
