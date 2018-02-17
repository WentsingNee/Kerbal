/*
 * complexor.hpp
 *
 *  Created on: 2017年5月8日
 *      Author: Peter
 */

#ifndef MATH_COMPLEXOR_HPP_
#define MATH_COMPLEXOR_HPP_

#include <iostream>

#include "matrix.hpp"

#if __cplusplus >= 201103L
#	include <functional>
#endif // C++0x

namespace kerbal
{
	namespace math
	{
		namespace matrix
		{
			class Matrix;
		}

		/** @brief 向量计算子库 */
		namespace complexor
		{
			using kerbal::math::matrix::Matrix;

			//类声明
			template <class Type>
			class Complexor;

			//矩阵乘以列向量, 返回向量
			template <class Type>
			const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V)
					throw (std::invalid_argument);

			//行向量乘以矩阵, 返回向量
			template <class Type>
			const Complexor<Type> operator*(const Complexor<Type> &V, const Matrix &M)
					throw (std::invalid_argument);

			//向量点积, 返回实数
			template <class Type>
			const Type dot_product(const Complexor<Type> &a, const Complexor<Type> &b)
					throw (std::invalid_argument);

			//数k乘以向量
			template <class Type>
			const Complexor<Type> operator*(double k, const Complexor<Type> &b);

			//向量乘以数k
			template <class Type>
			const Complexor<Type> operator*(const Complexor<Type> &b, double k);

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
				public:
					typedef Type type;
					typedef Type& reference;
					typedef const Type& const_reference;
					typedef Type* pointer;
					typedef const Type* const_pointer;

				protected:

					friend class Matrix;

					/** @brief 数据区 */
					Type* p;

					/** @brief 向量维数 */
					size_t num;

					/**
					 * @brief 指明此向量是否为列向量
					 * @remarks 当此值为真时, 表明此向量为列向量\n
					 *          当此值为假时, 表明此向量为行向量
					 * @remarks 构造函数的参数中未指明此参数时, 默认均为列向量
					 */
					bool vertical;

					/**
					 * @brief [友元声明] 不同模板参数的向量类互为友元
					 * @tparam 另一类型
					 */
					template <class Type2> friend class Complexor;

					struct Uninit
					{
					};

					static Uninit uninit_tag;

					Complexor(size_t num, Uninit uninit_tag, bool vertical = true);

					size_t mem_init(size_t init_num);

					/**
					 *
					 * @param new_num
					 * @return
					 * @throw std::bad_alloc 当内存分配失败时, 抛出此异常
					 * @warning 当向量维数增加时, 本函数不负责新维度上元素的构造
					 */
					size_t enlarge_buffer(size_t new_num);

				public:

					/**
					 * @brief 构造一个空向量
					 * @throw 本构造函数承诺不抛出任何异常
					 */
					Complexor() throw ();

					/**
					 * @brief 构造一个维数为 num 的列向量
					 * @param num 向量维数
					 * @throws std::bad_alloc 当内存分配失败时, 抛出此异常
					 */
					Complexor(size_t num);

					Complexor(size_t num, const Type &val, bool vertical = true);

					Complexor(const Complexor &src); //拷贝构造函数

					template <class Type2>
					Complexor(const Complexor<Type2> &src); //转类型拷贝构造函数

					/**
					 * @brief 根据矩阵中的某行或某列构造一个向量
					 * @param src
					 * @param index
					 * @param vertical
					 * @throws std::out_of_range
					 * @throws std::bad_alloc
					 */
					Complexor(const Matrix &src, size_t index = 0, bool vertical = true);

					template <size_t LEN>
					explicit Complexor(const Type (&src)[LEN], bool vertical = true);

					template <class InputIterator>
					Complexor(InputIterator begin, InputIterator end, bool vertical = true);

#if __cplusplus < 201103L //under C++0x
					Complexor(Type (*function)(), size_t num, bool vertical = true);
					Complexor(Type (*function)(size_t), size_t num, bool vertical = true);

#else

