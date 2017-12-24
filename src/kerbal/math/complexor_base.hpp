/*
 * complexor_base.hpp
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
#include "../except_C++0x.hpp"
#include "matrix.hpp"

#if __cplusplus >= 201103L
#	include <functional>
#endif // C++0x

namespace kerbal
{
	namespace math
	{

		template <class Type, class In, class On>
		void for_each_placement_new(In _begin, In _end, On _place)
		{
			In src_it = _begin;
			On tar_it = _place;
			while (src_it != _end) {
				new (tar_it) Type(*src_it);
				++src_it;
				++tar_it;
			}
		}

		template <class Type> class Complexor;

		template <class Type>
		int Complexor<Type>::mem_init(int init_num) throw (std::bad_alloc)
		{
			if (init_num > 0) {
				this->p = (Type*) malloc(init_num * sizeof(Type));
				if (this->p == NULL) {
					this->num = 0;
					throw std::bad_alloc();
				}
				this->num = init_num;
			} else {
				this->num = 0;
				this->p = NULL;
			}
			return this->num;
		}

		template <class Type>
		void Complexor<Type>::resize(int new_num) throw (std::bad_alloc)
		{ //本函数负责析构, 但不负责构造
			if (new_num <= this->num) { //内存是缩小的
				if (new_num <= 0) {
					this->clear();
				} else {
					Type *ptr = this->p + this->num;
					const Type * const ptr_end = this->p + new_num;
					while (ptr != ptr_end) {
						(--ptr)->~Type();
					}
					this->p = (Type*) realloc(this->p, new_num * sizeof(Type));
					this->num = new_num;
				}
			} else {
				Type *p_new = (Type*) realloc(this->p, new_num * sizeof(Type));
				if (p_new == NULL) { //内存分配失败
					throw std::bad_alloc();
				} else { //内存分配成功

					this->p = p_new;
					this->num = new_num;
					p_new = NULL;
				}
			}
		}

		template <class Type>
		Complexor<Type>::Complexor(const int num) throw (std::bad_alloc) :
				vertical(true)
		{
			if (mem_init(num) > 0) {
				for (Type *ptr = this->p, *end = this->p + this->num; ptr != end; ++ptr) {
					new (ptr) Type();
				}
			}
		}

		template <class Type>
		Complexor<Type>::Complexor(const int num, const Type &val, const bool vertical) throw (std::bad_alloc) :
				vertical(vertical)
		{
			if (mem_init(num) > 0) {
				for (Type *ptr = this->p, *end = this->p + this->num; ptr != end; ++ptr) {
					new (ptr) Type();
				}
			}
		}

		template <class Type>
		Complexor<Type>::Complexor(const Complexor<Type> &src) throw (std::bad_alloc) :
				p(NULL), num(0), vertical(src.vertical)
		{
			if (mem_init(src.num) > 0) {
				for (int i = 0; i != this->num; ++i) {
					new (this->p + i) Type(src.p[i]);
				}
			}
		}

		template <class Type>
		template <class Type2>
		Complexor<Type>::Complexor(const Complexor<Type2> &src) throw (std::bad_alloc) :
				p(NULL), num(0), vertical(src.vertical)
		{ //转类型拷贝构造函数
			if (mem_init(src.num) > 0) {
				for (int i = 0; i != this->num; ++i) {
					new (this->p + i) Type(src.p[i]);
				}
			}
		}

		template <class Type>
		Complexor<Type>::Complexor(const Matrix &src, int index, const bool vertical) throw (std::out_of_range, std::bad_alloc) :
				vertical(vertical)
		{
			if (vertical) {
				src.test_column(index);
				if (mem_init(src.get_row()) > 0) {
					const double **srcp = src.get_data();
					for (int i = 0; i != this->num; i++) {
						new (this->p + i) Type(srcp[i][index]);
					}
				}
			} else {
				src.test_row(index);
				if (mem_init(src.get_column()) > 0) {
					const Type * const srcp_index = src.get_data()[index];
					for (int i = 0; i != this->num; i++) {
						new (this->p + i) Type(srcp_index[i]);
					}
				}
			}
		}

		template <class Type>
		Complexor<Type>::Complexor(const Type src[], const int num, const bool vertical) throw (std::bad_alloc) :
				vertical(vertical)
		{
			if (mem_init(num) > 0) {
				for_each_placement_new<Type>(src, src + num, this->p);
			}
		}

#if __cplusplus < 201103L //under C++0x
		template <class Type>
		Complexor<Type>::Complexor(Type (*function)(), const int num, const bool vertical) throw (std::bad_alloc) :
		vertical(vertical)
		{
			if (mem_init(num) > 0) {
				for (int i = 0; i != this->num; ++i) {
					new (this->p + i) Type(function());
				}
			}
		}

		template <class Type>
		Complexor<Type>::Complexor(Type (*function)(int), const int num, const bool vertical) throw (std::bad_alloc):
		vertical(vertical)
		{
			if (mem_init(num) > 0) {
				for (int i = 0; i != this->num; ++i) {
					new (this->p + i) Type(function(i));
				}
			}
		}
#endif //under C++0x

#if __cplusplus >= 201103L //C++0x

		template <class Type>
		Complexor<Type>::Complexor(std::function<Type()> function, const int num, const bool vertical) throw (std::bad_alloc) :
				vertical(vertical)
		{
			if (mem_init(num) > 0) {
				for (Type *ptr = this->p, *end = this->p + this->num; ptr != end; ++ptr) {
					new (ptr) Type(function());
				}
			}
		}

		template <class Type>
		Complexor<Type>::Complexor(std::function<Type(int)> function, const int num, const bool vertical) throw (std::bad_alloc) :
				vertical(vertical)
		{
			if (mem_init(num) > 0) {
				for (int i = 0; i != this->num; i++) {
					new (this->p + i) Type(function(i));
				}
			}
		}

//Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行构造
		template <class Type>
		Complexor<Type>::Complexor(std::initializer_list<Type> src) throw (std::bad_alloc) :
				p(NULL), num(0), vertical(true)
		{
			if (mem_init(src.size()) > 0) {
				for_each_placement_new<Type>(src.begin(), src.end(), this->p);
			}
		}

//Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行转类型构造
		template <class Type>
		template <class Type2>
		Complexor<Type>::Complexor(std::initializer_list<Type2> src) throw (std::bad_alloc) :
				p(NULL), num(0), vertical(true)
		{
			if (mem_init(src.size()) > 0) {
				for_each_placement_new<Type>(src.begin(), src.end(), this->p);
			}
		}

//Complexor 为 C++ 11 准备的新特性: 转移构造函数
		template <class Type>
		Complexor<Type>::Complexor(Complexor &&src) :
				p(src.p), num(src.num), vertical(src.vertical)
		{
			src.p = NULL;
			src.num = 0;
		}

#endif //C++0x

		template <class Type>
		Complexor<Type>::~Complexor()
		{
			clear();
		}

		template <class Type>
		Complexor<Type>::operator Matrix()
		{
			if (this->vertical) {
				Matrix result(num, 1);
				for (int i = 0; i < num; i++) {
					result(i, 0) = p[i];
				}
				return result;
			} else {
				Matrix result(1, num);
				for (int i = 0; i < num; i++) {
					result(0, i) = p[i];
				}
				return result;
			}
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
		void Complexor<Type>::test_index(int num_test) const throw (std::out_of_range)
		{
			if (num_test < 0 || num_test >= num) {
				throw std::out_of_range("the complexor doesn't have the index");
			}
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
			Type *ptr = p + num;
			while (ptr != p) {
				(--ptr)->~Type();
			}
			free (p);
			p = NULL;
			num = 0;
		}

#if __cplusplus < 201103L //C++0x
		template <class Type>
		void Complexor<Type>::do_call(Type (*__pf)(Type))
		{
			for (int i = 0; i < num; ++i) {
				this->p[i] = __pf(this->p[i]);
			}
		}

		template <class Type>
		const Complexor<Type> Complexor<Type>::call_of(Type (*__pf)(Type)) const
		{
			Complexor<Type> result;
			result.resize(this->num);
			for (int i = 0; i < num; ++i) {
				new (result.p + i) Type(__pf(this->p[i]));
			}
			return result;
		}
#else

		template <class Type>
		void Complexor<Type>::do_call(std::function<Type(Type)> __pf)
		{
			for (int i = 0; i < num; ++i) {
				this->p[i] = __pf(this->p[i]);
			}
		}

		template <class Type>
		const Complexor<Type> Complexor<Type>::call_of(std::function<Type(Type)> __pf) const
		{
			Complexor<Type> result;
			result.resize(this->num);
			for (int i = 0; i < num; ++i) {
				new (result.p + i) Type(__pf(this->p[i]));
			}
			return result;
		}
#endif //C++0x

		template <class Type>
		inline void Complexor<Type>::set(int index, const Type &value) throw (std::out_of_range)
		{
			test_index(index);
			p[index] = value;
		}

		template <class Type>
		inline void Complexor<Type>::set_vertical(bool vertical)
		{
			this->vertical = vertical;
		}

		template <class Type>
		inline Type& Complexor<Type>::get(int index) throw (std::out_of_range)
		{
			test_index(index);
			return p[index];
		}

		template <class Type>
		inline const Type& Complexor<Type>::get(int index) const throw (std::out_of_range)
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
		Type& Complexor<Type>::operator[](int index) throw (std::out_of_range)
		{
			test_index(index);
			return p[index];
		}

		template <class Type>
		const Type& Complexor<Type>::operator[](int index) const throw (std::out_of_range)
		{
			test_index(index);
			return p[index];
		}

		template <class Type>
		Type& Complexor<Type>::operator()(int index) throw (std::out_of_range)
		{
			test_index(index);
			return p[index];
		}

		template <class Type>
		const Type& Complexor<Type>::operator()(int index) const throw (std::out_of_range)
		{
			test_index(index);
			return p[index];
		}

//	template <class Type>
//	Type& Complexor<Type>::operator()(int index) throw (std::out_of_range)
//	{
//		test_index(index);
//		return p[index];
//	}
//
//	template <class Type>
//	const Type& Complexor<Type>::operator()(int index) const throw (std::out_of_range)
//	{
//		test_index(index);
//		return p[index];
//	}

		template <class Type>
		void Complexor<Type>::print() const
		{
			std::cout << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::setfill(' '); //清除右对齐, 设置左对齐, 设置不足补空格
			std::cout << "(";

			if (!empty()) {
				std::cout << "  " << std::setw(10) << p[0];
				for (int i = 1; i < num; i++) {
					std::cout << ", " << std::setw(10) << p[i];
				}
			}

			std::cout << " )";
			if (this->vertical) {
				std::cout << " T";
			}
			std::cout << std::endl;
		}

		template <class Type>
		const Complexor<Type> operator+(const Complexor<Type> &a, const Complexor<Type> &b) throw (std::invalid_argument) //向量加法, 方向不同一律返回列向量
		{
			if (a.num != b.num) {
				throw std::invalid_argument("error: length(a) ≠ length(b)");
			}

			const int &num = a.num;

			Complexor<Type> result;
			result.resize(num);

			for (int i = 0; i < num; i++) {
				new (result.p + i) Type(a.p[i] + b.p[i]);
			}
			result.vertical = (a.vertical == b.vertical ? a.vertical : true);
			return result;
		}

		template <class Type>
		const Complexor<Type> operator-(const Complexor<Type> &a, const Complexor<Type> &b) throw (std::invalid_argument) //向量减法, 返回列向量
		{
			if (a.num != b.num) {
				throw std::invalid_argument("error: length(a) ≠ length(b)");
			}

			const int &num = a.num;

			Complexor<Type> result;
			result.resize(num);

			for (int i = 0; i < num; i++) {
				new (result.p + i) Type(a.p[i] - b.p[i]);
			}
			result.vertical = (a.vertical == b.vertical ? a.vertical : true);
			return result;
		}

#if __cplusplus >= 201103L //C++0x
		template <class Type1, class Type2>
		auto operator+(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument) ->const Complexor<decltype(a[0]+b[0])>
//两个不同类型向量的加法, 方向不同一律返回列向量, 自动推导返回类型, 例: Complexor<int> + Complexor<double> = Complexor<double>
		{
			if (a.get_num() != b.get_num()) {
				throw std::invalid_argument("error: length(a) ≠ length(b)");
			}

			const Type1 *ap = a.get_data();
			const Type2 *bp = b.get_data();

			Complexor<decltype(a[0]+b[0])> result([&ap,&bp](int i) {
				return ap[i]+bp[i];
			}, a.get_num(), a.is_vertical() == b.is_vertical() ? a.is_vertical() : true);
			return result;
		}

		template <class Type1, class Type2>
		auto operator-(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument)->const Complexor<decltype(a[0]-b[0])>
//两个不同类型向量的减法, 方向不同一律返回列向量, 自动推导返回类型, 例: Complexor<int> - Complexor<double> = Complexor<double>
		{
			if (a.get_num() != b.get_num()) {
				throw std::invalid_argument("error: length(a) ≠ length(b)");
			}

			const Type1 *ap = a.get_data();
			const Type2 *bp = b.get_data();

			Complexor<decltype(a[0]-b[0])> result([&ap,&bp](int i) {
				return ap[i]-bp[i];
			}, a.get_num(), a.is_vertical() == b.is_vertical() ? a.is_vertical() : true);
			return result;
		}
#endif //C++0x

		template <class Type>
		template <class Type2>
		Complexor<Type>& Complexor<Type>::operator+=(const Complexor<Type2> &with) throw (std::invalid_argument) //向量加法
		{
			if (num != with.get_num()) {
				throw std::invalid_argument("error: length(a) ≠ length(b)");
			}

			const Type2 *withp = with.get_data();
			for (int i = 0; i < num; i++) {
				p[i] += withp[i];
			}

			return *this;
		}

		template <class Type>
		template <class Type2>
		Complexor<Type>& Complexor<Type>::operator-=(const Complexor<Type2> &with) throw (std::invalid_argument) //向量加法
		{
			if (num != with.get_num()) {
				throw std::invalid_argument("error: length(a) ≠ length(b)");
			}

			const Type2 *withp = with.get_data();
			for (int i = 0; i < num; i++) {
				p[i] -= withp[i];
			}

			return *this;
		}

		template <class Type>
		Complexor<Type>& Complexor<Type>::operator*=(double with) throw () //向量乘法
		{
			for (int i = 0; i < num; i++) {
				p[i] *= with;
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
			Complexor<Type> result;
			result.resize(num);
			for (int i = 0; i < num; i++) {
				new (result.p + i) Type(-p[i]);
			}
			result.vertical = this->vertical;
			return result;
		}

		template <class Type>
		Complexor<Type>& Complexor<Type>::operator=(const Complexor<Type> &src) throw (std::bad_alloc)
		{

			if (this->num == src.num) {
				if (this != &src) {
					std::copy(src.p, src.p + this->num, this->p);
				}
			} else if (this->num < src.num) { //需要扩大内存
				const int old_num = this->num;
				this->resize(src.num);

				for_each_placement_new<Type>(src.p + old_num, src.p + src.num, this->p + old_num);

				std::copy(src.p, src.p + old_num, this->p);
			} else { //需要缩小内存
				this->resize(src.num);
				std::copy(src.p, src.p + src.num, this->p);
			}
			this->vertical = src.vertical;
			return *this;
		}

		template <class Type>
		template <class Type2>
		Complexor<Type>& Complexor<Type>::operator=(const Complexor<Type2> &src) throw (std::bad_alloc)
		{ //转换赋值运算符
			if (this->num == src.num) {
				std::copy(src.p, src.p + this->num, this->p);
			} else if (this->num < src.num) { //需要扩大内存
				const int old_num = this->num;
				this->resize(src.num);

				for_each_placement_new<Type>(src.p + old_num, src.p + src.num, this->p + old_num);

				std::copy(src.p, src.p + old_num, this->p);
			} else { //需要缩小内存
				this->resize(src.num);
				std::copy(src.p, src.p + src.num, this->p);
			}
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
			result.vertical = !result.vertical;
			return result;
		}

		template <class Type>
		const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V) throw (std::invalid_argument) //矩阵乘以列向量
		{
			if (V.vertical) {
				if (M.get_column() != V.num) {
					throw std::invalid_argument(
							TRACE("column(M)!=num(V)",
									"const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V)"));
				}
				const int &m = M.get_row();
				const int &n = V.num;
				const double ** const Mp = M.get_data(); //TODO optimized
				Complexor<Type> result(m, 0, true);
				for (int i = 0; i < m; i++) {
					for (int j = 0; j < n; j++) {
						result.p[i] += Mp[i][j] * V.p[j];
					}
				}
				return result;
			} else {
				throw std::invalid_argument(
						TRACE("V must be a vector in vertical",
								"const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V)")); //向量必须为列向量
			}
		}

		template <class Type>
		const Complexor<Type> operator*(const Complexor<Type> &V, const Matrix &M) throw (std::invalid_argument) //行向量乘以矩阵
		{
			if (V.vertical) {
				throw std::invalid_argument("V must be a vector in horizontal");
			} else {
				if (V.num != M.get_row()) {
					throw std::invalid_argument("num(V)!=row(M)");
				}
				const int &m = V.num;
				const int &n = M.get_column();

				Complexor<Type> result(n, 0, false); //TODO Matrix 模板化后这里需要改写下
				const double** const Mp = M.get_data();
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						result.p[i] += V.p[j] * Mp[j][i];
					}
				}
				return result;
			}
		}

		template <class Type>
		const Type dot_product(const Complexor<Type> &a, const Complexor<Type> &b) throw (std::invalid_argument) //向量点积
		{
			if (a.num != b.num) {
				throw std::invalid_argument("num(a)!=num(b)");
			}
			const int &num = a.num;

			if (num > 0) {
				Type result = a.p[0] * b.p[0];
				for (int i = 1; i < num; i++) {
					result += a.p[i] * b.p[i];
				}
				return result;
			} else {
				throw std::invalid_argument("empty complexor");
			}
		}

		template <class Type>
		const Matrix operator*(const Complexor<Type> &a, const Complexor<Type> &b) throw (std::invalid_argument) //向量乘以向量, 返回矩阵
		{
			if (a.vertical == true && b.vertical == false) {
				const int &m = a.num;
				const int &n = b.num;

				Matrix result(m, n);

				const double** result_p = result.get_data();

				for (int i = 0; i < m; i++) {
					for (int j = 0; j < n; j++) {
						result_p[i][j] = a.p[i] * b.p[j];
					}
				}

				return result;
			} else {
				return Matrix(1, 1, dot_product(a, b));
			}
		}

#if __cplusplus >= 201103L //c++0x
		template <class Type1, class Type2>
		auto dot_product(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument) ->const decltype(a[0]*b[0]) //向量点积
		{
			if (a.get_num() != b.get_num()) {
				throw std::invalid_argument("num(a)!=num(b)");
			}

			const int &num = a.get_num();

			if (num > 0) {
				const Type1* const ap = a.get_data();
				const Type2* const bp = b.get_data();
				auto result = ap[0] * bp[0];
				for (int i = 1; i < num; i++) {
					result += ap[i] * bp[i];
				}
				return result;
			} else {
				throw std::invalid_argument("empty complexor");
			}

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
		Type abs(const Complexor<Type> &src) throw (std::invalid_argument) //向量的模
		{
			if (src.num > 0) {
				Type sum = src.p[0] * src.p[0];
				for (int i = 1; i < src.num; i++) {
					sum += src.p[i] * src.p[i];
				}
				return sqrt(sum);
			} else {
				throw std::invalid_argument("empty complexor");
			}
		}

		template <class Type>
		Type angle(const Complexor<Type> &a, const Complexor<Type> &b) throw (std::invalid_argument) //向量夹角
		{
			return acos(dot_product(a, b) / abs(a) / abs(b));
		}

		template <class Type>
		const Complexor<Type> eqution(Matrix m) throw (std::invalid_argument)
		{
			const int &row = m.get_row();
			const int &column = m.get_column() - 1;

			const Type ** mp = m.get_data();

			if (row != column) {
				throw std::invalid_argument("不合法的增广矩阵");
			}
			const int &n = row;

			for (int k = 0; k < n - 1; k++) {

				Type max_ele = 0;
				int i1 = 0;
				int j1 = 0;

				for (int i = k; i < n; i++) {
					for (int j = k; j < n; j++) {
						Type ele = mp[i][j];
						if (fabs(ele) > fabs(max_ele)) {
							max_ele = ele;
							i1 = i;
							j1 = j;
						}
					}
				}

				if (max_ele == 0) {
					throw std::invalid_argument("不合法的增广矩阵");
				}
				m.switch_rows(k, i1);
				m.switch_columns(k, j1);

				for (int j = k + 1; j <= n; j++) {
					//m[k][j] /= m[k][k];
					m.get(k, j) /= mp[k][k];
				}

				for (int i = k + 1; i < n; i++) {
					for (int j = k + 1; j <= n; j++) {
						m[i][j] -= mp[i][k] * mp[k][j];
					}
				}
			}

			Complexor<Type> x(n, false, true);
			x.p[n - 1] = mp[n - 1][n] / mp[n - 1][n - 1];
			for (int i = n - 2; i >= 0; i--) {
				Type sum = 0;
				for (int j = i + 1; j < n; j++) {
					sum += mp[i][j] * x[j];
				}
				x.p[i] = mp[i][n] - sum;
			}

			return x;

		}

	} /* namespace math */

} /* namespace kerbal */

#endif /* MATH_COMPLEXOR_BASE_HPP_ */
