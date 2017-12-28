/*
 * complexor.h
 *
 *  Created on: 2017年5月8日
 *      Author: Peter
 */

#ifndef COMPLEXOR_HPP_
#define COMPLEXOR_HPP_

#include <iostream>
#include <iomanip>
#include <cstring>
#include "matrix.hpp"
#include "../except_C++0x.hpp"

#if __cplusplus >= 201103L
#	include <functional>
#endif // C++0x

namespace kerbal
{
	namespace math
	{
		/** @brief 向量计算子库 */
		namespace complexor
		{
			using kerbal::math::matrix::Matrix;

			//友元函数声明
			template <class Type> class Complexor;

			template <class Type> const Complexor<Type> TransposeOf(const Complexor<Type> &src);

			//矩阵乘以列向量, 返回向量
			template <class Type> const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V) throw (std::invalid_argument);

			//行向量乘以矩阵, 返回向量
			template <class Type> const Complexor<Type> operator*(const Complexor<Type> &V, const Matrix &M) throw (std::invalid_argument);

			//向量点积, 返回实数
			template <class Type> const Type dot_product(const Complexor<Type> &a, const Complexor<Type> &b) throw (std::invalid_argument);

			//数k乘以向量
			template <class Type> const Complexor<Type> operator*(double k, const Complexor<Type> &b);

			//向量乘以数k
			template <class Type> const Complexor<Type> operator*(const Complexor<Type> &b, double k);

			//向量的模
			template <class Type> Type abs(const Complexor<Type> &src) throw (std::invalid_argument);

			/**
			 * @brief 向量类
			 * @author 倪文卿
			 * @tparam 元素类型
			 */
			template <class Type>
			class Complexor
			{
				protected:

					/** @brief 数据区 */
					Type *p;

					/** @brief 向量维数 */
					int num;

					/**
					 * @brief 指明此向量是否为列向量
					 * @remarks 当此值为真时, 此向量为列向量\n
					 *          当此值为假时, 此向量为行向量
					 * @remarks 构造函数的参数中未指明此参数时, 默认均为列向量
					 */
					bool vertical;

					/**
					 * @brief 向量类默认, 不同模板参数的向量类互为友元
					 * @tparam 另一类型
					 */
					template <class Type2> friend class Complexor;

					int mem_init(int init_num) throw (std::bad_alloc);

					/**
					 * @brief 调整向量的维数
					 * @param new_num 调整至的维数
					 * @throws std::bad_alloc 当内存分配失败时, 抛出此异常
					 * @warning 当向量维数减小时, 本函数会自动析构被裁剪维度上的元素.\n
					 *          但当向量维数增加时, 本函数不负责新维度上元素的构造
					 */
					void resize(int new_num) throw (std::bad_alloc);

				public:

					/**
					 * @brief 构造一个零向量, 维数由参数 num 指定
					 * @param num 向量维数
					 * @throws std::bad_alloc 当内存分配失败时, 抛出此异常
					 */
					Complexor(const int num = 0) throw (std::bad_alloc);
					Complexor(const int num, const Type &val, const bool vertical = true) throw (std::bad_alloc);
					Complexor(const Complexor &src) throw (std::bad_alloc); //拷贝构造函数
					template <class Type2> Complexor(const Complexor<Type2> &src) throw (std::bad_alloc); //转类型拷贝构造函数
					Complexor(const Matrix &src, int index = 0, const bool vertical = true) throw (std::out_of_range, std::bad_alloc);
					Complexor(const Type src[], const int num, const bool vertical = true) throw (std::bad_alloc);

#if __cplusplus < 201103L //under C++0x
					Complexor(Type (*function)(), const int num, const bool vertical = true) throw (std::bad_alloc);
					Complexor(Type (*function)(int), const int num, const bool vertical = true) throw (std::bad_alloc);
#endif //under C++0x
					//TODO 仿函数

#if __cplusplus >= 201103L //C++0x

					//Complexor 为 C++ 11 准备的新特性: 调用 function 进行构造
					Complexor(std::function<Type()> function, const int num, const bool vertical = true) throw (std::bad_alloc);

					//Complexor 为 C++ 11 准备的新特性: 调用 function 进行构造
					Complexor(std::function<Type(int)> function, const int num, const bool vertical = true) throw (std::bad_alloc);

					//Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行构造
					Complexor(std::initializer_list<Type> src) throw (std::bad_alloc);

					//Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行转类型构造
					template <class Type2> Complexor(std::initializer_list<Type2> src) throw (std::bad_alloc);

