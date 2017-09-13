#include <algorithm>

#include "Matrix.hpp"

#include "../String_serve.hpp"
//#pragma message(__DATE__ "  " __TIME__"  正在编译"__FILE__)

#if __cplusplus < 201103L //C++0x
# pragma message("\n"\
"			* Matrix 使用了 C++ 11 新特性, 请打开 C++ 11 选项以便使用这些新特性\n"\
"					* Matrix 为 C++ 11 准备的新特性: 利用一维初始化列表进行构造\n"\
"					* Matrix 为 C++ 11 准备的新特性: 利用二维初始化列表进行构造"\
)
#endif //C++0x

namespace matrix
{
	namespace
	{
		using namespace std;
	}
	using namespace array_2d;

	Matrix::Matrix()
	{
		row = 0;
		column = 0;
		this->p = NULL;
	}

	Matrix::Matrix(const int row, const int column, bool if_set0) :
			Array_2d(row, column, if_set0)
	{
		//cout<<this<<endl;
	}

	Matrix::Matrix(const int row, const int column, double (*function)()) :
			Array_2d<double>(row, column, function)
	{

	}

	Matrix::Matrix(const int row, const int column, double (*function)(int, int)) :
			Array_2d<double>(row, column, function)
	{

	}

	Matrix::Matrix(double arr[], int len, bool in_a_row)
	{ //利用一维数组进行构造
		if (len > 0) {
			if (in_a_row) {
				this->row = 1;
				this->column = len;

				p = new double*[1];
				memcpy(p[0] = new double[column], arr, column * sizeof(double));
			} else {
				this->row = len;
				this->column = 1;

				p = new double*[row];
				for (int i = 0; i < row; i++) {
					p[i] = new double[1]; //开辟列
					p[i][0] = arr[i];
				}
			}
		} else {
			this->row = 0;
			this->column = 0;
			this->p = NULL;
		}
	}

#if __cplusplus >= 201103L //C++0x
	Matrix::Matrix(initializer_list<initializer_list<double>> src) :
			Array_2d<double>(src)
	{ //利用二维初始化列表进行构造
	}

	Matrix::Matrix(initializer_list<double> src) :
			Array_2d<double>(src)
	{ //利用一维初始化列表进行构造
	}

//Matrix::Matrix(Matrix &&src)
//{ //转移构造函数
//	row = src.row;
//	column = src.column;
//	p = src.p;
//	p[0][0] = 3.14159;
//
//	src.row = 0;
//	src.column = 0;
//	src.p = NULL;
//}

#endif //C++0x

	Matrix::Matrix(const Matrix &src)
	{
		//拷贝构造函数
		//cout<<this<<" cpy= "<<&src<<endl;
		if (src.row > 0 && src.column > 0) {
			this->row = src.row;
			this->column = src.column;

			const size_t size_of_a_row = column * sizeof(double); //这一行为加快速度而存在

			p = new double*[row]; //开辟行
			for (int i = 0; i < row; i++) {
				memcpy(p[i] = new double[column], src.p[i], size_of_a_row);
			}
		} else {
			this->row = 0;
			this->column = 0;
			this->p = NULL;
		}
	}

	Matrix::~Matrix()
	{
	}

	Matrix eye(int n)
	{ //构造一个单位矩阵
		Matrix result(n, n, true);
		for (int i = 0; i < n; ++i) {
			result.p[i][i] = 1;
		}
		return result;
	}