					//Complexor 为 C++ 11 准备的新特性: 调用 function 进行构造
					Complexor(std::function<Type()> function, size_t num, bool vertical = true);

					//Complexor 为 C++ 11 准备的新特性: 调用 function 进行构造
					Complexor(std::function<Type(size_t)> function, size_t num, bool vertical = true);

					//Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行构造
					Complexor(std::initializer_list<Type> src);

					//Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行转类型构造
					template <class Type2> Complexor(std::initializer_list<Type2> src);

					//Complexor 为 C++ 11 准备的新特性: 转移构造函数
					Complexor(Complexor &&src);
#endif //C++0x

					virtual ~Complexor();
					operator Matrix();
					bool is_const() throw ();
					bool is_const() const throw ();

					virtual void test_index(size_t num_test) const throw (std::out_of_range);
					bool empty() const throw ();
					void clear() throw ();

#if __cplusplus < 201103L //C++0x
					void do_call(Type (*__pf)(Type));
					const Complexor call_of(Type (*__pf)(Type)) const;
#else
					void do_call(std::function<Type(Type)> __pf);
					const Complexor call_of(std::function<Type(const Type&)> && __pf) const;
#endif //C++0x

					void set(size_t index, const Type &value) throw (std::out_of_range);
					void set_vertical(bool vertical) throw ();
					Type& get(size_t index) throw (std::out_of_range);
					const Type& get(size_t index) const throw (std::out_of_range);
					size_t get_num() const;
					bool is_vertical() const;

					const Type* get_data() const throw ();

					Type* const begin() const;
					Type* const end() const;

					size_t get_digit_size() const throw ();

					/**
					 * @brief 赋值运算符
					 * @param src 赋值源
					 * @return 赋值运算符左边变量的引用
					 * @throw std::bad_alloc 当内存分配失败时, 抛出此异常
					 */
					Complexor& operator=(const Complexor &src);

					/**
					 * @brief 转换赋值运算符
					 * @param src 赋值源
					 * @return 赋值运算符左边变量的引用
					 * @throw std::bad_alloc 当内存分配失败时, 抛出此异常
					 */
					template <class Type2>
					Complexor& operator=(const Complexor<Type2> &src);

#if __cplusplus >= 201103L //C++0x
					/**
					 * @brief 转移赋值运算符
					 * @param src
					 * @return
					 */
					const Complexor& operator=(Complexor && src) noexcept;
#endif //C++0x

					Type& operator[](size_t index) throw (std::out_of_range);
					const Type& operator[](size_t index) const throw (std::out_of_range);
					Type& operator()(size_t index) throw (std::out_of_range);
					const Type& operator()(size_t index) const throw (std::out_of_range);

					/**
					 * @brief 调整向量的维数
					 * @param new_num 调整至的维数
					 * @throws std::bad_alloc 当内存分配失败时, 抛出此异常
					 * @warning 当向量维数减小时, 本函数会自动析构被裁剪维度上的元素.\n
					 *          当向量维数增加时, 本函数负责新维度上元素的构造
					 */
					void resize(size_t new_num);

					/**
					 * @brief 将向量的维数裁剪至参数 new_size 指定的大小
					 * @param new_size
					 * @return 返回裁剪后, 向量的维数
					 * @warning 如果 new_size 比原来的大小要大, 则什么也不做, 并返回原来的大小
					 */
					size_t shrink(size_t new_num);

					/**
					 * @brief 当向量为空向量时, 引发一个 std::invalid_argument 异常
					 * @throw std::invalid_argument
					 */
					void test_empty() const;

					virtual void print() const;

					/**
					 * @brief 向量加法
					 * @param with
					 * @return 结果向量. 两个向量方向不同一律返回列向量
					 * @throw std::invalid_argument
					 */
					const Complexor operator+(const Complexor & with) const;

