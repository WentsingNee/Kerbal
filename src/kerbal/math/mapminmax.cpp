/*
 * mapminmax.cpp
 *
 *  Created on: 2017年7月13日
 *      Author: Peter
 *      Fuction:
 */

#include "mapminmax.hpp"
#include <map>
#include "statistics.hpp"

namespace kerbal
{
	namespace math
	{
		namespace mapminmax
		{

			namespace
			{
				class Record
				{
					private:
						size_t len;
						double max;
						double min;

						Record(size_t len, double max, double min);
					public:
						friend void mapminmax::mapminmax(double array[], size_t len);
						friend void mapminmax::anti_mapminmax(double array[]) throw (std::invalid_argument);
						friend double mapminmax::anti_mapminmax(double element, double reference[]) throw (std::invalid_argument);
				};

				Record::Record(size_t len, double max, double min) :
						len(len), max(max), min(min)
				{
				}

				typedef std::map<double *, Record> map_type;
				map_type arr_record;

			}/* namespace anonymous */

			void mapminmax(double array[], size_t len)
			{
				//数据归一化
				if (arr_record.find(array) == arr_record.end()) { //未找到
					double MaxValue;
					double MinValue;
					kerbal::math::statistics::max_and_min(array, len, MaxValue, MinValue);

					arr_record.insert(std::make_pair(array, Record(len, MaxValue, MinValue)));

					double k = 2.0 / (MaxValue - MinValue);
					double b = (MaxValue + MinValue) / 2.0;

					for (double * it = array, * const end = array + len; it != end; ++it) {
						*it = k * (*it - b);
					}
				}
			}

			void anti_mapminmax(double array[]) throw (std::invalid_argument)
			{
				//数据逆归一化
				map_type::iterator it = arr_record.find(array);
				if (it == arr_record.end()) { //未找到
					throw std::invalid_argument("un mapped");
				}

				//已找到
				const Record & record = it->second;
				const double k = 2.0 / (record.max - record.min);
				const double b = (record.max + record.min) / 2.0;

				for (double * it = array, * const end = array + record.len; it != end; ++it) {
					*it = *it / k + b;
				}
				arr_record.erase(it);
			}

			double anti_mapminmax(double element, double reference[]) throw (std::invalid_argument)
			{
				//数据逆归一化
				map_type::iterator it = arr_record.find(reference);
				if (it == arr_record.end()) { //未找到
					throw std::invalid_argument("un mapped");
				}

				//已找到
				const Record & record = it->second;
				double k = 2.0 / (record.max - record.min);
				double b = (record.max + record.min) / 2.0;
				return element / k + b;
			}

		} /* namespace mapminmax */

	} /* namespace math */

} /* namespace kerbal */