	void Matrix::print(Frame frame, bool print_corner, ostream &output) const
	{
		//Frame frame 默认= Fr_RtMatrix, bool print_corner 默认= true, ostream &output = output
		int i, j;
		const string *corner = NULL;
		switch (frame) {
			case Fr_RtMatrix:
				Array_2d<double>::print(true, print_corner, output);
				return;
			case Fr_RdMatrix:
				corner = Corner_RdMatrix;
				break;
			case Fr_Det:
				corner = Corner_Det;
				break;
			case Fr_double:
				corner = Corner_double;
				break;
			case Fr_Null:
				Array_2d<double>::print(false, false, output);
				return;
		}

		output << resetiosflags(ios::right) << setiosflags(ios::left) << setfill(' '); //清除右对齐, 设置左对齐, 设置不足补空格

		output << corner[0];
		for (j = 0; j < column; j++) {
			output << "  " << setw(12) << " ";
		}
		output << " " << corner[1] << endl;

		for (i = 0; i < row; i++) {
			output << corner[4];

			for (j = 0; j < column; j++) {
				output << "  " << setw(12) << p[i][j];
			}
			output << " " << corner[4] << endl;
		}

		output << corner[2];
		for (j = 0; j < column; j++) {
			output << "  " << setw(12) << " ";
		}
		output << " " << corner[3];
		if (print_corner) {
			output << " " << row << " × " << column;
		}
		output << endl;
	}

