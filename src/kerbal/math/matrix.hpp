/**
 * @file matrix.hpp
 * @brief 本文件提供了对基本矩阵计算的支持
 * @author 倪文卿
 * @date 2017-3-22
 * @copyright 倪文卿
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 <img src="ThinkSpirit团队logo.jpg" alt="ThinkSpirit logo" height=40 align ="left" />
 */

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "../array_2d.hpp"

#include <fstream>
#include <iostream>
#include <cmath>

/** @brief kerbal 库 */
namespace kerbal
{
	/** @brief 数学计算子库 */
	namespace math
	{
		/** @brief 矩阵计算子库  @author 倪文卿 */
		namespace matrix
		{
			class Matrix;
		}

		namespace complexor
		{
			template <typename _Tp>
			class Complexor;
		}
	}
}

namespace std
{
	/**
	 * @brief 交换两个矩阵
	 * @param a 矩阵 a
	 * @param b 矩阵 b
	 * @remark 重载了标准命名空间中的 swap 函数, 使得两个矩阵的交换操作能在 O(1) 的时间复杂度中完成
	 */
	void swap(kerbal::math::matrix::Matrix & a, kerbal::math::matrix::Matrix & b);
}

namespace kerbal
{
	namespace math
	{
		namespace matrix
		{
			using kerbal::data_struct::array_2d::Array_2d;
			using kerbal::math::complexor::Complexor;

			/**
			 * @brief 矩阵类
			 * @author 倪文卿
			 */
			class Matrix: public Array_2d<double>
			{
				protected:
					Matrix(size_t row, size_t column, Uninit);

				public:
					template <typename _Up>
					friend class Complexor;

					/**
					 * @brief 构造一个 0 行 0 列的空矩阵
					 * @throw 本构造函数承诺不抛出任何异常
					 */
					Matrix() throw ();

					/**
					 * @brief 构造一个 row 行 * column 列 的零矩阵
					 * @param row 行数
					 * @param column 列数
					 */
					Matrix(size_t row, size_t column);

					/**
					 * @brief 构造一个 row 行 * column 列 的矩阵, 矩阵中每个元素的初始值由参数 val 指定
					 * @param row 行数
					 * @param column 列数
					 * @param val 初始值
					 */
					Matrix(size_t row, size_t column, const double &val);

#if __cplusplus < 201103L
					Matrix(double (*function)(), size_t row, size_t column, bool para = false);
					Matrix(double (*function)(size_t, size_t), size_t row, size_t column, bool para =
							false);
#else
					Matrix(std::function<double()> fun, size_t row, size_t column, bool para = false);
					Matrix(std::function<double(size_t, size_t)> fun, size_t row, size_t column, bool para =
							false);
#endif

					/**
					 * @brief 利用一个长度为 LEN 的一维数组进行构造
					 * @param src 源数组
					 * @param in_row 为真时构造行向量, 为假时构造列向量
					 */
					template <size_t LEN>
					explicit Matrix(const double (&src)[LEN], bool in_row = true);

					/**
					 * @brief 利用一个 ROW 行 * COLUMN 列 的二维数组进行构造
					 * @param src 源数组
					 */
					template <size_t ROW, size_t COLUMN>
					explicit Matrix(const double (&src)[ROW][COLUMN]);

#if __cplusplus >= 201103L //C++0x
					/**
					 * @brief <b>[C++11]</b> 利用二维初始化列表进行构造
					 * @param src a 2d initializer list
					 * @warning only supported by C++ 11 or higher
					 */
					Matrix(std::initializer_list<std::initializer_list<double>> src);

					/**
					 * @brief <b>[C++11]</b> 利用一维初始化列表进行构造
					 * @param src a liner initializer list
					 * @warning only supported by C++ 11 or higher
					 */
					Matrix(std::initializer_list<double> src);

					/**
					 * @brief <b>[C++11]</b> 转移构造函数
					 * @param src 源矩阵
					 * @warning only supported by C++ 11 or higher
					 */
					Matrix(Matrix &&src);
#endif //C++0x

					/**
					 * @brief 拷贝构造函数
					 * @param src 源矩阵
					 */
					Matrix(const Matrix &src);

