/*
 * Complexor.h
 *
 *  Created on: 2017年5月8日
 *      Author: Peter
 */

#ifndef COMPLEXOR_H_
#define COMPLEXOR_H_

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Matrix.hpp"
#include "../except_C++0x.hpp"

namespace complexor
{
	using namespace std;
	using namespace matrix;

	class Complexor
	{
		protected:
			double *p;
			int num;
			bool vertical; //默认列向量

			void test_index(int num_test) const throw (out_of_range)
			{
				if (num_test < 0 || num_test >= num) {
					throw out_of_range("the complexor doesn't have the index");
				}
			}

		public:
			Complexor(const int num = 0, const bool if_set0 = true, const bool vertical = true) throw (bad_alloc);
			Complexor(const Complexor &src) throw (bad_alloc); //拷贝构造函数
			Complexor(const Matrix &src, int index = 0, const bool vertical = true) throw (bad_alloc);
			Complexor(const double src[], const int num, const bool vertical = true) throw (bad_alloc);
			Complexor(const int num, double (*function)(), const bool vertical = true) throw (bad_alloc);
			Complexor(const int num, double (*function)(int), const bool vertical = true) throw (bad_alloc);

#if __cplusplus >= 201103L //C++0x
			//Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行构造
			Complexor(initializer_list<double> a)
			{
				num = a.size();
				p = new double[num];
				vertical = true;

				int i = 0;
				for (auto ele : a) {
					p[i] = ele;
					i++;
				}
			}
#endif //C++0x

			/*explicit */
			operator Matrix()
			{
				try {
					if (this->vertical) {
						Matrix result(num, 1, false);
						for (int i = 0; i < num; i++) {
							result.get_element(i, 0) = p[i];
						}
						return result;
					} else {
						Matrix result(1, num, false);
						for (int i = 0; i < num; i++) {
							result.get_element(0, i) = p[i];
						}
						return result;
					}
				} catch (const bad_alloc &exct) {
					throw exct;
				}
			}
			virtual ~Complexor();
			bool is_const();
			bool is_const() const;

			bool empty() const;
			void clear();

			Complexor call(double (*__pf)(double))
			{
				Complexor result(this->num, false, this->vertical);
				for (int i = 0; i < num; ++i) {
					result.p[i] = __pf(this->p[i]);
				}
				return result;
			}

			void set_element(int index, const double &value) throw (out_of_range)
			{
				test_index(index);
				p[index] = value;
			}

			double& get_element(int index) throw (out_of_range)
			{
				test_index(index);
				return p[index];
			}

			const double& get_element(int index) const throw (out_of_range)
			{
				test_index(index);
				return p[index];
			}

			int get_num() const
			{
				return num;
			}

			void print() const;

			size_t get_digit_size() const
			{
				return num * sizeof(double);
			}

			friend Complexor operator+(const Complexor &a, const Complexor &b) throw (invalid_argument);
			//向量加法, 方向不同一律返回列向量
			Complexor& operator+=(const Complexor &with) throw (invalid_argument);  //向量加法
			Complexor operator+() const; //返回向量的反向同长向量
			friend Complexor operator-(const Complexor &a, const Complexor &b) throw (invalid_argument);
			//向量减法, 方向不同一律返回列向量
			Complexor& operator-=(const Complexor &with) throw (invalid_argument);  //向量加法
			Complexor operator-() const; //返回向量的反向同长向量

			Complexor& operator=(const Complexor &src);
			double& operator[](int index) throw (out_of_range);
			const double& operator[](int index) const throw (out_of_range);

			Complexor& doTranspose();
			friend Complexor TransposeOf(const Complexor &src);

			friend Complexor operator*(const Matrix &M, const Complexor &V) throw (invalid_argument);
			//矩阵乘以列向量, 返回向量
			friend Complexor operator*(const Complexor &V, const Matrix &M) throw (invalid_argument);
			//行向量乘以矩阵, 返回向量
			friend double dot_product(const Complexor &a, const Complexor &b) throw (invalid_argument);
			//向量点积, 返回实数
			friend Matrix operator*(const Complexor &a, const Complexor &b) throw (invalid_argument);
			//向量乘以向量, 返回矩阵
			friend Complexor operator*(const int &k, const Complexor &b); //数k乘以向量
			friend Complexor operator*(const Complexor &b, const int &k); //向量乘以数k

			friend double abs(const Complexor &src); //向量的模

//			friend void print_array_to_file(const Complexor &src, string separator, string file_name, bool if_output_number =
//					false) throw (invalid_argument);

			double* const begin() const
			{
				return p;
			}

			double* const end() const
			{
				return p + num;
			}
	};
	double operator^(const Complexor &a, const Complexor &b) throw (invalid_argument);
	//向量夹角
	Complexor eqution(Matrix m) throw (invalid_argument);

} /* namespace complexor */

#endif /* COMPLEXOR_H_ */