					//Complexor 为 C++ 11 准备的新特性: 转移构造函数
					Complexor(Complexor &&src);
#endif //C++0x

					virtual ~Complexor();
					operator Matrix();
					inline bool is_const();
					inline bool is_const() const;

					virtual void test_index(int num_test) const throw (std::out_of_range);
					inline bool empty() const;
					inline void clear();

#if __cplusplus < 201103L //C++0x
					void do_call(Type (*__pf)(Type));
					const Complexor call_of(Type (*__pf)(Type)) const;
#else
					void do_call(std::function<Type(Type)> __pf);
					const Complexor call_of(std::function<Type(Type)> __pf) const;
#endif //C++0x

					inline void set(int index, const Type &value) throw (std::out_of_range);
					inline void set_vertical(bool vertical);
					inline Type& get(int index) throw (std::out_of_range);
					inline const Type& get(int index) const throw (std::out_of_range);
					inline int get_num() const;
					inline bool is_vertical() const;

					inline const Type* get_data() const;

					inline Type* const begin() const;
					inline Type* const end() const;

					inline size_t get_digit_size() const;

					Complexor& operator=(const Complexor &src) throw (std::bad_alloc); //赋值运算符

					template <class Type2> Complexor& operator=(const Complexor<Type2> &src) throw (std::bad_alloc); //转换赋值运算符

#if __cplusplus >= 201103L //C++0x
					const Complexor& operator=(Complexor &&src); //转移赋值运算符
#endif //C++0x

					Type& operator[](int index) throw (std::out_of_range);
					const Type& operator[](int index) const throw (std::out_of_range);
					Type& operator()(int index) throw (std::out_of_range);
					const Type& operator()(int index) const throw (std::out_of_range);

					virtual void print() const;

					//向量加法, 方向不同一律返回列向量
					const Complexor operator+(const Complexor & with) const throw (std::invalid_argument);

					//向量减法, 方向不同一律返回列向量
					const Complexor operator-(const Complexor & with) const throw (std::invalid_argument);

					template <class Type2>
					Complexor& operator+=(const Complexor<Type2> &with) throw (std::invalid_argument);  //向量加法

					template <class Type2>
					Complexor& operator-=(const Complexor<Type2> &with) throw (std::invalid_argument);  //向量减法

					Complexor& operator*=(double with) throw ();  //向量乘法

					const Complexor operator+() const; //返回向量的同向同长向量
					const Complexor operator-() const; //返回向量的反向同长向量

					Complexor& doTranspose();
					friend const Complexor TransposeOf<>(const Complexor &src);

					//矩阵乘以列向量, 返回向量
					friend const Complexor operator*<>(const Matrix &M, const Complexor &V) throw (std::invalid_argument);

					//行向量乘以矩阵, 返回向量
					friend const Complexor operator*<>(const Complexor &V, const Matrix &M) throw (std::invalid_argument);

					//向量点积, 返回实数
					friend const Type dot_product<>(const Complexor &a, const Complexor &b) throw (std::invalid_argument);

					friend const Complexor operator*<>(double k, const Complexor &b); //数k乘以向量

					friend const Complexor operator*<>(const Complexor &b, double k); //向量乘以数k

					friend Type abs<>(const Complexor &src) throw (std::invalid_argument); //向量的模

					//throw (std::invalid_argument)
					const Matrix operator*(const Complexor & with) const;

					//throw invalid_argument
					Type operator^(const Complexor & with) const;

					//friend const Complexor<Type> eqution(Matrix m) throw (std::invalid_argument);
			};

#if __cplusplus >= 201103L //C++0x

			//两个不同类型向量的加法, 方向不同一律返回列向量, 自动推导返回类型
			//例: Complexor<int> + Complexor<double> = Complexor<double>
			template <class Type1, class Type2>
			auto operator+(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument)
			->const Complexor<decltype(a[0]+b[0])>;

			//两个不同类型向量的减法, 方向不同一律返回列向量, 自动推导返回类型
			//例: Complexor<int> - Complexor<double> = Complexor<double>
			template <class Type1, class Type2>
			auto operator-(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument)
			->const Complexor<decltype(a[0]-b[0])>;

			//向量点积
			//例: dor_product(Complexor<int>, Complexor<double>) = double
			template <class Type1, class Type2>
			auto dot_product(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (std::invalid_argument)
			->const decltype(a[0]*b[0]);

#endif //c++0x

		} /* namespace complexor */

	} /* namespace math */

} /* namespace kerbal */

#endif /* COMPLEXOR_HPP_ */

#include "complexor_base.hpp" /* 实现 */