					/** @brief 析构函数 */
					virtual ~Matrix();

					/** @brief 矩阵的输出样式 */
					enum Frame_style
					{
						/** @brief 输出直角 */
						rt_corner,

						/** @brief 输出圆角 */
						rd_corner,

						/** @brief 输出行列式 */
						single_det,

						/** @brief 输出双竖线 */
						double_det,

						/** @brief 无边框 */
						none
					};

					void print(Frame_style frame = rt_corner, bool print_corner = true, std::ostream &output =
							std::cout) const;

					void save(std::ofstream & fout) const
							throw (std::runtime_error, __cxxabiv1:: __forced_unwind );
					void save(const char * file_name) const throw (std::runtime_error, __cxxabiv1:: __forced_unwind );

					friend const Matrix load_from(std::ifstream & fin) throw (std::runtime_error);
					friend const Matrix load_from(const char * file_name) throw (std::runtime_error);

					/**
					 * @brief 交换矩阵的两行
					 * @param row1 行号1
					 * @param row2 行号2
					 * @throw std::out_of_range 若参数 row1 或 row2 越界, 则抛出此异常
					 * @par 时间复杂度\n
					 * 此操作具有 O(1) 阶复杂度
					 */
					void switch_rows(size_t row1, size_t row2);

					void switch_rows(size_t row1,size_t row2,size_t column_index_start);

					void switch_rows(size_t row1,size_t row2,size_t column_index_start,size_t column_index_end);

					/**
					 * @brief 交换矩阵的两列
					 * @param column1 列号1
					 * @param column2 列号2
					 * @throw std::out_of_range 若参数 column1 或 column2 越界, 则抛出此异常
					 * @par 时间复杂度\n
					 * 此操作具有 O(row) 阶复杂度. 其中, row 表示被操作矩阵的行数
					 */
					void switch_columns(size_t column1, size_t column2);

					/**
					 * @brief 令矩阵中指定行上的每一个元素均乘上系数 k
					 * @param k 系数
					 * @param row_dest 被乘行行号
					 * @throw std::out_of_range 若参数 row_dest 越界, 则抛出此异常
					 */
					void kmr(double k, size_t row_dest);

					/**
					 * @brief 将矩阵 row_from 行的 k 倍加到 row_dest 行上
					 * @param k 系数
					 * @param row_from 被乘行行号
					 * @param row_dest 被加行行号
					 * @throw std::out_of_range 若参数 row_from 或 row_dest 越界, 则抛出此异常
					 */
					void kmr_plus_to_another(double k, size_t row_from, size_t row_dest);

					/**
					 * @brief 令矩阵中指定列上的每一个元素均乘上系数 k
					 * @param k 系数
					 * @param column_dest 被乘列列号
					 * @throw std::out_of_range 若参数 column_dest 越界, 则抛出此异常
					 */
					void kmc(double k, size_t column_dest);

					/**
					 * @brief 将矩阵 column_from 列的 k 倍加到 column_dest 列上
					 * @param k 系数
					 * @param column_from 被乘列列号
					 * @param column_dest 被加列列号
					 * @throw std::out_of_range 若参数 column_from 或 column_dest 越界, 则抛出此异常
					 */
					void kmc_plus_to_another(double k, size_t column_from, size_t column_dest);

					/**
					 * @brief 将矩阵的上三角区域内的元素保留原值不变, 其余区域清零
					 */
					void do_triu();

					/**
					 * @brief 提取矩阵的上三角矩阵
					 * @return
					 */
					const Matrix triu_of() const;

					/**
					 * @brief 计算一个矩阵对应的行列式的值
					 * @return 计算结果
					 * @throw std::invalid_argument 当矩阵不为方阵时, 抛出此异常
					 * @par 空间复杂度\n
					 * 此操作具有 O(row * column) 阶空间复杂度
					 */
					double det()const;

					/**
					 * @brief 构造本方阵的伴随矩阵
					 * @return 结果矩阵
					 * @throw std::invalid_argument 当矩阵不为方阵时, 抛出此异常
					 */
					Matrix Adjugate_matrix() const;