	void Matrix::save(const string &file_name) const throw (runtime_error)
	{
		const size_t sizeof_row = sizeof(row);
		const size_t sizeof_column = sizeof(column);
		const size_t sizeof_element = sizeof(p[0][0]);

		ofstream fout(&file_name[0], ios::out | ios::binary);
		//输出位宽信息
		switch (sizeof(size_t)) {
			case 4:
				fout.write((char*) &sizeof_row, 4);
				fout.write("\0\0\0", 4);
				fout.write((char*) &sizeof_column, 4);
				fout.write("\0\0\0", 4);
				fout.write((char*) &sizeof_element, 4);
				fout.write("\0\0\0", 4);
				break;
			case 8:
				fout.write((char*) &sizeof_row, 8);
				fout.write((char*) &sizeof_column, 8);
				fout.write((char*) &sizeof_element, 8);
				break;
			default:
				fout.close();
				throw runtime_error("不支持的位宽");
		}

		fout.write((char*) &row, sizeof(row));
		fout.write((char*) &column, sizeof(column));
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				fout.write((char*) (p[i] + j), sizeof_element);
			}
		}
		fout.close();
	}

	Matrix load_from(const string &file_name)
	{
		ifstream fin(&file_name[0], ios::in | ios::binary);
		fin.ignore(24);
		int row;
		int column;

		fin.read((char*) &row, 4);
		fin.read((char*) &column, 4);

		Matrix tmp(row, column, false);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				fin.read((char*) (tmp.p[i] + j), 8);
			}
		}
		fin.close();
		return tmp;
	}

	void Matrix::switch_rows(const int row1, const int row2) throw (out_of_range)
	{
		//交换矩阵的两行

		this->test_row(row1);
		this->test_row(row2);
		swap(p[row1], p[row2]);
	}

	void Matrix::k_multiply_a_row(const double k, const int row_dest) throw (out_of_range)
	{
		test_row(row_dest);

		for (int i = 0; i < column; i++) {
			p[row_dest][i] *= k;
		}
	}

	void Matrix::k_multiply_a_row_plus_to_another(const double k, const int row_from, const int row_dest) throw (out_of_range)
	{
		test_row(row_from);
		test_row(row_dest);

		if (k == 0.0) {
			return;
		}

		for (int i = 0; i < column; i++) {
			p[row_dest][i] += k * p[row_from][i];
		}
	}

	void Matrix::optimize_rows() throw (invalid_argument)
	{
		//将行列式针对行进行优化
		test_square();
		bool k = false; //是否取相反数
		const int &n = row;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				//bool condition1 = p[j][0] != 0 && p[j + 1][0] == 0;
				//bool condition2 = p[j][0] != 0 && fabs(p[j][0]) < fabs(p[j + 1][0]);
				if (p[j][0] != 0 && p[j + 1][0] == 0) {
					swap(p[j], p[j + 1]);
					k = !k;
				} else {
					if (p[j][0] != 0 && fabs(p[j][0]) < fabs(p[j + 1][0])) {
						swap(p[j], p[j + 1]);
						k = !k;
					}
				}
			}
		}
		for (int i = 0; i < n - 1; i++) {
			if (p[i][0] != 0.0) {
				double ra = p[i][0] / p[n - 1][0];
				for (int j = 0; j < n; j++) { //列循环
					p[i][j] -= ra * p[n - 1][j];
				}
			}
		}

		if (k) { //k == true
			for (int j = 0; j < n; j++) { //列循环
				p[j][0] = -p[j][0];
			}
		}
	}

	Matrix optimize_rows(Matrix a) throw (invalid_argument)
	{
		a.test_square();
		const int &n = a.row;
		bool k = false; //是否取相反数
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				double * &p1 = a.p[j];
				double * &p2 = a.p[j + 1];
				if (p2[0] != 0) {
					if (p1[0] == 0 || fabs(p1[0]) < fabs(p2[0])) {
						swap(p1, p2);
						k = !k;
					}
				}
			}
		}

		for (int i = 0; i < n - 1; i++) {
			if (a.p[i][0] != 0.0) {
				double ra = a.p[i][0] / a.p[n - 1][0];
				for (int j = 0; j < n; j++) { //列循环
					a.p[i][j] -= ra * a.p[n - 1][j];
				}
			}
		}

		if (k) { //k == true
			for (int j = 0; j < n; j++) { //列循环
				double *p_to_first = a.p[j];
				p_to_first[0] = -p_to_first[0];
			}
		}

		return a;
	}

	void Matrix::switch_columns(const int column1, const int column2) throw (out_of_range)
	{
		this->test_column(column1);
		this->test_column(column2);

		for (int i = 0; i < row; i++) {
			swap(p[i][column1], p[i][column2]);
		}
	}

	double Matrix::Det() const throw (invalid_argument)
	{
		this->test_square();

		const int &n = row;
		switch (n) {
			case 1:
				return p[0][0];
			case 2:
				return p[0][0] * p[1][1] - p[0][1] * p[1][0];
			case 3:
				return p[0][0] * (p[1][1] * p[2][2] - p[1][2] * p[2][1])
						- p[0][1] * (p[1][0] * p[2][2] - p[1][2] * p[2][0])
						+ p[0][2] * (p[1][0] * p[2][1] - p[1][1] * p[2][0]);
		}

		double sum = 0.0;
		double det;

		for (int i = 0; i < n; i++) {
			if (p[i][0] != 0.0) { //p[0][i]!=0
				Matrix daishu = CofactorOf(*this, i, 0);

				if (n - 1 >= 4) {
					//如果代数余子式在4阶及以上,则进行行优化
					daishu.optimize_rows();
					//daishu = optimize_rows(daishu);
				}

				det = daishu.Det();
				if (i % 2) {
					//i为奇数
					sum -= p[i][0] * det;
				} else {
					//i为偶数
					sum += p[i][0] * det;
				}
			}
		}
		return sum;
	}

	Matrix Matrix::Adjugate_matrix() const throw (invalid_argument)
	{
		//返回本方阵的伴随矩阵

		this->test_square();
		Matrix result(row, column, false);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if ((i + j) % 2) {
					//i+j为奇数
					result.p[j][i] = -CofactorOf(*this, i, j).Det();
				} else {
					//i+j为偶数
					result.p[j][i] = CofactorOf(*this, i, j).Det();
				}
			}
		}
		return result;
	}

	Matrix Matrix::Inverse_matrix() const throw (invalid_argument)
	{
		//返回本方阵的逆矩阵
		this->test_square();

		double D = this->Det();
		if (D == 0.0) {
			throw invalid_argument("A does not have an inverse matrix");
		}
		Matrix result(this->Adjugate_matrix());
		const double k = 1.0 / D;
		return k * result;
	}

