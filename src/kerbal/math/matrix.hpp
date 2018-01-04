/**
 * @file matrix.hpp
 * @brief 本文件提供了对基本矩阵计算的支持
 * @author 倪文卿
 * @date 2017-4-30
 * @copyright 倪文卿
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 <img src="ThinkSpirit团队logo.jpg" alt="ThinkSpirit logo" height=40 align ="left" />
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <fstream>
#include <iostream>
#include <cmath>

#include "../array_2d.hpp"

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

			/**
			 * @brief 矩阵类
			 * @author 倪文卿
			 */
			class Matrix: public Array_2d<double>
			{
				public:
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
					Matrix(const int row, const int column);

					/**
					 * @brief 构造一个 row 行 * column 列 的矩阵, 矩阵中每个元素的初始值由参数 val 指定
					 * @param row 行数
					 * @param column 列数
					 * @param val 初始值
					 */
					Matrix(const int row, const int column, const double &val);
					Matrix(double (*function)(), const int row, const int column, bool para);
					Matrix(double (*function)(int, int), const int row, const int column, bool para);

					template <size_t M, size_t N>
					Matrix(const double (&src)[M][N], const int row, const int column); //利用二维数组进行构造

					Matrix(const double arr[], int len, bool in_a_row = true); //利用一维数组进行构造

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

					Matrix(Matrix &&src); //转移构造函数
#endif //C++0x

					Matrix(const Matrix &src); //拷贝构造函数

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

					virtual void print(Frame_style frame = rt_corner, bool print_corner = true, std::ostream &output =
							std::cout) const;

					void save(std::ofstream & fout) const throw (std::runtime_error, __cxxabiv1:: __forced_unwind );
					void save(const char * file_name) const throw (std::runtime_error, __cxxabiv1:: __forced_unwind );

					friend const Matrix load_from(std::ifstream & fin) throw (std::runtime_error);
					friend const Matrix load_from(const char * file_name) throw (std::runtime_error);

					/**
					 * @brief 交换矩阵的两行
					 * @param row1 行号1
					 * @param row2 行号2
					 * @throw std::out_of_range 若 参数 row1 或 row2 越界, 则抛出此异常
					 * @par 时间复杂度\n
					 * 此操作具有 O(1) 阶复杂度
					 */
					void switch_rows(const int row1, const int row2);

					/**
					 * @brief 交换矩阵的两列
					 * @param column1 列号1
					 * @param column2 列号2
					 * @throw std::out_of_range 若参数 column1 或 column2 越界, 则抛出此异常
					 * @par 时间复杂度\n
					 * 此操作具有 O(row) 阶复杂度. 其中, row 表示被操作矩阵的行数
					 */
					void switch_columns(const int column1, const int column2);

					/**
					 * @brief 令矩阵中指定行上的每一个元素均乘上系数 k
					 * @param k 系数
					 * @param row_dest 被乘行行号
					 * @throw std::out_of_range 若参数 row_dest 越界, 则抛出此异常
					 */
					void kmr(const double k, const int row_dest);

					/**
					 * @brief 将矩阵 row_from 行的 k 倍加到 row_dest 行上
					 * @param k 系数
					 * @param row_from 被乘行行号
					 * @param row_dest 被加行行号
					 * @throw std::out_of_range 若参数 row_from 或 row_dest 越界, 则抛出此异常
					 */
					void kmr_plus_to_another(const double k, const int row_from, const int row_dest);

					/**
					 * @brief 令矩阵中指定列上的每一个元素均乘上系数 k
					 * @param k 系数
					 * @param column_dest 被乘列列号
					 * @throw std::out_of_range 若参数 column_dest 越界, 则抛出此异常
					 */
					void kmc(const double k, const int column_dest);

					/**
					 * @brief 将矩阵 column_from 列的 k 倍加到 column_dest 列上
					 * @param k 系数
					 * @param column_from 被乘列列号
					 * @param column_dest 被加列列号
					 * @throw std::out_of_range 若参数 column_from 或 column_dest 越界, 则抛出此异常
					 */
					void kmc_plus_to_another(const double k, const int column_from, const int column_dest);

					void do_optimize_rows() throw (std::invalid_argument); //对本矩阵进行优化

					double det() const throw (std::invalid_argument);
					Matrix Adjugate_matrix() const throw (std::invalid_argument);//返回本方阵的伴随矩阵
					Matrix Inverse_matrix() const throw (std::invalid_argument);//返回本方阵的逆矩阵,当逆矩阵不存在时抛出异常

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
					 * @brief 计算一个矩阵的 n 次幂
					 * @par 计算规则\n
					 * - 若 n 为负数, 则计算基数矩阵的逆矩阵的 -n 次幂\n
					 * - 若 n 为 0, 则返回同样大小的单位矩阵\n
					 * - 若 n 为 1, 则返回原矩阵的拷贝
					 * @param A 基数矩阵
					 * @param n 次数
					 * @return A 的 n 次幂
					 * @throw std::invalid_argument 当 n 不等于 1 时, 要求基数矩阵必须为方阵, 否则抛出此异常
					 * @remark 表达式 A ^ n 完全等效于函数表达式 pow(A, n)
					 * @see const Matrix pow(const Matrix & A, const int n )
					 */
					friend const Matrix operator^(const Matrix &A, const int n);

					/**
					 * @brief 将两个矩阵按竖直方向连接
					 * @param A 待连接矩阵 A
					 * @param B 待连接矩阵 B
					 * @return 连接生成的矩阵
					 * @par 使用示例\n
					 * 假设有矩阵\n
					 * >
					 * >         | 1 2 |          | 7 4 |
					 * >     A = | 3 5 |      B = | 4 5 |
					 * >         | 7 9 |          | 0 1 |
					 * >
					 * 则表达式 A && B 返回的结果矩阵 result 为\n
					 * >
					 * >              | 1 2 |
					 * >              | 3 5 |
					 * >     result = | 7 9 |
					 * >              | 7 4 |
					 * >              | 4 5 |
					 * >              | 0 1 |
					 * >
					 *
					 * @throw std::invalid_argument 当两个待连接的矩阵的列数不一致时, 抛出此异常
					 * @see const Matrix operator||(const Matrix &A, const Matrix &B)
					 */
					friend const Matrix operator&&(const Matrix &A, const Matrix &B);

					/**
					 * @brief 将两个矩阵按水平方向连接
					 * @param A 待连接矩阵 A
					 * @param B 待连接矩阵 B
					 * @return 连接生成的矩阵
					 * @par 使用示例\n
					 * 假设有矩阵\n
					 * >
					 * >         | 1 2 |         | 7 4 9 |
					 * >     A = | 3 5 |     B = | 4 5 6 |
					 * >         | 7 9 |         | 0 1 2 |
					 * >
					 * 则表达式 A || B 返回的结果矩阵 result 为\n
					 * >
					 * >              | 1 2 7 4 9 |
					 * >     result = | 3 5 4 5 6 |
					 * >              | 7 9 0 1 2 |
					 * >
					 *
					 * @throw std::invalid_argument 当两个待连接的矩阵的行数不一致时, 抛出此异常
					 * @see const Matrix operator &&(const Matrix &A, const Matrix &B)
					 */
					friend const Matrix operator||(const Matrix &A, const Matrix &B);

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

					friend void operator<<=(Matrix &tar, Matrix &src); //将矩阵src的资产转移给tar, src变为与原来同样大小的随机矩阵
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
					const Matrix& operator=(Matrix &&src);
#endif //C++0x

					template <size_t N> friend const Matrix cat(const Matrix (&a)[N]) throw (std::invalid_argument);

					const Matrix sub_of(int up, int down, int left, int right) const throw (std::invalid_argument, std::out_of_range);

					//计算

					/**
					 * @brief 返回一个 n 阶单位矩阵
					 * @param n 阶数
					 * @return n 阶单位矩阵
					 */
					friend const Matrix eye(int n); //构造一个单位矩阵

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
					 * @see const Matrix operator^(const Matrix & A, const int n )
					 */
					friend const Matrix pow(const Matrix &A, const int n);

					friend double tr(const Matrix &src) throw (std::invalid_argument); //返回方阵的迹
					friend const Matrix transpose_of(const Matrix &A);//构造矩阵A的转置矩阵
					void do_transpose()
					{
						this->operator=(transpose_of(*this));
					}
					friend const Matrix cofactor_of(const Matrix &A, const int x, const int y) throw (std::out_of_range); //构造矩阵A的余子式A(x,y)
					void do_cofactor(const int row_tar, const int column_tar) throw (std::out_of_range);//返回一个矩阵划去row_tar 行和 column_tar 列后的矩阵
					friend bool Matcmp(const Matrix &A, const Matrix &B, double eps);

					virtual void test_row(const int row_test) const throw (std::out_of_range);
					virtual void test_column(const int column_test) const throw (std::out_of_range);
					void test_square() const throw (std::invalid_argument);

					friend const Matrix conv2(const Matrix &core, const Matrix &B, int size = 0);//矩阵卷积

					friend void std::swap(Matrix &a, Matrix &b);
				};

			template <size_t N>
			const Matrix cat(const Matrix (&a)[N]) throw (std::invalid_argument)
			{
				int row_total = a[0].row;
				int column_total = a[0].column;
				for (size_t i = 1; i < N; i++) {
					if (a[i].row != row_total) {
						throw std::invalid_argument("串联的矩阵的行数不一致");
					} else {
						column_total += a[i].column;
					}
				}

				Matrix result(row_total, column_total);
				int column_covered = 0;
				for (const Matrix *it = a, *end = a + N; it != end; ++it) { //数组循环
					for (int j = 0; j < row_total; j++) { //行循环
						std::copy(it->p[j], it->p[j] + it->column, result.p[j] + column_covered);
					}
					column_covered += it->column;
				}
				return result;
			}

			//应用部分

			const Matrix rotate_X(double sigma);
			const Matrix rotate_Y(double sigma);
			const Matrix rotate_Z(double sigma);

			void rotate_X(double sigma, const double& x0, double& y0, double& z0) throw ();
			void rotate_Y(double sigma, double& x0, const double& y0, double& z0) throw ();
			void rotate_Z(double sigma, double& x0, double& y0, const double& z0) throw ();

			template <size_t M, size_t N>
			Matrix::Matrix(const double (&src)[M][N], const int row, const int column) :
					Array_2d<double>(src, row, column)
			{
			}

		}/* namespace matrix */

	}/* namespace math */

} /* namespace kerbal */

#endif	/* End _MATRIX_H_ */