					/**
					 * @brief 构造本方阵的逆矩阵
					 * @return 结果矩阵
					 * @throw std::invalid_argument 当逆矩阵不存在时, 抛出此异常
					 */
					Matrix Inverse_matrix() const;

					/**
					 * @brief 计算本矩阵与其本身的转置矩阵的乘积
					 * @return 结果矩阵
					 */
					const Matrix mul_with_trans() const;

					//运算符重载

					/**
					 * @brief 计算两个矩阵的加法
					 * @param A 矩阵 A
					 * @param B 矩阵 B
					 * @return A + B 的结果
					 * @throw std::invalid_argument 如果两个矩阵的大小不一致, 即行数与列数中只要有一个不相等, 则抛出此异常
					 */
					friend const Matrix operator+(const Matrix &A, const Matrix &B);

					/**
					 * @brief 计算两个矩阵的减法
					 * @param A 矩阵 A
					 * @param B 矩阵 B
					 * @return A - B 的结果
					 * @throw std::invalid_argument 如果两个矩阵的大小不一致, 即行数与列数中只要有一个不相等, 则抛出此异常
					 */
					friend const Matrix operator-(const Matrix &A, const Matrix &B);
					friend const Matrix operator*(const double k, const Matrix &A); //数k乘矩阵
					friend const Matrix operator*(const Matrix &A, const double k);//矩阵乘数k
					friend const Matrix operator*(const Matrix &A, const Matrix &B) throw (std::invalid_argument);//矩阵乘矩阵

					/**
					 * @brief 计算 (A * B) + C 的结果
					 * @param A 矩阵 A
					 * @param B 矩阵 B
					 * @param C 矩阵 C
					 * @return (A * B) + C 的结果
					 * @throw std::invalid_argument 若参数矩阵的大小不可满足运算要求, 则抛出此异常
					 * @remark 完全等效于表达式 (A * B) + C , 但是速度有少许提高
					 */
					friend const Matrix fma(const Matrix &A, const Matrix &B, const Matrix &C);

					/**
					 * @brief 计算两个矩阵的点乘
					 * @param A 矩阵 A
					 * @param B 矩阵 B
					 * @return A .* B 的结果
					 * @throw std::invalid_argument 若两个矩阵的大小不一致, 则抛出此异常
					 * @remark 完全等价于 Matlab 中 A .* B 的运算
					 */
					friend const Matrix dot_product(const Matrix &A, const Matrix &B);

					/**
					 * @brief 计算矩阵的 n 次幂
					 * @par 计算规则\n
					 * - 若 n 为负数, 则计算基数矩阵的逆矩阵的 -n 次幂\n
					 * - 若 n 为 0, 则返回同样大小的单位矩阵\n
					 * - 若 n 为 1, 则返回原矩阵的拷贝
					 * @param n 次数
					 * @return A 的 n 次幂
					 * @throw std::invalid_argument 当 n 不等于 1 时, 要求基数矩阵必须为方阵, 否则抛出此异常
					 * @remark 表达式 A ^ n 完全等效于函数表达式 pow(A, n)
					 * @see friend inline const Matrix pow(const Matrix &A, int n)
					 */
					const Matrix operator^(int n) const;

					/**
					 * @brief 计算一个矩阵的 n 次幂
					 * @par 计算规则\n
					 * - 若 n 为负数, 则计算基数矩阵的逆矩阵的 -n 次幂\n
					 * - 若 n 为 0, 则返回同样大小的单位矩阵\n
					 * - 若 n 为 1, 则返回原矩阵的拷贝
					 * @param A 基数矩阵
					 * @param n 次数
					 * @return A 的 n 次幂
					 * @throw std::invalid_argument 当 n 不等于 1 时, 要求基数矩阵必须为方阵, 否则抛出此异常
					 * @remark 函数表达式 pow(A, n) 完全等效于表达式 A ^ n
					 * @see const Matrix operator^(int n) const
					 */
					friend inline const Matrix pow(const Matrix &A, int n)
					{
						return A ^ n;
					}

					const Matrix operator+() const;
					const Matrix operator-() const;

