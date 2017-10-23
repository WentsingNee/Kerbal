/*
 * Complexor_base.hpp
 *
 *  Created on: 2017年10月8日
 *      Author: Peter
 */

#ifndef MATH_COMPLEXOR_BASE_HPP_
#define MATH_COMPLEXOR_BASE_HPP_

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Matrix.hpp"
#include "../except_C++0x.hpp"

namespace complexor
{
	using namespace std;
	using namespace matrix;

	template <class Type> class Complexor;

	template <class Type>
	void Complexor<Type>::resize(int new_num)
	{ //TODO BUG
		bool alloc = false;
		if (alloc) {
			//new[] delete[]方案
			Type *p_former = p;
			try {
				p = new Type[new_num];
				std::copy(p_former, p_former + std::min(num, new_num), p);
				num = new_num;
				delete[] p_former;
				p_former = NULL;
			} catch (const bad_alloc &exct) { //内存分配失败
				delete[] p_former;
				num = 0;
				p_former = NULL;
				p = NULL;
				throw;
			}
		} else {
			//alloc方案
			Type *p_new = (Type*) realloc(p, new_num * sizeof(Type));
			if (p_new == NULL) { //内存分配失败
				num = 0;
				free (p);
				p = NULL;
				p_new = NULL;
				throw bad_alloc();
			} else { //内存分配成功
				p = p_new;
				num = new_num;
				p_new = NULL;
			}
		}
	}

//	template <class Type>
//	Complexor<Type>::Complexor(const int num, const bool if_set0, const bool vertical) throw (bad_alloc)
//	{
//		if (num > 0) {
//			this->num = num;
//			mem_init();
//			if (if_set0) {
//				memset(p, 0, num * sizeof(Type));
//			}
//		} else {
//			this->num = 0;
//			this->p = NULL;
//		}
//		this->vertical = vertical;
//	}

	template <class Type>
	Complexor<Type>::Complexor(const int num) throw (bad_alloc)
	{
		if (num > 0) {
			this->num = num;
			mem_init();
		} else {
			this->num = 0;
			this->p = NULL;
		}
		this->vertical = true;
	}

	template <class Type>
	Complexor<Type>::Complexor(const int num, const Type &val, const bool vertical) throw (bad_alloc)
	{
		if (num > 0) {
			this->num = num;
			mem_init();
			for (int i = 0; i < num; ++i) {
				p[i] = val;
			}
		} else {
			this->num = 0;
			this->p = NULL;
		}
		this->vertical = vertical;
	}

	template <class Type>
	Complexor<Type>::Complexor(const Complexor<Type> &src) throw (bad_alloc)
	{
		if (src.num > 0) {
			this->num = src.num;
			mem_init();
			std::copy(src.p, src.p + src.num, p);
		} else {
			this->num = 0;
			this->p = NULL;
		}
		this->vertical = src.vertical;
	}

	template <class Type>
	Complexor<Type>::Complexor(const Matrix &src, int index, const bool vertical) throw (bad_alloc)
	{
		if (vertical) {
			this->num = src.get_row();
			mem_init();
			for (int i = 0; i < num; i++) {
				p[i] = src.get_data()[i][index];
			}
		} else {
			this->num = src.get_column();
			mem_init();
			const Type * const p_to_row_first = src.get_data()[index];
			std::copy(p_to_row_first, p_to_row_first + num, p);
		}
		this->vertical = vertical;
	}

	template <class Type>
	Complexor<Type>::Complexor(const Type src[], const int num, const bool vertical) throw (bad_alloc)
	{
		if (num > 0) {
			this->num = num;
			mem_init();
			std::copy(src, src + num, p);
		} else {
			this->num = 0;
			p = NULL;
		}
		this->vertical = vertical;
	}

	template <class Type>
	Complexor<Type>::Complexor(Type (*function)(), const int num, const bool vertical) throw (bad_alloc)
	{
		if (num > 0) {
			this->num = num;
			mem_init();
			for (int i = 0; i < num; i++) {
				p[i] = function();
			}
		} else {
			this->num = 0;
			p = NULL;
		}
		this->vertical = vertical;
	}