					/**
					 * @brief 向量减法
					 * @param with
					 * @return 结果向量. 两个向量方向不同一律返回列向量
					 * @throw std::invalid_argument
					 */
					const Complexor operator-(const Complexor & with) const;

					/**
					 *
					 * @param with
					 * @return
					 * @throw std::invalid_argument
					 */
					template <class Type2>
					Complexor& operator+=(const Complexor<Type2> &with);

					/**
					 *
					 * @param with
					 * @return
					 * @throw std::invalid_argument
					 */
					template <class Type2>
					Complexor& operator-=(const Complexor<Type2> &with);

					/**
					 * @brief 向量乘法
					 * @param with
					 * @return
					 */
					Complexor& operator*=(double with);

					/**
					 * @brief 返回向量的同向同长向量
					 * @return
					 */
					const Complexor operator+() const;

					/**
					 * @brief 返回向量的反向同长向量
					 * @return
					 */
					const Complexor operator-() const;

					Complexor& do_transpose() throw ();
					const Complexor transpose_of() const;

					//矩阵乘以列向量, 返回向量
					friend const Complexor operator*<>(const Matrix &M, const Complexor &V)
							throw (std::invalid_argument);

					//行向量乘以矩阵, 返回向量
					friend const Complexor operator*<>(const Complexor &V, const Matrix &M)
							throw (std::invalid_argument);

					//向量点积, 返回实数
					friend const Type dot_product<>(const Complexor &a, const Complexor &b)
							throw (std::invalid_argument);

					friend const Complexor operator*<>(double k, const Complexor &b); //数k乘以向量

					friend const Complexor operator*<>(const Complexor &b, double k); //向量乘以数k

					friend Type abs<>(const Complexor &src) throw (std::invalid_argument); //向量的模

					//throw (std::invalid_argument)
					const Matrix operator*(const Complexor & with) const;

					/**
					 * @brief 计算两个向量间的夹角
					 * @param with
					 * @return
					 * @throw std::invalid_argument 当两个向量维度不同时, 抛出此异常
					 */
					Type operator^(const Complexor & with) const;

					static const Complexor softmax(const Complexor & src);

			};

			const Complexor<double> eqution(Matrix m) throw (std::invalid_argument);

#if __cplusplus >= 201103L //C++0x

			/**
			 * @brief 两个不同类型向量的加法
			 * @param a
			 * @param b
			 * @return 方向不同一律返回列向量, 自动推导返回类型
			 * 例: Complexor<int> + Complexor<double> = const Complexor<double>
			 * @throw std::invalid_argument
			 */
			template <class Type1, class Type2>
			auto operator+(const Complexor<Type1> &a, const Complexor<Type2> &b)->const Complexor<decltype(a[0]+b[0])>;

			/**
			 * @brief 两个不同类型向量的减法
			 * @param a
			 * @param b
			 * @return 方向不同一律返回列向量, 自动推导返回类型
			 * 例: Complexor<int> - Complexor<double> = const Complexor<double>
			 * @throw std::invalid_argument
			 */
			template <class Type1, class Type2>
			auto operator-(const Complexor<Type1> &a, const Complexor<Type2> &b)->const Complexor<decltype(a[0]-b[0])>;

			/**
			 * @brief 两个不同类型向量的点积
			 * @param a
			 * @param b
			 * @return
			 * 例: dor_product(Complexor<int>, Complexor<double>) = const double
			 * @throw std::invalid_argument
			 */
			template <class Type1, class Type2>
			auto dot_product(const Complexor<Type1> &a, const Complexor<Type2> &b)->const decltype(a[0]*b[0]);

#endif //c++0x

		} /* namespace complexor */

	} /* namespace math */

} /* namespace kerbal */

#include "complexor_base.hpp" /* 实现 */

#endif /* MATH_COMPLEXOR_HPP_ */