					/**
					 * @brief 令赋值运算符前的矩阵加上赋值运算符后的矩阵
					 * @param with 加上的矩阵
					 * @return 赋值运算符前被加矩阵的引用
					 * @throw std::invalid_argument 当两个矩阵大小不一致时, 抛出此异常
					 * @remark 此方法等效于 m = m + with 或 m = with + m , 不过具有更佳的效率
					 */
					Matrix& operator+=(const Matrix &with);

					/**
					 * @brief 令赋值运算符前的矩阵减去赋值运算符后的矩阵
					 * @param with 减去的矩阵
					 * @return 赋值运算符前被减矩阵的引用
					 * @throw std::invalid_argument 当两个矩阵大小不一致时, 抛出此异常
					 * @remark 此方法等效于 m = m - with , 不过具有更佳的效率
					 */
					Matrix& operator-=(const Matrix &with);

					/**
					 * @brief 令一个矩阵的每一个元素均乘以系数 k
					 * @param k 系数 k
					 * @return 赋值运算符前被乘矩阵的引用
					 * @throw 此方法保证不抛出任何异常
					 * @remark 此方法等效于 m = m * k 或 m = k * m , 不过具有更佳的效率
					 */
					Matrix& operator*=(double k) throw ();

					Matrix& operator=(const Matrix &src);

#if __cplusplus >= 201103L //C++0x
					/**
					 * @brief <b>[C++11]</b> 将移动赋值运算符后的矩阵的内容赋值给移动赋值运算符前的矩阵
					 * @param src 拷贝母本
					 * @return 被赋值矩阵的引用
					 * @warning only supported by C++ 11 or higher
					 * @remark 移动拷贝运算符比拷贝运算符具有更好的运行效率
					 * @remark 欲详细了解此方法, 您需要了解 C++ 11 中的 <b>移动语义</b>
					 */
					Matrix& operator=(Matrix &&src);
#endif //C++0x

					template <size_t N>
					friend const Matrix cat(const Matrix * const(&a)[N]) throw (std::invalid_argument);

					/**
					 * @brief 返回一个 n 阶单位矩阵
					 * @param n 阶数
					 * @return n 阶单位矩阵
					 */
					static const Matrix eye(size_t n); //构造一个单位矩阵

					static const Matrix vander(const Complexor<double> & src);

#if __cplusplus >= 201103L
					/**
					 * @brief <b>[C++11]</b> 构造一个 n 阶对角矩阵, 主对角线上的值依次为 arg0, arg1, arg2 ...
					 * @param arg0 主对角线上第一个元素的值
					 * @param args 主对角线上其他元素构成的参数包
					 * @return 对角矩阵
					 * @warning only supported by C++ 11 or higher
					 */
					template <class ...T>
					static const Matrix diag(double arg0, T ... args);
#endif //c++0x

					/**
					 * @brief 计算本方阵的迹
					 * @param src 源矩阵
					 * @return 计算结果
					 * @brief std::invalid_argument 当源矩阵不为方阵时, 抛出此异常
					 */
					double tr() const;

					const Matrix transpose_of() const; //构造矩阵A的转置矩阵

					void do_transpose()
					{
						const Matrix& result(transpose_of());
						std::swap(const_cast<double** &>(result.p), this->p);
						std::swap(const_cast<size_t &>(result.row), this->row);
						std::swap(const_cast<size_t &>(result.column), this->column);
					}

					const Matrix cofactor_of(size_t row_tar, size_t column_tar)const throw (std::out_of_range); //构造矩阵A的余子式A(x,y)

					void do_cofactor(size_t row_tar, size_t column_tar) throw (std::out_of_range)
					{ //返回一个矩阵划去row_tar 行和 column_tar 列后的矩阵
						const Matrix& result(cofactor_of(row_tar, column_tar));
						std::swap(const_cast<double** &>(result.p), this->p);
						std::swap(const_cast<size_t &>(result.row), this->row);
						std::swap(const_cast<size_t &>(result.column), this->column);
					}

					friend bool Matcmp(const Matrix &A, const Matrix &B, double eps);

					virtual void test_row(size_t row_test) const throw (std::out_of_range);
					virtual void test_column(size_t column_test) const throw (std::out_of_range);
					void test_square() const throw (std::invalid_argument);