	template <class Type>
	Complexor<Type>::Complexor(Type (*function)(int), const int num, const bool vertical) throw (bad_alloc)
	{
		if (num > 0) {
			this->num = num;
			mem_init();
			for (int i = 0; i < num; i++) {
				p[i] = function(i);
			}
		} else {
			this->num = 0;
			p = NULL;
		}
		this->vertical = vertical;
	}

#if __cplusplus >= 201103L //C++0x
	//Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行构造
	template <class Type>
	Complexor<Type>::Complexor(initializer_list<Type> src)
	{
		num = src.size();
		mem_init();
		vertical = true;

		std::copy(src.begin(), src.end(), p);
	}

	//Complexor 为 C++ 11 准备的新特性: 转移构造函数
	template <class Type>
	Complexor<Type>::Complexor(Complexor &&src)
	{
		num = src.num;
		p = src.p;

		src.p = NULL;
		src.num = 0;

		vertical = src.vertical;
	}

#endif //C++0x

	template <class Type>
	Complexor<Type>::operator Matrix()
	{
		if (this->vertical) {
			Matrix result(num, 1);
			for (int i = 0; i < num; i++) {
				result.get_element(i, 0) = p[i];
			}
			return result;
		} else {
			Matrix result(1, num);
			for (int i = 0; i < num; i++) {
				result.get_element(0, i) = p[i];
			}
			return result;
		}
	}

	template <class Type>
	Complexor<Type>::~Complexor()
	{
		clear();
	}

	template <class Type>
	inline bool Complexor<Type>::is_const()
	{
		return false;
	}

	template <class Type>
	inline bool Complexor<Type>::is_const() const
	{
		return true;
	}

	template <class Type>
	inline bool Complexor<Type>::empty() const
	{
		if (num == 0) {
			return true;
		} else {
			return false;
		}
	}

	template <class Type>
	inline void Complexor<Type>::clear()
	{
		delete[] p;
		p = NULL;
		num = 0;
	}

	template <class Type>
	const Complexor<Type> Complexor<Type>::call(Type (*__pf)(Type))
	{
		Complexor < Type > result(this->num, false, this->vertical);
		for (int i = 0; i < num; ++i) {
			result.p[i] = __pf(this->p[i]);
		}
		return result;
	}

	template <class Type>
	inline void Complexor<Type>::set_element(int index, const Type &value) throw (out_of_range)
	{
		test_index(index);
		p[index] = value;
	}

	template <class Type>
	inline Type& Complexor<Type>::get_element(int index) throw (out_of_range)
	{
		test_index(index);
		return p[index];
	}

	template <class Type>
	inline const Type& Complexor<Type>::get_element(int index) const throw (out_of_range)
	{
		test_index(index);
		return p[index];
	}

	template <class Type>
	inline int Complexor<Type>::get_num() const
	{
		return num;
	}

	template <class Type>
	inline bool Complexor<Type>::is_vertical() const
	{
		return vertical;
	}

	template <class Type>
	inline const Type* Complexor<Type>::get_data() const
	{
		return p;
	}

	template <class Type>
	inline Type* const Complexor<Type>::begin() const
	{
		return p;
	}

	template <class Type>
	inline Type* const Complexor<Type>::end() const
	{
		return p + num;
	}

	template <class Type>
	inline size_t Complexor<Type>::get_digit_size() const
	{
		return num * sizeof(Type);
	}

	template <class Type>
	void Complexor<Type>::print() const
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

	template <class Type>
	Type& Complexor<Type>::operator[](int index) throw (out_of_range)
	{
		test_index(index);
		return p[index];
	}

	template <class Type>
	const Type& Complexor<Type>::operator[](int index) const throw (out_of_range)
	{
		test_index(index);
		return p[index];
	}

	template <class Type>
	const Complexor<Type> operator+(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument) //向量加法, 方向不同一律返回列向量
	{
		if (a.num != b.num) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		const int &num = a.num;
		Complexor<Type> result(num, false, a.vertical == b.vertical ? a.vertical : true);
		for (int i = 0; i < num; i++) {
			result.p[i] = a.p[i] + b.p[i];
		}
		return result;
	}

