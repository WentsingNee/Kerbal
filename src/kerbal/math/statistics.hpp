#ifndef _STATISTICS_HPP_
#define _STATISTICS_HPP_

#include <math.h>

#include "basic_math.hpp"
#include "../except_C++0x.hpp"

namespace kerbal
{
	namespace math
	{
		namespace statistics
		{
			template <class T> T maximum(const T a[], int len);
			template <class T> T minimum(const T a[], int len);
			template <class T> void max_and_min(const T a[], int len, T& max, T& min);
			template <class T> double ave(const T a[], int len);
			template <class T> double geoave(const T a[], int len); //geometric mean
			template <class T> double harave(const T a[], int len); //harmonic mean
			template <class T> double squave(const T a[], int len); //squ
			template <class T> double var(const T a[], int len); //方差
			unsigned long long fact(unsigned int n); //计算阶乘, 目前可算到20!
			unsigned long combine(int n, int r) throw (std::invalid_argument);
			inline double normdist(double x, double sigma, double miu); //正态分布的概率密度函数, miu=ave, sigma=expect
			inline double std_normdist(double x); //标准正态分布的概率密度函数, miu=ave, sigma=expect
			double broad_combine(double a, unsigned int r);
			double regression(const double x[], const double y[], int len, double &a, double &b); //线性回归
			//double tdist_unint_n(double x,unsigned int n);

			template <class T>
			T maximum(const T a[], int len)
			{
				const T *p_to_max = a;
				for (int i = 1; i < len; i++) {
					if (a[i] > *p_to_max) {
						p_to_max = a + i;
					}
				}
				return *p_to_max;
			}

			template <class T>
			T minimum(const T a[], int len)
			{
				const T *p_to_min = a;
				for (int i = 1; i < len; i++) {
					if (a[i] < *p_to_min) {
						p_to_min = a + i;
					}
				}
				return *p_to_min;
			}

			template <class T>
			void max_and_min(const T a[], int len, T& max, T& min)
			{
				const T *p_to_max = a;
				const T *p_to_min = a;
				for (int i = 1; i < len; i++) {
					if (a[i] > *p_to_max) {
						p_to_max = a + i;
					} else if (a[i] < *p_to_min) {
						p_to_min = a + i;
					}
				}
				max = *p_to_max;
				min = *p_to_min;
			}

			template <class T>
			double ave(const T a[], int len)
			{
				double sum = a[0];

				for (int i = 1; i < len; i++) {
					sum += a[i];
				}
				return (sum / len);
			}

			template <class T>
			double geoave(const T a[], int len)
			{
				double product = a[0];

				for (int i = 1; i < len; i++) {
					product *= a[i];
				}
				return (pow(product, 1.0 / len));
			}

			template <class T>
			double harave(const T a[], int len)
			{
				double sum = 1.0 / a[0];

				for (int i = 1; i < len; i++) {
					sum += 1.0 / a[i];
				}
				return (len / sum);
			}

			template <class T>
			double squave(const T a[], int len)
			{
				double sum = 0;

				for (int i = 0; i < len; i++) {
					sum += a[i] * a[i];
				}
				return (sqrt(sum / len));
			}

			template <class T>
			double var(const T a[], int len) //方差
			{
				double squsum = 0, sum = 0;

				for (int i = 0; i < len; i++) {
					squsum += a[i] * a[i];
					sum += a[i];
				}

				double &ave = sum;
				ave /= len;
				return squsum / len - (ave * ave);
			}

			inline double normdist(double x, double sigma, double miu) //正态分布的概率密度函数, miu=ave, sigma=expect
			{
				return exp(pow((x - miu) / sigma, 2) / (-2)) / sqrt(2 * M_PI) / sigma;
			}

			inline double std_normdist(double x) //标准正态分布的概率密度函数, miu=ave, sigma=expect
			{
				return exp(x * x / (-2)) / sqrt(2 * M_PI);
			}

		}/* namespace statistics */
		using namespace statistics;
	} /* namespace math */
	using namespace math;
} /* namespace kerbal */

#endif	/* End _STATISTICS_HPP_ */
