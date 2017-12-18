#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <fstream>
#include <cmath>

#include "../array_2d.hpp"

namespace kerbal
{
	namespace
	{
		using std::string;
		using std::out_of_range;
		using std::invalid_argument;
	}
	using namespace array_2d;

	enum Frame
	{
		Fr_RtMatrix, Fr_RdMatrix, Fr_Det, Fr_double, Fr_Null
	};

	static const string Corner_RtMatrix[] = { "┌", "┐", "└", "┘", "│" };
	static const string Corner_RdMatrix[] = { "╭", "╮", "╰", "╯", "│" };
	static const string Corner_Det[] = { " ", " ", " ", " ", "│" };
	static const string Corner_double[] = { " ", " ", " ", " ", "║" };

	class Matrix: public Array_2d<double>
	{
		public:
			Matrix() throw ();
			Matrix(const int row, const int column);
			Matrix(const int row, const int column, const double &val);
			Matrix(double (*function)(), const int row, const int column, bool para);
			Matrix(double (*function)(int, int), const int row, const int column, bool para);

			template <size_t M, size_t N>
			Matrix(const double (&src)[M][N], const int row, const int column); //利用二维数组进行构造

			Matrix(const double arr[], int len, bool in_a_row = true); //利用一维数组进行构造

#if __cplusplus >= 201103L //C++0x
			Matrix(std::initializer_list<std::initializer_list<double>> src); //利用二维初始化列表进行构造
			Matrix(std::initializer_list<double> src);//利用一维初始化列表进行构造

			Matrix(Matrix &&src);//转移构造函数
#endif //C++0x

			Matrix(const Matrix &src); //拷贝构造函数

			virtual ~Matrix();

			virtual void print(Frame frame = Fr_RtMatrix, bool print_corner = true, std::ostream &output = std::cout) const;
			void save(const string &file_name) const throw (std::runtime_error);
			static const Matrix load_from(const string &file_name);

			void switch_rows(const int row1, const int row2) throw (out_of_range);
			void switch_columns(const int column1, const int column2) throw (out_of_range);
			void k_multiply_a_row(const double k, const int row_dest) throw (out_of_range);
			void k_multiply_a_row_plus_to_another(const double k, const int row_from, const int row_dest) throw (out_of_range);
			void k_multiply_a_column(const double k, const int column_dest) throw (out_of_range);
			void k_multiply_a_column_plus_to_another(const double k, const int column_from, const int column_dest) throw (out_of_range);

			void do_optimize_rows() throw (invalid_argument); //对本矩阵进行优化

			double Det() const throw (invalid_argument);
			Matrix Adjugate_matrix() const throw (invalid_argument); //返回本方阵的伴随矩阵
			Matrix Inverse_matrix() const throw (invalid_argument); //返回本方阵的逆矩阵,当逆矩阵不存在时抛出异常

			//运算符重载
			friend const Matrix operator+(const Matrix &A, const Matrix &B) throw (invalid_argument);
			friend const Matrix operator-(const Matrix &A, const Matrix &B) throw (invalid_argument);
			friend const Matrix operator*(const double k, const Matrix &A) throw (); //数k乘矩阵
			friend const Matrix operator*(const Matrix &A, const double k) throw (); //矩阵乘数k
			friend const Matrix operator*(const Matrix &A, const Matrix &B) throw (invalid_argument); //矩阵乘矩阵
			friend const Matrix fma(const Matrix &A, const Matrix &B, const Matrix &C) throw (invalid_argument); //return the result of A*B+C , but much faster
			friend const Matrix dot_product(const Matrix &A, const Matrix &B) throw (invalid_argument); //矩阵点乘矩阵
			friend const Matrix operator^(const Matrix &A, const int n) throw (invalid_argument); //矩阵的幂

			friend const Matrix operator&&(const Matrix &A, const Matrix &B) throw (invalid_argument); //将两个矩阵按竖直方向连接
			friend const Matrix operator||(const Matrix &A, const Matrix &B) throw (invalid_argument); //将两个矩阵按水平方向连接

			const Matrix operator+() const;
			const Matrix operator-() const;
			Matrix& operator+=(const Matrix &with) throw (std::invalid_argument);
			Matrix& operator-=(const Matrix &with) throw (std::invalid_argument);
			Matrix& operator*=(double k) throw ();

			friend void operator<<=(Matrix &tar, Matrix &src); //将矩阵src的资产转移给tar, src变为与原来同样大小的随机矩阵
			Matrix& operator=(const Matrix &src);

#if __cplusplus >= 201103L //C++0x
			const Matrix& operator=(Matrix &&src);
#endif //C++0x

			template <class T> friend Matrix Cat(const T &a);

			template <size_t N> friend const Matrix cat(const Matrix (&a)[N]) throw (std::invalid_argument);

			const Matrix sub_of(int up, int down, int left, int right) const throw (invalid_argument, out_of_range);

			//计算
			friend const Matrix eye(int n); //构造一个单位矩阵
			friend const Matrix pow(const Matrix &A, const int n) throw (invalid_argument);
			friend double tr(const Matrix &src) throw (invalid_argument); //返回方阵的迹
			friend const Matrix TransposeOf(const Matrix &A); //构造矩阵A的转置矩阵
			void doTranspose()
			{
				this->operator=(TransposeOf(*this));
			}
			friend const Matrix CofactorOf(const Matrix &A, const int x, const int y) throw (out_of_range); //构造矩阵A的余子式A(x,y)
			void do_Cofactor(const int row_tar, const int column_tar) throw (out_of_range); //返回一个矩阵划去row_tar 行和 column_tar 列后的矩阵
			friend bool Matcmp(const Matrix &A, const Matrix &B, double eps);

			virtual void test_row(const int row_test) const throw (out_of_range);
			virtual void test_column(const int column_test) const throw (out_of_range);
			void test_square() const throw (invalid_argument);

			friend const Matrix conv2(const Matrix &core, const Matrix &B, int size = 0); //矩阵卷积
	};

	template <class T>
	Matrix Cat(const T &a)
	{
		if (array_dimension(a) == 1) {
			int row_total = a[0].row;
			int column_total = a[0].column;
			for (int i = 1; i < arraylen(a); i++) {
				if (a[i].row != row_total) {
					throw std::invalid_argument("串联的矩阵的行数不一致");
				} else {
					column_total += a[i].column;
				}
			}

			Matrix result(row_total, column_total);
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

} /* namespace kerbal */

#endif	/* End _MATRIX_H_ */
