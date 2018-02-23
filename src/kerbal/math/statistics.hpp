#ifndef _STATISTICS_HPP_
#define _STATISTICS_HPP_

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

#if __cplusplus >=201103L
			template <class InputIterator, class Return_type = double>
			Return_type ave(InputIterator first, InputIterator last);

			template <class InputIterator, class Return_type = double>
			Return_type geoave(InputIterator first, InputIterator last); //geometric mean

			template <class InputIterator, class Return_type = double>
			Return_type harave(InputIterator first, InputIterator last); //harmonic mean

			template <class InputIterator, class Return_type = double>
			Return_type squave(InputIterator first, InputIterator last); //squ

			template <class InputIterator, class Return_type = double>
			Return_type var(InputIterator first, InputIterator last); //方差
#else
					template <class InputIterator, class Return_type>
					Return_type ave(InputIterator first, InputIterator last);

					template <class InputIterator, class Return_type>
					Return_type geoave(InputIterator first, InputIterator last); //geometric mean

					template <class InputIterator, class Return_type>
					Return_type harave(InputIterator first, InputIterator last);//harmonic mean

					template <class InputIterator, class Return_type>
					Return_type squave(InputIterator first, InputIterator last);//squ

					template <class InputIterator, class Return_type>
					Return_type var(InputIterator first, InputIterator last);//方差

					template <class InputIterator>
					double ave(InputIterator first, InputIterator last);

					template <class InputIterator>
					double geoave(InputIterator first, InputIterator last);//geometric mean

					template <class InputIterator>
					double harave(InputIterator first, InputIterator last);//harmonic mean

					template <class InputIterator>
					double squave(InputIterator first, InputIterator last);//squ

					template <class InputIterator>
					double var(InputIterator first, InputIterator last);//方差
#endif

			unsigned long long fact(unsigned int n); //计算阶乘, 目前可算到20!
			unsigned long combine(int n, int r) throw (std::invalid_argument);
			double broad_combine(double a, unsigned int r);
			double normdist(double x, double sigma, double miu); //正态分布的概率密度函数, miu=ave, sigma=expect
			double std_normdist(double x); //标准正态分布的概率密度函数, miu=ave, sigma=expect
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

			template <class InputIterator, class Return_type>
			Return_type ave(InputIterator first, InputIterator last)
			{
				if (first != last) {
					Return_type sum = *first;
					size_t len = 1;
					++first;

					while (first != last) {
						sum = sum + *first; // or: init=binary_op(init,*first) for the binary_op version
						++first;
						++len;
					}
					return (sum / len);
				} else {
					throw std::domain_error("divided by zero!");
				}
			}

			template <class InputIterator, class Return_type>
			Return_type geoave(InputIterator first, InputIterator last)
			{
				if (first != last) {
					Return_type product = *first;
					size_t len = 1;
					++first;

					while (first != last) {
						product = product * *first; // or: init=binary_op(init,*first) for the binary_op version
						++first;
						++len;
					}
					return pow(product, 1.0 / len);
				} else {
					throw std::domain_error("divided by zero!");
				}
			}

			template <class InputIterator, class Return_type>
			Return_type harave(InputIterator first, InputIterator last)
			{
				if (first != last) {
					Return_type sum = (Return_type) (1) / (*first);
					size_t len = 1;
					++first;

					while (first != last) {
						Return_type sum = sum + (Return_type) (1) / (*first); // or: init=binary_op(init,*first) for the binary_op version
						++first;
						++len;
					}
					return (len / sum);
				} else {
					throw std::domain_error("divided by zero!");
				}
			}

			template <class InputIterator, class Return_type>
			Return_type squave(InputIterator first, InputIterator last)
			{
				if (first != last) {
					Return_type sum = (*first) * (*first);
					size_t len = 1;
					++first;

					while (first != last) {
						Return_type sum = sum + (*first) * (*first); // or: init=binary_op(init,*first) for the binary_op version
						++first;
						++len;
					}
					return sqrt(sum / len);
				} else {
					throw std::domain_error("divided by zero!");
				}
			}

			template <class InputIterator, class Return_type>
			Return_type var(InputIterator first, InputIterator last) //方差
			{
				if (first != last) {
					Return_type squsum = (*first) * (*first);
					Return_type sum = *first;
					size_t len = 1;

					while (first != last) {
						squsum = squsum + (*first) * (*first);
						sum = sum + *first;
						++first;
						++len;
					}

					Return_type ave = sum / len;
					return squsum / len - (ave * ave);
				} else {
					throw std::domain_error("divided by zero!");
				}
			}

#if __cplusplus < 201103L
		template <class InputIterator>
		double ave(InputIterator first, InputIterator last)
		{
			if (first != last) {
				double sum = *first;
				size_t len = 1;
				++first;

				while (first != last) {
					sum = sum + *first; // or: init=binary_op(init,*first) for the binary_op version
					++first;
					++len;
				}
				return (sum / len);
			} else {
				throw std::domain_error("divided by zero!");
			}
		}

		template <class InputIterator>
		double geoave(InputIterator first, InputIterator last)
		{
			if (first != last) {
				double product = *first;
				size_t len = 1;
				++first;

				while (first != last) {
					product = product * *first; // or: init=binary_op(init,*first) for the binary_op version
					++first;
					++len;
				}
				return pow(product, 1.0 / len);
			} else {
				throw std::domain_error("divided by zero!");
			}
		}

		template <class InputIterator>
		double harave(InputIterator first, InputIterator last)
		{
			if (first != last) {
				double sum = (double) (1) / (*first);
				size_t len = 1;
				++first;

				while (first != last) {
					double sum = sum + (double) (1) / (*first); // or: init=binary_op(init,*first) for the binary_op version
					++first;
					++len;
				}
				return (len / sum);
			} else {
				throw std::domain_error("divided by zero!");
			}
		}

		template <class InputIterator>
		double squave(InputIterator first, InputIterator last)
		{
			if (first != last) {
				double sum = (*first) * (*first);
				size_t len = 1;
				++first;

				while (first != last) {
					double sum = sum + (*first) * (*first); // or: init=binary_op(init,*first) for the binary_op version
					++first;
					++len;
				}
				return sqrt(sum / len);
			} else {
				throw std::domain_error("divided by zero!");
			}
		}

		template <class InputIterator>
		double var(InputIterator first, InputIterator last) //方差
		{
			if (first != last) {
				double squsum = (*first) * (*first);
				double sum = *first;
				size_t len = 1;

				while (first != last) {
					squsum = squsum + (*first) * (*first);
					sum = sum + *first;
					++first;
					++len;
				}

				double ave = sum / len;
				return squsum / len - (ave * ave);
			} else {
				throw std::domain_error("divided by zero!");
			}
		}
#endif

	}
/* namespace statistics */

} /* namespace math */

} /* namespace kerbal */

#endif	/* End _STATISTICS_HPP_ */
