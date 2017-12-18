/*
 * mapminmax.cpp
 *
 *  Created on: 2017年7月13日
 *      Author: Peter
 *      Fuction:
 */

#ifndef MAPMINMAX_HPP_
#define MAPMINMAX_HPP_

#include <map>
#include "../except_C++0x.hpp"

namespace kerbal
{
	namespace math
	{
		namespace mapminmax
		{

			namespace
			{
				class Record;
			}

#if __cplusplus >= 201103L
#	define CXX_FINAL final
#else
#	define CXX_FINAL
#endif

			class Mapminmax CXX_FINAL
			{

#undef CXX_FINAL

				protected:
				typedef std::map<double *, Record> map_type;

				static map_type arr_record;

#if __cplusplus < 201103L
				Mapminmax()
				{
				}
#else
				Mapminmax() = delete;
#endif

				public:

				static void mapminmax(double array[], size_t len);
				static void anti_mapminmax(double array[]) throw (std::invalid_argument); //数据逆归一化
				static double anti_mapminmax(double a, double reference[]) throw (std::invalid_argument);
			};

			inline void mapminmax(double array[], size_t len)
			{
				//数据归一化
				Mapminmax::mapminmax(array, len);
			}

			inline void anti_mapminmax(double array[])
			{
				//数据逆归一化
				Mapminmax::anti_mapminmax(array);
			}

			inline double anti_mapminmax(double element, double reference[])
			{
				return Mapminmax::anti_mapminmax(element, reference);
			}

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
		using namespace mapminmax;

	} /* namespace math */
	using namespace math;

} /* namespace kerbal */

#endif /* End MAPMINMAX_HPP_ */