	template <class Type>
	const Complexor<Type> operator-(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument) //向量减法, 返回列向量
	{
		if (a.num != b.num) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		const int &num = a.num;
		Complexor<Type> result(num, false, a.vertical == b.vertical ? a.vertical : true);
		for (int i = 0; i < num; i++) {
			result.p[i] = a.p[i] - b.p[i];
		}
		return result;
	}

#if __cplusplus >= 201103L //C++0x
	template <class Type1, class Type2>
	auto operator+(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (invalid_argument) ->const Complexor<decltype(a[0]+b[0])>
	//两个不同类型向量的加法, 方向不同一律返回列向量, 自动推导返回类型, 例: Complexor<int> + Complexor<double> = Complexor<double>
	{
		if (a.get_num() != b.get_num()) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		const int &num = a.get_num();

		Complexor<decltype(a[0]+b[0])> result(num, false, a.is_vertical() == b.is_vertical() ? a.is_vertical() : true);
		for (int i = 0; i < num; i++) {
			result.set_element(i, a.get_data()[i] + b.get_data()[i]);
		}
		return result;
	}

	template <class Type1, class Type2>
	auto operator-(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (invalid_argument)->const Complexor<decltype(a[0]-b[0])>
	//两个不同类型向量的减法, 方向不同一律返回列向量, 自动推导返回类型, 例: Complexor<int> - Complexor<double> = Complexor<double>
	{
		if (a.get_num() != b.get_num()) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		const int &num = a.get_num();

		Complexor<decltype(a[0]-b[0])> result(num, false, a.is_vertical() == b.is_vertical() ? a.is_vertical() : true);
		for (int i = 0; i < num; i++) {
			result.set_element(i, a.get_data()[i] - b.get_data()[i]);
		}
		return result;
	}
#endif //C++0x

	template <class Type>
	Complexor<Type>& Complexor<Type>::operator+=(const Complexor<Type> &with) throw (invalid_argument)  //向量加法
	{
		if (num != with.num) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		for (int i = 0; i < num; i++) {
			p[i] += with.p[i];
		}

		return *this;
	}

	template <class Type>
	Complexor<Type>& Complexor<Type>::operator-=(const Complexor<Type> &with) throw (invalid_argument)  //向量加法
	{
		if (num != with.num) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		for (int i = 0; i < num; i++) {
			p[i] -= with.p[i];
		}

		return *this;
	}

	template <class Type>
	const Complexor<Type> Complexor<Type>::operator+() const //返回向量的同向同长向量
	{
		return Complexor(*this);
	}

	template <class Type>
	const Complexor<Type> Complexor<Type>::operator-() const //返回向量的反向同长向量
	{
		Complexor<Type> result(num, false, vertical);
		for (int i = 0; i < num; i++) {
			result.p[i] = -p[i];
		}
		return result;
	}

	template <class Type>
	Complexor<Type>& Complexor<Type>::operator=(const Complexor<Type> &src)
	{
		if (this->num != src.num) {
			delete[] p;
			this->num = src.num;
			p = new Type[num];
		} else if (this == &src) {
			return *this;
		}

		std::copy(src.p, src.p + num, p);
		this->vertical = src.vertical;
		return *this;
	}

#if __cplusplus >= 201103L //C++0x
	template <class Type>
	const Complexor<Type>& Complexor<Type>::operator=(Complexor<Type> &&src)
	{ //转移赋值运算符

		this->clear();
		num = src.num;
		p = src.p;

		src.p = NULL;
		src.num = 0;
		return *this;
	}
#endif

	template <class Type>
	Complexor<Type>& Complexor<Type>::doTranspose()
	{
		vertical = !vertical;
		return *this;
	}

	template <class Type>
	const Complexor<Type> TransposeOf(const Complexor<Type> &src)
	{
		Complexor<Type> result(src);
		src.vertical = !src.vertical;
		return result;
	}

	template <class Type>
	const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V) throw (invalid_argument) //矩阵乘以列向量
	{
		if (V.vertical) {
			if (M.get_column() != V.num) {
				throw invalid_argument(TRACE("column(M)!=num(V)", "operator*"));
			}
			const int &m = M.get_row();
			const int &n = V.num;
			Complexor<Type> result(m, true, true);
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					result.p[i] += M.get_data()[i][j] * V.p[j];
				}
			}
			return result;
		} else {
			throw invalid_argument("V must be a vector in vertical"); //向量必须为列向量
		}
	}

	template <class Type>
	const Complexor<Type> operator*(const Complexor<Type> &V, const Matrix &M) throw (invalid_argument) //行向量乘以矩阵
	{
		if (V.vertical) {
			throw invalid_argument("V must be a vector in horizontal");
		} else {
			if (V.num != M.get_row()) {
				throw invalid_argument("num(V)!=row(M)");
			}
			const int &m = V.num;
			const int &n = M.get_column();

			Complexor<Type> result(n, true, false);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					result.p[i] += V.p[j] * M.get_data()[j][i];
				}
			}
			return result;
		}
	}

	template <class Type>
	const Type dot_product(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument) //向量点积
	{
		if (a.num != b.num) {
			throw invalid_argument("num(a)!=num(b)");
		}
		const int &num = a.num;

		Type result = 0.0;
		for (int i = 0; i < num; i++) {
			result += a.p[i] * b.p[i];
		}
		return result;
	}

	template <class Type>
	const Matrix operator*(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument) //向量乘以向量, 返回矩阵
	{
		if (a.vertical == true && b.vertical == false) {
			const int &m = a.num;
			const int &n = b.num;

			Matrix result(m, n);
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					result.get_element(i, j) = a.p[i] * b.p[j];
				}
			}
			return result;
		} else {
			if (a.num != b.num) {
				throw invalid_argument("num(a)!=num(b)");
			}
			Matrix result(1, 1);
			result.get_element(0, 0) = dot_product(a, b);
			return result;
		}
	}

