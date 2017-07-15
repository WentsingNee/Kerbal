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
#include <stdexcept>

#include "Matrix.h"

using namespace std;

#if __cplusplus < 201103L //C++0x
# pragma message("Complexor 使用了 C++ 11 新特性, 请打开 C++ 11 选项以便使用这些新特性")
#else
#include <initializer_list>
#endif //C++0x

class Complexor //: public Matrix
{
	protected:
		double *p;
		int num;
		bool vertical; //默认列向量

		void test_index(int num_test) const throw (out_of_range)
		{
			if (num_test < 0 || num_test >= num) {
				throw out_of_range("");
			}
		}

	public:
		Complexor(const int num = 0, const bool if_set0 = true, const bool vertical = true);
		Complexor(const Complexor &src);
		Complexor(const Matrix &src, int index = 0, const bool vertical = true);
		Complexor(double src[], const int num, const bool vertical = true);

#if __cplusplus < 201103L //C++0x
//# pragma message("Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行构造")
#else
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
#endif

		/*explicit */
		operator Matrix()
		{
			if (this->vertical) {
				Matrix result(num, 1, false);
				for (int i = 0; i < num; i++) {
					result.set_element(i, 0, p[i]);
				}
				return result;
			} else {
				Matrix result(1, num, false);
				for (int i = 0; i < num; i++) {
					result.set_element(0, i, p[i]);
				}
				return result;
			}
		}
		virtual ~Complexor();
		bool is_const();
		bool is_const() const;

		bool empty() const;
		void clear();

		void set_element(int index, int value) throw (out_of_range)
		{
			test_index(index);
			p[index] = value;
		}

		double get_element(int index) const throw (out_of_range)
		{
			test_index(index);
			return p[index];
		}

		int get_num() const
		{
			return num;
		}

		void print() const
		{
			cout << resetiosflags(ios::right) << setiosflags(ios::left) << setfill(' '); //清除右对齐, 设置左对齐, 设置不足补空格
			cout << "(";

			if (!empty()) {
				cout << "  " << setw(10) << p[0];
				for (int i = 1; i < num; i++) {
					cout << ", " << setw(10) << p[i];
				}
			}

			cout << " )";
			if (this->vertical) {
				cout << " T";
			}
			cout << endl;
		}

		size_t get_digit_size() const
		{
			return num * sizeof(double);
		}

		friend Complexor operator+(const Complexor &a, const Complexor &b) throw (invalid_argument); //向量加法, 返回列向量
		friend Complexor operator-(const Complexor &a, const Complexor &b) throw (invalid_argument); //向量减法, 返回列向量
		Complexor operator-() const; //返回向量的反向同长向量
		const Complexor& operator=(const Complexor &src);
		double& operator[](int index) throw (out_of_range);
		const double& operator[](int index) const throw (out_of_range);

		friend Complexor Transpose(const Complexor &src);

		friend Complexor operator*(const Matrix &M, const Complexor &V) throw (invalid_argument); //矩阵乘以列向量, 返回向量
		friend Complexor operator*(const Complexor &V, const Matrix &M) throw (invalid_argument); //行向量乘以矩阵, 返回向量
		friend double dot_product(const Complexor &a, const Complexor &b) throw (invalid_argument); //向量点积, 返回实数
		friend Matrix operator*(const Complexor &a, const Complexor &b) throw (invalid_argument); //向量乘以向量, 返回矩阵
		friend Complexor operator*(const int &k, const Complexor &b); //数k乘以向量
		friend Complexor operator*(const Complexor &b, const int &k); //向量乘以数k

		friend double abs(const Complexor &src); //向量的模

		friend void print_array_to_file(const Complexor &src, string separator, string file_name, bool if_output_number = false) throw (invalid_argument);

};
double operator^(const Complexor &a, const Complexor &b) throw (invalid_argument);
//向量夹角
Complexor eqution(Matrix m) throw (invalid_argument);

#endif /* COMPLEXOR_H_ */