//运算符重载
	Matrix operator+(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{
		int i, j;

		//检查A,B是否同样大小
		if (A.row != B.row) {
			throw invalid_argument("error: row(A) ≠ row(B)");
		}
		if (A.column != B.column) {
			throw invalid_argument("error: column(A) ≠ column(B)");
		}
		const int &row = A.row;
		const int &column = A.column;

		Matrix result(row, column, false);

		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				result.p[i][j] = A.p[i][j] + B.p[i][j];
			}
		}

		return result;
	}

	Matrix operator-(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{
		int i, j;

		//检查A,B是否同样大小
		if (A.row != B.row) {
			throw invalid_argument("error: row(A) ≠ row(B)");
		}
		if (A.column != B.column) {
			throw invalid_argument("error: column(A) ≠ column(B)");
		}
		const int &row = A.row;
		const int &column = A.column;

		Matrix result(row, column, false);

		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				result.p[i][j] = A.p[i][j] - B.p[i][j];
			}
		}

		return result;
	}

	Matrix operator*(const double k, const Matrix &A)
	{
		//数k乘矩阵
		if (k == 1) {
			return A;
		}
		Matrix result(A);
		int i, j;
		for (i = 0; i < A.row; i++) {
			for (j = 0; j < A.column; j++) {
				result.p[i][j] *= k;
			}
		}
		return result;
	}

	Matrix operator*(const Matrix &A, const double k)
	{
		//矩阵乘数k
		if (k == 1) {
			return A;
		}
		Matrix result(A);
		int i, j;
		for (i = 0; i < A.row; i++) {
			for (j = 0; j < A.column; j++) {
				result.p[i][j] *= k;
			}
		}
		return result;
	}

	Matrix operator*(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{
		//矩阵乘矩阵

		//检查A的列数是否等于B的行数
		if (A.column != B.row) {
			throw invalid_argument("error: column(A) ≠ row(B)");
		}
		const int &row = A.row;
		const int &column = B.column;

		Matrix result(row, column, false);

		int i, j, k;
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				result.p[i][j] = 0.0;
				for (k = 0; k < A.column; k++) {
					result.p[i][j] += A.p[i][k] * B.p[k][j];
				}
			}
		}
		return result;
	}

	Matrix fma(const Matrix &A, const Matrix &B, const Matrix &C) throw (invalid_argument)
	{
		// A * B + C

		//检查A的列数是否等于B的行数
		if (A.column != B.row) {
			throw invalid_argument("error: column(A) ≠ row(B)");
		}
		const int &row = A.row;
		const int &column = B.column;
		if (row != C.row || column != C.column) {
			throw invalid_argument("error: size(A*B) ≠ row(C)");
		}

		Matrix result(row, column, false);

		int i, j, k;
		for (i = 0; i < row; ++i) {
			for (j = 0; j < column; ++j) {
				result.p[i][j] = C.p[i][j];
				for (k = 0; k < A.column; ++k) {
					result.p[i][j] += A.p[i][k] * B.p[k][j];
				}
			}
		}
		return result;
	}

	Matrix dot_product(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{
		//矩阵点乘矩阵

		//检查A,B是否同样大小
		if (A.row == 1 && A.column == 1) {
			return A.p[0][0] * B;
		} else if (B.row == 1 && B.column == 1) {
			return B.p[0][0] * A;
		} else if (A.row != B.row) {
			throw invalid_argument("error: row(A) ≠ row(B)");
		} else if (A.column != B.column) {
			throw invalid_argument("error: column(A) ≠ column(B)");
		}
		const int &row = A.row;
		const int &column = A.column;

		Matrix result(row, column, false);
		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				result.p[i][j] = A.p[i][j] * B.p[i][j];
			}
		}

		return result;
	}

	Matrix operator^(const Matrix &A, const int n) throw (invalid_argument)
	{
		//计算矩阵A的n次方

		A.test_square();

		switch (n) {
			case 0:
				return eye(A.row);
			case 1:
				return A;
			case 2:
				return A * A;
			default:
				if (n < 0) {
//					throw invalid_argument("unreasonable n:" + to_string(n));
					return A.Inverse_matrix() ^ -n;
				} else {

					Matrix tmp(A ^ (n / 2));
					tmp = tmp * tmp;
					if (n % 2) {
						//指数为奇数
						tmp = tmp * A;
					}
					return tmp;
				}
		}
	}

	Matrix operator&&(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{
		//将两个矩阵按竖直方向连接
		/*   A
		 *  ---
		 *   B  */

		if (A.column != B.column) {
			throw invalid_argument("串联的矩阵的列数不一致");
		}

		const int row_total = A.row + B.row;
		const int &column_total = A.column;

		Matrix result(row_total, column_total, false);

		const size_t size_of_a_row = column_total * sizeof(double);
		for (int i = 0; i < A.row; i++) { //行循环
			memcpy(result.p[i], A.p[i], size_of_a_row);
		}

		for (int i = 0; i < B.row; i++) { //行循环
			memcpy(result.p[A.row + i], B.p[i], size_of_a_row);
		}

		return result;
	}

	Matrix operator||(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{
		//将两个矩阵按水平方向连接
		/*   A | B   */

		if (A.row != B.row) {
			throw invalid_argument("串联的矩阵的行数不一致");
		}
		const int &row_total = A.row;
		const int column_total = A.column + B.column;

		Matrix result(row_total, column_total, false);

		const size_t size_of_a_row_of_a_left = A.column * sizeof(double);
		const size_t size_of_a_row_of_a_right = B.column * sizeof(double);
		for (int i = 0; i < row_total; i++) { //行循环
			memcpy(result.p[i], A.p[i], size_of_a_row_of_a_left);
			memcpy(result.p[i] + A.column, B.p[i], size_of_a_row_of_a_right);
		}

		return result;
	}

	void operator<<=(Matrix &tar, Matrix &src)
	{
		//将矩阵src的资产转移给tar
		tar.clear();
		tar.row = src.row;
		tar.column = src.column;
		tar.p = src.p;
		src.p = NULL;
		src.row = 0;
		src.column = 0;
	}

	Matrix& Matrix::operator=(const Matrix &src)
	{
		//cout << this << " = " << &src << endl;
		if (row == src.row) {
			if (column == src.column) { //行,列数都与原来相等
				const size_t size_of_a_row = src.column * sizeof(double);
				for (int i = 0; i < src.row; i++) {
					memcpy(p[i], src.p[i], size_of_a_row);
				}
			} else { //行数与原来相等, 列数不等

				this->column = src.column;
				const size_t size_of_a_row = column * sizeof(double);
				for (int i = 0; i < row; i++) {
					delete[] p[i];
					memcpy(p[i] = new double[column], src.p[i], size_of_a_row);
				}
			}
		} else {
			for (int i = 0; i < row; i++)
				delete[] p[i];
			delete[] p;

			this->row = src.row;
			this->column = src.column;

			p = new double*[row]; //开辟行
			const size_t size_of_a_row = column * sizeof(double);
			for (int i = 0; i < row; i++) {
				memcpy(p[i] = new double[column], src.p[i], size_of_a_row);
			}
		}

		return *this;
	}

//#if __cplusplus < 201103L //C++0x
////# pragma message("Matrix 为 C++ 11 准备的新特性: 转移赋值运算符")
//#else
//const Matrix& Matrix::operator=(Matrix &&src)
//{
//	//转移赋值运算符
//
//	this->clear();
//	row = src.row;
//	column = src.column;
//	p = src.p;
//
//	src.p = NULL;
//	src.row = 0;
//	src.column = 0;
//	return *this;
//}
//#endif

	Matrix pow(const Matrix &A, const int n) throw (invalid_argument)
	{
		return A ^ n;
	}

	double tr(const Matrix &src) throw (invalid_argument)
	{
//返回方阵的迹
		src.test_square();
		double result = 0;
		for (int i = 0; i < src.row; i++) {
			result += src.p[i][i];
		}
		return result;
	}

	void Matrix::test_row(const int row_test) const throw (out_of_range)
	{
		if (row_test < 0 || row_test >= this->row) {
			throw out_of_range(
					"The " + to_string(this->row) + " × " + to_string(this->column) + " Matrix doesn't have the no."
							+ to_string(row_test) + " row!");
		}
	}

	void Matrix::test_column(const int column_test) const throw (out_of_range)
	{
		if (column_test < 0 || column_test >= this->column) {
			throw out_of_range(
					"The " + to_string(this->row) + " × " + to_string(this->column) + " Matrix doesn't have the no."
							+ to_string(column_test) + " column!");
		}
	}

	void Matrix::test_square() const throw (invalid_argument)
	{
		if (row != column) {
			throw invalid_argument("A is not a square matrix");
		}
	}

	Matrix conv2(const Matrix &core, const Matrix &A, int size)
	{ //矩阵卷积
		int i, j;
		int n, m;
		Matrix z(A.row + core.row - 1, A.column + core.column - 1, true);
		Matrix z2(A.row, A.column, true);
		for (i = 0; i < A.row + core.row - 1; ++i)
			for (j = 0; j < A.column + core.column - 1; ++j) {
				for (m = 0; m < A.row; ++m)
					for (n = 0; n < A.column; ++n)
						if ((m <= i) && (i < m + core.row) && (n <= j) && (j < n + core.column))
							z.p[i][j] += A.p[m][n] * core.p[i - m][j - n];
			}
		for (i = 0; i < A.row; ++i)
			for (j = 0; j < A.column; ++j) {
				z2.p[i][j] = z.p[i + (core.row - 1) / 2][j + (core.column - 1) / 2];
			}
		switch (size) {
			case 0:
				return z;
			case 1:
				return z2;
			default:
				return z;
		}
	}

//计算
	bool Matcmp(const Matrix &A, const Matrix &B, double eps)
	{
		for (int i = 0; i < A.row; i++) {
			for (int j = 0; j < A.column; j++) {
				if (fabs(A.p[i][j] - B.p[i][j]) > eps) {
					return false;
				}
			}
		}
		return true;
	}

	Matrix TransposeOf(const Matrix &A)
	{
		//返回矩阵A的转置矩阵
		Matrix result(A.column, A.row, false);
		for (int i = 0; i < result.row; i++) {
			for (int j = 0; j < result.column; j++) {
				result.p[i][j] = A.p[j][i];
			}
		}
		return result;
	}

	Matrix CofactorOf(const Matrix &A, const int row_tar, const int column_tar) throw (out_of_range)
	{
		//构造方阵A的余子式A(x,y)

		A.test_row(row_tar);
		A.test_column(column_tar);

		Matrix result(A.row - 1, A.column - 1, false);

		const size_t size_of_a_row_of_a_left = column_tar * sizeof(double); //这一行为加快速度而存在
		const size_t size_of_a_row_of_a_right = (A.column - 1 - column_tar) * sizeof(double); //这一行为加快速度而存在
		for (int i = 0; i < row_tar; i++) {
			memcpy(result.p[i], A.p[i], size_of_a_row_of_a_left);
			memcpy(result.p[i] + column_tar, A.p[i] + column_tar + 1, size_of_a_row_of_a_right);
		}
		for (int i = row_tar + 1; i < A.row; i++) {
			memcpy(result.p[i - 1], A.p[i], size_of_a_row_of_a_left);
			memcpy(result.p[i - 1] + column_tar, A.p[i] + column_tar + 1, size_of_a_row_of_a_right);
		}
		return result;
	}

	void Matrix::do_Cofactor(const int row_tar, const int column_tar) throw (out_of_range)
	{
		//返回一个矩阵划去row_tar 行和 column_tar 列后的矩阵
		this->operator =(CofactorOf(*this, row_tar, column_tar));
	}

//应用部分
	namespace rotate_matrix
	{
		Matrix rotate_X(double sigma)
		{
			double cosine = cos(sigma);
			double sine = sin(sigma);
			double a[3][3] = { 1, 0, 0, 0, cosine, -sine, 0, sine, cosine };
			return Matrix(a, 3, 3);
		}

		Matrix rotate_Y(double sigma)
		{
			double cosine = cos(sigma);
			double sine = sin(sigma);
			double a[3][3] = { cosine, 0, sine, 0, 1, 0, -sine, 0, cosine };
			return Matrix(a, 3, 3);
		}

		Matrix rotate_Z(double sigma)
		{
			double cosine = cos(sigma);
			double sine = sin(sigma);
			double a[3][3] = { cosine, -sine, 0, sine, cosine, 0, 0, 0, 1 };
			return Matrix(a, 3, 3);
		}

		void rotate_X(double sigma, const double& x0, double& y0, double& z0)
		{
			double cosine = cos(sigma);
			double sine = sin(sigma);
			double y1 = y0 * cosine - z0 * sine;
			double z1 = y0 * sine + z0 * cosine;

			y0 = y1;
			z0 = z1;
		}

		void rotate_Y(double sigma, double& x0, const double& y0, double& z0)
		{
			double cosine = cos(sigma);
			double sine = sin(sigma);
			double x1 = x0 * cosine + z0 * sine;
			double z1 = -x0 * sine + z0 * cosine;

			x0 = x1;
			z0 = z1;
		}

		void rotate_Z(double sigma, double& x0, double& y0, const double& z0)
		{
			double cosine = cos(sigma);
			double sine = sin(sigma);
			double x1 = x0 * cosine - y0 * sine;
			double y1 = x0 * sine + y0 * cosine;

			x0 = x1;
			y0 = y1;
		}
	} /* namespace rotate_matrix */

} /* namespace matrix */

/*void Matrix::print_to_file(char file_name[],bool if_output_frame) const
 {


 // 保存cout流缓冲区指针
 streambuf* coutBuf = cout.rdbuf();

 ofstream of(file_name);
 // 获取文件out.txt流缓冲区指针
 streambuf* fileBuf = of.rdbuf();

 // 设置cout流缓冲区指针为out.txt的流缓冲区指针
 cout.rdbuf(fileBuf);

 this->print();

 of.flush();
 of.close();

 // 恢复cout原来的流缓冲区指针
 cout.rdbuf(coutBuf);
 //cout << "Write Personal Information over..." << endl;



 //	int i,j;
 //	string separator="\t";
 //
 //
 //	cout<<"┌";
 //	for(j=0; j<=column-1; j++) {
 //		cout<<"\t";
 //	}
 //	cout<<" ┐"<<endl;
 //
 //
 //	for(i=0; i<=row-1; i++) {
 //		//cout<<"\t";
 //		for(j=0; j<=column-1; j++) {
 //			if(j==0) {
 //				cout<<"│ ";
 //			} else {
 //				cout<<"   ";
 //			}
 //			cout<<p[i][j];
 //			if(j!=column-1) {
 //				cout<<" "<<separator;
 //			}
 //		}
 //		cout<<"\t │"<<endl;
 //	}
 //
 //
 //	cout<<"└";
 //	for(j=0; j<=column-1; j++) {
 //		cout<<"\t";
 //	}
 //	cout<<" ┘"<<endl;

 }*/

//测试行列式计算功能的代码
/*	unsigned long k;

 #define N 20
 int a[N][N];
 for(int i=0; i<=N-1; i++) {
 for(int j=0; j<=N-1; j++) {
 a[i][j]=(int)rand_between(-10,10);
 }
 }

 Matrix B(a);
 B.print();
 Matrix C=1.5*B;
 cout<<C.get_element(2,2)<<endl;
 C.print();

 k=GetTickCount();
 printf("%.5f\n",B.Det());
 cout<<GetTickCount()-k<<"ms"<<endl;*/