					enum Conv_size
					{
						max, same, valid
					};

					template<Conv_size>
					friend const Matrix conv_2d(const Matrix &core, const Matrix &A); //矩阵卷积

					friend void std::swap(Matrix &a, Matrix &b);

					/**
					 *
					 * @param up
					 * @param down
					 * @param left
					 * @param right
					 * @return
					 * @throws std::invalid_argument
					 * @throws std::out_of_range
					 */
					const Matrix sub_of(size_t up, size_t down, size_t left, size_t right) const;

					const Matrix max_pooling_of(size_t core_height, size_t core_width, size_t step_h, size_t step_w)const;
				};

			template <size_t LEN>
			Matrix::Matrix(const double (&src)[LEN], bool in_row) :
					Array_2d<double>(src, in_row)
			{ //利用一维数组进行构造
			}

			template <size_t ROW, size_t COLUMN>
			Matrix::Matrix(const double (&src)[ROW][COLUMN]) :
					Array_2d<double>(src)
			{ //利用二维数组进行构造
			}

//			template <size_t N>
//			const Matrix cat(const Matrix (&a)[N]) throw (std::invalid_argument)
//			{
//				size_t row_total = a[0].row;
//				size_t column_total = a[0].column;
//
//				for (size_t i = 1; i < N; ++i) {
//					if (a[i].row != row_total) {
//						throw std::invalid_argument("串联的矩阵的行数不一致");
//					}
//					column_total += a[i].column;
//				}
//
//				Matrix result(row_total, column_total);
//				size_t column_covered = 0;
//				for (const Matrix *it = a; it != a + N; ++it) { //数组循环
//					for (size_t j = 0; j < row_total; ++j) { //行循环
//						std::copy(it->p[j], it->p[j] + it->column, result.p[j] + column_covered);
//					}
//					column_covered += it->column;
//				}
//				return result;
//			}

			template <size_t N>
			const Matrix cat(const Matrix * const (&a)[N]) throw (std::invalid_argument)
			{
				size_t row_total = a[0]->row;
				size_t column_total = 0;

				typedef const Matrix* const item_type;
				const item_type * const end = a + N;

				for (const item_type * it = a; it != end; ++it) {
					if ((*it)->row != row_total) {
						throw std::invalid_argument("串联的矩阵的行数不一致");
					}
					column_total += (*it)->column;
				}

				Matrix result(row_total, column_total, Matrix::uninit_tag);
				size_t column_covered = 0;
				for (const item_type * it = a; it != end; ++it) { //数组循环
					for (size_t i = 0; i < row_total; ++i) { //行循环
						std::uninitialized_copy((*it)->p[i], (*it)->p[i] + (*it)->column,
								result.p[i] + column_covered);
					}
					column_covered += (*it)->column;
				}
				return result;
			}

			template <Matrix::Conv_size>
			const Matrix conv_2d(const Matrix &core, const Matrix &A); //矩阵卷积

			template <>
			const Matrix conv_2d<Matrix::max>(const Matrix &core, const Matrix &A);

			template <>
			const Matrix conv_2d<Matrix::same>(const Matrix &core, const Matrix &A);

			template <>
			const Matrix conv_2d<Matrix::valid>(const Matrix &core, const Matrix &A);

			//应用部分
#if __cplusplus >= 201103L
			template <class ...T>
			const Matrix Matrix::diag(double arg0, T ... args)
			{
				Matrix result(1 + sizeof...(args), 1 + sizeof...(args), 0);
				size_t i = 0;
				for (const double & ele : { arg0, args... }) {
					result.p[i][i] = ele;
					++i;
				}
				return result;
			}
#endif //c++0x

			const Matrix rotate_X(double sigma);
			const Matrix rotate_Y(double sigma);
			const Matrix rotate_Z(double sigma);

			void rotate_X(double sigma, const double& x0, double& y0, double& z0) throw ();
			void rotate_Y(double sigma, double& x0, const double& y0, double& z0) throw ();
			void rotate_Z(double sigma, double& x0, double& y0, const double& z0) throw ();

		}/* namespace matrix */

	}/* namespace math */

} /* namespace kerbal */

#endif	/* End _MATRIX_HPP_ */