#if __cplusplus >= 201103L //c++0x
	template <class Type1, class Type2>
	auto dot_product(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (invalid_argument) ->const decltype(a[0]*b[0]) //向量点积
	{
		if (a.get_num() != b.get_num()) {
			throw invalid_argument("num(a)!=num(b)");
		}
		const int &num = a.get_num();

		decltype(a[0]*b[0]) result = 0.0;
		for (int i = 0; i < num; i++) {
			result += a.get_data()[i] * b.get_data()[i];
		}
		return result;
	}
#endif //c++0x

	template <class Type>
	const Complexor<Type> operator*(const double &k, const Complexor<Type> &b) //数k乘以向量
	{
		Complexor<Type> result(b);
		for (int i = 0; i < b.num; i++) {
			result.p[i] *= k;
		}
		return result;
	}

	template <class Type>
	const Complexor<Type> operator*(const Complexor<Type> &b, const double &k) //向量乘以数k
	{
		Complexor<Type> result(b);
		for (int i = 0; i < b.num; i++) {
			result.p[i] *= k;
		}
		return result;
	}

	template <class Type>
	Type abs(const Complexor<Type> &src) //向量的模
	{
		Type sum = 0.0;
		for (int i = 0; i < src.num; i++) {
			sum += src.p[i] * src.p[i];
		}
		return sqrt(sum);
	}

	template <class Type>
	Type angle(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument) //向量夹角
	{
		return acos(dot_product(a, b) / abs(a) / abs(b));
	}

//	template <class Type>
//	const Complexor<Type> eqution(Matrix m) throw (invalid_argument)
//	{
//		const int &row = m.get_row();
//		const int &column = m.get_column() - 1;
//		if (row != column) {
//			throw invalid_argument("不合法的增广矩阵");
//		}
//		const int &n = row;
//
//		for (int k = 0; k < n - 1; k++) {
//
//			Type max_ele = 0;
//			int i1 = 0;
//			int j1 = 0;
//
//			for (int i = k; i < n; i++) {
//				for (int j = k; j < n; j++) {
//					Type ele = m.get_data()[i][j];
//					if (fabs(ele) > fabs(max_ele)) {
//						max_ele = ele;
//						i1 = i;
//						j1 = j;
//					}
//				}
//			}
//
//			if (max_ele == 0) {
//				throw invalid_argument("不合法的增广矩阵");
//			}
//			m.switch_rows(k, i1);
//			m.switch_columns(k, j1);
//
//			for (int j = k + 1; j <= n; j++) {
//				//m[k][j] /= m[k][k];
//				m.get_element(k, j) /= m.get_data()[k][k];
//			}
//
//			for (int i = k + 1; i < n; i++) {
//				for (int j = k + 1; j <= n; j++) {
//					m[i][j] -= m.get_data()[i][k] * m.get_data()[k][j];
//				}
//			}
//		}
//
//		Complexor<Type> x(n, false, true);
//		x.p[n - 1] = m.get_data()[n - 1][n] / m.get_data()[n - 1][n - 1];
//		for (int i = n - 2; i >= 0; i--) {
//			Type sum = 0;
//			for (int j = i + 1; j < n; j++) {
//				sum += m.get_data()[i][j] * x[j];
//			}
//			x.p[i] = m.get_data()[i][n] - sum;
//		}
//
//		return x;
//
//	}
} /* namespace complexor */

#endif /* MATH_COMPLEXOR_BASE_HPP_ */
