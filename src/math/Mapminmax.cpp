/*
 * Mapminmax.cpp
 *
 *  Created on: 2017年7月13日
 *      Author: Peter
 *      Fuction:
 */

#include "Mapminmax.hpp"

namespace statistics
{
	std::vector<Record> Mapminmax::arr_record = std::vector<Record>();

	void Mapminmax::mapminmax(double a[], int len)
	{
		double MaxValue;
		double MinValue;
		max_and_min(a, len, MaxValue, MinValue);
		double k = 1.0 * 2 / (MaxValue - MinValue);
		double b = -(MaxValue + MinValue) / 2.0;
		for (int i = 0; i < len; i++) {
			a[i] = k * (a[i] + b);
		}

		arr_record.push_back(Record(a, len, MaxValue, MinValue));
	}

	void Mapminmax::anti_mapminmax(double a[])
	{
		//数据逆归一化
		for (unsigned int i = 0; i < arr_record.size(); i++) {
			if (arr_record[i].p == a) {
				int &len = arr_record[i].len;
				double &MaxValue = arr_record[i].max;
				double &MinValue = arr_record[i].min;
				double k = 1.0 * 2 / (MaxValue - MinValue);
				double b = -(MaxValue + MinValue) / 2.0;
				for (int i = 0; i < len; i++) {
					a[i] = a[i] / k - b;
				}
				return;
			}
		}
	}

	double Mapminmax::anti_mapminmax(double a, double reference[]) throw (std::invalid_argument)
	{
		//数据逆归一化
		for (unsigned int i = 0; i < arr_record.size(); i++) {
			if (arr_record[i].p == reference) {
				double &MaxValue = arr_record[i].max;
				double &MinValue = arr_record[i].min;
				double k = 1.0 * 2 / (MaxValue - MinValue);
				double b = -(MaxValue + MinValue) / 2.0;
				return a / k - b;
			}
		}
		throw std::invalid_argument("");
	}
} /* namespace statistics */

