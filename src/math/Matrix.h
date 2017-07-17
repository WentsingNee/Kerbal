#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <stdarg.h>

#include "basic_math.h"
#include "..\array_serve.h"
#include "..\array_2d.h"
#include "randnum.h"

//#pragma message(__DATE__ "  " __TIME__"  正在编译"__FILE__)

using namespace std;

enum Frame
{
	Fr_RtMatrix, Fr_RdMatrix, Fr_Det, Fr_double, Fr_Null
};

static string Corner_RtMatrix[] = { "┌", "┐", "└", "┘", "│" };
static string Corner_RdMatrix[] = { "╭", "╮", "╰", "╯", "│" };
static string Corner_Det[] = { " ", " ", " ", " ", "│" };
static string Corner_double[] = { " ", " ", " ", " ", "║" };

class Matrix: public Array_2d<double>
{

	public:
		Matrix();
		Matrix(const int row, const int column, bool if_set0 = true);
		Matrix(const int row, const int column, const double rand_min, const double rand_max); //构造一个随机矩阵
//		Matrix(const int row, const int column, int argc, ...); //利用可变参数表进行构造

		template <class T> Matrix(const T *src, const int row, const int column); //利用二维数组进行构造
		Matrix(double arr[], int len, bool in_a_row = true); //利用一维数组进行构造

#if __cplusplus < 201103L //C++0x
//# pragma message("Matrix 为 C++ 11 准备的新特性: 利用初始化列表进行构造")
#else
		Matrix(initializer_list<initializer_list<double>> src); //利用二维初始化列表进行构造
		Matrix(initializer_list<double> src); //利用一维初始化列表进行构造

//		Matrix(Matrix &&src); //转移构造函数
#endif

		Matrix(const Matrix &src); //拷贝构造函数

		~Matrix();

		Matrix call(double (*__pf)(double)) const;

		void print(Frame frame = Fr_RtMatrix, bool print_corner = true, ostream &output = cout) const;
		//void print_to_file(char file_name[],bool if_output_frame) const;

		void switch_columns(const int column1, const int column2) throw (out_of_range);
		void k_multiply_a_row(const double k, const int row_dest) throw (out_of_range);
		void k_multiply_a_row_plus_to_another(const double k, const int row_from, const int row_dest) throw (out_of_range);
		void optimize_rows() throw (invalid_argument); //对本矩阵进行优化
		friend Matrix optimize_rows(Matrix a) throw (invalid_argument);
		void switch_rows(const int row1, const int row2) throw (out_of_range);
		Matrix Cofactor(const int row_tar, const int column_tar) const throw (out_of_range); //返回一个矩阵划去row_tar 行和 column_tar 列后的矩阵

		double Det() const throw (invalid_argument);
		Matrix Adjugate_matrix() const throw (invalid_argument); //返回本方阵的伴随矩阵
		Matrix Inverse_matrix() const throw (invalid_argument); //返回本方阵的逆矩阵,当逆矩阵不存在时抛出异常

		//运算符重载
		friend Matrix operator+(const Matrix &A, const Matrix &B) throw (invalid_argument);
		friend Matrix operator-(const Matrix &A, const Matrix &B) throw (invalid_argument);
		friend Matrix operator*(const double k, const Matrix &A); //数k乘矩阵
		friend Matrix operator*(const Matrix &A, const double k); //矩阵乘数k
		friend Matrix operator*(const Matrix &A, const Matrix &B) throw (invalid_argument); //矩阵乘矩阵
		friend Matrix dot_product(const Matrix &A, const Matrix &B) throw (invalid_argument); //矩阵点乘矩阵
		friend Matrix operator^(const Matrix &A, const int n) throw (invalid_argument); //矩阵的幂

		friend Matrix operator&&(const Matrix &A, const Matrix &B) throw (invalid_argument); //将两个矩阵按竖直方向连接
		friend Matrix operator||(const Matrix &A, const Matrix &B) throw (invalid_argument); //将两个矩阵按水平方向连接

		friend void operator<<=(Matrix &tar, Matrix &src); //将矩阵src的资产转移给tar
		const Matrix& operator=(const Matrix &src);

		template <class T> friend Matrix Cat(const T &a);
//#if __cplusplus < 201103L //C++0x
////# pragma message("Matrix 为 C++ 11 准备的新特性: 转移赋值运算符")
//#else
//		const Matrix& operator=(Matrix &&src);
//#endif

		bool operator==(const Matrix &with) const;
		bool operator!=(const Matrix &with) const;

		//计算
		friend Matrix pow(const Matrix &A, const int n);
		friend double tr(const Matrix &src) throw (invalid_argument);		//返回方阵的迹
		friend Matrix Transpose(const Matrix &A);
		friend Matrix Cofactor(const Matrix &A, const int x, const int y) throw (out_of_range); //构造方阵A的余子式A(x,y)
		friend bool Matcmp(const Matrix &A, const Matrix &B, double eps);
		friend inline void swap(Matrix &A, Matrix &B)
		{
			swap(A.row, B.row);
			swap(A.column, B.column);
			swap(A.p, B.p);
		}

		void test_row(const int row_test) const throw (out_of_range);
		void test_column(const int column_test) const throw (out_of_range);
		void test_square() const throw (invalid_argument);
};

template <class T>
Matrix::Matrix(const T *src, const int row, const int column) //利用二维数组进行构造
{
	if (row > 0 && column > 0) {
		this->row = row;
		this->column = column;

		const size_t size_of_a_row = column * sizeof(double); //这一行为加快速度而存在

		p = new double*[row]; //开辟行
		for (int i = 0; i < row; i++) {
			p[i] = new double[column]; //开辟列
			memcpy(p[i], src + i * size_of_a_row, size_of_a_row);
		}
	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

template <class T>
Matrix Cat(const T &a)
{
	if (array_dimension(a) == 1) {
		int row_total = a[0].row;
		int column_total = a[0].column;
		for (int i = 1; i < arraylen(a); i++) {
			if (a[i].row != row_total) {
				cerr << "串联的矩阵的行数不一致" << endl;
				throw 0;
			} else {
				column_total += a[i].column;
			}
		}

		Matrix result(row_total, column_total, false);
		for (int i = 0, column_covered = 0; i < arraylen(a); i++) { //数组循环
			for (int j = 0; j < row_total; j++) { //行循环
				for (int k = 0; k < a[i].get_column(); k++) { //一个矩阵内的列循环
					result.p[j][column_covered + k] = a[i].p[j][k];
				}
			}
			column_covered += a[i].column;
		}
		return result;
	} else if (array_dimension(a) == 2) {
		return Matrix(1, 1);
	} else {
		throw 0;
	}
}

//应用部分

Matrix rotate_X(double sigma);
Matrix rotate_Y(double sigma);
Matrix rotate_Z(double sigma);

void rotate_X(double sigma, const double& x0, double& y0, double& z0);
void rotate_Y(double sigma, double& x0, const double& y0, double& z0);
void rotate_Z(double sigma, double& x0, double& y0, const double& z0);

#endif	/* End _MATRIX_H_ */
