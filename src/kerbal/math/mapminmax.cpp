/*
 * mapminmax.cpp
 *
 *  Created on: 2017年7月13日
 *      Author: Peter
 *      Fuction:
 */

#include "mapminmax.hpp"
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
						friend class mapminmax::Mapminmax;
				};

				Record::Record(size_t len, double max, double min) :
						len(len), max(max), min(min)
				{
				}
			}

			Mapminmax::map_type Mapminmax::arr_record;

			void Mapminmax::mapminmax(double array[], size_t len)
			{
				if (arr_record.find(array) == arr_record.end()) { //未找到
					double MaxValue;
					double MinValue;
					kerbal::max_and_min(array, len, MaxValue, MinValue);

					arr_record.insert(std::make_pair(array, Record(len, MaxValue, MinValue)));

					double k = 2.0 / (MaxValue - MinValue);
					double b = (MaxValue + MinValue) / 2.0;

					for (double * it = array, * const end = array + len; it != end; ++it) {
						*it = k * (*it - b);
					}
				}
			}

			void Mapminmax::anti_mapminmax(double array[]) throw (std::invalid_argument)
			{
				//数据逆归一化
				Mapminmax::map_type::iterator it = arr_record.find(array);
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

			double Mapminmax::anti_mapminmax(double element, double reference[]) throw (std::invalid_argument)
			{
				//数据逆归一化
				Mapminmax::map_type::iterator it = arr_record.find(reference);
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
		using namespace mapminmax;

	} /* namespace math */
	using namespace math;

} /* namespace kerbal */
